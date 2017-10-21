#include "roteador.h"

void roteador::execute() {
	if (cf_norte->in_val.read() == 1)
	{
		std::cout << "norte" << endl;


		// Se teve uma solicitação então escrevo 
		cf_norte->out_cf_buffer.write(20);
	}
	if (cf_sul->in_val.read() == 1)
	{
		/* EXECUTA ALGUMA COISA AQUI */
		std::cout << "sul" << endl;

	}
	if (cf_leste->in_val.read() == 1)
	{
		std::cout << "leste" << endl;
		/* EXECUTA ALGUMA COISA AQUI */
	}
	if (cf_oeste->in_val.read() == 1)
	{
		//std::cout << "oeste" << endl;
		cf_oeste->out_cf_buffer.write(1);

		//Colocar isso num outro método sensível ao ack

		/* EXECUTA ALGUMA COISA AQUI */
	}
	if (cf_local->in_val.read() == 1)
	{
		std::cout << "local" << endl;
		/* EXECUTA ALGUMA COISA AQUI */
	}

}
	