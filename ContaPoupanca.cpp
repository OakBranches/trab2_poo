#include "ContaPoupanca.h"

ContaPoupanca::ContaPoupanca(std::string CPF, std::string nconta,
            std::string data, float saldo) : Conta(CPF, nconta,
                                                   data, saldo)
{
    //ctor
}

ContaPoupanca::~ContaPoupanca()
{
    //dtor
}
