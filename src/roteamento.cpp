#include "roteamento.h"

Roteamento::Roteamento()
{
	
}

void Roteamento::rotear_xy()
{
	if (cordenada_destino.y > cordenada.y)
	{
		portaDestino = EAST;
		std::cout << "leste" << std::endl;
	} else if (cordenada_destino.y < cordenada.y)
	{
		portaDestino = WEST;
		std::cout << "Oeste" << std::endl;
	} else if (cordenada_destino.x > cordenada.x)
	{
		portaDestino = SOUTH;
		std::cout << "sul" << std::endl;
	} else if (cordenada_destino.x < cordenada.x)
	{
		portaDestino = NORTH;
		std::cout << "norte" << std::endl;
	} else {
		portaDestino = LOCAL;
	}
}
