//
// Created by Adelino on 30/11/17.
//

#include "noc.h"

bool teste = false;
std::vector<int> size_pac;
std::tuple<int, int> origem;



int org = 0;


// *************************** Interface para injetar flits ****************************
void Noc::interface() {
	origem = nula;
	clock++;

	for (int i = 0; i < pacotes_tg.size(); ++i)
		pacotes_tg[i].contador_ciclos++;
	
	if (cont_vetor == (pacotes_tg.size()*flit_stop))
		sc_stop();	


	if (clock == 1)
	{
		// Criar os primeiros pacotes...
		for (int i = 0; i < pacotes_tg.size(); ++i)
		{
			pacotes_tg[i].injetado.push_back(true);
			pacotes_tg[i].ciclo_criacao.push_back(clock);
			pacotes_tg[i].contador.push_back(1);
		}
	} 








	for (int i = 0; i < pacotes_tg.size(); ++i)
	{
		if (pacotes_tg[i].contador_ciclos >= pacotes_tg[i].idleCycles)
		{
			if (pacotes_tg[i].contador.size() < pacotes_tg[i].pacotes)
			{

				pacotes_tg[i].ciclo_criacao.push_back(clock);
				pacotes_tg[i].injetado.push_back(true);
				if (pacotes_tg[i].injetado[0] == false)
				{
					pacotes_tg[i].injetado.pop_front();
				}
				pacotes_tg[i].contador_ciclos = 0;
				pacotes_tg[i].contador.push_back(1);
			}
		}
	}

	for (int i = 0; i < pacotes_tg.size(); ++i)
	{
		if (pacotes_tg[i].fila_flits.size() > 0)
		{
			if (pacotes_tg[i].injetado[0] != false)
			{	
				if (origem == pacotes_tg[i].origem)
				{				
					goto next;

				} else if (origem == nula)
				{
					origem = pacotes_tg[i].origem;	
				} else if (origem != pacotes_tg[i].origem and origem != nula) 
				{
					origem = pacotes_tg[i].origem;
				}

				if (noc[std::get<0>(pacotes_tg[i].origem)][std::get<1>(pacotes_tg[i].origem)]->buffer_local_entrada->espaco(pacotes_tg[i].fila_flits.front().prioridade) > 0)
				{
					if (pacotes_tg[i].fila_flits.front().end != -1){
						if (pacotes_tg[i].injetado.size() == 1)
						{
							pacotes_tg[i].injetado[0] = false;
						} else {
							pacotes_tg[i].injetado.pop_front();
						}
	
					}
					noc[std::get<0>(pacotes_tg[i].origem)][std::get<1>(pacotes_tg[i].origem)]->buffer_local_entrada->din = pacotes_tg[i].fila_flits.front();
					noc[std::get<0>(pacotes_tg[i].origem)][std::get<1>(pacotes_tg[i].origem)]->buffer_local_entrada->add(pacotes_tg[i].fila_flits.front().prioridade);
					pacotes_tg[i].fila_flits.pop();
				}
			}
		}
		next:;	
	}


}
// ******************************** FIM INTERFACE *************************************	

