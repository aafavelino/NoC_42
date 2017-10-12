#include "controle_fluxo.h"

void controle_fluxo::request(){
	if(in_val.read() == 1){
		wr.write(1);
	}
}

void controle_fluxo::response(){
	if(wok.read() == 1){
		in_ack.write(1);
	}
}