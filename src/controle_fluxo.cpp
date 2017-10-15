#include "controle_fluxo.h"

void controle_fluxo::request(){
	if(in_val == 1){
		wr.write(1);
	}
}

void controle_fluxo::response(){
	if(wok == 1){
		in_ack.write(1);
	}
}