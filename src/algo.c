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

unsigned int path_len(t_antFarm *af, t_room *sink) {
  unsigned int len = 0;
  t_room *node = sink;
  t_room *next;

  while(node) {
    if(af->start_room == node) {
      return len;
    }
    if((next = next_min_node(af, node)) == NULL || next->h >= node->h)
      return 0;
    len++;
    node = next;
  }
  return 0;
}

static t_room **make_path(t_antFarm *af) {
  t_room *node = af->end_room;
  t_room *next;
  t_room **path;
  int len;

  if(!(len = path_len(af, af->end_room)))
    return 0;

  if (!(path = malloc(sizeof(t_room *) * (len + 1))))
    ft_malloc_error();
  for (int l = 0; l <= len + 1; l++) { path[l] = NULL; }
  
  while(node) {
    path[len] = node;
    if(node == af->start_room || len == 0)
      break;
    len--;
    node->visited = 1;
    next = next_min_node(af, node);
    node = next;
  }
  return path;
}



static t_room **bfs(t_antFarm *af, t_room ***ant_path)
{
  t_room **visited;
  t_room **queue;
  t_room *ant_room = af->start_room;
  t_room **path;

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
        if((path = make_path(af)))
          return path;
        return 0;
      }
    }
  }
  return 0;
}


void algo(t_antFarm *af)
{
  t_room ***ant_path;

  if (!(ant_path = malloc(sizeof(t_room *) * (af->ants_amount + 1))))
    ft_malloc_error();
  for(int i = 0; i < af->ants_amount; i++)
    ant_path[i] = NULL;

  for(int i = 0; i < af->ants_amount; i++) {
    ant_path[i] = bfs(af, ant_path);
    for (int j = 0; ant_path[i][j]; j++)
      printf("%s ", ant_path[i][j]->name);
  }

  // ant_path[0] = bfs(af, ant_path);

  // view_graph(af);
}
