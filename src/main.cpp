#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "pacote.h"
#include "system.h"

using namespace std;
//aqui


int sc_main (int argc, char* argv[]) {

	SYSTEM* sistema = NULL;
	sistema = new SYSTEM( "sistema" );
	sc_start();

  return 0;// Terminate simulation
}