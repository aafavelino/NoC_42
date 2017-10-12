#include <iostream>
#include <vector>
#include "systemc.h"
#include "pacote.h"
#include "buffer.h"
#include "flit.h"
#include "roteamento.h"
#include "roteador.h"

using namespace std;

int main(int argc, char const *argv[])
{
	Pacote pct;
	//Setar as cordenadas destinos dos flits...

	//Sinais do controle de fluxo
	sc_signal < sc_int<32> > in_ack_BN;
	sc_signal < sc_int<32> > in_ack_BS;
	sc_signal < sc_int<32> > in_ack_BL;
	sc_signal < sc_int<32> > in_ack_BO;

	sc_signal < sc_int<32> > in_val_BN;
	sc_signal < sc_int<32> > in_val_BS;
	sc_signal < sc_int<32> > in_val_BL;
	sc_signal < sc_int<32> > in_val_BO;

	//Sinais do controle de fluxo para o buffer
	sc_signal < sc_int<32> > wr_BN;
	sc_signal < sc_int<32> > wr_BS;
	sc_signal < sc_int<32> > wr_BL;
	sc_signal < sc_int<32> > wr_BO;

	sc_signal < sc_int<32> > wok_BN;
	sc_signal < sc_int<32> > wok_BS;
	sc_signal < sc_int<32> > wok_BL;
	sc_signal < sc_int<32> > wok_BO;	

//****************************************
	sc_signal < sc_int<32> > rd_BN;
	sc_signal < sc_int<32> > rd_BS;
	sc_signal < sc_int<32> > rd_BL;
	sc_signal < sc_int<32> > rd_BO;

	sc_signal < sc_int<32> > rok_BN;
	sc_signal < sc_int<32> > rok_BS;
	sc_signal < sc_int<32> > rok_BL;
	sc_signal < sc_int<32> > rok_BO;
//****************************************


// Criar uma Rede 4x4
	roteador *rede[3][3];

// Criando os roteadores para alocar na rede
	roteador roteador1("rot1");
	roteador roteador2("rot2");
	roteador roteador3("rot3");
	roteador roteador4("rot4");
	roteador roteador5("rot5");
	roteador roteador6("rot6");
	roteador roteador7("rot7");
	roteador roteador8("rot8");
	roteador roteador9("rot9");

// Alocando os roteadores no vetor rede
	rede[0][0] = &roteador1;	
	rede[0][1] = &roteador2;	
	rede[0][2] = &roteador3;	
	rede[1][0] = &roteador4;	
	rede[1][1] = &roteador5;	
	rede[1][2] = &roteador6;	
	rede[2][0] = &roteador7;	
	rede[2][1] = &roteador8;	
	rede[2][2] = &roteador9;

	

	return 0;
}