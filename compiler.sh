#MAC OSX
g++ -std=c++11 -pedantic -o bin/exe src/main.cpp src/arbitro.cpp src/buffer.cpp src/roteador.cpp src/roteamento.cpp src/system.cpp  -I include/ -I/Users/adelinofernandes/Documents/systemc-2.3.1/include -L/Users/adelinofernandes/Documents/systemc-2.3.1/lib-macosx64 -lsystemc -D ODD_EVEN -D RANDOMICA

# LINUX
#g++ -std=c++11 -I. -I$SYSTEMC_HOME/include -L. -L$SYSTEMC_HOME/lib-linux64 -Wl,-rpath=$SYSTEMC_HOME/lib-linux64 -o bin/exeOddE src/main.cpp src/arbitro.cpp src/buffer.cpp src/roteador.cpp src/roteamento.cpp src/system.cpp  -I include/ -lsystemc -lm -D NEGATIVE_FIRST -D ESTATICA
