/*
 * Copyright 2004-2017 Cray Inc.
 * Other additional copyright holders may be indicated within.
 *
 * The entirety of this work is licensed under the Apache License,
 * Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License.
 *
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "resolveFunction.h"

#include "astutil.h"
#include "CatchStmt.h"
#include "CForLoop.h"
#include "DeferStmt.h"
#include "driver.h"
#include "expr.h"
#include "ForLoop.h"
#include "ForallStmt.h"
#include "iterator.h"
#include "LoopStmt.h"
#include "ParamForLoop.h"
#include "passes.h"
#include "resolution.h"
#include "resolveIntents.h"
#include "stmt.h"
#include "stringutil.h"
#include "symbol.h"
#include "TryStmt.h"
#include "view.h"
#include "WhileStmt.h"

#include <set>

static void resolveFormals(FnSymbol* fn);

static void resolveSpecifiedReturnType(FnSymbol* fn);

static bool isFollowerIterator(FnSymbol* fn);
static bool isVecIterator(FnSymbol* fn);

static void setScalarPromotionType(AggregateType* at);
static void fixTypeNames(AggregateType* at);

static void insertUnrefForArrayReturn(FnSymbol* fn);

static void instantiateDefaultConstructor(FnSymbol* fn);

/************************************* | **************************************
*                                                                             *
*                                                                             *
*                                                                             *
************************************** | *************************************/

void resolveSignatureAndFunction(FnSymbol* fn) {
  resolveSignature(fn);
  resolveFunction(fn);
}

/************************************* | **************************************
*                                                                             *
*                                                                             *
*                                                                             *
************************************** | *************************************/

void resolveSignature(FnSymbol* fn) {
  if (fn->hasFlag(FLAG_GENERIC) == false) {
    static std::set<FnSymbol*> done;

    if (done.find(fn) == done.end()) {
      done.insert(fn);

      resolveFormals(fn);

      if (fn->retExprType != NULL) {
        resolveSpecifiedReturnType(fn);
      }

      resolvedFormals.set_add(fn);
    }
  }
}

/************************************* | **************************************
*                                                                             *
*                                                                             *
*                                                                             *
************************************** | *************************************/

static void updateIfRefFormal(FnSymbol* fn, ArgSymbol* formal);

static bool needRefFormal(FnSymbol* fn, ArgSymbol* formal);

static bool shouldUpdateAtomicFormalToRef(FnSymbol* fn, ArgSymbol* formal);

static void resolveFormals(FnSymbol* fn) {
  for_formals(formal, fn) {
    if (formal->type == dtUnknown) {
      if (formal->typeExpr == NULL) {
        formal->type = dtObject;

      } else {
        resolveBlockStmt(formal->typeExpr);

        formal->type = formal->typeExpr->body.tail->getValType();
      }
    }

    if (formal->type->symbol->hasFlag(FLAG_REF) == false) {
      if (formal->type                             != dtString ||
          formal->hasFlag(FLAG_INSTANTIATED_PARAM) == false) {
        updateIfRefFormal(fn, formal);
      }
    }
  }
}

// Fix up value types that need to be ref types.
static void updateIfRefFormal(FnSymbol* fn, ArgSymbol* formal) {
  // For begin functions, copy ranges in if passed by blank intent.
  if (fn->hasFlag(FLAG_BEGIN)                   == true &&
      formal->type->symbol->hasFlag(FLAG_RANGE) == true) {
    if (formal->intent == INTENT_BLANK ||
        formal->intent == INTENT_IN) {
      formal->intent = INTENT_CONST_IN;
    }
  }

  if (needRefFormal(fn, formal) == true) {
    makeRefType(formal->type);

    if (formal->type->refType) {
      formal->type = formal->type->refType;

    } else {
      formal->qual = QUAL_REF;
    }

  // Adjust tuples for intent.
  } else if (formal->type->symbol->hasFlag(FLAG_TUPLE) == true      &&
             formal->hasFlag(FLAG_TYPE_VARIABLE)       == false     &&
             formal                                    != fn->_this &&
             doNotChangeTupleTypeRefLevel(fn, false)   == false) {

    // Let 'in' intent work similarly to the blank intent.
    AggregateType* tupleType = toAggregateType(formal->type);
    IntentTag      intent    = formal->intent;

    if (intent == INTENT_IN) {
      intent = INTENT_BLANK;
    }

    INT_ASSERT(tupleType);

    formal->type = computeTupleWithIntent(intent, tupleType);
  }
}

static bool needRefFormal(FnSymbol* fn, ArgSymbol* formal) {
  bool retval = false;

  if (formal->intent == INTENT_INOUT     ||
      formal->intent == INTENT_OUT       ||
      formal->intent == INTENT_REF       ||
      formal->intent == INTENT_CONST_REF) {
    retval = true;

  } else if (shouldUpdateAtomicFormalToRef(fn, formal) == true) {
    retval = true;

  } else if (fn->hasFlag(FLAG_ITERATOR_FN)     == true &&
             isRecordWrappedType(formal->type) == true) {
    retval = true;

  } else if (formal                              == fn->_this &&
             formal->hasFlag(FLAG_TYPE_VARIABLE) == false     &&
             (isUnion(formal->type)  == true||
              isRecord(formal->type) == true)) {
    retval = true;

  } else {
    retval = false;
  }

  return retval;
}

