#include "Lancamentos.h"
#include <sstream>
#include <iomanip>
#include <iostream>



Lancamentos::Lancamentos()
{
	numLancamentos = new int[1];
	*numLancamentos = 0;
	//ctor
	listaLancamentos = new float*[1];
	listaLancamentos[0] = new float[1];
	listaLancamentos[0][0] = 0;
}

Lancamentos::~Lancamentos()
{
    //dtor
	delete[] listaLancamentos[0];
	delete[] listaLancamentos;
	delete numLancamentos;
}

void Lancamentos::novoLancamento(float valor)
{
    //se o valor for valido, ie, maior ou igual a um centavo,
    //guarda o valor atual e aloca uma posicao nova na memoria
    //para o lancamento seguinte e guarda o valor 0 para controle
    if (abs(valor) >= 0.01f) {

		(*numLancamentos)++;
		float* vet = new float[*numLancamentos];
		std::copy_n(this->listaLancamentos[0], *numLancamentos-1, vet);
		delete[] this->listaLancamentos[0];
		this->listaLancamentos[0] = vet;
		this->listaLancamentos[0][*numLancamentos-1] = valor;    

    }
}

int Lancamentos::getNumLancamentos() const
{
    return *this->numLancamentos;
}

//toString()
std::string Lancamentos::toString() const
{
    std::ostringstream lancamentosStr;
    lancamentosStr << "Lancamentos da conta:" << "\n";
    for (int i = 0; i < getNumLancamentos(); i++) {

			lancamentosStr << std::fixed << std::setprecision(2) << listaLancamentos[0][i] << "\n";
    }
    return lancamentosStr.str();
}
