/* INTEGRANTES DO GRUPO
 * GABRIEL PENAJO 769712
 * JOAO BUENO CALDAS 769657
 * MATHEUS RAMOS  769703
 * MATHEUS MATTIOLI 769783
 */


#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "Conta.h"
#include "Cliente.h"
#include "Banco.h"
#include "ContaCorrente.h"
#include "ContaPoupanca.h"
#include "PessoaFisica.h"
#include "PessoaJuridica.h"

using namespace std;

int main()
{
    int aux, opNum; //atua como opcao
    string num_conta, cpf;
    Banco banco;
    float valor, novolimite;

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
             << " 9- Alterar limite do cheque especial de uma conta corrente" << '\n'
             << "10- Ver todas as contas" << '\n'
             << "11- Ver total de contas" << '\n'
             << "12- Ver total de contas corrente" << '\n'
             << "13- Ver total de contas poupanca" << '\n'
             << "14- Ver total de pessoas fisicas " << '\n'
             << "15- Ver total de pessoas juridicas " << '\n'
             << "16- Ver total de clientes e de contas" << '\n'
             << "17- Ver montante total do banco" << '\n'
             << "18- Terminar o dia atual" << '\n'
			 << "19- Ver extrato da conta" << '\n'
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
              cout << "Digite o novo valor para cheque especial:\n";
              cin >> novolimite;
              banco.change_limit(novolimite);
              cout << '\n';
              break;
            }
            case (10): {
                banco.get_contas();
                cout << '\n';
                break;
            }
            case (11): {
                cout << "Total de contas = " << Conta::num_contas << '\n';
                break;
            }
            case (12): {
                cout << "Total de contas corrente = " << ContaCorrente::count_chain
                        << '\n';
                break;
            }
            case (13): {
                cout << "Total de contas poupanca = " << ContaPoupanca::count_poup
                        << '\n';
                break;
            }
            case (14): {
                cout << "Total de pessoas fisicas = " << PessoaFisica::count_f << '\n';
                break;
            }
            case (15): {
                cout << "Total de pessoas juridicas = " << PessoaJuridica::count_j << '\n';
                break;
            }
            case (16): {
                cout << banco.toString() << '\n';
                break;
            }
            case (17): {
                banco.get_montante();
                cout << '\n';
                break;
            }
            case (18): {
                banco.next_data();
                cout << '\n';
                break;
            }case (19): {
				cout << "Digite o numero da conta:" << '\n';
				cin >> num_conta;
				banco.get_extrato(num_conta);
				cout << '\n';
				break;
			}
            case (0):
                break;
            default:
                cout << "Opcao nao disponivel. Tente novamente." << "\n\n";


        }
    } while (opNum);
    banco.destroy = true;
    banco.~Banco();
    return 0;
}
