#include "Cliente.h"
#include <sstream>
#include <iostream>

int Cliente::num_clientes = 0;

/*
*/
Cliente::Cliente(std::string nome, std::string cpf, std::string endereco, std::string telefone, std::string email) {
    num_clientes++;
    set_cliente(nome, cpf, endereco, telefone, email);
}

Cliente::~Cliente() {
    num_clientes--;
}

/* -----Setters------ */
void Cliente::set_cliente(std::string nome, std::string cpf, std::string endereco, std::string telefone, std::string email){
    this->set_nome(nome);
	this->set_endereco(endereco);
	this->set_telefone(telefone);
    this->set_cpf(cpf);
	this->set_email(email);
}

void Cliente::set_nome(std::string nome){
	this->nome = nome;
}

void Cliente::set_cpf(std::string cpf){
	this->cpf = cpf;
}

void Cliente::set_email(std::string email){
	this->email = email;
}

void Cliente::set_endereco(std::string endereco){
	this->endereco = endereco;
}

void Cliente::set_telefone(std::string telefone){
	this->telefone = telefone;
}

/* -----Getters----- */
const std::string Cliente::get_nome(){
	return this->nome;
}

const std::string Cliente::get_cpf(){
	return this->cpf;
}

const std::string Cliente::get_endereco(){
	return this->endereco;
}

const std::string Cliente::get_telefone(){
	return this->telefone;
}

const std::string Cliente::get_email(){
	return this->email;
}

//To string method
std::string Cliente::toString() const
{
	std::stringstream create;
	create << "Nome: " << this->nome << std::endl << "CPF: " << this->cpf << std::endl
		<< "Endereco: " << this->endereco << std::endl << "Telefone: " << this->telefone
		<< std::endl << "Email: " << this->email << std::endl;
	return create.str();
}
