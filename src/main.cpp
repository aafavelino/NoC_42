#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "pacote.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {
	SYSTEM* sistema = new SYSTEM("sistema");
	//sc_start();
	sistema->comunicacao();
  	return 0;
}