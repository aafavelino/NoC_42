
g++ -std=c++11 -pedantic -o bin/exe src/main.cpp src/arbitro.cpp src/buffer.cpp src/controle_fluxo.cpp src/pacote.cpp src/rede.cpp src/roteador.cpp src/roteamento.cpp  -I include/ -I/Users/adelinofernandes/Documents/systemc-2.3.1/include -L/Users/adelinofernandes/Documents/systemc-2.3.1/lib-macosx64 -lsystemc

#echo "Compilando em C++ puro..."

#g++ -std=c++11 -pedantic -I include/ src/main.cpp src/arbitro.cpp src/buffer.cpp src/controle_fluxo.cpp src/fila.cpp src/flit.cpp src/pacote.cpp src/rede.cpp src/roteador.cpp  -o bin/exe 

