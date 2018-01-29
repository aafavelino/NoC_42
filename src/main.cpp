#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {
	REDE *teste = new REDE("rede");


		// teste->injeta_flits(2,0, 0, 0);
		
		teste->injeta_flits(0,6, 6, 6);
		teste->injeta_flits(1,6, 6, 6);
		teste->injeta_flits(2,6, 6, 6);
		teste->injeta_flits(3,6, 6, 6);
		teste->injeta_flits(4,6, 6, 6);
		teste->injeta_flits(5,6, 6, 6);


		// teste->injeta_flits(6,0, 6, 6);
		// teste->injeta_flits(6,1, 6, 6);
		// teste->injeta_flits(6,2, 6, 6);
		// teste->injeta_flits(6,3, 6, 6);
		// teste->injeta_flits(6,4, 6, 6);
		 sc_start();	

			
	



  	return 0;
}