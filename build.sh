#!/bin/bash
#
# How to run
# ./build.sh [distribution_dir]
#
# Where distribution_dir is the target directory for the built plugins. Plugins are installed into
# an 'OpenSceneryX' subdirectory within this directory.  If it is not specifid, it defaults to dist/
# 

DISTDIR="$1"

echo Building OpenSceneryX Plugin
echo ============================
echo

if [ -z $DISTDIR ] || [[ ! -d $DISTDIR ]]
then
    echo "Distribution directory not specified or doesn't exist, using dist/"
    DISTDIR="dist/"
fi

mkdir -p $DISTDIR/OpenSceneryX/64

echo Clearing old builds
echo -------------------

rm -r src/build-mac/*
rm -r src/build-lin/*
rm -r src/build-win/*
rm -r $DISTDIR/OpenSceneryX/64/*.xpl

echo
echo Docker build
echo ------------

(cd docker; make)

echo 
echo Deploying to $DISTDIR
echo ---------------------

cp src/build-mac/mac.xpl $DISTDIR/OpenSceneryX/64/mac.xpl
cp src/build-lin/lin.xpl $DISTDIR/OpenSceneryX/64/lin.xpl
cp src/build-win/win.xpl $DISTDIR/OpenSceneryX/64/win.xpl

echo 
echo Finished
echo --------
