#include "clist.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct _node
{
  struct _node *next;
  void *data;
} node_t;

typedef struct _clist_private_
{
  int num_elements;
  unsigned int element_size;
  node_t *head;
  node_t *tail;
} clist_priv_t;


void clist_push (clist_t * l, void *o);
void clist_insert (clist_t * l, void *o, int n);
void clist_remove (clist_t * l, int n);
void *clist_at (clist_t * l, int n);
int clist_size (clist_t * l);
void clist_clear (clist_t * l);
void clist_free (clist_t * l);
void clist_print (clist_t * l);
void clist_for_each (clist_t * l, void (*func_ptr) (void *o));
int clist_find (clist_t * l, int (*func_ptr) (void *o));

clist_t *
clist_create (unsigned int element_size)
{
  clist_t *list = malloc (sizeof (clist_t));
  clist_priv_t *priv = malloc (sizeof (clist_priv_t));
  if (!list || !priv) {
    fprintf (stderr, "[clist:create] could not allocate clist.\n");
    return NULL;
  }

  priv->num_elements = 0;
  priv->element_size = element_size;
  priv->head = NULL;
  priv->tail = NULL;
  list->push = &clist_push;
  list->print = &clist_print;
  list->size = &clist_size;
  list->at = &clist_at;
  list->clear = &clist_clear;
  list->free = &clist_free;
  list->for_each = &clist_for_each;
  list->find = &clist_find;
  list->_private_data = priv;

  return list;
}

void
clist_push (clist_t * l, void *o)
{
  if (!l || !o) {
    fprintf (stderr, "[clist:push] function do not accept NULL.\n");
    return;
  }

  clist_priv_t *p = (clist_priv_t *) l->_private_data;

  node_t *node = (node_t *) malloc (sizeof (node_t));
  void *data = (void *) malloc (p->element_size);

  if (!node || !data) {
    fprintf (stderr, "[clist:push] could not allocate new node.\n");
    assert (node && data);
    return;
  }

  if (p->num_elements) {
    p->tail->next = node;
    node->data = data;
    p->tail = node;
    node->next = NULL;
  }
  else {
    node->next = NULL;
    node->data = data;
    p->head = node;
    p->tail = node;
  }
  memcpy (data, o, p->element_size);
  p->num_elements++;
}

void
clist_clear (clist_t * l)
{
  if (!l) {
    fprintf (stderr, "[clist:clear] function do not accept NULL.\n");
    return;
  }

  clist_priv_t *p = (clist_priv_t *) l->_private_data;
  node_t *node = p->head;
  node_t *tmp = NULL;

  for (int i = 0; i < p->num_elements; ++i) {
    tmp = node->next;
    free (node->data);
    free (node);
    node = tmp;
  }

  p->num_elements = 0;
  p->head = NULL;
  p->tail = NULL;
}

void
clist_free (clist_t * l)
{
  if (!l) {
    fprintf (stderr, "[clist:clear] function do not accept NULL.\n");
    return;
  }
  clist_clear (l);
  clist_priv_t *p = (clist_priv_t *) l->_private_data;
  free (p);
  free (l);
  l = NULL;
}

void *
clist_at (clist_t * l, int n)
{
  if (!l) {
    fprintf (stderr, "[clist:at] function do not accept NULL.\n");
    return NULL;
  }

  clist_priv_t *p = (clist_priv_t *) l->_private_data;

  if (n < 0 || n >= p->num_elements) {
    fprintf (stderr, "[clist:at] invalid indexing.\n");
    return NULL;
  }

  node_t *node = p->head;
  for (int i = 0; i != n; ++i) {
    if (node) {
      node = node->next;
    }
  }

  return node->data;

}


int
clist_size (clist_t * l)
{
  if (!l) {
    fprintf (stderr, "[clist:clear] function do not accept NULL.\n");
    return;
  }
  clist_priv_t *p = (clist_priv_t *) l->_private_data;
  return p->num_elements;
}

void
clist_print (clist_t * l)
{
  clist_priv_t *p = (clist_priv_t *) l->_private_data;
  printf ("\n[clist:print] size = %i  element_size = %u   "
	  "head = %p   tail = %p\n\n", p->num_elements, p->element_size,
	  p->head, p->tail);
}

void
clist_for_each (clist_t * l, void (*func_ptr) (void *o))
{
  if (!l || !func_ptr) {
    fprintf (stderr, "[clist:for_each] function do not accept NULL.\n");
    return;
  }
  clist_priv_t *p = (clist_priv_t *) l->_private_data;
  node_t *node = p->head;
  for (int i = 0; i < p->num_elements; ++i) {
    if (node) {
      func_ptr (node->data);
      node = node->next;
    }
  }
}

int
clist_find(clist_t * l, int (*func_ptr) (void *o))
{
  if (!l || !func_ptr) {
    fprintf (stderr, "[clist:for_each] function do not accept NULL.\n");
    return -1;
  }
  clist_priv_t *p = (clist_priv_t *) l->_private_data;
  node_t *node = p->head;
  for (int i = 0; i < p->num_elements; ++i) {
    if (node) {
      if(func_ptr (node->data)){
        return i;
      }
      else {
        node = node->next;
      }
    }
  }
  return -1;
}