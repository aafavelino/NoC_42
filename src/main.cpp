#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "pacote.h"
#include "system.h"

// Não tá simples, nem manutenível
// Tem que melhorar o código
// refactorring 

#define LARGURA_REDE 2
#define ALTURA_REDE 2

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define LOCAL 4

using namespace std;
//aqui


int sc_main (int argc, char* argv[]) {

	SYSTEM* sistema = NULL;
	sistema = new SYSTEM( "sistema" );
	sc_start();

  return 0;// Terminate simulation
}