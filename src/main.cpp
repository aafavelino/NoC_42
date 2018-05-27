//
// Created by Adelino on 30/11/17.
//
#include <iostream>
#include <fstream>
#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "../constantes/constantes.h"
#include "system.h"

#include <math.h>

using namespace std;

int sc_main (int argc, char* argv[]) {

	sc_clock clock("clock", 1, SC_NS, 1, 1, SC_NS);
	REDE *simulation = new REDE("rede");
	simulation->Clk(clock);
	int **padrao_tfg;
	int size_pct = 0;

  int aux_latencia;
  std::vector<int> media_Latencias;
  int latencia_media_simulacao=0;
  int menor_latencia = 0;
  int maior_latencia = 0;
	// Leitura do Arquivo de tráfego
	FILE *traffic;
	traffic = fopen("traffic.txt","r");
	
	fscanf(traffic,"tg %i",&size_pct);


	padrao_tfg = (int**)malloc(size_pct * sizeof(int*));

  	for (int i = 0; i < size_pct; i++) 
       padrao_tfg[i] = (int*) malloc(8 * sizeof(int));

    for (int i = 0; i < size_pct; ++i)
    	fscanf(traffic,"%i %i %i %i %i %i %i %i", &padrao_tfg[i][0], &padrao_tfg[i][1], &padrao_tfg[i][2], &padrao_tfg[i][3], &padrao_tfg[i][4], &padrao_tfg[i][5], &padrao_tfg[i][6], &padrao_tfg[i][7]);
    // Fim da leitura do arquivo de tráfego
    fclose(traffic);

  	for (int i = 0; i < size_pct; ++i)
  		simulation->pacotes_tg.push_back(Pacote(padrao_tfg[i][0],padrao_tfg[i][1], padrao_tfg[i][2], padrao_tfg[i][3],  padrao_tfg[i][4],  padrao_tfg[i][5],  padrao_tfg[i][6], padrao_tfg[i][7]));

    simulation->latencias.resize(size_pct);

  	
	sc_start();	// Run the simulation till sc_stop is encountered

  // cout << "sc_stop is encountered" << endl;

  maior_latencia = simulation->latencias[0][0];
  menor_latencia = simulation->latencias[0][0];

  // cout << "size_pct "<<size_pct << endl;
  ofstream latencias_pc ("latencias.txt");
  for (int j = 0; j < size_pct; ++j)
  {
    for (int i = 0; i < padrao_tfg[j][6]; ++i)
    {
      latencias_pc << "Latencia posição:["<<j<<"]-> Pacote:[" << i << "]: " << simulation->latencias[j][i] << endl;
      if (menor_latencia > simulation->latencias[j][i])
      {
        menor_latencia = simulation->latencias[j][i];
      }
      if (maior_latencia < simulation->latencias[j][i])
      {
        maior_latencia = simulation->latencias[j][i];
      }      
    }
    latencias_pc << endl;
  }


  for (int j = 0; j < size_pct; ++j)
  {
    aux_latencia = 0;
    for (int i = 0; i < padrao_tfg[j][6]; ++i)
    {
      aux_latencia += simulation->latencias[j][i];
    }
    media_Latencias.push_back(aux_latencia/padrao_tfg[j][6]);
  }

  for (int j = 0; j < size_pct; ++j)
  {
      latencias_pc << "Latencia média do pacote["<<j<<"]: " << media_Latencias[j] << endl;
  }

  for (int j = 0; j < size_pct; ++j)
  {
      latencia_media_simulacao += media_Latencias[j];
  }

  ofstream vazoes ("vazoes.txt");

  vazoes <<"Vazões da simulação: " << endl; 


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

  latencias_pc << "\n\nMenor Latência: "<< menor_latencia << endl;
  latencias_pc << "Maior Latência: "<< maior_latencia << endl;
  // if (size_pct > 1)
  // {
  //   cout << "Latência Média da simulação: "<< latencia_media_simulacao/(size_pct-1) << endl;
  // } else {
  latencias_pc << "Latência Média da simulação: "<< latencia_media_simulacao/(size_pct) << endl;
  // }
  cout << endl;
  double variancia = 0.0;
  ofstream desvio ("desvio_padrao.txt");
  for (int j = 0; j < size_pct; ++j)
  {
    for (int k = 0; k < padrao_tfg[j][6]; ++k)
    {
      // cout << simulation->latencias[j][k]<<" "<<media_Latencias[j]<< endl;
      variancia+= ((simulation->latencias[j][k]-media_Latencias[j])*(simulation->latencias[j][k]-media_Latencias[j]));
    }
    desvio <<"Variância do pacote["<<j<<"]: " <<(variancia / padrao_tfg[j][6])<<endl;
    desvio <<"Desvio padrão do pacote["<<j<<"]:" <<sqrt((variancia / padrao_tfg[j][6])) << endl<<endl;
    variancia = 0.0;
  }





  	return 0;
}