//
// Generally, atomics must also be passed by reference when
// passed by blank intent.  The following expression checks for
// these cases by looking for atomics passed by blank intent and
// changing their type to a ref type.  Interestingly, this
// conversion does not seem to be required for single-locale
// compilation, but it is for multi-locale.  Otherwise, updates
// to atomics are lost (as demonstrated by
// test/functions/bradc/intents/test_pass_atomic.chpl).
//
// I say "generally" because there are a few cases where passing
// atomics by reference breaks things -- primarily in
// constructors, assignment operators, and tuple construction.
// So we have some unfortunate special checks that dance around
// these cases.
//
// While I can't explain precisely why these special cases are
// required yet, here are the tests that tend to have problems
// without these special conditions:
//
//   test/release/examples/benchmarks/hpcc/ra-atomics.chpl
//   test/types/atomic/sungeun/no_atomic_assign.chpl
//   test/functions/bradc/intents/test_construct_atomic_intent.chpl
//   test/users/vass/barrierWF.test-1.chpl
//   test/studies/shootout/spectral-norm/spectralnorm.chpl
//   test/release/examples/benchmarks/ssca2/SSCA2_main.chpl
//   test/parallel/taskPar/sungeun/barrier/*.chpl
//
static bool shouldUpdateAtomicFormalToRef(FnSymbol* fn, ArgSymbol* formal) {
  return formal->intent                        == INTENT_BLANK &&
         formal->hasFlag(FLAG_TYPE_VARIABLE)   == false        &&
         isAtomicType(formal->type)            == true         &&

         fn->name                              != astrSequals  &&

         fn->hasFlag(FLAG_DEFAULT_CONSTRUCTOR) == false        &&
         fn->hasFlag(FLAG_CONSTRUCTOR)         == false        &&
         fn->hasFlag(FLAG_BUILD_TUPLE)         == false;
}

/************************************* | **************************************
*                                                                             *
*                                                                             *
*                                                                             *
************************************** | *************************************/

static void      protoIteratorClass(FnSymbol* fn);

static FnSymbol* protoIteratorMethod(IteratorInfo* ii,
                                     const char*   name,
                                     Type*         retType);

static void resolveSpecifiedReturnType(FnSymbol* fn) {
  Type* retType = NULL;

  resolveBlockStmt(fn->retExprType);

  retType = fn->retExprType->body.tail->typeInfo();

  if (SymExpr* se = toSymExpr(fn->retExprType->body.tail)) {
    // Try resolving global type aliases
    if (se->symbol()->hasFlag(FLAG_TYPE_VARIABLE) == true) {
      retType = resolveTypeAlias(se);
    }

    if (retType->symbol->hasFlag(FLAG_GENERIC)    == true) {
      SET_LINENO(fn->retExprType->body.tail);

      retType = resolveDefaultGenericTypeSymExpr(se);
    }
  }

  if (retType != dtUnknown) {
    if (retType->symbol->hasFlag(FLAG_TUPLE)   == true   &&
        doNotChangeTupleTypeRefLevel(fn, true) == false) {
      AggregateType* tupleType = toAggregateType(retType);

      retType     = getReturnedTupleType(fn, tupleType);
      fn->retType = retType;

    } else if (fn->returnsRefOrConstRef() == true) {
      makeRefType(retType);

      retType     = retType->refType;
      fn->retType = retType;

    } else {
      fn->retType = retType;
    }

    fn->retExprType->remove();

    if (fn->isIterator() == true && fn->iteratorInfo == NULL) {
      // Note: protoIteratorClass changes fn->retType to the iterator record.
      // The original return type is stored here in retType.
      protoIteratorClass(fn);
    }

  } else {
    fn->retType = retType;
  }

  // Also update the return symbol type
  if (Symbol* ret = fn->getReturnSymbol()) {
    if (ret->type == dtUnknown) {
      ret->type = retType;
    }
  }
}

static void protoIteratorClass(FnSymbol* fn) {
  INT_ASSERT(!fn->iteratorInfo);

  SET_LINENO(fn);

  IteratorInfo* ii = new IteratorInfo();
  fn->iteratorInfo = ii;
  fn->iteratorInfo->iterator = fn;

  const char* className = astr(fn->name);

  if (fn->_this != NULL) {
    className = astr(className, "_", fn->_this->type->symbol->cname);
  }

  ii->iclass = new AggregateType(AGGREGATE_CLASS);

  TypeSymbol* cts = new TypeSymbol(astr("_ic_", className), ii->iclass);

  cts->addFlag(FLAG_ITERATOR_CLASS);
  cts->addFlag(FLAG_POD);

  ii->iclass->addRootType();

  fn->defPoint->insertBefore(new DefExpr(cts));

  ii->irecord = new AggregateType(AGGREGATE_RECORD);

  TypeSymbol* rts = new TypeSymbol(astr("_ir_", className), ii->irecord);

  rts->addFlag(FLAG_ITERATOR_RECORD);

  // TODO -- do a better job of deciding if an iterator record is
  // POD or not POD.
  rts->addFlag(FLAG_NOT_POD);

  if (fn->retTag == RET_REF) {
    rts->addFlag(FLAG_REF_ITERATOR_CLASS);
  }

  fn->defPoint->insertBefore(new DefExpr(rts));

  ii->tag      = it_iterator;
  ii->advance  = protoIteratorMethod(ii, "advance",  dtVoid);
  ii->zip1     = protoIteratorMethod(ii, "zip1",     dtVoid);
  ii->zip2     = protoIteratorMethod(ii, "zip2",     dtVoid);
  ii->zip3     = protoIteratorMethod(ii, "zip3",     dtVoid);
  ii->zip4     = protoIteratorMethod(ii, "zip4",     dtVoid);
  ii->hasMore  = protoIteratorMethod(ii, "hasMore",  dtInt[INT_SIZE_DEFAULT]);
  ii->getValue = protoIteratorMethod(ii, "getValue", fn->retType);
  ii->init     = protoIteratorMethod(ii, "init",     dtVoid);
  ii->incr     = protoIteratorMethod(ii, "incr",     dtVoid);

  // Save the iterator info in the iterator record.
  // The iterator info is still owned by the iterator function.
  ii->irecord->iteratorInfo        = ii;
  ii->irecord->scalarPromotionType = fn->retType;

  ii->yieldedType = fn->retType;
  ii->iteratorRetTag = fn->retTag;

  fn->retType = ii->irecord;
  fn->retTag  = RET_VALUE;

  makeRefType(fn->retType);

  ii->getIterator = new FnSymbol("_getIterator");

  ii->getIterator->addFlag(FLAG_AUTO_II);
  ii->getIterator->addFlag(FLAG_INLINE);
  ii->getIterator->retType = ii->iclass;

  ii->getIterator->insertFormalAtTail(new ArgSymbol(INTENT_BLANK,
                                                    "ir",
                                                    ii->irecord));

  VarSymbol* ret = newTemp("_ic_", ii->iclass);

  ii->getIterator->insertAtTail(new DefExpr(ret));

  CallExpr* icAllocCall = callChplHereAlloc(ret->typeInfo());

  ii->getIterator->insertAtTail(new CallExpr(PRIM_MOVE, ret, icAllocCall));
  ii->getIterator->insertAtTail(new CallExpr(PRIM_SETCID, ret));
  ii->getIterator->insertAtTail(new CallExpr(PRIM_RETURN, ret));

  fn->defPoint->insertBefore(new DefExpr(ii->getIterator));

  // Save the iterator info in the iterator class also.
  // This makes it easy to obtain the iterator given
  // just a symbol of the iterator class type.  This may include _getIterator
  // and _getIteratorZip functions in the module code.
  ii->iclass->iteratorInfo = ii;

  normalize(ii->getIterator);

  resolveFunction(ii->getIterator);
}

