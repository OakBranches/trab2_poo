#include "Data.h"
#include <sstream>
#include <string>

/*
 * Atribui uma data atraves de setters,
 * ja foi verificada antes de entrar nesta classe
 */
Data::Data(int dia, int mes, int ano) {
    set_dia(dia);
    set_mes(mes);
    set_ano(ano);
}

Data::~Data() {}

void Data::set_ano(int ano) {
    this->ano = ano;
}

void Data::set_mes(int mes) {
    this->mes = mes;
}

void Data::set_dia(int dia) {
    this->dia = dia;
}

int Data::get_dia() const {
    return this->dia;
}

int Data::get_mes() const {
    return this->mes;
}

int Data::get_ano() const {
    return this->ano;
}

std::string Data::toString() const {
    std::ostringstream aux;
    aux << this->dia << "/" << this->mes << "/" << this->ano;
    return aux.str();
}
