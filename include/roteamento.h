#ifndef _ROTEAMENTO_H_
#define _ROTEAMENTO_H_ 

#include <iostream>
#include "flit.h"
#include <systemc.h>
#include "../constantes/constantes.h"

class Roteamento 
{
public:

	struct cordenada_local
	{
	public:
		int x;
		int y;
	} cordenada;

	struct cordenada_dest
	{
	public:
		int x;
		int y;
	} cordenada_destino;

	int portaDestino; 

	void rotear_xy();
	
};
#endif