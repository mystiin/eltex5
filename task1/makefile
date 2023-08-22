SRC = add.c subt.c
OBJ = $(SRC:.c=.o)
LIBNAME = libcalc
LIB_STATIC = $(LIBNAME).a
LIB_DYNAMIC = $(LIBNAME).so
static: $(LIB_STATIC) 
dynamic: $(LIB_DYNAMIC)
$(LIB_STATIC): $(OBJ)
	ar rcs $(LIB_STATIC) $(OBJ)
$(LIB_DYNAMIC): $(OBJ)
	gcc -shared -o $(LIB_DYNAMIC) $(OBJ)
%.o: %.c
	gcc -c $< -o $@
clean:
	rm -f $(OBJ) $(LIB_STATIC) $(LIB_DYNAMIC)
