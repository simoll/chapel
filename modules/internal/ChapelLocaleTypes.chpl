/*
 * Copyright 2004-2015 Cray Inc.
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

// ChapelLocaleTypes.chpl
//
module ChapelLocaleTypes {

  //
  // Node and sublocale types and special sublocale values.
  //
  type chpl_nodeID_t = int(32);
  type chpl_sublocID_t = int(32);

  extern const c_sublocid_none: chpl_sublocID_t;
  extern const c_sublocid_any: chpl_sublocID_t;

  extern var chpl_nodeID: chpl_nodeID_t;
}

