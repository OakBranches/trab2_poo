#ifndef BANCO_H_
#define BANCO_H_

#include <iostream>
#include "Cliente.h"
#include "Conta.h"
#include <string>

typedef struct contas {
    Conta *conta_atual;
    struct contas *prox;
} listaContas;

typedef struct clientes {
    Cliente *cliente_atual;
    struct clientes *prox;
} listaClientes;

/* Classe para gerir o banco. */
class Banco
{
    public:
        Banco();
        ~Banco();
        /* Adiciona e remove clientes/contas. */
        void add_cliente();
        void add_conta();
        void rmv_cliente(listaClientes *);
        void rmv_conta(listaContas *);

        /* M�todo toString */
        std::string toString() const;
        /* getters para membros static */
        static int getqtdcliente();
        static int getqtdconta();
    private:
        listaClientes *clientes; //Lista de clientes;
        listaContas *contas; //Lista de contas;

        static int contcliente;
        static int contconta;

        //validators conta//
        bool is_valid_numConta(std::string);
        bool is_valid_data(int, int, int);

        // Validators cliente
        const bool is_valid_email(std::string);
        const bool is_valid_cpf(std::string);

        //auxiliary functions
        std::string intToStr(int, int, int);
        bool bissexto(int);
        int buscaClientecpf(std::string); //Busca um cpf de cliente cadastrado;
};

#endif /* BANCO_H_ */
