#include <iostream>
#include <systemc.h>

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3
#define LOCAL 4

class Arbitro 
{
public:
	sc_uint<32> portaDestino;
	int buffercircular[5];

	Arbitro();
	~Arbitro();
	void setPrioridade();
	int checkPrioridade();
	
};