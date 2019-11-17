#include "Lancamentos.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include<algorithm>

Lancamentos::Lancamentos()
{
	destroid = 0;
	listaLancamentos = new float[100];
}

Lancamentos::~Lancamentos()
{
    //dtor
	if (destroid)
		delete[](listaLancamentos);
}

void Lancamentos::novoLancamento(float valor, int counter)
{
    //guarda o valor atual em um vetor
    this->listaLancamentos[counter - 1] = valor;
}

//toString()
std::string Lancamentos::toString(int counter) const
{
    std::ostringstream lancamentosStr;
    int i;
    lancamentosStr << "Lancamentos da conta:" << "\n";
    for (i = 0; i < counter; i++)
        if (listaLancamentos[i] != 0.00f) {
            lancamentosStr << std::fixed << std::setprecision(2) << listaLancamentos[i] << "\n";
        }
    return lancamentosStr.str();
}
