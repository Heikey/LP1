#include "database.h"
#include "medicine.h"
#include <stdio.h>

typedef struct TagDatabase {
  FILE *file;
  char *filename;
} Database;

<<<<<<< HEAD
int database_new_id(Database *db) {
  static int id = 0;
  if (id == 0) {
    char buf;
    rewind(db->file_start);
    if (getc(db->file_start) == EOF) {
      return ++id;
    }
    fseek(db->file_start, 0, SEEK_END);
		char buff;
    while ((buff=getc(db->file_start)) != '\n') {
			if(buff == -1){
				rewind(db->file_start);
				break;
			}
      fseek(db->file_start, -2, SEEK_CUR);
    }
    char *last_line = (char *)malloc(512);
    fgets(last_line, 512, db->file_start);
    separate_key_val(last_line, &id, NULL);
    fseek(db->file_start, 0, SEEK_END);
  }
  return ++id;
}
// alloc Database
Database *database_alloc() {
  Database *db = (Database *)malloc(sizeof(Database));
  db->filename = (char *)malloc(sizeof(char) * 512);
  return db;
}
=======
Database *database_alloc() { return (Database *)malloc(sizeof(Database)); }
>>>>>>> Oops...

Database *database_init(char *filename) {
  Database *db = database_alloc();
  FILE *file;
<<<<<<< HEAD
  // if(file not exist)
  //   file = new file
  if ((file = fopen(file_path, "r+")) == NULL) {
    file = fopen(file_path, "w+");
  };
  // check if file is created
  assert(file != NULL);
  Database *db = database_alloc();
  db->filename = file_path;
  db->file_start = file;
=======
  if ((file = fopen(filename, "r+b")) == NULL)
    file = fopen(filename, "w+b");

  db->file = file;
  db->filename = filename;
  rewind(db->file);
>>>>>>> Oops...
  return db;
}

void database_add(Database *db, void *value, size_t size) {
  fseek(db->file, 0, SEEK_END);
  int valid = fwrite(value, size, 1, db->file);
  rewind(db->file);
}

<<<<<<< HEAD
void database_list(Database *db) {
  char *buff = (char *)malloc(sizeof(char) * 512);
  while (fgets(buff, 512, db->file_start)) {
    printf("%s\n", buff);
	};
	rewind(db->file_start);
}

void database_edit(Database *db, int key) {
  FILE *tmp = fopen("tmp.txt", "w");
  rewind(db->file_start);
  char *line = (char *)malloc(sizeof(char) * 512);
  while (fgets(line, 512, db->file_start) != NULL) {
    int k;
    separate_key_val(line, &k, NULL);
    if (k == key) {
      Medicine *med = medicine_alloc();
      medicine_read(med);
      char *out = medicine_serialize(med);
      fprintf(tmp, "%d|%s\n", key, out);
    } else {
      fprintf(tmp, "%s", line);
    }
	}
	fclose(db->file_start);
	fclose(tmp);
	remove(db->filename);
	rename("tmp.txt", db->filename);
	db->file_start = fopen(db->filename,"r+");
=======
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
>>>>>>> Oops...
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