static FnSymbol* protoIteratorMethod(IteratorInfo* ii,
                                     const char*   name,
                                     Type*         retType) {
  FnSymbol* fn = new FnSymbol(name);

  fn->addFlag(FLAG_AUTO_II);

  if (strcmp(name, "advance") != 0) {
    fn->addFlag(FLAG_INLINE);
  }

  fn->insertFormalAtTail(new ArgSymbol(INTENT_BLANK, "_mt", dtMethodToken));

  fn->addFlag(FLAG_METHOD);

  fn->_this = new ArgSymbol(INTENT_BLANK, "this", ii->iclass);

  fn->_this->addFlag(FLAG_ARG_THIS);

  fn->retType = retType;

  fn->insertFormalAtTail(fn->_this);

  ii->iterator->defPoint->insertBefore(new DefExpr(fn));

  normalize(fn);

  // Pretend that this function is already resolved.
  // Its body will be filled in during the lowerIterators pass.
  fn->addFlag(FLAG_RESOLVED);

  return fn;
}


/************************************* | **************************************
*                                                                             *
*                                                                             *
*                                                                             *
************************************** | *************************************/

void resolveFunction(FnSymbol* fn) {
  if (fn->isResolved())
    return;

  if (fn->id == breakOnResolveID) {
    printf("breaking on resolve fn:\n");
    print_view(fn);
    gdbShouldBreakHere();
  }

  fn->addFlag(FLAG_RESOLVED);

  if (fn->hasFlag(FLAG_EXTERN)) {
    resolveBlockStmt(fn->body);
    resolveReturnType(fn);
    return;
  }

  //
  // Mark serial loops that yield inside of follower, standalone, and
  // explicitly vectorized iterators as order independent. By using a forall
  // loop or a loop over a vectorized iterator, a user is asserting that the
  // loop can be executed in any iteration order. Here we just mark the
  // iterator's yielding loops as order independent as they are ones that will
  // actually execute the body of the loop that invoked the iterator. Note that
  // for nested loops with a single yield, only the inner most loop is marked.
  //
  if (isFollowerIterator(fn)   ||
      isStandaloneIterator(fn) ||
      isVecIterator(fn)) {
    std::vector<CallExpr*> callExprs;

    collectCallExprs(fn->body, callExprs);

    for_vector(CallExpr, call, callExprs) {
      if (call->isPrimitive(PRIM_YIELD)) {
        if (LoopStmt* loop = LoopStmt::findEnclosingLoop(call)) {
          if (loop->isCoforallLoop() == false) {
            loop->orderIndependentSet(true);
          }
        }
      }
    }
  }

  //
  // Mark leader and standalone parallel iterators for inlining. Also stash a
  // pristine copy of the iterator (required by forall intents)
  //
  if (isLeaderIterator(fn) || isStandaloneIterator(fn)) {
    fn->addFlag(FLAG_INLINE_ITERATOR);
    stashPristineCopyOfLeaderIter(fn, /*ignore_isResolved:*/ true);
  }

  insertFormalTemps(fn);

  resolveBlockStmt(fn->body);

  if (tryFailure) {
    fn->removeFlag(FLAG_RESOLVED);
    return;
  }

  if (fn->hasFlag(FLAG_TYPE_CONSTRUCTOR)) {
    AggregateType* ct = toAggregateType(fn->retType);

    if (!ct) {
      INT_FATAL(fn, "Constructor has no class type");
    }

    setScalarPromotionType(ct);

    if (developer == false) {
      fixTypeNames(ct);
    }
  }

  insertUnrefForArrayReturn(fn);

  resolveReturnType(fn);

  //
  // insert casts as necessary
  //
  insertAndResolveCasts(fn);

  if (fn->isIterator() && !fn->iteratorInfo) {
    protoIteratorClass(fn);
  }

  // Resolve base class type constructors as well.
  if (fn->hasFlag(FLAG_TYPE_CONSTRUCTOR)) {
    forv_Vec(Type, parent, fn->retType->dispatchParents) {
      AggregateType* pt = toAggregateType(parent);
      if (pt                         != NULL     &&
          pt                         != dtObject &&
          pt->defaultTypeConstructor != NULL) {
        resolveSignature(pt->defaultTypeConstructor);

        if (resolvedFormals.set_in(pt->defaultTypeConstructor)) {
          resolveFunction(pt->defaultTypeConstructor);
        }
      }
    }

    AggregateType* ct = toAggregateType(fn->retType);

    if (ct) {
      for_fields(field, ct) {
        if (AggregateType* fct = toAggregateType(field->type)) {
          if (fct->defaultTypeConstructor) {
            resolveSignature(fct->defaultTypeConstructor);

            if (resolvedFormals.set_in(fct->defaultTypeConstructor)) {
              resolveFunction(fct->defaultTypeConstructor);
            }
          }
        }
      }
    }

    if (ct                   != NULL &&
        ct->instantiatedFrom != NULL &&
        (ct->initializerStyle          == DEFINES_INITIALIZER ||
         ct->wantsDefaultInitializer() == true)) {
      // Don't instantiate the default constructor for generic types that
      // define initializers, they don't have one!

    } else {
      // This instantiates the default constructor
      // for  the corresponding type constructor.
      instantiateDefaultConstructor(fn);
    }

    //
    // resolve destructor
    //
    if (ct                                  != NULL  &&
        ct->hasDestructor()                 == false &&
        ct->symbol->hasFlag(FLAG_REF)       == false &&
        isTupleContainingOnlyReferences(ct) == false) {
      BlockStmt* block = new BlockStmt();
      VarSymbol* tmp   = newTemp(ct);
      CallExpr*  call  = new CallExpr("deinit", gMethodToken, tmp);

      // In case resolveCall drops other stuff into the tree ahead
      // of the call, we wrap everything in a block for safe removal.

      block->insertAtHead(call);

      fn->insertAtHead(block);
      fn->insertAtHead(new DefExpr(tmp));

      resolveCallAndCallee(call);

      ct->setDestructor(call->resolvedFunction());

      block->remove();

      tmp->defPoint->remove();
    }
  }

  //
  // mark privatized classes
  //
  if (fn->hasFlag(FLAG_PRIVATIZED_CLASS)) {
    if (fn->getReturnSymbol() == gTrue) {
      fn->getFormal(1)->type->symbol->addFlag(FLAG_PRIVATIZED_CLASS);
    }
  }

  //
  // make sure methods are in the methods list
  //
  ensureInMethodList(fn);
}

