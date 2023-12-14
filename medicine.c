#define _XOPEN_SOURCE
#include "medicine.h"
#include "database.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFF_MAX 128

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
  printf("Dia de compra:%d/%d/%d\n", time->day, time->month, time->year);
}

Medicine *medicine_alloc() {
  Medicine *out = (Medicine *)malloc(sizeof(Medicine));
  return out;
}

inline void trim(char *string) {
  if (string[strlen(string) - 1] == '\n')
    string[strlen(string) - 1] = '\0';
}

void medicine_read(void *med_) {
	Medicine* med = (Medicine*) med_;
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
}

void medicine_format(void *med_) {
	Medicine* med = (Medicine*) med_;
	printf("Id: %d\n",med->ID);
  printf("Nome: %s\n", med->name);
  printf("Laboratorio: %s\n", med->lab);
  printf("Fornecedor: %s\n", med->supplier);
  printf("Codigo: %lil\n", med->code);
  printf("Preço: %.2f\n", med->price);
  time_print(&med->buy_date);
	printf("\n");
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
}
