#include <iostream>
using namespace std;

int main() {
    int escolha, op;

    do {
        cout << "\n===== MENU PRINCIPAL =====\n";
        cout << "1 - Usar Lista de Adjacência\n";
        cout << "2 - Usar Matriz de Adjacência\n";
        cout << "3 - Sair\n";
        cout << "Escolha uma opção: ";
        cin >> escolha;

        switch (escolha) {
            case 1:
                do {
                    cout << "\n--- Lista de Adjacência ---\n";
                    cout << "1 - Adicionar aresta\n";
                    cout << "2 - Exibir grafo\n";
                    cout << "3 - Voltar ao menu principal\n";
                    cout << "Escolha: ";
                    cin >> op;

                    switch (op) {
                        case 1:
                            cout << "Opção de adicionar aresta escolhida.\n";
                            break;
                        case 2:
                            cout << "Opção de exibir grafo escolhida.\n";
                            break;
                        case 3:
                            cout << "Voltando ao menu principal...\n";
                            break;
                        default:
                            cout << "Opção inválida! Tente novamente.\n";
                    }
                } while (op != 3);
                break;

            case 2:
                do {
                    cout << "\n--- Matriz de Adjacência ---\n";
                    cout << "1 - Adicionar aresta\n";
                    cout << "2 - Exibir grafo\n";
                    cout << "3 - Voltar ao menu principal\n";
                    cout << "Escolha: ";
                    cin >> op;

                    switch (op) {
                        case 1:
                            cout << "Opção de adicionar aresta escolhida.\n";
                            break;
                        case 2:
                            cout << "Opção de exibir grafo escolhida.\n";
                            break;
                        case 3:
                            cout << "Voltando ao menu principal...\n";
                            break;
                        default:
                            cout << "Opção inválida! Tente novamente.\n";
                    }
                } while (op != 3);
                break;

            case 3:
                cout << "Saindo do programa...\n";
                break;

            default:
                cout << "Opção inválida! Tente novamente.\n";
        }
    } while (escolha != 3);

    return 0;
}