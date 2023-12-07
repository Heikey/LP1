#ifndef __DATABASE_H
#define __DATABASE_H

typedef struct TagDatabase Database;
int database_new_id(Database* db); Database *database_alloc();
Database *database_init(char *file_path);
void database_add(Database *db, char *value);
int database_goto(Database *db, int key);
int database_read(Database *db, char *dst, int key);
void database_list(Database* db);
void database_edit(Database* db, int key);

#endif
