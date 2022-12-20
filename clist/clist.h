#ifndef CLIST_H_
#define CLIST_H_

#ifdef __cplusplus
extern "C"
{
#endif

  typedef struct _linked_list
  {
    void (*push) (struct _linked_list * l, void *o);
    void (*insert) (struct _linked_list * l, void *o, int n);
    void (*remove) (struct _linked_list * l, int n);
    void *(*at) (struct _linked_list * l, int n);
    int (*size) (struct _linked_list * l);
    void (*clear) (struct _linked_list * l);
    void (*free) (struct _linked_list * l);
    void (*print) (struct _linked_list * l);
    void (*for_each) (struct _linked_list * l, void (*func_ptr) (void *o));
    int (*find) (struct _linked_list * l, int (*func_ptr) (void *o));
    void *_private_data;
  } clist_t;

  clist_t *clist_create (unsigned int element_size);

#ifdef __cplusplus
}
#endif

#endif				// CLIST_H_
