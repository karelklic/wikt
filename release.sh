#!/bin/bash

# get version
version=`awk '/WIKT_VERSION / {print $3}' src/libwikt/version.h | sed 's/"//g'`
tmpdir="/tmp/wikt-$version"
mkdir $tmpdir

files=" AUTHORS COPYING Makefile README wikt.pri wikt.pro release.sh sync_web.sh"
files+=" debian docs src tests web"
files+=" share/share.pro share/wikt/translations share/wikt/wikt.pro"
files+=" share/wikt/data/*.errata share/wikt/data/*.css share/wikt/data/*.js"
cp --verbose -r --parents $files $tmpdir

DIR=`pwd`
cd /tmp
tar -cvzf "wikt-$version.tar.gz" "wikt-$version"
mv "wikt-$version.tar.gz" "$DIR/"
rm -r $tmpdir
