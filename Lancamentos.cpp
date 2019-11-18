#include "Lancamentos.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include<algorithm>

Lancamentos::Lancamentos()
{
	destroid = 0;
	listaLancamentos = new float[100];
	listaDatas = new Data*[100];
}

Lancamentos::~Lancamentos()
{
    //dtor
	if (destroid) {
		delete[] (listaLancamentos);
        delete[] (listaDatas);
	}
}

void Lancamentos::novoLancamento(float valor, int counter, Data* nova)
{
	Data *dataa = new Data(nova->get_dia(), nova->get_mes(), nova->get_ano());
    //guarda o valor atual em um vetor
    this->listaLancamentos[counter - 1] = valor;
    this->listaDatas[counter - 1] =dataa;
}

Data** Lancamentos::getData()const
{
	return listaDatas;
}

float* Lancamentos::getListL()const
{
	return listaLancamentos;
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

