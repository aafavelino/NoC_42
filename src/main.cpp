#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {
	REDE *teste = new REDE("rede");

	teste->injeta_flits(0,0, 3, 0);
	teste->comunicacao();
	

  	return 0;
}