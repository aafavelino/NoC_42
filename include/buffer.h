//
// Created by Adelino on 30/11/17.
//

#ifndef _BUFFER_H_
#define _BUFFER_H_ 

#include <iostream>
#include <queue>
#include "systemc.h"
#include "flit.h"
#include "controle_fluxo.h"
#include "../constantes/constantes.h"


SC_MODULE (Buffer)
{

public:
	int arquivo[3];
	std::queue<Flit> flit;
    int size[QT_CANAIS_VIRTUAIS];

    std::vector<std::queue<Flit> > buffer_virtual;

	Flit din; //Entrada data + bop + eop
	Flit dout; //Saída que vai para o roteamento

	sc_int<4>  wr; //Entrada que vem do controle de fluxo
	sc_int<4>  wok; //Saída que volta para o buffer

	void add(int);
	void remove(int);
	int isEmpty(int);
	int espaco(int);

	~Buffer() {
		free(size);
	}

	SC_CTOR(Buffer) {
		FILE *config;
		config = fopen("configuracoes.txt","r");
		fscanf(config,"tmb %i, arb %i, rot %i",&arquivo[0], &arquivo[1], &arquivo[2]);
		fclose(config);
		// cout << "TAMANHO_BUFFER " << TAMANHO_BUFFER << endl;
		for (int i = 0; i < QT_CANAIS_VIRTUAIS; ++i)
		{
			buffer_virtual.push_back(flit);
			size[i] = 0;
		}
        
	}

	
};
#endif
