//
// Created by Adelino on 30/11/17.
//

#include "system.h"
int ciclos = 0;

void REDE::comunicacao_externa() 
{

	// Colocar aqui a entrada e verificações de ciclos de injeção em cada porta 
	// local 
	// Colocar pacotes em  um vetor de pacotes e verificar um por umm




	for (int y = 0; y < ALTURA_REDE; y++)
	{
		if (y==0)
		{
			ciclos++;
			if (ciclos == 100)
				sc_stop();
		}

		for (int x = 0; x < LARGURA_REDE; x++)
		{   



	if(rede[y][x]->buffer_local->size != 0) {
		rede[y][x]->roteamento_local.cordenada_destino.x =   rede[y][x]->buffer_local->flits.front().cordenadas_f.x;
		rede[y][x]->roteamento_local.cordenada_destino.y =   rede[y][x]->buffer_local->flits.front().cordenadas_f.y;
		
		//Roteando
		
		#ifdef NEGATIVE_FIRST
		rede[y][x]->roteamento_local.rotear_negative_first();
		#endif

		#ifdef XY
		rede[y][x]->roteamento_local.rotear_xy();
		#endif	
		
		#ifdef NORTH_LAST
		rede[y][x]->roteamento_local.rotear_north_last();
		#endif

		#ifdef WEST_FIRST	
		rede[y][x]->roteamento_local.rotear_west_first();
		#endif



		if (rede[y][x]->roteamento_local.portaDestino == NORTE)
		{
			
			rede[y][x]->arbitro_norte.addSolicitacao(NORTE);
			rede[y][x]->arbitro_norte.setPrioridade();
			rede[y][x]->roteamento_norte.cordenada_destino.x =   rede[y][x]->buffer_local->flits.front().cordenadas_f.x;
			rede[y][x]->roteamento_norte.cordenada_destino.y =   rede[y][x]->buffer_local->flits.front().cordenadas_f.y;
			rede[y][x]->buffer_norte->din =  rede[y][x]->buffer_local->flits.front();
			rede[y][x]->buffer_local->remove();
			rede[y][x]->buffer_norte->add();
			rede[y][x]->cf_saida_norte->out_val.write(1);
			// cout << "NORTE" << endl;
		} else if (rede[y][x]->roteamento_local.portaDestino == SUL)
		{
			
			rede[y][x]->arbitro_sul.addSolicitacao(SUL);
			rede[y][x]->arbitro_sul.setPrioridade();
			rede[y][x]->roteamento_sul.cordenada_destino.x =   rede[y][x]->buffer_local->flits.front().cordenadas_f.x;
			rede[y][x]->roteamento_sul.cordenada_destino.y =   rede[y][x]->buffer_local->flits.front().cordenadas_f.y;
			rede[y][x]->buffer_sul->din =  rede[y][x]->buffer_local->flits.front();
			rede[y][x]->buffer_local->remove();
			rede[y][x]->buffer_sul->add();
			rede[y][x]->cf_saida_sul->out_val.write(1);
			// cout << "SUL" << endl;
		} else if (rede[y][x]->roteamento_local.portaDestino == LESTE)
		{
			
			rede[y][x]->arbitro_leste.addSolicitacao(LESTE);
			rede[y][x]->arbitro_leste.setPrioridade();
			rede[y][x]->roteamento_leste.cordenada_destino.x =   rede[y][x]->buffer_local->flits.front().cordenadas_f.x;
			rede[y][x]->roteamento_leste.cordenada_destino.y =   rede[y][x]->buffer_local->flits.front().cordenadas_f.y;
			rede[y][x]->buffer_leste->din =  rede[y][x]->buffer_local->flits.front();
			rede[y][x]->buffer_local->remove();
			rede[y][x]->buffer_leste->add();
			rede[y][x]->cf_saida_leste->out_val.write(1);
			// cout << "LESTE" << endl;
		} else if (rede[y][x]->roteamento_local.portaDestino == OESTE)
		{	
			
			rede[y][x]->arbitro_oeste.addSolicitacao(OESTE);
			rede[y][x]->arbitro_oeste.setPrioridade();
			rede[y][x]->roteamento_oeste.cordenada_destino.x =   rede[y][x]->buffer_local->flits.front().cordenadas_f.x;
			rede[y][x]->roteamento_oeste.cordenada_destino.y =   rede[y][x]->buffer_local->flits.front().cordenadas_f.y;
			rede[y][x]->buffer_oeste->din =  rede[y][x]->buffer_local->flits.front();
			rede[y][x]->buffer_local->remove();
			rede[y][x]->buffer_oeste->add();
			rede[y][x]->cf_saida_oeste->out_val.write(1);
			// cout << "OESTE" << endl;
		} else {
			// cout << y <<  x << " "<<  x << y << endl;
			// printf("CHEGOU...\n");
			// rede[y][x]->buffer_local->din =	 rede[y][x]->buffer_local->flits.front();
			// rede[y][x]->buffer_local->remove();
			// rede[y][x]->buffer_local->add();

			// Esse caso será somente para não haver contenção de pacote... Ex: Se tem um camarada que ainda precisa ser enviado. mas existe outro que está
			// na frente e já está no seu destino final. Então esse camarada vai para o fim da fila e deixa o fluxo correr para a fila não ficar parada... 
			// É como se o filho ficasse guardando o lugar da mãe na fila da riachuelo/c&a, a mãe continua comprando, chega a vez de passar no caixa e a mãe não 
			// chega
		}
	}


			// cout << rede[0][0]->buffer_leste->size << endl;
			if (rede[y][x]->cf_leste->in_ack.read() == 1)
			{
				// printf("[%d][%d]--LESTE\n",y,x);
				rede[y][x]->buffer_leste->din = rede[y][x+1]->buffer_oeste->flits.front(); 
				rede[y][x]->buffer_leste->add();
				rede[y][x+1]->buffer_oeste->remove();
				if (rede[y][x+1]->buffer_oeste->size == 0)
				{
					rede[y][x+1]->cf_saida_oeste->out_val.write(0);
					rede[y][x]->cf_leste->in_ack = 0;
				}
				ver_leste[y][x] = true;
			}

			if (rede[y][x]->cf_oeste->in_ack.read() == 1)
			{
				// printf("[%d][%d]--OESTE\n",y,x);
				rede[y][x]->buffer_oeste->din = rede[y][x-1]->buffer_leste->flits.front();			 
				rede[y][x]->buffer_oeste->add();
				rede[y][x-1]->buffer_leste->remove();
				if (rede[y][x-1]->buffer_leste->size == 0) {
					rede[y][x-1]->cf_saida_leste->out_val.write(0);
					rede[y][x]->cf_oeste->in_ack = 0;
				}
				ver_oeste[y][x] = true;
			}			

			if (rede[y][x]->cf_sul->in_ack.read() == 1) 
			{
				// printf("[%d][%d]--SUL\n",y,x);
				rede[y][x]->buffer_sul->din = rede[y+1][x]->buffer_norte->flits.front();
				rede[y][x]->buffer_sul->add();
				rede[y+1][x]->buffer_norte->remove();
				if (rede[y+1][x]->buffer_norte->size == 0)
				{
					rede[y+1][x]->cf_saida_norte->out_val.write(0);
					rede[y][x]->cf_sul->in_ack = 0;
				}

				ver_sul[y][x] = true;
			}

			if (rede[y][x]->cf_norte->in_ack.read() == 1)
			{
				// printf("[%d][%d]--NORTE\n",y,x);
				rede[y][x]->buffer_norte->din = rede[y-1][x]->buffer_sul->flits.front();
				rede[y][x]->buffer_norte->add();
				rede[y-1][x]->buffer_sul->remove();
				if (rede[y-1][x]->buffer_sul->size == 0) {
					rede[y-1][x]->cf_saida_sul->out_val.write(0);
					rede[y][x]->cf_norte->in_ack = 0;
				}
				ver_norte[y][x] = true;
			}					


			if (ver_norte[y][x])
			{
				rede[y][x]->roteamento_norte.cordenada_destino.x = rede[y][x]->buffer_norte->flits.front().cordenadas_f.x;
				rede[y][x]->roteamento_norte.cordenada_destino.y = rede[y][x]->buffer_norte->flits.front().cordenadas_f.y;								
				
				#ifdef NEGATIVE_FIRST
				rede[y][x]->roteamento_norte.rotear_negative_first();
				#endif

				#ifdef XY
				rede[y][x]->roteamento_norte.rotear_xy();
				#endif	

				#ifdef NORTH_LAST
				rede[y][x]->roteamento_norte.rotear_north_last();
				#endif

				#ifdef WEST_FIRST	
				rede[y][x]->roteamento_norte.rotear_west_first();
				#endif	

				if (rede[y][x]->roteamento_norte.portaDestino == LESTE)
				{
					rede[y][x]->arbitro_norte.addSolicitacao(LESTE);
					rede[y][x]->arbitro_norte.setPrioridade();
				} else if (rede[y][x]->roteamento_norte.portaDestino == OESTE)
				{
					rede[y][x]->arbitro_norte.addSolicitacao(OESTE);
					rede[y][x]->arbitro_norte.setPrioridade();
				} else if (rede[y][x]->roteamento_norte.portaDestino == NORTE)
				{
					rede[y][x]->arbitro_norte.addSolicitacao(NORTE);
					rede[y][x]->arbitro_norte.setPrioridade();
				} else if (rede[y][x]->roteamento_norte.portaDestino == SUL)
				{
					rede[y][x]->arbitro_norte.addSolicitacao(SUL);
					rede[y][x]->arbitro_norte.setPrioridade();
				}

				if (rede[y][x]->roteamento_norte.portaDestino == LOCAL)
				{
					ver_norte[y][x] = false;
					printf("CHEGOUUUUU norte...\n");
					rede[y][x]->buffer_local->din = rede[y][x]->buffer_norte->flits.front();
					rede[y][x]->buffer_norte->remove();
					rede[y][x]->buffer_local->add();				
				} else {
					if (rede[y][x]->roteamento_norte.portaDestino == NORTE)
					{
						rede[y][x]->cf_saida_norte->out_val.write(1);
					}
					if (rede[y][x]->roteamento_norte.portaDestino == SUL and rede[y][x]->arbitro_norte.checkPrioridade() == SUL)
					{
						ver_norte[y][x] = false;
						rede[y][x]->cf_saida_sul->out_val.write(1);
						rede[y][x]->buffer_sul->din = rede[y][x]->buffer_norte->flits.front();
						rede[y][x]->buffer_sul->add();
						rede[y][x]->buffer_norte->remove();
						rede[y][x]->arbitro_norte.remSolicitacao(SUL);
					}
					if (rede[y][x]->roteamento_norte.portaDestino == LESTE and rede[y][x]->arbitro_norte.checkPrioridade() == LESTE)
					{
						ver_norte[y][x] = false;
						rede[y][x]->cf_saida_leste->out_val.write(1);			
						rede[y][x]->buffer_leste->din = rede[y][x]->buffer_norte->flits.front();
						rede[y][x]->buffer_leste->add();
						rede[y][x]->buffer_norte->remove();	
						rede[y][x]->arbitro_norte.remSolicitacao(LESTE);
					}
					if (rede[y][x]->roteamento_norte.portaDestino == OESTE and rede[y][x]->arbitro_norte.checkPrioridade() == OESTE)
					{
						ver_norte[y][x] = false;
						rede[y][x]->cf_saida_oeste->out_val.write(1);
						rede[y][x]->buffer_oeste->din = rede[y][x]->buffer_norte->flits.front();
						rede[y][x]->buffer_oeste->add();
						rede[y][x]->buffer_norte->remove();
						rede[y][x]->arbitro_norte.remSolicitacao(OESTE);
					}
				}


			}

			if (ver_sul[y][x])
			{
				rede[y][x]->roteamento_sul.cordenada_destino.x = rede[y][x]->buffer_sul->flits.front().cordenadas_f.x;
				rede[y][x]->roteamento_sul.cordenada_destino.y = rede[y][x]->buffer_sul->flits.front().cordenadas_f.y;								
				
				#ifdef NEGATIVE_FIRST
				rede[y][x]->roteamento_sul.rotear_negative_first();
				#endif

				#ifdef XY
				rede[y][x]->roteamento_sul.rotear_xy();
				#endif	

				#ifdef NORTH_LAST
				rede[y][x]->roteamento_sul.rotear_north_last();
				#endif

				#ifdef WEST_FIRST	
				rede[y][x]->roteamento_sul.rotear_west_first();
				#endif	

				if (rede[y][x]->roteamento_sul.portaDestino == LESTE)
				{
					rede[y][x]->arbitro_sul.addSolicitacao(LESTE);
					rede[y][x]->arbitro_sul.setPrioridade();
				} else if (rede[y][x]->roteamento_sul.portaDestino == OESTE)
				{
					rede[y][x]->arbitro_sul.addSolicitacao(OESTE);
					rede[y][x]->arbitro_sul.setPrioridade();
				} else if (rede[y][x]->roteamento_sul.portaDestino == NORTE)
				{
					rede[y][x]->arbitro_sul.addSolicitacao(NORTE);
					rede[y][x]->arbitro_sul.setPrioridade();
				} else if (rede[y][x]->roteamento_sul.portaDestino == SUL)
				{
					rede[y][x]->arbitro_sul.addSolicitacao(SUL);
					rede[y][x]->arbitro_sul.setPrioridade();
				}

				if (rede[y][x]->roteamento_sul.portaDestino == LOCAL)
				{
					ver_sul[y][x] = false;
					printf("CHEGOUUUUU sul...\n");
					rede[y][x]->buffer_local->din = rede[y][x]->buffer_sul->flits.front();
					rede[y][x]->buffer_sul->remove();
					rede[y][x]->buffer_local->add();				
				} else {
					if (rede[y][x]->roteamento_sul.portaDestino == SUL)
					{
						rede[y][x]->cf_saida_sul->out_val.write(1);
					}
					if (rede[y][x]->roteamento_sul.portaDestino == NORTE  and rede[y][x]->arbitro_sul.checkPrioridade() == NORTE)
					{
						ver_sul[y][x] = false;
						rede[y][x]->cf_saida_norte->out_val.write(1);
						rede[y][x]->buffer_norte->din = rede[y][x]->buffer_sul->flits.front();
						rede[y][x]->buffer_norte->add();
						rede[y][x]->buffer_sul->remove();
						rede[y][x]->arbitro_sul.remSolicitacao(SUL);
					}
					if (rede[y][x]->roteamento_sul.portaDestino == LESTE  and rede[y][x]->arbitro_sul.checkPrioridade() == LESTE)
					{
						ver_sul[y][x] = false;
						rede[y][x]->cf_saida_leste->out_val.write(1);			
						rede[y][x]->buffer_leste->din = rede[y][x]->buffer_sul->flits.front();
						rede[y][x]->buffer_leste->add();
						rede[y][x]->buffer_sul->remove();	
						rede[y][x]->arbitro_sul.remSolicitacao(LESTE);
					}
					if (rede[y][x]->roteamento_sul.portaDestino == OESTE  and rede[y][x]->arbitro_sul.checkPrioridade() == OESTE)
					{
						ver_sul[y][x] = false;
						rede[y][x]->cf_saida_oeste->out_val.write(1);
						rede[y][x]->buffer_oeste->din = rede[y][x]->buffer_sul->flits.front();
						rede[y][x]->buffer_oeste->add();
						rede[y][x]->buffer_sul->remove();
						rede[y][x]->arbitro_sul.remSolicitacao(OESTE);
					}
				}
			}



			if (ver_leste[y][x])
			{

				rede[y][x]->roteamento_leste.cordenada_destino.x = rede[y][x]->buffer_leste->flits.front().cordenadas_f.x;
				rede[y][x]->roteamento_leste.cordenada_destino.y = rede[y][x]->buffer_leste->flits.front().cordenadas_f.y;	


				#ifdef NEGATIVE_FIRST
				rede[y][x]->roteamento_leste.rotear_negative_first();
				#endif

				#ifdef XY
				rede[y][x]->roteamento_leste.rotear_xy();
				#endif	

				#ifdef NORTH_LAST
				rede[y][x]->roteamento_leste.rotear_north_last();
				#endif

				#ifdef WEST_FIRST	
				rede[y][x]->roteamento_leste.rotear_west_first();
				#endif	

				// cout << "Porta destino " << rede[y][x]->roteamento_leste.portaDestino << endl;

				if (rede[y][x]->roteamento_leste.portaDestino == LESTE)
				{
					rede[y][x]->arbitro_leste.addSolicitacao(LESTE);
					rede[y][x]->arbitro_leste.setPrioridade();
				} else if (rede[y][x]->roteamento_leste.portaDestino == OESTE)
				{
					rede[y][x]->arbitro_leste.addSolicitacao(OESTE);
					rede[y][x]->arbitro_leste.setPrioridade();
				} else if (rede[y][x]->roteamento_leste.portaDestino == NORTE)
				{
					rede[y][x]->arbitro_leste.addSolicitacao(NORTE);
					rede[y][x]->arbitro_leste.setPrioridade();
				} else if (rede[y][x]->roteamento_leste.portaDestino == SUL)
				{
					rede[y][x]->arbitro_leste.addSolicitacao(SUL);
					rede[y][x]->arbitro_leste.setPrioridade();
				}

				if (rede[y][x]->roteamento_leste.portaDestino == LOCAL)
				{
					ver_leste[y][x] = false;
					printf("CHEGOUUUUU leste...\n");
					rede[y][x]->buffer_local->din = rede[y][x]->buffer_leste->flits.front();
					rede[y][x]->buffer_leste->remove();
					rede[y][x]->buffer_local->add();					
				} else {
					if (rede[y][x]->roteamento_leste.portaDestino == NORTE and rede[y][x]->arbitro_leste.checkPrioridade() == NORTE)
					{
						// cout << "Entrou pro norte" << endl;
						ver_leste[y][x] = false;
						rede[y][x]->cf_saida_norte->out_val.write(1);
						rede[y][x]->buffer_norte->din = rede[y][x]->buffer_leste->flits.front();
						rede[y][x]->buffer_norte->add();
						rede[y][x]->buffer_leste->remove();
						rede[y][x]->arbitro_leste.remSolicitacao(NORTE);
					}
					if (rede[y][x]->roteamento_leste.portaDestino == LESTE)
					{
						rede[y][x]->cf_saida_leste->out_val.write(1);
					}
					if (rede[y][x]->roteamento_leste.portaDestino == SUL and rede[y][x]->arbitro_leste.checkPrioridade() == SUL)
					{
						ver_leste[y][x] = false;
						rede[y][x]->cf_saida_sul->out_val.write(1);
						rede[y][x]->buffer_sul->din = rede[y][x]->buffer_leste->flits.front();
						rede[y][x]->buffer_sul->add();
						rede[y][x]->buffer_leste->remove();

						rede[y][x]->arbitro_leste.remSolicitacao(SUL);
					}	
					if (rede[y][x]->roteamento_leste.portaDestino == OESTE and rede[y][x]->arbitro_leste.checkPrioridade() == OESTE)
					{
						// cout << "Entrou pro oeste" << endl;

						ver_leste[y][x] = false;
						rede[y][x]->cf_saida_oeste->out_val.write(1);
						rede[y][x]->buffer_oeste->din = rede[y][x]->buffer_leste->flits.front();
						rede[y][x]->buffer_oeste->add();
						rede[y][x]->buffer_leste->remove();
						rede[y][x]->arbitro_leste.remSolicitacao(LESTE);
					}
				}
			}




			if (ver_oeste[y][x])
			{
				rede[y][x]->roteamento_oeste.cordenada_destino.x = rede[y][x]->buffer_oeste->flits.front().cordenadas_f.x;
				rede[y][x]->roteamento_oeste.cordenada_destino.y = rede[y][x]->buffer_oeste->flits.front().cordenadas_f.y;				

				#ifdef NEGATIVE_FIRST
				rede[y][x]->roteamento_oeste.rotear_negative_first();
				#endif

				#ifdef XY
				rede[y][x]->roteamento_oeste.rotear_xy();
				#endif	

				#ifdef NORTH_LAST
				rede[y][x]->roteamento_oeste.rotear_north_last();
				#endif

				#ifdef WEST_FIRST	
				rede[y][x]->roteamento_oeste.rotear_west_first();
				#endif	

				if (rede[y][x]->roteamento_oeste.portaDestino == LESTE)
				{
					rede[y][x]->arbitro_oeste.addSolicitacao(LESTE);
					rede[y][x]->arbitro_oeste.setPrioridade();
				} else if (rede[y][x]->roteamento_oeste.portaDestino == OESTE)
				{
					rede[y][x]->arbitro_oeste.addSolicitacao(OESTE);
					rede[y][x]->arbitro_oeste.setPrioridade();
				} else if (rede[y][x]->roteamento_oeste.portaDestino == NORTE)
				{
					rede[y][x]->arbitro_oeste.addSolicitacao(NORTE);
					rede[y][x]->arbitro_oeste.setPrioridade();
				} else if (rede[y][x]->roteamento_oeste.portaDestino == SUL)
				{
					rede[y][x]->arbitro_oeste.addSolicitacao(SUL);
					rede[y][x]->arbitro_oeste.setPrioridade();
				}

				if (rede[y][x]->roteamento_oeste.portaDestino == LOCAL)
				{
					ver_oeste[y][x] = false;
					printf("CHEGOUUUUU oeste...\n");
					rede[y][x]->buffer_local->din = rede[y][x]->buffer_oeste->flits.front();
					rede[y][x]->buffer_oeste->remove();
					rede[y][x]->buffer_local->add();					
				} else {
					if (rede[y][x]->roteamento_oeste.portaDestino == NORTE and rede[y][x]->arbitro_oeste.checkPrioridade() == NORTE)
					{
						ver_oeste[y][x] = false;
						rede[y][x]->cf_saida_norte->out_val.write(1);
						rede[y][x]->buffer_norte->din = rede[y][x]->buffer_oeste->flits.front();
						rede[y][x]->buffer_norte->add();
						rede[y][x]->buffer_oeste->remove();
						rede[y][x]->arbitro_oeste.remSolicitacao(NORTE);
					}
					if (rede[y][x]->roteamento_oeste.portaDestino == LESTE and rede[y][x]->arbitro_oeste.checkPrioridade() == LESTE)
					{
						ver_oeste[y][x] = false;
						rede[y][x]->cf_saida_leste->out_val.write(1);			
						rede[y][x]->buffer_leste->din = rede[y][x]->buffer_oeste->flits.front();
						rede[y][x]->buffer_leste->add();
						rede[y][x]->buffer_oeste->remove();	
						rede[y][x]->arbitro_oeste.remSolicitacao(LESTE);
					}
					if (rede[y][x]->roteamento_oeste.portaDestino == SUL and rede[y][x]->arbitro_oeste.checkPrioridade() == SUL)
					{
						ver_oeste[y][x] = false;
						rede[y][x]->cf_saida_sul->out_val.write(1);
						rede[y][x]->buffer_sul->din = rede[y][x]->buffer_oeste->flits.front();
						rede[y][x]->buffer_sul->add();
						rede[y][x]->buffer_oeste->remove();
						rede[y][x]->arbitro_oeste.remSolicitacao(SUL);
					}	
					if (rede[y][x]->roteamento_oeste.portaDestino == OESTE)
					{
						rede[y][x]->cf_saida_oeste->out_val.write(1);

					}
				}
			}	
		}
	}
}
//Pacote(int xs, int ys, int xd, int yd, int qt_flits, int idleCycles, int size)

// 1º Local xy -> 2º Destino xy
void REDE::injeta_flits(int local_y , int local_x, int x, int y, int qt_flits, int idleCycles, int size ) {

	Pacote *pct = new Pacote(local_y, local_x, x,y,qt_flits,idleCycles,size);

	rede[local_y][local_x]->buffer_local->din =  pct->flits;
	rede[local_y][local_x]->buffer_local->add();
}