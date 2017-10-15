#include "roteador.h"


void roteador::execute() {
	


	//if (in_val.read() == 1)
	//{
		// falta fazer verificações no buffer local
		buffer_local->din = this->in_data;
		buffer_local->wr = 1;
		buffer_local->add();
		//cout << "size " << buffer_local->flits.size() << endl;
		// Isso podeRIA dar problemas NAO DA MAIS DESSE JEITO...
		roteamento_local.cordenada_destino.x = this->in_data.cordenadas_f.x;
		roteamento_local.cordenada_destino.y = this->in_data.cordenadas_f.y;

		roteamento_local.rotear_xy();
		
		//std::cout << roteamento_local.portaDestino << endl;





		if (roteamento_local.portaDestino == SOUTH)
		{
			//sul
			cf_buffer_sul->in_val = 1;
			cf_buffer_sul->request();
			
			
			
			if (cf_buffer_sul->wr == 1){
				buffer_sul->wr = cf_buffer_sul->wr;
				// colocar um if aqui ainda...
				cf_buffer_sul->wok = buffer_sul->isEmpty();
			}
			
			//cout << "wok " << cf_buffer_sul->wok << endl;
			
			if (cf_buffer_sul->wok == 1)
				cf_buffer_sul->in_ack = 1;

			if (cf_buffer_sul->in_ack == 1) {
				std::cout << ">>> Escrevendo no --din-- do buffer sul" << endl;
				buffer_sul->din = din;


				buffer_sul->add();
	
				buffer_local->remove();
	

			}
			std::cout << "entrei na sul" << endl;

		} else if (roteamento_local.portaDestino == NORTH)
		{
			//norte
			cf_buffer_norte->in_val = 1;
			cf_buffer_norte->request();
			
			
			
			if (cf_buffer_norte->wr == 1){
				buffer_norte->wr = cf_buffer_norte->wr;
				// colocar um if aqui ainda...
				cf_buffer_norte->wok = buffer_norte->isEmpty();
			}
			
			//cout << "wok " << cf_buffer_norte->wok << endl;
			
			if (cf_buffer_norte->wok == 1)
				cf_buffer_norte->in_ack = 1;

			if (cf_buffer_norte->in_ack == 1) {
				std::cout << ">>> Escrevendo no --din-- do buffer norte" << endl;
				buffer_norte->din = din;


				buffer_norte->add();
	
				buffer_local->remove();
	

			}
			std::cout << "entrei na norte" << endl;

		} else if (roteamento_local.portaDestino == EAST)
		{
			//leste
			cf_buffer_leste->in_val = 1;
			cf_buffer_leste->request();
			
			
			
			if (cf_buffer_leste->wr == 1){
				buffer_leste->wr = cf_buffer_leste->wr;
				// colocar um if aqui ainda...
				cf_buffer_leste->wok = buffer_leste->isEmpty();
			}
			
			//cout << "wok " << cf_buffer_leste->wok << endl;
			
			if (cf_buffer_leste->wok == 1)
				cf_buffer_leste->in_ack = 1;

			if (cf_buffer_leste->in_ack == 1) {
				std::cout << ">>> Escrevendo no --din-- do buffer leste" << endl;
				buffer_leste->din = din;


				buffer_leste->add();
	
				buffer_local->remove();
	

			}
			std::cout << "entrei na leste" << endl;
		
		} else if (roteamento_local.portaDestino == WEST)
		{
			//oeste
			cf_buffer_oeste->in_val = 1;
			cf_buffer_oeste->request();
			
			
			
			if (cf_buffer_oeste->wr == 1){
				buffer_oeste->wr = cf_buffer_oeste->wr;
				// colocar um if aqui ainda...
				cf_buffer_sul->wok = buffer_sul->isEmpty();
			}
			
			//cout << "wok " << cf_buffer_oeste->wok << endl;
			
			if (cf_buffer_oeste->wok == 1)
				cf_buffer_oeste->in_ack = 1;

			if (cf_buffer_oeste->in_ack == 1) {
				std::cout << ">>> Escrevendo no --din-- do buffer oeste" << endl;
				buffer_oeste->din = din;


				buffer_oeste->add();
	
				buffer_local->remove();
	

			}
			std::cout << "entrei na oeste" << endl;
		
		}

	//}
		
}
