#ifndef PESSOAFISICA_H
#define PESSOAFISICA_H

#include "Cliente.h"

class PessoaFisica : public Cliente
{
    public:
        PessoaFisica(std::string, std::string, std::string, std::string, std::string);
        ~PessoaFisica();

    protected:

    private:
};

#endif // PESSOAFISICA_H
