# Makefile

SRC = add.c subtract.c main.c
OBJ = $(SRC:.c=.o)

LIBNAME = libcalc
LIB = $(LIBNAME).a 

all: app

app: $(OBJ) $(LIB)
    gcc $(OBJ) $(LIB) -o app

$(LIB): $(OBJ)
    ar rcs $(LIB) add.o subtract.o

%.o: %.c
    gcc -c $< -o $@

clean:
    rm -f $(OBJ) $(LIB) app
// add.c
int add(int a, int b) 
{
  return a + b; 
}

// subtract.c
int subtract(int a, int b) 
{
  return a - b;
}
// main.c
#include <stdio.h>

int add(int a, int b);
int subtract(int a, int b);

int main() {
  int x = add(2, 3);
  int y = subtract(10, 5);

  printf("x = %d\n", x); 
  printf("y = %d\n", y);
  
  return 0;
}