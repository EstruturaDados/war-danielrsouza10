// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    char nome[50];
    char corExercito[20];
    int numTropas;
} Territorio;

void cadastrarTerritorios(Territorio *territorios, int n) {
    for (int i = 0; i < n; i++) {
        printf("Digite o nome do território %d: ", i + 1);
        fgets(territorios[i].nome, 50, stdin);
        printf("Digite a cor do exército dominante: ");
        fgets(territorios[i].corExercito, 20, stdin);
        printf("Digite o número de tropas: ");
        scanf("%d", &territorios[i].numTropas);
        getchar(); // Limpar buffer
    }
}

void exibirTerritorios(Territorio *territorios, int n) {
    printf("\nEstado Atual dos Territórios:\n");
    for (int i = 0; i < n; i++) {
        printf("Território %d: %sCor: %sNúmero de Tropas: %d\n\n",
               i + 1,
               territorios[i].nome,
               territorios[i].corExercito,
               territorios[i].numTropas);
    }
}

void simularAtaque(Territorio *territorios, int atacante, int defensor) {
    int dadosAtacante = rand() % 6 + 1;
    int dadosDefensor = rand() % 6 + 1;

    printf("Dados do atacante: %d\n", dadosAtacante);
    printf("Dados do defensor: %d\n", dadosDefensor);

    if (dadosAtacante >= dadosDefensor) {
        territorios[defensor].numTropas--;
        printf("Atacante venceu! Defensor perde uma tropa.\n");
        if (territorios[defensor].numTropas <= 0) {
            printf("Território %d conquistado pelo atacante!\n", defensor + 1);
            // Mudança de cor para indicar conquista pode ser adicionada
        }
    } else {
        printf("Defensor venceu! Nenhuma tropa perdida.\n");
    }
}

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
int main() {
    int n = 5;
    Territorio *territorios = (Territorio *)calloc(n, sizeof(Territorio));
    if (!territorios) {
        printf("Falha na alocação de memória.\n");
        return 1;
    }

    srand(time(NULL));

    cadastrarTerritorios(territorios, n);
    exibirTerritorios(territorios, n);

    int atacante, defensor;
    printf("Digite o território atacante (1-5): ");
    scanf("%d", &atacante);
    printf("Digite o território defensor (1-5): ");
    scanf("%d", &defensor);

    simularAtaque(territorios, atacante - 1, defensor - 1);
    exibirTerritorios(territorios, n);

    free(territorios);
    return 0;
}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.
