#!/bin/bash
#
# How to run
# ./build.sh

echo Building OpenSceneryX Plugin
echo ============================
echo

mkdir -p dist/OpenSceneryX/64

echo Clearing old builds
echo -------------------

rm -r src/build-mac/*
rm -r src/build-lin/*
rm -r src/build-win/*
rm -r dist/OpenSceneryX/64/*.xpl

echo
echo Docker build
echo ------------

(cd docker; make)

echo 
echo Deploying to dist
echo -----------------

cp src/build-mac/mac.xpl dist/OpenSceneryX/64/mac.xpl
cp src/build-lin/lin.xpl dist/OpenSceneryX/64/lin.xpl
cp src/build-win/win.xpl dist/OpenSceneryX/64/win.xpl

echo 
echo Finished
echo --------
