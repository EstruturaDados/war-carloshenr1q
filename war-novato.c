// Novato (aula 1)

#include <stdio.h>
#include <string.h>

// Definição da struct Territorio conforme especificado
// Esta struct agrupa os dados relacionados a um território: nome, cor do exército e quantidade de tropas
typedef struct {
    char nome[30];  // Campo para armazenar o nome do território (até 29 caracteres + \0)
    char cor[10];   // Campo para armazenar a cor do exército (até 9 caracteres + \0)
    int tropas;     // Campo para armazenar a quantidade de tropas (inteiro)
} Territorio;

int main() {
    // Declaração de um vetor de structs para armazenar 5 territórios
    // Capacidade fixa de 5, conforme requisitos
    Territorio territorios[5];
    // Laço para cadastro dos 5 territórios
    // Percorre o vetor e solicita entrada do usuário para cada campo
    for (int i = 0; i < 5; i++) {
        printf("Cadastro do Territorio %d:\n", i + 1);
        // Entrada do nome: usa scanf com limite para evitar overflow
        printf("Digite o nome do territorio (max 29 caracteres): ");
        scanf("%29s", territorios[i].nome);  // Limita a 29 chars para caber no array
        // Entrada da cor: usa scanf com limite para evitar overflow
        printf("Digite a cor do exercito (max 9 caracteres): ");
        scanf("%9s", territorios[i].cor);  // Limita a 9 chars para caber no array
        // Entrada da quantidade de tropas: usa scanf para inteiro
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
        printf("\n");  // Quebra de linha para separar cadastros
    }
    // Exibição dos dados cadastrados
    // Percorre o vetor e imprime as informações de cada território com formatação clara
    printf("Dados dos territorios cadastrados:\n");
    for (int i = 0; i < 5; i++) {
        printf("Territorio %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor: %s\n", territorios[i].cor);
    }
}