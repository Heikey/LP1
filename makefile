CC = clang
ARGS = -g

build:
	$(CC) $(ARGS) medicine.c database.c main.c

run:
	$(CC) $(ARGS) medicine.c database.c main.c
	./a.out

