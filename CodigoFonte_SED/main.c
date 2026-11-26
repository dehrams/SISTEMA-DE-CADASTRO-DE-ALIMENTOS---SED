
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define NUM_MAX_CAD 1024
#define TAM_NOME 256
#define TAM_CODIGO 13
#define TAM_VALIDADE 11
#define ARQUIVO "cadastro.txt"

typedef struct alimento {
    int ocupado;
    char nome[TAM_NOME];
    char codigo[TAM_CODIGO];
    int quantidade;
    char validade[TAM_VALIDADE];
    float unidade;
} alimento;

alimento vetor_alimentos[NUM_MAX_CAD];
int total_alimentos = 0;

/* PROTOTIPOS */

void limpar_tela(void);
void pausar(void);
void limpar_fim_linha(char *texto);
void ler_texto(const char *mensagem, char *destino, size_t tamanho);
int ler_inteiro(const char *mensagem, int minimo, int maximo);
float ler_float(const char *mensagem, float minimo);
int confirmar(const char *mensagem);

int data_valida(const char *data);
void ler_validade(char *validade);

int codigo_valido(const char *codigo);
void ler_codigo(char *codigo);

void cadastro_inicializar(void);
int cadastro_inserir_alimento(alimento novo);
alimento cadastro_pesquisar_alimento(const char *codigo);
int cadastro_remover_alimento(const char *codigo);
void cadastro_carregar_dados_arquivo(void);
int cadastro_salvar_dados_arquivo(void);

void tela_menu_opcoes(void);
void tela_cadastrar(void);
void tela_pesquisar(void);
void tela_remover(void);
void tela_relatorio(void);
void imprimir_alimento(const alimento *item);


/* PROGRAMA PRINCIPAL */

int main(void) {

#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    setlocale(LC_ALL, "portugese");
    system("chcp 1252 > null");

    cadastro_inicializar();
    cadastro_carregar_dados_arquivo();

    int opcao;

    do {
        tela_menu_opcoes();

        opcao = ler_inteiro("Escolha uma opção: ", 1, 5);

        switch (opcao) {

            case 1:
                tela_cadastrar();
                break;

            case 2:
                tela_pesquisar();
                break;

            case 3:
                tela_remover();
                break;

            case 4:
                tela_relatorio();
                break;

            case 5:

                if (confirmar("Deseja realmente sair?")) {

                    if (cadastro_salvar_dados_arquivo()) {

                        limpar_tela();

                        printf("\n========================================\n");
                        printf("       SISTEMA ENCERRADO COM SUCESSO\n");
                        printf("========================================\n\n");

                    } else {

                        printf("\nNao foi possivel salvar os dados.\n");
                        opcao = 0;

                    }

                } else {

                    opcao = 0;

                }

                break;
        }

    } while (opcao != 5);

    return 0;
}


/* UTILITÁRIOS */

void limpar_tela(void) {
    system("cls");
    printf("\033[2J\033[H");
}


void pausar(void) {

    printf("\nPressione ENTER para continuar...");

    int c;

    while ((c = getchar()) != '\n' && c != EOF) {}

}


void limpar_fim_linha(char *texto) {
    texto[strcspn(texto, "\r\n")] = '\0';
}


void ler_texto(const char *mensagem, char *destino, size_t tamanho) {

    for (;;) {

        printf("%s", mensagem);

        if (fgets(destino, (int)tamanho, stdin) == NULL) {
            destino[0] = '\0';
            return;
        }

        if (strchr(destino, '\n') == NULL) {

            int c;

            while ((c = getchar()) != '\n' && c != EOF) {}

        }

        limpar_fim_linha(destino);

        if (destino[0] != '\0') {
            return;
        }

        printf("Entrada inválida. Tente novamente.\n");
    }
}


int ler_inteiro(const char *mensagem, int minimo, int maximo) {

    char entrada[100];
    char *fim;
    long valor;

    for (;;) {

        ler_texto(mensagem, entrada, sizeof entrada);

        valor = strtol(entrada, &fim, 10);

        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        if (fim != entrada && *fim == '\0' &&
            valor >= minimo && valor <= maximo) {
            return (int)valor;
        }

        printf("Digite um número entre %d e %d.\n", minimo, maximo);
    }
}


float ler_float(const char *mensagem, float minimo) {

    char entrada[100];
    char *fim;
    float valor;

    for (;;) {

        ler_texto(mensagem, entrada, sizeof entrada);

        valor = strtof(entrada, &fim);

        while (isspace((unsigned char)*fim)) {
            fim++;
        }

        if (fim != entrada && *fim == '\0' && valor >= minimo) {
            return valor;
        }

        printf("Digite um valor válido, maior ou igual a %.2f.\n", minimo);
    }
}


