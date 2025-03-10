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
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>

Banco::Banco() {
	int dia, mes, ano;
	listaContas_c = new ContaCorrente*[1];
	listaContas_p = new ContaPoupanca*[1];
	listaClientes_j = new PessoaJuridica*[1];
	listaClientes_f = new PessoaFisica*[1];
	destroy = 0;
    do {
        std::cout << "Por favor, digite a data atual: " << '\n';
        std::cin >> dia >> mes >> ano;
    } while (this->is_valid_data(dia, mes, ano) == false);
    dataAtual = new Data(dia, mes, ano);
    std::cout << "Data atual: " << dataAtual->toString() << '\n';
}

Banco::~Banco() {

    /* Libera todas as contas */
    if (destroy) {
        Lancamentos aux;
        while (ContaPoupanca::count_poup > 0) {
            for (int atr = 0; atr < ContaPoupanca::count_poup; atr++) {
                aux = listaContas_p[atr]->getList();
                aux.destroid = 1;
                aux.~Lancamentos();
                delete  listaContas_p[atr];
            }
        }
        while ((ContaCorrente::count_chain > 0)) {
            for (int tr = 0; tr < ContaCorrente::count_chain; tr++) {
                aux = listaContas_c[tr]->getList();
                aux.destroid = 1;
                aux.~Lancamentos();
                delete listaContas_c[tr];
            }
        }
        /* Libera todos os clientes */
        while (PessoaFisica::count_f > 0) {
            for (int itr = 0; itr < PessoaFisica::count_f; itr++)
                rmv_cliente_f((listaClientes_f[itr])->get_cpf());
        }
        while (PessoaJuridica::count_j > 0) {
            for (int it = 0; it < PessoaJuridica::count_j; it++)
                rmv_cliente_j((listaClientes_j[it])->get_cpf());
        }
    }
}

/* Metodos */

Data* Banco::getData()
{
    return this->dataAtual;
}

void Banco::next_data()
{
    Data* data = getData();
    data->set_dia(data->get_dia() + 1);
    std::cout << "Data atual: " << data->toString() << '\n';
}

