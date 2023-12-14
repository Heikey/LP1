#include "database.h"
#include "medicine.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Limpa o console
void clear_console() {
  if (system("cls"))
    // tentativa de arrumar um bug do linux
    system("export TERM=xterm-256color;clear");
}
// caso o ultimo caractere seja uma quebra de linha(\n), remove e troca por um
// \0 para remover
void trim(char *string) {
  if (string[strlen(string) - 1] == '\n')
    string[strlen(string) - 1] = '\0';
}
// checa se a string é um numero
int isnumber(char *string) {
  for (int i = 0; i < strlen(string); ++i) {
    if (!isdigit(string[i])) {
      return 0;
    };
  }
  return 1;
}

// Limpar o buffer do teclado
void clear_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

int main() {
  char choice;
  // inicializa a database com um arquivo chamado de product.txt
  Database *db = database_init("product.txt");
  while (1) {
    clear_console();
    printf("===================================\n");
    printf("\t\tWhat do you want to do?\t\n\n");
    printf("[1] Register product \n");
    printf("[2] List the products and their suppliers and edit \n");
    printf("[3] Remove registration from a product\n");
    printf("[4] Exit\n\n");
    printf("===================================\n");

    // Entrada do usuario.
    printf("Type here: ");
    scanf(" %c", &choice);
    clear_buffer();
    clear_console();
    if (isnumber(&choice)) {
      fflush(stdin);
      int choice_ = atoi(&choice);
      switch (choice_) {
      case 1:
          // esse ; perdido é um erro do codigo, tem que colocar esse ; para não
          // dar erro
          ;
        Medicine *med = medicine_alloc();
        medicine_read(med);
        // adiciona o medicamento na database
        database_add(db, med, sizeof(Medicine));
        break;
      case 2:
        // essa função mostra todos os produtos da database, usando uma função
        // de formatar o valor para uma string
        database_list(db, sizeof(Medicine), medicine_format);
        printf("Select one Id to edit, or press [0] and Enter to exit...");
        char *input = (char *)malloc(sizeof(char) * 512);
        fgets(input, 512, stdin);
        trim(input);
        // caso escolha zero, volte pro começo
        if (atoi(input) == 0) {
          break;
        }
        if (isnumber(input)) {
          // essa função edita o elemento de id atoi(input) usando uma função
          // para identificar o id unico do valor,
          //  e como argumento final, recebe uma função para "ler" o valor,
          //  assim editando o conteudo
          database_edit(db, sizeof(Medicine), atoi(input), medicine_identity,
                        medicine_read);
        }
        break;
      case 3:
        database_list(db, sizeof(Medicine), medicine_format);
        printf("Select one Id to delete, or press [0] and Enter to exit...");
        char *input_ = (char *)malloc(sizeof(char) * 512);
        fgets(input_, 512, stdin);
        trim(input_);
        int input_int = atoi(input_);
        if (input_int == 0) {
          break;
        }
        // Aqui, iremos remover o elemento de id (atoi
        database_remove(db, sizeof(Medicine), medicine_identity, input_int);
        break;
      case 4:
        exit(1);
      default:
        break;
      }
    } else {
      continue;
    }
  }
  printf("Leaving...");
  return 0;
}