int confirmar(const char *mensagem) {

    char resposta[20];

    for (;;) {

        printf("\n%s (S/N): ", mensagem);

        if (fgets(resposta, sizeof resposta, stdin) == NULL) {
            return 0;
        }

        if (toupper((unsigned char)resposta[0]) == 'S') {
            return 1;
        }

        if (toupper((unsigned char)resposta[0]) == 'N') {
            return 0;
        }

        printf("Digite apenas S ou N.\n");
    }
}


/* VALIDAÇÃO DA DATA */

int data_valida(const char *data) {

    if (strlen(data) != 10 ||
        data[2] != '/' ||
        data[5] != '/') {
        return 0;
    }

    for (int i = 0; i < 10; i++) {

        if (i == 2 || i == 5) {
            continue;
        }

        if (!isdigit((unsigned char)data[i])) {
            return 0;
        }
    }

    int dia = (data[0] - '0') * 10 + (data[1] - '0');

    int mes = (data[3] - '0') * 10 + (data[4] - '0');

    int ano = (data[6] - '0') * 1000 +
              (data[7] - '0') * 100 +
              (data[8] - '0') * 10 +
              (data[9] - '0');

    if (ano < 1 || mes < 1 || mes > 12) {
        return 0;
    }

    int dias_mes[] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    int bissexto = (ano % 400 == 0) ||
                   (ano % 4 == 0 && ano % 100 != 0);

    if (bissexto) {
        dias_mes[1] = 29;
    }

    return dia >= 1 && dia <= dias_mes[mes - 1];
}


void ler_validade(char *validade) {

    char entrada[50];

    for (;;) {

        ler_texto("Data de validade (DD/MM/AAAA): ",
                  entrada, sizeof entrada);

        if (data_valida(entrada)) {
            strcpy(validade, entrada);
            return;
        }

        printf("Data inválida! Use DD/MM/AAAA.\n");
    }
}


/* VALIDAÇÃO DO CÓDIGO DO ALIMENTO */

int codigo_valido(const char *codigo) {

    if (strlen(codigo) != 6) {
        return 0;
    }

    for (int i = 0; i < 6; i++) {

        if (!isalnum((unsigned char)codigo[i])) {
            return 0;
        }
    }

    return 1;
}


void ler_codigo(char *codigo) {

    for (;;) {

        ler_texto("Código do alimento: ", codigo, TAM_CODIGO);

        for (int i = 0; codigo[i] != '\0'; i++) {
            codigo[i] = (char)toupper((unsigned char)codigo[i]);
        }

        if (codigo_valido(codigo)) {
            return;
        }

        printf("Código inválido! Use exatamente 6 letras e/ou números.\n");
    }
}


/* GERENCIAMENTO DO CADASTRO */

void cadastro_inicializar(void) {

    total_alimentos = 0;

    for (int i = 0; i < NUM_MAX_CAD; i++) {
        vetor_alimentos[i].ocupado = 0;
    }
}


int cadastro_inserir_alimento(alimento novo) {

    if (total_alimentos >= NUM_MAX_CAD) {
        return 0;
    }

    for (int i = 0; i < NUM_MAX_CAD; i++) {

        if (vetor_alimentos[i].ocupado &&
            strcmp(vetor_alimentos[i].codigo, novo.codigo) == 0) {
            return -1;
        }
    }

    for (int i = 0; i < NUM_MAX_CAD; i++) {

        if (!vetor_alimentos[i].ocupado) {

            novo.ocupado = 1;
            vetor_alimentos[i] = novo;
            total_alimentos++;

            return 1;
        }
    }

    return 0;
}


alimento cadastro_pesquisar_alimento(const char *codigo) {

    alimento vazio = {0};

    for (int i = 0; i < NUM_MAX_CAD; i++) {

        if (vetor_alimentos[i].ocupado &&
            strcmp(vetor_alimentos[i].codigo, codigo) == 0) {
            return vetor_alimentos[i];
        }
    }

    return vazio;
}


int cadastro_remover_alimento(const char *codigo) {

    for (int i = 0; i < NUM_MAX_CAD; i++) {

        if (vetor_alimentos[i].ocupado &&
            strcmp(vetor_alimentos[i].codigo, codigo) == 0) {

            vetor_alimentos[i].ocupado = 0;
            total_alimentos--;

            return 1;
        }
    }

    return 0;
}


/* TELA DO SISTEMA */

void tela_menu_opcoes(void) {

    limpar_tela();

    printf("+--------------------------------------+\n");
    printf("|        SISTEMA DE ALIMENTOS          |\n");
    printf("+--------------------------------------+\n");
    printf("|  1. Cadastrar alimento               |\n");
    printf("|  2. Pesquisar alimento               |\n");
    printf("|  3. Remover alimento                 |\n");
    printf("|  4. Relatório                        |\n");
    printf("|  5. Sair                             |\n");
    printf("+--------------------------------------+\n");

    printf("Alimentos cadastrados: %d\n\n", total_alimentos);
}


