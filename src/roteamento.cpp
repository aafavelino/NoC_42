#include "roteamento.h"

void Roteamento::rotear_xy()
{	
	if (cordenada_destino.y > cordenada.y )
	{
		portaDestino = LESTE;
		//printf("Porta no roteamento leste\n");
	} else if (cordenada_destino.y < cordenada.y)
	{
		portaDestino = OESTE;
		//printf("Porta no roteamento Oeste\n");
	} else if (cordenada_destino.x > cordenada.x)
	{
		portaDestino = SUL;
		//printf("Porta no roteamento sul\n");
	} else if (cordenada_destino.x < cordenada.x)
	{
		portaDestino = NORTE;
		//printf("Porta no roteamento norte\n");
	} else {
		//printf("local\n");
		portaDestino = LOCAL;
	}
}

void Roteamento::rotear_west_first() 
{
	// Para validação se a porta vai para o oeste primeiro...
	portaAnterior = portaDestino;

	if ((cordenada_destino.y < cordenada.y) and (portaAnterior != NORTE) and (portaAnterior != SUL))
	{
		portaDestino = OESTE;
		//printf("Porta no roteamento Oeste\n");
	} else if (cordenada_destino.y > cordenada.y )
	{
		portaDestino = LESTE;
		//printf("Porta no roteamento leste\n");
	} else if (cordenada_destino.x > cordenada.x)
	{
		portaDestino = SUL;
		//printf("Porta no roteamento sul\n");
	} else if (cordenada_destino.x < cordenada.x)
	{
		portaDestino = NORTE;
		//printf("Porta no roteamento norte\n");
	} else {
		//printf("local\n");
		portaDestino = LOCAL;
	}
}