/************************************* | **************************************
*                                                                             *
*                                                                             *
*                                                                             *
************************************** | *************************************/

static bool isIteratorOfType(FnSymbol* fn, Symbol* iterTag);

bool isLeaderIterator(FnSymbol* fn) {
  return isIteratorOfType(fn, gLeaderTag);
}

bool isStandaloneIterator(FnSymbol* fn) {
  return isIteratorOfType(fn, gStandaloneTag);
}

static bool isFollowerIterator(FnSymbol* fn) {
  return isIteratorOfType(fn, gFollowerTag);
}

static bool isVecIterator(FnSymbol* fn) {
  bool retval = false;

  if (fn->isIterator() == true) {
    retval = fn->hasFlag(FLAG_VECTORIZE_YIELDING_LOOPS);
  }

  return retval;
}

// Simple wrappers to check if a function is a specific type of iterator
static bool isIteratorOfType(FnSymbol* fn, Symbol* iterTag) {
  bool retval = false;

  if (fn->isIterator() == true) {
    for_formals(formal, fn) {
      if (formal->type == iterTag->type && paramMap.get(formal) == iterTag) {
        retval = true;
        break;
      }
    }
  }

  return retval;
}

/************************************* | **************************************
*                                                                             *
*                                                                             *
*                                                                             *
************************************** | *************************************/

static void setScalarPromotionType(AggregateType* at) {
  for_fields(field, at) {
    if (strcmp(field->name, "_promotionType") == 0) {
      at->scalarPromotionType = field->type;
    }
  }
}

static void fixTypeNames(AggregateType* at) {
  const char defaultDomainName[] = "DefaultRectangularDom";

  if (at->symbol->hasFlag(FLAG_BASE_ARRAY) == false &&
      isArrayClass(at)                     ==  true) {
    const char* domainType = at->getField("dom")->type->symbol->name;
    const char* eltType    = at->getField("eltType")->type->symbol->name;

    at->symbol->name = astr("[", domainType, "] ", eltType);
  }

  if (at->instantiatedFrom                                          != NULL &&
      strcmp(at->instantiatedFrom->symbol->name, defaultDomainName) == 0) {
    at->symbol->name = astr("domain",
                            at->symbol->name + strlen(defaultDomainName));
  }

  if (isRecordWrappedType(at) == true) {
    at->symbol->name = at->getField("_instance")->type->symbol->name;
  }
}

/************************************* | **************************************
*                                                                             *
* If the returnSymbol of 'fn' is assigned to from an _array record, insert    *
* an autoCopy for that _array. If the autoCopy has not yet been resolved,     *
* this function will call 'resolveAutoCopyEtc'.                               *
*                                                                             *
* This supports the 'copy-out' rule for returning arrays.                     *
*                                                                             *
************************************** | *************************************/

static void insertUnrefForArrayReturn(FnSymbol* fn) {
  Symbol* ret = fn->getReturnSymbol();

  // BHARSH: Should this also check if fn->retTag != RET_TYPE?
  //
  // Do nothing for these kinds of functions:
  if (fn->hasFlag(FLAG_CONSTRUCTOR) ||
      fn->hasFlag(FLAG_NO_COPY_RETURN) ||
      fn->hasFlag(FLAG_UNALIAS_FN) ||
      fn->hasFlag(FLAG_RUNTIME_TYPE_INIT_FN) ||
      fn->hasFlag(FLAG_INIT_COPY_FN) ||
      fn->hasFlag(FLAG_AUTO_COPY_FN) ||
      fn->hasFlag(FLAG_IF_EXPR_FN) ||
      fn->hasFlag(FLAG_RETURNS_ALIASING_ARRAY)) {
    return;
  }

  for_SymbolSymExprs(se, ret) {
    if (CallExpr* call = toCallExpr(se->parentExpr)) {
      if (call->isPrimitive(PRIM_MOVE) && se == call->get(1)) {
        Type* rhsType = call->get(2)->typeInfo();

        // TODO: Should we check if the RHS is a symbol with 'no auto
        // destroy' on it? If it is, then we'd be copying the RHS and it
        // would never be destroyed...
        if (rhsType->symbol->hasFlag(FLAG_ARRAY) == true &&
            isTypeExpr(call->get(2))             == false) {
          Expr*      origRHS = call->get(2)->remove();
          VarSymbol* tmp     = newTemp(arrayUnrefName, rhsType);

          // Used by callDestructors to catch assignment from a ref to
          // 'tmp' when we know we don't want to copy.
          tmp->addFlag(FLAG_NO_COPY);

          call->insertBefore(new DefExpr(tmp));

          CallExpr* init_unref_tmp = new CallExpr(PRIM_MOVE,
                                                  tmp,
                                                  origRHS->copy());
          call->insertBefore(init_unref_tmp);

          CallExpr* unrefCall = new CallExpr("chpl__unref", tmp);

          call->insertAtTail(unrefCall);

          FnSymbol* unrefFn = resolveNormalCall(unrefCall);

          resolveFunction(unrefFn);

          // Relies on the ArrayView variant having the 'unref fn' flag in
          // ChapelArray.
          if (unrefFn->hasFlag(FLAG_UNREF_FN) == false) {
            // If the function does not have this flag, we must be dealing with
            // a non-view array, so we can remove the useless unref call.
            unrefCall->replace(origRHS->copy());

            // Remove now-useless AST
            tmp->defPoint->remove();

            init_unref_tmp->remove();

            INT_ASSERT(unrefCall->inTree() == false);
          }
        }
      }
    }
  }
}

