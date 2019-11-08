#include "Banco.h"
#include "Cliente.h"
#include "Conta.h"
#include "PessoaFisica.h"
#include "PessoaJuridica.h"
#include "ContaCorrente.h"
#include "ContaPoupanca.h"
#include "Data.h"
#include <string>
#include <sstream>
#include <iostream>
#include <new>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>

Banco::Banco() {
}

Banco::~Banco() {

    /* Libera todas as contas */
    while (!listaContas_p.empty()) {
        listaContas_p.pop_back();
    }

    /* Libera todos os clientes */
    while (!listaClientes_j.empty()) {
        listaClientes_j.pop_back();
    }

    while (!listaContas_c.empty()) {
		listaContas_c.pop_back();
	}

	/* Libera todos os clientes */
	while (!listaClientes_f.empty()) {
		listaClientes_f.pop_back();
	}
}

/* Métodos */

bool Banco::is_ContaCorrente() {
	int i;
	do {
		std::cout << "Digite o tipo de Conta: \n1-Conta Corrente|2-Conta Poupanca\n";
		std::cin  >> i;
	} while (i != 1 && i != 2);
	return(i == 1);
}

bool Banco::is_Juridico() {
	int i;
	do {
		std::cout << "Digite o tipo de Cliente: \n1-Pessoa Juridica|2-Pessoa Fisica\n";
		std::cin  >> i;
	} while (i != 1 && i != 2);
	return(i == 1);
}

void Banco::add_conta_c()
{
    //Inicializa variáveis da conta;
    std::string numero_conta, data, cpf;
    int dia, mes, ano;
    float saldo;
	std::string tipo,cnpj;
	do {
		std::cout << "Pessoa Juridica: ou Pessoa Fisica? (j/f)" << "\n";
		std::cin >> tipo;
	} while (tipo[0] != 'j' && tipo[0] != 'f');

    std::cout << "Digite o numero da conta: " << "\n";
    std::cin >> numero_conta;

    //Cria uma conta nova(se o numero for valido);
    if (is_valid_numConta_c(numero_conta)) {
        do {
            std::cout << "Digite os dados da conta: " << "\n" << "CPF (ja cadastrado): ";
            std::cin >> cpf;
        } while (buscaCliente_cpf_f(cpf) < 0 || buscaCliente_cpf_j(cpf) < 0);
		if (tipo[0] == 'j') {
			do {
				std::cout << "Digite o CNPJ" << "\n" ;
				std::cin >> cnpj;
			} while (!is_valid_cnpj(cnpj));
		}
        do {
            std::cout << "Data de abertura, no formato: 'dia mes ano': " << "\n";
            std::cin >> dia >> mes >> ano;
        } while (is_valid_data(dia, mes, ano) == false);
        data = intToStr(dia, mes, ano);

        std::cout << "Saldo inicial:" << "\n";
        std::cin >> saldo;
		if (tipo[0] == 'j') {
			listaContas_c.push_back(ContaCorrente(cpf, numero_conta, data, saldo,cnpj,tipo));
		}
		else {
			listaContas_c.push_back(ContaCorrente(cpf, numero_conta, data, saldo,tipo));

		}
    }
    else
        std::cout << "Numero ja utilizado. Tente novamente." << "\n";
}

void Banco::add_conta_p()
{
	//Inicializa variaveis da conta;
	std::string numero_conta, data, cpf;
	int dia, mes, ano;
	float saldo;

	std::cout << "Digite o numero da conta: " << "\n";
	std::cin >> numero_conta;

	//Cria uma conta nova(se o numero for valido);
	if (is_valid_numConta_p(numero_conta)) {
		do {
			std::cout << "Digite os dados da conta: " << "\n" << "CPF (ja cadastrado): ";
			std::cin >> cpf;
		} while (buscaCliente_cpf_f(cpf) < 0);

		do {
			std::cout << "Data de abertura, no formato: 'dia mes ano': " << "\n";
			std::cin >> dia >> mes >> ano;
		} while (is_valid_data(dia, mes, ano) == false);
		Data datac(dia, mes, ano);
		data = datac.toString();

		std::cout << "Saldo inicial:" << "\n";
		std::cin >> saldo;
		listaContas_p.push_back(ContaPoupanca(cpf, numero_conta, data, saldo));
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
    /* Variáveis para cadastro de cliente */
    std::string cpf, nome, endereco, email, telefone;

    std::cout << "Cadastrando cliente..." << std::endl;
	do {
        std::cout << "Escolha o tipo de cliente: (1- Pessoa Fisica|2- Pessoa Juridica)" << '\n';
		std::cin >> opcaoCliente;
		if (opcaoCliente != 1 || opcaoCliente != 2)
			std::cout << "Opcao indisponivel." << '\n';
	} while (opcaoCliente != 1 || opcaoCliente != 2);

    std::cout << "Cadastrando cliente..." << std::endl << "Insira dados:" << '\n';
    if (opcaoCliente == 1) std::cout << "CPF: ";
    else if (opcaoCliente == 2) std::cout << "CPF do socio majoritario: ";
	do {
		std::cin >> cpf;
		if (!is_valid_cpf_j(cpf))
			std::cout << "CPF invalido ou ja utilizado. Tente novamente." << '\n';
	} while (!is_valid_cpf_j(cpf));
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
        listaClientes_f.push_back( PessoaFisica(nome, cpf, endereco, telefone, email) );
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

        listaClientes_j.push_back( PessoaJuridica(nome, cpf, endereco, telefone, email,
                                                cnpj, ramo, fundacao, contrato) );
    }
}

