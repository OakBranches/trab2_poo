#include "Conta.h"
#include "Cliente.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <sstream>
#include <list>

/* Contador para número de contas */
int Conta::num_contas = 0;

/* Construtor, inicia lista de lançamentos,
   inicia parametros,
   incrementa contador;  */
Conta::Conta(std::string CPF, std::string nconta,
            std::string data, float saldo) : cpf(CPF),
            num_conta(nconta), data_abertura(data)
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

std::string Conta::getData() const
{
    return this->data_abertura;
}

float Conta::getSaldo()
{
    return this->saldo_atual;
}

void Conta::printSaldo()
{
    std::cout << "Saldo atual: " << std::fixed << std::setprecision(2)
              << this->getSaldo() << "\n\n";
}

Lancamentos Conta::getLancamentos()
{
    return this->lancamentos;
}

/* Mostra na tela histórico de lançamentos(extrato) */
void Conta::getExtrato()
{
    std::cout << this->lancamentos.toString();
    std::cout << "Saldo final: " << std::fixed
              << std::setprecision(2) << this->getSaldo();
    std::cout << std::endl;
}

/* Métodos set */
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
        this->lancamentos.novoLancamento(valor);
    }
    else if (operacao == 1 && valor > 0) {
        this->saldo_atual += valor;
        this->lancamentos.novoLancamento(valor);
    }

    else std::cout << "Operacao invalida." << '\n';
}

/* toString */

std::string Conta::toString() const {
    std::stringstream format;
    format << "Apresentando dados da conta..." << std::endl
        << "Numero da conta: " << this->num_conta << std::endl
        << "CPF: " << this->cpf << std::endl << "Data de abertura: " << this->data_abertura
        << std::endl << "Saldo atual: " << std::fixed << std::setprecision(2) << this->saldo_atual << std::endl;
    return format.str();
}
