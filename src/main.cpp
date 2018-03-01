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

	sc_clock clock("clock", 10, SC_NS, 1, 10, SC_NS);
	REDE *teste = new REDE("rede");
	teste->Clk(clock);
	int **padrao_tfg;
	int size = 0;
	// Leitura do Arquivo de tráfego
	FILE *traffic;
	traffic = fopen("traffic.txt","r");
	
	fscanf(traffic,"tg %i",&size);


	padrao_tfg = (int**)malloc(size * sizeof(int*));

  	for (int i = 0; i < size; i++) 
       padrao_tfg[i] = (int*) malloc(7 * sizeof(int));


    for (int i = 0; i < size; ++i)
    	fscanf(traffic,"%i %i %i %i %i %i %i", &padrao_tfg[i][0], &padrao_tfg[i][1], &padrao_tfg[i][2], &padrao_tfg[i][3], &padrao_tfg[i][4], &padrao_tfg[i][5], &padrao_tfg[i][6]);
   
    fclose(traffic);


  	for (int i = 0; i < size; ++i)
  	{
  		teste->injeta_flits(padrao_tfg[i][0],padrao_tfg[i][1], padrao_tfg[i][2], padrao_tfg[i][3]);
  	}

  	for (int i = 0; i < size; ++i)
  	{
  		for (int j = 0; j < 7; ++j)
  		{
  			cout << padrao_tfg[i][j];
  		}
  		cout << endl;
  	}

	sc_start();	// Run the simulation till sc_stop is encountered

  	return 0;
}