void Banco::get_clientes()
{
	std::cout << "\n\nPESSOAS FISICAS\n\n";
    std::list<PessoaFisica>::iterator itr;
    for (itr = listaClientes_f.begin(); itr != listaClientes_f.end(); itr++)
        std::cout << (*itr).toString() << "\n";
	std::cout << "\n\nPESSOAS JURIDICAS\n\n";
	std::list<PessoaJuridica>::iterator it;
	for (it = listaClientes_j.begin(); it != listaClientes_j.end(); it++)
		std::cout << (*it).toString() << "\n";
}

void Banco::set_cliente_f(std::string busca)
{
    int numPassos = buscaCliente_cpf_f(busca);
    std::list<PessoaFisica>::iterator itr = listaClientes_f.begin();
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

void Banco::set_cliente_j(std::string busca)
{
	int numPassos = buscaCliente_cpf_j(busca);
	std::list<PessoaJuridica>::iterator itr = listaClientes_j.begin();
	for (int i = 0; i < numPassos; i++)
		itr++;
	std::string ramo,cnpj;
	int dia, mes, ano;
	std::cout << "Digite os dados do cliente: " << '\n';
	do {
		std::cout << "CNPJ (formato: xxxxxxxx/xxxx-xx): ";
		std::cin >> cnpj;
		if (is_valid_cnpj(cnpj) == false)
			std::cout << "CNPJ invalido." << '\n';
	} while (is_valid_cnpj(cnpj) == false);
	do {
		std::cout << "Data de Fundacao: \n";
		std::cin >> dia >> mes >> ano;
	} while (!is_valid_data(dia, mes, ano));
	Data fundacao(dia, mes, ano);
	do {
		std::cout << "Data de Contrato: \n";
		std::cin >> dia >> mes >> ano;
	} while (!is_valid_data(dia, mes, ano));
	Data contrato(dia, mes, ano);
	std::cout << "Digite o ramo: \n";
	scanf("\n");
	std::getline(std::cin, ramo);
	itr->set_PessoaJuridica(cnpj,ramo, fundacao.toString(), contrato.toString());
}

void Banco::get_contas()
{
    std::list<ContaCorrente>::iterator itr;
	std::cout << "\n\nCONTAS CORRENTES\n\n"
    for (itr = listaContas_c.begin(); itr != listaContas_c.end(); itr++)
        std::cout << itr->toString() << "\n";
	std::list<ContaPoupanca>::iterator it;
	std::cout<< "\n\nCONTAS POUPANCAS\n\n"
	for (it = listaContas_p.begin(); it != listaContas_p.end(); it++)
		std::cout << it->toString() << "\n";
}

void Banco::rmv_cliente_f(std::string retirar) {
    std::list<PessoaFisica>::iterator itr;

    for (itr = listaClientes_f.begin(); itr != listaClientes_f.end()
    && itr->get_cpf().compare(retirar) != 0; itr++) {
        ;
    }

    if (itr != listaClientes_f.end()) {
		if (buscaCliente_cpf_f(retirar) != -1)
			std::cout << "nao e possivel remover, ha contas nao finalizadas\n";
		else
			listaClientes_f.erase(itr);
    }
}

void Banco::rmv_cliente_j(std::string retirar) {
	std::list<PessoaJuridica>::iterator itr;

	for (itr = listaClientes_j.begin(); itr != listaClientes_j.end()
		&& itr->get_cpf().compare(retirar) != 0; itr++) {
		;
	}

	if (itr != listaClientes_j.end()) {
		if (buscaCliente_cpf_j(retirar) != -1)
			std::cout << "nao e possivel remover, ha contas nao finalizadas\n";
		else
			listaClientes_j.erase(itr);
	}
}

void Banco::rmv_conta(std::string retirar) {

	int i;
	std::cout << "Escolha o tipo de conta: (1- Conta Corrente|2- Conta Poupanca)" << '\n';
	std::cin >> i;
	if (i == 2) {
		std::cout << "removendo conta poupanca\n";
		std::list<ContaPoupanca>::iterator itr;

		for (itr = listaContas_p.begin(); itr != listaContas_p.end()
			&& itr->getNum().compare(retirar) != 0; itr++) {
			;
		}
		if (itr != listaContas_p.end()) {
			listaContas_p.erase(itr);
		}else {
			std::cout << "conta nao encontrada\n";
		}
	}
	else {
		std::list<ContaCorrente>::iterator it;
		std::cout << "removendo conta corrente\n";
		for (it = listaContas_c.begin(); it != listaContas_c.end()
			&& it->getNum().compare(retirar) != 0; it++) {
			;
		}
		if (it != listaContas_c.end()) {
			listaContas_c.erase(it);
		}else {
			std::cout << "conta nao encontrada\n";
		}
	}

}

/* to String */

std::string Banco::toString() const{
    std::stringstream format;
    format << "Quantidade de clientes cadastrados no banco: " << PessoaFisica::count_f+PessoaJuridica::count_j <<
        std::endl << "Pessoas Fisicas: "<< PessoaFisica::count_f<< "\nPessoas Juridicas: " << PessoaJuridica::count_j<<
		"\nQuantidade de contas cadastradas: " << ContaCorrente::count_chain+ContaPoupanca::count_poup << std::endl<<
		"\nContas Correntes: "<<ContaCorrente::count_chain<<"\nContas Poupancas"<<ContaPoupanca::count_poup<< std::endl;
    return format.str();
}

//validators//

bool Banco::is_valid_numConta_c(std::string numero)
{
    std::list<ContaCorrente>::iterator itr;
    for (itr = listaContas_c.begin(); itr != listaContas_c.end(); itr++)
        if (itr->getNum().compare(numero) == 0)
            return false;
    return true;
}

bool Banco::is_valid_numConta_p(std::string numero)
{
	std::list<ContaPoupanca>::iterator itr;
	for (itr = listaContas_p.begin(); itr != listaContas_p.end(); itr++)
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

const bool Banco::is_valid_cpf_j(std::string cpf){
	int i, repeated = 0;
	std::list<PessoaJuridica>::iterator itr;
	// Procura se hï¿½ algum cpf repetido na lista;
	for (i = 0; i < PessoaJuridica::num_clientes && itr != listaClientes_j.end(); i++){
        if(itr->get_cpf() == cpf){
			repeated = 1;
			break;
		}
		itr++;
	}
	return (cpf.length() == 11 && !repeated) ? true : false;
}

const bool Banco::is_valid_cpf_f(std::string cpf) {
	int i, repeated = 0;
	std::list<PessoaFisica>::iterator itr;
	// Procura se hï¿½ algum cpf repetido na lista;
	for (i = 0; i < PessoaFisica::num_clientes && itr != listaClientes_f.end(); i++) {
		if (itr->get_cpf() == cpf) {
			repeated = 1;
			break;
		}
		itr++;
	}
	return (cpf.length() == 11 && !repeated) ? true : false;
}
//auxiliary functions//
std::string Banco::intToStr(int dia, int mes, int ano) {
    std::stringstream change;
    std::string aux;
    change << dia << "/" << mes << "/" << ano;
    change >> aux;
    return aux;
}

bool Banco::bissexto (int ano) {
    if ((ano % 400 == 0 || ano % 100 != 0) && ano % 4 == 0)
        return true;
    return false;
}

int Banco::buscaCliente_cnpj(std::string cpf) {
	std::list<PessoaJuridica>::iterator itr;
	int i = 0;
	//procura se o cpf inserido estï¿½ cadastrado
	for (itr = listaClientes_j.begin(); itr != listaClientes_j.end() && itr->get_cpf().compare(cpf) != 0; itr++) {
		i++;
	}
	
	if (itr == listaClientes_j.end() ) {
		std::cout << "CNPJ nao encontrado." << '\n';
		return -1;
	}

	return i;
}
/* Busca cpf na lista de clientes e retorna 1 se encontrou */
int Banco::buscaCliente_cpf_j(std::string cpf) {
    std::list<PessoaJuridica>::iterator itr;
    int i = 0;
    //procura se o cpf inserido estï¿½ cadastrado
	for (itr = listaClientes_j.begin(); itr != listaClientes_j.end() && itr->get_cpf().compare(cpf) != 0; itr++) {
		i++;
	}
	
    if (itr == listaClientes_j.end()) {
        std::cout << "CPF nao encontrado." << '\n';
        return -1;
    }

    return i;
}

int Banco::buscaCliente_cpf_f(std::string cpf) {

	std::list<PessoaFisica>::iterator it;
	int j = 0;
	//procura se o cpf inserido estï¿½ cadastrado
	for (it = listaClientes_f.begin(); it != listaClientes_f.end() && it->get_cpf().compare(cpf) != 0; it++) {
		j++;
	}
	if (it == listaClientes_f.end()) {
		std::cout << "CPF nao encontrado." << '\n';
		return -1;
	}

	return  j;
}

int Banco::buscaContaNum_c(std::string numeroBusca) {
	std::list<ContaCorrente>::iterator it;
	int  j = 0;
	for (it = listaContas_c.begin(); it != listaContas_c.end() && it->getNum().compare(numeroBusca) != 0; it++) {
		j++;
	}
	if ( it == listaContas_c.end()) {
		std::cout << "Conta nao encontrada." << '\n';
		return -1;
	}
	//retorna o numero de passos, a partir do inicio, ate encontrar a conta
	//com o numero em questao
	return j;
}

int Banco::buscaContaNum_p(std::string numeroBusca) {
    std::list<ContaPoupanca>::iterator itr;
	std::list<ContaCorrente>::iterator it;
    int i = 0;
    for (itr = listaContas_p.begin(); itr != listaContas_p.end() && itr->getNum().compare(numeroBusca) != 0; itr++) {
        i++;
    }
    if (itr == listaContas_p.end()) {
        std::cout << "Conta nao encontrada." << '\n';
		return -1;
    }
    //retorna o numero de passos, a partir do inicio, até encontrar a conta
    //com o numero em questão
    return i;
}

void Banco::novoLancamento_c(std::string numeroBusca, float valor, int operacao)
{
    std::list<ContaCorrente>::iterator itr = listaContas_c.begin();
    int aux = this->buscaContaNum_c(numeroBusca);
    for (int i = 0; i < aux; i++) {
        itr++;
    }
    if (aux != -1) {
        itr->novoLancamento(valor, operacao);
    }
}

void Banco::novoLancamento_c(std::string numeroBusca, float valor, int operacao)
{
	std::list<ContaCorrente>::iterator itr = listaContas_c.begin();
	int aux = this->buscaContaNum_p(numeroBusca);
	for (int i = 0; i < aux; i++) {
		itr++;
	}
	if (aux != -1) {
		itr->novoLancamento(valor, operacao);
	}
}

void Banco::get_lancamento_p(std::string numeroBusca) {
    std::list<ContaPoupanca>::iterator itr = listaContas_p.begin();
    int numeroIteracoes = this->buscaContaNum_p(numeroBusca);

    for (int i = 0; i < numeroIteracoes; i++) {
        itr++;
    }
    if ( numeroIteracoes != -1 )
        itr->getExtrato();
}

void Banco::get_lancamento_c(std::string numeroBusca) {
	std::list<ContaCorrente>::iterator itr = listaContas_c.begin();
	int numeroIteracoes = this->buscaContaNum_c(numeroBusca);

	for (int i = 0; i < numeroIteracoes; i++) {
		itr++;
	}
	if (numeroIteracoes != -1)
		itr->getLancamentos();
}

void Banco::get_montante()
{
    std::list<ContaPoupanca>::iterator itr;
    float montante = 0;
    for (itr = listaContas_p.begin(); itr != listaContas_p.end(); itr++) {
        montante += itr->getSaldo();
    }
	std::list<ContaCorrente>::iterator it;
	for (it = listaContas_c.begin(); it != listaContas_c.end(); it++) {
		montante += it->getSaldo();
	}
    std::cout << "Montante do banco: " << std::fixed << std::setprecision(2) << montante << '\n';
}
