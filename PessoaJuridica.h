#ifndef PESSOAJURIDICA_H
#define PESSOAJURIDICA_H

#include "Cliente.h"

class PessoaJuridica : public Cliente
{
    public:
        PessoaJuridica(std::string, std::string, std::string, std::string, std::string,
                       std::string, std::string, std::string, std::string);
        ~PessoaJuridica();

        // Setters
        void setPessoaJuridica(std::string, std::string, std::string, std::string);
        // Getter
        std::string getCNPJ() const;
        //toString
        virtual std::string toString() const;

        // Variavel estatica para tipo pessoa juridica
        static int count_j;

    private:
        //variables
        std::string cnpj;
        std::string ramo_atuacao;
        std::string data_fundacao;
        std::string data_contrato;

        //private setters
        void set_cnpj(std::string);
        void set_ramo(std::string);
        void set_fundacao(std::string);
        void set_contrato(std::string);
        void set_nascimento(std::string);
};

#endif // PESSOAJURIDICA_H
