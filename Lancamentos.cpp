#include "Lancamentos.h"
#include <sstream>
#include <iomanip>
#include <iostream>


int Lancamentos::numLancamentos = 0;
//ctor
float* Lancamentos::listaLancamentos = new float[1];
Lancamentos::Lancamentos()
{
   
}

Lancamentos::~Lancamentos()
{
    //dtor
}

void Lancamentos::novoLancamento(float valor)
{
    //se o valor for valido, ie, maior ou igual a um centavo,
    //guarda o valor atual e aloca uma posicao nova na memoria
    //para o lancamento seguinte e guarda o valor 0 para controle
    if (abs(valor) >= 0.01f) {
		this->listaLancamentos[numLancamentos] = valor;
        this->numLancamentos++;
        this->listaLancamentos = (float*) realloc(this->listaLancamentos, numLancamentos);
    }
}

int Lancamentos::getNumLancamentos() const
{
    return this->numLancamentos;
}

//toString()
std::string Lancamentos::toString() const
{
    std::ostringstream lancamentosStr;
    lancamentosStr << "Lancamentos da conta:" << "\n";
    for (int i = 0; i <= getNumLancamentos(); i++) {

			lancamentosStr << std::fixed << std::setprecision(2) << listaLancamentos[i] << "\n";
    }
    return lancamentosStr.str();
}
