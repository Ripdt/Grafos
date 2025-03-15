@echo off

rem Compila o projeto
cmake -S . -B build
cmake --build build

rem Roda os testes
cd build
ctest -C Debug --output-on-failure
cd ..