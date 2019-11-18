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
    //guarda o valor atual em um vetor
    this->listaLancamentos[counter - 1] = valor;
    this->listaDatas[counter - 1] = nova;
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

std::string Lancamentos::toString(int counter, Data inicio, Data fim) const
{
    std::ostringstream lancamentosStr;
    int i;
    lancamentosStr << "Lancamentos da conta, de " << inicio.toString() << " ate " << fim.toString() << ":\n";
    for (i = 0; i < counter; i++) {
        if (listaLancamentos[i] != 0.0f &&
            (listaDatas[i]->get_ano() >= inicio.get_ano() && listaDatas[i]->get_ano() <= fim.get_ano()) ) {
                if (inicio.get_ano() == fim.get_ano()) {
                    if (inicio.get_mes() == fim.get_mes()) {
                        if (inicio.get_dia() <= listaDatas[i]->get_dia() && listaDatas[i]->get_dia() <= fim.get_dia())
                            lancamentosStr << std::fixed << std::setprecision(2) << listaLancamentos[i] << "\n";
                    }
                    else {
                        if ( (inicio.get_dia() <= listaDatas[i]->get_dia() && inicio.get_mes() == listaDatas[i]->get_mes()) ||
                             (fim.get_dia() >= listaDatas[i]->get_dia() && fim.get_mes() == listaDatas[i]->get_mes()) )
                            lancamentosStr << std::fixed << std::setprecision(2) << listaLancamentos[i] << "\n";
                    }
                }
                else {
                    if (inicio.get_mes() == fim.get_mes()) {
                        if (inicio.get_dia() <= listaDatas[i]->get_dia() && listaDatas[i]->get_dia() <= fim.get_dia())
                            lancamentosStr << std::fixed << std::setprecision(2) << listaLancamentos[i] << "\n";
                    }
                    else {
                        if ( (inicio.get_dia() <= listaDatas[i]->get_dia() && inicio.get_mes() == listaDatas[i]->get_mes()) ||
                             (fim.get_dia() >= listaDatas[i]->get_dia() && fim.get_mes() == listaDatas[i]->get_mes()) )
                            lancamentosStr << std::fixed << std::setprecision(2) << listaLancamentos[i] << "\n";
                    }

                }
            }
    }
    return lancamentosStr.str();
}
