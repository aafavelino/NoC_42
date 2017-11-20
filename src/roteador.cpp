#include "roteador.h"

void roteador::execute_controle_fluxo() 
{
	if (cf_leste->in_val.read() == 1)
	{
		//printf("Controle de fluxo no buffer leste\n");
		cf_leste->out_cf_buffer.write(1);
	} 
	if (cf_oeste->in_val.read() == 1)
	{
		//printf("Controle de fluxo no buffer oeste\n");
		cf_oeste->out_cf_buffer.write(1);
	} 
	if (cf_norte->in_val.read() == 1)
	{
		//printf("Controle de fluxo no buffer norte\n");
		cf_norte->out_cf_buffer.write(1);
	} 
	if (cf_sul->in_val.read() == 1)
	{
		//printf("Controle de fluxo no buffer sul\n");
		cf_sul->out_cf_buffer.write(1);
	} 	
	if (cf_local->in_val.read() == 1)
	{
		//printf("Controle de fluxo no buffer local\n");
		cf_local->out_cf_buffer.write(1);
	}

}

void roteador::execute_buffer() 
{
	if (buffer_norte->in_bf_controle_fluxo.read() == 1)
	{
		//printf("No buffer norte\n");
		buffer_norte->out_bf_controle_fluxo.write(buffer_norte->isEmpty());
	}
	if (buffer_sul->in_bf_controle_fluxo.read() == 1)
	{
		//printf("No buffer sul\n");
		buffer_sul->out_bf_controle_fluxo.write(buffer_sul->isEmpty());
	}
	if (buffer_leste->in_bf_controle_fluxo.read() == 1)
	{
		//printf("No buffer leste\n");
		buffer_leste->out_bf_controle_fluxo.write(buffer_leste->isEmpty());
	}
	if (buffer_oeste->in_bf_controle_fluxo.read() == 1)
	{
		//printf("No buffer oeste\n");
		buffer_oeste->out_bf_controle_fluxo.write(buffer_oeste->isEmpty());
	}
	if (buffer_local->in_bf_controle_fluxo.read() == 1)
	{
		//printf("No buffer local\n");
		buffer_local->out_bf_controle_fluxo.write(buffer_local->isEmpty());
	}
}

void roteador::execute_buffer_retorno() 
{
	if (cf_norte->in_cf_buffer.read() == 1)
	{
		//printf("Retorno do buffer norte\n");
		cf_norte->in_ack.write(1);
	}
	if (cf_sul->in_cf_buffer.read() == 1)
	{
		//printf("Retorno do buffer sul\n");
		cf_sul->in_ack.write(1);
	}
	if (cf_leste->in_cf_buffer.read() == 1)
	{
		//printf("Retorno do buffer leste\n");
		cf_leste->in_ack.write(1);
	}
	if (cf_oeste->in_cf_buffer.read() == 1)
	{
		//printf("Retorno do buffer oeste\n");
		cf_oeste->in_ack.write(1);
	}
	if (cf_local->in_cf_buffer.read() == 1)
	{
		//printf("Retorno do buffer local\n");
		cf_local->in_ack.write(1);
	}				
}

