#include "roteamento.h"

void Roteamento::rotear_xy()
{	
	// cout << "Cord Destino y " << cordenada_destino.y << " Cord Destino x " << cordenada_destino.x << endl;
	// cout << "Cord y " << cordenada.y << " Cord x " << cordenada.x << endl;
	if (cordenada_destino.y > cordenada.y )
	{
		portaDestino = LESTE;
		//printf("Porta no roteamento leste\n");
	} else if (cordenada_destino.y < cordenada.y)
	{
		portaDestino = OESTE;
		// printf("Porta no roteamento Oeste\n");
	} else if (cordenada_destino.x > cordenada.x)
	{

		portaDestino = SUL;
		// printf("Porta no roteamento sul\n");
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

void Roteamento::rotear_north_last()
{
	portaAnterior = portaDestino;

	if (portaAnterior == NORTE)
	{
		if (cordenada_destino.x < cordenada.x)
		{
			portaDestino = NORTE;
			//printf("Porta no roteamento norte\n");
		}
	} else {	
		if (cordenada_destino.y < cordenada.y)
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

}

void Roteamento::rotear_negative_first()
{
	portaAnterior = portaDestino;
	// cout << "PORTA: " << portaAnterior << endl;

	if (cordenada_destino.y < cordenada.y)
	{
		portaDestino = OESTE;
			//printf("Porta no roteamento Oeste\n");
	} else if (cordenada_destino.x > cordenada.x)
	{
		portaDestino = SUL;
		//printf("Porta no roteamento sul\n");
	} else if ((cordenada_destino.y >= cordenada.y) and (cordenada_destino.x <= cordenada.x))
	{
		if (cordenada_destino.y > cordenada.y)
		{
			portaDestino = LESTE;
				//printf("Porta no roteamento leste\n");
		} else if (cordenada_destino.x < cordenada.x)
		{
			portaDestino = NORTE;
				//printf("Porta no roteamento norte\n");
		} else {
				//printf("local\n");
			portaDestino = LOCAL;
		}
	}	

	if ((cordenada_destino.x >= cordenada.x) and (cordenada_destino.y >= cordenada.y))
	{
		if (cordenada_destino.x > cordenada.x)
		{
			portaDestino = SUL;
			//printf("Porta no roteamento sul\n");
		} else if (cordenada_destino.y > cordenada.y)
		{
			portaDestino = LESTE;
			//printf("Porta no roteamento leste\n");
		} else {
			//printf("local\n");
			portaDestino = LOCAL;
		}
	}

}





