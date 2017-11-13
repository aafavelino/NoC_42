#include "roteamento.h"

Roteamento::Roteamento()
{
	
}

void Roteamento::rotear_xy()
{	
	if (cordenada_destino.y > cordenada.y )
	{
		portaDestino = LESTE;
		std::cout << "Porta no roteamento leste" << std::endl;
	} else if (cordenada_destino.y < cordenada.y)
	{
		portaDestino = OESTE;
		std::cout << "Porta no roteamento Oeste" << std::endl;
	} else if (cordenada_destino.x > cordenada.x)
	{
		portaDestino = SUL;
		std::cout << "Porta no roteamento sul" << std::endl;
	} else if (cordenada_destino.x < cordenada.x)
	{
		portaDestino = NORTE;
		std::cout << "Porta no roteamento norte" << std::endl;
	} else {
		std::cout << "local" << std::endl;
		portaDestino = LOCAL;
	}
}
