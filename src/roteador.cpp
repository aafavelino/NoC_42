#include "roteador.h"

void roteador::entrada_controle_de_fluxo()
{
	if (cf_norte->in_val.read() == 1)
	{
		// printf("Leitura do in_val pelo norte\n");
		cf_norte->wr = 1;
		entrada_buffer();
		confirmacao_buffer();
		cf_norte->wok = buffer_norte->wok;
		execute_retorno_controle_de_fluxo();
	}
	if (cf_sul->in_val.read() == 1)
	{
		// printf("Leitura do in_val pelo sul\n");
		cf_sul->wr = 1;
		entrada_buffer();
		confirmacao_buffer();
		cf_sul->wok = buffer_sul->wok;
		execute_retorno_controle_de_fluxo();
	}
	if (cf_leste->in_val.read() == 1)
	{
		// printf("Leitura do in_val pelo leste\n");
		cf_leste->wr = 1;
		entrada_buffer();
		confirmacao_buffer();
		cf_leste->wok = buffer_leste->wok;
		execute_retorno_controle_de_fluxo();
	}
	if (cf_oeste->in_val.read() == 1)
	{
		// printf("Leitura do in_val pelo oeste\n");
		cf_oeste->wr = 1;
		entrada_buffer();
		confirmacao_buffer();
		cf_oeste->wok = buffer_oeste->wok;
		execute_retorno_controle_de_fluxo();
	}	
}

// Após a solicitação do controle de fluxo é chamado esse método para verificar se há espaço no buffer e dar o retorno da comunicação com 
// o controle de fluxo de sua respectiva direção.
void roteador::entrada_buffer() 
{
	if (cf_norte->wr == 1)
		buffer_norte->wr = 1;

	if (cf_sul->wr == 1)
		buffer_sul->wr = 1;

	if (cf_leste->wr == 1)
		buffer_leste->wr = 1;

	if (cf_oeste->wr == 1)
		buffer_oeste->wr = 1;

}


void roteador::confirmacao_buffer()
{
	if (buffer_norte->wr == 1)
	{
		// Se tiver espaço no buffer retorna 1 para a variável wok do buffer para o controle de fluxo 
		if (buffer_norte->isEmpty() == 1)
		{
			buffer_norte->wok = 1;
		} else if (buffer_norte->isEmpty_canais_virtuais() == 1)
		{
			buffer_norte->wok = 1;
		}
		if (buffer_norte->wok == 1){
			cf_norte->wr = 0;
			buffer_norte->wr = 0;
		}		
	}

	if (buffer_sul->wr == 1)
	{
		// Se tiver espaço no buffer retorna 1 para a variável wok do buffer para o controle de fluxo 
		if (buffer_sul->isEmpty() == 1)
		{
			buffer_sul->wok = 1;
		} else if (buffer_sul->isEmpty_canais_virtuais() == 1)
		{
			buffer_sul->wok = 1;
		}
		if (buffer_sul->wok == 1){
			cf_sul->wr = 0;
			buffer_sul->wr = 0;
		}	
	}

	if (buffer_leste->wr == 1)
	{
		// Se tiver espaço no buffer retorna 1 para a variável wok do buffer para o controle de fluxo 
		if (buffer_leste->isEmpty() == 1)
		{
			buffer_leste->wok = 1;
		} else if (buffer_leste->isEmpty_canais_virtuais() == 1)
		{
			buffer_leste->wok = 1;
		}
		if (buffer_leste->wok == 1){
			cf_leste->wr = 0;
			buffer_leste->wr = 0;
		}
	}

	if (buffer_oeste->wr == 1)
	{
		// Se tiver espaço no buffer retorna 1 para a variável wok do buffer para o controle de fluxo 
		if (buffer_oeste->isEmpty() == 1)
		{
			buffer_oeste->wok = 1;
		} else if (buffer_oeste->isEmpty_canais_virtuais() == 1)
		{
			buffer_oeste->wok = 1;
		}
		if (buffer_oeste->wok == 1){
			cf_oeste->wr = 0;
			buffer_oeste->wr = 0;
		}
	}

}


void roteador::execute_retorno_controle_de_fluxo()
{
	if (cf_norte->wok == 1)
	{
		cf_norte->in_ack.write(1);
		buffer_norte->wok = 0;
		cf_norte->wok = 0;
	}

	if (cf_sul->wok == 1)
	{
		cf_sul->in_ack.write(1);
		buffer_sul->wok = 0;
		cf_sul->wok = 0;
	}
	if (cf_leste->wok == 1)
	{
		cf_leste->in_ack.write(1);
		buffer_leste->wok = 0;
		cf_leste->wok = 0;

	}
	if (cf_oeste->wok == 1)
	{
		cf_oeste->in_ack.write(1);
		buffer_oeste->wok = 0;
		cf_oeste->wok = 0;
	}
} 