/************************************* | **************************************
*                                                                             *
*                                                                             *
*                                                                             *
************************************** | *************************************/

static void instantiateDefaultConstructor(FnSymbol* fn) {
  if (fn->instantiatedFrom && !fn->hasFlag(FLAG_PARTIAL_TUPLE)) {
    AggregateType* retAt = toAggregateType(fn->retType);
    INT_ASSERT(retAt);

    INT_ASSERT(!retAt->defaultInitializer);

    FnSymbol* instantiatedFrom = fn->instantiatedFrom;

    while (instantiatedFrom->instantiatedFrom) {
      instantiatedFrom = instantiatedFrom->instantiatedFrom;
    }

    AggregateType* instanceRetAt = toAggregateType(instantiatedFrom->retType);

    INT_ASSERT(instanceRetAt);

    CallExpr* call = new CallExpr(instanceRetAt->defaultInitializer);

    // This should not be happening for iterators.
    TypeSymbol* ts = instanceRetAt->symbol;

    INT_ASSERT(!ts->hasEitherFlag(FLAG_ITERATOR_RECORD, FLAG_ITERATOR_CLASS));

    for_formals(formal, fn) {
      if (formal->type == dtMethodToken || formal == fn->_this) {
        call->insertAtTail(formal);

      } else if (paramMap.get(formal)) {
        call->insertAtTail(new NamedExpr(formal->name,
                                         new SymExpr(paramMap.get(formal))));

      } else {
        Symbol* field = fn->retType->getField(formal->name);

        if (instantiatedFrom->hasFlag(FLAG_TUPLE)) {
          call->insertAtTail(field);
        } else {
          call->insertAtTail(new NamedExpr(formal->name, new SymExpr(field)));
        }
      }
    }

    fn->insertBeforeEpilogue(call);

    resolveCall(call);

    retAt->defaultInitializer = call->resolvedFunction();

    INT_ASSERT(retAt->defaultInitializer);

    call->remove();
  }
}

/************************************* | **************************************
*                                                                             *
*                                                                             *
*                                                                             *
************************************** | *************************************/

static void computeReturnTypeParamVectors(BaseAST*      ast,
                                          Symbol*       retSymbol,
                                          Vec<Type*>&   retTypes,
                                          Vec<Symbol*>& retParams);

void resolveReturnType(FnSymbol* fn) {
  Symbol* ret     = fn->getReturnSymbol();
  Type*   retType = ret->type;

  if (retType == dtUnknown) {
    Vec<Type*>   retTypes;
    Vec<Symbol*> retParams;

    computeReturnTypeParamVectors(fn, ret, retTypes, retParams);

    if (retTypes.n == 1) {
      retType = retTypes.head();

    } else if (retTypes.n > 1) {
      // adjust the reference level:
      //  if they are all references, leave it that way
      //  otherwise make them all values.
      bool allRef   = true;
      bool allValue = true;

      for (int i = 0; i < retTypes.n; i++) {
        if (isReferenceType(retTypes.v[i])) {
          allValue = false;
        } else {
          allRef = false;
        }
      }

      // If there is a mix, adjust the return types to be values.
      if (!allValue && !allRef) {
        for (int i = 0; i < retTypes.n; i++) {
          retTypes.v[i] = retTypes.v[i]->getValType();
        }
      }

      for (int i = 0; i < retTypes.n; i++) {
        bool best = true;

        for (int j = 0; j < retTypes.n; j++) {
          if (retTypes.v[i] != retTypes.v[j]) {
            bool requireScalarPromotion = false;

            if (canDispatch(retTypes.v[j],
                            retParams.v[j],
                            retTypes.v[i],
                            fn,
                            &requireScalarPromotion) == false) {
              best = false;
            }

            if (requireScalarPromotion) {
              best = false;
            }
          }
        }

        if (best) {
          retType = retTypes.v[i];
          break;
        }
      }
    }

    if (!fn->iteratorInfo) {
      if (retTypes.n == 0) {
        retType = dtVoid;
      }
    }
  }

  // For tuples, generally do not allow a tuple to contain a reference
  // when it is returned
  if (retType->symbol->hasFlag(FLAG_TUPLE)   ==  true &&
      doNotChangeTupleTypeRefLevel(fn, true) == false) {
    // Compute the tuple type without any refs
    // Set the function return type to that type.
    AggregateType* tupleType = toAggregateType(retType);

    INT_ASSERT(tupleType);

    retType = getReturnedTupleType(fn, tupleType);
  }

  ret->type = retType;

  if (!fn->iteratorInfo) {
    if (retType == dtUnknown) {
      USR_FATAL(fn, "unable to resolve return type");
    }

    fn->retType = retType;
  }

}

static void computeReturnTypeParamVectors(BaseAST*      ast,
                                          Symbol*       retSymbol,
                                          Vec<Type*>&   retTypes,
                                          Vec<Symbol*>& retParams) {
  if (CallExpr* call = toCallExpr(ast)) {
    if (call->isPrimitive(PRIM_MOVE)) {
      if (SymExpr* sym = toSymExpr(call->get(1))) {
        if (sym->symbol() == retSymbol) {
          if (SymExpr* sym = toSymExpr(call->get(2))) {
            retParams.add(sym->symbol());
          } else {
            retParams.add(NULL);
          }

          retTypes.add(call->get(2)->typeInfo());
        }
      }
    }
  }

  AST_CHILDREN_CALL(ast,
                    computeReturnTypeParamVectors,
                    retSymbol,
                    retTypes,
                    retParams);
}

/************************************* | **************************************
*                                                                             *
*                                                                             *
*                                                                             *
************************************** | *************************************/

