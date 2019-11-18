#ifndef LANCAMENTOS_H
#define LANCAMENTOS_H

#include <string>
#include <stdlib.h>

#include "Data.h"

class Lancamentos
{
    public:
        Lancamentos();
        ~Lancamentos();
        /* setters */
        void novoLancamento(float, int, Data*);
        /* getters */
        Data** getData() const;
		float* getListL()const;
        std::string toString(int) const;

    private:
        float* listaLancamentos;
        Data** listaDatas;
		int destroid;
};

#endif // LANCAMENTOS_H
