#ifndef BANCO_H_
#define BANCO_H_

#include <iostream>
#include "Cliente.h"
#include "Conta.h"
#include "ContaCorrente.h"
#include "ContaPoupanca.h"
#include "PessoaFisica.h"
#include "PessoaJuridica.h"
#include "Data.h"
#include <string>
#include <list>

/* Classe para gerir o banco. */
class Banco
{
    public:
        Banco();
        ~Banco();

        /* Adiciona/remove/altera clientes/contas/datas. */
        void add_cliente();
        void add_conta();
        void next_data();

        void add_conta_p();
        void add_conta_c();
        void rmv_cliente(std::string);

        void rmv_cliente_f(std::string);
        void rmv_cliente_j(std::string);

        void rmv_conta(std::string);

        void set_cliente(std::string);
        void set_cliente_f(std::string);
        void set_cliente_j(std::string);

        /* Método toString */
        std::string toString() const;

        /* getters para listas */
        void get_clientes();
        void get_contas();
        void get_lancamento(std::string);
        void get_lancamento_c(std::string);
        void get_lancamento_p(std::string);
        void get_montante();
        bool is_Juridico();
        bool is_ContaCorrente();
        /* Alterar limite do cheque especial em tempo de execucao */
        void change_limit(float);
        //procura uma conta para fazer lancamento
        void novoLancamento(std::string, float, int);

        void novoLancamento_c(std::string, float, int);
        void novoLancamento_p(std::string, float, int);
        /* Lista de clientes e contas, composicao de objetos */
        ContaCorrente** listaContas_c;
        ContaPoupanca** listaContas_p;
        PessoaJuridica** listaClientes_j;
        PessoaFisica** listaClientes_f;

    private:
        Data* dataAtual;

        //validators conta
        bool is_valid_numConta_c(std::string);
        bool is_valid_numConta_p(std::string);
        bool is_valid_data(int, int, int);
        bool destroy;

        //validators cliente
        const bool is_valid_email(std::string);
        const bool is_valid_cpf_j(std::string);
        const bool is_valid_cpf_f(std::string);
        const bool is_valid_cnpj(std::string);

        //auxiliary functions
        Data* getData();
        std::string intToStr(int, int, int);
        bool bissexto(int);
        int buscaCliente_cpf_j(std::string);
        int buscaCliente_cpf_f(std::string);
        int buscaContaNum_p(std::string);    //Busca a conta com o numero respectivo;
        int buscaContaCPF_c(std::string);
        int buscaContaCPF_p(std::string);
        int buscaCliente_cnpj(std::string); //Busca um cnpj de cliente cadastrado;
        int buscaContaNum_c(std::string);
};

#endif /* BANCO_H_ */
