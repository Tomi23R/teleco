
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "premio.h"
#include "const.h"

int test_creacion()
{
  premio * galardon = new_premio();

  destroy_premio(galardon);

  return 1;
}

int test_set_get_id()
{
  int id = 123;
  int id0, id2;

  premio * galardon = new_premio();
  
  id0 = get_premio_id(galardon);

  set_premio_id(galardon, id);
  id2 = get_premio_id(galardon);

  destroy_premio(galardon);

  return id0 == NULL_ID && id == id2 ? 1 : 0;
}

int test_set_get_anio()
{
  int anio = 2018;
  int ret;

  premio * galardon = new_premio();

  set_premio_anio(galardon, anio);
  ret = get_premio_anio(galardon) == anio;

  destroy_premio(galardon);

  return ret;
}

int test_set_get_categoria()
{
  char txt[] = {"fisica"};
  int ret;

  premio * galardon = new_premio();

  set_premio_categoria(galardon, txt);
  ret = strcmp(get_premio_categoria(galardon), txt);

  destroy_premio(galardon);

  return ret==0 ? 1 : 0;
}


int test_premio_premiados()
{
  premio * galardon;
  premiado *t1, *t2, *t3;
  BOOL ret1, ret2, ret3;

  galardon = new_premio();

  set_premio_id(galardon, 1);
  set_premio_anio(galardon, 2018);

  t1 = new_premiado();
  set_premiado_id(t1,1);
  set_premiado_nombre(t1,"Hola mundo");
  add_premio_premiado(galardon, t1);
   
  t2 = new_premiado();
  set_premiado_id(t2,2);
  set_premiado_nombre(t2,"Hola de nuevo");
  add_premio_premiado(galardon, t2);

  ret1 = has_premio_premiado(galardon, t1);
  ret2 = has_premio_premiado(galardon, t2);
  
  t3 = new_premiado();
  set_premiado_id(t3,3);
  set_premiado_nombre(t3,"Hola hola");

  ret3 = has_premio_premiado(galardon, t3);

  destroy_premio(galardon);
  destroy_premiado(t1);
  destroy_premiado(t2);
  destroy_premiado(t3);

  return ret1==TRUE && ret2==TRUE && ret3==FALSE; 
}

int test_print()
{
  premio * galardon = new_premio();

  set_premio_id(galardon, 1);
  set_premio_anio(galardon, 2018);
  set_premio_categoria(galardon, "Pepe Perez");
  print_premio(galardon);

  destroy_premio(galardon);

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
  assert(test_set_get_anio());
  assert(test_set_get_categoria());
  assert(test_premio_premiados());
  assert(test_print());

  printf("premio.c OK\n");

  return 0;
}
