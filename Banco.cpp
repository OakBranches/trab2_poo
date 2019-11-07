#include "Banco.h"
#include "Cliente.h"
#include "Conta.h"
#include "ContaCorrente.h"
#include "ContaPoupanca.h"
#include "PessoaFisica.h"
#include "PessoaJuridica.h"
#include "Data.h"
#include <string>
#include <sstream>
#include <iostream>
#include <new>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>

int Banco::contcliente = 0;
int Banco::contconta = 0;

Banco::Banco() {
}

Banco::~Banco() {

    /* Libera todas as contas */
    while (!listaContas.empty()) {
        listaContas.pop_back();
    }

    /* Libera todos os clientes */
    while (!listaClientes.empty()) {
        listaClientes.pop_back();
    }
}

/* Metodos */

void Banco::add_conta()
{
    //Inicializa variaveis da conta;
    std::string numero_conta, data, cpf;
    int dia, mes, ano;
    float saldo;
    
    std::cout << "Digite o numero da conta: " << "\n";
    std::cin >> numero_conta;

    //Cria uma conta nova(se o numero for valido);
    if (is_valid_numConta(numero_conta)) {
        do {
            std::cout << "Digite os dados da conta: " << "\n" << "CPF (ja cadastrado): ";
            std::cin >> cpf;
        } while (buscaClientecpf(cpf) < 0);

        do {
            std::cout << "Data de abertura, no formato: 'dia mes ano': " << "\n";
            std::cin >> dia >> mes >> ano;
        } while (is_valid_data(dia, mes, ano) == false);
        Data datac(dia, mes, ano);
        data = datac.toString();

        std::cout << "Saldo inicial:" << "\n";
        std::cin >> saldo;
        listaContas.push_back( Conta(cpf, numero_conta, data, saldo) );
        contconta++;
    }
    else
        std::cout << "Numero ja utilizado. Tente novamente." << "\n";
}

const bool Banco::is_valid_cnpj(std::string cnpj)
{
    std::string test1 = "/", test2 = "-";
	return (cnpj.find(test1)!= std::string::npos && cnpj.find(test2) != std::string::npos
            && cnpj.size() == 16) ? true : false;
}

void Banco::add_cliente()
{
    int opcaoCliente;
    /* Variaveis para cadastro de cliente */
    std::string cpf, nome, endereco, email, telefone;

    std::cout << "Cadastrando cliente..." << std::endl;
	do {
        std::cout << "Escolha o tipo de cliente: (1- Pessoa Fisica|2- Pessoa Juridica)" << '\n';
		std::cin >> opcaoCliente;
		if (opcaoCliente != 1 && opcaoCliente != 2)
			std::cout << "Opcao indisponivel." << '\n';
	} while (opcaoCliente != 1 && opcaoCliente != 2);

    std::cout << "Cadastrando cliente..." << std::endl << "Insira dados:" << '\n';
    if (opcaoCliente == 1) std::cout << "CPF: ";
    else if (opcaoCliente == 2) std::cout << "CPF do socio majoritario: ";
	do {
		std::cin >> cpf;
		if (!is_valid_cpf(cpf))
			std::cout << "CPF invalido ou ja utilizado. Tente novamente." << '\n';
	} while (!is_valid_cpf(cpf));
	//std::cout << cpf<<std::endl;
	std::cout << "Nome: ";
	scanf("\n");
    std::getline(std::cin, nome);
    //std::cout << email << std::endl;
	std::cout << "Email: ";
	do {
		std::cin >> email;
		if (!is_valid_email(email))
			std::cout << "Email invalido!! Tente novamente" << std::endl;
	} while (!is_valid_email(email));
	//std::cout << nome<<std::endl;
    std::cout << "Telefone: ";
	scanf("\n");
    std::cin >> telefone;
	//std::cout << telefone<<std::endl;
    std::cout << "Endereco: ";
	scanf("\n");
	std::getline(std::cin, endereco);
	//std::cout << endereco<<std::endl;
	if (opcaoCliente == 1)
        listaClientes.push_back( PessoaFisica(nome, cpf, endereco, telefone, email) );
    else if (opcaoCliente == 2) {
        int dia, mes, ano;
        std::string cnpj, ramo, fundacao, contrato;
        do {
            std::cout << "CNPJ (formato: xxxxxxxx/xxxx-xx): ";
            std::cin >> cnpj;
		if (!is_valid_cnpj(cnpj))
			std::cout << "CNPJ invalido ou ja utilizado. Tente novamente." << '\n';
        } while (!is_valid_cnpj(cnpj));

        std::cout << "Ramo de atuacao: ";
        std::getline(std::cin, ramo);
        do {
            std::cout << "Data de fundacao, no formato: 'dia mes ano': ";
            std::cin >> dia >> mes >> ano;
        } while (is_valid_data(dia, mes, ano) == false);
        fundacao = intToStr(dia, mes, ano);

        do {
            std::cout << "Data da ultima atualizacao do contrato social, no formato: 'dia mes ano': ";
            std::cin >> dia >> mes >> ano;
        } while (is_valid_data(dia, mes, ano) == false);
        contrato = intToStr(dia, mes, ano);

        listaClientes.push_back( PessoaJuridica(nome, cpf, endereco, telefone, email,
                                                cnpj, ramo, fundacao, contrato) );
    }
    contcliente++;
}

void Banco::get_clientes()
{
    std::list<Cliente>::iterator itr;
    for (itr = listaClientes.begin(); itr != listaClientes.end(); itr++)
        std::cout << (*itr).toString() << "\n";
}


