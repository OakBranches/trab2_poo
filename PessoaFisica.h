#ifndef PESSOAFISICA_H
#define PESSOAFISICA_H

#include "Cliente.h"

class PessoaFisica : public Cliente
{
    public:
        PessoaFisica(std::string, std::string, std::string, std::string, std::string);
        ~PessoaFisica();

        /* Contador para tipo pessoa fisica */
        static int count_f;

    protected:

    private:
};

#endif // PESSOAFISICA_H
