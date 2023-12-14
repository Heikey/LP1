#define _XOPEN_SOURCE
#include "medicine.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFF_MAX 128

void time_read(Time *time_) {
  struct tm day_tm;
	time_t now_ = time(NULL);
	day_tm = *localtime(&now_);
  time_->day = day_tm.tm_mday;
  time_->month = day_tm.tm_mon + 1;
  time_->year = day_tm.tm_year + 1900;
}

void time_print(Time *time) {
  printf("Dia de compra:%d/%d/%d\n", time->day, time->month, time->year);
}

Medicine *medicine_alloc() {
  return (Medicine *)malloc(sizeof(Medicine));
}

inline void trim(char *string) {
  if (string[strlen(string) - 1] == '\n')
    string[strlen(string) - 1] = '\0';
}

void medicine_read(void *med_) {
	Medicine* med;

	if(med_ == NULL){
		med = medicine_alloc(); 
	}else{
		med = (Medicine*) med_;	
	}
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

  Time buy_date;
	time_read(&buy_date);
  med->buy_date = buy_date;
}

void medicine_format(void *med_) {
	Medicine* med = (Medicine*) med_;
	printf("Id: %d\n",med->ID);
  printf("Nome: %s\n", med->name);
  printf("Laboratorio: %s\n", med->lab);
  printf("Fornecedor: %s\n", med->supplier);
  printf("Codigo: %li\n", med->code);
  printf("Preço: %.2f\n", med->price);
  time_print(&med->buy_date);
	printf("\n");
}

int medicine_identity(void *med) { return ((Medicine *)med)->ID; }
