// Trabalho 1 - EDB1 (DIM0119)
// Exercicio 7: Busca Ternaria Iterativa
// Autor: Otávio Felipe

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Busca ternaria: parecida com a binaria, mas divide o vetor em 3 partes por passo
int buscaTernaria(int A[], int esq, int dir, int chave) {
    // Continua enquanto o intervalo [esq, dir) ainda tiver elementos
    while (esq < dir) {
        // Calcula quantos elementos existem no intervalo atual
        int tamanho = dir - esq;

        // m1 e o primeiro ponto de corte (aproximadamente 1/3 do intervalo)
        int m1 = esq + tamanho / 3;
        // m2 e o segundo ponto de corte (aproximadamente 2/3 do intervalo)
        int m2 = esq + (2 * tamanho) / 3;

        // Verifica se a chave esta em um dos dois pontos de corte
        if (A[m1] == chave) {
            return m1;  // achou no primeiro ponto
        }
        if (A[m2] == chave) {
            return m2;  // achou no segundo ponto
        }

        // Compara a chave com os dois pontos de corte para decidir
        // qual dos 3 "tercos" do vetor deve continuar sendo buscado
        if (chave < A[m1]) {
            // a chave, se existir, esta no primeiro terco (antes de m1)
            dir = m1;
        } else if (chave < A[m2]) {
            // a chave, se existir, esta no terco do meio (entre m1 e m2)
            esq = m1 + 1;
            dir = m2;
        } else {
            // a chave, se existir, esta no ultimo terco (depois de m2)
            esq = m2 + 1;
        }
        // o laco while volta a testar a condicao com os novos valores de esq/dir
    }
    // se o laco terminou, o intervalo ficou vazio: nao encontrou a chave
    return -1;
}

int main() {
    int n;                  // tamanho do vetor
    cin >> n;               // le o tamanho

    vector<int> A(n);        // cria o vetor
    for (int i = 0; i < n; i++) {
        cin >> A[i];          // le cada elemento (ja ordenado)
    }

    int chave;                // valor procurado
    cin >> chave;              // le a chave

    // marca o tempo antes de executar a busca
    auto inicio = chrono::high_resolution_clock::now();

    // executa a busca ternaria no vetor inteiro [0, n)
    int resultado = buscaTernaria(A.data(), 0, n, chave);

    // marca o tempo depois que a busca terminou
    auto fim = chrono::high_resolution_clock::now();

    // calcula a duracao da busca em nanossegundos
    auto duracao = chrono::duration_cast<chrono::nanoseconds>(fim - inicio);

    cout << "Resultado: " << resultado << endl;          // imprime o indice (ou -1)
    cout << "Tempo (ns): " << duracao.count() << endl;   // imprime o tempo gasto

    return 0;
}