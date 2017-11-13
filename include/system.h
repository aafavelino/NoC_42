#ifndef _SYSTEM_H_
#define _SYSTEM_H_ 

#include <systemc.h>
#include <vector>
#include "roteador.h"



#define LARGURA_REDE 5
#define ALTURA_REDE 5

#define NORTE 0
#define LESTE 1
#define SUL 2
#define OESTE 3
#define LOCAL 4

using namespace std;

SC_MODULE (SYSTEM)
{

	// Criando uma Rede Altura x Largura
	roteador *rede[ALTURA_REDE][LARGURA_REDE];


	//Aterramentos
	sc_signal<int> ground_connection_val[100];
	sc_signal<int> ground_connection_ack[100];

	void comunicacao ();
	void injeta_flits();

	SC_CTOR(SYSTEM) 
	{ 

		const char* roteadores_nomes[] = {"roteador_01", "roteador_02", "roteador_03", "roteador_04", "roteador_05", "roteador_06", "roteador_07", "roteador_08", "roteador_09", "roteador_10",
						              	  "roteador_11", "roteador_12", "roteador_13", "roteador_14", "roteador_15", "roteador_16", "roteador_17", "roteador_18", "roteador_19", "roteador_20",
						                  "roteador_21", "roteador_22", "roteador_23", "roteador_24", "roteador_25", "roteador_26", "roteador_27", "roteador_28", "roteador_29", "roteador_30",
						                  "roteador_31", "roteador_32", "roteador_33", "roteador_34", "roteador_35", "roteador_36", "roteador_37", "roteador_38", "roteador_39", "roteador_40",
						                  "roteador_41", "roteador_42", "roteador_43", "roteador_44", "roteador_45", "roteador_46", "roteador_47", "roteador_48", "roteador_49", "roteador_50"};
	 
		int rt_cont = 0;
	  	for (int i = 0; i < ALTURA_REDE; ++i)
	  	{
	  		for (int j = 0; j < LARGURA_REDE; ++j)
	  		{
	  			rede[i][j] = new roteador(roteadores_nomes[rt_cont]);
	  			rt_cont++;
	  		}
	  	}


		int cont = 0;
		for (int i = 0; i < ALTURA_REDE; ++i)
		{
			for (int j = 0; j < LARGURA_REDE; ++j)
			{
				if (i == 0)
				{	
					
					// cout << "rede[" << i << "][" << j << "]->cf_norte->in_val(ground_connection_val[" << cont<< "])"  << endl;
					// cout << "rede[" << i << "][" << j << "]->cf_norte->in_ack(ground_connection_val[" << cont<< "])"  << endl;
					rede[i][j]->cf_norte->in_val(ground_connection_val[cont]);
					rede[i][j]->cf_norte->in_ack(ground_connection_ack[cont]);
					cont++;
				}
				if (j == 0)
				{	
					// cout << "rede[" << i << "][" << j << "]->cf_oeste->in_val(ground_connection_val[" << cont<< "])"  << endl;
					// cout << "rede[" << i << "][" << j << "]->cf_oeste->in_ack(ground_connection_val[" << cont<< "])"  << endl;				
					rede[i][j]->cf_oeste->in_val(ground_connection_val[cont]);
					rede[i][j]->cf_oeste->in_ack(ground_connection_ack[cont]);
					cont++;
				}
				if (i == ALTURA_REDE-1)
				{	
					// cout << "rede[" << i << "][" << j << "]->cf_sul->in_val(ground_connection_val[" << cont<< "])"  << endl;
					// cout << "rede[" << i << "][" << j << "]->cf_sul->in_ack(ground_connection_val[" << cont<< "])"  << endl;				
					rede[i][j]->cf_sul->in_val(ground_connection_val[cont]);
					rede[i][j]->cf_sul->in_ack(ground_connection_ack[cont]);
					cont++;
				}
				if (j == LARGURA_REDE-1)
				{	
					// cout << "rede[" << i << "][" << j << "]->cf_leste->in_val(ground_connection_val[" << cont<< "])"  << endl;
					// cout << "rede[" << i << "][" << j << "]->cf_leste->in_ack(ground_connection_val[" << cont<< "])"  << endl;				
					rede[i][j]->cf_leste->in_val(ground_connection_val[cont]);
					rede[i][j]->cf_leste->in_ack(ground_connection_ack[cont]);
					cont++;
				}

			}
		}
		// Ligando sinais entre os roteadores	
		for (int i = 0; i < ALTURA_REDE; ++i)
		{
			for (int j = 0; j < LARGURA_REDE; ++j)
			{
				if (j != LARGURA_REDE-1)
				{
					rede[i][j]->cf_leste->in_val(rede[i][j+1]->val_cf_oeste_to_leste_wire);
					rede[i][j]->cf_leste->in_ack(rede[i][j+1]->ack_cf_oeste_to_leste_wire);
				}
				if (j != 0)
				{
					rede[i][j]->cf_oeste->in_val(rede[i][j-1]->val_cf_leste_to_oeste_wire);
					rede[i][j]->cf_oeste->in_ack(rede[i][j-1]->ack_cf_leste_to_oeste_wire);
					
				}
				if (i != ALTURA_REDE-1)
				{
					rede[i][j]->cf_sul->in_val(rede[i+1][j]->val_cf_norte_to_sul_wire);
					rede[i][j]->cf_sul->in_ack(rede[i+1][j]->ack_cf_norte_to_sul_wire);
				}
				if (i != 0)
				{
					rede[i][j]->cf_norte->in_val(rede[i-1][j]->val_cf_sul_to_norte_wire);
					rede[i][j]->cf_norte->in_ack(rede[i-1][j]->ack_cf_sul_to_norte_wire);
				}


			}
		}

		//Setando as Cordenadas dos roteadores Ex.: roteador1 se encontra em rede[0][0]
		for (int x = 0; x < ALTURA_REDE; ++x){
			for (int y = 0; y < LARGURA_REDE; ++y) {	
				rede[x][y]->roteamento_norte.cordenada.x = x;
				rede[x][y]->roteamento_norte.cordenada.y = y;
				rede[x][y]->roteamento_sul.cordenada.x = x;
				rede[x][y]->roteamento_sul.cordenada.y = y;
				rede[x][y]->roteamento_leste.cordenada.x = x;
				rede[x][y]->roteamento_leste.cordenada.y = y;
				rede[x][y]->roteamento_oeste.cordenada.x = x;
				rede[x][y]->roteamento_oeste.cordenada.y = y;
				rede[x][y]->roteamento_local.cordenada.x = x;
				rede[x][y]->roteamento_local.cordenada.y = y;			
			}
		}
		SC_METHOD(comunicacao);
		for (int x = 0; x < ALTURA_REDE; ++x){
			for (int y = 0; y < LARGURA_REDE; ++y) {
				sensitive << rede[x][y]->buffer_norte->in_bf_controle_fluxo;
				sensitive << rede[x][y]->buffer_sul->in_bf_controle_fluxo;
				sensitive << rede[x][y]->buffer_leste->in_bf_controle_fluxo;
				sensitive << rede[x][y]->buffer_oeste->in_bf_controle_fluxo;
			}
		}
			
			
	}

};

#endif