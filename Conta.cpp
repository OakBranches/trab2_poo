#include "Conta.h"
#include "Cliente.h"
#include "Data.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include "Lancamentos.h"
#include <list>

/* Contador para numero de contas */
int Conta::num_contas = 0;

/* Construtor, inicia lista de lancamentos,
   inicia parametros,
   incrementa contador;  */
Conta::Conta(std::string CPF, std::string nconta,
            Data data, float saldo) : cpf(CPF),
            num_conta(nconta), dataAbertura(data)
{
    this->saldo_atual = saldo;
	this->saldo_inicial = saldo;
    num_contas++;
    counter = 0;
    std::cout << "Conta criada com sucesso!" << std::endl;
}

Conta::~Conta(){
    num_contas--;
}

/* Getters */
std::string Conta::getNum() const
{
    return this->num_conta;
}

std::string Conta::getCPF() const
{
    return this->cpf;
}

Data Conta::getData() const
{
    return this->dataAbertura;
}

float Conta::getSaldo() const
{
    return this->saldo_atual;
}

float Conta::getSaldo_inicial() const
{
	return saldo_inicial;
}

void Conta::printSaldo() const
{
    std::cout << "Saldo atual: " << std::fixed << std::setprecision(2)
              << this->getSaldo() << "\n\n";
}

Lancamentos Conta::getList()
{
    return this->lancamentos;
}

/* Mostra na tela historico de lancamentos(extrato) */
void Conta::getLancamentos() const
{
    std::cout << lancamentos.toString(this->counter) << '\n';
    std::cout << "Saldo final: " << std::fixed
              << std::setprecision(2) << getSaldo();
    std::cout << std::endl;
}
void Conta::getLancamentos(Data a, Data j) const
{
	float ni = getSaldo_inicial(),nf;
	int i;
	for (i = 0; i < counter; i++) {
		if (lancamentos.getListL()[i] != 0.00f && a.toInt() > lancamentos.getData()[i]->toInt()) {
			ni += lancamentos.getListL()[i];
		}
	}
	nf = ni;
	std::cout << "Saldo inicial: " << std::fixed
		<< std::setprecision(2)<< ni<<std::endl;
	for (i = 0; i < counter; i++) {
		if (lancamentos.getListL()[i] != 0.00f && j.toInt() >= lancamentos.getData()[i]->toInt() && a.toInt() <= lancamentos.getData()[i]->toInt()) {
			nf+=lancamentos.getListL()[i];
			std::cout << lancamentos.getListL()[i] <<" em "<<lancamentos.getData()[i]->toString()<< std::endl;
		}
	}



	std::cout << "Saldo final: " << std::fixed
		<< std::setprecision(2) << nf;
	std::cout << std::endl;
}

void Conta::setSaldo(float i )
{
	this->saldo_atual =  i;
}



/* Atualiza a lista de lancamentos */
void Conta::novoLancamento(float valor, int operacao, Data* data)
{
    //operacao = 1: credito, operacao = 2: debito
    if (operacao == 2 && this->saldo_atual - valor >= 0) {
        this->saldo_atual -= valor;
        valor *= (-1);
        this->counter++;
        this->getList().novoLancamento(valor, this->counter, data);
    }
    else if (operacao == 1 && valor > 0) {
        this->saldo_atual += valor;
        this->counter++;
        this->getList().novoLancamento(valor, this->counter, data);
    }
	else std::cout << "Operacao invalida." << '\n';
	std::cout << "saldo atual: " << std::fixed << std::setprecision(2) << getSaldo() << std::endl;
}

/* toString */
std::string Conta::toString() const {
    std::stringstream format;
    format << "Apresentando dados da conta..." << std::endl
        << "Numero da conta: " << getNum() << std::endl
        << "CPF: " << getCPF() << std::endl << "Data de abertura: " << getData().toString()
        << std::endl << "Saldo atual: " << std::fixed << std::setprecision(2) << getSaldo() << std::endl;
    return format.str();
}
