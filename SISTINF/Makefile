########################################################################
# Autor: Gil Perez, Borja (bor.gil@predoc.uam.es)
# Fecha: 2018-10-18 (yyyy-mm-dd)
########################################################################
# The GNU compiler collection
CC = gcc #variable
# -O para aplicar el optimizador de codigo, -g para poder depurar, -Wall: avisos extra
CFLAGS = -O -g -Wall

LIBS = -lnetpbm -lpthread

# $ make
# $ make all
all: examen

# $@ es el item que aparece a la izquierda de ':'
# $< es el primer item en la lista de dependencias
# $^ son todos los archivos que se encuentran a la derecha de ':'

########################################################################
# P1 -create_pgm_file
########################################################################
#crear primero el objeto, por crea un .o por cada .c
examen.o : examen.c
	$(CC) -c $< $(CFLAGS)
examen: examen.o
	$(CC) $^ -o $@ $(CFLAGS) $(LIBS)

########################################################################
# Utilities
########################################################################
# Un objetivo falso ("phony target") es aquel que no es el nombre de un
# archivo, sino un nombre descriptivo de alguna accion, de algunas
# ordenes que se ejecutarán al requerirse explicitamente.
UTILS = info astyle valgrind doxygen clean dev-essential lubuntu1404-custom
.PHONY: $(UTILS)
# $ make info
info:
	##echo lo que hace es mostrar por pantalla la información
	@echo "<Grado en ingeniería de Tecnologías y servicios de Telecomunicación>"
	@echo "<Fundamentos de Sistemas Informáticos>"
	@echo "<Codigo de la entrega>"
	@echo "Autores:"
	@echo "	<Patricia, patricia.serranog01@estudiante.uam.es>"
	@echo "	<Autor, correo electronico>"
	@echo "Ejecutables: create_pgm_file rotate_pgm_file"
	@echo "	$(P1)"
	@echo "	$(P2)"
	@echo "	$(UTILS)"
# $ make astyle
astyle:
	astyle *.h *.c
	@echo "Run make clean to remove *.orig files if any file was formated."
# $ make valgrind ARGS="./<executable> [<arguments>]"
valgrind:
	valgrind --leak-check=full ${ARGS}
# $ make doxygen
doxygen:
	@rm -fr Doxyfile html latex
	@doxygen -g
	@doxygen Doxyfile
# $ make clean
clean:
	@rm -fr Doxyfile html latex examen
	@rm -f *.o *~ core *.orig $(P1) $(P2)

# $ make dev-essential
dev-essential:
	@echo "Installing essential developer tools."
	sudo apt-get install astyle build-essential nemiver nmon terminator valgrind
	sudo apt-get install doxygen graphviz
	sudo update-alternatives --config x-terminal-emulator
	sudo apt-get autoremove && sudo apt-get autoclean
# $ make lubuntu1404-custom
lubuntu1404-custom:
	@echo "Customizing Lubuntu 14.04"
	sudo apt-get install language-selector-gnome lubuntu-restricted-extras
	sudo apt-get purge abiword gnumeric && sudo apt-get install libreoffice libreoffice-l10n-es
	sudo add-apt-repository ppa:indicator-brightness/ppa
	sudo add-apt-repository ppa:webupd8team/java
	sudo apt-get update
	sudo apt-get install indicator-brightness
	sudo apt-get install oracle-java8-installer && sudo apt-get install oracle-java8-set-default
	sudo apt-get autoremove && sudo apt-get autoclean
