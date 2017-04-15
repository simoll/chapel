#!/bin/bash

if [ ! -d "$CHPL_HOME" ]
then
  if [ -d "util/chplenv" ]
  then
    export CHPL_HOME="$PWD"
    echo "Detecting CHPL_HOME as $CHPL_HOME"
  else
    echo Exiting: CHPL_HOME not set or not a directory
    exit -1
  fi
fi

PREFIX=""
DEST_DIR=""
if [ -f "$CHPL_HOME/configured-prefix" ]
then
  read -r PREFIX < "$CHPL_HOME/configured-prefix"
fi

if [ ! -z "$PREFIX" ]
then
  if [ ! -d "$PREFIX" ]
  then
    echo "Exiting: Installation prefix path '$PREFIX' does not exist"
    exit -1
  fi
else
  if [ -f "$CHPL_HOME/configured-chpl-home" ]
  then
    read -r DEST_DIR < "$CHPL_HOME/configured-chpl-home"
    if [ ! -d "$DEST_DIR" ]
    then
      echo "Exiting: Installation dest path '$DEST_DIR' does not exist"
      exit -1
    fi
  else
    echo "Exiting: Installation path not configured."
    echo "         See ./configure --help"
    exit -1
  fi
fi

case "$PREFIX" in
  '""')
    echo Exiting: PREFIX was not set.
    echo          ... did you forget to run configure ?
    exit -1
    ;;
  *\\*)
    # For now, fail if PREFIX contains a backslash.
    # The issue is that the C string and Bash variable might treat
    # the prefix differently.
    echo Exiting: PREFIX contains backslash
    echo          ... please use a prefix that does not contain backslash
    exit -1
    ;;
  *)
    ;;
esac

# Gather the version number for the Chapel binary.
export CHPL_HOST_PLATFORM=`"$CHPL_HOME"/util/chplenv/chpl_platform.py host`
VERS=`$CHPL_HOME/bin/$CHPL_HOST_PLATFORM/chpl --version`
# Remove the "chpl Version " part
VERS=${VERS#chpl Version }
# Replace the periods with spaces.
VERS=${VERS//./ }
VERS_ARRAY=($VERS)
MAJOR_VERSION=${VERS_ARRAY[0]}
MINOR_VERSION=${VERS_ARRAY[1]}
VERS="${MAJOR_VERSION}.${MINOR_VERSION}"
echo "Installing Chapel version $VERS"

if [ ! -z "$PREFIX" ]
then
  DEST_RUNTIME_LIB="$PREFIX/lib/chapel/$VERS/runtime/lib"
  DEST_RUNTIME_INCL="$PREFIX/lib/chapel/$VERS/runtime/include"
  DEST_THIRD_PARTY="$PREFIX/lib/chapel/$VERS/third-party"
  DEST_CHPL_HOME="$PREFIX/share/chapel/$VERS"
  echo "Installing Chapel split to bin, lib, share to $PREFIX"
else
  DEST_RUNTIME_LIB="$DEST_DIR/lib"
  DEST_RUNTIME_INCL="$DEST_DIR/runtime/include"
  DEST_THIRD_PARTY="$DEST_DIR/third-party"
  DEST_CHPL_HOME="$DEST_DIR"
  echo "Installing Chapel-as-a-directory to $DEST_DIR"
fi

echo "DEST_RUNTIME_LIB=$DEST_RUNTIME_LIB"
echo "DEST_RUNTIME_INCL=$DEST_RUNTIME_INCL"
echo "DEST_THIRD_PARTY=$DEST_THIRD_PARTY"
echo "DEST_CHPL_HOME=$DEST_CHPL_HOME"

myinstalldir () {
  FROM="$CHPL_HOME/$1"
  TO="$2"
  #echo myinstalldir $FROM $TO
  mkdir -p $TO
  ( cd $FROM ; tar cf - . ) | ( cd $TO ; tar xf - )
  return $?
}

myinstallfile () {
  FROM="$CHPL_HOME/$1"
  TO="$2"
  mkdir -p $TO
  #echo myinstallfile $FROM $TO
  cp $FROM $TO
  return $?
}

myinstallfileto () {
  FROM="$CHPL_HOME/$1"
  TO="$2"
  #echo myinstallfile $FROM $TO
  cp $FROM $TO
  return $?
}


# copy chpl and chpldoc
if [ ! -z "$PREFIX" ]
then
  myinstalldir  "bin/$CHPL_HOST_PLATFORM" "$PREFIX/bin"
else
  myinstalldir  bin                       "$DEST_DIR"/bin
fi

# copy runtime lib
myinstalldir  lib                     "$DEST_RUNTIME_LIB"

# copy runtime include
myinstalldir  runtime/include         "$DEST_RUNTIME_INCL"

# copy README etc
myinstallfile ACKNOWLEDGEMENTS.md     "$DEST_CHPL_HOME"
myinstallfile CHANGES.md              "$DEST_CHPL_HOME"
myinstallfile CONTRIBUTORS.md         "$DEST_CHPL_HOME"
myinstallfile COPYRIGHT               "$DEST_CHPL_HOME"
myinstallfile GOALS.md                "$DEST_CHPL_HOME"
myinstallfile PERFORMANCE.md          "$DEST_CHPL_HOME"
myinstallfile README.rst              "$DEST_CHPL_HOME"
myinstallfile STATUS                  "$DEST_CHPL_HOME"

# copy modules
myinstalldir  modules                 "$DEST_CHPL_HOME"/modules

# copy util/printchplenv 
myinstallfile util/printchplenv       "$DEST_CHPL_HOME"/util/

# copy util/chplenv
myinstalldir  util/chplenv            "$DEST_CHPL_HOME"/util/chplenv/

if [ ! -z "$DEST_DIR" ]
then
  # copy util/setchplenv*, util/quickstart
  for f in util/setchplenv*
  do
    myinstallfile "$f"                "$DEST_CHPL_HOME"/util/
  done

  myinstalldir  util/quickstart       "$DEST_CHPL_HOME"/util/quickstart/
fi

# copy compiler/etc
myinstalldir  compiler/etc            "$DEST_CHPL_HOME"/compiler/etc/

# copy runtime/etc
myinstalldir  runtime/etc             "$DEST_CHPL_HOME"/runtime/etc/

# copy runtime/make
myinstalldir  runtime/make            "$DEST_CHPL_HOME"/runtime/make/

# copy make
# TODO - just Makefile.base, platform, tasks ?
myinstalldir  make                    "$DEST_CHPL_HOME"/make/

# copy third-party makefile snippets
cd third-party
THIRD_PARTY_DIRS=`echo *`
cd ..

for dir in $THIRD_PARTY_DIRS
do
  #echo "Considering 3p dir $dir"
  if [ -f third-party/"$dir"/Makefile.include ]
  then
    for f in third-party/"$dir"/Makefile*
    do
      myinstallfile "$f"  "$DEST_THIRD_PARTY"/"$dir"
    done
  fi
  if [ -d third-party/"$dir"/install ]
  then
    myinstalldir "third-party/$dir/install" "$DEST_THIRD_PARTY/$dir/install/"
  fi
done

# copy utf8-decoder header
myinstallfile third-party/utf8-decoder/utf8-decoder.h "$DEST_THIRD_PARTY"/utf8-decoder/

# copy configured-chplconfig
if [ ! -z "$PREFIX" ]
then
  myinstallfileto  configured-chplconfig  "$PREFIX/lib/chapel/$VERS/chplconfig"
else
  myinstallfileto  configured-chplconfig  "$DEST_CHPL_HOME/chplconfig"
fi
