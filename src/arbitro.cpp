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

	for (int i = 0; i < 5; ++i)
	{
		if (buffercircular[i] == 1)
		{
			prioridade = i;
			return;
		}
	}
}

int Arbitro::checkPrioridade()
{
	return prioridade;
}
