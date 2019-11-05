#ifndef CONTACORRENTE_H
#define CONTACORRENTE_H

#include "Conta.h"

class ContaCorrente : public Conta {
public:
    //Construtor
    ContaCorrente(const std::string, const std::string, const Data, float, 
            float, const std::string, const std::string);
    //Destrutor
    ~ContaCorrente();
    //Setter
    void setLimiteCheque(float);
    //Getter
    float getLimiteCheque() const;
    std::string getCPForCNPJ() const;
    std::string getTipoCliente() const;
    //toString
    virtual std::string toString() const;
    
private:
    const std::string cnpj;
    const std::string tipo_cliente;
    float limite_cheque;
};

#endif /* CONTACORRENTE_H */