bool Banco::is_ContaCorrente() {
	int i;
	do {
		std::cout << "Digite o tipo de Conta: (1- Conta Corrente | 2- Conta Poupanca)\n";
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
            std::cout << "Digite os dados da conta: " << "\n" << "CPF (ja cadastrado), ou '0' (zero) para cancelar: ";
            std::cin >> cpf;
        } while (buscaCliente_cpf_f(cpf) == -1 && cpf.compare("0") != 0);
    }
    if (cpf == "0") return;
    if (tipo[0] == 'j') {
		do {
			std::cout << "Digite os dados da conta: " << '\n' << "CPF (ja cadastrado), ou '0' (zero) para cancelar: ";
			std::cin >> cpf;
		} while(buscaCliente_cpf_j(cpf) == -1 && cpf.compare("0") != 0);
		if (cpf.compare("0") == 0) return;
		do {
			std::cout << "Digite o CNPJ" << "\n" ;
			std::cin >> cnpj;
		  } while (!is_valid_cnpj(cnpj) || buscaCliente_cnpj(cnpj)==-1);
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
	listaContas_c = (ContaCorrente**) realloc(listaContas_c,sizeof(ContaCorrente*)* (ContaCorrente::count_chain + 1));
	ContaCorrente* novalista;
	if (tipo[0] == 'j') {
		novalista = new ContaCorrente(cpf, numero_conta, data, saldo, limite, cnpj, tipo);
	}
	else {
        novalista = new ContaCorrente(cpf, numero_conta, data, saldo, limite, tipo);
	}
	listaContas_c[ContaCorrente::count_chain - 1] = (novalista);
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
			std::cout << "Digite os dados da conta: " << "\n" << "CPF (ja cadastrado), ou '0' (zero) para cancelar: ";
			std::cin >> cpf;
		} while (buscaCliente_cpf_f(cpf) < 0 && cpf.compare("0") != 0);
        if (cpf.compare("0") == 0) return;
		do {
			std::cout << "Data de abertura, no formato: 'dia mes ano': " << "\n";
			std::cin >> dia >> mes >> ano;
		} while (is_valid_data(dia, mes, ano) == false);
		Data datac(dia, mes, ano);
		std::cout << "Saldo inicial:" << "\n";
		std::cin >> saldo;
		int b = ContaPoupanca::count_poup;
		ContaPoupanca* a = new ContaPoupanca(cpf, numero_conta, datac, saldo);
		listaContas_p = (ContaPoupanca**)realloc(listaContas_p, sizeof(ContaPoupanca*) * (ContaPoupanca::count_poup ));
		listaContas_p[ContaPoupanca::count_poup-1] = a;

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
    else if (opcaoCliente == 2) std::cout << "CPF do proprietario(ja cadastrado): ";
	if (opcaoCliente == 1) {
		do {
            std::cin >> cpf;
			if (!is_valid_cpf_f(cpf))
				std::cout << "CPF invalido ou ja utilizado. Tente novamente." << '\n' << "Caso queira cancelar a operacao insira 0\n";
		} while (cpf != "0" && !is_valid_cpf_f(cpf));
	}
	else if (opcaoCliente == 2) {
		do {
            std::cin >> cpf;
			if (cpf != "0" && (!is_valid_cpf_j(cpf) || buscaCliente_cpf_f(cpf) == -1)) {
                std::cout << "CPF invalido ou nao cadastrado. Tente novamente." << '\n';
                std::cout << "Caso queira cancelar a operacao insira 0\n";
			}
		} while (cpf != "0" && (!is_valid_cpf_j(cpf) || buscaCliente_cpf_f(cpf) == -1));
	}
	if (cpf == "0") return;
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
	std::getline(std::cin, telefone);
	//std::cout << telefone<<std::endl;
    std::cout << "Endereco: ";
	scanf("\n");
    std::getline(std::cin, endereco);
    //std::cout << endereco<<std::endl;
	if (opcaoCliente == 1) {
		listaClientes_f = (PessoaFisica * *)realloc(listaClientes_f, sizeof(PessoaFisica*) * (PessoaFisica::count_f + 1));
		PessoaFisica* pessoa =new PessoaFisica(nome, cpf, endereco, telefone, email);
		listaClientes_f[PessoaFisica::count_f - 1] = pessoa;
	}
	else if (opcaoCliente == 2) {
        int dia, mes, ano;
        std::string cnpj, ramo, fundacao, contrato;
        do {
            std::cout << "CNPJ (formato: xxxxxxxx/xxxx-xx): ";
            std::cin >> cnpj;
			if ((!is_valid_cnpj(cnpj) || buscaCliente_cnpj(cnpj) != -1) && cnpj != "0") {
				std::cout << "CNPJ invalido ou ja utilizado. Tente novamente, ou digite 0 para sair." << '\n';
			}
        } while ((!is_valid_cnpj(cnpj) || buscaCliente_cnpj(cnpj) != -1)&& cnpj != "0");
		if (cnpj == "0")
			return;
        std::cout << "Ramo de atuacao: ";
        scanf("\n");
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

        PessoaJuridica *pers = new PessoaJuridica(nome, cpf, endereco, telefone, email, cnpj, ramo, fundacao, contrato) ;
		listaClientes_j = (PessoaJuridica * *)realloc(listaClientes_j, sizeof(PessoaJuridica*) * (PessoaJuridica::count_j));
		listaClientes_j[PessoaJuridica::count_j - 1] = pers;
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
    int itr;
    for (itr = 0; listaClientes_f[itr-1] != listaClientes_f[PessoaFisica::count_f-1]; itr++)
        std::cout << (listaClientes_f[itr])->toString() << "\n";
	std::cout << "\n\nPESSOAS JURIDICAS\n\n";
	int it;
	for (it = 0; listaClientes_j[it-1] != listaClientes_j[PessoaJuridica::count_j-1]; it++)
		std::cout <<listaClientes_j[it]->toString() << "\n";
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
	scanf("\n");
	std::getline(std::cin, telefone);
    std::cout << "Endereco: ";
    scanf("\n");
    std::getline(std::cin, endereco);
    (listaClientes_f[numPassos])->set_cliente(nome, busca, endereco, telefone, email);
}