void Noc::simulacao() 
{
	for (int x = 0; x < ALTURA_REDE; ++x)
	{
		

		for (int y = 0; y < LARGURA_REDE; ++y)
		{
				bool v_local = false;
				for (int i = 0; i < QT_CANAIS_VIRTUAIS; ++i)
				{
					if (noc[x][y]->buffer_local_entrada->size[i] == 0)
					{
						v_local = false;
					} else {
						v_local = true; 
						break;
					}
				}

			if(v_local) {
				for (int i = 0; i < QT_CANAIS_VIRTUAIS; ++i)
				{
					if (noc[x][y]->local_fila_prio[i] <= noc[x][y]->fila_virtual[i] and noc[x][y]->buffer_local_entrada->size[i] != 0)
					{
						
						if (noc[x][y]->local_fila_prio[i] == noc[x][y]->fila_virtual[i])
						{
							noc[x][y]->local_fila_prio[i] = 0;
						} else{
							noc[x][y]->local_fila_prio[i]++;
						}
						noc[x][y]->canal_local = i;
						break;
					}
				}
				noc[x][y]->roteamento_local.destino =  noc[x][y]->buffer_local_entrada->buffer_virtual[noc[x][y]->canal_local].front().destino;

				switch(arquivo[2]) {
					case 1:
						noc[x][y]->roteamento_local.rotear_negative_first();
					break;
					case 2:
						noc[x][y]->roteamento_local.rotear_xy();
					break;
					case 3:
						noc[x][y]->roteamento_local.rotear_north_last();
					break;
					case 4:
						noc[x][y]->roteamento_local.rotear_west_first();
					break;
					case 5:
						(x%2==0)? noc[x][y]->roteamento_local.odd_even = 0: noc[x][y]->roteamento_local.odd_even = 1;
						noc[x][y]->roteamento_local.portaAnterior = LOCAL;
						noc[x][y]->roteamento_local.rotear_odd_even();					
					break;																				
				}


				if (noc[x][y]->roteamento_local.portaDestino == SUL)
				{
					if (noc[x][y]->buffer_sul_saida->espaco(noc[x][y]->buffer_local_entrada->buffer_virtual[noc[x][y]->canal_local].front().prioridade) > 0)
					{
						noc[x][y]->buffer_sul_saida->din =  noc[x][y]->buffer_local_entrada->buffer_virtual[noc[x][y]->canal_local].front();
						noc[x][y]->buffer_local_entrada->remove(noc[x][y]->canal_local);
						noc[x][y]->buffer_sul_saida->add(noc[x][y]->canal_local);

						noc[x+1][y]->cf_norte->val = true;
						noc[x+1][y]->canal_vt = noc[x][y]->canal_local;
						throughput[x][y]->saida_sul++;
						noc[x][y]->cf_saida_sul->out_val.write(clock);
					}
				}
				else if (noc[x][y]->roteamento_local.portaDestino == NORTE)
				{
					if (noc[x][y]->buffer_norte_saida->espaco(noc[x][y]->buffer_local_entrada->buffer_virtual[noc[x][y]->canal_local].front().prioridade) > 0)
					{
						noc[x][y]->buffer_norte_saida->din =  noc[x][y]->buffer_local_entrada->buffer_virtual[noc[x][y]->canal_local].front();
						noc[x][y]->buffer_local_entrada->remove(noc[x][y]->canal_local);
						noc[x][y]->buffer_norte_saida->add(noc[x][y]->canal_local);
					
						noc[x-1][y]->cf_sul->val = true;
						noc[x-1][y]->canal_vt = noc[x][y]->canal_local;
						throughput[x][y]->saida_norte++;
						noc[x][y]->cf_saida_norte->out_val.write(clock);
					}
				}  else if (noc[x][y]->roteamento_local.portaDestino == LESTE)
				{
					if (noc[x][y]->buffer_leste_saida->espaco(noc[x][y]->buffer_local_entrada->buffer_virtual[noc[x][y]->canal_local].front().prioridade) > 0)
					{
						noc[x][y]->buffer_leste_saida->din =  noc[x][y]->buffer_local_entrada->buffer_virtual[noc[x][y]->canal_local].front();
						noc[x][y]->buffer_local_entrada->remove(noc[x][y]->canal_local);
						noc[x][y]->buffer_leste_saida->add(noc[x][y]->canal_local);

						
						noc[x][y+1]->cf_oeste->val = true;
						noc[x][y+1]->canal_vt = noc[x][y]->canal_local;
						throughput[x][y]->saida_leste++;
						noc[x][y]->cf_saida_leste->out_val.write(clock);
					}
				} else if (noc[x][y]->roteamento_local.portaDestino == OESTE)
				{	
					if (noc[x][y]->buffer_oeste_saida->espaco(noc[x][y]->buffer_local_entrada->buffer_virtual[noc[x][y]->canal_local].front().prioridade) > 0)
					{
						noc[x][y]->buffer_oeste_saida->din =  noc[x][y]->buffer_local_entrada->buffer_virtual[noc[x][y]->canal_local].front();
						noc[x][y]->buffer_local_entrada->remove(noc[x][y]->canal_local);
						noc[x][y]->buffer_oeste_saida->add(noc[x][y]->canal_local);

						noc[x][y-1]->cf_leste->val = true;
						noc[x][y-1]->canal_vt = noc[x][y]->canal_local;
						throughput[x][y]->saida_oeste++;
						noc[x][y]->cf_saida_oeste->out_val.write(clock);
					}
				}
			}




			if (noc[x][y]->cf_leste->ack == true)
			{
				for (int i = 0; i < QT_CANAIS_VIRTUAIS; ++i)
				{
					if (noc[x][y]->oeste_fila_prio[i] <= noc[x][y]->fila_virtual[i] and noc[x][y+1]->buffer_oeste_saida->size[i] != 0)
					{
						// cout << "PRINT i: " << i << endl;
						if (noc[x][y]->oeste_fila_prio[i] == noc[x][y]->fila_virtual[i])
						{
							noc[x][y]->oeste_fila_prio[i] = 0;
						} else{
							noc[x][y]->oeste_fila_prio[i]++;
						}
						noc[x][y]->canal_leste = i;
						break;
					}
				}
				// printf("[%d][%d]--LESTE\n",y,x);
				if (noc[x][y]->buffer_leste->espaco(noc[x][y]->canal_leste) > 0)
				{
					noc[x][y]->buffer_leste->din = noc[x][y+1]->buffer_oeste_saida->buffer_virtual[noc[x][y]->canal_leste].front(); 
					noc[x][y]->buffer_leste->add(noc[x][y]->canal_leste);
					noc[x][y+1]->buffer_oeste_saida->remove(noc[x][y]->canal_leste);


				}
					bool v_oeste = false;
					for (int i = 0; i < QT_CANAIS_VIRTUAIS; ++i)
					{
						if (noc[x][y+1]->buffer_oeste_saida->size[i] == 0)
						{
							v_oeste = true;
						} else {
							v_oeste = false; 
							break;
						}
					}

					if (v_oeste)
						noc[x][y]->cf_leste->ack = false;
					ver_leste[x][y] = true;				
			}



			if (noc[x][y]->cf_norte->ack == true)
			{			


				for (int i = 0; i < QT_CANAIS_VIRTUAIS; ++i)
				{
					if (noc[x][y]->sul_fila_prio[i] <= noc[x][y]->fila_virtual[i] and noc[x-1][y]->buffer_sul_saida->size[i] != 0)
					{
						// cout << "PRINT i: " << i << endl;
						if (noc[x][y]->sul_fila_prio[i] == noc[x][y]->fila_virtual[i])
						{
							noc[x][y]->sul_fila_prio[i] = 0;
						} else{
							noc[x][y]->sul_fila_prio[i]++;
						}
						noc[x][y]->canal_norte = i;
						break;
					}
				}				
				// printf("[%d][%d]--NORTE\n",y,x);
				if (noc[x][y]->buffer_norte->espaco(noc[x][y]->canal_norte) > 0)
				{
					noc[x][y]->buffer_norte->din = noc[x-1][y]->buffer_sul_saida->buffer_virtual[noc[x][y]->canal_norte].front();
					noc[x][y]->buffer_norte->add(noc[x][y]->canal_norte);
					noc[x-1][y]->buffer_sul_saida->remove(noc[x][y]->canal_norte);
				

				}
					bool v_sul = false;
					for (int i = 0; i < QT_CANAIS_VIRTUAIS; ++i)
					{
						if (noc[x-1][y]->buffer_sul_saida->size[i] == 0)
						{
							v_sul = true;
						} else {
							v_sul = false; 
							break;
						}
					}

					if (v_sul)
						noc[x][y]->cf_norte->ack = false;
					ver_norte[x][y] = true;	



			}	


			if (noc[x][y]->cf_oeste->ack == true)
			{

				for (int i = 0; i < QT_CANAIS_VIRTUAIS; ++i)
				{
					if (noc[x][y]->leste_fila_prio[i] <= noc[x][y]->fila_virtual[i] and noc[x][y-1]->buffer_leste_saida->size[i] != 0)
					{
						// cout << "PRINT i: " << i << endl;
						if (noc[x][y]->leste_fila_prio[i] == noc[x][y]->fila_virtual[i])
						{
							noc[x][y]->leste_fila_prio[i] = 0;
						} else{
							noc[x][y]->leste_fila_prio[i]++;
						}
						noc[x][y]->canal_oeste = i;
						break;
					}
				}					
				// printf("[%d][%d]--OESTE\n",y,x);
				if (noc[x][y]->buffer_oeste->espaco(noc[x][y]->canal_oeste) > 0)
				{
					noc[x][y]->buffer_oeste->din = noc[x][y-1]->buffer_leste_saida->buffer_virtual[noc[x][y]->canal_oeste].front();			 
					noc[x][y]->buffer_oeste->add(noc[x][y]->canal_oeste);
					noc[x][y-1]->buffer_leste_saida->remove(noc[x][y]->canal_oeste);
						
				}

					bool v_leste = false;
					for (int i = 0; i < QT_CANAIS_VIRTUAIS; ++i)
					{
						if (noc[x][y-1]->buffer_leste_saida->size[i] == 0)
						{
							v_leste = true;
						} else {
							v_leste = false; 
							break;
						}
					}
					if (v_leste)
						noc[x][y]->cf_oeste->ack = false;
					ver_oeste[x][y] = true;
			}			


			if (noc[x][y]->cf_sul->ack == true) 
			{

				for (int i = 0; i < QT_CANAIS_VIRTUAIS; ++i)
				{
					if (noc[x][y]->norte_fila_prio[i] <= noc[x][y]->fila_virtual[i] and noc[x+1][y]->buffer_norte_saida->size[i] != 0)
					{
						if (noc[x][y]->norte_fila_prio[i] == noc[x][y]->fila_virtual[i])
						{
							noc[x][y]->norte_fila_prio[i] = 0;
						} else{
							noc[x][y]->norte_fila_prio[i]++;
						}
						noc[x][y]->canal_sul = i;
						break;
					}
				}					
				// printf("[%d][%d]--SUL\n",y,x);

				if (noc[x][y]->buffer_sul->espaco(noc[x][y]->canal_sul) > 0)
				{
					noc[x][y]->buffer_sul->din = noc[x+1][y]->buffer_norte_saida->buffer_virtual[noc[x][y]->canal_sul].front();
					noc[x][y]->buffer_sul->add(noc[x][y]->canal_sul);
					noc[x+1][y]->buffer_norte_saida->remove(noc[x][y]->canal_sul);
					
				}
					bool v_norte = false;
					for (int i = 0; i < QT_CANAIS_VIRTUAIS; ++i)
					{
						if (noc[x+1][y]->buffer_norte_saida->size[i] == 0)
						{
							v_norte = true;
						} else {
							v_norte = false; 
							break;
						}
					}

					if (v_norte)
						noc[x][y]->cf_sul->ack = false;
					ver_sul[x][y] = true;


			}




			if (ver_norte[x][y])
			{

				// cout << "entrou " << noc[x][y]->canal_norte << endl;
				noc[x][y]->roteamento_norte.destino = noc[x][y]->buffer_norte->buffer_virtual[noc[x][y]->canal_norte].front().destino;
				
				
				switch(arquivo[2]) {
					case 1:
						noc[x][y]->roteamento_norte.rotear_negative_first();
					break;
					case 2:
						noc[x][y]->roteamento_norte.rotear_xy();
					break;
					case 3:
						noc[x][y]->roteamento_norte.rotear_north_last();
					break;
					case 4:
						noc[x][y]->roteamento_norte.rotear_west_first();
					break;
					case 5:
						(x%2==0)? noc[x][y]->roteamento_norte.odd_even = 0: noc[x][y]->roteamento_norte.odd_even = 1;
						noc[x][y]->roteamento_norte.portaAnterior = NORTE;
						noc[x][y]->roteamento_norte.rotear_odd_even();					
					break;																				
				}


				if (noc[x][y]->roteamento_norte.portaDestino == LESTE)
				{
					noc[x][y]->arbitro_norte.addSolicitacao(LESTE,noc[x][y]->buffer_norte->buffer_virtual[noc[x][y]->canal_norte].front());
					noc[x][y]->arbitro_norte.setPrioridade();
				} else if (noc[x][y]->roteamento_norte.portaDestino == OESTE)
				{
					noc[x][y]->arbitro_norte.addSolicitacao(OESTE,noc[x][y]->buffer_norte->buffer_virtual[noc[x][y]->canal_norte].front());
					noc[x][y]->arbitro_norte.setPrioridade();
				} else if (noc[x][y]->roteamento_norte.portaDestino == NORTE)
				{
					noc[x][y]->arbitro_norte.addSolicitacao(NORTE,noc[x][y]->buffer_norte->buffer_virtual[noc[x][y]->canal_norte].front());
					noc[x][y]->arbitro_norte.setPrioridade();
				} else if (noc[x][y]->roteamento_norte.portaDestino == SUL)
				{
					noc[x][y]->arbitro_norte.addSolicitacao(SUL,noc[x][y]->buffer_norte->buffer_virtual[noc[x][y]->canal_norte].front());
					noc[x][y]->arbitro_norte.setPrioridade();
				}
				
				if (noc[x][y]->roteamento_norte.portaDestino == LOCAL)
				{
					// printf("Chegou pelo norte...\n");

					
					if (noc[x][y]->buffer_norte->buffer_virtual[noc[x][y]->canal_norte].front().end != -1)
					{
						pacotes_tg[noc[x][y]->buffer_norte->buffer_virtual[noc[x][y]->canal_norte].front().end].ciclo_final.push_back(clock);
						cont_vetor++;
					}

					latencias[noc[x][y]->buffer_norte->buffer_virtual[noc[x][y]->canal_norte].front().id].push_back(clock - noc[x][y]->buffer_norte->buffer_virtual[noc[x][y]->canal_norte].front().inicio);


					noc[x][y]->buffer_local->din = noc[x][y]->buffer_norte->buffer_virtual[noc[x][y]->canal_norte].front();
					noc[x][y]->buffer_norte->remove(noc[x][y]->canal_norte);
					noc[x][y]->buffer_local->add(noc[x][y]->canal_norte);
	
					////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					if (noc[x][y]->buffer_norte->isEmpty(noc[x][y]->canal_norte) == 1)
					{
						ver_norte[x][y] = false;	
					}								
				} else {
					if (noc[x][y]->roteamento_norte.portaDestino == NORTE)
					{
						noc[x-1][y]->cf_sul->val = true;
						noc[x-1][y]->canal_vt = noc[x][y]->canal_norte;
						throughput[x][y]->saida_norte++;
						noc[x][y]->cf_saida_norte->out_val.write(clock);
					}
					if (noc[x][y]->roteamento_norte.portaDestino == SUL and noc[x][y]->arbitro_norte.checkPrioridade() == SUL)
					{
						


						noc[x+1][y]->cf_norte->val = true;
						noc[x+1][y]->canal_vt = noc[x][y]->canal_norte;
						noc[x][y]->cf_saida_sul->out_val.write(clock);
						noc[x][y]->buffer_sul_saida->din = noc[x][y]->buffer_norte->buffer_virtual[noc[x][y]->canal_norte].front();
						
						noc[x][y]->buffer_sul_saida->add(noc[x][y]->canal_norte);
						noc[x][y]->buffer_norte->remove(noc[x][y]->canal_norte);
						noc[x][y]->arbitro_norte.remSolicitacao(SUL);
						throughput[x][y]->saida_sul++;
						if (noc[x][y]->buffer_norte->isEmpty(noc[x][y]->canal_norte) == 1)
							ver_norte[x][y] = false;						
					}
					if (noc[x][y]->roteamento_norte.portaDestino == LESTE and noc[x][y]->arbitro_norte.checkPrioridade() == LESTE)
					{
						
						
						noc[x][y+1]->cf_oeste->val = true;
						noc[x][y+1]->canal_vt = noc[x][y]->canal_norte;
						noc[x][y]->cf_saida_leste->out_val.write(clock);			
						noc[x][y]->buffer_leste_saida->din = noc[x][y]->buffer_norte->buffer_virtual[noc[x][y]->canal_norte].front();
						noc[x][y]->buffer_leste_saida->add(noc[x][y]->canal_norte);
						noc[x][y]->buffer_norte->remove(noc[x][y]->canal_norte);	
						noc[x][y]->arbitro_norte.remSolicitacao(LESTE);
						throughput[x][y]->saida_leste++;
						if (noc[x][y]->buffer_norte->isEmpty(noc[x][y]->canal_norte) == 1)
							ver_norte[x][y] = false;							
					}
					if (noc[x][y]->roteamento_norte.portaDestino == OESTE and noc[x][y]->arbitro_norte.checkPrioridade() == OESTE)
					{
						
						
						noc[x][y-1]->cf_leste->val = true;
						noc[x][y-1]->canal_vt = noc[x][y]->canal_norte;
						noc[x][y]->cf_saida_oeste->out_val.write(clock);
						noc[x][y]->buffer_oeste_saida->din = noc[x][y]->buffer_norte->buffer_virtual[noc[x][y]->canal_norte].front();
						noc[x][y]->buffer_oeste_saida->add(noc[x][y]->canal_norte);
						noc[x][y]->buffer_norte->remove(noc[x][y]->canal_norte);
						noc[x][y]->arbitro_norte.remSolicitacao(OESTE);
						throughput[x][y]->saida_oeste++;
						if (noc[x][y]->buffer_norte->isEmpty(noc[x][y]->canal_norte) == 1)
							ver_norte[x][y] = false;							
					}
				}


			}


			if (ver_sul[x][y])
			{
				noc[x][y]->roteamento_sul.destino = noc[x][y]->buffer_sul->buffer_virtual[noc[x][y]->canal_sul].front().destino;
	
				switch(arquivo[2]) {
					case 1:
						noc[x][y]->roteamento_sul.rotear_negative_first();
					break;
					case 2:
						noc[x][y]->roteamento_sul.rotear_xy();
					break;
					case 3:
						noc[x][y]->roteamento_sul.rotear_north_last();
					break;
					case 4:
						noc[x][y]->roteamento_sul.rotear_west_first();
					break;
					case 5:
						(x%2==0)? noc[x][y]->roteamento_sul.odd_even = 0: noc[x][y]->roteamento_sul.odd_even = 1;
						noc[x][y]->roteamento_sul.portaAnterior = SUL;
						noc[x][y]->roteamento_sul.rotear_odd_even();					
					break;																				
				}			


				if (noc[x][y]->roteamento_sul.portaDestino == LESTE)
				{
					noc[x][y]->arbitro_sul.addSolicitacao(LESTE,noc[x][y]->buffer_sul->buffer_virtual[noc[x][y]->canal_sul].front());
					noc[x][y]->arbitro_sul.setPrioridade();
				} else if (noc[x][y]->roteamento_sul.portaDestino == OESTE)
				{
					noc[x][y]->arbitro_sul.addSolicitacao(OESTE,noc[x][y]->buffer_sul->buffer_virtual[noc[x][y]->canal_sul].front());
					noc[x][y]->arbitro_sul.setPrioridade();
				} else if (noc[x][y]->roteamento_sul.portaDestino == NORTE)
				{
					noc[x][y]->arbitro_sul.addSolicitacao(NORTE,noc[x][y]->buffer_sul->buffer_virtual[noc[x][y]->canal_sul].front());
					noc[x][y]->arbitro_sul.setPrioridade();
				} else if (noc[x][y]->roteamento_sul.portaDestino == SUL)
				{
					noc[x][y]->arbitro_sul.addSolicitacao(SUL,noc[x][y]->buffer_sul->buffer_virtual[noc[x][y]->canal_sul].front());
					noc[x][y]->arbitro_sul.setPrioridade();
				}

				if (noc[x][y]->roteamento_sul.portaDestino == LOCAL)
				{

	

					// printf("Chegou pelo sul...\n");

					if (noc[x][y]->buffer_sul->buffer_virtual[noc[x][y]->canal_sul].front().end != -1)
					{
						pacotes_tg[noc[x][y]->buffer_sul->buffer_virtual[noc[x][y]->canal_sul].front().end].ciclo_final.push_back(clock);
						cont_vetor++;
					}
				
					latencias[noc[x][y]->buffer_sul->buffer_virtual[noc[x][y]->canal_sul].front().id].push_back(clock - noc[x][y]->buffer_sul->buffer_virtual[noc[x][y]->canal_sul].front().inicio);






					noc[x][y]->buffer_local->din = noc[x][y]->buffer_sul->buffer_virtual[noc[x][y]->canal_sul].front();
					noc[x][y]->buffer_sul->remove(noc[x][y]->canal_sul);
					noc[x][y]->buffer_local->add(noc[x][y]->canal_sul);

					if (noc[x][y]->buffer_sul->size[noc[x][y]->canal_sul] == 0)
					{
						ver_sul[x][y] = false;
					}

				} else {

					if (noc[x][y]->roteamento_sul.portaDestino == NORTE  and noc[x][y]->arbitro_sul.checkPrioridade() == NORTE)
					{

						noc[x-1][y]->cf_sul->val = true;
						noc[x-1][y]->canal_vt = noc[x][y]->canal_sul;
						noc[x][y]->cf_saida_norte->out_val.write(clock);
						noc[x][y]->buffer_norte_saida->din = noc[x][y]->buffer_sul->buffer_virtual[noc[x][y]->canal_sul].front();
						noc[x][y]->buffer_norte_saida->add(noc[x][y]->canal_sul);
						noc[x][y]->buffer_sul->remove(noc[x][y]->canal_sul);
						noc[x][y]->arbitro_sul.remSolicitacao(SUL);
						throughput[x][y]->saida_norte++;
						if (noc[x][y]->buffer_sul->isEmpty(noc[x][y]->canal_sul) == 1)
							ver_sul[x][y] = false;
					}
					if (noc[x][y]->roteamento_sul.portaDestino == LESTE  and noc[x][y]->arbitro_sul.checkPrioridade() == LESTE)
					{
						
						
						noc[x][y+1]->cf_oeste->val = true;
						noc[x][y+1]->canal_vt = noc[x][y]->canal_sul;
						noc[x][y]->cf_saida_leste->out_val.write(clock);			
						noc[x][y]->buffer_leste_saida->din = noc[x][y]->buffer_sul->buffer_virtual[noc[x][y]->canal_sul].front();
						noc[x][y]->buffer_leste_saida->add(noc[x][y]->canal_sul);
						noc[x][y]->buffer_sul->remove(noc[x][y]->canal_sul);	
						noc[x][y]->arbitro_sul.remSolicitacao(LESTE);
						throughput[x][y]->saida_leste++;
						if (noc[x][y]->buffer_sul->isEmpty(noc[x][y]->canal_sul) == 1)
							ver_sul[x][y] = false;						
					}
					if (noc[x][y]->roteamento_sul.portaDestino == OESTE  and noc[x][y]->arbitro_sul.checkPrioridade() == OESTE)
					{
						
						
						noc[x][y-1]->cf_leste->val = true;  
						noc[x][y-1]->canal_vt = noc[x][y]->canal_sul;                                                                                                                                                                                                                                                                              
						noc[x][y]->cf_saida_oeste->out_val.write(clock);
						noc[x][y]->buffer_oeste_saida->din = noc[x][y]->buffer_sul->buffer_virtual[noc[x][y]->canal_sul].front();
						noc[x][y]->buffer_oeste_saida->add(noc[x][y]->canal_sul);
						noc[x][y]->buffer_sul->remove(noc[x][y]->canal_sul);
						noc[x][y]->arbitro_sul.remSolicitacao(OESTE);
						throughput[x][y]->saida_oeste++;
						if (noc[x][y]->buffer_sul->isEmpty(noc[x][y]->canal_sul) == 1)
							ver_sul[x][y] = false;						
					}
					if (noc[x][y]->roteamento_sul.portaDestino == SUL)
					{
						noc[x+1][y]->cf_norte->val = true;
						noc[x+1][y]->canal_vt = noc[x][y]->canal_sul;
						throughput[x][y]->saida_sul++;
						noc[x][y]->cf_saida_sul->out_val.write(clock);
					}
				}
			}



			if (ver_leste[x][y])
			{

				noc[x][y]->roteamento_leste.destino = noc[x][y]->buffer_leste->buffer_virtual[noc[x][y]->canal_leste].front().destino;
				
				switch(arquivo[2]) {
					case 1:
						noc[x][y]->roteamento_leste.rotear_negative_first();
					break;
					case 2:
						noc[x][y]->roteamento_leste.rotear_xy();
					break;
					case 3:
						noc[x][y]->roteamento_leste.rotear_north_last();
					break;
					case 4:
						noc[x][y]->roteamento_leste.rotear_west_first();
					break;
					case 5:
						(x%2==0)? noc[x][y]->roteamento_leste.odd_even = 0: noc[x][y]->roteamento_leste.odd_even = 1;
						noc[x][y]->roteamento_leste.portaAnterior = LESTE;
						noc[x][y]->roteamento_leste.rotear_odd_even();					
					break;																				
				}



				if (noc[x][y]->roteamento_leste.portaDestino == LESTE)
				{
					noc[x][y]->arbitro_leste.addSolicitacao(LESTE,noc[x][y]->buffer_leste->buffer_virtual[noc[x][y]->canal_leste].front());
					noc[x][y]->arbitro_leste.setPrioridade();
				} else if (noc[x][y]->roteamento_leste.portaDestino == OESTE)
				{
					noc[x][y]->arbitro_leste.addSolicitacao(OESTE,noc[x][y]->buffer_leste->buffer_virtual[noc[x][y]->canal_leste].front());
					noc[x][y]->arbitro_leste.setPrioridade();
				} else if (noc[x][y]->roteamento_leste.portaDestino == NORTE)
				{
					noc[x][y]->arbitro_leste.addSolicitacao(NORTE,noc[x][y]->buffer_leste->buffer_virtual[noc[x][y]->canal_leste].front());
					noc[x][y]->arbitro_leste.setPrioridade();
				} else if (noc[x][y]->roteamento_leste.portaDestino == SUL)
				{
					noc[x][y]->arbitro_leste.addSolicitacao(SUL,noc[x][y]->buffer_leste->buffer_virtual[noc[x][y]->canal_leste].front());
					noc[x][y]->arbitro_leste.setPrioridade();
				}

				if (noc[x][y]->roteamento_leste.portaDestino == LOCAL)
				{
					
					// printf("Chegou pelo leste...\n");

					if (noc[x][y]->buffer_leste->buffer_virtual[noc[x][y]->canal_leste].front().end != -1)
					{
						pacotes_tg[noc[x][y]->buffer_leste->buffer_virtual[noc[x][y]->canal_leste].front().end].ciclo_final.push_back(clock);	
						cont_vetor++;
					}


					latencias[noc[x][y]->buffer_leste->buffer_virtual[noc[x][y]->canal_leste].front().id].push_back(clock - noc[x][y]->buffer_leste->buffer_virtual[noc[x][y]->canal_leste].front().inicio);


					noc[x][y]->buffer_local->din = noc[x][y]->buffer_leste->buffer_virtual[noc[x][y]->canal_leste].front();
					noc[x][y]->buffer_leste->remove(noc[x][y]->canal_leste);
					noc[x][y]->buffer_local->add(noc[x][y]->canal_leste);	

					if (noc[x][y]->buffer_leste->size[noc[x][y]->canal_leste] == 0)
					{
						ver_leste[x][y] = false;
					}									
				} else {
					if (noc[x][y]->roteamento_leste.portaDestino == LESTE)
					{
						noc[x][y+1]->cf_oeste->val = true;
						noc[x][y+1]->canal_vt = noc[x][y]->canal_leste;
						throughput[x][y]->saida_leste++;
						noc[x][y]->cf_saida_leste->out_val.write(clock);
					}
					if (noc[x][y]->roteamento_leste.portaDestino == NORTE and noc[x][y]->arbitro_leste.checkPrioridade() == NORTE)
					{


						noc[x-1][y]->cf_sul->val = true;
						noc[x-1][y]->canal_vt = noc[x][y]->canal_leste;
						noc[x][y]->cf_saida_norte->out_val.write(clock);
						noc[x][y]->buffer_norte_saida->din = noc[x][y]->buffer_leste->buffer_virtual[noc[x][y]->canal_leste].front();
						noc[x][y]->buffer_norte_saida->add(noc[x][y]->canal_leste);
						noc[x][y]->buffer_leste->remove(noc[x][y]->canal_leste);
						noc[x][y]->arbitro_leste.remSolicitacao(NORTE);
						throughput[x][y]->saida_norte++;
						if (noc[x][y]->buffer_leste->isEmpty(noc[x][y]->canal_leste) == 1)
							ver_leste[x][y] = false;						
					}
					if (noc[x][y]->roteamento_leste.portaDestino == SUL and noc[x][y]->arbitro_leste.checkPrioridade() == SUL)
					{
						
						noc[x+1][y]->cf_norte->val = true;
						noc[x+1][y]->canal_vt = noc[x][y]->canal_leste;
						noc[x][y]->cf_saida_sul->out_val.write(clock);
						noc[x][y]->buffer_sul_saida->din = noc[x][y]->buffer_leste->buffer_virtual[noc[x][y]->canal_leste].front();
						noc[x][y]->buffer_sul_saida->add(noc[x][y]->canal_leste);
						noc[x][y]->buffer_leste->remove(noc[x][y]->canal_leste);
						noc[x][y]->arbitro_leste.remSolicitacao(SUL);
						throughput[x][y]->saida_sul++;
						if (noc[x][y]->buffer_leste->isEmpty(noc[x][y]->canal_leste) == 1)
							ver_leste[x][y] = false;						
					}	
					if (noc[x][y]->roteamento_leste.portaDestino == OESTE and noc[x][y]->arbitro_leste.checkPrioridade() == OESTE)
					{

						
						noc[x][y-1]->cf_leste->val = true;
						noc[x][y-1]->canal_vt = noc[x][y]->canal_leste;
						noc[x][y]->cf_saida_oeste->out_val.write(clock);
						noc[x][y]->buffer_oeste_saida->din = noc[x][y]->buffer_leste->buffer_virtual[noc[x][y]->canal_leste].front();
						noc[x][y]->buffer_oeste_saida->add(noc[x][y]->canal_leste);
						noc[x][y]->buffer_leste->remove(noc[x][y]->canal_leste);
						noc[x][y]->arbitro_leste.remSolicitacao(LESTE);
						throughput[x][y]->saida_oeste++;
						if (noc[x][y]->buffer_leste->isEmpty(noc[x][y]->canal_leste) == 1)
							ver_leste[x][y] = false;						
					}

				}
			}




			if (ver_oeste[x][y])
			{
				noc[x][y]->roteamento_oeste.destino = noc[x][y]->buffer_oeste->buffer_virtual[noc[x][y]->canal_oeste].front().destino;
						

				switch(arquivo[2]) {
					case 1:
						noc[x][y]->roteamento_oeste.rotear_negative_first();
					break;
					case 2:
						noc[x][y]->roteamento_oeste.rotear_xy();
					break;
					case 3:
						noc[x][y]->roteamento_oeste.rotear_north_last();
					break;
					case 4:
						noc[x][y]->roteamento_oeste.rotear_west_first();
					break;
					case 5:
						(x%2==0)? noc[x][y]->roteamento_oeste.odd_even = 0: noc[x][y]->roteamento_oeste.odd_even = 1;
						noc[x][y]->roteamento_oeste.portaAnterior = OESTE;
						noc[x][y]->roteamento_oeste.rotear_odd_even();					
					break;																				
				}



				if (noc[x][y]->roteamento_oeste.portaDestino == LESTE)
				{
					noc[x][y]->arbitro_oeste.addSolicitacao(LESTE,noc[x][y]->buffer_oeste->buffer_virtual[noc[x][y]->canal_oeste].front());
					noc[x][y]->arbitro_oeste.setPrioridade();
				} else if (noc[x][y]->roteamento_oeste.portaDestino == OESTE)
				{
					noc[x][y]->arbitro_oeste.addSolicitacao(OESTE,noc[x][y]->buffer_oeste->buffer_virtual[noc[x][y]->canal_oeste].front());
					noc[x][y]->arbitro_oeste.setPrioridade();
				} else if (noc[x][y]->roteamento_oeste.portaDestino == NORTE)
				{
					noc[x][y]->arbitro_oeste.addSolicitacao(NORTE,noc[x][y]->buffer_oeste->buffer_virtual[noc[x][y]->canal_oeste].front());
					noc[x][y]->arbitro_oeste.setPrioridade();
				} else if (noc[x][y]->roteamento_oeste.portaDestino == SUL)
				{
					noc[x][y]->arbitro_oeste.addSolicitacao(SUL,noc[x][y]->buffer_oeste->buffer_virtual[noc[x][y]->canal_oeste].front());
					noc[x][y]->arbitro_oeste.setPrioridade();
				}
				if (noc[x][y]->roteamento_oeste.portaDestino == LOCAL)
				{
					
					// printf("Chegou pelo oeste...\n");


					if (noc[x][y]->buffer_oeste->buffer_virtual[noc[x][y]->canal_oeste].front().end != -1)
					{
						pacotes_tg[noc[x][y]->buffer_oeste->buffer_virtual[noc[x][y]->canal_oeste].front().end].ciclo_final.push_back(clock);
						cont_vetor++;
					}


					latencias[noc[x][y]->buffer_oeste->buffer_virtual[noc[x][y]->canal_oeste].front().id].push_back(clock - noc[x][y]->buffer_oeste->buffer_virtual[noc[x][y]->canal_oeste].front().inicio);

							
					noc[x][y]->buffer_local->din = noc[x][y]->buffer_oeste->buffer_virtual[noc[x][y]->canal_oeste].front();
					noc[x][y]->buffer_oeste->remove(noc[x][y]->canal_oeste);
					noc[x][y]->buffer_local->add(noc[x][y]->canal_oeste);	
					if (noc[x][y]->buffer_oeste->size[noc[x][y]->canal_oeste] == 0)
					{
						ver_oeste[x][y] = false;
					}									
				} else {
					if (noc[x][y]->roteamento_oeste.portaDestino == OESTE)
					{
						noc[x][y-1]->cf_leste->val = true;
						noc[x][y-1]->canal_vt = noc[x][y]->canal_oeste;
						throughput[x][y]->saida_oeste++;
						noc[x][y]->cf_saida_oeste->out_val.write(clock);
					}
					if (noc[x][y]->roteamento_oeste.portaDestino == NORTE and noc[x][y]->arbitro_oeste.checkPrioridade() == NORTE)
					{

						noc[x-1][y]->cf_sul->val = true;
						noc[x-1][y]->canal_vt = noc[x][y]->canal_oeste;
						noc[x][y]->cf_saida_norte->out_val.write(clock);
						noc[x][y]->buffer_norte_saida->din = noc[x][y]->buffer_oeste->buffer_virtual[noc[x][y]->canal_oeste].front();
						noc[x][y]->buffer_norte_saida->add(noc[x][y]->canal_oeste);
						noc[x][y]->buffer_oeste->remove(noc[x][y]->canal_oeste);
						noc[x][y]->arbitro_oeste.remSolicitacao(NORTE);
						throughput[x][y]->saida_norte++;
						if (noc[x][y]->buffer_oeste->isEmpty(noc[x][y]->canal_oeste) == 1)
							ver_oeste[x][y] = false;						
					}
					if (noc[x][y]->roteamento_oeste.portaDestino == LESTE and noc[x][y]->arbitro_oeste.checkPrioridade() == LESTE)
					{
						
						
						noc[x][y+1]->cf_oeste->val = true;
						noc[x][y+1]->canal_vt = noc[x][y]->canal_oeste;
						noc[x][y]->cf_saida_leste->out_val.write(clock);			
						noc[x][y]->buffer_leste_saida->din = noc[x][y]->buffer_oeste->buffer_virtual[noc[x][y]->canal_oeste].front();
						noc[x][y]->buffer_leste_saida->add(noc[x][y]->canal_oeste);
						noc[x][y]->buffer_oeste->remove(noc[x][y]->canal_oeste);	
						noc[x][y]->arbitro_oeste.remSolicitacao(LESTE);
						throughput[x][y]->saida_leste++;
						if (noc[x][y]->buffer_oeste->isEmpty(noc[x][y]->canal_oeste) == 1)
							ver_oeste[x][y] = false;						
					}
					if (noc[x][y]->roteamento_oeste.portaDestino == SUL and noc[x][y]->arbitro_oeste.checkPrioridade() == SUL)
					{
						
						
						noc[x+1][y]->cf_norte->val = true;
						noc[x+1][y]->canal_vt = noc[x][y]->canal_oeste;
						noc[x][y]->cf_saida_sul->out_val.write(clock);
						noc[x][y]->buffer_sul_saida->din = noc[x][y]->buffer_oeste->buffer_virtual[noc[x][y]->canal_oeste].front();
						noc[x][y]->buffer_sul_saida->add(noc[x][y]->canal_oeste);
						noc[x][y]->buffer_oeste->remove(noc[x][y]->canal_oeste);
						noc[x][y]->arbitro_oeste.remSolicitacao(SUL);
						throughput[x][y]->saida_sul++;
						if (noc[x][y]->buffer_oeste->isEmpty(noc[x][y]->canal_oeste) == 1)
							ver_oeste[x][y] = false;
					}	

				}
			}	

		}
	}
}
