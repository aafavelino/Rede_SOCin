//
// Created by Adelino on 30/11/17.
//

#ifndef _ARBITRO_H_
#define _ARBITRO_H_ 

#include <iostream>
#include <systemc.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "../constantes/constantes.h"


class Arbitro 
{
public:
	sc_uint<32> portaDestino;
	int arquivo[3];
	int buffercircular[5];
	int prioridade;
	int rotatividade = 1;
	int arbitragem = -1;

	Arbitro();
	void addSolicitacao(int);
	void remSolicitacao(int);
	void setPrioridade();
	int checkPrioridade();
	
};

#endif