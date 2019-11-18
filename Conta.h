#ifndef CONTA_H
#define CONTA_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "Data.h"
#include "Lancamentos.h"

class Conta
{
    public:
        /* Construtor e destrutor */
        Conta(const std::string, const std::string, const Data, float);
        ~Conta();

        /* Metodos get */
        std::string getNum() const;
        std::string getCPF() const;
        Data getData() const;
        float getSaldo() const;
	float getSaldo_inicial() const;
        void getLancamentos() const; 
	void getLancamentos(Data,Data) const;//Extrato da conta;
        void printSaldo() const;
        Lancamentos getList();

        /* Metodo toString */
         std::string toString() const;

        /* Metodos set */
		void setSaldo(float);

        virtual void novoLancamento(float, int, Data*);

        /* Contador para numero de contas */
        static int num_contas;
        int counter;
    private:
        Lancamentos lancamentos;
        const std::string cpf;
        const std::string num_conta;
        const Data dataAbertura;
        float saldo_atual;
		float saldo_inicial;
};

#endif // CONTA_H