Type* getReturnedTupleType(FnSymbol* fn, AggregateType* retType) {
  Type* retval = NULL;

  INT_ASSERT(retType->symbol->hasFlag(FLAG_TUPLE));

  if (fn->returnsRefOrConstRef() == true) {
    retval = computeTupleWithIntent(INTENT_REF, retType);

  } else {
    // Compute the tuple type without any refs
    retval = computeNonRefTuple(retType);
  }

  return retval;
}

/************************************* | **************************************
*                                                                             *
*                                                                             *
*                                                                             *
************************************** | *************************************/

static bool formalRequiresTemp(ArgSymbol* formal);

static bool backendRequiresCopyForIn(Type* t);

static void addLocalCopiesAndWritebacks(FnSymbol*  fn,
                                        SymbolMap& formals2vars);

static bool typeHasRefField(Type* type);

static bool hasRefField(Type* type);

void insertFormalTemps(FnSymbol* fn) {
  SymbolMap formals2vars;

  for_formals(formal, fn) {
    if (formalRequiresTemp(formal)) {
      SET_LINENO(formal);

      VarSymbol* tmp = newTemp(astr("_formal_tmp_", formal->name));

      if (formal->hasFlag(FLAG_CONST_DUE_TO_TASK_FORALL_INTENT)) {
        tmp->addFlag(FLAG_CONST_DUE_TO_TASK_FORALL_INTENT);
      }

      formals2vars.put(formal, tmp);
    }
  }

  if (formals2vars.n > 0) {
    // The names of formals in the body of this function are replaced
    // with the names of their corresponding local temporaries.
    update_symbols(fn->body, &formals2vars);

    // Add calls to chpl__initCopy to create local copies as necessary.
    // Add writeback code for out and inout intents.
    addLocalCopiesAndWritebacks(fn, formals2vars);
  }
}

// Returns true if the formal needs an internal temporary, false otherwise.
static bool formalRequiresTemp(ArgSymbol* formal) {
  //
  // get the formal's function
  //
  FnSymbol* fn = toFnSymbol(formal->defPoint->parentSymbol);

  INT_ASSERT(fn);

  return
    //
    // 'out' and 'inout' intents are passed by ref at the C level, so we
    // need to make an explicit copy in the codegen'd function */
    //
    (formal->intent == INTENT_OUT ||
     formal->intent == INTENT_INOUT ||
     //
     // 'in' and 'const in' also require a copy, but for simple types
     // (like ints or class references), we can rely on C's copy when
     // passing the argument, as long as the routine is not
     // inlined or an iterator.
     //
     ((formal->intent == INTENT_IN || formal->intent == INTENT_CONST_IN) &&
      (backendRequiresCopyForIn(formal->type) ||
       fn->hasFlag(FLAG_INLINE) ||
       fn->hasFlag(FLAG_ITERATOR_FN)))
     );
}

//
// Can Chapel rely on the compiler's back end (e.g.,
// C) to provide the copy for us for 'in' or 'const in' intents when
// passing an argument of type 't'.
//
static bool backendRequiresCopyForIn(Type* t) {
  return isRecord(t)                     == true ||
         isUnion(t)                      == true ||
         t->symbol->hasFlag(FLAG_ARRAY)  == true ||
         t->symbol->hasFlag(FLAG_DOMAIN) == true;
}


