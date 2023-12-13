#ifndef __DATABASE_H
#define __DATABASE_H
#include <stdlib.h>

typedef struct TagDatabase Database;
<<<<<<< HEAD
int database_new_id(Database* db); Database *database_alloc();
Database *database_init(char *file_path);
void database_add(Database *db, char *value);
int database_goto(Database *db, int key);
int database_read(Database *db, char *dst, int key);
void database_list(Database* db);
void database_edit(Database* db, int key);
void database_remove(Database* db, int key);

=======
Database *database_alloc();
Database *database_init(char *filename);
void database_add(Database *db, void *value, size_t size);
void database_edit(Database *db, int id, int func_indentify(void *val), void* func_read(void*));
void *database_filter(Database *db, size_t size,
                      int filter_func(void *val, void *arg), void *arg);
void database_remove(Database *db, size_t size, int func_identify(void *value),
                     int identifier);
>>>>>>> Oops...
#endif
