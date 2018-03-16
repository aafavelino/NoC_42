//
// Created by Adelino on 30/11/17.
//
#include <iostream>
#include <fstream>
#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {

	sc_clock clock("clock", 1, SC_NS, 1, 1, SC_NS);
	REDE *simulation = new REDE("rede");
	simulation->Clk(clock);
	int **padrao_tfg;
	int size_pct = 0;
	// Leitura do Arquivo de tráfego
	FILE *traffic;
	traffic = fopen("traffic.txt","r");
	
	fscanf(traffic,"tg %i",&size_pct);


	padrao_tfg = (int**)malloc(size_pct * sizeof(int*));

  	for (int i = 0; i < size_pct; i++) 
       padrao_tfg[i] = (int*) malloc(7 * sizeof(int));

    for (int i = 0; i < size_pct; ++i)
    	fscanf(traffic,"%i %i %i %i %i %i %i", &padrao_tfg[i][0], &padrao_tfg[i][1], &padrao_tfg[i][2], &padrao_tfg[i][3], &padrao_tfg[i][4], &padrao_tfg[i][5], &padrao_tfg[i][6]);
    // Fim da leitura do arquivo de tráfego
    fclose(traffic);

  	for (int i = 0; i < size_pct; ++i)
  		simulation->pacotes_tg.push_back(Pacote(padrao_tfg[i][0],padrao_tfg[i][1], padrao_tfg[i][2], padrao_tfg[i][3],  padrao_tfg[i][4],  padrao_tfg[i][5],  padrao_tfg[i][6]));

  	
  	// cout << simulation->pacotes_tg[0].qtd_flits.size() << endl;
  	// simulation->injetar();
  	
	sc_start();	// Run the simulation till sc_stop is encountered



  cout << "sc_stop is encountered" << endl;

  	return 0;
}