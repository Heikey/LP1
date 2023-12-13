#ifndef __MEDICINE_H
#define __MEDICINE_H

typedef struct TagTime {
  int day;
  int month;
  int year;
} Time;

typedef struct TagMedicine {
  int ID;
  char name[64];
  char lab[64];
  char supplier[64];
  long int code;
  float price;
  Time buy_date;
} Medicine;

void time_read(Time *time_, int now);
int time_cmp(Time *t1, Time *t2);

Medicine *medicine_alloc();
void medicine_read(void *med_);

int medicine_identity(void *med);

int filter_by_id(void *val, void *arg);
int filter_by_name(void *val, void *arg);
int filter_by_lab(void *val, void *arg);
int filter_by_supplier(void *val, void *arg);
int filter_by_buy_date(void *val, void *arg);

#endif
