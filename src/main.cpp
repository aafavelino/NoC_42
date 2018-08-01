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
#include <queue>
#include <ctime>        

using namespace std;

const std::string currentDateTime() 
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}



int myrandom (int i) 
{ 
	return std::rand()%i;
}


int sc_main (int argc, char* argv[]) {


	std::srand ( unsigned ( std::time(0) ) );

	sc_clock clock("clock", 1, SC_NS, 1, 1, SC_NS);
	Noc *simulation = new Noc("NoC");
	simulation->Clk(clock);
	int **padrao_tfg;
	int size_pct = 0;

	// Leitura do Arquivo de tráfego
	FILE *traffic;
	traffic = fopen("traffic.txt","r");
	
	fscanf(traffic,"tg %i",&size_pct);

	simulation->stop = size_pct;


	padrao_tfg = (int**)malloc(size_pct * sizeof(int*));

  	for (int i = 0; i < size_pct; i++) 
       padrao_tfg[i] = (int*) malloc(8 * sizeof(int));


    for (int i = 0; i < size_pct; ++i){

    	fscanf(traffic,"%i %i %i %i %i %i %i %i", &padrao_tfg[i][0], &padrao_tfg[i][1], &padrao_tfg[i][2], &padrao_tfg[i][3], &padrao_tfg[i][4], &padrao_tfg[i][5], &padrao_tfg[i][6], &padrao_tfg[i][7]);
   	
    }
    // Fim da leitura do arquivo de tráfego
    fclose(traffic);

    std::queue<bool> fila_aux;


    int x_ant = padrao_tfg[0][0];
    int y_ant = padrao_tfg[0][1];
    int contador = 0;
    int posicao = 0;
    std::deque<Pacote> auxiliar;
    auxiliar.push_back(Pacote(padrao_tfg[0][0],padrao_tfg[0][1], padrao_tfg[0][2], padrao_tfg[0][3],  padrao_tfg[0][4],  padrao_tfg[0][5],  padrao_tfg[0][6],  padrao_tfg[0][7], 0));
    simulation->pacotes_tgf.push_back(auxiliar);
    simulation->pacotes_verify.push_back(false);
    simulation->pacotes_verify_pacote.push_back(fila_aux);

    auxiliar.pop_front();

    simulation->pacotes_tg.push_back(Pacote(padrao_tfg[0][0],padrao_tfg[0][1], padrao_tfg[0][2], padrao_tfg[0][3],  padrao_tfg[0][4],  padrao_tfg[0][5],  padrao_tfg[0][6],  padrao_tfg[0][7], 0));
  	for (int i = 1; i < size_pct; ++i){

  		if (x_ant != padrao_tfg[i][0] or y_ant != padrao_tfg[i][1])
  		{
  			contador++;
  			x_ant = padrao_tfg[i][0];
    		y_ant = padrao_tfg[i][1];
    		// cout << contador << "x "<< padrao_tfg[i][0] << " y "<< padrao_tfg[i][1] << endl;
    		auxiliar.push_back(Pacote(padrao_tfg[i][0],padrao_tfg[i][1], padrao_tfg[i][2], padrao_tfg[i][3],  padrao_tfg[i][4],  padrao_tfg[i][5],  padrao_tfg[i][6],  padrao_tfg[i][7], contador));
    		simulation->pacotes_tgf.push_back(auxiliar);
    		simulation->pacotes_verify.push_back(false);
    		simulation->pacotes_verify_pacote.push_back(fila_aux);


    		auxiliar.pop_front();
    		posicao++;
  		} else {
  			contador++;
  			simulation->pacotes_tgf[posicao].push_back(Pacote(padrao_tfg[i][0],padrao_tfg[i][1], padrao_tfg[i][2], padrao_tfg[i][3],  padrao_tfg[i][4],  padrao_tfg[i][5],  padrao_tfg[i][6],  padrao_tfg[i][7], contador));
		    simulation->pacotes_verify.push_back(false);
    		simulation->pacotes_verify_pacote.push_back(fila_aux);

  		}

  		simulation->pacotes_tg.push_back(Pacote(padrao_tfg[i][0],padrao_tfg[i][1], padrao_tfg[i][2], padrao_tfg[i][3],  padrao_tfg[i][4],  padrao_tfg[i][5],  padrao_tfg[i][6],  padrao_tfg[i][7], contador));
  	}

  	// cout << simulation->pacotes_tgf[0].size() << endl;


    simulation->latencias.resize(size_pct);

    simulation->flit_stop =  padrao_tfg[0][4];

    if (atoi(argv[1]) == 1)
    {
		for (int i = 0; i < simulation->pacotes_tgf.size(); ++i){
			
	 		std::random_shuffle ( simulation->pacotes_tgf[i].begin(), simulation->pacotes_tgf[i].end() );
	  		std::random_shuffle ( simulation->pacotes_tgf[i].begin(), simulation->pacotes_tgf[i].end(), myrandom);

		}
    }

    




		// for (int i = 0; i < simulation->pacotes_tgf.size(); ++i){
		// 	for (int j = 0; j < simulation->pacotes_tgf[i].size(); ++j)
		// 	{
		// 		cout << i << " "<<j <<" >>> " << simulation->pacotes_tgf[i][j].id <<endl;
		// 	}
	 		
		// }
  	
	sc_start();	// Run the simulation till sc_stop is encountered

	std::string dir = currentDateTime();


	char ch[100]="";
	strcat(ch,"mkdir ");
	strcat(ch,dir.c_str());
	system(ch); 

	// cout << dir << endl;
	ofstream latencias (dir+"/latencias.txt");



	

	latencias << "Latências de Pacote:" << endl << endl;

	// cout << "um "<< size_pct<<  endl;
	double media = 0;
	double media_interna = 0;
	for (int i = 0; i < size_pct; ++i)
	{
		for (int j = 0; j < padrao_tfg[i][4]; ++j)
		{
			// cout << "Fluxo "<<i << " Pacote  "<< j << " Final " << simulation->pacotes_tg[i].ciclo_final[j] <<" criacao "<< simulation->pacotes_tg[i].ciclo_criacao[j] << endl;
			media_interna +=  simulation->pacotes_tg[i].ciclo_final[j] - simulation->pacotes_tg[i].ciclo_criacao[j];
			latencias << "Latência pacote " <<j<< " no fluxo["<< i<<"] "<< simulation->pacotes_tg[i].ciclo_final[j] - simulation->pacotes_tg[i].ciclo_criacao[j] << endl;
		}

		media += (media_interna/padrao_tfg[i][4]);
		media_interna = 0;
	}

	// cout << "dois "<< endl;
	// latencias << endl << "Lat. Média: "<< media/(size_pct) << endl;
	latencias <<"Lat. Média: "<< media/(size_pct) << endl;
	cout << media/(size_pct) << endl;



	ofstream vazoes (dir+"/vazoes.txt");


	char conf[100]="";
	strcat(conf,"cp configuracoes.txt traffic.txt ");
	strcat(conf,dir.c_str());
	system(conf); 	

	


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

	// latencias << endl << endl;
	// double med_lat = 0;

	// double med_abs = 0;

	// for (int i = 0; i < size_pct; ++i)
	// {
	// 	for (int j = 0; j < simulation->latencias[i].size(); ++j)
	// 	{
	// 		// cout << "Latência absoluta pacote["<< i <<"] " << simulation->latencias[i][j] << endl;
	// 		med_lat += simulation->latencias[i][j];
	// 	}

	// 	latencias << "Latência absoluta pacote["<< i <<"] "<<  med_lat/simulation->latencias[i].size() << endl;


	// 	med_abs += (med_lat/simulation->latencias[i].size());
	// 	med_lat = 0;
	// }

	// 	latencias << endl << "Média... :"<< med_abs/size_pct;

  	return 0;
}