#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {
	REDE *teste = new REDE("rede");
	teste->injeta_flits(0,0, 0, 4);
	teste->comunicacao();
		sc_start();	

	// teste->injeta_flits(0,1, 1, 4);
	// 	sc_start();		
	// teste->injeta_flits(0,3, 1, 2);
	// 	sc_start();			
	// teste->injeta_flits(4,3, 1, 0);
	// 	sc_start();	


  	return 0;
}