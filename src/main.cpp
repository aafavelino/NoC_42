#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {
	REDE *teste = new REDE("rede");

			/*Ver este caso depois...*/		
		// teste->injeta_flits(0,6, 6, 6);
		// teste->injeta_flits(1,6, 6, 6);
		// teste->injeta_flits(2,6, 6, 6);
		// teste->injeta_flits(3,6, 6, 6);
		// teste->injeta_flits(4,6, 6, 6);
		// teste->injeta_flits(5,6, 6, 6);


		teste->injeta_flits(5,6, 6, 6);
		teste->injeta_flits(5,0, 6, 6);
		teste->injeta_flits(0,0, 6, 6);
		teste->injeta_flits(6,6, 0, 0);



		 sc_start();	

			
	



  	return 0;
}