void Banco::set_cliente_j(std::string busca)
{
	std::string ramo,cnpj;
	int dia, mes, ano;
	std::cout << "Digite os dados do cliente: " << '\n';
	do {
		std::cout << "CNPJ (formato: xxxxxxxx/xxxx-xx): ";
		std::cin >> cnpj;
		if (is_valid_cnpj(cnpj) == false||buscaCliente_cnpj(cnpj)==-1)
			std::cout << "CNPJ invalido." << '\n';
	} while (is_valid_cnpj(cnpj) == false || buscaCliente_cnpj(cnpj) == -1);
	int numPassos = buscaCliente_cnpj(cnpj);
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
	(listaClientes_j[numPassos])->setPessoaJuridica(cnpj,ramo, fundacao.toString(), contrato.toString());
}

void Banco::get_contas()
{
    int itr;
	std::cout << "\n\nCONTAS CORRENTES\n\n";
    for(itr = 0; listaContas_c[itr-1] != listaContas_c[ContaCorrente::count_chain-1]; itr++)
        std::cout << (listaContas_c[itr])->toString() << "\n";
	std::cout << "\n\nCONTAS POUPANCAS\n\n";
	for (itr = 0; listaContas_c[itr-1] != listaContas_c[ContaPoupanca::count_poup - 1]; itr++) {
		std::cout<<listaContas_p[itr]->toString() << std::endl;
	}

}

void Banco::get_lancamento(std::string s)
{
	bool i = is_ContaCorrente();
	if (i)
		get_lancamento_c(s);
	else
		get_lancamento_p(s);
}

void Banco::get_extrato(std::string s )
{
	int dia, mes,ano,b;
	std::cout << "Deseja extrato total?(1-sim|0-nao)\n";
	std::cin >> b;
	Data i(0,0,-10000), f(99,99,99999);
	if (!b) {
		do {
			std::cout << "Insira a data de inicio :\n";
			std::cin >> dia >> mes >> ano;
			if (!is_valid_data(dia, mes, ano))
				std::cout << "\ndata invalida, tente novamente\n";
		} while (!is_valid_data(dia, mes, ano));
		 i = Data(dia, mes, ano);
		do {
			std::cout << "Insira a data de termino :\n";
			std::cin >> dia >> mes >> ano;
			if (!is_valid_data(dia, mes, ano))
				std::cout << "\ndata invalida, tente novamente\n";
		} while (!is_valid_data(dia, mes, ano));
		 f = Data(dia, mes, ano);
		if (ano * 10000 + mes * 100 + dia < i.get_ano() * 10000 + i.get_mes() * 100 + i.get_dia()) {
			std::cout << "Periodo de tempo invalido\n";
			return;
		}
	}
	bool c = is_ContaCorrente();
	if (c)
		get_lancamento_c(s,i,f);
	else
		get_lancamento_p(s,i,f);
}

void Banco::rmv_cliente_f(std::string retirar) {
	int itr, j;
	for (itr = 0; itr < PessoaFisica::count_f && (listaClientes_f[itr])->get_cpf().compare(retirar) != 0; itr++) {
		;
	}
	if (buscaContaCPF_c(retirar) != -1 || buscaContaCPF_p(retirar) != -1) {
		std::cout << "nao eh possivel remover, ha contas nao finalizadas\n";
		return;
	} //ha conta corrente, ou ha conta poupanca associada a esse cpf
	if (itr < PessoaFisica::count_f) {
		for (j = itr; j < PessoaFisica::count_f - 1; j++)
			listaClientes_f[j] = listaClientes_f[j + 1];
		delete listaClientes_f[j];
                if (PessoaFisica::count_f == 0)
                    listaClientes_f = (PessoaFisica * *)realloc(listaClientes_f, sizeof(PessoaFisica*));
                else
                    listaClientes_f = (PessoaFisica * *)realloc(listaClientes_f, sizeof(PessoaFisica*) * (PessoaFisica::count_f));
		std::cout << "Cliente removido com sucesso!!\n";
	}
	else std::cout << "CPF nao cadastrado\n";

}

