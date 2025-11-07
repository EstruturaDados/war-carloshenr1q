// Aventureiro (aula 1)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio conforme especificado
// Esta struct agrupa os dados relacionados a um território: nome, cor do exército e quantidade de tropas
typedef struct {
    char nome[30];  // Campo para armazenar o nome do território (até 29 caracteres + \0)
    char cor[10];   // Campo para armazenar a cor do exército (até 9 caracteres + \0)
    int tropas;     // Campo para armazenar a quantidade de tropas (inteiro)
} Territorio;

// Função para cadastrar os territórios
// Recebe um ponteiro para o vetor de territórios e o tamanho, preenchendo os dados via entrada do usuário
void cadastrarTerritorios(Territorio* mapa, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("Cadastro do Territorio %d:\n", i + 1);
        printf("Digite o nome do territorio (max 29 caracteres): ");
        scanf("%29s", mapa[i].nome);  // Limita entrada para evitar overflow
        printf("Digite a cor do exercito (max 9 caracteres): ");
        scanf("%9s", mapa[i].cor);    // Limita entrada
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        printf("\n");
    }
}

// Função para exibir o mapa (todos os territórios)
// Recebe ponteiro para o mapa e tamanho, imprimindo os dados de cada território
void exibirMapa(Territorio* mapa, int tamanho) {
    printf("\nMapa atual:\n");
    for (int i = 0; i < tamanho; i++) {
        printf("Territorio %d: Nome: %s, Cor: %s, Tropas: %d\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
    printf("\n");
}

// Função para simular ataque entre dois territórios
// Recebe ponteiros para atacante e defensor, simula dados aleatórios e atualiza os campos conforme regras
void atacar(Territorio* atacante, Territorio* defensor) {
    // Validação: não permitir ataque a território da mesma cor
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("Erro: Nao e possivel atacar um territorio da mesma cor!\n");
        return;
    }

    // Simulação de dados: rand() para valores de 1 a 6
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;
    printf("Resultado do ataque:\n");
    printf("Dado do atacante (%s): %d\n", atacante->nome, dadoAtacante);
    printf("Dado do defensor (%s): %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        // Atacante vence: defensor muda de cor e recebe metade das tropas do atacante
        strcpy(defensor->cor, atacante->cor);
        int metadeTropas = atacante->tropas / 2;
        defensor->tropas = metadeTropas;
        atacante->tropas -= metadeTropas;  // Atacante perde metade das tropas
        printf("Atacante venceu! Territorio %s agora pertence a %s com %d tropas.\n", defensor->nome, atacante->cor, defensor->tropas);
    } else {
        // Defensor vence: atacante perde 1 tropa
        atacante->tropas--;
        printf("Defensor venceu! Atacante perdeu 1 tropa (agora tem %d).\n", atacante->tropas);
    }
}

// Função para liberar a memória alocada dinamicamente
// Recebe ponteiro para o mapa e libera o espaço
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

int main() {
    // Inicialização da semente para números aleatórios
    srand(time(NULL));

    // Solicitar ao usuário o número de territórios
    int tamanho;
    printf("Digite o numero de territorios a cadastrar: ");
    scanf("%d", &tamanho);

    // Alocação dinâmica de memória para o vetor de territórios usando calloc (inicializa com zero)
    Territorio* mapa = (Territorio*)calloc(tamanho, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, tamanho);

    // Exibição inicial do mapa
    exibirMapa(mapa, tamanho);

    // Loop para permitir ataques interativos
    char continuar = 's';
    while (continuar == 's' || continuar == 'S') {
        // Orientação ao usuário: listar territórios disponíveis
        printf("Escolha o territorio atacante (1 a %d):\n", tamanho);
        for (int i = 0; i < tamanho; i++) {
            printf("%d - %s (%s, %d tropas)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }
        int idxAtacante;
        scanf("%d", &idxAtacante);
        idxAtacante--;  // Ajuste para índice 0-based

        printf("Escolha o territorio defensor (1 a %d):\n", tamanho);
        for (int i = 0; i < tamanho; i++) {
            printf("%d - %s (%s, %d tropas)\n", i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
        }
        int idxDefensor;
        scanf("%d", &idxDefensor);
        idxDefensor--;  // Ajuste para índice 0-based

        // Validação básica de índices
        if (idxAtacante < 0 || idxAtacante >= tamanho || idxDefensor < 0 || idxDefensor >= tamanho) {
            printf("Indices invalidos!\n");
            continue;
        }

        // Chamada da função de ataque (passando ponteiros)
        atacar(&mapa[idxAtacante], &mapa[idxDefensor]);

        // Exibição do mapa atualizado
        exibirMapa(mapa, tamanho);

        // Perguntar se deseja continuar
        printf("Deseja realizar outro ataque? (s/n): ");
        scanf(" %c", &continuar);  // Espaço antes de %c para consumir newline
    }

    // Liberação da memória alocada
    liberarMemoria(mapa);

    printf("Programa encerrado. Memoria liberada.\n");
    return 0;
}
