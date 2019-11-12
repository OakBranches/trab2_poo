#include "PessoaFisica.h"
#include <string>
#include <iostream>

// Inicializa contador

int PessoaFisica::count_f = 0;

PessoaFisica::PessoaFisica(std::string nome, std::string cpf,
    std::string endereco, std::string telefone, std::string email)
    : Cliente(nome, cpf, endereco, telefone, email)
{
	PessoaFisica::count_f++;
    //ctor
    std::cout <<PessoaFisica::count_f<<"o Cliente do tipo 'Pessoa Fisica' cadastrado." << '\n';
    
}

PessoaFisica::~PessoaFisica()
{
    count_f--;
}
