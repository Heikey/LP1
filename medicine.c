#define _XOPEN_SOURCE
#define _GNU_SOURCE
#include <string.h>
#include "medicine.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFF_MAX 128

// Essa função remove o \n da string
inline void trim(char* string) {
	if(string[strlen(string)-1] == '\n')
		string[strlen(string)-1] = '\0';
}

typedef struct TagMedicine {
	char* name;
	char* lab;
	char* supplier;
	long int code;
	float price;
} Medicine;

// Função responsavel pelo alocamento da struct
Medicine* medicine_alloc() {
	Medicine* out = (Medicine*)malloc(sizeof(Medicine));
	out->name = (char*)malloc(sizeof(char) * BUFF_MAX);
	out->lab = (char*)malloc(sizeof(char) * BUFF_MAX);
	out->supplier = (char*)malloc(sizeof(char) * BUFF_MAX);
	return out;
}

// Pega os dados inseridos pelo usuario e passa pra struct Medicine
int medicine_read(Medicine* med) {
	printf("Escreva o nome do produto:");
	fflush(stdin);
	fgets(med->name, BUFF_MAX, stdin);
	trim(med->name);

	printf("Escreva o nome do laboratorio:");
	fflush(stdin);
	fgets(med->lab, BUFF_MAX, stdin);
	trim(med->lab);
	
	printf("Escreva o nome do fornecedor:");
	fflush(stdin);
	fgets(med->supplier, BUFF_MAX, stdin);
	trim(med->supplier);
	
	printf("Digite o codigo do produto:");
	scanf("%li",&med->code);

	printf("Digite o preço do produto:");
	scanf("%f", &med->price);
	return 1;
}

// Transformar a struct em string
char* medicine_serialize(Medicine* med) {
		char* string;
		asprintf(&string,"\"%s\", \"%s\", \"%s\", \"%li\", \"%.2f\"",med->name,med->lab,med->supplier,med->code,med->price);
		return string;
}

// Função que separa os valores das chaves
void separate_key_val(char* line, int *key, char* val) {
		char* id = (char*)malloc(10);
		id = strsep(&line, "|");
		if(key!=NULL)
			*key = atoi(id);
		if(val!=NULL)
			*val = *line;
}


void medicine_deserialize(char* string, Medicine* med) {
	int selected;
	char* value = (char*)malloc(sizeof(char)*512);
	separate_key_val(string, NULL, value);
	char* name = strsep(&value,"\", ");
	char* lab = strsep(&value,"\", ");
	char* supplier = strsep(&value,"\", ");
	char* code = strsep(&value,"\", ");
	char* price = strsep(&value,"\", ");
	char* date = strsep(&value,"\", ");
}
