//
// Created by Adelino on 30/11/17.
//

#include "roteamento.h"

void Roteamento::rotear_odd_even() {
	//ODD
	if (portaAnterior == LOCAL)
	{
		if (cordenada_destino.y > cordenada.y )
		{
			portaDestino = LESTE;
		} else if (cordenada_destino.y < cordenada.y)
		{
			portaDestino = OESTE;
		} else if (cordenada_destino.x > cordenada.x)
		{
			portaDestino = SUL;

		} else if (cordenada_destino.x < cordenada.x)
		{
			portaDestino = NORTE;
		}
	} else {
		if (odd_even == 1) // odd
		{
			if (portaAnterior == NORTE or portaAnterior == SUL)
			{
				if (cordenada_destino.y > cordenada.y )
					portaDestino = LESTE;
			 	else if (cordenada_destino.x > cordenada.x)
					portaDestino = SUL;
				else if (cordenada_destino.x < cordenada.x)
					portaDestino = NORTE;
				else 
					portaDestino = LOCAL;
			}  else {
				if (cordenada_destino.y < cordenada.y)
					portaDestino = OESTE;
				else if (cordenada_destino.y > cordenada.y )
					portaDestino = LESTE;
				else 
					portaDestino = LOCAL;
			}
		} else { // even
			if (portaAnterior == OESTE)
			{
				if (cordenada_destino.y > cordenada.y )
					portaDestino = LESTE;
				else if (cordenada_destino.y < cordenada.y)
					portaDestino = OESTE;
				else 
					portaDestino = LOCAL;
			} else {
				if (cordenada_destino.x > cordenada.x)
					portaDestino = SUL;
				else if (cordenada_destino.x < cordenada.x)
					portaDestino = NORTE;
				else 
					portaDestino = LOCAL;
			}
		}		
	}



}


void Roteamento::rotear_xy()
{	
	if (cordenada_destino.y > cordenada.y )
	{
		portaDestino = LESTE;
	} else if (cordenada_destino.y < cordenada.y)
	{
		portaDestino = OESTE;
	} else if (cordenada_destino.x > cordenada.x)
	{
		portaDestino = SUL;
	} else if (cordenada_destino.x < cordenada.x)
	{
		portaDestino = NORTE;
	} else {
		portaDestino = LOCAL;
	}
}

void Roteamento::rotear_west_first() 
{
	if (cordenada_destino.y < cordenada.y)
	{
		portaDestino = OESTE;
	} else if (cordenada_destino.y > cordenada.y )
	{
		portaDestino = LESTE;
	} else if (cordenada_destino.x > cordenada.x)
	{
		portaDestino = SUL;
	} else if (cordenada_destino.x < cordenada.x)
	{
		portaDestino = NORTE;
	} else {
		portaDestino = LOCAL;
	}
}

void Roteamento::rotear_north_last()
{
		if (cordenada_destino.y < cordenada.y)
		{
			portaDestino = OESTE;
		} else if (cordenada_destino.y > cordenada.y )
		{
			portaDestino = LESTE;
		} else if (cordenada_destino.x > cordenada.x)
		{
			portaDestino = SUL;
		} else if (cordenada_destino.x < cordenada.x)
		{
			portaDestino = NORTE;
		} else {
			portaDestino = LOCAL;
		}

}

void Roteamento::rotear_negative_first()
{

	if (cordenada_destino.y < cordenada.y)
	{
		portaDestino = OESTE;
	} else if (cordenada_destino.x > cordenada.x)
	{
		portaDestino = SUL;
	} else if ((cordenada_destino.y >= cordenada.y) and (cordenada_destino.x <= cordenada.x))
	{
		if (cordenada_destino.y > cordenada.y)
		{
			portaDestino = LESTE;
		} else if (cordenada_destino.x < cordenada.x)
		{
			portaDestino = NORTE;
		} else {
			portaDestino = LOCAL;
		}
	}	

	if ((cordenada_destino.x >= cordenada.x) and (cordenada_destino.y >= cordenada.y))
	{
		if (cordenada_destino.x > cordenada.x)
		{
			portaDestino = SUL;
		} else if (cordenada_destino.y > cordenada.y)
		{
			portaDestino = LESTE;
		} else {
			portaDestino = LOCAL;
		}
	}

}





