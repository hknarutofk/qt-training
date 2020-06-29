#!/bin/bash


# 本脚本当前仅允许在Kylin Desktop系统下运行



sh qmake.sh
version=`./build/qt-training --version`
cp build/qt-training deb/opt/hknarutofk/qt-training/ -f
cp icon.png deb/opt/hknarutofk/qt-training/icon.png -f

dpkg -b deb gwinstaller-"$version"_x86_64.deb

