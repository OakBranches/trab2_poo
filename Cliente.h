#ifndef CLIENTE_H_
#define CLIENTE_H_
#include <string>

class Cliente {
public:
	// Constructors
	Cliente(std::string, std::string, std::string, std::string, std::string);
	~Cliente();

	// Setters
	void set_cliente(std::string, std::string, std::string, std::string, std::string);
	void set_email(std::string);
	void set_telefone(std::string);

	// Getters
	const std::string get_nome();
	const std::string get_cpf();
	const std::string get_endereco();
	const std::string get_telefone();
	const std::string get_email();

	//toString
	virtual std::string toString() const;


	//Static for count number of clients;
	static int num_clientes;

private:
	// Variables
	std::string nome;
	std::string cpf;
	std::string endereco;
	std::string telefone;
	std::string email;

	//Private Setters
	void set_cpf(std::string);
	void set_nome(std::string);
	void set_endereco(std::string);
};

#endif /* CLIENTE_H_ */
