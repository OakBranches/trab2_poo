#include "PessoaJuridica.h"

#include <string>
#include <sstream>
#include <iostream>


//Inicializar variavel estatica
int PessoaJuridica::count_j = 0;

PessoaJuridica::PessoaJuridica(std::string nome, std::string cpf,
    std::string endereco, std::string telefone, std::string email,
    std::string cnpj, std::string ramo, std::string data_fundacao,
    std::string data_contrato)
    : Cliente(nome, cpf, endereco, telefone, email)
{
    //ctor
    this->setPessoaJuridica(cnpj, ramo, data_fundacao, data_contrato);
    std::cout << "Cliente do tipo 'Pessoa Juridica' cadastrado." << '\n';
    count_j++;
}

PessoaJuridica::~PessoaJuridica()
{
    //dtor
    count_j--;
}

/* -setters- */
void PessoaJuridica::setPessoaJuridica(std::string cnpj, std::string ramo,
                       std::string fundacao, std::string contrato)
{
    this->set_cnpj(cnpj);
    this->set_ramo(ramo);
    this->set_fundacao(fundacao);
    this->set_contrato(contrato);
}

void PessoaJuridica::set_cnpj(std::string cnpj)
{
    this->cnpj = cnpj;
}

void PessoaJuridica::set_ramo(std::string ramo)
{
    this->ramo_atuacao = ramo;
}

void PessoaJuridica::set_fundacao(std::string fundacao)
{
    this->data_fundacao = fundacao;
}

void PessoaJuridica::set_contrato(std::string contrato)
{
    this->data_contrato = contrato;
}

std::string PessoaJuridica::toString() const {
    std::ostringstream change;
    change << Cliente::toString() << "CNPJ: " << this->cnpj << std::endl << "Ramo de atuacao: "
            << this->ramo_atuacao << std::endl << "Data de fundacao: " << this->data_fundacao
            << std::endl << "Data de contrato: " << this->data_contrato << std::endl;
    return change.str();
}
