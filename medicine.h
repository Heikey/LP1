#ifndef __MEDICINE_H
#define __MEDICINE_H
	
typedef struct TagMedicine Medicine;
Medicine* medicine_alloc();
int medicine_read(Medicine* med);
char *medicine_serialize(Medicine *med); 


#endif