// Given the map from formals to local "_formal_tmp_" variables, this function
// adds code as necessary
//  - to copy the formal into the temporary at the start of the function
//  - and copy it back when done.
// The copy in is needed for "inout", "in" and "const in" intents.
// The copy out is needed for "inout" and "out" intents.
// Blank intent is treated like "const", and normally copies the formal through
// chpl__autoCopy.
// Note that autoCopy is called in this case, but not for "inout", "in" and
// "const in".
// Either record-wrapped types are always passed by ref, or some unexpected
// behavior will result by applying "in" intents to them.
static void addLocalCopiesAndWritebacks(FnSymbol*  fn,
                                        SymbolMap& formals2vars) {
  // Enumerate the formals that have local temps.
  form_Map(SymbolMapElem, e, formals2vars) {
    ArgSymbol* formal = toArgSymbol(e->key); // Get the formal.
    Symbol*    tmp    = e->value;            // Get the temp.

    SET_LINENO(formal);

    // TODO: Move this closer to the location (in code) where we determine
    // whether tmp owns its value or not.  That is, push setting these flags
    // (or not) into the cases below, as appropriate.
    Type* formalType = formal->type->getValType();

    // mark CONST as needed
    if (concreteIntent(formal->intent, formalType) & INTENT_FLAG_CONST) {
      tmp->addFlag(FLAG_CONST);

      if (isRefCountedType(formalType) == false) {
        tmp->addFlag(FLAG_INSERT_AUTO_DESTROY);
      }
    }

    // This switch adds the extra code inside the current function necessary
    // to implement the ref-to-value semantics, where needed.
    switch (formal->intent)
    {
      // Make sure we handle every case.
     default:
      INT_FATAL("Unhandled INTENT case.");
      break;

      // These cases are weeded out by formalRequiresTemp() above.
     case INTENT_PARAM:
     case INTENT_TYPE:
     case INTENT_REF:
     case INTENT_CONST_REF:
      INT_FATAL("Unexpected INTENT case.");
      break;

     case INTENT_OUT:
      if (formal->defaultExpr &&
          formal->defaultExpr->body.tail->typeInfo() != dtTypeDefaultToken) {
        BlockStmt* defaultExpr = formal->defaultExpr->copy();

        fn->insertAtHead(new CallExpr(PRIM_MOVE,
                                      tmp,
                                      defaultExpr->body.tail->remove()));
        fn->insertAtHead(defaultExpr);

      } else {
        AggregateType* formalAt = toAggregateType(formal->getValType());

        if (isNonGenericRecordWithInitializers(formalAt)) {
          fn->insertAtHead(new CallExpr("init",
                                        gMethodToken,
                                        tmp));
          tmp->type = formalAt;

        } else {
          VarSymbol* typeTmp = newTemp("_formal_type_tmp_");

          typeTmp->addFlag(FLAG_MAYBE_TYPE);

          fn->insertAtHead(new CallExpr(PRIM_MOVE,
                                        tmp,
                                        new CallExpr(PRIM_INIT, typeTmp)));

          fn->insertAtHead(new CallExpr(PRIM_MOVE,
                                        typeTmp,
                                        new CallExpr(PRIM_TYPEOF, formal)));

          fn->insertAtHead(new DefExpr(typeTmp));
        }
      }

      tmp->addFlag(FLAG_INSERT_AUTO_DESTROY);
      tmp->addFlag(FLAG_FORMAL_TEMP);
      break;

     case INTENT_INOUT:
      fn->insertAtHead(new CallExpr(PRIM_MOVE,
                                    tmp,
                                    new CallExpr("chpl__initCopy", formal)));

      tmp->addFlag(FLAG_INSERT_AUTO_DESTROY);
      tmp->addFlag(FLAG_FORMAL_TEMP);

      break;

     case INTENT_IN:
     case INTENT_CONST_IN:
      // TODO: Adding a formal temp for INTENT_CONST_IN is conservative.
      // If the compiler verifies in a separate pass that it is never written,
      // we don't have to copy it.
      fn->insertAtHead(new CallExpr(PRIM_MOVE,
                                    tmp,
                                    new CallExpr("chpl__initCopy", formal)));

      tmp->addFlag(FLAG_INSERT_AUTO_DESTROY);
      break;

     case INTENT_BLANK:
     case INTENT_CONST:
     {
       TypeSymbol* ts = formal->type->symbol;

       if (!getRecordWrappedFlags(ts).any()   &&
           !ts->hasFlag(FLAG_ITERATOR_CLASS)  &&
           !ts->hasFlag(FLAG_ITERATOR_RECORD)) {
         if (fn->hasFlag(FLAG_BEGIN)) {
           // autoCopy/autoDestroy will be added later, in parallel pass
           // by insertAutoCopyDestroyForTaskArg()
           fn->insertAtHead(new CallExpr(PRIM_MOVE, tmp, formal));
           tmp->removeFlag(FLAG_INSERT_AUTO_DESTROY);

         } else {
           // Note that because we reject the case of record-wrapped types
           // above, the only way we can get a formal whose call to
           // chpl__autoCopy does anything different from calling
           // chpl__initCopy is if the formal is a tuple containing a
           // record-wrapped type.

           // This is probably not intentional: It gives tuple-wrapped
           // record-wrapped types different behavior from bare record-wrapped
           // types.
           fn->insertAtHead(new CallExpr(PRIM_MOVE,
                                         tmp,
                                         new CallExpr("chpl__autoCopy",
                                                      formal)));

           // WORKAROUND:
           // This is a temporary bug fix that results in leaked memory.
           //
           // Here we avoid calling the destructor for any formals that
           //  are records or have records because the call may result
           //  in repeatedly freeing memory if the user defined
           //  destructor calls delete on any fields.  I think we
           //  probably need a similar change in the INOUT/IN case
           //  above.  See test/types/records/sungeun/destructor3.chpl
           //  and test/users/recordbug3.chpl.
           //
           // For records, this problem should go away if/when we
           //  implement 'const ref' intents and make them the default
           //  for records.
           //
           // Another solution (and the one that would fix records in
           //  classes) is to call the user record's default
           //  constructor if it takes no arguments.  This is not the
           //  currently described behavior in the spec.  This would
           //  require the user to implement a default constructor if
           //  explicit memory allocation is required.
           //
           if (!isAggregateType(formal->type) ||
               (isRecord(formal->type) &&
                ((formal->type->getModule()->modTag==MOD_INTERNAL) ||
                 (formal->type->getModule()->modTag==MOD_STANDARD))) ||
               !typeHasRefField(formal->type))
             tmp->addFlag(FLAG_INSERT_AUTO_DESTROY);
         }

       } else {
         fn->insertAtHead(new CallExpr(PRIM_MOVE, tmp, formal));
         // If this is a simple move, then we did not call chpl__autoCopy to
         // create tmp, so then it is a bad idea to insert a call to
         // chpl__autodestroy later.
         tmp->removeFlag(FLAG_INSERT_AUTO_DESTROY);
       }

       break;
     }
    }

    fn->insertAtHead(new DefExpr(tmp));

    // For inout or out intent, this assigns the modified value back to the
    // formal at the end of the function body.
    if (formal->intent == INTENT_INOUT || formal->intent == INTENT_OUT) {
      fn->insertIntoEpilogue(new CallExpr("=", formal, tmp));
    }
  }
}

static bool typeHasRefField(Type* type) {
  bool retval = false;

  if (AggregateType* ct = toAggregateType(type)) {
    for_fields(field, ct) {
      if (hasRefField(field->typeInfo())) {
        retval = true;
        break;
      }
    }
  }

  return retval;
}

static bool hasRefField(Type* type) {
  bool retval = false;

  if (isPrimitiveType(type)) {
    retval = false;

  } else if (type->symbol->hasFlag(FLAG_OBJECT_CLASS)) {
    retval = false;

  } else if (isClass(type) == false) { // record or union
    if (AggregateType* ct = toAggregateType(type)) {
      for_fields(field, ct) {
        if (hasRefField(field->type)) {
          retval = true;
          break;
        }
      }
    }

  } else {
    retval = true;
  }

  return retval;
}

/************************************* | **************************************
*                                                                             *
*                                                                             *
*                                                                             *
************************************** | *************************************/

static void insertCasts(BaseAST* ast, FnSymbol* fn, Vec<CallExpr*>& casts);

void insertAndResolveCasts(FnSymbol* fn) {
  if (fn->retTag != RET_PARAM) {
    Vec<CallExpr*> casts;

    insertCasts(fn->body, fn, casts);

    forv_Vec(CallExpr, cast, casts) {
      resolveCallAndCallee(cast, true);
    }
  }
}

