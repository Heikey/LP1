#ifndef __DATABASE_H
#define __DATABASE_H
#include <stdlib.h>

typedef struct TagDatabase Database;
Database *database_alloc();
Database *database_init(char *filename);
void database_list(Database *db, size_t size, void format(void *val));
void database_add(Database *db, void *value, size_t size);
void database_edit(Database *db, size_t size, int id,
                   int func_indentify(void *val), void func_read(void *));
void database_remove(Database *db, size_t size, int func_identify(void *value),
                     int identifier);
#endif
