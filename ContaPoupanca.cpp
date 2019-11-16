#include "ContaPoupanca.h"

// Inicializa contador
int ContaPoupanca::count_poup = 0;

ContaPoupanca::ContaPoupanca(std::string CPF, std::string nconta,
            Data data, float saldo) : Conta(CPF, nconta, data, saldo) {
    count_poup++;
    std::cout << "Criando conta poupanca... " << '\n';
	destroy = 0;
}


ContaPoupanca::~ContaPoupanca() {
	if(destroy)
    count_poup--;
}

