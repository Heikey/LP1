#define _XOPEN_SOURCE
#include "medicine.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFF_MAX 128

<<<<<<< HEAD
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
=======
void time_read(Time *time_, int now) {
  struct tm day_tm;
  if (now == 1) {
    time_t now_ = time(NULL);
    day_tm = *localtime(&now_);
  } else {
    printf("Digite o dia da compra:");
    char day_str[32];
    fflush(NULL);
    fgets(day_str, 32, stdin);
    strptime(day_str, "%d/%m/%Y", &day_tm);
  }
  time_->day = day_tm.tm_mday;
  time_->month = day_tm.tm_mon + 1;
  time_->year = day_tm.tm_year + 1900;
}

int time_cmp(Time *t1, Time *t2) {
  return t1->day == t2->day && t1->month == t2->month && t1->year == t2->year;
}

void time_print(Time *time) {
  printf("%d/%d/%d", time->day, time->month, time->year);
}

Medicine *medicine_alloc() {
  Medicine *out = (Medicine *)malloc(sizeof(Medicine));
  return out;
}

inline void trim(char *string) {
  if (string[strlen(string) - 1] == '\n')
    string[strlen(string) - 1] = '\0';
}

int medicine_read(Medicine *med) {
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
  scanf("%li", &med->code);

  printf("Digite o preço do produto:");
  scanf("%f", &med->price);

  printf("Foi comprado hoje?[S/N]");
  Time buy_date;
  while (1) {
    char awns;
    scanf("%c", &awns);
    if (awns == 's') {
      time_read(&buy_date, 1);
      break;
    } else if (awns == 'n') {
      time_read(&buy_date, 0);
      break;
    }
  }
  med->buy_date = buy_date;
  return 1;
}

void medicine_print(Medicine *med) {
  printf("Nome: %s\n", med->name);
  printf("Laboratorio: %s\n", med->lab);
  printf("Fornecedor: %s\n", med->supplier);
  printf("Codigo: %lil\n", med->code);
  printf("Preço: %.2f\n", med->price);
  time_print(&med->buy_date);
}

int medicine_identity(void *med) { return ((Medicine *)med)->ID; }

// int func(val,arg)

int filter_by_id(void *val, void *arg) {
  return ((Medicine *)val)->ID == *(int *)arg;
}

int filter_by_name(void *val, void *arg) {
  return strcmp(((Medicine *)val)->name, (char *)arg) == 0;
}
int filter_by_lab(void *val, void *arg) {
  return strcmp(((Medicine *)val)->lab, (char *)arg) == 0;
}
int filter_by_supplier(void *val, void *arg) {
  return strcmp(((Medicine *)val)->supplier, (char *)arg) == 0;
}
int filter_by_buy_date(void *val, void *arg) {
  return time_cmp(&((Medicine *)val)->buy_date, (Time *)arg);
>>>>>>> Medicine: Update Medicine struct and functions
}
