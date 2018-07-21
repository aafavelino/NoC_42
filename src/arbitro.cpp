//
// Created by Adelino on 30/11/17.
//

#include "arbitro.h"

Arbitro::Arbitro() {
	FILE *config;
	config = fopen("configuracoes.txt","r");
	fscanf(config,"tmb %i, arb %i, rot %i",&arquivo[0], &arquivo[1], &arquivo[2]);
	fclose(config);
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 2; ++j)
			buffercircular[i][j] = -1;
	prioridade = -1;
}

void Arbitro::addSolicitacao(int port, Flit flit) 
{	

	if (flit.begin != -1)
	{
		buffercircular[port][0] = 1;
		buffercircular[port][1] = flit.id;
		// arbitra = true;
		// livre =  false;		
	}

	if (livre)
	{
		arbitra = true;
		livre =  false;	
	}
}

void Arbitro::remSolicitacao(int x, Flit flit)
{
	if (flit.end == id_pacote)
	{
		buffercircular[x][0] = -1;
		buffercircular[x][1] = -1;
		livre =  true;	
		prioridade = -1;
	}
}

int roda = 0;

void Arbitro::setPrioridade()
{

	if (arbitra)
	{

		
		switch (arquivo[1]) {
			case 1:
				arbitra =  false;
				for (int i = 4; i >= 0; --i)
				{
					if (buffercircular[i][0] == 1)
					{
						prioridade = i;
						id_pacote = buffercircular[i][1];
						buffercircular[i][0] = -1;
						buffercircular[i][1] = -1;

						return;
					}
				}			
			break;
			case 2:
				arbitra =  false;
				roda:;
				if (buffercircular[roda][0] == 1) 
				{
					id_pacote = buffercircular[roda][1];
					prioridade = roda;
					buffercircular[roda][0] = -1;
					buffercircular[roda][1] = -1;
				} else {
					if (roda == 4)
					{
						roda = 0;
					} else {
						roda++;
					}
					goto roda;
				}
				return;		
			break;
			case 3:
				arbitra =  false;
				std::function<int (int, int)> func = [](int i, int j){return rand() % i + j;};
				arbitra =  false;
				volta:;
				int i = func(5,0);
				if (buffercircular[i][0] == 1)
				{
					prioridade = i;
					id_pacote = buffercircular[i][1];
					buffercircular[i][0] = -1;
					buffercircular[i][1] = -1;
					return;
				} else {
					goto volta;
				}
				
								
				
			break;
		}
	}
}

int Arbitro::checkPrioridade()
{
	// printf("%s %i\n", "Prioridade em ", prioridade);
	return prioridade;
}
