#!/bin/bash

rm -f *.deb
make package
sudo dpkg -r liblog++
sudo dpkg -i liblog++*.deb
