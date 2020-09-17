
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "premiado.h"
#include "premiados.h"
#include "const.h"

void add_premiados(premiados *aa, int n, int with_ids)
{ 
  int i;
  char *nombres[] = {"Supercalifragilisticuespialidoso", "Hola mundo"};
  premiado * a;

  for(i = 0; i < n; i++) {
    a = new_premiado();
    if (with_ids) {
      set_premiado_id(a, i+1);
    }
    set_premiado_nombre(a, nombres[i%2]);
    add_premiado(aa, a);
  }

}

int test_creacion()
{
  premiados * aa = new_premiados();

  destroy_premiados(aa);

  return 1;
}

int test_add_simple()
{
  premiado *a;
  premiados * aa = new_premiados();

  add_premiados(aa, 1, FALSE);
  if (1 != get_n_premiados(aa)) {
    return 0;
  }

  a = get_premiado_i(aa, 0);
  if (a == NULL) {
    return 0;
  }

  destroy_premiado(a);
  destroy_premiados(aa);

  return 1;
}

int test_get_premiado_by_id(int with_ids)
{
  int i;
  int ok;
  premiado *a;
  premiados * aa = new_premiados();

  add_premiados(aa, 10, with_ids ? TRUE : FALSE);

  ok = 1;
  for( i = get_n_premiados(aa)-1; i>=0; i--) {
    if (NULL==(a=get_premiado_by_id(aa, i+1))) {
      printf("ERROR: No se encuentra el premiado con id %d\n", i+1);
      ok = 0;
      break;
    }
    else if (get_premiado_id(a)!=i+1) {
      printf("ERROR: premiado encontrado con id distinto al pedido\n");
      ok = 0;
      break;
    }
  }

  for( i = get_n_premiados(aa)-1; i>=0; i--) {
    a=get_premiado_i(aa, i);
    destroy_premiado(a);
  }

  destroy_premiados(aa);

  return ok;
}


int test_print()
{
  premiados * aa = new_premiados();

  print_premiados(aa);

  destroy_premiados(aa);

  return 1;
}

/**
 * Funcion main de test 
 *
 */
int main(int argn, char**argv) 
{
  assert(test_creacion());
  assert(test_add_simple());
  /*assert(test_get_premiado_by_id(FALSE));*/
  assert(test_get_premiado_by_id(TRUE));
  assert(test_print());

  printf("premiados.c OK\n");

  return 0;
}
