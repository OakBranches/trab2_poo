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

Banco::Banco() {}

Banco::~Banco() {

  /* Libera todas as contas */
  while (!listaContas_p.empty()) {
	  std::list<ContaPoupanca*>::iterator atr;
	  for (atr = listaContas_p.begin(); atr != listaContas_p.end(); atr++) {
		  delete[] * atr;
		  listaContas_p.erase(atr);
	  }
  }
	while (!listaContas_c.empty()) {
		std::list<ContaCorrente*>::iterator tr;
		for (tr = listaContas_c.begin(); tr != listaContas_c.end(); tr++) {
			delete[] * tr;
			listaContas_c.erase(tr);
		}
	}
  /* Libera todos os clientes */
  while (!listaClientes_f.empty()) {
	 std::list<PessoaFisica*>::iterator itr;
	 for (itr = listaClientes_f.begin(); itr != listaClientes_f.end(); itr++)
		 rmv_cliente_f((*itr)->get_cpf());

  }
	while (!listaClientes_j.empty()) {
		std::list<PessoaJuridica*>::iterator it;
		for (it = listaClientes_j.begin(); it != listaClientes_j.end(); it++)
			rmv_cliente_j((*it)->get_cpf());
	}
}

/* M�todos */

bool Banco::is_ContaCorrente() {
	int i;
	do {
		std::cout << "Digite o tipo de Conta: \n1-Conta Corrente|2-Conta Poupanca\n";
		std::cin >> i;
	} while (i != 1 && i != 2);
	return(i == 1);
}

void Banco::novoLancamento(std::string s, float a, int p)
{
	bool i = is_ContaCorrente();
	if (i)
		novoLancamento_c( s,  a,  p);
	else
		novoLancamento_p(s, a, p);
}

bool Banco::is_Juridico() {
	int i;
	do {
		std::cout << "Digite o tipo de Cliente: (1- Pessoa Juridica | 2- Pessoa Fisica)\n";
		std::cin >> i;
	} while (i != 1 && i != 2);
	return(i == 1);
}

void Banco::add_conta_c()
{
  //Inicializa variaveis da conta;
  std::string numero_conta, data, cpf;
  int dia, mes, ano;
  float saldo,limite;
	std::string tipo,cnpj;
	do {
		std::cout << "Pessoa Juridica ou Pessoa Fisica? (j/f)" << "\n";
		std::cin >> tipo;
	} while (tipo[0] != 'j' && tipo[0] != 'f');

  std::cout << "Digite o numero da conta: " << "\n";
  std::cin >> numero_conta;

  //Cria uma conta nova(se o numero for valido);
  if (is_valid_numConta_c(numero_conta)) {
    if (tipo[0] == 'f'){
      do {
          std::cout << "Digite os dados da conta: " << "\n" << "CPF (ja cadastrado): ";
          std::cin >> cpf;
	    } while (buscaCliente_cpf_f(cpf) == -1);
    }
	  if (tipo[0] == 'j') {
      do {
        std::cout << "Digite os dados da conta: " << '\n' << "CPF (ja cadastrado): ";
        std::cin >> cpf;
      } while(buscaCliente_cpf_j(cpf) == -1);
      do {
	      std::cout << "Digite o CNPJ" << "\n" ;
		    std::cin >> cnpj;
      } while (!is_valid_cnpj(cnpj));
	  }
    do {
      std::cout << "Data de abertura, no formato: 'dia mes ano': " << "\n";
      std::cin >> dia >> mes >> ano;
    } while (is_valid_data(dia, mes, ano) == false);
    Data data(dia, mes, ano);
    std::cout << "Limite do cheque especial:" << "\n";
    std::cin >> limite;
    std::cout << "Saldo inicial:" << "\n";
    std::cin >> saldo;
    if (tipo[0] == 'j') 
      listaContas_c.push_back(new ContaCorrente(cpf, numero_conta, data, saldo, limite, cnpj, tipo));
    else 
      listaContas_c.push_back(new ContaCorrente(cpf, numero_conta, data, saldo, limite, tipo));
  }
    else
        std::cout << "Numero ja utilizado. Tente novamente." << "\n";
}

