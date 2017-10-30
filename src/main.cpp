#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "pacote.h"
#include "system.h"

using namespace std;
//aqui


int sc_main (int argc, char* argv[]) {

	//SYSTEM* sistema = NULL;
	SYSTEM* sistema = new SYSTEM( "sistema" );
	//cout << "A hora atual é" << sc_time_stamp () << endl ; 
	sc_start(100, SC_NS);
	//cout << "A hora atual é" << sc_time_stamp () << endl ; 


  return 0;// Terminate simulation
}