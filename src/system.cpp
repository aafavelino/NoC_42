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

while(true){
	if (rede[0][0]->cf_saida_leste->ack.read() == 1)
	{
		std::cout << "Gravar no buffer oeste r2" << endl;


		rede[0][1]->buffer_oeste->din =  rede[0][0]->buffer_leste->din;
		rede[0][1]->buffer_oeste->add();
		rede[0][1]->roteamento_oeste.cordenada_destino.x =  rede[0][1]->buffer_oeste->din.cordenadas_f.x;
		rede[0][1]->roteamento_oeste.cordenada_destino.y =  rede[0][1]->buffer_oeste->din.cordenadas_f.y;
		cout << "->>>>>>>>>>>>>>>>>>>>>>>>>>> " << rede[0][1]->buffer_oeste->din.cordenadas_f.x << " " << rede[0][1]->buffer_oeste->din.cordenadas_f.y  << endl;
		cout << "->>>>>>>>>>>>>>>>>>>>>>>>>>> " << rede[0][1]->roteamento_oeste.cordenada_destino.x << " " << rede[0][1]->roteamento_oeste.cordenada_destino.y  << endl;
		
		rede[0][1]->roteamento_oeste.rotear_xy();

		cout << "->>>>>>>>>>>>>>>>>>>>>>>>>>> " << rede[0][1]->roteamento_oeste.cordenada_destino.x << " " << rede[0][1]->roteamento_oeste.cordenada_destino.y  << endl;
	
		rede[0][1]->arbitro_centralizado.portaDestino = rede[0][1]->roteamento_oeste.portaDestino;
		rede[0][1]->arbitro_centralizado.setPrioridade();
		// teste


		if ((rede[0][1]->roteamento_oeste.cordenada.x ==  rede[0][1]->buffer_oeste->din.cordenadas_f.x) and (rede[0][1]->roteamento_oeste.cordenada.y ==  rede[0][1]->buffer_oeste->din.cordenadas_f.y))
		{
			cout << "Chegou" << endl;
			//jogar no buffer local
			rede[0][1]->buffer_local->din = rede[0][1]->buffer_oeste->flits.front();
			rede[0][1]->buffer_oeste->remove();
			rede[0][1]->buffer_local->add();


		} else {
			if (rede[0][1]->arbitro_centralizado.portaDestino == 2)
				rede[0][1]->cf_saida_sul->val.write(1);
			if(sc_pending_activity())
  				sc_start();
			
		}
		//cout << "OPA " << sc_time_stamp() << endl;
	} 

	if (rede[0][0]->cf_saida_sul->ack.read() == 1)
	{
		std::cout << "Gravar no buffer norte r3" << endl;
		rede[1][0]->buffer_norte->din =  rede[0][0]->buffer_sul->din;
		rede[1][0]->buffer_norte->add();
		rede[1][0]->roteamento_norte.cordenada_destino.x =  rede[1][0]->buffer_norte->din.cordenadas_f.x;
		rede[1][0]->roteamento_norte.cordenada_destino.y =  rede[1][0]->buffer_norte->din.cordenadas_f.y;

		rede[1][0]->roteamento_norte.rotear_xy();
	
		rede[1][0]->arbitro_centralizado.portaDestino = rede[1][0]->roteamento_norte.portaDestino;
		rede[1][0]->arbitro_centralizado.setPrioridade();
		// teste


		if ((rede[1][0]->roteamento_norte.cordenada.x ==  rede[1][0]->buffer_norte->din.cordenadas_f.x) and (rede[1][0]->roteamento_norte.cordenada.y ==  rede[1][0]->buffer_norte->din.cordenadas_f.y))
		{
			cout << "Chegou" << endl;
			//jogar no buffer local
			rede[1][0]->buffer_local->din = rede[0][1]->buffer_norte->flits.front();
			rede[1][0]->buffer_norte->remove();
			rede[1][0]->buffer_local->add();
		} else {
			if (rede[1][0]->arbitro_centralizado.portaDestino == 1)
				rede[1][0]->cf_saida_leste->val.write(1);
			if(sc_pending_activity())
  				sc_start();

		}

	} 

	if (rede[0][1]->cf_saida_sul->ack.read() == 1)
	{
		std::cout << "Gravar no buffer norte r4" << endl;
		rede[1][1]->buffer_norte->din =  rede[0][1]->buffer_sul->din;
		rede[1][1]->buffer_norte->add();
		rede[1][1]->roteamento_norte.cordenada_destino.x =  rede[1][1]->buffer_norte->din.cordenadas_f.x;
		rede[1][1]->roteamento_norte.cordenada_destino.y =  rede[1][1]->buffer_norte->din.cordenadas_f.y;

		rede[1][1]->roteamento_norte.rotear_xy();
	
		rede[1][1]->arbitro_centralizado.portaDestino = rede[1][1]->roteamento_norte.portaDestino;
		rede[1][1]->arbitro_centralizado.setPrioridade();

		if ((rede[1][1]->roteamento_norte.cordenada.x ==  rede[1][1]->buffer_norte->din.cordenadas_f.x) and (rede[1][1]->roteamento_norte.cordenada.y ==  rede[1][1]->buffer_norte->din.cordenadas_f.y))
		{
			cout << "Chegou..." << endl;
			rede[1][1]->buffer_local->din = rede[1][1]->buffer_norte->flits.front();
			rede[1][1]->buffer_norte->remove();
			rede[1][1]->buffer_local->add();
		} else {
			if (rede[1][1]->arbitro_centralizado.portaDestino == 3)
				rede[1][1]->cf_saida_oeste->val.write(1);
			if(sc_pending_activity())
  				sc_start();
		}

	} 

	if (rede[0][1]->cf_saida_oeste->ack.read() == 1)
	{
		std::cout << "Gravar no buffer leste r1" << endl;
		rede[0][0]->buffer_leste->din =  rede[0][1]->buffer_oeste->din;
		rede[0][0]->buffer_leste->add();
		rede[0][0]->roteamento_leste.cordenada_destino.x =  rede[0][0]->buffer_leste->din.cordenadas_f.x;
		rede[0][0]->roteamento_leste.cordenada_destino.y =  rede[0][0]->buffer_leste->din.cordenadas_f.y;

		rede[0][0]->roteamento_leste.rotear_xy();
	
		rede[0][0]->arbitro_centralizado.portaDestino = rede[0][0]->roteamento_leste.portaDestino;
		rede[0][0]->arbitro_centralizado.setPrioridade();
		// teste


		if ((rede[0][0]->roteamento_leste.cordenada.x ==  rede[0][0]->buffer_leste->din.cordenadas_f.x) and (rede[0][1]->roteamento_leste.cordenada.y ==  rede[0][0]->buffer_leste->din.cordenadas_f.y))
		{
			cout << "Chegou" << endl;
			rede[0][0]->buffer_local->din = rede[0][0]->buffer_leste->flits.front();
			rede[0][0]->buffer_leste->remove();
			rede[0][0]->buffer_local->add();			

		} else {
			if (rede[0][0]->arbitro_centralizado.portaDestino == 2)
				rede[0][0]->cf_saida_sul->val.write(1);		
			if(sc_pending_activity())
  				sc_start();
		}

	} 	




	if (rede[1][1]->cf_saida_norte->ack.read() == 1)
	{
		std::cout << "Gravar no buffer sul r2" << endl;
		rede[0][1]->buffer_sul->din =  rede[1][1]->buffer_norte->din;
		rede[0][1]->buffer_sul->add();
		rede[0][1]->roteamento_sul.cordenada_destino.x =  rede[0][1]->buffer_sul->din.cordenadas_f.x;
		rede[0][1]->roteamento_sul.cordenada_destino.y =  rede[0][1]->buffer_sul->din.cordenadas_f.y;

		rede[0][1]->roteamento_sul.rotear_xy();
	
		rede[0][1]->arbitro_centralizado.portaDestino = rede[0][1]->roteamento_sul.portaDestino;
		rede[0][1]->arbitro_centralizado.setPrioridade();
		// teste


		if ((rede[0][1]->roteamento_sul.cordenada.x ==  rede[0][1]->buffer_sul->din.cordenadas_f.x) and (rede[0][1]->roteamento_sul.cordenada.y ==  rede[0][1]->buffer_sul->din.cordenadas_f.y))
		{
			cout << "Chegou" << endl;
			//jogar no buffer local
			rede[0][1]->buffer_local->din = rede[0][1]->buffer_sul->flits.front();
			rede[0][1]->buffer_sul->remove();
			rede[0][1]->buffer_local->add();
		} else {
			if (rede[0][1]->arbitro_centralizado.portaDestino == 3)
				rede[0][1]->cf_saida_oeste->val.write(1);
			if(sc_pending_activity())
  				sc_start();
		}

	} 	


	if (rede[1][1]->cf_saida_oeste->ack.read() == 1)
	{
		std::cout << "Gravar no buffer leste r3" << endl;
		rede[1][0]->buffer_leste->din =  rede[1][1]->buffer_oeste->din;
		rede[1][0]->buffer_leste->add();
		rede[1][0]->roteamento_leste.cordenada_destino.x =  rede[1][0]->buffer_leste->din.cordenadas_f.x;
		rede[1][0]->roteamento_leste.cordenada_destino.y =  rede[1][0]->buffer_leste->din.cordenadas_f.y;

		rede[1][0]->roteamento_leste.rotear_xy();
	
		rede[1][0]->arbitro_centralizado.portaDestino = rede[1][0]->roteamento_leste.portaDestino;
		rede[1][0]->arbitro_centralizado.setPrioridade();
		// teste


		if ((rede[1][0]->roteamento_leste.cordenada.x ==  rede[1][0]->buffer_leste->din.cordenadas_f.x) and (rede[1][0]->roteamento_leste.cordenada.y ==  rede[1][0]->buffer_leste->din.cordenadas_f.y))
		{
			cout << "Chegou" << endl;
			//jogar no buffer local
			rede[1][0]->buffer_local->din = rede[1][0]->buffer_leste->flits.front();
			rede[1][0]->buffer_leste->remove();
			rede[1][0]->buffer_local->add();
		} else {
			if (rede[1][0]->arbitro_centralizado.portaDestino == 0)
				rede[1][0]->cf_saida_norte->val.write(1);
			if(sc_pending_activity())
  				sc_start();
		}

	} 	



	if (rede[1][0]->cf_saida_norte->ack.read() == 1)
	{
		std::cout << "Gravar no buffer sul r1" << endl;
		rede[0][0]->buffer_sul->din =  rede[1][0]->buffer_norte->din;
		rede[0][0]->buffer_sul->add();
		rede[0][0]->roteamento_sul.cordenada_destino.x =  rede[0][0]->buffer_sul->din.cordenadas_f.x;
		rede[0][0]->roteamento_sul.cordenada_destino.y =  rede[0][0]->buffer_sul->din.cordenadas_f.y;

		rede[0][0]->roteamento_sul.rotear_xy();
	
		rede[0][0]->arbitro_centralizado.portaDestino = rede[0][0]->roteamento_sul.portaDestino;
		rede[0][0]->arbitro_centralizado.setPrioridade();
		// teste


		if ((rede[0][0]->roteamento_sul.cordenada.x ==  rede[0][0]->buffer_sul->din.cordenadas_f.x) and (rede[0][0]->roteamento_sul.cordenada.y ==  rede[0][0]->buffer_sul->din.cordenadas_f.y))
		{
			cout << "Chegou" << endl;
			//jogar no buffer local
			rede[0][0]->buffer_local->din = rede[0][0]->buffer_sul->flits.front();
			rede[0][0]->buffer_sul->remove();
			rede[0][0]->buffer_local->add();
		} else {
			if (rede[0][0]->arbitro_centralizado.portaDestino == 1)
				rede[0][0]->cf_saida_leste->val.write(1);
			if(sc_pending_activity())
  				sc_start();
		}

	} 	



	if (rede[1][0]->cf_saida_leste->ack.read() == 1)
	{
		std::cout << "Gravar no buffer oeste r4" << endl;
		rede[1][1]->buffer_oeste->din =  rede[1][0]->buffer_leste->din;
		rede[1][1]->buffer_oeste->add();
		rede[1][1]->roteamento_oeste.cordenada_destino.x =  rede[1][1]->buffer_oeste->din.cordenadas_f.x;
		rede[1][1]->roteamento_oeste.cordenada_destino.y =  rede[1][1]->buffer_oeste->din.cordenadas_f.y;

		rede[1][1]->roteamento_oeste.rotear_xy();
	
		rede[1][1]->arbitro_centralizado.portaDestino = rede[1][1]->roteamento_oeste.portaDestino;
		rede[1][1]->arbitro_centralizado.setPrioridade();


		if ((rede[1][1]->roteamento_oeste.cordenada.x ==  rede[1][1]->buffer_oeste->din.cordenadas_f.x) and (rede[1][1]->roteamento_oeste.cordenada.y ==  rede[1][1]->buffer_oeste->din.cordenadas_f.y))
		{
			cout << "Chegou" << endl;
			//jogar no buffer local
			rede[1][0]->buffer_local->din = rede[0][1]->buffer_oeste->flits.front();
			rede[1][0]->buffer_oeste->remove();
			rede[1][0]->buffer_local->add();			
		} else {
			if (rede[1][1]->arbitro_centralizado.portaDestino == 1)
				rede[1][1]->cf_saida_norte->val.write(1);
			if(sc_pending_activity())
  				sc_start();
		}

	}
break;
	//sc_stop();
} 	
}
