#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {
	SYSTEM *teste = new SYSTEM("rede");
	
	teste->injeta_flits(4, 4,10, 0, 0);
	teste->comunicacao();
	

	

  	return 0;
}