CC = gcc
CFLAGS = -Wall -ansi -g
MOD = premiado.o premiados.o premio.o premios.o main3.o data_base.o list.o btree.o

all: practica3

test_premiado: premiado.o test_premiado.o
	$(CC) $(CFLAGS) -o $@ premiado.o test_premiado.o
	
test_premiados: premiados.o test_premiados.o premiado.o
	$(CC) $(CFLAGS) -o $@ premiados.o test_premiados.o premiado.o
	
test_premio: premio.o test_premio.o premiados.o premiado.o
	$(CC) $(CFLAGS) -o $@ premio.o test_premio.o premiados.o premiado.o
	
test_btree: btree.o list.o test_btree.o
	$(CC) $(CFLAGS) -o $@ btree.o list.o test_btree.o
	
practica3: $(MOD)
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
	
	$(CC) $(CFLAGS) -o $@ $(MOD)

.PHONY: clean dist tests runtests

clean:
	rm -f *.o practica3 test_premiado test_premiados test_premio test_btree
dist:
	tar -zcvf lab4111_gr1_p3.tgz *.c *.h *.txt datos 
tests: test_premiado test_premiados test_premio test_btree
runtests:
	@echo "#Premiado test---->"
	./test_premiado
	@echo "#Premiados test---->"
	./test_premiados
	@echo "#Premio test---->"
	./test_premio
	@echo "#Premio test---->"
	./test_btree

premiados.o: premiados.c premiados.h const.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@
	
premiado.o: premiado.c premiado.h const.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@

premio.o: premio.c premio.h premiados.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@

premios.o: premios.c premios.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@
	
principal.o: principal.c premios.h premiados.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@
	
test_premiado.o: test_premiado.c premiado.h const.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@
	
test_premiados.o: test_premiados.c premiado.h premiados.h const.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@
	
test_premio.o: test_premio.c premio.h const.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@
	
data_base.o: data_base.c premiados.h premios.h premio.h premiado.h 
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@
	
list.o: list.c list.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@
	
btree.o: btree.c btree.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@
	
test_btree.o: test_btree.c btree.h
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@
	
main3.o: main3.c 
	@echo "#---------------------------"
	@echo "# Generando $@"
	@echo "# Depende de $^"
	@echo "# Ha cambiado $<"
   
	$(CC) $(CFLAGS) -c $< -o $@	