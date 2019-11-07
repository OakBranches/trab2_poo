#ifndef CONTAPOUPANCA_H
#define CONTAPOUPANCA_H

#include "Conta.h"
#include <string>

class ContaPoupanca : public Conta
{
    public:
        ContaPoupanca(const std::string, const std::string, const std::string, float);
        virtual ~ContaPoupanca();

    protected:

    private:

};

#endif // CONTAPOUPANCA_H
