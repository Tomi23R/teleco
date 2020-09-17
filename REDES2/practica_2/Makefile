#---------------------------------------------------------------
# Otro Makefile
#---------------------------------------------------------------
# La siguiente no es necesariamente requerida, se agrega para
# mostrar como funciona.

.SUFFIXES: .o .c
.c.o:
	$(CC) -c $(CFLAGS) $<


# Macros

CC = gcc 
CFLAGS = -g -Wall -lpcap -lpthread
SRC1 = main_enviar.c rc_funcs.c nivelEth.c rc_funcs.h  niveEth.h
SRC2 = main_recibir.c rc_funcs.c nivel1a.c rc_funcs.h nivelEth.h
OBJ1 = main_enviar.o nivelEth.o rc_funcs.o
OBJ2 = main_recibir.o nivelEth.o rc_funcs.o


# Reglas expl citas
all: receptor emisor
receptor: $(OBJ1)
	$(CC)  $(OBJ1) -o enviar $(CFLAGS) 
emisor: $(OBJ2)
	$(CC) $(OBJ2) -o recibir $(CFLAGS) 

clean:
	$(RM) $(OBJ1) $(OBJ2) enviar recibir

# Reglas implicitas
rc_funcs.o: rc_funcs.c rc_funcs.h
main_recibir.o: main_recibir.c
main_enviar.o: main_enviar.c
nivel1a.o: nivel1a.c nivel1a.h