void Banco::rmv_cliente_j(std::string retirar) {
		int itr, j;

		for (itr = 0; itr < PessoaJuridica::count_j && (listaClientes_j[itr])->get_cpf().compare(retirar) != 0; itr++) {
			;
		}

		if (buscaContaCPF_c(retirar) != -1 || buscaContaCPF_p(retirar) != -1) {
			std::cout << "nao eh possivel remover, ha contas nao finalizadas\n";
			return;
		} //ha conta corrente, ou ha conta poupanca associada a esse cpf

		if (itr < PessoaJuridica::count_j) {
			for (j = itr; j < PessoaJuridica::count_j - 1; j++)
				listaClientes_j[j] = listaClientes_j[j + 1];
			delete listaClientes_j[j];
                        if (PessoaJuridica::count_j == 0)
                            listaClientes_j = (PessoaJuridica * *)realloc(listaClientes_j, sizeof(PessoaJuridica*));
                        else
                            listaClientes_j = (PessoaJuridica * *)realloc(listaClientes_j, sizeof(PessoaJuridica*) * (PessoaJuridica::count_j));
			std::cout << "Cliente removido com sucesso!!\n";
		}
		else std::cout << "CPF nao cadastrado\n";
}

void Banco::rmv_conta(std::string retirar) {

	int i, j;
	std::cout << "Escolha o tipo de conta: (1- Conta Corrente|2- Conta Poupanca)" << '\n';
	std::cin >> i;
	if (i == 1 && ContaCorrente::count_chain > 0) {
		std::cout << "removendo conta corrente\n";
		int itr;

		for (itr = 0; itr < ContaCorrente::count_chain && (listaContas_c[itr])->getNum().compare(retirar) != 0; itr++) {
			;
		}
		if (listaContas_c[itr]->counter != 0) {
			printf("Ha lancamentos nessa conta, nao eh possivel remocao\n");
			return;
		}
		if (itr < ContaCorrente::count_chain) {
			for (j = itr; j < ContaCorrente::count_chain - 1; j++)
				listaContas_c[j] = listaContas_c[j + 1];
			delete listaContas_c[j];
                        if (ContaCorrente::count_chain == 0)
                            listaContas_c = (ContaCorrente * *)realloc(listaContas_c, sizeof(ContaCorrente*));
                        else
                            listaContas_c = (ContaCorrente * *)realloc(listaContas_c, sizeof(ContaCorrente*) * (ContaCorrente::count_chain ));
			std::cout << "Conta removida com sucesso!!\n";
		}
		else {
			std::cout << "conta nao encontrada\n";
		}
	}
	else if (ContaPoupanca::count_poup > 0) {
		int it;
		std::cout << "removendo conta poupanca\n";
		for (it = 0; it < ContaPoupanca::count_poup && (listaContas_p[it])->getNum().compare(retirar) != 0; it++) {
			;
		}
		if (listaContas_p[it]->counter != 0) {
			printf("Ha lancamentos nessa conta, nao eh possivel remocao\n");
			return;
		}
		if (it < ContaPoupanca::count_poup) {
			for (j = it; j < ContaPoupanca::count_poup - 1; j++)
				listaContas_p[j] = listaContas_p[j + 1];
			delete listaContas_p[j];
                        if (ContaPoupanca::count_poup == 0)
                            listaContas_p = (ContaPoupanca * *)realloc(listaContas_p, sizeof(ContaPoupanca*));
                        else
                            listaContas_p = (ContaPoupanca * *)realloc(listaContas_p, sizeof(ContaPoupanca*) * (ContaPoupanca::count_poup));
			std::cout << "Conta removida com sucesso!!\n";
		}
		else {
			std::cout << "conta nao encontrada\n";
		}
	}
    if (ContaPoupanca::count_poup == 0 && ContaCorrente::count_chain == 0) {
        std::cout << "nenhuma conta cadastrada\n";
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
    int itr;
	for (itr = 0; itr < ContaCorrente::count_chain - 1; itr++) {
		if ((listaContas_c[itr])->getNum().compare(numero) == 0)
			return false;
	}
    return true;
}

bool Banco::is_valid_numConta_p(std::string numero)
{
	int itr;
	for (itr = 0; itr < ContaPoupanca::count_poup - 1; itr++) {
		std::cout << "cout\n";
		if (listaContas_p[itr]->getNum().compare(numero) == 0) {
			std::cout << "out\n";
			return false;

		}
	}
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
	return cpf.length() == 11  ;
}

const bool Banco::is_valid_cpf_f(std::string cpf) {
	int i, repeated = 0;
	int itr = 0;
	// Procura se ha algum cpf repetido na lista;
	for (i = 0; i < PessoaFisica::count_f; i++) {
		if ( (listaClientes_f[itr])->get_cpf().compare(cpf)==0) {
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

	int itr;
	int i = 0;
        int flag = 0;
	//procura se o cpf inserido esta cadastrado
	for (itr = 0; (listaClientes_j[itr-1]) != (listaClientes_j[PessoaJuridica::count_j-1]) && (listaClientes_j[itr])->get_cpf().compare(cnpj) != 0; itr++) {
            if ((listaClientes_j[itr])->getCNPJ().compare(cnpj)==0) {
                flag = 1;
                i++;
                break;
            }
            i++;
	}

	if ((listaClientes_j[itr-1]) == (listaClientes_j[ PessoaJuridica::count_j-1 ])&& flag == 0) {
		return -1;
	}

	return i;
}

int Banco::buscaContaCPF_c(std::string cpfBusca) {
	int itr;
	int i = 0;
	int flag = 0;
	for (itr = 0; itr < ContaCorrente::count_chain; itr++) {
		if (listaContas_c[itr]->getCPF().compare(cpfBusca) == 0) {
			i++;
			flag = 1;
			break;
		}
		i++;
	}
	if (itr == ContaCorrente::count_chain && !flag) {
		return -1;
	}
	//retorna o numero de passos, a partir do inicio, ate encontrar a conta
	//com o cpf em questao
	return i;
}

int Banco::buscaContaCPF_p(std::string cpfBusca) {
	int itr;
	int i = 0;
	int flag = 0;
	for (itr = 0; itr < ContaPoupanca::count_poup; itr++) {
		if (listaContas_p[itr]->getCPF().compare(cpfBusca) == 0) {
			i++;
			flag = 1;
			break;
		}
		i++;
	}
	if (itr == ContaPoupanca::count_poup && !flag) {
		return -1;
	}
	//retorna o numero de passos, a partir do inicio, ate encontrar a conta
	//com o cpf em questao
	return i;
}

/* Busca cpf na lista de clientes e retorna i se encontrou */
int Banco::buscaCliente_cpf_j(std::string cpf) {
    int itr;
    int i = 0;
    int flag = 0;
    //procura se o cpf inserido esta cadastrado
	for (itr = 0; itr < PessoaJuridica::count_j; itr++) {
        if ((listaClientes_j[itr])->get_cpf().compare(cpf) == 0){
            flag = 1;
            i++;
            break;
        }
        i++;
	}

    if (listaClientes_j[itr-1] == listaClientes_j[PessoaJuridica::count_j-1] && flag == 0) {
        //std::cout << "CPF nao encontrado." << '\n';
        return -1;
    }

    return i;
}

int Banco::buscaCliente_cpf_f(std::string cpf) {
	int it = 0;
	int j = 0;
    int flag = 0;
	//procura se o cpf inserido esta cadastrado
	for (it = 0; it < PessoaFisica::count_f; it++) {
		if ((listaClientes_f[it])->get_cpf().compare( cpf) == 0) {
                flag = 1;
                j++;
                break;
            }
            j++;
	}

	if (it == PessoaFisica::count_f && flag == 0) {
		//std::cout << "CPF nao encontrado." << '\n';
		return -1;
	}
	return  j;
}

int Banco::buscaContaNum_c(std::string numeroBusca) {
	int it;
	int  j = 0;
	int flag = 0;
	for (it = 0; it < ContaCorrente::count_chain; it++) {
		if ((listaContas_c[it])->getNum().compare(numeroBusca) == 0) {
			flag = 1;
			j++;
			break;
		}
		j++;
	}
	if (it == ContaCorrente::count_chain && !flag) {
		std::cout << "Conta nao encontrada." << '\n';
		return -1;
	}
	//retorna o numero de passos, a partir do inicio, ate encontrar a conta
	//com o numero em questao
	return j;
}

int Banco::buscaContaNum_p(std::string numeroBusca) {
    int itr;
    int i = 0;
	int flag = 0;
    for (itr = 0; itr < ContaPoupanca::count_poup; itr++) {
		if ((listaContas_p[itr])->getNum().compare(numeroBusca)==0) {
			i++;
			flag = 1;
			break;
		}
        i++;
    }
    if (itr == ContaPoupanca::count_poup && !flag) {
        std::cout << "Conta nao encontrada." << '\n';
		return -1;
    }
    //retorna o numero de passos, a partir do inicio, ate encontrar a conta
    //com o numero em quest�o
    return i;
}

void Banco::novoLancamento_c(std::string numeroBusca, float valor, int operacao)
{
    int aux = this->buscaContaNum_c(numeroBusca);
    if (aux != -1) {
        (listaContas_c[aux - 1])->novoLancamento(valor, operacao, getData());
    }
}

void Banco::novoLancamento_p(std::string numeroBusca, float valor, int operacao)
{
	int aux = this->buscaContaNum_p(numeroBusca);
	if (aux != -1) {
		listaContas_p[aux - 1]->novoLancamento(valor, operacao, getData());
	}
}

void Banco::get_lancamento_p(std::string numeroBusca) {
    int numeroIteracoes = this->buscaContaNum_p(numeroBusca);

    if ( numeroIteracoes != -1 )
        (listaContas_p[numeroIteracoes - 1])->getLancamentos();
}
void Banco::get_lancamento_p(std::string numeroBusca,Data i, Data j) {
	int numeroIteracoes = this->buscaContaNum_p(numeroBusca);

	if (numeroIteracoes != -1)
		(listaContas_p[numeroIteracoes - 1])->getLancamentos(i,j);
}

void Banco::get_lancamento_c(std::string numeroBusca) {
	int numeroIteracoes = this->buscaContaNum_c(numeroBusca);
	if (numeroIteracoes != -1)
		(listaContas_c[numeroIteracoes - 1])->getLancamentos();
}
void Banco::get_lancamento_c(std::string numeroBusca, Data i, Data j) {
	int numeroIteracoes = this->buscaContaNum_c(numeroBusca);
	if (numeroIteracoes != -1)
		(listaContas_c[numeroIteracoes - 1])->getLancamentos(i,j);
}

void Banco::get_montante()
{
    int itr;
    float montante = 0;
    for (itr = 0; itr <=ContaPoupanca::count_poup-1; itr++) {
        montante += (listaContas_p[itr])->getSaldo();
    }
	int it;
	for (it = 0; it <=ContaCorrente::count_chain-1; it++) {
		montante += (listaContas_c[it])->getSaldo();
	}
    std::cout << "Montante do banco: " << std::fixed << std::setprecision(2) << montante << '\n';
}

/* funcao para alterar limite do cheque especial em tempo de execucao */

void Banco::change_limit(float novo_limite) {
  std::string numconta;
  int niterador;
  float limiteantigo;
  ContaCorrente* itr = listaContas_c[0];

  do {
    std::cout << "Insira o numero da conta corrente: " << "(ja cadastrado)\n"
      << "Se quiser cadastrar uma conta antes, entre com 0 para cancelar a operacao\n";
    std::cin >> numconta;
  } while (numconta[0] != '0' && (buscaContaNum_c(numconta)) == -1);
  niterador = buscaContaNum_c(numconta);
  if (numconta[0] != '0') {
    for (int i = 0; i < niterador; i++)
      itr++;
    limiteantigo = (itr)->getLimiteCheque();
    (itr)->setLimiteCheque(novo_limite);

    std::cout << "cheque especial alterado de " << limiteantigo << " para " <<      (itr)->getLimiteCheque() << '\n';
  }
}
