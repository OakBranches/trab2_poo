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
        void novoLancamento(float);
        /* getters */
        std::string toString() const;
        int getNumLancamentos() const;

    protected:

    private:
        float** listaLancamentos;
        int* numLancamentos;
};

#endif // LANCAMENTOS_H
