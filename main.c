#include "database.h"
#include "medicine.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_console() {
  // little hack for clear terminal in windows and *nix systems
  if (system("cls"))
    system("clear");
}

void trim(char* string) {
	if(string[strlen(string)-1] == '\n')
		string[strlen(string)-1] = '\0';
}

int isnumber(char* string) {
	for(int i = 0;i<strlen(string);++i){
		if(!isdigit(string[i])){
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

// Função para verificar se a entrada é um inteiro.
int entry_check(char choice) {
  // Verifica se a entrada é um número
  if (isdigit(choice)) {
    clear_buffer();
    return 1;
  } else {
    printf("ERRO: Character entered is not among the options!\n\n");
    clear_buffer();
    return 0;
  }
}

int main() {
  char choice;
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
    clear_console();
    if (entry_check(choice)) {
      int choice_ = atoi(&choice);
      switch (choice_) {
      case 1:
				;
        Medicine *med = medicine_alloc();
        if (medicine_read(med)) {
          char *serialized = medicine_serialize(med);
          database_add(db, serialized);
        } else {
					printf("ERRO: can't read the product info.\n");
				}
        break;
      case 2:
        database_list(db);
				printf("Select one Id to edit, or press [0] and Enter to exit...");

				char* input = (char*)malloc(sizeof(char)*512);
				fgets(input,512,stdin);
				trim(input);
				printf("NUMBER: %s",input);
				if(atoi(input) == 0){
					printf("zero!\n");
					break;
				}
				if(isnumber(input)) {
					database_edit(db, atoi(input));
				}
        break;
      case 3:
        database_list(db);
				printf("Select one Id to edit, or press [0] and Enter to exit...");
				char* input = (char*)malloc(sizeof(char)*512);
				fgets(input,512,stdin);
				trim(input);
				printf("NUMBER: %s",input);
				if(atoi(input) == 0){
					printf("zero!\n");
					break;
				}
				if(isnumber(input)) {
					database_edit(db, atoi(input));
				}
        break;
      case 4:
        exit(1);
      default:
        printf("Invalid digit!");
      }
    } else {
      continue;
    }
  }
  printf("Leaving...");
  return 0;
}
