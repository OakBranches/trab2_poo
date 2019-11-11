#ifndef CONTAPOUPANCA_H
#define CONTAPOUPANCA_H

#include "Conta.h"
/* Nada eh feito, pois eh a propria classe conta */
class ContaPoupanca : public Conta {
public:
    /* Construtor e destrutor */
    ContaPoupanca(const std::string, const std::string, const Data, float);
    ~ContaPoupanca();

    /* Contador para tipo conta poupanca */
    static int count_poup;
private:
};

#endif /* CONTAPOUPANCA_H */

