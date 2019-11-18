#ifndef CONTAPOUPANCA_H
#define CONTAPOUPANCA_H

#include "Conta.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
/* Nada eh feito, pois eh a propria classe conta */
class ContaPoupanca : public Conta {
public:
    /* Construtor e destrutor */
    ContaPoupanca(const std::string, const std::string, const Data, float);
    ~ContaPoupanca();
	bool destroy;

    /* Contador para tipo conta poupanca */
    static int count_poup;
private:
};

#endif /* CONTAPOUPANCA_H */

