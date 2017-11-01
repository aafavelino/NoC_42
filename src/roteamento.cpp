#include "roteamento.h"

Roteamento::Roteamento()
{
	
}

void Roteamento::rotear_xy()
{
	//std::cout << "DEstino y " << cordenada_destino.y << std::endl;
	//std::cout << "Cord local " << cordenada.y << std::endl;
	
	if (cordenada_destino.y > cordenada.y)
	{

		portaDestino = EAST;
		std::cout << "Porta no roteamento leste" << std::endl;
	} else if (cordenada_destino.y < cordenada.y)
	{
		portaDestino = WEST;
		std::cout << "Porta no roteamento Oeste" << std::endl;
	} else if (cordenada_destino.x > cordenada.x)
	{
		portaDestino = SOUTH;
		std::cout << "Porta no roteamento sul" << std::endl;
	} else if (cordenada_destino.x < cordenada.x)
	{
		portaDestino = NORTH;
		std::cout << "Porta no roteamento norte" << std::endl;
	} else {
		//std::cout << "local" << std::endl;

		portaDestino = LOCAL;
	}
}
