#include "PessoaFisica.h"
#include <string>
#include <iostream>

PessoaFisica::PessoaFisica(std::string nome, std::string cpf,
    std::string endereco, std::string telefone, std::string email)
    : Cliente(nome, cpf, endereco, telefone, email)
{
    //ctor
    std::cout << "Cliente do tipo 'Pessoa Fisica' cadastrado." << '\n';
}

PessoaFisica::~PessoaFisica()
{
    //dtor
}
