#include <systemc.h>
#include <vector>
#include "roteador.h"
#include "system.h"

using namespace std;

int sc_main (int argc, char* argv[]) {
	SYSTEM *teste = new SYSTEM("rede");
	sc_start();
  	return 0;
}