#include "system.h"
void SYSTEM::comunicacao() 
{

	injeta_flits(1, 0,10);
	sc_start();

}

void SYSTEM::injeta_flits(int x, int y, int quantidade) {
	Flit flit[3];
	flit[0].cordenadas_f.x = x;
	flit[0].cordenadas_f.y = y;
	

	//Setando as cordenadas do primeiro flit
	rede[4][4]->roteamento_local.cordenada_destino.x =  flit[0].cordenadas_f.x;
	rede[4][4]->roteamento_local.cordenada_destino.y =  flit[0].cordenadas_f.y;
	//Alocando o flit no buffer
	rede[4][4]->buffer_local->din =  flit[0];
	//Roteando
	rede[4][4]->roteamento_local.rotear_xy();

	//Colocando no buffer circular
	rede[4][4]->arbitro_centralizado.setPrioridade();


	if (rede[4][4]->roteamento_local.portaDestino == NORTE)
	{
		rede[4][4]->cf_saida_norte->val.write(1);
	} else if (rede[4][4]->roteamento_local.portaDestino == SUL)
	{
		rede[4][4]->cf_saida_sul->val.write(1);
	} else if (rede[4][4]->roteamento_local.portaDestino == LESTE)
	{
		rede[4][4]->cf_saida_leste->val.write(1);
	} else if (rede[4][4]->roteamento_local.portaDestino == OESTE)
	{
		rede[4][4]->cf_saida_oeste->val.write(1);
	}
}