static void insertCasts(BaseAST* ast, FnSymbol* fn, Vec<CallExpr*>& casts) {
  if (CallExpr* call = toCallExpr(ast)) {
    if (call->parentSymbol == fn) {
      if (call->isPrimitive(PRIM_MOVE)) {
        if (SymExpr* lhs = toSymExpr(call->get(1))) {
          Type* lhsType = lhs->symbol()->type;

          if (lhsType != dtUnknown) {
            Expr*     rhs     = call->get(2);
            Type*     rhsType = rhs->typeInfo();
            CallExpr* rhsCall = toCallExpr(rhs);

            if (call->id == breakOnResolveID)
              gdbShouldBreakHere();

            if (rhsCall && rhsCall->isPrimitive(PRIM_COERCE)) {
              rhsType = rhsCall->get(1)->typeInfo();
            }

            // would this be simpler with getValType?
            bool typesDiffer = (rhsType          != lhsType &&
                                rhsType->refType != lhsType &&
                                rhsType          != lhsType->refType);

            SET_LINENO(rhs);

            // Generally, we want to add casts for PRIM_MOVE that have two
            // different types. This function also handles PRIM_COERCE on the
            // right-hand side by either removing the PRIM_COERCE entirely if
            // the types are the same, or by using a = call if the types are
            // different. It could use a _cast call if the types are different,
            // but the = call works better in cases where an array is returned.

            if (rhsCall && rhsCall->isPrimitive(PRIM_COERCE)) {
              // handle move lhs, coerce rhs
              SymExpr* fromExpr     = toSymExpr(rhsCall->get(1));
              SymExpr* fromTypeExpr = toSymExpr(rhsCall->get(2));

              Symbol*  from         = fromExpr->symbol();
              Symbol*  fromType     = fromTypeExpr->symbol();

              Symbol*  to           = lhs->symbol();

              // Check that lhsType == the result of coercion
              INT_ASSERT(lhsType == rhsCall->typeInfo());

              if (!typesDiffer) {
                // types are the same. remove coerce and
                // handle reference level adjustments. No cast necessary.

                if (rhsType == lhsType) {
                  rhs = new SymExpr(from);

                } else if (rhsType == lhsType->refType) {
                  rhs = new CallExpr(PRIM_DEREF, new SymExpr(from));

                } else if (rhsType->refType == lhsType) {
                  rhs = new CallExpr(PRIM_ADDR_OF, new SymExpr(from));
                }

                CallExpr* move = new CallExpr(PRIM_MOVE, to, rhs);

                call->replace(move);

                casts.add(move);

              } else if (lhsType->symbol->hasFlag(FLAG_HAS_RUNTIME_TYPE) ||
                         rhsType->symbol->hasFlag(FLAG_HAS_RUNTIME_TYPE) ) {

                // Use = if the types differ.  This should cause the 'from'
                // value to be coerced to 'to' if possible or result in an
                // compilation error. We use = here (vs _cast) in order to work
                // better with returning arrays. We could probably use _cast
                // instead of = if fromType does not have a runtime type.

                CallExpr* init     = new CallExpr(PRIM_NO_INIT, fromType);
                CallExpr* moveInit = new CallExpr(PRIM_MOVE, to, init);

                call->insertBefore(moveInit);

                // By resolving =, we will generate an error if from cannot be
                // coerced into to.
                CallExpr* assign = new CallExpr("=", to, from);

                call->insertBefore(assign);

                // Resolve each of the new CallExprs They need to be resolved
                // separately since resolveExpr does not recurse.
                resolveExpr(init);
                resolveExpr(moveInit);
                resolveExpr(assign);

                // We've replaced the move with no-init/assign, so remove it.
                call->remove();

              } else {
                // Add a cast if the types don't match

                // Remove the right-hand-side, which is call->get(2)
                // The code below assumes it is the final argument
                rhs->remove();

                Symbol* tmp = NULL;

                if (SymExpr* se = toSymExpr(fromExpr)) {
                  tmp = se->symbol();

                } else {
                  tmp = newTemp("_cast_tmp_", fromExpr->typeInfo());

                  call->insertBefore(new DefExpr(tmp));
                  call->insertBefore(new CallExpr(PRIM_MOVE, tmp, fromExpr));
                }

                CallExpr* cast = createCast(tmp, lhsType->symbol);

                call->insertAtTail(cast);
                casts.add(cast);
              }

            } else {
              // handle adding casts for a regular PRIM_MOVE

              if (typesDiffer) {

                // Remove the right-hand-side, which is call->get(2)
                // The code below assumes it is the final argument
                rhs->remove();

                // Add a cast if the types don't match
                Symbol* tmp = NULL;

                if (SymExpr* se = toSymExpr(rhs)) {
                  tmp = se->symbol();

                } else {
                  tmp = newTemp("_cast_tmp_", rhs->typeInfo());
                  call->insertBefore(new DefExpr(tmp));
                  call->insertBefore(new CallExpr(PRIM_MOVE,
                                                  tmp,
                                                  rhs->copy()));
                }

                if (lhsType->symbol->hasFlag(FLAG_TUPLE) &&
                    lhs->symbol()->hasFlag(FLAG_RVV)) {
                  // When returning tuples, we might return a
                  // tuple containing a ref, while the return type
                  // is the tuple with no refs. This code adjusts
                  // the AST to compensate.
                  CallExpr* unref = new CallExpr("chpl__unref", tmp);
                  call->insertAtTail(unref);
                  resolveExpr(unref);

                } else {
                  CallExpr* cast = createCast(tmp, lhsType->symbol);
                  call->insertAtTail(cast);
                  casts.add(cast);
                }

              } else {
                // types are the same.
                // handle reference level adjustments. No cast necessary.

                if (rhsType == lhsType->refType) {
                  lhs->remove();
                  rhs->remove();

                  CallExpr* move = new CallExpr(PRIM_MOVE,
                                                lhs,
                                                new CallExpr(PRIM_DEREF, rhs));

                  call->replace(move);

                  casts.add(move);
                }
              }
            }
          }
        }
      }
    }
  }

  AST_CHILDREN_CALL(ast, insertCasts, fn, casts);
}

/************************************* | **************************************
*                                                                             *
*                                                                             *
*                                                                             *
************************************** | *************************************/

void ensureInMethodList(FnSymbol* fn) {
  if (fn->hasFlag(FLAG_METHOD) && fn->_this != NULL) {
    Type* thisType = fn->_this->type->getValType();
    bool  found    = false;

    INT_ASSERT(thisType);
    INT_ASSERT(thisType != dtUnknown);

    forv_Vec(FnSymbol, method, thisType->methods) {
      if (method == fn) {
        found = true;
        break;
      }
    }

    if (found == false) {
      thisType->methods.add(fn);
    }
  }
}
