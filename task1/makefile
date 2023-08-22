SRC = add.c subt.c main.c
OBJ = $(SRC:.c=.o)

LIBNAME = libcalc
LIB = $(LIBNAME).a 

all: app

app: $(OBJ) $(LIB)
	gcc $(OBJ) $(LIB) -o app

$(LIB): $(OBJ)
	ar rcs $(LIB) add.o subt.o

%.o: %.c
	gcc -c $< -o $@

clean:
	rm -f $(OBJ) $(LIB) app