void tela_cadastrar(void) {

    do {

        limpar_tela();

        printf("+--------------------------------------+\n");
        printf("|          CADASTRAR ALIMENTO          |\n");
        printf("+--------------------------------------+\n");

        if (total_alimentos >= NUM_MAX_CAD) {

            printf("Limite máximo de cadastros atingido.\n");
            pausar();

            return;
        }

        alimento novo = {0};

        ler_texto("Nome: ", novo.nome, sizeof novo.nome);

        ler_codigo(novo.codigo);

        novo.quantidade = ler_inteiro(
            "Quantidade: ", 1, 120
        );

        ler_validade(novo.validade);

        novo.unidade = ler_float(
            "Peso/volume (em gramas ou litros): ", 1.0f
        );

        int resultado = cadastro_inserir_alimento(novo);

        if (resultado == 1) {

            if (cadastro_salvar_dados_arquivo()) {
                printf("\n[OK] Alimento cadastrado e salvo com sucesso!\n");
            } else {
                printf("\n[ERRO] Cadastro feito, mas nao foi possivel salvar no TXT.\n");
            }

        } else if (resultado == -1) {

            printf("\n[ERRO] Já existe um alimento com esse código.\n");

        } else {

            printf("\n[ERRO] Não foi possível realizar o cadastro.\n");
        }

    } while (confirmar("Deseja cadastrar outro alimento?"));
}


void imprimir_alimento(const alimento *item) {

    printf("----------------------------------------\n");

    printf("Código:      %s\n", item->codigo);
    printf("Nome:        %s\n", item->nome);
    printf("Quantidade:  %d\n", item->quantidade);
    printf("Validade:    %s\n", item->validade);
    printf("Peso/volume: %.2f g/L\n", item->unidade);

    printf("----------------------------------------\n");
}


void tela_pesquisar(void) {

    do {

        limpar_tela();

        printf("+--------------------------------------+\n");
        printf("|          PESQUISAR ALIMENTO          |\n");
        printf("+--------------------------------------+\n");

        char codigo[TAM_CODIGO];

        ler_codigo(codigo);

        alimento encontrado = cadastro_pesquisar_alimento(codigo);

        if (encontrado.ocupado) {

            printf("\nAlimento encontrado:\n");
            imprimir_alimento(&encontrado);

        } else {

            printf("\nNenhum alimento encontrado com esse código.\n");
        }

    } while (confirmar("Deseja pesquisar outro alimento?"));
}


void tela_remover(void) {

    do {

        limpar_tela();

        printf("+--------------------------------------+\n");
        printf("|           REMOVER ALIMENTO           |\n");
        printf("+--------------------------------------+\n");

        char codigo[TAM_CODIGO];

        ler_codigo(codigo);

        alimento encontrado = cadastro_pesquisar_alimento(codigo);

        if (encontrado.ocupado) {

            printf("\nAlimento selecionado:\n");
            imprimir_alimento(&encontrado);

            if (confirmar("Confirma a remoção deste alimento?")) {

                cadastro_remover_alimento(codigo);

                if (cadastro_salvar_dados_arquivo()) {
                    printf("\n[OK] Alimento removido e arquivo atualizado.\n");
                } else {
                    printf("\n[ERRO] Remocao feita na memoria, mas nao foi possivel atualizar o TXT.\n");
                }

            } else {

                printf("\nRemoção cancelada.\n");
            }

        } else {

            printf("\nAlimento não encontrado.\n");
        }

    } while (confirmar("Deseja remover outro alimento?"));
}


void tela_relatorio(void) {

    limpar_tela();

    printf("+--------------------------------------+\n");
    printf("|          RELATÓRIO DE ALIMENTOS      |\n");
    printf("+--------------------------------------+\n");

    printf("Total de alimentos cadastrados: %d\n\n",
           total_alimentos);

    if (total_alimentos == 0) {

        printf("Nenhum alimento cadastrado.\n");

    } else {

        for (int i = 0; i < NUM_MAX_CAD; i++) {

            if (vetor_alimentos[i].ocupado) {
                imprimir_alimento(&vetor_alimentos[i]);
            }
        }
    }

    pausar();
}


/* MANIPULAÇÃO DO ARQUIVO */

/* CARREGAR DADOS DO TXT */

