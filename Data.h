#ifndef DATA_H
#define DATA_H

#include <string>

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
    std::string toString() const;
private:
    int dia, mes, ano;
};

#endif /* DATA_H */

