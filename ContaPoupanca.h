#ifndef CONTAPOUPANCA_H
#define CONTAPOUPANCA_H

#include "Conta.h"

class ContaPoupanca : public Conta {
public:
    ContaPoupanca();
    ~ContaPoupanca();
    virtual std::string toString() const;
private:

};

#endif /* CONTAPOUPANCA_H */

