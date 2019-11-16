#include "Lancamentos.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include<algorithm>


Lancamentos::Lancamentos()
{
	destroid = 0;
	numLancamentos = new int[1];
	numLancamentos[0] = 0;
	//ctor
	listaLancamentos = new float*[1];
	listaLancamentos[0] = new float[1];
	listaLancamentos[0][0] = 0;
}

Lancamentos::~Lancamentos()
{
    //dtor
	if (destroid) {
		delete[](listaLancamentos[0]);
		delete[](listaLancamentos);
		delete[](numLancamentos);
	}
	
}

void Lancamentos::novoLancamento(float valor)
{
    //se o valor for valido, ie, maior ou igual a um centavo,
    //guarda o valor atual e aloca uma posicao nova na memoria
    //para o lancamento seguinte e guarda o valor 0 para controle
    numLancamentos[0]+=1;
    float* vet = new float[numLancamentos[0]];
	for (int i = 0; i < numLancamentos[0]; i++) {
		vet[i] = listaLancamentos[0][i];
	}
	delete[] this->listaLancamentos[0];
    this->listaLancamentos[0] = vet;
    this->listaLancamentos[0][numLancamentos[0]-1] = valor;

}

int Lancamentos::getNumLancamentos() const
{
    return *(this->numLancamentos);
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