void Banco::set_cliente(std::string busca)
{
    int numPassos = buscaClientecpf(busca);
    std::list<Cliente>::iterator itr = listaClientes.begin();
    for (int i = 0; i < numPassos; i++)
        itr++;
    std::string nome, endereco, telefone, email;
    std::cout << "Digite os dados do cliente: " << '\n'
              << "Nome: ";
    scanf("\n");
    std::getline(std::cin, nome);
    do {
        std::cout << "Email: ";
        std::cin >> email;
        if (is_valid_email(email) == false)
            std::cout << "Email invalido." << '\n';
    } while (is_valid_email(email) == false);
    std::cout << "Telefone: ";
    std::cin >> telefone;
    std::cout << "Endereco: ";
    scanf("\n");
    std::getline(std::cin, endereco);
    itr->set_cliente(nome, busca, endereco, telefone, email);
}

void Banco::get_contas()
{
    std::list<Conta>::iterator itr;

    for (itr = listaContas.begin(); itr != listaContas.end(); itr++)
        std::cout << itr->toString() << "\n";
}

void Banco::rmv_cliente(std::string retirar) {
    std::list<Cliente>::iterator itr;

    for (itr = listaClientes.begin(); itr != listaClientes.end()
    && itr->get_cpf().compare(retirar) != 0; itr++) {
        ;
    }
    if (itr != listaClientes.end()) {
        listaClientes.erase(itr);
        contcliente--;
    }
}

void Banco::rmv_conta(std::string retirar) {
    std::list<Conta>::iterator itr;

    for (itr = listaContas.begin(); itr != listaContas.end()
    && itr->getNum().compare(retirar) != 0; itr++) {
        ;
    }
    if (itr != listaContas.end()) {
        listaContas.erase(itr);
        contconta--;
    }
}

/* getters de statics */
int Banco::getqtdcliente() {
    return contcliente;
}

int Banco::getqtdconta() {
    return contconta;
}

std::string Banco::toString() const{
    std::stringstream format;
    format << "Quantidade de clientes cadastrados no banco: " << this->contcliente <<
        std::endl << "Quantidade de contas cadastradas: " << this->contconta << std::endl;
    return format.str();
}

//validators//

bool Banco::is_valid_numConta(std::string numero)
{
    std::list<Conta>::iterator itr;
    for (itr = listaContas.begin(); itr != listaContas.end(); itr++)
        if (itr->getNum().compare(numero) == 0)
            return false;
    return true;
}

bool Banco::is_valid_data(int dia, int mes, int ano) {
    if (mes < 1 || mes > 12){
        return false;
    }
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return (dia > 0 && dia < 32) ? true : false;
        case 4: case 6: case 9: case 11:
            return (dia > 0 && dia < 31) ? true : false;
        case 2:
            if (bissexto(ano)) {
                return (dia > 0 && dia < 30) ? true : false;
            }
            return (dia > 0 && dia < 29) ? true : false;
    }
    return false;
}

const bool Banco::is_valid_email(std::string email){
	std::string test1 = "@", test2 = ".";
	return (email.find(test1)!= std::string::npos && email.find(test2) != std::string::npos) ? true : false;
}

const bool Banco::is_valid_cpf(std::string cpf){
	int i, repeated = 0;
	std::list<Cliente>::iterator itr;
	// Procura se h� algum cpf repetido na lista;
	for (i = 0; i < Cliente::num_clientes && itr != listaClientes.end(); i++){
        if(itr->get_cpf() == cpf){
			repeated = 1;
			break;
		}
		itr++;
	}
	return (cpf.length() == 11 && !repeated) ? true : false;
}

//auxiliary functions//
bool Banco::bissexto (int ano) {
    if ((ano % 400 == 0 || ano % 100 != 0) && ano % 4 == 0)
        return true;
    return false;
}
/* Busca cpf na lista de clientes e retorna 1 se encontrou */
int Banco::buscaClientecpf(std::string cpf) {
    std::list<Cliente>::iterator itr;
    int i = 0;
    //procura se o cpf inserido est� cadastrado
	for (itr = listaClientes.begin(); itr != listaClientes.end() && itr->get_cpf().compare(cpf) != 0; itr++) {
		i++;
	}
    if (itr == listaClientes.end()) {
        std::cout << "CPF nao encontrado." << '\n';
        return -1;
    }
    return i;
}

int Banco::buscaContaNum(std::string numeroBusca) {
    std::list<Conta>::iterator itr;
    int i = 0;
    for (itr = listaContas.begin(); itr != listaContas.end() && itr->getNum().compare(numeroBusca) != 0; itr++) {
        i++;
    }
    if (itr == listaContas.end()) {
        std::cout << "Conta nao encontrada." << '\n';
        return -1;
    }
    //retorna o numero de passos, a partir do inicio, ate encontrar a conta
    //com o numero em questao
    return i;
}

void Banco::novoLancamento(std::string numeroBusca, float valor, int operacao)
{
    std::list<Conta>::iterator itr = listaContas.begin();
    int aux = this->buscaContaNum(numeroBusca);
    for (int i = 0; i < aux; i++) {
        itr++;
    }
    if (aux != -1) {
        itr->novoLancamento(valor, operacao);
    }
}

void Banco::get_lancamento(std::string numeroBusca) {
    std::list<Conta>::iterator itr = listaContas.begin();
    int numeroIteracoes = this->buscaContaNum(numeroBusca);

    for (int i = 0; i < numeroIteracoes; i++) {
        itr++;
    }
    if ( numeroIteracoes != -1 )
        itr->getLancamentos();
}

void Banco::get_montante()
{
    std::list<Conta>::iterator itr;
    float montante = 0;
    for (itr = listaContas.begin(); itr != listaContas.end(); itr++) {
        montante += itr->getSaldo();
    }
    std::cout << "Montante do banco: " << std::fixed << std::setprecision(2) << montante << '\n';
}
