#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {
	SYSTEM *teste = new SYSTEM("rede");
	//teste->injeta_flits(0, 0,10);
	for (int i = 0; i < 10; ++i)
	{
			teste->injeta_flits(4, 1,10, 4, 2);
	
	
	}
	teste->comunicacao();

	

  	return 0;
}