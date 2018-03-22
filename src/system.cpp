	//
// Created by Adelino on 30/11/17.
//

#include "system.h"


int tes = 0;
void REDE::comunicacao_externa() 
{
	for (int y = 0; y < ALTURA_REDE; y++)
	{
		
		if (y==0)
		{
			// cout << sc_time_stamp() << endl;
			clock++;



			if (clock == 1) {
				
				for (int i = 0; i < pacotes_tg.size(); ++i)
				{
					pacotes_tg[i].flits.ciclo = clock;
					pacotes_tg[i].flits.begin = i;
					rede[pacotes_tg[i].xs][pacotes_tg[i].ys]->buffer_local_entrada->din = pacotes_tg[i].flits;
					rede[pacotes_tg[i].xs][pacotes_tg[i].ys]->buffer_local_entrada->add();
					pacotes_tg[i].contador_flits++;
					pacotes_tg[i].first_flit = clock;
					pacotes_tg[i].contador_size++;
				}
			}
			

			for (int i = 0; i < pacotes_tg.size(); ++i)
				pacotes_tg[i].contador_ciclos++;




			for (int i = 0; i < pacotes_tg.size(); ++i)
			{
				// cout<<"pacote["<<i<<"]"<< pacotes_tg[i].contador_ciclos <<"=="<< pacotes_tg[i].idleCycles <<"-----" <<pacotes_tg[i].contador_flits <<"<"<< pacotes_tg[i].qt_flits << endl;
				if (pacotes_tg[i].contador_ciclos == pacotes_tg[i].idleCycles and pacotes_tg[i].contador_flits < pacotes_tg[i].qt_flits)
				{
					if (pacotes_tg[i].contador_flits == 0)
					{
						pacotes_tg[i].first_flit = clock;
						pacotes_tg[i].flits.ciclo = clock;
					}

					pacotes_tg[i].contador_flits++;
					// Ultimo Flit do pacote
					if (pacotes_tg[i].contador_flits == pacotes_tg[i].qt_flits){
						pacotes_tg[i].flits.end = i;
						pacotes_tg[i].last_flit = clock;

						if (pacotes_tg[i].contador_size == pacotes_tg[i].size)
						{
							pacotes_tg[i].flits.stop = true;
						}



					} else {
						pacotes_tg[i].flits.end = -1;
					}
					

					pacotes_tg[i].flits.ciclo = clock;
					rede[pacotes_tg[i].xs][pacotes_tg[i].ys]->buffer_local_entrada->din = pacotes_tg[i].flits;
					rede[pacotes_tg[i].xs][pacotes_tg[i].ys]->buffer_local_entrada->add();
					pacotes_tg[i].contador_ciclos = 0;
				}
				
			}


			for (int i = 0; i <  pacotes_tg.size(); ++i)
			{
				if (pacotes_tg[i].contador_flits == pacotes_tg[i].qt_flits)
				{
					if (pacotes_tg[i].contador_size < pacotes_tg[i].size)
					{
						pacotes_tg[i].contador_flits = 0;
					}
					pacotes_tg[i].contador_size++;

				}
			}



			for (int i = 0; i < pacotes_tg.size(); ++i){
				if (pacotes_tg[i].stop)
					cont_vetor++;
				if (i == pacotes_tg.size()-1 and cont_vetor != pacotes_tg.size())
				{
					cont_vetor = 0;
				}
			}


			if (cont_vetor == pacotes_tg.size())
			{
				sc_stop();
			}


		}



		for (int x = 0; x < LARGURA_REDE; x++)
		{   

			if(rede[y][x]->buffer_local_entrada->size > 0) {

				rede[y][x]->roteamento_local.cordenada_destino.x =  rede[y][x]->buffer_local_entrada->flits.front().cordenadas_f.x;
				rede[y][x]->roteamento_local.cordenada_destino.y =  rede[y][x]->buffer_local_entrada->flits.front().cordenadas_f.y;

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
				if (rede[y][x]->roteamento_local.portaDestino == SUL)
				{
					rede[y][x]->buffer_sul_saida->din =  rede[y][x]->buffer_local_entrada->flits.front();
					rede[y][x]->buffer_local_entrada->remove();
					rede[y][x]->buffer_sul_saida->add();
					rede[y+1][x]->cf_norte->val = true;
					rede[y][x]->cf_saida_sul->out_val.write(clock);
					
				}
				else if (rede[y][x]->roteamento_local.portaDestino == NORTE)
				{
					rede[y][x]->buffer_norte_saida->din =  rede[y][x]->buffer_local_entrada->flits.front();
					rede[y][x]->buffer_local_entrada->remove();
					rede[y][x]->buffer_norte_saida->add();
					rede[y-1][x]->cf_sul->val = true;
					rede[y][x]->cf_saida_norte->out_val.write(clock);
					
				}  else if (rede[y][x]->roteamento_local.portaDestino == LESTE)
				{
					rede[y][x]->buffer_leste_saida->din =  rede[y][x]->buffer_local_entrada->flits.front();
					rede[y][x]->buffer_local_entrada->remove();
					rede[y][x]->buffer_leste_saida->add();
					rede[y][x+1]->cf_oeste->val = true;
					rede[y][x]->cf_saida_leste->out_val.write(clock);

				} else if (rede[y][x]->roteamento_local.portaDestino == OESTE)
				{	
					rede[y][x]->buffer_oeste_saida->din =  rede[y][x]->buffer_local_entrada->flits.front();
					rede[y][x]->buffer_local_entrada->remove();
					rede[y][x]->buffer_oeste_saida->add();
					rede[y][x-1]->cf_leste->val = true;
					rede[y][x]->cf_saida_oeste->out_val.write(clock);

				}
			}




			if (rede[y][x]->cf_leste->ack == true)
			{

				// printf("[%d][%d]--LESTE\n",y,x);
				rede[y][x]->buffer_leste->din = rede[y][x+1]->buffer_oeste_saida->flits.front(); 
				rede[y][x]->buffer_leste->add();
				rede[y][x+1]->buffer_oeste_saida->remove();
				if (rede[y][x+1]->buffer_oeste_saida->size == 0)
					rede[y][x]->cf_leste->ack = false;
				ver_leste[y][x] = true;
			}

			if (rede[y][x]->cf_oeste->ack == true)
			{
				// printf("[%d][%d]--OESTE\n",y,x);
				rede[y][x]->buffer_oeste->din = rede[y][x-1]->buffer_leste_saida->flits.front();			 
				rede[y][x]->buffer_oeste->add();
				rede[y][x-1]->buffer_leste_saida->remove();
				if (rede[y][x-1]->buffer_leste_saida->size == 0)
					rede[y][x]->cf_oeste->ack = false;
				ver_oeste[y][x] = true;
			}			

			if (rede[y][x]->cf_norte->ack == true)
			{			
				// printf("[%d][%d]--NORTE\n",y,x);
				rede[y][x]->buffer_norte->din = rede[y-1][x]->buffer_sul_saida->flits.front();
				rede[y][x]->buffer_norte->add();
				rede[y-1][x]->buffer_sul_saida->remove();
				if (rede[y-1][x]->buffer_sul_saida->size ==0)
					rede[y][x]->cf_norte->ack = false;
				ver_norte[y][x] = true;
			}	

			if (rede[y][x]->cf_sul->ack == true) 
			{
				// printf("[%d][%d]--SUL\n",y,x);
				rede[y][x]->buffer_sul->din = rede[y+1][x]->buffer_norte_saida->flits.front();
				rede[y][x]->buffer_sul->add();
				rede[y+1][x]->buffer_norte_saida->remove();
				if (rede[y+1][x]->buffer_norte_saida->size == 0)
					rede[y][x]->cf_sul->ack = false;
				ver_sul[y][x] = true;
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

					printf("CHEGOUUUUU sul...\n");

					if (rede[y][x]->buffer_sul->flits.front().end != -1)
					{
						latencias[rede[y][x]->buffer_sul->flits.front().end].push_back(clock - rede[y][x]->buffer_sul->flits.front().ciclo);
					}
					if (rede[y][x]->buffer_sul->flits.front().stop)
					{
						pacotes_tg[rede[y][x]->buffer_sul->flits.front().begin].stop = true;
					}

					rede[y][x]->buffer_local->din = rede[y][x]->buffer_sul->flits.front();
					rede[y][x]->buffer_sul->remove();
					rede[y][x]->buffer_local->add();

					if (rede[y][x]->buffer_sul->size == 0)
					{
						ver_sul[y][x] = false;
					}

				} else {

					if (rede[y][x]->roteamento_sul.portaDestino == NORTE  and rede[y][x]->arbitro_sul.checkPrioridade() == NORTE)
					{
						ver_sul[y][x] = false;
						rede[y-1][x]->cf_sul->val = true;

						rede[y][x]->cf_saida_norte->out_val.write(clock);
						rede[y][x]->buffer_norte_saida->din = rede[y][x]->buffer_sul->flits.front();
						rede[y][x]->buffer_norte_saida->add();
						rede[y][x]->buffer_sul->remove();
						rede[y][x]->arbitro_sul.remSolicitacao(SUL);
					}
					if (rede[y][x]->roteamento_sul.portaDestino == LESTE  and rede[y][x]->arbitro_sul.checkPrioridade() == LESTE)
					{
						
						ver_sul[y][x] = false;
						rede[y][x+1]->cf_oeste->val = true;

						rede[y][x]->cf_saida_leste->out_val.write(clock);			
						rede[y][x]->buffer_leste_saida->din = rede[y][x]->buffer_sul->flits.front();
						rede[y][x]->buffer_leste_saida->add();
						rede[y][x]->buffer_sul->remove();	
						rede[y][x]->arbitro_sul.remSolicitacao(LESTE);
					}
					if (rede[y][x]->roteamento_sul.portaDestino == OESTE  and rede[y][x]->arbitro_sul.checkPrioridade() == OESTE)
					{
						
						ver_sul[y][x] = false;
						rede[y][x-1]->cf_leste->val = true;                                                                                                                                                                                                                                                                                
						rede[y][x]->cf_saida_oeste->out_val.write(clock);
						rede[y][x]->buffer_oeste_saida->din = rede[y][x]->buffer_sul->flits.front();
						rede[y][x]->buffer_oeste_saida->add();
						rede[y][x]->buffer_sul->remove();
						rede[y][x]->arbitro_sul.remSolicitacao(OESTE);
					}
					if (rede[y][x]->roteamento_sul.portaDestino == SUL)
					{
						rede[y+1][x]->cf_norte->val = true;

						rede[y][x]->cf_saida_sul->out_val.write(clock);
					}
				}
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
					printf("CHEGOUUUUU norte...\n");
					
					if (rede[y][x]->buffer_norte->flits.front().end != -1)
					{
						latencias[rede[y][x]->buffer_norte->flits.front().end].push_back(clock - rede[y][x]->buffer_norte->flits.front().ciclo);
					}

					if (rede[y][x]->buffer_norte->flits.front().stop)
					{
						pacotes_tg[rede[y][x]->buffer_norte->flits.front().begin].stop = true;
					}


					rede[y][x]->buffer_local->din = rede[y][x]->buffer_norte->flits.front();
					rede[y][x]->buffer_norte->remove();
					rede[y][x]->buffer_local->add();	
					if (rede[y][x]->buffer_norte->size == 0)
					{
						ver_norte[y][x] = false;
						
					}								
				} else {
					if (rede[y][x]->roteamento_norte.portaDestino == NORTE)
					{
						rede[y-1][x]->cf_sul->val = true;

						rede[y][x]->cf_saida_norte->out_val.write(clock);
					}
					if (rede[y][x]->roteamento_norte.portaDestino == SUL and rede[y][x]->arbitro_norte.checkPrioridade() == SUL)
					{
						
						ver_norte[y][x] = false;
						rede[y+1][x]->cf_norte->val = true;

						rede[y][x]->cf_saida_sul->out_val.write(clock);
						rede[y][x]->buffer_sul_saida->din = rede[y][x]->buffer_norte->flits.front();
						rede[y][x]->buffer_sul_saida->add();
						rede[y][x]->buffer_norte->remove();
						rede[y][x]->arbitro_norte.remSolicitacao(SUL);
					}
					if (rede[y][x]->roteamento_norte.portaDestino == LESTE and rede[y][x]->arbitro_norte.checkPrioridade() == LESTE)
					{
						
						ver_norte[y][x] = false;
						rede[y][x+1]->cf_oeste->val = true;

						rede[y][x]->cf_saida_leste->out_val.write(clock);			
						rede[y][x]->buffer_leste_saida->din = rede[y][x]->buffer_norte->flits.front();
						rede[y][x]->buffer_leste_saida->add();
						rede[y][x]->buffer_norte->remove();	
						rede[y][x]->arbitro_norte.remSolicitacao(LESTE);
					}
					if (rede[y][x]->roteamento_norte.portaDestino == OESTE and rede[y][x]->arbitro_norte.checkPrioridade() == OESTE)
					{
						
						ver_norte[y][x] = false;
						rede[y][x-1]->cf_leste->val = true;
						rede[y][x]->cf_saida_oeste->out_val.write(clock);
						rede[y][x]->buffer_oeste_saida->din = rede[y][x]->buffer_norte->flits.front();
						rede[y][x]->buffer_oeste_saida->add();
						rede[y][x]->buffer_norte->remove();
						rede[y][x]->arbitro_norte.remSolicitacao(OESTE);
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
					
					printf("CHEGOUUUUU leste...\n");
					if (rede[y][x]->buffer_leste->flits.front().end != -1)
					{
						latencias[rede[y][x]->buffer_leste->flits.front().end].push_back(clock - rede[y][x]->buffer_leste->flits.front().ciclo);
					}
					if (rede[y][x]->buffer_leste->flits.front().stop)
					{
						pacotes_tg[rede[y][x]->buffer_leste->flits.front().begin].stop = true;
					}

					rede[y][x]->buffer_local->din = rede[y][x]->buffer_leste->flits.front();
					rede[y][x]->buffer_leste->remove();
					rede[y][x]->buffer_local->add();	
					if (rede[y][x]->buffer_leste->size == 0)
					{
						ver_leste[y][x] = false;
					}									
				} else {
					if (rede[y][x]->roteamento_leste.portaDestino == LESTE)
					{
						rede[y][x+1]->cf_oeste->val = true;

						rede[y][x]->cf_saida_leste->out_val.write(clock);
					}
					if (rede[y][x]->roteamento_leste.portaDestino == NORTE and rede[y][x]->arbitro_leste.checkPrioridade() == NORTE)
					{

						ver_leste[y][x] = false;
						rede[y-1][x]->cf_sul->val = true;
						rede[y][x]->cf_saida_norte->out_val.write(clock);
						rede[y][x]->buffer_norte_saida->din = rede[y][x]->buffer_leste->flits.front();
						rede[y][x]->buffer_norte_saida->add();
						rede[y][x]->buffer_leste->remove();
						rede[y][x]->arbitro_leste.remSolicitacao(NORTE);
					}
					if (rede[y][x]->roteamento_leste.portaDestino == SUL and rede[y][x]->arbitro_leste.checkPrioridade() == SUL)
					{
						ver_leste[y][x] = false;
						rede[y+1][x]->cf_norte->val = true;
						rede[y][x]->cf_saida_sul->out_val.write(clock);
						rede[y][x]->buffer_sul_saida->din = rede[y][x]->buffer_leste->flits.front();
						rede[y][x]->buffer_sul_saida->add();
						rede[y][x]->buffer_leste->remove();
						rede[y][x]->arbitro_leste.remSolicitacao(SUL);
					}	
					if (rede[y][x]->roteamento_leste.portaDestino == OESTE/* and rede[y][x]->arbitro_leste.checkPrioridade() == OESTE*/)
					{

						ver_leste[y][x] = false;
						rede[y][x-1]->cf_leste->val = true;
						rede[y][x]->cf_saida_oeste->out_val.write(clock);
						rede[y][x]->buffer_oeste_saida->din = rede[y][x]->buffer_leste->flits.front();
						rede[y][x]->buffer_oeste_saida->add();
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
					
					printf("CHEGOUUUUU oeste...\n");

					if (rede[y][x]->buffer_oeste->flits.front().end != -1)
					{
						latencias[rede[y][x]->buffer_oeste->flits.front().end].push_back(clock - rede[y][x]->buffer_oeste->flits.front().ciclo);	
					}		
					if (rede[y][x]->buffer_oeste->flits.front().stop)
					{
						pacotes_tg[rede[y][x]->buffer_oeste->flits.front().begin].stop = true;
					}			
					rede[y][x]->buffer_local->din = rede[y][x]->buffer_oeste->flits.front();
					rede[y][x]->buffer_oeste->remove();
					rede[y][x]->buffer_local->add();	
					if (rede[y][x]->buffer_oeste->size == 0)
					{
						ver_oeste[y][x] = false;
					}									
				} else {
					if (rede[y][x]->roteamento_oeste.portaDestino == OESTE)
					{
						rede[y][x-1]->cf_leste->val = true;
						rede[y][x]->cf_saida_oeste->out_val.write(clock);
					}
					if (rede[y][x]->roteamento_oeste.portaDestino == NORTE and rede[y][x]->arbitro_oeste.checkPrioridade() == NORTE)
					{
						ver_oeste[y][x] = false;
						rede[y-1][x]->cf_sul->val = true;
						rede[y][x]->cf_saida_norte->out_val.write(clock);
						rede[y][x]->buffer_norte_saida->din = rede[y][x]->buffer_oeste->flits.front();
						rede[y][x]->buffer_norte_saida->add();
						rede[y][x]->buffer_oeste->remove();
						rede[y][x]->arbitro_oeste.remSolicitacao(NORTE);
					}
					if (rede[y][x]->roteamento_oeste.portaDestino == LESTE /*and rede[y][x]->arbitro_oeste.checkPrioridade() == LESTE*/)
					{
						
						ver_oeste[y][x] = false;
						rede[y][x+1]->cf_oeste->val = true;
						rede[y][x]->cf_saida_leste->out_val.write(clock);			
						rede[y][x]->buffer_leste_saida->din = rede[y][x]->buffer_oeste->flits.front();
						rede[y][x]->buffer_leste_saida->add();
						rede[y][x]->buffer_oeste->remove();	
						rede[y][x]->arbitro_oeste.remSolicitacao(LESTE);
					}
					if (rede[y][x]->roteamento_oeste.portaDestino == SUL and rede[y][x]->arbitro_oeste.checkPrioridade() == SUL)
					{
						
						ver_oeste[y][x] = false;
						rede[y+1][x]->cf_norte->val = true;
						rede[y][x]->cf_saida_sul->out_val.write(clock);
						rede[y][x]->buffer_sul_saida->din = rede[y][x]->buffer_oeste->flits.front();
						rede[y][x]->buffer_sul_saida->add();
						rede[y][x]->buffer_oeste->remove();
						rede[y][x]->arbitro_oeste.remSolicitacao(SUL);
					}	

				}
			}	
		}
	}
}
