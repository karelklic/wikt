#!/bin/bash

# get version
version=`awk '/WIKT_VERSION / {print $3}' src/Version.h | sed 's/"//g'`
tmpdir="/tmp/wikt-$version"
mkdir $tmpdir

files=`find data/*.txt -type f`
files+=" AUTHORS COPYING Makefile RELEASE-NOTES Makefile.Debug Makefile.Release wikt.pro wikt.qrc release.sh"
files+=" docs/Doxyfile docs/.gitignore docs/index.html docs/FrontPage.dox"
files+=" .settings .project"
files+=" images src debian data/enwiktionary-20090711.errata"
cp --verbose -r --parents $files $tmpdir

DIR=`pwd`
cd /tmp
tar -cvzf "wikt-$version.tar.gz" "wikt-$version"
mv "wikt-$version.tar.gz" "$DIR/"
rm -r $tmpdir
