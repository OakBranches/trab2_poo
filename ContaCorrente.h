#ifndef CONTACORRENTE_H
#define CONTACORRENTE_H

#include "Conta.h"

class ContaCorrente : public Conta {
public:
    //Construtor para pessoa fisica
    ContaCorrente(const std::string, const std::string, const Data, float,
            float, const std::string );
    //Construtor para pessoa juridica
    ContaCorrente(const std::string, const std::string, const Data, float,
            float, const std::string, const std::string);
    //Destrutor
    ~ContaCorrente();
    //Setter
    void setLimiteCheque(float);
    //Getter
    float getLimiteCheque() const;
    std::string getCNPJ() const;
    std::string getTipoCliente() const;
    //toString
    virtual std::string toString() const;
	//lancamento
	virtual void novoLancamento(float, int, Data*);
    /* Contador para tipo conta corrente */
    static int count_chain;

private:
    const std::string cnpj;
    const std::string tipo_cliente;
    float limite_cheque;
};

#endif /* CONTACORRENTE_H */

