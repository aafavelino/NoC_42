#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {
	REDE *teste = new REDE("rede");


		// teste->injeta_flits(2,0, 0, 0);
		teste->injeta_flits(0,0, 6, 6);
		teste->injeta_flits(6,6, 0, 0);

		 sc_start();	

			
	



  	return 0;
}