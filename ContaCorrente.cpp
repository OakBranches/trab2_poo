#include "ContaCorrente.h"
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

/* Inicializacao da variavel estatica */
int ContaCorrente::count_chain = 0;

/* Construtor para tipo pessoa física */
ContaCorrente::ContaCorrente(string CPF, string nconta,
                            Data data, float saldo,
                            float limite, string tipo) : Conta(CPF,
                            nconta, data, saldo), tipo_cliente(tipo) {
    setLimiteCheque(limite);
    count_chain++;
    cout << "Criando conta corrente para pessoa fisica... " << '\n';
}

/* Construtor para tipo pessoa juridica */
ContaCorrente::ContaCorrente(string CPF, string nconta,
                            Data data, float saldo,
                            float limite, string CNPJ, string tipo)
                            : Conta(CPF, nconta, data, saldo),
                            tipo_cliente(tipo), cnpj(CNPJ) {
    setLimiteCheque(limite);
    count_chain++;
    cout << "Criando conta corrente para pessoa juridica... " << '\n';
}

/* Destrutor */
ContaCorrente::~ContaCorrente() {
    count_chain--;
}

/* Setter para limite do cheque especial */
void ContaCorrente::setLimiteCheque(float limite) {
    this->limite_cheque = (limite < 0) ? limite : 0;
}

/* Getters para atributos de conta corrente */
float ContaCorrente::getLimiteCheque() const {
    return this->limite_cheque;
}

string ContaCorrente::getTipoCliente() const {
    return this->tipo_cliente;
}

string ContaCorrente::getCNPJ() const {
    return this->cnpj;
}

/* toString */

string ContaCorrente::toString() const {
    ostringstream aux;
    if (tipo_cliente == "j") {
        aux << "Apresentando dados da conta..." << std::endl
            << "Tipo de conta: " << this->tipo_cliente
            << std::endl << "Numero da conta: " << this->getNum()<< std::endl
            << "CNPJ: " << this->cnpj << std::endl << "CPF: " << this->getCPF() << std::endl << "Data de abertura: " << "this->getData()"
            << std::endl << "Saldo atual: " << std::fixed << std::setprecision(2) << this->getSaldo() << std::endl
            << std::fixed << std::setprecision(2) << this->limite_cheque << endl;
    } else {
        aux << "Tipo de conta: " << this->tipo_cliente << Conta::toString()
                << std::fixed << std::setprecision(2) << this->limite_cheque << endl;
    }
    return aux.str();
}

void ContaCorrente::novoLancamento(float valor, int operacao)
{
	//operacao = 1: credito, operacao = 2: debito
	if (operacao == 2 && getSaldo() - valor >= getLimiteCheque() && valor >= 0) {
		setSaldo(getSaldo() - valor);
		valor *= (-1);
		this->getList().novoLancamento(valor);
	}
	else if (operacao == 1 && valor > 0){
		setSaldo(getSaldo() + valor);
		this->getList().novoLancamento(valor);
	}
	else std::cout << "Operacao invalida." << '\n';
	std::cout << "saldo atual :" << getSaldo() << std::endl;
}
