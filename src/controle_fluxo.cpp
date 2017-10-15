#include "controle_fluxo.h"

void controle_fluxo::request(){
	if(in_val == 1){
		wr = 1;
		//cout << "wr no CF " << wr << endl;
	}
}

void controle_fluxo::response(){
	if(wok == 1){
		in_ack = 1;
	}
}