#include "system.h"
void SYSTEM::comunicacao() 
{

	injeta_flits();
	sc_start();

	for (int y = 0; y < ALTURA_REDE; ++y)
	{
		for (int x = 0; x < LARGURA_REDE; ++x)
		{	


			if (rede[y][x]->cf_saida_sul->ack.read() == 1)
			{
				cout << "[" << y << "][" << x << "]"  << endl;

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
					if (rede[y+1][x]->arbitro_centralizado.portaDestino == OESTE){
						rede[y+1][x]->cf_saida_oeste->val.write(1);
						rede[y+1][x]->buffer_oeste->din =  rede[y][x]->buffer_sul->din;

					}
					if (rede[y+1][x]->arbitro_centralizado.portaDestino == LESTE){
						rede[y+1][x]->cf_saida_leste->val.write(1);
						rede[y+1][x]->buffer_leste->din =  rede[y][x]->buffer_sul->din;

					}
					if (rede[y+1][x]->arbitro_centralizado.portaDestino == SUL){
						rede[y+1][x]->cf_saida_sul->val.write(1);
						rede[y+1][x]->buffer_sul->din =  rede[y][x]->buffer_sul->din;

					}
				}
				rede[y][x]->ack_cf_sul_to_norte_wire = 0;							
			}

			if (rede[y][x]->cf_saida_leste->ack.read() == 1)
			{
				
				cout << "[" << y << "][" << x << "]"  << endl;

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
					if (rede[y][x+1]->arbitro_centralizado.portaDestino == NORTE){
						rede[y][x+1]->cf_saida_norte->val.write(1);
						rede[y][x+1]->buffer_norte->din =  rede[y][x]->buffer_leste->din;
					}
					if (rede[y][x+1]->arbitro_centralizado.portaDestino == LESTE){
						rede[y][x+1]->cf_saida_leste->val.write(1);
						rede[y][x+1]->buffer_leste->din =  rede[y][x]->buffer_leste->din;
					} 				
					if (rede[y][x+1]->arbitro_centralizado.portaDestino == SUL){
						rede[y][x+1]->cf_saida_sul->val.write(1);
						rede[y][x+1]->buffer_sul->din =  rede[y][x]->buffer_leste->din;
					}
				}		
				rede[y][x]->ack_cf_leste_to_oeste_wire = 0;	
			}

			if (rede[y][x]->cf_saida_oeste->ack.read() == 1)
			{
			
				cout << "[" << y << "][" << x << "]"  << endl;

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
					if (rede[y][x-1]->arbitro_centralizado.portaDestino == NORTE){
						rede[y][x-1]->cf_saida_norte->val.write(1);
						rede[y][x-1]->buffer_norte->din =  rede[y][x]->buffer_oeste->din;

					}
					if (rede[y][x-1]->arbitro_centralizado.portaDestino == OESTE){
						rede[y][x-1]->cf_saida_oeste->val.write(1);
						rede[y][x-1]->buffer_oeste->din =  rede[y][x]->buffer_oeste->din;

					}
					if (rede[y][x-1]->arbitro_centralizado.portaDestino == SUL){
						rede[y][x-1]->cf_saida_sul->val.write(1);
						rede[y][x-1]->buffer_sul->din =  rede[y][x]->buffer_oeste->din;

					}
				}	
				rede[y][x]->ack_cf_oeste_to_leste_wire = 0;
			}

			if (rede[y][x]->cf_saida_norte->ack.read() == 1)
			{
	
				cout << "[" << y << "][" << x << "]"  << endl;

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
					if (rede[y-1][x]->arbitro_centralizado.portaDestino == OESTE){
						rede[y-1][x]->cf_saida_oeste->val.write(1);
						rede[y-1][x]->buffer_oeste->din =  rede[y][x]->buffer_norte->din;

					}
					if (rede[y-1][x]->arbitro_centralizado.portaDestino == LESTE){
						rede[y-1][x]->cf_saida_leste->val.write(1);
						rede[y-1][x]->buffer_leste->din =  rede[y][x]->buffer_norte->din;
					}
					if (rede[y-1][x]->arbitro_centralizado.portaDestino == NORTE){
						rede[y-1][x]->cf_saida_norte->val.write(1);
						rede[y-1][x]->buffer_norte->din =  rede[y][x]->buffer_norte->din;
					}
				}
				rede[y][x]->ack_cf_norte_to_sul_wire = 0;
			}			
		}
	}		
}

void SYSTEM::injeta_flits() {
	Flit flit[3];
	flit[0].cordenadas_f.x = 0;
	flit[0].cordenadas_f.y = 0;
	flit[1].cordenadas_f.x = 0;
	flit[1].cordenadas_f.y = 1;
	flit[2].cordenadas_f.x = 0;
	flit[2].cordenadas_f.y = 0;

	//Setando as cordenadas do primeiro flit
	rede[4][4]->roteamento_oeste.cordenada_destino.x =  flit[0].cordenadas_f.x;
	rede[4][4]->roteamento_oeste.cordenada_destino.y =  flit[0].cordenadas_f.y;
	//Alocando o flit no buffer
	rede[4][4]->buffer_oeste->din =  flit[0];
	//Roteando
	rede[4][4]->roteamento_oeste.rotear_xy();
	//Recebendo na porta destino do arbitro 
	rede[4][4]->arbitro_centralizado.portaDestino = rede[4][4]->roteamento_oeste.portaDestino;
	//Colocando no buffer circular
	rede[4][4]->arbitro_centralizado.setPrioridade();

	rede[4][4]->cf_saida_oeste->val.write(1);

	//Setando as cordenadas do primeiro flit
	rede[0][4]->roteamento_oeste.cordenada_destino.x =  flit[1].cordenadas_f.x;
	rede[0][4]->roteamento_oeste.cordenada_destino.y =  flit[1].cordenadas_f.y;
	//Alocando o flit no buffer
	rede[0][4]->buffer_oeste->din =  flit[1];
	//Roteando
	rede[0][4]->roteamento_oeste.rotear_xy();
	//Recebendo na porta destino do arbitro 
	rede[0][4]->arbitro_centralizado.portaDestino = rede[0][4]->roteamento_oeste.portaDestino;
	//Colocando no buffer circular
	rede[0][4]->arbitro_centralizado.setPrioridade();

	rede[0][4]->cf_saida_oeste->val.write(1);


}
