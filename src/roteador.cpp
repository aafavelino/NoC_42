#include "roteador.h"

void roteador::execute() {
	if (cf_leste->in_val.read() == 1)
	{
		std::cout << "leste" << endl;
		cf_leste->out_cf_buffer.write(1);
		sc_start();
		if (buffer_leste->in_bf_controle_fluxo.read() == 1)
			buffer_leste->out_bf_controle_fluxo.write(buffer_leste->isEmpty());
		sc_start();
		if (cf_leste->in_cf_buffer.read() == 1)
			cf_leste->in_ack.write(1);	
	} 
	if (cf_oeste->in_val.read() == 1)
	{
		std::cout << "oeste" << endl;
		cf_oeste->out_cf_buffer.write(1);
		sc_start();
		if (buffer_oeste->in_bf_controle_fluxo.read() == 1)
			buffer_oeste->out_bf_controle_fluxo.write(buffer_oeste->isEmpty());
		sc_start();
		if (cf_oeste->in_cf_buffer.read() == 1)
			cf_oeste->in_ack.write(1);	
	} 
	if (cf_norte->in_val.read() == 1)
	{
		std::cout << "norte" << endl;
		cf_norte->out_cf_buffer.write(1);
		sc_start();
		if (buffer_norte->in_bf_controle_fluxo.read() == 1)
			std::cout << "vazio? " << buffer_norte->isEmpty() << endl;
			buffer_norte->out_bf_controle_fluxo.write(buffer_norte->isEmpty());
		sc_start();
		if (cf_norte->in_cf_buffer.read() == 1)
			cf_norte->in_ack.write(1);			
	} 
	if (cf_sul->in_val.read() == 1)
	{
		/* EXECUTA ALGUMA COISA AQUI */
		std::cout << "sul" << endl;
		cf_sul->out_cf_buffer.write(1);
		sc_start();
		if (buffer_sul->in_bf_controle_fluxo.read() == 1)
			buffer_sul->out_bf_controle_fluxo.write(buffer_sul->isEmpty());
		sc_start();
		if (cf_sul->in_cf_buffer.read() == 1)
			cf_sul->in_ack.write(1);	
	} 	
	if (cf_local->in_val.read() == 1)
	{
		std::cout << "local" << endl;
		/* EXECUTA ALGUMA COISA AQUI */
	}

}


/*

void roteador::gravar() {
	if (cf_saida_leste->ack.read() == 1)
	{
		std::cout << "Gravar no buffer leste" << endl;

	} 
	if (cf_saida_oeste->ack.read() == 1)
	{
		std::cout << "Gravar no buffer oeste" << endl;
		
	} 
	if (cf_saida_norte->ack.read() == 1)
	{
		std::cout << "Gravar no buffer norte" << endl;
		
	} 
	if (cf_saida_sul->ack.read() == 1)
	{
		std::cout << "Gravar no buffer sul" << endl;
		
	}


	
}*/
