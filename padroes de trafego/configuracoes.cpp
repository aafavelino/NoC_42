#include <iostream>
#include <tuple>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{

    ofstream trafego ("../configuracoes.txt");
    trafego << "tmb "<< argv[1] <<", arb " << argv[2]<<", rot "<< argv[3] << endl;



	trafego << endl << endl << endl << "Parâmetros:"<< endl <<
										"1- Tamanho do Buffer > 0"<< endl <<
										"2- Arbitragens: 1: Estática, 2: Rotativa, 3: Randômica"<< endl<<
										"3- Roteamentos: 1: Negative first, 2: XY, 3: North last, 4: West first, 5: Odd even";

										
	return 0;
}