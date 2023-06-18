#include "../lem_in.h"

static t_room *next_min_node(t_antFarm *af, t_room *room) {
  unsigned int min_h = UINT_MAX;
  t_room **edge = room->connections;
  t_room *edge_with_min_h = NULL;

  for(int i = 0; edge[i]; i++) {
    if(edge[i] != af->end_room && edge[i]->h < min_h
      && edge[i]->visited == 0 && (edge[i]->h || edge[i] == af->start_room)) {
        min_h = edge[i]->h;
        edge_with_min_h = edge[i];
    }
  }
  return edge_with_min_h;
}


static int bfs(t_antFarm *af)
{
  t_room **visited;
  t_room **queue;
  t_room *ant_room = af->start_room;

  int rear = 0, front = 0;

  if (!(visited = malloc(sizeof(t_room *) * (room_amount(af) + 3) * af->ants_amount)))
    ft_malloc_error();
  *visited = NULL;
  if (!(queue = malloc(sizeof(t_room *) * (room_amount(af) + 3) * af->ants_amount)))
    ft_malloc_error();
  *queue = NULL;

  add_room_end_array(visited, ant_room);
  queue[rear++] = ant_room;

  while (front < rear)
  {
    t_room *current = queue[front++];

    for (int i = 0; current->connections[i]; i++)
    {
      t_room *adj = current->connections[i];
      if((adj->h == 0 && adj != af->start_room) || adj == af->end_room)
        adj->h = current->h + 1;

      if (!room_in_array(visited, current->connections[i]))
      {
        add_room_end_array(visited, adj);
        queue[rear++] = adj;
      }

      if(adj == af->end_room) {
        t_room *test = next_min_node(af, adj);
        printf("%s\n", test->name);
        t_room *test2 = next_min_node(af, test);
        printf("%s\n", test2->name);
      }
    }
  }
  return 0;
}

int edmondsKarp(t_antFarm *af) {
  int max_flow = 0;

  while(19) {
    int flow = bfs(af);
  }
}

void algo(t_antFarm *af)
{
  bfs(af);
  // view_graph(af);
}
