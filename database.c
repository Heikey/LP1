#include "database.h"
#include "medicine.h"
#include <stdio.h>

typedef struct TagDatabase {
  FILE *file;
  char *filename;
} Database;

Database *database_alloc() { return (Database *)malloc(sizeof(Database)); }

Database *database_init(char *filename) {
  Database *db = database_alloc();
  FILE *file;
  if ((file = fopen(filename, "r+b")) == NULL)
    file = fopen(filename, "w+b");

  db->file = file;
  db->filename = filename;
  rewind(db->file);
  return db;
}

void database_add(Database *db, void *value, size_t size) {
  fseek(db->file, 0, SEEK_END);
  int valid = fwrite(value, size, 1, db->file);
  rewind(db->file);
}

void *database_filter(Database *db, size_t size,
                      int filter_func(void *value, void *arg), void *arg) {
  void *tmp;
  while (1) {
    if (fread(tmp, size, 1, db->file) == 0) {
      return NULL;

      if (filter_func(tmp, arg) == 1) {
        fseek(db->file, -size, SEEK_CUR);
        return tmp;
      }
    }
  }
}

void database_remove(Database *db, size_t size, int func_identify(void *value),
                     int identifier) {
  FILE *tmp = fopen("tmp.txt", "w+b");
  void *tmp_obj;
  while (fread(tmp_obj, size, 1, db->file) != 0) {
    if (func_identify(tmp_obj) != identifier) {
      fwrite(tmp_obj, size, 1, tmp);
    }
  }
  fclose(tmp);
  fclose(db->file);
  remove(db->filename);
  rename("tmp.txt", db->filename);
  db->file = fopen(db->filename, "r+b");
}
