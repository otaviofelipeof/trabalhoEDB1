// Trabalho 1 - EDB1 (DIM0119)
// Exercicio 3: Busca Sequencial Alternativa - Versao Iterativa
// Autor: Otávio Felipe

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// Busca sequencial alternativa: como o vetor esta ORDENADO, paramos mais cedo
// se encontrarmos um elemento maior que a chave (ela nao pode estar mais adiante)
int buscaSeqAlternativa(int A[], int esq, int dir, int chave) {
    // Percorre o intervalo [esq, dir)
    for (int i = esq; i < dir; i++) {
        // Se o elemento atual e igual a chave, achamos
        if (A[i] == chave) {
            return i;
        }
        // Se o elemento atual ja e maior que a chave, o vetor ordenado
        // garante que nenhum elemento depois sera igual a chave.
        // Entao paramos aqui (corte antecipado), sem precisar continuar.
        if (A[i] > chave) {
            return -1;
        }
        // Se nao entrou em nenhum dos dois "if" acima, o laco continua
    }
    // Se saiu do laco sem retornar, e porque a chave e maior que todos
    // os elementos do vetor (o corte nunca foi acionado)
    return -1;
}

int main() {
    int n;
    cin >> n;              // le o tamanho do vetor

    vector<int> A(n);       // cria o vetor
    for (int i = 0; i < n; i++) {
        cin >> A[i];         // le cada elemento (o arquivo ja vem ordenado)
    }

    int chave;
    cin >> chave;            // le a chave buscada

    auto inicio = chrono::high_resolution_clock::now();  // marca o inicio da medicao

    int resultado = buscaSeqAlternativa(A.data(), 0, n, chave);  // executa a busca

    auto fim = chrono::high_resolution_clock::now();  // marca o fim da medicao

    // converte a duracao medida para nanossegundos
    auto duracao = chrono::duration_cast<chrono::nanoseconds>(fim - inicio);

    cout << "Resultado: " << resultado << endl;          // imprime o indice (ou -1)
    cout << "Tempo (ns): " << duracao.count() << endl;   // imprime o tempo gasto

    return 0;
}