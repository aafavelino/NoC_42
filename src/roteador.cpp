#include "roteador.h"

void roteador::execute_controle_fluxo() 
{
	if (cf_leste->in_val.read() == 1)
	{
		std::cout << "Controle de fluxo no buffer leste" << endl;
		cf_leste->out_cf_buffer.write(1);

	} 

	if (cf_oeste->in_val.read() == 1)
	{
		std::cout << "Controle de fluxo no buffer oeste" << endl;
		cf_oeste->out_cf_buffer.write(1);
	} 

	if (cf_norte->in_val.read() == 1)
	{
		std::cout << "Controle de fluxo no buffer norte" << endl;
		cf_norte->out_cf_buffer.write(1);
	} 

	if (cf_sul->in_val.read() == 1)
	{
		std::cout << "Controle de fluxo no buffer sul" << endl;
		cf_sul->out_cf_buffer.write(1);
	} 	

	if (cf_local->in_val.read() == 1)
	{
		std::cout << "Controle de fluxo no buffer local" << endl;
		cf_local->out_cf_buffer.write(1);
	}

}

void roteador::execute_buffer() 
{
	if (buffer_norte->in_bf_controle_fluxo.read() == 1)
	{
		std::cout << "No buffer norte" << endl;

		buffer_norte->out_bf_controle_fluxo.write(buffer_norte->isEmpty());
	}

	if (buffer_sul->in_bf_controle_fluxo.read() == 1)
	{
		std::cout << "No buffer sul" << endl;

		buffer_sul->out_bf_controle_fluxo.write(buffer_sul->isEmpty());
	}

	if (buffer_leste->in_bf_controle_fluxo.read() == 1)
	{
		std::cout << "No buffer leste" << endl;

		buffer_leste->out_bf_controle_fluxo.write(buffer_leste->isEmpty());
	}

	if (buffer_oeste->in_bf_controle_fluxo.read() == 1)
	{
		std::cout << "No buffer oeste" << endl;

		buffer_oeste->out_bf_controle_fluxo.write(buffer_oeste->isEmpty());
	}

	if (buffer_local->in_bf_controle_fluxo.read() == 1)
	{
		std::cout << "No buffer local" << endl;

		buffer_local->out_bf_controle_fluxo.write(buffer_local->isEmpty());
	}
}

void roteador::execute_buffer_retorno() 
{
	if (cf_norte->in_cf_buffer.read() == 1)
	{
		std::cout << "Retorno do buffer norte" << endl;
		cf_norte->in_ack.write(1);
	}

	if (cf_sul->in_cf_buffer.read() == 1)
	{
		std::cout << "Retorno do buffer sul" << endl;
		cf_sul->in_ack.write(1);
	}

	if (cf_leste->in_cf_buffer.read() == 1)
	{
		std::cout << "Retorno do buffer leste" << endl;
		cf_leste->in_ack.write(1);
	}

	if (cf_oeste->in_cf_buffer.read() == 1)
	{
		std::cout << "Retorno do buffer oeste" << endl;
		cf_oeste->in_ack.write(1);
	}

	if (cf_local->in_cf_buffer.read() == 1)
	{
		std::cout << "Retorno do buffer local" << endl;
		cf_local->in_ack.write(1);
	}				
}

