#include "system.h"

void SYSTEM::comunicacao() 
{


	Flit flit[1];
	flit[0].cordenadas_f.x = 1;
	flit[0].cordenadas_f.y = 1;

	//Setando as cordenadas do primeiro flit
	rede[0][0]->roteamento_leste.cordenada_destino.x =  flit[0].cordenadas_f.x;
	rede[0][0]->roteamento_leste.cordenada_destino.y =  flit[0].cordenadas_f.y;
	//Alocando o flit no buffer
	rede[0][0]->buffer_leste->din =  flit[0];
	//Roteando
	rede[0][0]->roteamento_leste.rotear_xy();
	//Recebendo na porta destino do arbitro 
	rede[0][0]->arbitro_centralizado.portaDestino = rede[0][0]->roteamento_norte.portaDestino;
	//Colocando no buffer circular
	rede[0][0]->arbitro_centralizado.setPrioridade();

	rede[0][0]->cf_saida_leste->val.write(1);

	sc_start();

	for (int y = 0; y < ALTURA_REDE; ++y)
	{
		for (int x = 0; x < LARGURA_REDE; ++x)
		{	

			if (rede[y][x]->cf_saida_norte->ack.read() == 1)
			{
				rede[y-1][x]->buffer_sul->din = rede[y][x]->buffer_norte->din;
				rede[y-1][x]->buffer_sul->add();
				rede[y-1][x]->roteamento_sul.cordenada_destino.x = rede[y-1][x]->buffer_sul->din.cordenadas_f.x;
				rede[y-1][x]->roteamento_sul.cordenada_destino.y = rede[y-1][x]->buffer_sul->din.cordenadas_f.y;
				
				rede[y-1][x]->roteamento_sul.rotear_xy();

				rede[y-1][x]->arbitro_centralizado.portaDestino = rede[y-1][x]->roteamento_sul.portaDestino;
				rede[y-1][x]->arbitro_centralizado.setPrioridade();

				if ((rede[y-1][x]->roteamento_sul.cordenada.x == rede[y-1][x]->buffer_sul->din.cordenadas_f.x) and (rede[y-1][x]->roteamento_sul.cordenada.y == rede[y-1][x]->buffer_sul->din.cordenadas_f.y))
				{
					std::cout << ">>> Chegou..." << std::endl;
					rede[y-1][x]->buffer_local->din = rede[y-1][x]->buffer_sul->flits.front();
					rede[y-1][x]->buffer_sul->remove();
					rede[y-1][x]->buffer_local->add();
				} else {
					if (rede[y-1][x]->arbitro_centralizado.portaDestino == WEST)
						rede[y-1][x]->cf_saida_oeste->val.write(1);
					if (rede[y-1][x]->arbitro_centralizado.portaDestino == EAST)
						rede[y-1][x]->cf_saida_leste->val.write(1);
					if (rede[y-1][x]->arbitro_centralizado.portaDestino == NORTH)
						rede[y-1][x]->cf_saida_norte->val.write(1);

					if (sc_pending_activity())
						sc_start();

				}
			}

			if (rede[y][x]->cf_saida_sul->ack.read() == 1)
			{
				rede[y+1][x]->buffer_norte->din = rede[y][x]->buffer_sul->din;
				rede[y+1][x]->buffer_norte->add();
				rede[y+1][x]->roteamento_norte.cordenada_destino.x = rede[y+1][x]->buffer_norte->din.cordenadas_f.x;
				rede[y+1][x]->roteamento_norte.cordenada_destino.y = rede[y+1][x]->buffer_norte->din.cordenadas_f.y;
				
				rede[y+1][x]->roteamento_norte.rotear_xy();

				rede[y+1][x]->arbitro_centralizado.portaDestino = rede[y+1][x]->roteamento_norte.portaDestino;
				rede[y+1][x]->arbitro_centralizado.setPrioridade();

				if ((rede[y+1][x]->roteamento_norte.cordenada.x == rede[y+1][x]->buffer_norte->din.cordenadas_f.x) and (rede[y+1][x]->roteamento_norte.cordenada.y == rede[y+1][x]->buffer_norte->din.cordenadas_f.y))
				{
					std::cout << ">>> Chegou..." << std::endl;
					rede[y+1][x]->buffer_local->din = rede[y+1][x]->buffer_norte->flits.front();
					rede[y+1][x]->buffer_norte->remove();
					rede[y+1][x]->buffer_local->add();
				} else {
					if (rede[y+1][x]->arbitro_centralizado.portaDestino == WEST)
						rede[y+1][x]->cf_saida_oeste->val.write(1);
					if (rede[y+1][x]->arbitro_centralizado.portaDestino == EAST)
						rede[y+1][x]->cf_saida_leste->val.write(1);
					if (rede[y+1][x]->arbitro_centralizado.portaDestino == SOUTH)
						rede[y+1][x]->cf_saida_sul->val.write(1);

					if (sc_pending_activity())
						sc_start();

				}				
			}

			if (rede[y][x]->cf_saida_leste->ack.read() == 1)
			{
				rede[y][x+1]->buffer_oeste->din = rede[y][x]->buffer_leste->din;
				rede[y][x+1]->buffer_oeste->add();
				rede[y][x+1]->roteamento_oeste.cordenada_destino.x = rede[y][x+1]->buffer_oeste->din.cordenadas_f.x;
				rede[y][x+1]->roteamento_oeste.cordenada_destino.y = rede[y][x+1]->buffer_oeste->din.cordenadas_f.y;
				
				rede[y][x+1]->roteamento_oeste.rotear_xy();

				rede[y][x+1]->arbitro_centralizado.portaDestino = rede[y][x+1]->roteamento_oeste.portaDestino;
				rede[y][x+1]->arbitro_centralizado.setPrioridade();

				if ((rede[y][x+1]->roteamento_oeste.cordenada.x == rede[y][x+1]->buffer_oeste->din.cordenadas_f.x) and (rede[y][x+1]->roteamento_oeste.cordenada.y == rede[y][x+1]->buffer_oeste->din.cordenadas_f.y))
				{
					std::cout << ">>> Chegou..." << std::endl;
					rede[y][x+1]->buffer_local->din = rede[y][x+1]->buffer_oeste->flits.front();
					rede[y][x+1]->buffer_oeste->remove();
					rede[y][x+1]->buffer_local->add();
				} else {
					if (rede[y][x+1]->arbitro_centralizado.portaDestino == NORTH)
						rede[y][x+1]->cf_saida_norte->val.write(1);
					if (rede[y][x+1]->arbitro_centralizado.portaDestino == EAST)
						rede[y][x+1]->cf_saida_leste->val.write(1);
					if (rede[y][x+1]->arbitro_centralizado.portaDestino == SOUTH)
						rede[y][x+1]->cf_saida_sul->val.write(1);

					if (sc_pending_activity())
						sc_start();

				}				
			}

			if (rede[y][x]->cf_saida_oeste->ack.read() == 1)
			{
				rede[y][x-1]->buffer_leste->din = rede[y][x]->buffer_oeste->din;
				rede[y][x-1]->buffer_leste->add();
				rede[y][x-1]->roteamento_leste.cordenada_destino.x = rede[y][x-1]->buffer_leste->din.cordenadas_f.x;
				rede[y][x-1]->roteamento_leste.cordenada_destino.y = rede[y][x-1]->buffer_leste->din.cordenadas_f.y;
				
				rede[y][x-1]->roteamento_leste.rotear_xy();

				rede[y][x-1]->arbitro_centralizado.portaDestino = rede[y][x-1]->roteamento_leste.portaDestino;
				rede[y][x-1]->arbitro_centralizado.setPrioridade();

				if ((rede[y][x-1]->roteamento_leste.cordenada.x == rede[y][x-1]->buffer_leste->din.cordenadas_f.x) and (rede[y][x-1]->roteamento_leste.cordenada.y == rede[y][x-1]->buffer_leste->din.cordenadas_f.y))
				{
					std::cout << ">>> Chegou..." << std::endl;
					rede[y][x-1]->buffer_local->din = rede[y][x-1]->buffer_leste->flits.front();
					rede[y][x-1]->buffer_leste->remove();
					rede[y][x-1]->buffer_local->add();
				} else {
					if (rede[y][x-1]->arbitro_centralizado.portaDestino == NORTH)
						rede[y][x-1]->cf_saida_norte->val.write(1);
					if (rede[y][x-1]->arbitro_centralizado.portaDestino == WEST)
						rede[y][x-1]->cf_saida_oeste->val.write(1);
					if (rede[y][x-1]->arbitro_centralizado.portaDestino == SOUTH)
						rede[y][x-1]->cf_saida_sul->val.write(1);

					if (sc_pending_activity())
						sc_start();

				}					

			}

		}
	}
}
