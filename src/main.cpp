#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {
	REDE *teste = new REDE("rede");

	// teste->injeta_flits(4,4, 0, 0);
	// for (int i = 0; i < 1000; ++i)
	// {
		teste->injeta_flits(0,0, 0, 4);
			sc_start();	
		// teste->injeta_flits(0,0, 4, 4);
			// sc_start();	

	// }		

  	return 0;
}