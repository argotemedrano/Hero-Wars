@echo off

mkdir ..\build
push build
cl -Zi ..\code\main.cpp
popd 