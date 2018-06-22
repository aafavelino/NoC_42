//
// Created by Adelino on 30/11/17.
//

#include "roteamento.h"

void Roteamento::rotear_odd_even() {
	//ODD
	if (portaAnterior == LOCAL)
	{
		if (std::get<1>(destino) > std::get<1>(origem))
		{
			portaDestino = LESTE;
		} else if (std::get<1>(destino) < std::get<1>(origem))
		{
			portaDestino = OESTE;
		} else if (std::get<0>(destino) > std::get<0>(origem))
		{
			portaDestino = SUL;

		} else if (std::get<0>(destino) < std::get<0>(origem))
		{
			portaDestino = NORTE;
		}
	} else {
		if (odd_even == 1) // odd
		{
			if (portaAnterior == NORTE or portaAnterior == SUL)
			{
				if (std::get<1>(destino) > std::get<1>(origem) )
					portaDestino = LESTE;
			 	else if (std::get<0>(destino) > std::get<0>(origem))
					portaDestino = SUL;
				else if (std::get<0>(destino) < std::get<0>(origem))
					portaDestino = NORTE;
				else 
					portaDestino = LOCAL;
			}  else {
				if (std::get<1>(destino) < std::get<1>(origem))
					portaDestino = OESTE;
				else if (std::get<1>(destino) > std::get<1>(origem) )
					portaDestino = LESTE;
				else 
					portaDestino = LOCAL;
			}
		} else { // even
			if (portaAnterior == OESTE)
			{
				if (std::get<1>(destino) > std::get<1>(origem) )
					portaDestino = LESTE;
				else if (std::get<1>(destino) < std::get<1>(origem))
					portaDestino = OESTE;
				else 
					portaDestino = LOCAL;
			} else {
				if (std::get<0>(destino) > std::get<0>(origem))
					portaDestino = SUL;
				else if (std::get<0>(destino) < std::get<0>(origem))
					portaDestino = NORTE;
				else 
					portaDestino = LOCAL;
			}
		}		
	}



}


void Roteamento::rotear_xy()
{	
	if (std::get<1>(destino) > std::get<1>(origem) )
	{
		portaDestino = LESTE;
	} else if (std::get<1>(destino) < std::get<1>(origem))
	{
		portaDestino = OESTE;
	} else if (std::get<0>(destino) > std::get<0>(origem))
	{
		portaDestino = SUL;
	} else if (std::get<0>(destino) < std::get<0>(origem))
	{
		portaDestino = NORTE;
	} else {
		portaDestino = LOCAL;
	}
}

void Roteamento::rotear_west_first() 
{
	if (std::get<1>(destino) < std::get<1>(origem))
	{
		portaDestino = OESTE;
	} else if (std::get<1>(destino) > std::get<1>(origem) )
	{
		portaDestino = LESTE;
	} else if (std::get<0>(destino) > std::get<0>(origem))
	{
		portaDestino = SUL;
	} else if (std::get<0>(destino) < std::get<0>(origem))
	{
		portaDestino = NORTE;
	} else {
		portaDestino = LOCAL;
	}
}

void Roteamento::rotear_north_last()
{
		if (std::get<1>(destino) < std::get<1>(origem))
		{
			portaDestino = OESTE;
		} else if (std::get<1>(destino) > std::get<1>(origem) )
		{
			portaDestino = LESTE;
		} else if (std::get<0>(destino) > std::get<0>(origem))
		{
			portaDestino = SUL;
		} else if (std::get<0>(destino) < std::get<0>(origem))
		{
			portaDestino = NORTE;
		} else {
			portaDestino = LOCAL;
		}

}

void Roteamento::rotear_negative_first()
{

	if (std::get<1>(destino) < std::get<1>(origem))
	{
		portaDestino = OESTE;
	} else if (std::get<0>(destino) > std::get<0>(origem))
	{
		portaDestino = SUL;
	} else if ((std::get<1>(destino) >= std::get<1>(origem)) and (std::get<0>(destino) <= std::get<0>(origem)))
	{
		if (std::get<1>(destino) > std::get<1>(origem))
		{
			portaDestino = LESTE;
		} else if (std::get<0>(destino) < std::get<0>(origem))
		{
			portaDestino = NORTE;
		} else {
			portaDestino = LOCAL;
		}
	}	

	if ((std::get<0>(destino) >= std::get<0>(origem)) and (std::get<1>(destino) >= std::get<1>(origem)))
	{
		if (std::get<0>(destino) > std::get<0>(origem))
		{
			portaDestino = SUL;
		} else if (std::get<1>(destino) > std::get<1>(origem))
		{
			portaDestino = LESTE;
		} else {
			portaDestino = LOCAL;
		}
	}

}





