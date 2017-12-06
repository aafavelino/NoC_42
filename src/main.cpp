#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {
	SYSTEM *teste = new SYSTEM("rede");

	for (int i = 0; i < 1; ++i)
	{
	

		//teste->injeta_flits(3, 3, 0,3);
		teste->injeta_flits(4, 0, 0,0);
		//teste->injeta_flits(7, 7, 0,7);
		//teste->injeta_flits(0, 7, 7,7);
		//teste->injeta_flits(4, 4, 0,0);
		teste->comunicacao();
	}

	teste->injeta_flits(4, 0, 0,0);
	teste->comunicacao();




/*

	printf("%s\n", "Outra");
	teste->injeta_flits(4, 4, 0, 1);
	teste->comunicacao();


	printf("%s\n", "Outra");
	teste->injeta_flits(0, 0, 4, 4);
	teste->comunicacao();
	*/

  	return 0;
}