void Banco::rmv_cliente(std::string s)
{
	bool i = is_Juridico();
	if (i)
		rmv_cliente_j(s);
	else
		rmv_cliente_f(s);
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


		std::cout << "Saldo inicial:" << "\n";
		std::cin >> saldo;
		listaContas_p.push_back(new ContaPoupanca(cpf, numero_conta, datac, saldo));
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
    /* Vari�veis para cadastro de cliente */
    std::string cpf, nome, endereco, email, telefone;

    std::cout << "Cadastrando cliente..." << std::endl;
	do {
        std::cout << "Escolha o tipo de cliente: (1- Pessoa Fisica | 2- Pessoa Juridica)" << '\n';
		std::cin >> opcaoCliente;
		if (opcaoCliente != 1 && opcaoCliente != 2)
			std::cout << "Opcao indisponivel." << '\n';
	} while (opcaoCliente != 1 && opcaoCliente != 2);

    std::cout << "Cadastrando cliente..." << std::endl << "Insira dados:" << '\n';
    if (opcaoCliente == 1) std::cout << "CPF: ";
    else if (opcaoCliente == 2) std::cout << "CPF do socio majoritario: ";
	if (opcaoCliente == 1) {
		do {
			std::cin >> cpf;
			if (!is_valid_cpf_f(cpf))
				std::cout << "CPF invalido ou ja utilizado. Tente novamente." << '\n';
		} while (!is_valid_cpf_f(cpf));
	}
	else if (opcaoCliente == 2) {
		do {
			std::cin >> cpf;
			if (!is_valid_cpf_j(cpf))
				std::cout << "CPF invalido ou ja utilizado. Tente novamente." << '\n';
		} while (!is_valid_cpf_j(cpf));
	}
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
        listaClientes_f.push_back(new PessoaFisica(nome, cpf, endereco, telefone, email));
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
        scanf("\n");
        std::getline(std::cin, ramo);
        do {
            std::cout << "Data de fundacao, no formato: 'dia mes ano': ";
            std::cin >> dia >> mes >> ano;
            scanf("\n");
        } while (is_valid_data(dia, mes, ano) == false);
        fundacao = intToStr(dia, mes, ano);

        do {
            std::cout << "Data da ultima atualizacao do contrato social, no formato: 'dia mes ano': ";
            std::cin >> dia >> mes >> ano;
            scanf("\n");
        } while (is_valid_data(dia, mes, ano) == false);
        contrato = intToStr(dia, mes, ano);

        listaClientes_j.push_back(new PessoaJuridica(nome, cpf, endereco, telefone, email,
                                                cnpj, ramo, fundacao, contrato) );
    }
}

void Banco::add_conta()
{
	bool i = is_ContaCorrente();
	if (i)
		add_conta_c();
	else
		add_conta_p();
}

void Banco::get_clientes()
{
	std::cout << "\n\nPESSOAS FISICAS\n\n";
    std::list<PessoaFisica*>::iterator itr;
    for (itr = listaClientes_f.begin(); itr != listaClientes_f.end(); itr++)
        std::cout << (*itr)->toString() << "\n";
	std::cout << "\n\nPESSOAS JURIDICAS\n\n";
	std::list<PessoaJuridica*>::iterator it;
	for (it = listaClientes_j.begin(); it != listaClientes_j.end(); it++)
		std::cout << (*it)->toString() << "\n";
}

void Banco::set_cliente(std::string s)
{
	bool i = is_Juridico();
	if (i)
		set_cliente_j(s);
	else
		set_cliente_f(s);
}

void Banco::set_cliente_f(std::string busca)
{
    int numPassos = buscaCliente_cpf_f(busca);
    std::list<PessoaFisica*>::iterator itr = listaClientes_f.begin();
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
    (*itr)->set_cliente(nome, busca, endereco, telefone, email);
}

