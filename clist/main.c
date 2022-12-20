
#include "clist.h"

typedef struct client
{
  int sockfd;
  int id;
} client_t;

void
func (void *data)
{
  client_t *client = (client_t *) data;
  if (client->sockfd % 2 == 0) {
    client->sockfd *= 2;
  }
  printf ("%i ", client->sockfd);
}

int
find(void *data, int uid)
{
  client_t *client = (client_t *) data;
  if (client->id == uid) {
  	return 1;
  }
  else
  	return 0;
}



int
main (int argc, char *argv[])
{
  if(argc != 2) {
    printf ("Syntax: <./test> <num elements>\n");
    return 1;
  }

  clist_t *list = clist_create(sizeof(client_t));

  const int N = atoi(argv[1]);
  printf ("Add %i elements: ", N);
  for (int i = 0; i < N; ++i) {
    client_t client = { i, i };
    list->push (list, (void *) &client);
    printf ("%i ", client.sockfd);
  }

  printf ("\n\nApply for_each (x2 on even): ", N);
  list->for_each (list, &func);
  printf ("\n");

  list->print (list);

  srand((unsigned int)time(0));
  const int INDEX = rand() % N;
  client_t *pclient = (client_t *) list->at(list, INDEX);
  printf ("Index: %i, has value: %i\n", INDEX, pclient->sockfd);

  list->clear (list);

  list->print (list);

  list->free (list);

  return 0;
}
