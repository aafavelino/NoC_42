#include "arbitro.h"

Arbitro::Arbitro() {
	for (int i = 0; i < 5; ++i)
		buffercircular[i] = 0;
}

void Arbitro::setPrioridade()
{
	if (buffercircular[portaDestino] == 0)
		buffercircular[portaDestino] = 1;
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
