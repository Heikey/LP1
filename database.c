#include "database.h"
#include "medicine.h"
#include <stdio.h>

// a struct só guarda o ponteiro pro arquivo e pro nome do arquivo
typedef struct TagDatabase {
  FILE *file;
  char *filename;
} Database;

// função para alocar a struct
Database *database_alloc() { return (Database *)malloc(sizeof(Database)); }

// inicializa a Database, abrindo/criando o arquivo
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

// essa função recebe uma função para formatar o valor para string
void database_list(Database *db, size_t size, void format(void *val)) {
  void *tmp_obj;
  while (fread(tmp_obj, size, 1, db->file) != 0) {
		format(tmp_obj);
  }
	rewind(db->file);
}

// adiciona um valor para a Database
void database_add(Database *db, void *value, size_t size) {
  fseek(db->file, 0, SEEK_END);
  int valid = fwrite(value, size, 1, db->file);
  rewind(db->file);
}

// essa função recebe como argumentos a database, o tamanho do tipo do valor,
// o id unico do valor que quer editar, uma função para pegar o id de um certo
// tipo e uma função que edita o valor.
void database_edit(Database *db, size_t size, int id,
                   int func_identify(void *val), void func_read(void *)) {
  FILE *tmp = fopen("tmp.txt", "w+b");
  void *tmp_obj;
  while (fread(tmp_obj, size, 1, db->file) != 0) {
    if (func_identify(tmp_obj) != id) {
      fwrite(tmp_obj, size, 1, tmp);
    } else {
    }
  }
  fclose(tmp);
  fclose(db->file);
  remove(db->filename);
  rename("tmp.txt", db->filename);
  db->file = fopen(db->filename, "r+b");
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
