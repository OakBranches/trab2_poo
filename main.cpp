#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <list>

#include "Conta.h"
#include "Cliente.h"
#include "Banco.h"

using namespace std;

int main()
{
    int aux, opNum; //atua como op��o
    string num_conta, cpf;
    Banco banco;
    float valor;

    do {
        cout << "O que deseja fazer?" << '\n'
             << " 1- Adicionar um cliente" << '\n'
             << " 2- Alterar os dados de um cliente" << '\n'
             << " 3- Remover um cliente" << '\n'
             << " 4- Ver os clientes cadastrados" << '\n'
             << " 5- Adicionar uma conta" << '\n'
             << " 6- Remover uma conta" << '\n'
             << " 7- Fazer um lancamento" << '\n'
             << " 8- Ver os lancamentos de uma conta" << '\n'
             << " 9- Ver todas as contas" << '\n'
             << "10- Ver total de clientes e de contas" << '\n'
             << "11- Ver montante total do banco" << '\n'
             << " 0- Sair" << '\n';
        cin >> opNum;
        cout << '\n';
        switch (opNum) {
            case (1): {
                banco.add_cliente();
                cout << '\n';
                break;
            }
            case (2): {
                cout << "Digite o CPF:" << '\n';
                cin >> cpf;
                banco.set_cliente(cpf);
                cout << '\n';
                break;
            }
            case (3): {
                cout << "Digite o CPF:" << '\n';
                cin >> cpf;
                banco.rmv_cliente(cpf);
                cout << '\n';
                break;
            }
            case (4): {
                banco.get_clientes();
                if (PessoaFisica::count_f+PessoaJuridica::count_j == 0) {
                    cout << "Nenhum cliente cadastrado. Deseja cadastrar um novo? (1- sim | 0- nao)" << '\n';
                    cin >> aux;
                    if (aux)
                        banco.add_cliente();
                }
                cout << '\n';
                break;
            }
            case (5): {
                banco.add_conta();
                cout << '\n';
                break;
            }
            case (6): {
                cout << "Digite o numero da conta:" << '\n';
                cin >> num_conta;
                banco.rmv_conta(num_conta);
                cout << '\n';
                break;
            }
            case (7): {
                cout << "Digite o numero da conta:" << '\n';
                cin >> num_conta;
                cout << "Digite o tipo de lancamento: (1- credito | 2- debito)" << '\n';
                cin >> aux;
                cout << "Digite o valor do lancamento:" << '\n';
                cin >> valor;
                banco.novoLancamento(num_conta, valor, aux);
                cout << '\n';
                break;
            }
            case (8): {
                cout << "Digite o numero da conta:" << '\n';
                cin >> num_conta;
                banco.get_lancamento(num_conta);
                cout << '\n';
                break;
            }
            case (9): {
                banco.get_contas();
                cout << '\n';
                break;
            }
            case (10): {
                cout << banco.toString() << '\n';
                break;
            }
            case (11): {
                banco.get_montante();
                cout << '\n';
                break;
            }
            case (0):
                break;
            default:
                cout << "Opcao nao disponivel. Tente novamente." << "\n\n";
        }
    } while (opNum);
    return 0;
}
