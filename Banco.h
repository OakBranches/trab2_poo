#ifndef BANCO_H_
#define BANCO_H_

#include <iostream>
#include "Cliente.h"
#include "Conta.h"
#include <string>
#include <list>

/* Classe para gerir o banco. */
class Banco
{
    public:
        Banco();
        ~Banco();

        /* Adiciona/remove/altera clientes/contas. */
        void add_cliente();
        void add_conta();
        void rmv_cliente(std::string);
        void rmv_conta(std::string);
        void rmv_conta_cpf(std::string);
        void set_cliente(std::string);

        /* M�todo toString */
        std::string toString() const;

        /* getters para membros static */
        static int getqtdcliente();
        static int getqtdconta();

        /* getters para listas */
        void get_clientes();
        void get_contas();
        void get_lancamento(std::string);
        void get_montante();

        //procura uma conta para fazer lancamento
        void novoLancamento(std::string, float, int);


    private:
        /* Lista de clientes e contas, composicao de objetos */
        std::list<Conta> listaContas;
        std::list<Cliente> listaClientes;

        static int contcliente;
        static int contconta;

        //validators conta
        bool is_valid_numConta(std::string);
        bool is_valid_data(int, int, int);

        //validators cliente
        const bool is_valid_email(std::string);
        const bool is_valid_cpf(std::string);
        const bool is_valid_cnpj(std::string);

        //auxiliary functions
        bool bissexto(int);
        int buscaClientecpf(std::string); //Busca um cpf de cliente cadastrado;
        int buscaContaNum(std::string); //Busca a conta com o numero respectivo;
};

#endif /* BANCO_H_ */
