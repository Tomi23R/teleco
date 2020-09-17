
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "premiado.h"
#include "const.h"

int test_creacion()
{
  premiado * t = new_premiado();

  destroy_premiado(t);

  return 1;
}

int test_set_get_id()
{
  long long int id = 123;
  long long int id0, id2;

  premiado * t = new_premiado();

  id0 = get_premiado_id(t);

  set_premiado_id(t, id);
  id2 = get_premiado_id(t);

  destroy_premiado(t);

  return id0 == NULL_ID && id == id2 ? 1 : 0;
}

int test_set_get_nombre()
{
  char nombre[] = {"Supercalifragislisticuespialidoso"};
  int ret;

  premiado * t = new_premiado();

  set_premiado_nombre(t, nombre);
  ret = strcmp(get_premiado_nombre(t), nombre);

  if (get_premiado_nombre(t)==nombre) {
    printf("ERROR: No copias la cadena nombre\n");
    ret = 1;
  }

  destroy_premiado(t);

  return ret==0 ? 1 : 0;
}

int test_set_get_pais()
{
  char pais[] = {"ES"};
  int ret;

  premiado * t = new_premiado();

  set_premiado_pais(t, pais);
  ret = strcmp(get_premiado_pais(t), pais);

  if (get_premiado_pais(t)==pais) {
    printf("ERROR: No copias la cadena pais\n");
    ret = 1;
  }

  destroy_premiado(t);

  return ret==0 ? 1 : 0;
}

int test_gestion_memoria()
{
  char *txt = malloc(100);

  strcpy(txt, "test");

  premiado * t = new_premiado();

  set_premiado_nombre(t, txt);
  set_premiado_nombre(t, txt);
  set_premiado_pais(t, txt);
  set_premiado_pais(t, txt);

  free(txt);

  destroy_premiado(t);

  return 1;
}

int test_set_get_genero()
{
  int ret;

  premiado * t = new_premiado();

  set_premiado_genero(t, MUJER);
  ret = MUJER == get_premiado_genero(t);

  destroy_premiado(t);

  return ret==1 ? 1 : 0;
}

int test_print()
{
  premiado * t = new_premiado();

  set_premiado_id(t, 1);
  set_premiado_nombre(t, "Hola mundo");
  print_premiado(t);

  destroy_premiado(t);

  return 1;
}

/**
 * Funcion main de test 
 *
 */
int main(int argn, char**argv) 
{

  assert(test_creacion());
  assert(test_set_get_id());
  assert(test_set_get_nombre());
  assert(test_set_get_pais());
  assert(test_gestion_memoria());
  assert(test_set_get_genero());
  assert(test_print());

  printf("premiado.c OK\n");

  return 0;
}
