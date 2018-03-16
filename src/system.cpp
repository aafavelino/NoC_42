	//
// Created by Adelino on 30/11/17.
//

#include "system.h"



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
			  		// cout << "só uma vez" << endl;
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



			// cout << pacotes_tg[0].contador_flits << pacotes_tg[0].qt_flits << endl;

			for (int i = 0; i < pacotes_tg.size(); ++i)
			{

				if (pacotes_tg[i].contador_ciclos == pacotes_tg[i].idleCycles and pacotes_tg[i].contador_flits < pacotes_tg[i].qt_flits)
				{

					pacotes_tg[i].contador_flits++;
					// Ultimo Flit do pacote
					if (pacotes_tg[i].contador_flits == pacotes_tg[i].qt_flits){
						pacotes_tg[i].flits.end = i;
						if (pacotes_tg[i].contador_size == pacotes_tg[i].size)
						{
							cout << "testetetet" << endl;
							pacotes_tg[i].flits.stop = true;
						}	
					}
					

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
				if (pacotes_tg[i].contador_size == pacotes_tg[i].size)
				{
					cout << "teste" << endl;
					finish = true;
				} else {
					finish = false;
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



				// if(y==0)
				// cout << rede[y][x]->buffer_local_entrada->size << endl;

			if(rede[y][x]->buffer_local_entrada->size > 0) {
				// cout <<y<<x <<"teste" << endl;
				// cout << rede[y][x]->name << endl;
				// cout << "buffer local ent" << rede[y][x]->buffer_local_entrada->size << endl;
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
					if (rede[y+1][x]->cf_norte->in_ack.read() != 1){
						rede[y+1][x]->cf_norte->val = true;

						rede[y][x]->cf_saida_sul->out_val.write(1);
					}
					// cout << "SUL" << endl;
					// cout << y << " "<<x << " -SUL- " << rede[y][x]->cf_saida_sul->out_val.read() << " " << rede[y+1][x]->cf_norte->in_ack.read() << endl;
				}
				 else if (rede[y][x]->roteamento_local.portaDestino == NORTE)
				{
					rede[y][x]->buffer_norte_saida->din =  rede[y][x]->buffer_local_entrada->flits.front();
					rede[y][x]->buffer_local_entrada->remove();
					rede[y][x]->buffer_norte_saida->add();
					if (rede[y-1][x]->cf_sul->in_ack.read() != 1)
						rede[y-1][x]->cf_sul->val = true;

						rede[y][x]->cf_saida_norte->out_val.write(1);
					
					

					// cout << y << " "<<x << " -NORTE- " << rede[y][x]->cf_saida_norte->out_val.read() << " " << rede[y-1][x]->cf_sul->in_ack.read() << endl;
				}  else if (rede[y][x]->roteamento_local.portaDestino == LESTE)
				{

					rede[y][x]->buffer_leste_saida->din =  rede[y][x]->buffer_local_entrada->flits.front();
					rede[y][x]->buffer_local_entrada->remove();
					rede[y][x]->buffer_leste_saida->add();
					if (rede[y][x+1]->cf_oeste->in_ack.read() == 0){// opaaaaaaaaaaaaaaaaaa
						rede[y][x+1]->cf_oeste->val = true;

						rede[y][x]->cf_saida_leste->out_val.write(1);
						// cout << "out_val? "<< endl; 
					}



				
					
					// cout << "LESTE" << endl;
				} else if (rede[y][x]->roteamento_local.portaDestino == OESTE)
				{	
					rede[y][x]->buffer_oeste_saida->din =  rede[y][x]->buffer_local_entrada->flits.front();
					rede[y][x]->buffer_local_entrada->remove();
					rede[y][x]->buffer_oeste_saida->add();
					if (rede[y][x-1]->cf_leste->in_ack.read() != 1){
						rede[y][x-1]->cf_leste->val = true;

						rede[y][x]->cf_saida_oeste->out_val.write(1);
					}
					// cout << "OESTE" << endl;
				}
			}


			// cout << rede[0][0]->buffer_leste->size << endl;
			if (rede[y][x]->cf_leste->in_ack.read() == 1)
			{
				printf("[%d][%d]--LESTE\n",y,x);
				rede[y][x]->buffer_leste->din = rede[y][x+1]->buffer_oeste_saida->flits.front(); 
				rede[y][x]->buffer_leste->add();
				rede[y][x+1]->buffer_oeste_saida->remove();
				if (rede[y][x+1]->buffer_oeste_saida->size == 0)
				{
					// cout << "opa 1" << endl;

					rede[y][x+1]->cf_saida_oeste->out_val.write(0);
					rede[y][x]->cf_leste->in_ack = 0;
				}
				ver_leste[y][x] = true;
			}

			if (rede[y][x]->cf_oeste->in_ack.read() == 1)
			{
				printf("[%d][%d]--OESTE\n",y,x);
				rede[y][x]->buffer_oeste->din = rede[y][x-1]->buffer_leste_saida->flits.front();			 
				rede[y][x]->buffer_oeste->add();
				rede[y][x-1]->buffer_leste_saida->remove();
				if (rede[y][x-1]->buffer_leste_saida->size == 0) {
					// cout << "opa 2" << endl;

					rede[y][x-1]->cf_saida_leste->out_val.write(0);
					rede[y][x]->cf_oeste->in_ack = 0;
				}
				ver_oeste[y][x] = true;
			}			

			if (rede[y][x]->cf_norte->in_ack.read() == 1)
			{
				printf("[%d][%d]--NORTE\n",y,x);
				rede[y][x]->buffer_norte->din = rede[y-1][x]->buffer_sul_saida->flits.front();
				rede[y][x]->buffer_norte->add();
				rede[y-1][x]->buffer_sul_saida->remove();
				if (rede[y-1][x]->buffer_sul_saida->size == 0) {
					// cout << "opa 3" << endl;

					rede[y-1][x]->cf_saida_sul->out_val.write(0);
					rede[y][x]->cf_norte->in_ack = 0;
				}
				ver_norte[y][x] = true;
			}	

			if (rede[y][x]->cf_sul->in_ack.read() == 1) 
			{
				printf("[%d][%d]--SUL\n",y,x);
				rede[y][x]->buffer_sul->din = rede[y+1][x]->buffer_norte_saida->flits.front();
				rede[y][x]->buffer_sul->add();
				rede[y+1][x]->buffer_norte_saida->remove();
				if (rede[y+1][x]->buffer_norte_saida->size == 0)
				{
					// cout << "opa 4" << endl;
					rede[y+1][x]->cf_saida_norte->out_val.write(0);
					rede[y][x]->cf_sul->in_ack = 0;
				}

				ver_sul[y][x] = true;
			}

				


	

			if (ver_sul[y][x])
			{
				// cout << "teste" << endl;
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
						cout << "end:"<<rede[y][x]->buffer_sul->flits.front().end<< clock <<endl;
						
					}
					if (rede[y][x]->buffer_sul->flits.front().stop)
					{
						cout << "ULTIMO" << endl;

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

						rede[y][x]->cf_saida_norte->out_val.write(1);
						rede[y][x]->buffer_norte_saida->din = rede[y][x]->buffer_sul->flits.front();
						rede[y][x]->buffer_norte_saida->add();
						rede[y][x]->buffer_sul->remove();
						rede[y][x]->arbitro_sul.remSolicitacao(SUL);
					}
					if (rede[y][x]->roteamento_sul.portaDestino == LESTE  and rede[y][x]->arbitro_sul.checkPrioridade() == LESTE)
					{
						
						ver_sul[y][x] = false;
						rede[y][x+1]->cf_oeste->val = true;

						rede[y][x]->cf_saida_leste->out_val.write(1);			
						rede[y][x]->buffer_leste_saida->din = rede[y][x]->buffer_sul->flits.front();
						rede[y][x]->buffer_leste_saida->add();
						rede[y][x]->buffer_sul->remove();	
						rede[y][x]->arbitro_sul.remSolicitacao(LESTE);
					}
					if (rede[y][x]->roteamento_sul.portaDestino == OESTE  and rede[y][x]->arbitro_sul.checkPrioridade() == OESTE)
					{
						
						ver_sul[y][x] = false;
						rede[y][x-1]->cf_leste->val = true;
						rede[y][x]->cf_saida_oeste->out_val.write(1);
						rede[y][x]->buffer_oeste_saida->din = rede[y][x]->buffer_sul->flits.front();
						rede[y][x]->buffer_oeste_saida->add();
						rede[y][x]->buffer_sul->remove();
						rede[y][x]->arbitro_sul.remSolicitacao(OESTE);
					}
					if (rede[y][x]->roteamento_sul.portaDestino == SUL)
					{
						rede[y+1][x]->cf_norte->val = true;

						rede[y][x]->cf_saida_sul->out_val.write(1);
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
						cout << "end: "<<rede[y][x]->buffer_norte->flits.front().end <<endl;
						
					}
						cout << "veio de: "<< rede[y][x]->buffer_norte->flits.front().begin <<endl;

					if (rede[y][x]->buffer_norte->flits.front().stop)
					{
						cout << "ULTIMO" << endl;
						pacotes_tg[rede[y][x]->buffer_norte->flits.front().begin].stop = true;
					}


					rede[y][x]->buffer_local->din = rede[y][x]->buffer_norte->flits.front();
					rede[y][x]->buffer_norte->remove();
					rede[y][x]->buffer_local->add();	
					if (rede[y][x]->buffer_norte->size == 0)
					{
						ver_norte[y][x] = false;
						// cout << "está ø" << endl;
						
					}								

				} else {
					if (rede[y][x]->roteamento_norte.portaDestino == NORTE)
					{
						rede[y-1][x]->cf_sul->val = true;

						rede[y][x]->cf_saida_norte->out_val.write(1);
					}
					if (rede[y][x]->roteamento_norte.portaDestino == SUL and rede[y][x]->arbitro_norte.checkPrioridade() == SUL)
					{
						
						ver_norte[y][x] = false;
						rede[y+1][x]->cf_norte->val = true;

						rede[y][x]->cf_saida_sul->out_val.write(1);
						rede[y][x]->buffer_sul_saida->din = rede[y][x]->buffer_norte->flits.front();
						rede[y][x]->buffer_sul_saida->add();
						rede[y][x]->buffer_norte->remove();
						rede[y][x]->arbitro_norte.remSolicitacao(SUL);
					}
					if (rede[y][x]->roteamento_norte.portaDestino == LESTE and rede[y][x]->arbitro_norte.checkPrioridade() == LESTE)
					{
						
						ver_norte[y][x] = false;
						rede[y][x+1]->cf_oeste->val = true;

						rede[y][x]->cf_saida_leste->out_val.write(1);			
						rede[y][x]->buffer_leste_saida->din = rede[y][x]->buffer_norte->flits.front();
						rede[y][x]->buffer_leste_saida->add();
						rede[y][x]->buffer_norte->remove();	
						rede[y][x]->arbitro_norte.remSolicitacao(LESTE);
					}
					if (rede[y][x]->roteamento_norte.portaDestino == OESTE and rede[y][x]->arbitro_norte.checkPrioridade() == OESTE)
					{
						
						ver_norte[y][x] = false;
						rede[y][x-1]->cf_leste->val = true;
						rede[y][x]->cf_saida_oeste->out_val.write(1);
						rede[y][x]->buffer_oeste_saida->din = rede[y][x]->buffer_norte->flits.front();
						rede[y][x]->buffer_oeste_saida->add();
						rede[y][x]->buffer_norte->remove();
						rede[y][x]->arbitro_norte.remSolicitacao(OESTE);
					}
				}


			}
			if (ver_leste[y][x])
			{
				// cout << ">>>>>>>>>>>>>>>>>>>>>>> aqui..."<< endl;
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
					
					printf("CHEGOUUUUU leste...\n");
					if (rede[y][x]->buffer_leste->flits.front().end != -1)
					{
						cout << "end: " << rede[y][x]->buffer_leste->flits.front().end <<endl;
						
					}

						// cout << "veio de: "<< rede[y][x]->buffer_leste->flits.front().begin <<endl;
					if (rede[y][x]->buffer_leste->flits.front().stop)
					{
						cout << "ULTIMO" << endl;

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

						rede[y][x]->cf_saida_leste->out_val.write(1);
					}
					if (rede[y][x]->roteamento_leste.portaDestino == NORTE and rede[y][x]->arbitro_leste.checkPrioridade() == NORTE)
					{
						// cout << "Entrou pro norte" << endl;
						
						ver_leste[y][x] = false;
						rede[y-1][x]->cf_sul->val = true;

						rede[y][x]->cf_saida_norte->out_val.write(1);
						rede[y][x]->buffer_norte_saida->din = rede[y][x]->buffer_leste->flits.front();
						rede[y][x]->buffer_norte_saida->add();
						rede[y][x]->buffer_leste->remove();
						rede[y][x]->arbitro_leste.remSolicitacao(NORTE);
					}
		
					if (rede[y][x]->roteamento_leste.portaDestino == SUL and rede[y][x]->arbitro_leste.checkPrioridade() == SUL)
					{
						
						ver_leste[y][x] = false;
						rede[y+1][x]->cf_norte->val = true;

						rede[y][x]->cf_saida_sul->out_val.write(1);
						rede[y][x]->buffer_sul_saida->din = rede[y][x]->buffer_leste->flits.front();
						rede[y][x]->buffer_sul_saida->add();
						rede[y][x]->buffer_leste->remove();

						rede[y][x]->arbitro_leste.remSolicitacao(SUL);
					}	
					if (rede[y][x]->roteamento_leste.portaDestino == OESTE/* and rede[y][x]->arbitro_leste.checkPrioridade() == OESTE*/)
					{
						// cout << "Entrou pro oeste" << endl;

						
						ver_leste[y][x] = false;
						rede[y][x-1]->cf_leste->val = true;

						rede[y][x]->cf_saida_oeste->out_val.write(1);
						rede[y][x]->buffer_oeste_saida->din = rede[y][x]->buffer_leste->flits.front();
						rede[y][x]->buffer_oeste_saida->add();
						rede[y][x]->buffer_leste->remove();
						rede[y][x]->arbitro_leste.remSolicitacao(LESTE);
					}

				}
			}




			if (ver_oeste[y][x])
			{
				// cout << "e depois?" << endl;
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
				// cout << "Porta destino do oeste " << rede[y][x]->roteamento_oeste.portaDestino << endl;
				if (rede[y][x]->roteamento_oeste.portaDestino == LOCAL)
				{
					
					printf("CHEGOUUUUU oeste...\n");
					if (rede[y][x]->buffer_oeste->flits.front().end != -1)
					{
						cout <<"end:"<< rede[y][x]->buffer_oeste->flits.front().end <<endl;
						
					}		
					if (rede[y][x]->buffer_oeste->flits.front().stop)
					{
						cout << "ULTIMO" << endl;

						pacotes_tg[rede[y][x]->buffer_oeste->flits.front().begin].stop = true;
					}			
					rede[y][x]->buffer_local->din = rede[y][x]->buffer_oeste->flits.front();
					rede[y][x]->buffer_oeste->remove();
					rede[y][x]->buffer_local->add();	
					if (rede[y][x]->buffer_oeste->size == 0)
					{
						// cout << "^^^^^^^^^" << endl;
						ver_oeste[y][x] = false;
					}									
				} else {
					if (rede[y][x]->roteamento_oeste.portaDestino == OESTE)
					{
						// cout << "^^^^^^^^^"<< "y:"<<y << " x: "<< x << " " << rede[y][x]->cf_saida_oeste->out_val.read()<< "  ******  "<< rede[y][x-1]->cf_leste->in_val.read() << endl;
							rede[y][x-1]->cf_leste->val = true;
							
			


							rede[y][x]->cf_saida_oeste->out_val.write(1);
							
						rede[y][x-1]->cf_leste->in_val.read();

					}
					if (rede[y][x]->roteamento_oeste.portaDestino == NORTE and rede[y][x]->arbitro_oeste.checkPrioridade() == NORTE)
					{
						
						ver_oeste[y][x] = false;
						rede[y-1][x]->cf_sul->val = true;

						rede[y][x]->cf_saida_norte->out_val.write(1);
						rede[y][x]->buffer_norte_saida->din = rede[y][x]->buffer_oeste->flits.front();
						rede[y][x]->buffer_norte_saida->add();
						rede[y][x]->buffer_oeste->remove();
						rede[y][x]->arbitro_oeste.remSolicitacao(NORTE);
					}
					if (rede[y][x]->roteamento_oeste.portaDestino == LESTE /*and rede[y][x]->arbitro_oeste.checkPrioridade() == LESTE*/)
					{
						// cout << "essa" <<endl;
						ver_oeste[y][x] = false;
						rede[y][x+1]->cf_oeste->val = true;

						rede[y][x]->cf_saida_leste->out_val.write(1);			
						rede[y][x]->buffer_leste_saida->din = rede[y][x]->buffer_oeste->flits.front();
						rede[y][x]->buffer_leste_saida->add();
						rede[y][x]->buffer_oeste->remove();	
						rede[y][x]->arbitro_oeste.remSolicitacao(LESTE);
					}
					if (rede[y][x]->roteamento_oeste.portaDestino == SUL and rede[y][x]->arbitro_oeste.checkPrioridade() == SUL)
					{
						
						ver_oeste[y][x] = false;
						rede[y+1][x]->cf_norte->val = true;

						rede[y][x]->cf_saida_sul->out_val.write(1);
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
