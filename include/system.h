#ifndef _SYSTEM_H_
#define _SYSTEM_H_ 

#include <systemc.h>
#include <vector>
#include "roteador.h"
#include <iostream>
#include <fstream>
#include "../constantes/constantes.h"

using namespace std;

SC_MODULE (REDE)
{
	bool ver_leste[ALTURA_REDE][LARGURA_REDE];
	bool ver_oeste[ALTURA_REDE][LARGURA_REDE];
	bool ver_sul[ALTURA_REDE][LARGURA_REDE];
	bool ver_norte[ALTURA_REDE][LARGURA_REDE];

	bool aux_rot_norte[2];
	bool aux_rot_sul[2];
	bool aux_rot_leste[2];
	bool aux_rot_oeste[2];

	// Criando uma Rede Altura x Largura
	roteador *rede[ALTURA_REDE][LARGURA_REDE];


	//Aterramentos
	sc_signal<int> ground_connection_val[100];
	sc_signal<int> ground_connection_ack[100];

	void comunicacao_externa();
	void injeta_flits(int, int, int, int);
	void roteamentos_macros_externa(int,int,int);
	void roteamentos_macros_interna(int,int,int);

	SC_CTOR(REDE) 
	{ 
		
		const char* roteadores_nomes[]={	"roteador_01" , "roteador_02" , "roteador_03" , "roteador_04" , "roteador_05" , "roteador_06" , "roteador_07" , "roteador_08" , "roteador_09" , "roteador_10" ,
		"roteador_11" , "roteador_12" , "roteador_13" , "roteador_14" , "roteador_15" , "roteador_16" , "roteador_17" , "roteador_18" , "roteador_19" , "roteador_20" ,
		"roteador_21" , "roteador_22" , "roteador_23" , "roteador_24" , "roteador_25" , "roteador_26" , "roteador_27" , "roteador_28" , "roteador_29" , "roteador_30" ,
		"roteador_31" , "roteador_32" , "roteador_33" , "roteador_34" , "roteador_35" , "roteador_36" , "roteador_37" , "roteador_38" , "roteador_39" , "roteador_40" ,
		"roteador_41" , "roteador_42" , "roteador_43" , "roteador_44" , "roteador_45" , "roteador_46" , "roteador_47" , "roteador_48" , "roteador_49" , "roteador_50" ,
		"roteador_51" , "roteador_52" , "roteador_53" , "roteador_54" , "roteador_55" , "roteador_56" , "roteador_57" , "roteador_58" , "roteador_59" , "roteador_60" ,
		"roteador_61" , "roteador_62" , "roteador_63" , "roteador_64" , "roteador_65" , "roteador_66" , "roteador_67" , "roteador_68" , "roteador_69" , "roteador_70" ,
		"roteador_71" , "roteador_72" , "roteador_73" , "roteador_74" , "roteador_75" , "roteador_76" , "roteador_77" , "roteador_78" , "roteador_79" , "roteador_80" ,
		"roteador_81" , "roteador_82" , "roteador_83" , "roteador_84" , "roteador_85" , "roteador_86" , "roteador_87" , "roteador_88" , "roteador_89" , "roteador_90" ,
		"roteador_91" , "roteador_92" , "roteador_93" , "roteador_94" , "roteador_95" , "roteador_96" , "roteador_97" , "roteador_98" , "roteador_99" , "roteador_100",
		"roteador_101", "roteador_102", "roteador_103", "roteador_104", "roteador_105", "roteador_106", "roteador_107", "roteador_108", "roteador_109", "roteador_110",
		"roteador_111", "roteador_112", "roteador_113", "roteador_114", "roteador_115", "roteador_116", "roteador_117", "roteador_118", "roteador_119", "roteador_120",
		"roteador_121", "roteador_122", "roteador_123", "roteador_124", "roteador_125", "roteador_126", "roteador_127", "roteador_128", "roteador_129", "roteador_130",
		"roteador_131", "roteador_132", "roteador_133", "roteador_134", "roteador_135", "roteador_136", "roteador_137", "roteador_138", "roteador_139", "roteador_140",
		"roteador_141", "roteador_142", "roteador_143", "roteador_144", "roteador_145", "roteador_146", "roteador_147", "roteador_148", "roteador_149", "roteador_150",
		"roteador_151", "roteador_152", "roteador_153", "roteador_154", "roteador_155", "roteador_156", "roteador_157", "roteador_158", "roteador_159", "roteador_160",
		"roteador_161", "roteador_162", "roteador_163", "roteador_164", "roteador_165", "roteador_166", "roteador_167", "roteador_168", "roteador_169", "roteador_170"
	};
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
	for (int x = 0; x < ALTURA_REDE; ++x)
	{
		for (int y = 0; y < LARGURA_REDE; ++y)
		{
			if (x == 0)
			{	
				
					//printf("rede[ %d ][ %d ]->cf_norte->in_val(ground_connection_val[%d]\n",i,j,cont);
					//printf("rede[ %d ][ %d ]->cf_norte->in_ack(ground_connection_val[%d]\n",i,j,cont);
				rede[x][y]->cf_norte->in_val(ground_connection_val[cont]);
				rede[x][y]->cf_norte->in_ack(ground_connection_ack[cont]);
				cont++;
			}
			if (y == 0)
			{	
					//printf("rede[ %d ][ %d ]->cf_oeste->in_val(ground_connection_val[%d]\n",i,j,cont);
					//printf("rede[ %d ][ %d ]->cf_oeste->in_ack(ground_connection_val[%d]\n",i,j,cont);				
				rede[x][y]->cf_oeste->in_val(ground_connection_val[cont]);
				rede[x][y]->cf_oeste->in_ack(ground_connection_ack[cont]);
				cont++;
			}
			if (x == ALTURA_REDE-1)
			{	
					//printf("rede[ %d ][ %d ]->cf_sul->in_val(ground_connection_val[ %d)\n",i,j,cont);					
					//printf("rede[ %d ][ %d ]->cf_sul->in_ack(ground_connection_val[ %d)\n",i,j,cont);			
				rede[x][y]->cf_sul->in_val(ground_connection_val[cont]);
				rede[x][y]->cf_sul->in_ack(ground_connection_ack[cont]);
				cont++;
			}
			if (y == LARGURA_REDE-1)
			{	
					//printf("rede[ %d ][ %d ]->cf_leste->in_val(ground_connection_val[%d]\n",i,j,cont);
					//printf("rede[ %d ][ %d ]->cf_leste->in_ack(ground_connection_val[%d]\n",i,j,cont);				
				rede[x][y]->cf_leste->in_val(ground_connection_val[cont]);
				rede[x][y]->cf_leste->in_ack(ground_connection_ack[cont]);
				cont++;
			}

		}
	}

		// Ligando sinais entre os roteadores	
	for (int x = 0; x < ALTURA_REDE; ++x)
	{
		for (int y = 0; y < LARGURA_REDE; ++y)
		{
			if (y != LARGURA_REDE-1)
			{
				rede[x][y]->cf_leste->in_val(rede[x][y+1]->val_cf_oeste_to_leste_wire);
				rede[x][y]->cf_leste->in_ack(rede[x][y+1]->ack_cf_oeste_to_leste_wire);
			}
			if (y != 0)
			{
				rede[x][y]->cf_oeste->in_val(rede[x][y-1]->val_cf_leste_to_oeste_wire);
				rede[x][y]->cf_oeste->in_ack(rede[x][y-1]->ack_cf_leste_to_oeste_wire);
				
			}
			if (x != ALTURA_REDE-1)
			{
				rede[x][y]->cf_sul->in_val(rede[x+1][y]->val_cf_norte_to_sul_wire);
				rede[x][y]->cf_sul->in_ack(rede[x+1][y]->ack_cf_norte_to_sul_wire);
			}
			if (x != 0)
			{
				rede[x][y]->cf_norte->in_val(rede[x-1][y]->val_cf_sul_to_norte_wire);
				rede[x][y]->cf_norte->in_ack(rede[x-1][y]->ack_cf_sul_to_norte_wire);
			}


		}
	}

	for (int x = 0; x < ALTURA_REDE; ++x){
		for (int y = 0; y < LARGURA_REDE; ++y) {	
			ver_leste[x][y] = false;
			ver_oeste[x][y] = false;
			ver_sul[x][y] = false;
			ver_norte[x][y] = false;
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

	SC_METHOD(comunicacao_externa);
	for (int x = 0; x < ALTURA_REDE; ++x){
		for (int y = 0; y < LARGURA_REDE; ++y) {
			sensitive << rede[x][y]->cf_saida_norte->out_ack;
			sensitive << rede[x][y]->cf_saida_sul->out_ack;
			sensitive << rede[x][y]->cf_saida_leste->out_ack;
			sensitive << rede[x][y]->cf_saida_oeste->out_ack;
		}
	}	
}
};

#endif