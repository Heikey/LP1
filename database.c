#include "database.h"
#include "medicine.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline void separate_key_val(char *line, int *key, char *val) {
  char *id = (char *)malloc(10);
  id = strsep(&line, "|");
  if (key != NULL)
    *key = atoi(id);
  if (val != NULL)
    *val = *line;
}
// store only the beginning of the file
typedef struct TagDatabase {
  FILE *file_start;
  char *filename;
} Database;

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
			printf("stuck in newid");
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

// initialize the database, creating stream to the file
Database *database_init(char *file_path) {
  FILE *file;
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
  return db;
}

void database_add(Database *db, char *value) {
  // goto the end of file and add the key|value
  fseek(db->file_start, 0, SEEK_END);
  fprintf(db->file_start, "%d|%s\n", database_new_id(db), value);
  rewind(db->file_start);
}

// find the line that has the key and set the file ptr to this line
int database_goto(Database *db, int key) {
  int len = 0;
  while (key /= 10) {
    len++;
  };
  rewind(db->file_start);
  char line[256] = {0};
  char valid = 0;
  while (fgets(line, 256, db->file_start) != NULL) {
		printf("stuck in goto");
    int find_key;
    separate_key_val(line, &find_key, NULL);
    if (find_key == key) {
      valid = 1;
    }
    // is valid
    if (valid == 1) {
      fseek(db->file_start, -strlen(line), SEEK_CUR);
      return 1;
    };
  }
  rewind(db->file_start);
  return 0;
}

// search value of a key, and set dest to value
int database_read(Database *db, char *dest, int key) {
  if (database_goto(db, key) == 0) {
    perror("can't find query.");
    return 0;
  };
  fgets(dest, 256, db->file_start);
  rewind(db->file_start);
  return 1;
}

void database_list(Database *db) {
  char *buff = (char *)malloc(sizeof(char) * 512);
  while (fgets(buff, 512, db->file_start)) {
    printf("%s\n", buff);
  };
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
      fprintf(tmp, "%s\n", out);
    } else {
      fprintf(tmp, "%s", line);
    }
	}
	fclose(db->file_start);
	printf("remove success? %d\n",remove(db->filename));
	rename("tmp.txt", db->filename);
	db = database_init(db->filename);
}


void database_remove(Database* db, int key) {
  FILE *tmp = fopen("tmp.txt", "w");
  rewind(db->file_start);
  char *line = (char *)malloc(sizeof(char) * 512);
  while (fgets(line, 512, db->file_start) != NULL) {
    int k;
    separate_key_val(line, &k, NULL);
    if (k == key) {
			;
    } else {
      fprintf(tmp, "%s", line);
    }
	}
	fclose(db->file_start);
	printf("remove success? %d\n",remove(db->filename));
	rename("tmp.txt", db->filename);
	db = database_init(db->filename);


}
