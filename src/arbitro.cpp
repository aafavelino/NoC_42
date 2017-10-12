#include "arbitro.h"

Arbitro::Arbitro() {
	for (int i = 0; i < 5; ++i)
		buffercircular[i] = 0;
}

Arbitro::~Arbitro() {
	
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
		if (buffercircular[i] == 1 and i == 4)
		{
			return i;
		} else if (buffercircular[i] == 1 and i == 3)
		{
			return i;
		} else if (buffercircular[i] == 1 and i == 2)
		{
			return i;
		} else if (buffercircular[i] == 1 and i == 1)
		{
			return i;
		} else if (buffercircular[i] == 1 and i == 0)
		{
			return i;
		}
	}

	return -1;

}
