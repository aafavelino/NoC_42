#include "roteamento.h"

Roteamento::Roteamento()
{
	
}

void Roteamento::rotear_xy()
{	
	if (cordenada_destino.y > cordenada.y )
	{
		portaDestino = LESTE;
		printf("Porta no roteamento leste\n");
	} else if (cordenada_destino.y < cordenada.y)
	{
		portaDestino = OESTE;
		printf("Porta no roteamento Oeste\n");
	} else if (cordenada_destino.x > cordenada.x)
	{
		portaDestino = SUL;
		printf("Porta no roteamento sul\n");
	} else if (cordenada_destino.x < cordenada.x)
	{
		portaDestino = NORTE;
		printf("Porta no roteamento norte\n");
	} else {
		printf("local\n");
		portaDestino = LOCAL;
	}
}
