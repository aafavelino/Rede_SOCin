#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {
	REDE *teste = new REDE("rede");

		// teste->injeta_flits(2,1, 0, 2);
		 teste->injeta_flits(1,1, 1, 1);
		// teste->injeta_flits(0,0, 1, 1);
		// teste->injeta_flits(4,4, 0, 4);
		// teste->injeta_flits(4,7, 0, 0);
		// teste->injeta_flits(7,7, 0, 0);
			
	



  	return 0;
}