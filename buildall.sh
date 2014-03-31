#!/bin/bash

build()
{
	mkdir $1
	cd $1
	pwd
	qmake ../../$1/$1.pro && make
	RET=$?
	cd ..
	return $RET
}

if [ -d "build" ]
then
	rm build -rf
fi

if [ -d "lib" ]
then
	rm lib -rf
fi

cp ../build/lib . -r

git submodule update --init

mkdir build
cd build

build optimalus && build reapers && build RebattreClient && build DrumLight && build Arkanoid
