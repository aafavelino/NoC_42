#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {
	REDE *teste = new REDE("rede");

		// teste->injeta_flits(4,3, 1, 1);
		// 	sc_start();	
		teste->injeta_flits(3,0, 4, 4);
		// 	sc_start();	
		// teste->injeta_flits(0,3, 1, 2);
		// 	sc_start();			
		// teste->injeta_flits(4,4, 0, 0);
		// teste->injeta_flits(3,3, 0, 0);
		// teste->injeta_flits(3,3, 0, 0);
			sc_start();	
	



  	return 0;
}