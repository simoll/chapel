#!/bin/sh

if [ -d llvm ]
then

echo Updating LLVM
cd llvm
git pull
echo Updating CLANG
cd tools/clang
git pull
cd ../..
echo Updating POLLY
cd tools/polly
git pull
cd ../..
#echo Updating RV
#cd tools/rv
##git pull
#cd ../..
echo Updating compiler-rt
cd runtimes/compiler-rt
git pull
cd ../..
cd ..

else

echo Checking out current LLVM trunk
git clone https://git.llvm.org/git/llvm.git llvm
echo Checking out current CLANG trunk
git clone https://git.llvm.org/git/clang.git llvm/tools/clang
echo Checking out current POLLY trunk
git clone https://git.llvm.org/git/polly.git llvm/tools/polly
#echo Checking out current RV trunk
#git clone https://github.com/cdl-saarland/rv llvm/tools/rv
echo Checking out current compiler-rt trunk
git clone https://git.llvm.org/git/compiler-rt.git llvm/runtimes/compiler-rt

echo Applying Chapel patches to LLVM
patch -p0 < llvm-4.0.1-BasicAliasAnalysis-patch.txt
patch -p0 < llvm-4.0.1-ValueTracking-patch.txt


fi
