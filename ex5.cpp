// Trabalho 1 - EDB1 (DIM0119)
// Exercicio 5: Busca Binaria Iterativa
// Autor: Otávio Felipe

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Busca binaria: a cada passo, olha o elemento do meio e descarta metade do vetor
int buscaBinaria(int A[], int esq, int dir, int chave) {
    // Continua enquanto o intervalo [esq, dir) ainda tiver pelo menos 1 elemento
    while (esq < dir) {
        // Calcula a posicao do meio do intervalo atual.
        // Usamos esq + (dir - esq) / 2 em vez de (esq + dir) / 2 para
        // evitar que a soma esq + dir "estoure" o limite do tipo int
        // em vetores muito grandes (boa pratica de programacao).
        int m = esq + (dir - esq) / 2;

        // Compara o elemento do meio com a chave
        if (A[m] == chave) {
            return m;  // achou exatamente no meio
        } else if (chave < A[m]) {
            // Se a chave e menor que o elemento do meio, ela so pode estar
            // na metade esquerda. Atualizamos dir para m (m fica de fora,
            // pois ja sabemos que A[m] nao e a chave)
            dir = m;
        } else {
            // Se a chave e maior que o elemento do meio, ela so pode estar
            // na metade direita. Atualizamos esq para m + 1
            esq = m + 1;
        }
        // O laco while volta a testar a condicao (esq < dir) com os novos valores
    }
    // Se o laco terminou, esq alcancou ou passou de dir: intervalo vazio, nao achou
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

    // marca o tempo antes de chamar a busca
    auto inicio = chrono::high_resolution_clock::now();

    // executa a busca binaria no vetor inteiro [0, n)
    int resultado = buscaBinaria(A.data(), 0, n, chave);

    // marca o tempo depois da busca terminar
    auto fim = chrono::high_resolution_clock::now();

    // calcula a diferenca de tempo em nanossegundos
    auto duracao = chrono::duration_cast<chrono::nanoseconds>(fim - inicio);

    cout << "Resultado: " << resultado << endl;          // imprime o indice (ou -1)
    cout << "Tempo (ns): " << duracao.count() << endl;   // imprime o tempo gasto

    return 0;
}