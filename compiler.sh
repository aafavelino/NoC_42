#!/bin/bash
g++ -std=c++11 -pedantic -o bin/exe src/main.cpp src/arbitro.cpp src/buffer.cpp src/roteador.cpp src/roteamento.cpp src/system.cpp  -I include/ -I/Users/adelinofernandes/Documents/systemc-2.3.1/include -L/Users/adelinofernandes/Documents/systemc-2.3.1/lib-macosx64 -lsystemc

