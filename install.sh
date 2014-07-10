#!/bin/bash

#TODO take version inside version.h
version="2.0.0"

mkdir -p Build/package

find src -name "*.h" > Build/.includes
exec 3</tmp/.tests
while read -u3 file    
do
	echo "Add $file"    
	mkdir -p Build/package/include/$(dirname $file)
	cp $file Build/package/include/$(dirname $file)
done

mkdir -p Build/package/lib
cp Build/lib/liblog++.so Build/package/lib



rm -f *.deb
make package
sudo dpkg -r liblog++
sudo dpkg -i liblog++*.deb


