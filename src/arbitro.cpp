#include "arbitro.h"

Arbitro::Arbitro() {
	for (int i = 0; i < 5; ++i)
		buffercircular[i] = 0;
	prioridade = -1;
}

void Arbitro::addSolicitacao(int port) 
{
	buffercircular[port] = 1;
}

void Arbitro::remSolicitacao(int port) 
{
	buffercircular[port] = 0;
}


void Arbitro::setPrioridade()
{
	int aux;
	srand (time(NULL));
	aux = rand() % 5;
	if (buffercircular[aux] != 0)
	{
		prioridade = aux;
	
	} 
	else
	{
		for (int i = 0; i < 5; ++i)
		{
			if (buffercircular[i] != 0)
			{
				prioridade = i;
				return;
			}
		}
	}
}

int Arbitro::checkPrioridade()
{
	for (int i = 0; i < 5; ++i)
	{
		if (buffercircular[i] == 1 and i == LOCAL)
		{
			return i;
		} else if (buffercircular[i] == 1 and i == OESTE)
		{
			return i;
		} else if (buffercircular[i] == 1 and i == SUL)
		{
			return i;
		} else if (buffercircular[i] == 1 and i == LESTE)
		{
			return i;
		} else if (buffercircular[i] == 1 and i == NORTE)
		{
			return i;
		}
	}

	return -1;

}
