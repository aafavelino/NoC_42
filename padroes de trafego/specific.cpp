#include <iostream>
#include <tuple>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{

    std::tuple<int, int> origem;
    std::tuple<int, int> destino;
	destino = std::make_tuple (stoi(argv[6]),stoi(argv[7]));
    
    int flits = atoi(argv[1]);
    int pacotes = atoi(argv[2]);
    int idlecycles = atoi(argv[3]);
    int prioridade = atoi(argv[4]);

    int tam_rede = atoi(argv[5]);

    ofstream trafego ("../traffic.txt");
    trafego << "tg " << (tam_rede*tam_rede)-1 << endl;

	for (int i = 0; i < tam_rede; ++i)
	{
		for (int j = 0; j < tam_rede; ++j)
		 {


		 			origem = std::make_tuple (i,j);
		 			
		 			if (origem != destino) 			
		 				trafego << i <<" " << j << " " << std::get<0>(destino) << " " << std::get<1>(destino) << " " << pacotes <<" " << flits << " " << idlecycles << " " << prioridade << endl;

		 } 
	}

	trafego << endl << endl << endl << "Parâmetros:"<< endl <<
										"1,2- Tupla do tipo <x,x> origem"<< endl <<
										"3,4- Tupla do tipo <x,x> destino"<< endl<<
										"5- Quantidade de pacotes" << endl <<
										"6- Tamanho do pacote" << endl <<
										"7- Idle Cycles" << endl <<
										"8- Prioridade do pacote" << endl;
	return 0;
}