void Banco::set_cliente_j(std::string busca)
{
	int numPassos = buscaCliente_cpf_j(busca);
	std::list<PessoaJuridica*>::iterator itr = listaClientes_j.begin();
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
	(*itr)->setPessoaJuridica(cnpj,ramo, fundacao.toString(), contrato.toString());
}

void Banco::get_contas()
{
    std::list<ContaCorrente*>::iterator itr;
	std::cout << "\n\nCONTAS CORRENTES\n\n";
    for(itr = listaContas_c.begin(); itr != listaContas_c.end(); itr++)
        std::cout << (*itr)->toString() << "\n";
	std::list<ContaPoupanca*>::iterator it;
	std::cout << "\n\nCONTAS POUPANCAS\n\n";
	for(it = listaContas_p.begin(); it != listaContas_p.end(); it++)
		std::cout << (*it)->toString() << "\n";
}

void Banco::get_lancamento(std::string s)
{
	bool i = is_ContaCorrente();
	if (i)
		get_lancamento_c(s);
	else
		get_lancamento_p(s);
}

void Banco::rmv_cliente_f(std::string retirar) {
    std::list<PessoaFisica*>::iterator itr;

    for (itr = listaClientes_f.begin(); itr != listaClientes_f.end()
    && (*itr)->get_cpf().compare(retirar) != 0; itr++) {
        ;
    }

    if (itr != listaClientes_f.end()) {
		if (buscaCliente_cpf_f(retirar) != -1)
			std::cout << "nao eh possivel remover, ha contas nao finalizadas\n";
		else {
			delete[] *itr;
			listaClientes_f.erase(itr);
		}
    }
}

void Banco::rmv_cliente_j(std::string retirar) {
	std::list<PessoaJuridica*>::iterator itr;

	for (itr = listaClientes_j.begin(); itr != listaClientes_j.end()
		&& (*itr)->get_cpf().compare(retirar) != 0; itr++) {
		;
	}

	if (itr != listaClientes_j.end()) {
		if (buscaCliente_cpf_j(retirar) != -1)
			std::cout << "nao eh possivel remover, ha contas nao finalizadas\n";
		else {
			delete[] * itr;
			listaClientes_j.erase(itr);
		}
	}
}

void Banco::rmv_conta(std::string retirar) {

	int i;
	std::cout << "Escolha o tipo de conta: (1- Conta Corrente|2- Conta Poupanca)" << '\n';
	std::cin >> i;
	if (i == 2) {
		std::cout << "removendo conta poupanca\n";
		std::list<ContaPoupanca*>::iterator itr;

		for (itr = listaContas_p.begin(); itr != listaContas_p.end()
			&& (*itr)->getNum().compare(retirar) != 0; itr++) {
			;
		}
		if (itr != listaContas_p.end()) {
			delete[] * itr;
			listaContas_p.erase(itr);
		}
		else {
			std::cout << "conta nao encontrada\n";
		}
	}
	else {
		std::list<ContaCorrente*>::iterator it;
		std::cout << "removendo conta corrente\n";
		for (it = listaContas_c.begin(); it != listaContas_c.end()
			&& (*it)->getNum().compare(retirar) != 0; it++) {
			;
		}
		if (it != listaContas_c.end()) {
			delete[] * it;
			listaContas_c.erase(it);
		}else {
			std::cout << "conta nao encontrada\n";
		}
	}

}

/* to String */

std::string Banco::toString() const{
    std::stringstream format;
    format << "Quantidade de clientes cadastrados no banco: " << PessoaFisica::count_f + PessoaJuridica::count_j <<
        std::endl << "Pessoas Fisicas: " << PessoaFisica::count_f << "\nPessoas Juridicas: " << PessoaJuridica::count_j <<
		"\nQuantidade de contas cadastradas: " << ContaCorrente::count_chain + ContaPoupanca::count_poup << std::endl<<
		"\nContas Correntes: "<<ContaCorrente::count_chain<<"\nContas Poupancas: "<<ContaPoupanca::count_poup<< std::endl;
    return format.str();
}

