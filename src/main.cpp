//
// Created by Adelino on 30/11/17.
//
#include <iostream>
#include <fstream>
#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "../constantes/constantes.h"
#include "noc.h"
#include <math.h>

using namespace std;

int sc_main (int argc, char* argv[]) {

	sc_clock clock("clock", 1, SC_NS, 1, 1, SC_NS);
	Noc *simulation = new Noc("NoC");
	simulation->Clk(clock);
	int **padrao_tfg;
	int size_pct = 0;

	// Leitura do Arquivo de tráfego
	FILE *traffic;
	traffic = fopen("traffic.txt","r");
	
	fscanf(traffic,"tg %i",&size_pct);


	padrao_tfg = (int**)malloc(size_pct * sizeof(int*));

  	for (int i = 0; i < size_pct; i++) 
       padrao_tfg[i] = (int*) malloc(8 * sizeof(int));

    for (int i = 0; i < size_pct; ++i)
    	fscanf(traffic,"%i %i %i %i %i %i %i", &padrao_tfg[i][0], &padrao_tfg[i][1], &padrao_tfg[i][2], &padrao_tfg[i][3], &padrao_tfg[i][4], &padrao_tfg[i][5], &padrao_tfg[i][6]);
    // Fim da leitura do arquivo de tráfego
    fclose(traffic);

  	for (int i = 0; i < size_pct; ++i)
  		simulation->pacotes_tg.push_back(Pacote(padrao_tfg[i][0],padrao_tfg[i][1], padrao_tfg[i][2], padrao_tfg[i][3],  padrao_tfg[i][4],  padrao_tfg[i][5],  padrao_tfg[i][6], i));

    simulation->latencias.resize(size_pct);

  	
	sc_start();	// Run the simulation till sc_stop is encountered
	 // std::queue<Flit> flit;
	 // std::vector<std::queue<Flit> > buffer_virtual;
	 // buffer_virtual.push_back(flit);
	 // buffer_virtual.push_back(flit);

	 // buffer_virtual[0].pop();
	 // buffer_virtual[0].pop();

	double media = 0;
	for (int i = 0; i < size_pct; ++i)
	{
		media += simulation->pacotes_tg[i].last_flit - simulation->pacotes_tg[i].first_flit;
		// cout << "Latência pacote["<< i<<"] "<< simulation->pacotes_tg[i].last_flit - simulation->pacotes_tg[i].first_flit << endl;
	}

	cout << endl << endl <<"Lat. Média: "<< media/size_pct << endl;
	 // cout << buffer_virtual[0].size() << endl;


	ofstream vazoes ("vazoes.txt");


	for (int i = 0; i < ALTURA_REDE; ++i)
	{
	    for (int j = 0; j < LARGURA_REDE; ++j)
	    {
	      if ((i-1)>=0)
	        vazoes << "["<<i<<"]["<<j<<"]->["<<i-1<<"]["<<j<<"]: " <<((double)simulation->throughput[i][j]->saida_norte/(double)simulation->clock) <<endl;
	      if ((i+1)<ALTURA_REDE)
	        vazoes << "["<<i<<"]["<<j<<"]->["<<i+1<<"]["<<j<<"]: " <<((double)simulation->throughput[i][j]->saida_sul/(double)simulation->clock) <<endl;
	      if ((j+1) < LARGURA_REDE)
	        vazoes << "["<<i<<"]["<<j<<"]->["<<i<<"]["<<j+1<<"]: " <<((double)simulation->throughput[i][j]->saida_leste/(double)simulation->clock) <<endl;
	      if ((j-1)>=0) 
	        vazoes << "["<<i<<"]["<<j<<"]->["<<i<<"]["<<j-1<<"]: " <<((double)simulation->throughput[i][j]->saida_oeste/(double)simulation->clock) <<endl;
	        vazoes << endl;
	    }

	}

  	return 0;
}