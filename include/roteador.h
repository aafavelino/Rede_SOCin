//
// Created by Adelino on 30/11/17.
//

#ifndef _ROTEADOR_H_
#define _ROTEADOR_H_

#include <iostream>
#include <systemc.h>
#include "arbitro.h"
#include "roteamento.h"
#include "controle_fluxo.h"
#include "controle_fluxo_saida.h"
#include "buffer.h"
#include "flit.h"
#include "pacote.h"
#include <time.h>




SC_MODULE (roteador)
{
	
	//Da comunicação entre roteadores
	sc_signal <int> val_cf_norte_to_sul_wire; //Sai do norte e entra no sul
	sc_signal <int> val_cf_sul_to_norte_wire; //Sai do sul e entra no norte
	sc_signal <int> val_cf_leste_to_oeste_wire; //Sai do leste e entra no oeste
	sc_signal <int> val_cf_oeste_to_leste_wire; //Sai do oeste e entra no leste

	sc_signal <int> ack_cf_norte_to_sul_wire; //Sai do norte e entra no sul
	sc_signal <int> ack_cf_sul_to_norte_wire; //Sai do sul e entra no norte
	sc_signal <int> ack_cf_leste_to_oeste_wire; //Sai do leste e entra no oeste
	sc_signal <int> ack_cf_oeste_to_leste_wire; //Sai do oeste e entra no leste

	std::string name;

	int canal_vt;
	int leste_fila_prio[QT_CANAIS_VIRTUAIS];
	int oeste_fila_prio[QT_CANAIS_VIRTUAIS];
	int norte_fila_prio[QT_CANAIS_VIRTUAIS];
	int sul_fila_prio[QT_CANAIS_VIRTUAIS];
	int local_fila_prio[QT_CANAIS_VIRTUAIS];

	int fila_virtual[QT_CANAIS_VIRTUAIS];

	int canal_norte;
	int canal_sul;
	int canal_leste;
	int canal_oeste;
	int canal_local;



	// Ver isso aqui DEPOISSSS
	Flit in_data; //n+2 data + bop + eop
	Flit out_data; // Saída do roteamento n+2

	// Arbitros
	Arbitro arbitro_norte;
	Arbitro arbitro_sul;
	Arbitro arbitro_leste;
	Arbitro arbitro_oeste;
	Arbitro arbitro_local;
	
	// Roteamentos...
	Roteamento roteamento_norte;
	Roteamento roteamento_sul;
	Roteamento roteamento_leste;
	Roteamento roteamento_oeste;
	Roteamento roteamento_local;

	// Controles de fluxo
	controle_fluxo *cf_norte;
	controle_fluxo *cf_sul;
	controle_fluxo *cf_leste;
	controle_fluxo *cf_oeste;
	
	// Controles de fluxo de saída
	controle_fluxo_saida *cf_saida_norte;
	controle_fluxo_saida *cf_saida_sul;
	controle_fluxo_saida *cf_saida_leste;
	controle_fluxo_saida *cf_saida_oeste;
	
	// Buffers
	Buffer *buffer_norte;
	Buffer *buffer_sul;
	Buffer *buffer_leste;
	Buffer *buffer_oeste;
	Buffer *buffer_local;

	Buffer *buffer_norte_saida;
	Buffer *buffer_sul_saida;
	Buffer *buffer_leste_saida;
	Buffer *buffer_oeste_saida;
	Buffer *buffer_local_entrada;



	void entrada_controle_de_fluxo();
	void entrada_buffer();
	void confirmacao_buffer();
	void execute_retorno_controle_de_fluxo();

	~roteador() {
		free(buffer_norte);
		free(buffer_sul);
		free(buffer_leste);
		free(buffer_oeste);
		free(buffer_local);
		free(buffer_norte_saida);
		free(buffer_sul_saida);
		free(buffer_leste_saida);
		free(buffer_oeste_saida);
		free(buffer_local_entrada);
		free(cf_norte);
		free(cf_sul);
		free(cf_leste);
		free(cf_oeste);
		free(cf_saida_norte);
		free(cf_saida_sul);
		free(cf_saida_leste);
		free(cf_saida_oeste);	
	}

	SC_CTOR(roteador) { 

		for (int i = 0; i < QT_CANAIS_VIRTUAIS; ++i)
		{
			leste_fila_prio[i] = 0;
			oeste_fila_prio[i] = 0;
			norte_fila_prio[i] = 0;
			sul_fila_prio[i] = 0;
			local_fila_prio[i] = 0;

		}

		for (int i = 0; i < QT_CANAIS_VIRTUAIS; ++i)
		{
			fila_virtual[i] = QT_CANAIS_VIRTUAIS - i;
		}

		cf_norte = new controle_fluxo("controle_de_fluxo_buffer_Norte");
		cf_sul = new controle_fluxo("controle_de_fluxo_buffer_Sul");
		cf_leste = new controle_fluxo("controle_de_fluxo_buffer_Leste");
		cf_oeste = new controle_fluxo("controle_de_fluxo_buffer_Oeste");
		
		cf_saida_norte = new controle_fluxo_saida("controle_de_fluxo_saida_Norte");
		cf_saida_sul = new controle_fluxo_saida("controle_de_fluxo_saida_Sul");
		cf_saida_leste = new controle_fluxo_saida("controle_de_fluxo_saida_Leste");
		cf_saida_oeste = new controle_fluxo_saida("controle_de_fluxo_saida_Oeste");
		
		buffer_norte = new Buffer("Buffer_norte");
		buffer_sul = new Buffer("Buffer_sul");
		buffer_leste = new Buffer("Buffer_leste");
		buffer_oeste = new Buffer("Buffer_oeste");
		buffer_local = new Buffer("Buffer_local");

		buffer_norte_saida = new Buffer("Buffer_norte_saida");
		buffer_sul_saida = new Buffer("Buffer_sul_saida");
		buffer_leste_saida = new Buffer("Buffer_leste_saida");
		buffer_oeste_saida = new Buffer("Buffer_oeste_saida");
		buffer_local_entrada = new Buffer("buffer_local_entrada");

		//Ligação dos controles de fluxo internos...
		cf_saida_norte->out_val(val_cf_norte_to_sul_wire);
		cf_saida_norte->out_ack(ack_cf_norte_to_sul_wire);
		cf_saida_sul->out_val(val_cf_sul_to_norte_wire);
		cf_saida_sul->out_ack(ack_cf_sul_to_norte_wire);
		cf_saida_leste->out_val(val_cf_leste_to_oeste_wire);
		cf_saida_leste->out_ack(ack_cf_leste_to_oeste_wire);
		cf_saida_oeste->out_val(val_cf_oeste_to_leste_wire);
		cf_saida_oeste->out_ack(ack_cf_oeste_to_leste_wire);






		SC_METHOD(entrada_controle_de_fluxo);
		sensitive << cf_norte->in_val; 
		sensitive << cf_sul->in_val;
		sensitive << cf_leste->in_val; 
		sensitive << cf_oeste->in_val; 


	}
	
};
#endif