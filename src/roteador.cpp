#include "roteador.h"

void roteador::execute() {
		out_cff.write(in_cff.read());
		
		cout << "OUT DEU " << out_cff.read() << endl;
		cout << "in DEU " << in_cff.read() << endl;
	}
	