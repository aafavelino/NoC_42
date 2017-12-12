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
			cout << "PRIO >>> " << buffercircular[i] <<" " <<i << endl;
			prioridade = i;
			return;
		}
	}
}

int Arbitro::checkPrioridade()
{
	// for (int i = 0; i < 5; ++i)
	// {
	// 	if (buffercircular[i] == 1 and i == LOCAL)
	// 	{
	// 		return i;
	// 	} else if (buffercircular[i] == 1 and i == OESTE)
	// 	{
	// 		return i;
	// 	} else if (buffercircular[i] == 1 and i == SUL)
	// 	{
	// 		return i;
	// 	} else if (buffercircular[i] == 1 and i == LESTE)
	// 	{
	// 		cout << "ARBITRO PORTA LESTE" << endl;
	// 		return i;
	// 	} else if (buffercircular[i] == 1 and i == NORTE)
	// 	{
	// 		return i;
	// 	}
	// }
	
	cout << "PRIORIDADE "<< prioridade << endl;


	return prioridade;

}