void cadastro_carregar_dados_arquivo(void) {

    FILE *fp = fopen(ARQUIVO, "r");

    char linha[400];

    if (fp == NULL) {
        return;
    }

    while (fgets(linha, sizeof linha, fp) != NULL) {

        alimento item = {0};

        char quantidade[100] = "";
        char valor[100] = "";

        char *fim_qtd;
        char *fim_valor;
        char *campo;

        long qtd;
        float unidade;

        if (strncmp(linha, "Codigo: ", 8) != 0 &&
            strncmp(linha, "Código: ", 9) != 0) {
            continue;
        }

        campo = strchr(linha, ':');

        if (campo == NULL) {
            continue;
        }

        campo++;

        while (*campo == ' ') {
            campo++;
        }

        limpar_fim_linha(campo);

        strncpy(item.codigo, campo, sizeof item.codigo - 1);

        if (fgets(linha, sizeof linha, fp) == NULL) {
            break;
        }

        campo = strchr(linha, ':');

        if (campo == NULL) {
            continue;
        }

        campo++;

        while (*campo == ' ') {
            campo++;
        }

        limpar_fim_linha(campo);

        strncpy(item.nome, campo, sizeof item.nome - 1);

        if (fgets(linha, sizeof linha, fp) == NULL) {
            break;
        }

        campo = strchr(linha, ':');

        if (campo == NULL) {
            continue;
        }

        campo++;

        while (*campo == ' ') {
            campo++;
        }

        limpar_fim_linha(campo);

        strncpy(quantidade, campo, sizeof quantidade - 1);
        quantidade[sizeof quantidade - 1] = '\0';

        if (fgets(linha, sizeof linha, fp) == NULL) {
            break;
        }

        campo = strchr(linha, ':');

        if (campo == NULL) {
            continue;
        }

        campo++;

        while (*campo == ' ') {
            campo++;
        }

        limpar_fim_linha(campo);

        strncpy(item.validade, campo, sizeof item.validade - 1);

        if (fgets(linha, sizeof linha, fp) == NULL) {
            break;
        }

        campo = strchr(linha, ':');

        if (campo == NULL) {
            continue;
        }

        campo++;

        while (*campo == ' ') {
            campo++;
        }

        limpar_fim_linha(campo);

        strncpy(valor, campo, sizeof valor - 1);
        valor[sizeof valor - 1] = '\0';

        qtd = strtol(quantidade, &fim_qtd, 10);

        while (isspace((unsigned char)*fim_qtd)) {
            fim_qtd++;
        }

        unidade = strtof(valor, &fim_valor);

        /*
           Aceita o sufixo g/L que aparece
           no arquivo TXT.
        */

        while (isspace((unsigned char)*fim_valor)) {
            fim_valor++;
        }

        if (strcmp(fim_valor, "g/L") == 0) {
            fim_valor += 3;
        }

        while (isspace((unsigned char)*fim_valor)) {
            fim_valor++;
        }

        if (!codigo_valido(item.codigo) ||
            item.nome[0] == '\0' ||
            !data_valida(item.validade) ||
            fim_qtd == quantidade ||
            *fim_qtd != '\0' ||
            qtd < 1 ||
            qtd > 120 ||
            fim_valor == valor ||
            *fim_valor != '\0' ||
            unidade < 1.0f) {

            continue;
        }

        item.quantidade = (int)qtd;
        item.unidade = unidade;

        cadastro_inserir_alimento(item);
    }

    fclose(fp);
}


/* SALVAR DADOS NO TXT */

int cadastro_salvar_dados_arquivo(void) {

    FILE *fp = fopen(ARQUIVO, "w");

    if (fp == NULL) {

        printf("Erro: nao foi possivel abrir %s para gravacao.\n",
               ARQUIVO);

        return 0;
    }

    fprintf(fp, "========================================\n");
    fprintf(fp, "         CADASTRO DE ALIMENTOS\n");
    fprintf(fp, "========================================\n\n");

    fprintf(fp, "Total de alimentos cadastrados: %d\n\n",
            total_alimentos);

    int numero = 1;

    for (int i = 0; i < NUM_MAX_CAD; i++) {

        if (vetor_alimentos[i].ocupado) {

            fprintf(fp, "----------------------------------------\n");
            fprintf(fp, "ALIMENTO %d\n", numero);
            fprintf(fp, "----------------------------------------\n");

            fprintf(fp, "Codigo: %s\n",
                    vetor_alimentos[i].codigo);

            fprintf(fp, "Nome: %s\n",
                    vetor_alimentos[i].nome);

            fprintf(fp, "Quantidade: %d\n",
                    vetor_alimentos[i].quantidade);

            fprintf(fp, "Validade: %s\n",
                    vetor_alimentos[i].validade);

            fprintf(fp, "Peso/volume: %.2f g/L\n\n",
                    vetor_alimentos[i].unidade);

            numero++;
        }
    }

    fprintf(fp, "========================================\n");
    fprintf(fp, "           FIM DO RELATORIO\n");
    fprintf(fp, "========================================\n");

    if (fclose(fp) != 0) {

        printf("Erro ao finalizar a gravacao de %s.\n",
               ARQUIVO);

        return 0;
    }

    return 1;
}
