#include "Data.h"
#include <sstream>
#include <string>

/*
 * Atribui uma data atraves de setters,
 * ja foi verificada antes de entrar nesta classe
 */
Data::Data(int dia, int mes, int ano) {
    set_ano(ano);
    set_mes(mes);
    set_dia(dia);
}

Data::~Data() {}

void Data::set_ano(int ano) {
    this->ano = ano;
}

void Data::set_mes(int mes) {
    if (mes < 13)
        this->mes = mes;
    else if (mes > 12) {
        this->mes = mes - 12;
        this->set_ano(this->get_ano() + 1);
    }
}

void Data::set_dia(int dia) {
    if ( (this->mes == 1 ||
          this->mes == 3 ||
          this->mes == 5 ||
          this->mes == 7 ||
          this->mes == 8 ||
          this->mes == 10 ||
          this->mes == 12) &&
         (dia > 0 && dia < 32) )
        this->dia = dia;

    else if ( (this->mes == 1 ||
               this->mes == 3 ||
               this->mes == 5 ||
               this->mes == 7 ||
               this->mes == 8 ||
               this->mes == 10 ||
               this->mes == 12) &&
               dia > 31 ) {
        this->dia = dia%31;
        this->set_mes(this->get_mes() + 1);
    }

    else if ( (this->mes == 4 ||
               this->mes == 6 ||
               this->mes == 9 ||
               this->mes == 11) &&
              (dia > 0 && dia < 31) )
        this->dia = dia;
    else if ( (this->mes == 4 ||
               this->mes == 6 ||
               this->mes == 9 ||
               this->mes == 11) &&
               dia > 30 ) {
        this->dia = dia%30;
        this->set_mes(this->get_mes() + 1);
    }

    else if (this->mes == 2 &&
             (dia > 0 && dia < 29) )
        this->dia = dia;
    else if (this->mes == 2 && dia > 28 && !bissexto()) {
        this->dia = dia%28;
        this->set_mes(this->get_mes() + 1);
    }
    else if (this->mes == 2 && dia < 30 && bissexto())
        this->dia = dia;
    else if (this->mes == 2 && dia > 29 && bissexto()) {
        this->dia = dia%29;
        this->set_mes(this->get_mes() + 1);
    }
    if (this->dia == 0) this->dia = 1;
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

int Data::toInt() const
{
	return dia+100*mes+10000*ano;
}

bool Data::bissexto () {
    if ((this->ano % 400 == 0 || this->ano % 100 != 0) && this->ano % 4 == 0)
        return true;
    return false;
}
