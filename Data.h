#ifndef DATA_H
#define DATA_H

#include<cstdlib>
#include<iostream>
#include<string>

class Data {
public:
    Data(int, int, int);
    ~Data();
    void set_dia(int);
    void set_mes(int);
    void set_ano(int);
    int get_dia() const;
    int get_mes() const;
    int get_ano() const;
    int toInt() const;
    std::string toString() const;

private:
    int dia, mes, ano;
    bool bissexto();
};

#endif /* DATA_H */

