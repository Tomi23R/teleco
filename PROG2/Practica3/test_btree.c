#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>

#include "btree.h"

#define N_ELEMS 1000

void compose_key(char *key, int number)
{
  sprintf(key, "%06d", number);
}

btree* insert_lineal(btree *t, int n)
{
  long long int i;
  char key[64];

  for(i = 0; i < n; i++) { 
    compose_key(key, i);
    t = btree_insert_node(t, key, (void*)i);
    if (t==NULL) return NULL;
  }

  return t;
}

btree* insert_eq(btree *t, long long int n0, long long int n1)
{
  char key[64];

  if (n1-n0 < 0) return t;

  compose_key(key, n0 + (n1-n0)/2);
  t = btree_insert_node(t, key, (void*)(n0 + (n1-n0)/2));
  if (t==NULL) return NULL;

  if ((t=insert_eq(t, n0, n0 + (n1-n0)/2 - 1))==NULL) return NULL;
  if ((t=insert_eq(t, n0 + (n1-n0)/2 + 1, n1))==NULL) return NULL;

  return t;
}
int search_all(btree *t, int to)
{
  char key[64];
  long long int i, info;


  for (i = 0; i < to; i++) {
    compose_key(key, i);
    info = (long long int)btree_find_element(t, key);
    if (info!=i) return 0;
  }

  return 1;
}

int test_newtree()
{
  btree * t = new_btree();

  destroy_btree(t);

  return 1;
}
int test_insertone()
{
  btree * t = new_btree();

  t = btree_insert_node(t, "a", "hola");
  if (t==NULL) return 0;

  destroy_btree(t);

  return 1;
}

int test_insert1()
{
  btree * t = new_btree();

  t = insert_lineal(t, N_ELEMS);
  
  if (t==NULL) return 0;

  destroy_btree(t);

  return 1;
}


int test_insert2()
{
  btree * t = new_btree();

  if ((t=insert_eq(t, 0, N_ELEMS))==NULL) return 0;

  destroy_btree(t);

  return 1;
}

int test_search1()
{
  btree * t = new_btree();

  if ((t=insert_lineal(t, N_ELEMS))==NULL) return 0;

  if (0==search_all(t, N_ELEMS)) return 0;

  destroy_btree(t);

  return 1;
}

int test_search2()
{
  btree * t = new_btree();

  if ((t=insert_eq(t, 0, N_ELEMS))==NULL) return 0;

  if (0==search_all(t, N_ELEMS+1)) return 0;

  destroy_btree(t);

  return 1;
}

int test_search3()
{
  char key[64];
  void *info;
  btree * t = new_btree();

  if ((t=insert_eq(t, 0, N_ELEMS))==NULL) return 0;

  sprintf(key, "%0d", N_ELEMS+1);
  info = btree_find_element(t, key);
  if (info!=NULL) return 0;

  destroy_btree(t);

  return 1;
}

int test_traverse()
{
  list *l;
  list_node *n;
  long long int n_eq;
  btree * t = new_btree();

  if ((t=insert_eq(t, 0, N_ELEMS))==NULL) return 0;

  l = new_list();
  btree_traverse(t,l);

  n = list_first(l);
  n_eq = 0;
  while(n) {
    if ((long long int)list_get_data(n)==n_eq) n_eq++;
    n = list_node_next(n);
  }

  destroy_list(l);
  destroy_btree(t);

  return n_eq==N_ELEMS+1;
}

int test_times()
{
  btree * t;
  struct timeval t1, t0;
  double i1, i2;

  t = new_btree();

  if ((t=insert_eq(t, 0, N_ELEMS*100))==NULL) return 0;

  gettimeofday(&t0, NULL);
  if (search_all(t, N_ELEMS*10)==0) return 0;
  gettimeofday(&t1, NULL);
  i1 = (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;

  gettimeofday(&t0, NULL);
  if (search_all(t, N_ELEMS*100)==0) return 0;
  gettimeofday(&t1, NULL);
  i2 = (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;

  printf("¿Es %g parecido a %g?\n", i1*10, i2);

  destroy_btree(t);

  return 1;
}

int main(int argn, char**argv) 
{
  assert(test_newtree());
  assert(test_insertone());
  assert(test_insert1());
  assert(test_insert2());
  assert(test_search1());
  assert(test_search2());
  assert(test_search3());
  assert(test_traverse());
  assert(test_times());

  printf("Test btree OK\n");

  return 1;
}
