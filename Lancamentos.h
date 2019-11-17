#ifndef LANCAMENTOS_H
#define LANCAMENTOS_H

#include <string>
#include <stdlib.h>

class Lancamentos
{
    public:
        Lancamentos();
        ~Lancamentos();
        /* setters */
        void novoLancamento(float, int);
        /* getters */
        std::string toString(int) const;
    private:
        float* listaLancamentos;
		int destroid;
};

#endif // LANCAMENTOS_H
