#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {
	REDE *teste = new REDE("rede");

	//teste->injeta_flits(4,4, 0, 0);

		teste->injeta_flits(0,0, 4, 4);
			sc_start();	
		teste->injeta_flits(1,1, 1, 4);
			sc_start();	
		teste->injeta_flits(4,4, 0, 0);
			sc_start();				

			//Ver isso aqui em breve 
		teste->rede[0][0]->cf_saida_leste->out_val.write(0);
			sc_start();	

		teste->injeta_flits(1,0, 0,4);
			sc_start();	



  	return 0;
}