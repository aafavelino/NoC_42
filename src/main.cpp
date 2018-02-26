//
// Created by Adelino on 30/11/17.
//
#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {

	sc_clock clock("clock", 10, SC_NS, 1, 10, SC_NS);
	REDE *teste = new REDE("rede");
	teste->Clk(clock);

	teste->injeta_flits(0,2, 0, 6); 
	teste->injeta_flits(0,0, 6, 6); 
	teste->injeta_flits(0,0, 6, 6); 
	// teste->injeta_flits(0,1, 1, 0);
	// teste->injeta_flits(0,0, 6, 6);
	// teste->injeta_flits(0,0, 6, 6);                                                               
	// teste->injeta_flits(0,0, 1, 0);            
	// teste->injeta_flits(6,6, 0, 0);
	// teste->injeta_flits(1,6, 1, 0);
	// teste->injeta_flits(1,0, 1, 6);
	// teste->injeta_flits(2,6, 2, 0);
	// teste->injeta_flits(2,0, 2, 6);	
	// teste->injeta_flits(3,6, 3, 0);
	// teste->injeta_flits(3,0, 3, 6);					
	// teste->injeta_flits(0,0, 0, 6);
	// teste->injeta_flits(0,0, 6, 6);
	// teste->injeta_flits(0,1, 6, 6);
	// teste->injeta_flits(6,6, 0, 0);
	// teste->injeta_flits(6,0, 6, 6);
	// teste->injeta_flits(6,1, 6, 6);
	// teste->injeta_flits(6,2, 6, 6);
	// teste->injeta_flits(6,3, 6, 6);
	// teste->injeta_flits(6,4, 6, 6);	
	// teste->injeta_flits(0,6, 6, 6);
	// teste->injeta_flits(1,6, 6, 6);
	// teste->injeta_flits(2,6, 6, 6);
	// teste->injeta_flits(3,6, 6, 6);
	// teste->injeta_flits(4,6, 6, 6);
	// teste->injeta_flits(5,6, 6, 6);
	// teste->injeta_flits(0,0, 5, 5);
	// teste->injeta_flits(0,1, 5, 6);
	// teste->injeta_flits(0,2, 5, 6);
	// teste->injeta_flits(0,3, 5, 6);
	// teste->injeta_flits(0,5, 5, 6);
	// teste->injeta_flits(0,6, 5, 6);
	// teste->injeta_flits(0,0, 6, 6);
	// teste->injeta_flits(6,6, 0, 0);
	// teste->injeta_flits(0,6, 0, 0);
	// teste->injeta_flits(1,6, 0, 0);
	// teste->injeta_flits(2,1, 6, 6);
	// teste->injeta_flits(1,0, 0, 0);
	// teste->injeta_flits(0,0, 1, 0);
	// teste->injeta_flits(0,0, 2, 0); 
	// teste->injeta_flits(0,0, 0, 1); 


	sc_start();	// Run the simulation till sc_stop is encountered

  	return 0;
}