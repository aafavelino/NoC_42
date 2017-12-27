#include "system.h"


void REDE::comunicacao_externa() 
{
	for (int y = 0; y < ALTURA_REDE; y++)
	{
		for (int x = 0; x < LARGURA_REDE; x++)
		{
			if (rede[y][x]->cf_saida_norte->out_ack.read())
			{
				printf("[%d][%d]--NORTE\n",y,x);
				rede[y][x]->cf_saida_norte->out_val.write(0);

				rede[y-1][x]->buffer_sul->din = rede[y][x]->buffer_norte->flits.front();
				rede[y-1][x]->buffer_sul->add();
				rede[y][x]->buffer_norte->remove();
				//Setando as cordenadas
				rede[y-1][x]->roteamento_sul.cordenada_destino.x = rede[y-1][x]->buffer_sul->din.cordenadas_f.x;
				rede[y-1][x]->roteamento_sul.cordenada_destino.y = rede[y-1][x]->buffer_sul->din.cordenadas_f.y;
				rede[y-1][x]->roteamento_sul.rotear_xy();

				if (rede[y-1][x]->roteamento_sul.portaDestino == OESTE)
				{
					rede[y-1][x]->arbitro_sul.addSolicitacao(OESTE);
					rede[y-1][x]->arbitro_sul.setPrioridade();
				} else if (rede[y-1][x]->roteamento_sul.portaDestino == LESTE)
				{
					rede[y-1][x]->arbitro_sul.addSolicitacao(LESTE);
					rede[y-1][x]->arbitro_sul.setPrioridade();
				} else if (rede[y-1][x]->roteamento_sul.portaDestino == NORTE)
				{
					rede[y-1][x]->arbitro_sul.addSolicitacao(NORTE);
					rede[y-1][x]->arbitro_sul.setPrioridade();
				}

				if ((rede[y-1][x]->roteamento_sul.cordenada.x == rede[y-1][x]->buffer_sul->din.cordenadas_f.x) and (rede[y-1][x]->roteamento_sul.cordenada.y == rede[y-1][x]->buffer_sul->din.cordenadas_f.y))
				{
					printf("CHEGOUUUUU...\n");
					rede[y-1][x]->buffer_local->din = rede[y-1][x]->buffer_sul->flits.front();
					rede[y-1][x]->buffer_sul->remove();
					rede[y-1][x]->buffer_local->add();
				} else {
					// Se chegou aqui, quem escreve? quem tem prioridade?
					if ((rede[y-1][x]->roteamento_sul.portaDestino == OESTE) and rede[y-1][x]->arbitro_sul.checkPrioridade() == OESTE)
					{
						rede[y-1][x]->cf_saida_oeste->out_val.write(1);
						rede[y-1][x]->buffer_oeste->din = rede[y-1][x]->buffer_sul->flits.front();
						rede[y-1][x]->buffer_oeste->add();
						rede[y-1][x]->buffer_sul->remove();
						rede[y-1][x]->arbitro_sul.remSolicitacao(OESTE);
					}
					if ((rede[y-1][x]->roteamento_sul.portaDestino == LESTE) and rede[y-1][x]->arbitro_sul.checkPrioridade() == LESTE)
					{
						rede[y-1][x]->cf_saida_leste->out_val.write(1);
						rede[y-1][x]->buffer_leste->din = rede[y-1][x]->buffer_sul->flits.front();
						rede[y-1][x]->buffer_leste->add();
						rede[y-1][x]->buffer_sul->remove();
						rede[y-1][x]->arbitro_sul.remSolicitacao(LESTE);
					}
					if ((rede[y-1][x]->roteamento_sul.portaDestino == NORTE) and rede[y-1][x]->arbitro_sul.checkPrioridade() == NORTE)
					{
						rede[y-1][x]->cf_saida_norte->out_val.write(1);
						rede[y-1][x]->buffer_norte->din = rede[y-1][x]->buffer_sul->flits.front();
						rede[y-1][x]->buffer_norte->add();
						rede[y-1][x]->buffer_sul->remove();
						rede[y-1][x]->arbitro_sul.remSolicitacao(NORTE);
					}				
				}
				rede[y][x]->ack_cf_norte_to_sul_wire = 0;
			}



			if (rede[y][x]->cf_saida_sul->out_ack.read())
			{
				printf("[%d][%d]--SUL\n",y,x);
				cout << rede[3][1]->cf_saida_leste->out_ack.read() << endl;
				rede[y][x]->cf_saida_sul->out_val.write(0);

				rede[y+1][x]->buffer_norte->din = rede[y][x]->buffer_sul->flits.front();
				rede[y+1][x]->buffer_norte->add();
				rede[y][x]->buffer_sul->remove();
				//Setando as cordenadas
				rede[y+1][x]->roteamento_norte.cordenada_destino.x = rede[y+1][x]->buffer_norte->din.cordenadas_f.x;
				rede[y+1][x]->roteamento_norte.cordenada_destino.y = rede[y+1][x]->buffer_norte->din.cordenadas_f.y;
				rede[y+1][x]->roteamento_norte.rotear_xy();

				if (rede[y+1][x]->roteamento_norte.portaDestino == OESTE)
				{
					rede[y+1][x]->arbitro_norte.addSolicitacao(OESTE);
					rede[y+1][x]->arbitro_norte.setPrioridade();
				} else if (rede[y+1][x]->roteamento_norte.portaDestino == LESTE)
				{
					rede[y+1][x]->arbitro_norte.addSolicitacao(LESTE);
					rede[y+1][x]->arbitro_norte.setPrioridade();
				} else if (rede[y+1][x]->roteamento_norte.portaDestino == SUL)
				{
					rede[y+1][x]->arbitro_norte.addSolicitacao(SUL);
					rede[y+1][x]->arbitro_norte.setPrioridade();
				}

				if ((rede[y+1][x]->roteamento_norte.cordenada.x == rede[y+1][x]->buffer_norte->din.cordenadas_f.x) and (rede[y+1][x]->roteamento_norte.cordenada.y == rede[y+1][x]->buffer_norte->din.cordenadas_f.y))
				{
					printf("CHEGOUUUUU...\n");
					rede[y+1][x]->buffer_local->din = rede[y+1][x]->buffer_norte->flits.front();
					rede[y+1][x]->buffer_norte->remove();
					rede[y+1][x]->buffer_local->add();
					// sc_stop();
				} else {
					if ((rede[y+1][x]->roteamento_norte.portaDestino == OESTE) and rede[y+1][x]->arbitro_norte.checkPrioridade() == OESTE)
					{
						rede[y+1][x]->cf_saida_oeste->out_val.write(1);
						rede[y+1][x]->buffer_oeste->din = rede[y+1][x]->buffer_norte->flits.front();
						rede[y+1][x]->buffer_oeste->add();
						rede[y+1][x]->buffer_norte->remove();
						rede[y+1][x]->arbitro_norte.remSolicitacao(OESTE);
					}
					if ((rede[y+1][x]->roteamento_norte.portaDestino == LESTE) and rede[y+1][x]->arbitro_norte.checkPrioridade() == LESTE)
					{
						rede[y+1][x]->cf_saida_leste->out_val.write(1);
						rede[y+1][x]->buffer_leste->din = rede[y+1][x]->buffer_norte->flits.front();
						rede[y+1][x]->buffer_leste->add();
						rede[y+1][x]->buffer_norte->remove();
						rede[y+1][x]->arbitro_norte.remSolicitacao(LESTE);
					}
					if ((rede[y+1][x]->roteamento_norte.portaDestino == SUL) and rede[y+1][x]->arbitro_norte.checkPrioridade() == SUL)
					{
						rede[y+1][x]->cf_saida_sul->out_val.write(1);
						rede[y+1][x]->buffer_sul->din = rede[y+1][x]->buffer_norte->flits.front();
						rede[y+1][x]->buffer_sul->add();
						rede[y+1][x]->buffer_norte->remove();
						rede[y+1][x]->arbitro_norte.remSolicitacao(SUL);
					}				
				}					
				rede[y][x]->ack_cf_sul_to_norte_wire = 0;
			}



			if (rede[y][x]->cf_saida_leste->out_ack.read())
			{
				// cout << "Y= " << y << "X= " << x << " cf_saida_leste->out_ack.read()==  " << rede[y][x]->cf_saida_leste->out_ack.read() << endl;
				printf("[%d][%d]--LESTE\n",y,x);
				rede[y][x]->cf_saida_leste->out_val.write(0);

				// cout << rede[3][1]->cf_saida_leste->out_ack.read() << endl;

				
				rede[y][x+1]->buffer_oeste->din = rede[y][x]->buffer_leste->flits.front();
				rede[y][x]->buffer_leste->remove();
				rede[y][x+1]->buffer_oeste->add();
				//Setando as cordenadas
				rede[y][x+1]->roteamento_oeste.cordenada_destino.x = rede[y][x+1]->buffer_oeste->din.cordenadas_f.x;
				rede[y][x+1]->roteamento_oeste.cordenada_destino.y = rede[y][x+1]->buffer_oeste->din.cordenadas_f.y;
				rede[y][x+1]->roteamento_oeste.rotear_xy();

				if (rede[y][x+1]->roteamento_oeste.portaDestino == LESTE)
				{
					rede[y][x+1]->arbitro_oeste.addSolicitacao(LESTE);
					rede[y][x+1]->arbitro_oeste.setPrioridade();
				} else if (rede[y][x+1]->roteamento_oeste.portaDestino == SUL)
				{
					rede[y][x+1]->arbitro_oeste.addSolicitacao(SUL);
					rede[y][x+1]->arbitro_oeste.setPrioridade();
				} else if (rede[y][x+1]->roteamento_oeste.portaDestino == NORTE)
				{
					rede[y][x+1]->arbitro_oeste.addSolicitacao(NORTE);
					rede[y][x+1]->arbitro_oeste.setPrioridade();
				}

				if ((rede[y][x+1]->roteamento_oeste.cordenada.x == rede[y][x+1]->buffer_oeste->din.cordenadas_f.x) and (rede[y][x+1]->roteamento_oeste.cordenada.y == rede[y][x+1]->buffer_oeste->din.cordenadas_f.y))
				{
					if (rede[y][x+1]->buffer_local->size < 4)
					{
						printf("CHEGOUUUUU...\n");
						rede[y][x+1]->buffer_local->din = rede[y][x+1]->buffer_oeste->flits.front();
						rede[y][x+1]->buffer_oeste->remove();
						rede[y][x+1]->buffer_local->add();
					} else
					{
						// printf("buffer cheio\n");
					}

				} else {
					if ((rede[y][x+1]->roteamento_oeste.portaDestino == NORTE) and rede[y][x+1]->arbitro_oeste.checkPrioridade() == NORTE)
					{
						rede[y][x+1]->cf_saida_norte->out_val.write(1);
						rede[y][x+1]->buffer_norte->din = rede[y][x+1]->buffer_oeste->flits.front();
						rede[y][x+1]->buffer_norte->add();
						rede[y][x+1]->buffer_oeste->remove();
						rede[y][x+1]->arbitro_oeste.remSolicitacao(NORTE);
					}
					if ((rede[y][x+1]->roteamento_oeste.portaDestino == LESTE) and rede[y][x+1]->arbitro_oeste.checkPrioridade() == LESTE)
					{
						// cout << "OPA" << endl;
						rede[y][x+1]->cf_saida_leste->out_val.write(1);
						rede[y][x+1]->buffer_leste->din = rede[y][x+1]->buffer_oeste->flits.front();
						rede[y][x+1]->buffer_leste->add();
						rede[y][x+1]->buffer_oeste->remove();
						rede[y][x+1]->arbitro_oeste.remSolicitacao(LESTE);
					}
					if ((rede[y][x+1]->roteamento_oeste.portaDestino == SUL) and rede[y][x+1]->arbitro_oeste.checkPrioridade() == SUL)
					{
						rede[y][x+1]->cf_saida_sul->out_val.write(1);
						rede[y][x+1]->buffer_sul->din = rede[y][x+1]->buffer_oeste->flits.front();
						rede[y][x+1]->buffer_sul->add();
						rede[y][x+1]->buffer_oeste->remove();
						rede[y][x+1]->arbitro_oeste.remSolicitacao(SUL);
					}				
				}					
				cout << "Teste " << endl;
				rede[y][x]->ack_cf_leste_to_oeste_wire = 0;


			}

			if (rede[y][x]->cf_saida_oeste->out_ack.read())
			{
				printf("[%d][%d]--OESTE\n",y,x);
				rede[y][x]->cf_saida_oeste->out_val.write(0);

				rede[y][x-1]->buffer_leste->din = rede[y][x]->buffer_oeste->flits.front();
				rede[y][x-1]->buffer_leste->add();
				rede[y][x]->buffer_oeste->remove();
				//Setando as cordenadas
				rede[y][x-1]->roteamento_leste.cordenada_destino.x = rede[y][x-1]->buffer_leste->din.cordenadas_f.x;
				rede[y][x-1]->roteamento_leste.cordenada_destino.y = rede[y][x-1]->buffer_leste->din.cordenadas_f.y;
				rede[y][x-1]->roteamento_leste.rotear_xy();


				if (rede[y][x-1]->roteamento_leste.portaDestino == OESTE)
				{
					rede[y][x-1]->arbitro_leste.addSolicitacao(OESTE);
					rede[y][x-1]->arbitro_leste.setPrioridade();
				} else if (rede[y][x-1]->roteamento_leste.portaDestino == NORTE)
				{
					rede[y][x-1]->arbitro_leste.addSolicitacao(NORTE);
					rede[y][x-1]->arbitro_leste.setPrioridade();
				} else if (rede[y][x-1]->roteamento_leste.portaDestino == SUL)
				{
					rede[y][x-1]->arbitro_leste.addSolicitacao(SUL);
					rede[y][x-1]->arbitro_leste.setPrioridade();
				}

				if ((rede[y][x-1]->roteamento_leste.cordenada.x == rede[y][x-1]->buffer_leste->din.cordenadas_f.x) and (rede[y][x-1]->roteamento_leste.cordenada.y == rede[y][x-1]->buffer_leste->din.cordenadas_f.y))
				{
					printf("CHEGOUUUUU...\n");
					rede[y][x-1]->buffer_local->din = rede[y][x-1]->buffer_leste->flits.front();
					rede[y][x-1]->buffer_leste->remove();
					rede[y][x-1]->buffer_local->add();
				} else {
					if ((rede[y][x-1]->roteamento_leste.portaDestino == NORTE) and rede[y][x-1]->arbitro_leste.checkPrioridade() == NORTE)
					{
						rede[y][x-1]->cf_saida_norte->out_val.write(1);
						rede[y][x-1]->buffer_norte->din = rede[y][x-1]->buffer_leste->flits.front();
						rede[y][x-1]->buffer_norte->add();
						rede[y][x-1]->buffer_leste->remove();
						rede[y][x-1]->arbitro_leste.remSolicitacao(NORTE);
					}
					if ((rede[y][x-1]->roteamento_leste.portaDestino == OESTE) and rede[y][x-1]->arbitro_leste.checkPrioridade() == OESTE)
					{
						rede[y][x-1]->cf_saida_oeste->out_val.write(1);
						rede[y][x-1]->buffer_oeste->din = rede[y][x-1]->buffer_leste->flits.front();
						rede[y][x-1]->buffer_oeste->add();
						rede[y][x-1]->buffer_leste->remove();
						rede[y][x-1]->arbitro_leste.remSolicitacao(OESTE);
					}
					if ((rede[y][x-1]->roteamento_leste.portaDestino == SUL)  and rede[y][x-1]->arbitro_leste.checkPrioridade() == SUL)
					{
						rede[y][x-1]->cf_saida_sul->out_val.write(1);
						rede[y][x-1]->buffer_sul->din = rede[y][x-1]->buffer_leste->flits.front();
						rede[y][x-1]->buffer_sul->add();
						rede[y][x-1]->buffer_leste->remove();
						rede[y][x-1]->arbitro_leste.remSolicitacao(SUL);
					}				
				}		
				rede[y][x]->ack_cf_oeste_to_leste_wire = 0;
			}		
		}
	}
}
int xyz = 0;
// 1º Local xy -> 2º Destino xy
void REDE::injeta_flits(int local_y , int local_x, int x, int y) {

	if (xyz < 5)
	{

	Pacote *pct = new Pacote(x,y,1);

	//Alocando o flit no buffer
	rede[local_y][local_x]->buffer_local->din =  pct->v[0];

	//Setando as cordenadas do primeiro flit
	rede[local_y][local_x]->roteamento_local.cordenada_destino.x =   pct->v[0].cordenadas_f.x;
	rede[local_y][local_x]->roteamento_local.cordenada_destino.y =   pct->v[0].cordenadas_f.y;
	
	//Roteando
	rede[local_y][local_x]->roteamento_local.rotear_xy();


	if (rede[local_y][local_x]->roteamento_local.portaDestino == NORTE)
	{
		rede[local_y][local_x]->arbitro_norte.addSolicitacao(NORTE);
		rede[local_y][local_x]->arbitro_norte.setPrioridade();
		rede[local_y][local_x]->roteamento_norte.cordenada_destino.x =   pct->v[0].cordenadas_f.x;
		rede[local_y][local_x]->roteamento_norte.cordenada_destino.y =   pct->v[0].cordenadas_f.y;	
		rede[local_y][local_x]->buffer_norte->din =  pct->v[0];
		rede[local_y][local_x]->buffer_norte->add();
		rede[local_y][local_x]->cf_saida_norte->out_val.write(1);
		cout << "NORTE" << endl;
	} else if (rede[local_y][local_x]->roteamento_local.portaDestino == SUL)
	{
		rede[local_y][local_x]->arbitro_sul.addSolicitacao(SUL);
		rede[local_y][local_x]->arbitro_sul.setPrioridade();
		rede[local_y][local_x]->roteamento_sul.cordenada_destino.x =   pct->v[0].cordenadas_f.x;
		rede[local_y][local_x]->roteamento_sul.cordenada_destino.y =   pct->v[0].cordenadas_f.y;	
		rede[local_y][local_x]->buffer_sul->din =  pct->v[0];
		rede[local_y][local_x]->buffer_sul->add();
		rede[local_y][local_x]->cf_saida_sul->out_val.write(1);
		cout << "SUL" << endl;
	} else if (rede[local_y][local_x]->roteamento_local.portaDestino == LESTE)
	{
		rede[local_y][local_x]->arbitro_leste.addSolicitacao(LESTE);
		rede[local_y][local_x]->arbitro_leste.setPrioridade();
		rede[local_y][local_x]->roteamento_leste.cordenada_destino.x =   pct->v[0].cordenadas_f.x;
		rede[local_y][local_x]->roteamento_leste.cordenada_destino.y =   pct->v[0].cordenadas_f.y;	
		rede[local_y][local_x]->buffer_leste->din =  pct->v[0];
		rede[local_y][local_x]->buffer_leste->add();
		rede[local_y][local_x]->cf_saida_leste->out_val.write(1);
		cout << "LESTE" << endl;
	} else if (rede[local_y][local_x]->roteamento_local.portaDestino == OESTE)
	{	
		rede[local_y][local_x]->arbitro_oeste.addSolicitacao(OESTE);
		rede[local_y][local_x]->arbitro_oeste.setPrioridade();
		rede[local_y][local_x]->roteamento_oeste.cordenada_destino.x =   pct->v[0].cordenadas_f.x;
		rede[local_y][local_x]->roteamento_oeste.cordenada_destino.y =   pct->v[0].cordenadas_f.y;	
		rede[local_y][local_x]->buffer_oeste->din =  pct->v[0];
		rede[local_y][local_x]->buffer_oeste->add();
		rede[local_y][local_x]->cf_saida_oeste->out_val.write(1);
		cout << "OESTE" << endl;
	} else {
		printf("CHEGOUUUUU...\n");
		rede[local_y][local_x]->buffer_local->din =	 pct->v[0];
		rede[local_y][local_x]->buffer_local->add();
	} 
		//xyz++;
	}

}