//validators//

bool Banco::is_valid_numConta_c(std::string numero)
{
    std::list<ContaCorrente*>::iterator itr;
    for (itr = listaContas_c.begin(); itr != listaContas_c.end(); itr++)
        if ((*itr)->getNum().compare(numero) == 0)
            return false;
    return true;
}

bool Banco::is_valid_numConta_p(std::string numero)
{
	std::list<ContaPoupanca*>::iterator itr;
	for (itr = listaContas_p.begin(); itr != listaContas_p.end(); itr++)
		if ((*itr)->getNum().compare(numero) == 0)
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
	std::list<PessoaJuridica*>::iterator itr = listaClientes_j.begin();
	// Procura se ha algum cpf repetido na lista;
	for (i = 0; i < PessoaJuridica::count_j; i++){
      if ((*itr)->get_cpf() == cpf){
			  repeated = 1;
			  break;
		  } else if (itr != listaClientes_j.end()) {
        itr++;
      } 
	}
	return (cpf.length() == 11 && !repeated) ? true : false;
}

const bool Banco::is_valid_cpf_f(std::string cpf) {
	int i, repeated = 0;
	std::list<PessoaFisica*>::iterator itr = listaClientes_f.begin();
	// Procura se ha algum cpf repetido na lista;
	for (i = 0; i < PessoaFisica::count_f; i++) {
		if ( (*itr)->get_cpf() == cpf) {
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

int Banco::buscaCliente_cnpj(std::string cnpj) {
	std::list<PessoaJuridica*>::iterator itr;
	int i = 0;
        int flag = 0;
	//procura se o cpf inserido esta cadastrado
	for (itr = listaClientes_j.begin(); itr != listaClientes_j.end() && (*itr)->get_cpf().compare(cnpj) != 0; itr++) {
            if ((*itr)->getCNPJ() == cnpj) {
                flag = 1;
                i++;
                break;
            }
            i++;
	}

	if (itr == listaClientes_j.end() && flag == 0) {
		std::cout << "CNPJ nao encontrado." << '\n';
		return -1;
	}

	return i;
}
/* Busca cpf na lista de clientes e retorna i se encontrou */
int Banco::buscaCliente_cpf_j(std::string cpf) {
    std::list<PessoaJuridica*>::iterator itr;
    int i = 0;
    int flag = 0;
    //procura se o cpf inserido esta cadastrado
	for (itr = listaClientes_j.begin(); itr != listaClientes_j.end() && (*itr)->get_cpf().compare(cpf); itr++) {
            if ((*itr)->get_cpf() == cpf){
                flag = 1;
                i++;
                break;
            }
            i++;
	}

    if (itr == listaClientes_j.end() && flag == 0) {
        std::cout << "CPF nao encontrado." << '\n';
        return -1;
    }

    return i;
}

int Banco::buscaCliente_cpf_f(std::string cpf) {
	std::list<PessoaFisica*>::iterator it = listaClientes_f.begin();
	int j = 0;
  int flag = 0;
	//procura se o cpf inserido esta cadastrado
	for (it = listaClientes_f.begin(); it != listaClientes_f.end() && (*it)->get_cpf().compare(cpf); it++) {
            if ((*it)->get_cpf() == cpf) {
                flag = 1;
                j++;
                break;
            }
            j++;
	}
        
	if (it == listaClientes_f.end() && flag == 0) {
		std::cout << "CPF nao encontrado." << '\n';
		return -1;
	}
	return  j;
}

int Banco::buscaContaNum_c(std::string numeroBusca) {
	std::list<ContaCorrente*>::iterator it;
	int  j = 0;
	int flag = 0;
	for (it = listaContas_c.begin(); it != listaContas_c.end() && (*it)->getNum().compare(numeroBusca) != 0; it++) {
		if ((*it)->getNum().compare(numeroBusca)) {
			flag = 1;
			j++;
			break;
		}
		j++;
	}
	if (it == listaContas_c.end() && !flag) {
		std::cout << "Conta nao encontrada." << '\n';
		return -1;
	}
	//retorna o numero de passos, a partir do inicio, ate encontrar a conta
	//com o numero em questao
	return j;
}

int Banco::buscaContaNum_p(std::string numeroBusca) {
    std::list<ContaPoupanca*>::iterator itr;
    int i = 0;
	int flag = 0;
    for (itr = listaContas_p.begin(); itr != listaContas_p.end() && (*itr)->getNum().compare(numeroBusca) != 0; itr++) {
		if ((*itr)->getNum().compare(numeroBusca)) {
			i++;
			flag = 1;
			break;
		}
        i++;
    }
    if (itr == listaContas_p.end() && !flag) {
        std::cout << "Conta nao encontrada." << '\n';
		return -1;
    }
    //retorna o numero de passos, a partir do inicio, ate encontrar a conta
    //com o numero em quest�o
    return i;
}

void Banco::novoLancamento_c(std::string numeroBusca, float valor, int operacao)
{
    std::list<ContaCorrente*>::iterator itr = listaContas_c.begin();
    int aux = this->buscaContaNum_c(numeroBusca);
    for (int i = 0; i < aux; i++) {
        itr++;
    }
    if (aux != -1) {
        (*itr)->novoLancamento(valor, operacao);
    }
}

void Banco::novoLancamento_p(std::string numeroBusca, float valor, int operacao)
{
	std::list<ContaPoupanca*>::iterator itr = listaContas_p.begin();
	int aux = this->buscaContaNum_p(numeroBusca);
	for (int i = 0; i < aux; i++) {
		itr++;
	}
	if (aux != -1) {
		(*itr)->novoLancamento(valor, operacao);
	}
}

void Banco::get_lancamento_p(std::string numeroBusca) {
    std::list<ContaPoupanca*>::iterator itr = listaContas_p.begin();
    int numeroIteracoes = this->buscaContaNum_p(numeroBusca);
    for (int i = 0; i < numeroIteracoes; i++) {
        itr++;
    }
    if ( numeroIteracoes != -1 )
        (*itr)->getLancamentos();
}

void Banco::get_lancamento_c(std::string numeroBusca) {
	std::list<ContaCorrente*>::iterator itr = listaContas_c.begin();
	int numeroIteracoes = this->buscaContaNum_c(numeroBusca);
	for (int i = 0; i < numeroIteracoes; i++) {
		itr++;
	}
	if (numeroIteracoes != -1)
		(*itr)->getLancamentos();
}

void Banco::get_montante()
{
    std::list<ContaPoupanca*>::iterator itr;
    float montante = 0;
    for (itr = listaContas_p.begin(); itr != listaContas_p.end(); itr++) {
        montante += (*itr)->getSaldo();
    }
	std::list<ContaCorrente*>::iterator it;
	for (it = listaContas_c.begin(); it != listaContas_c.end(); it++) {
		montante += (*it)->getSaldo();
	}
    std::cout << "Montante do banco: " << std::fixed << std::setprecision(2) << montante << '\n';
}

/* funcao para alterar limite do cheque especial em tempo de execucao */

void Banco::change_limit(float novo_limite) {
  std::string numconta;
  int niterador;
  float limiteantigo;
  std::list<ContaCorrente*>::iterator itr = listaContas_c.begin();

  do {
    std::cout << "Insira o numero da conta corrente: " << "(ja cadastrado)\n" 
      << "Se quiser cadastrar uma conta antes, entre com 0 para cancelar a operacao\n"; 
    std::cin >> numconta;
  } while (numconta[0] != '0' && (buscaContaNum_c(numconta)) == -1); 
  niterador = buscaContaNum_c(numconta);
  if (numconta[0] != '0') {
    for (int i = 0; i < niterador; i++) 
      itr++;
    limiteantigo = (*itr)->getLimiteCheque();
    (*itr)->setLimiteCheque(novo_limite);
    
    std::cout << "cheque especial alterado de " << limiteantigo << " para " <<      (*itr)->getLimiteCheque() << '\n';
  }
}
