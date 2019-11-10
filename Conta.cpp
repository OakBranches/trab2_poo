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

/* Contador para n�mero de contas */
int Conta::num_contas = 0;

/* Construtor, inicia lista de lan�amentos,
   inicia parametros,
   incrementa contador;  */
Conta::Conta(std::string CPF, std::string nconta,
            Data data, float saldo) : cpf(CPF),
            num_conta(nconta), dataAbertura(data)
{
    this->saldo_atual = saldo;
    num_contas++;

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

void Conta::printSaldo() const
{
    std::cout << "Saldo atual: " << std::fixed << std::setprecision(2)
              << this->getSaldo() << "\n\n";
}

std::vector<float> Conta::getVector() const
{
    return this->lancamentos;
}

/* Mostra na tela hist�rico de lan�amentos(extrato) */
void Conta::getLancamentos() const
{
    std::vector<float>::iterator itr;
    for (itr = this->lancamentos.begin(); itr != this->lancamentos.end(); itr++) {
        std::cout << "Lancamento: " << std::fixed << std::setprecision(2)
                  << *itr << '\n';
    }
    std::cout << "Saldo final: " << std::fixed
              << std::setprecision(2) << this->getSaldo();
    std::cout << std::endl;
}

/* M�todos set */
void Conta::updateSaldo(float valor, int operacao)
{
    //operacao = 1: credito, operacao = 2: debito.
    if (operacao == 2 && this->saldo_atual - valor >= 0) {
        novoLancamento(valor, operacao);
        this->saldo_atual = this->saldo_atual - valor;
    }
    else if (operacao == 1)
        this->saldo_atual = this->saldo_atual + valor;
}

/* Atualiza a lista de lancamentos */
void Conta::novoLancamento(float valor, int operacao)
{
    //operacao = 1: credito, operacao = 2: debito
    if (operacao == 2 && this->saldo_atual - valor >= 0) {
        this->saldo_atual -= valor;
        valor *= (-1);
        this->lancamentos.push_back(valor);
    }
    else if (operacao == 1 && valor > 0) {
        this->saldo_atual += valor;
        this->lancamentos.push_back(valor);
    }

    else std::cout << "Operacao invalida." << '\n';
}

/* toString */

std::string Conta::toString() const {
    std::stringstream format;
    format << "Apresentando dados da conta..." << std::endl
        << "Numero da conta: " << this->num_conta << std::endl
        << "CPF: " << this->cpf << std::endl << "Data de abertura: " << this->dataAbertura.toString()
        << std::endl << "Saldo atual: " << std::fixed << std::setprecision(2) << this->saldo_atual << std::endl;
    return format.str();
}
