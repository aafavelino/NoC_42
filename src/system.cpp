#include "system.h"


void REDE::comunicacao() 
{
	
	if( sc_pending_activity() )
	sc_start();
	cout << "entrou" << endl;
	for (int y = 0; y < ALTURA_REDE; y++)
	{
		for (int x = 0; x < LARGURA_REDE; x++)
		{
			if (rede[y][x]->cf_saida_norte->out_ack.read())
			{
				/* code */
			}
			if (rede[y][x]->cf_saida_sul->out_ack.read())
			{
				
				cout << "Teste "<< rede[y][x]->cf_saida_sul->out_ack.read() << endl;
				rede[y+1][x]->cf_norte->in_ack.write(0);
					if( sc_pending_activity() )
						sc_start();

			}
			if (rede[y][x]->cf_saida_leste->out_ack.read())
			{
				
			}
			if (rede[y][x]->cf_saida_oeste->out_ack.read())
			{
				/* code */
			}

			
		}
	}
}

// 1º Local xy -> 2º Destino xy
void REDE::injeta_flits(int local_y , int local_x, int x, int y) {


	Pacote *pct = new Pacote(x,y,1);


	//Alocando o flit no buffer
	rede[local_y][local_x]->buffer_local->din =  pct->v[0];

	//Setando as cordenadas do primeiro flit
	rede[local_y][local_x]->roteamento_local.cordenada_destino.x =   pct->v[0].cordenadas_f.x;
	rede[local_y][local_x]->roteamento_local.cordenada_destino.y =   pct->v[0].cordenadas_f.y;
	
	//Roteando
	rede[local_y][local_x]->roteamento_local.rotear_xy();

	// rede[local_y][local_x]->arbitro_centralizado.addSolicitacao(rede[local_y][local_x]->roteamento_local.portaDestino);


	if (rede[local_y][local_x]->roteamento_local.portaDestino == NORTE)
	{
		rede[local_y][local_x]->cf_saida_norte->out_val.write(1);
		rede[local_y][local_x]->roteamento_norte.cordenada_destino.x =   pct->v[0].cordenadas_f.x;
		rede[local_y][local_x]->roteamento_norte.cordenada_destino.y =   pct->v[0].cordenadas_f.y;	
		rede[local_y][local_x]->buffer_norte->din =  pct->v[0];

		cout << "NORTE" << endl;
	} else if (rede[local_y][local_x]->roteamento_local.portaDestino == SUL)
	{
		rede[local_y][local_x]->cf_saida_sul->out_val.write(1);
		rede[local_y][local_x]->roteamento_sul.cordenada_destino.x =   pct->v[0].cordenadas_f.x;
		rede[local_y][local_x]->roteamento_sul.cordenada_destino.y =   pct->v[0].cordenadas_f.y;	
		rede[local_y][local_x]->buffer_sul->din =  pct->v[0];

		cout << "SUL" << endl;
	} else if (rede[local_y][local_x]->roteamento_local.portaDestino == LESTE)
	{
		rede[local_y][local_x]->cf_saida_leste->out_val.write(1);
		rede[local_y][local_x]->roteamento_leste.cordenada_destino.x =   pct->v[0].cordenadas_f.x;
		rede[local_y][local_x]->roteamento_leste.cordenada_destino.y =   pct->v[0].cordenadas_f.y;	
		rede[local_y][local_x]->buffer_leste->din =  pct->v[0];

		cout << "LESTE" << endl;
	} else if (rede[local_y][local_x]->roteamento_local.portaDestino == OESTE)
	{	
		rede[local_y][local_x]->roteamento_oeste.cordenada_destino.x =   pct->v[0].cordenadas_f.x;
		rede[local_y][local_x]->roteamento_oeste.cordenada_destino.y =   pct->v[0].cordenadas_f.y;	
		rede[local_y][local_x]->buffer_oeste->din =  pct->v[0];
		rede[local_y][local_x]->cf_saida_oeste->out_val.write(1);

		cout << "OESTE" << endl;
	} else {
		printf("CHEGOUUUUU...\n");
		rede[local_y][local_x]->buffer_local->din =	 pct->v[0];
		rede[local_y][local_x]->buffer_local->add();
	}
}