#include "database.h"
#include "medicine.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_console() {
  // Limpa o console
  if (system("cls"))
    system("clear");
}

void trim(char *string) {
  if (string[strlen(string) - 1] == '\n')
    string[strlen(string) - 1] = '\0';
}

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
      case 1:;
        Medicine *med = medicine_alloc();
        medicine_read(med); 
				database_add(db, med, sizeof(Medicine));
        break;
      case 2:
        printf("Select one Id to edit, or press [0] and Enter to exit...");
        // database_list(db);
        char *input = (char *)malloc(sizeof(char) * 512);
        fgets(input, 512, stdin);
        trim(input);
        if (atoi(input) == 0) {
          break;
        }
        if (isnumber(input)) {
          database_edit(db, atoi(input), medicine_identity, medicine_read);
        }
        break;
      case 3:
        // database_list(db);
        printf("Select one Id to edit, or press [0] and Enter to exit...");
        char *input_ = (char *)malloc(sizeof(char) * 512);
        fgets(input_, 512, stdin);
        trim(input_);
        if (atoi(input_) == 0) {
          break;
        }
        if (isnumber(input_)) {
          database_remove(db, sizeof(Medicine), medicine_identity, 1);
          break;
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
