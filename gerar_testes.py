# gerar_testes.py
# Script auxiliar (nao faz parte da implementacao dos algoritmos em si).
# Gera arquivos de teste de melhor e pior caso, com tamanhos de 0 ate 500.000.
# Formato de cada arquivo: primeira linha = n, segunda linha = os n numeros,
# terceira linha = a chave que sera buscada.

import random  # biblioteca usada para embaralhar os vetores (busca linear)

START_SIZE = 0        # menor tamanho de vetor a ser testado
END_SIZE = 500000      # maior tamanho de vetor a ser testado
STEP = 10000            # intervalo entre um tamanho e outro (mesmo do exemplo do professor)

# Gera a lista de tamanhos: 0, 10000, 20000, ..., 500000
# range(START_SIZE, END_SIZE + 1, STEP) inclui o END_SIZE porque somamos 1
TAMANHOS = list(range(START_SIZE, END_SIZE + 1, STEP))

def gerar_vetor_ordenado(n):
    # Gera uma lista de n numeros pares, em ordem crescente: 0, 2, 4, 6, ...
    # Usados nos exercicios que exigem vetor ORDENADO (3 a 8)
    return [i * 2 for i in range(n)]

def gerar_vetor_nao_ordenado(n):
    # Gera a mesma lista de numeros pares, mas embaralhada
    # Usada nos exercicios que NAO exigem ordenacao (1 e 2)
    vetor = [i * 2 for i in range(n)]  # cria a lista ordenada primeiro
    random.shuffle(vetor)               # embaralha a lista no lugar (in-place)
    return vetor                         # devolve a lista embaralhada

def escrever_arquivo(nome_arquivo, vetor, chave):
    # Escreve um arquivo de teste no formato exigido pelo enunciado
    with open(nome_arquivo, "w") as f:      # abre o arquivo para escrita
        f.write(f"{len(vetor)}\n")           # primeira linha: tamanho do vetor
        f.write(" ".join(str(x) for x in vetor) + "\n")  # segunda linha: os elementos separados por espaco
        f.write(f"{chave}\n")                 # terceira linha: a chave buscada

def gerar_para_busca_nao_ordenada(numero_exercicio):
    # Gera os arquivos de teste para um exercicio que NAO precisa de vetor ordenado
    # (usado para os exercicios 1 e 2, busca linear)
    for n in TAMANHOS:  # repete para cada tamanho de vetor definido em TAMANHOS
        if n == 0:
            # Caso especial: vetor vazio. Nao ha elementos, entao a chave
            # nunca sera encontrada, tanto no melhor quanto no pior caso.
            escrever_arquivo(f"m{numero_exercicio}v{n}.txt", [], 1)
            escrever_arquivo(f"p{numero_exercicio}v{n}.txt", [], 1)
            continue  # pula o resto do laco e vai para o proximo tamanho

        vetor = gerar_vetor_nao_ordenado(n)  # gera um vetor embaralhado de tamanho n

        # Melhor caso: a chave e o primeiro elemento do vetor gerado
        # (a busca linear encontra na primeira comparacao)
        escrever_arquivo(f"m{numero_exercicio}v{n}.txt", vetor, vetor[0])

        # Pior caso: a chave e um numero que nunca aparece no vetor
        # (a busca linear percorre tudo e nao encontra)
        escrever_arquivo(f"p{numero_exercicio}v{n}.txt", vetor, 999999999)

def gerar_para_busca_ordenada(numero_exercicio, tipo):
    # Gera os arquivos de teste para um exercicio que PRECISA de vetor ordenado
    # (usado para os exercicios 3 a 8: sequencial alternativa, binaria, ternaria)
    for n in TAMANHOS:  # repete para cada tamanho de vetor
        if n == 0:
            # Mesmo caso especial de vetor vazio
            escrever_arquivo(f"m{numero_exercicio}v{n}.txt", [], 1)
            escrever_arquivo(f"p{numero_exercicio}v{n}.txt", [], 1)
            continue

        vetor = gerar_vetor_ordenado(n)  # gera um vetor ja ordenado de tamanho n

        # Escolhe a posicao do "melhor caso" de acordo com o tipo de algoritmo,
        # porque cada algoritmo tem uma posicao diferente onde encontra mais rapido
        if tipo == "sequencial_alt":
            # Na busca sequencial alternativa, o melhor caso e o primeiro elemento
            melhor_chave = vetor[0]
        elif tipo == "binaria":
            # Na busca binaria, o melhor caso e o elemento exatamente no meio
            melhor_chave = vetor[n // 2]
        elif tipo == "ternaria":
            # Na busca ternaria, o melhor caso e o elemento no primeiro ponto de corte
            melhor_chave = vetor[n // 3]

        # Grava o arquivo de melhor caso, usando a chave escolhida acima
        escrever_arquivo(f"m{numero_exercicio}v{n}.txt", vetor, melhor_chave)

        # Grava o arquivo de pior caso: chave maior que todos os elementos
        # (forca o algoritmo a percorrer o maximo de comparacoes possivel)
        escrever_arquivo(f"p{numero_exercicio}v{n}.txt", vetor, 999999999)

# Este bloco so executa se o arquivo for rodado diretamente (nao se for importado)
if __name__ == "__main__":
    gerar_para_busca_nao_ordenada(1)              # exercicio 1: linear iterativa
    gerar_para_busca_nao_ordenada(2)              # exercicio 2: linear recursiva
    gerar_para_busca_ordenada(3, "sequencial_alt") # exercicio 3: seq. alternativa iterativa
    gerar_para_busca_ordenada(4, "sequencial_alt") # exercicio 4: seq. alternativa recursiva
    gerar_para_busca_ordenada(5, "binaria")        # exercicio 5: binaria iterativa
    gerar_para_busca_ordenada(6, "binaria")        # exercicio 6: binaria recursiva
    gerar_para_busca_ordenada(7, "ternaria")       # exercicio 7: ternaria iterativa
    gerar_para_busca_ordenada(8, "ternaria")       # exercicio 8: ternaria recursiva
    print("Arquivos de teste gerados!")             # avisa que terminou tudo