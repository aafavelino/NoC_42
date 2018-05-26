//
// Created by Adelino on 30/11/17.
//

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
	#ifdef ESTATICA
		for (int i = 0; i < 5; ++i)
		{
			if (buffercircular[i] == 1)
			{
				prioridade = i;
				return;
			}
		}				
	#endif

	#ifdef ROTATIVA
		std::vector<int> prioridades;
		for (int i = 0; i < 5; ++i)
			if (buffercircular[i] == 1){
				prioridades.push_back(i);
				buffercircular[i] = 0;
			}
		// cout << "prioridades " <<prioridades.size()-1 << "   " << prioridades[prioridades.size()-2] << endl;
		prioridade = prioridades[prioridades.size()-1];

		prioridades.pop_back();
		return;
	#endif

	#ifdef RANDOMICA
		std::vector<int> prioridades;
		for (int i = 0; i < 5; ++i)
			if (buffercircular[i] == 1){
				prioridades.push_back(i);
				buffercircular[i] = 0;
			}

		std::function<int (int, int)> func = [](int i, int j) { return rand() % i + j; };
		
		prioridade = prioridades[func(prioridades.size(), 0)];
		prioridades.erase (prioridades.begin(),prioridades.begin()+prioridades.size());
		return;
	#endif

}

int Arbitro::checkPrioridade()
{
	return prioridade;
}
