#include "queue.h"
#include "tile_game.h"

// struct linked_list 
// {
//     struct linked_list list;
// }


void enqueue(struct queue *q, struct game_state state) 
{
    size_t serial_state = serialize(state);
    insert_at_tail(&q -> data, serial_state);
}

struct game_state dequeue(struct queue *q) 
{ 
    size_t serial_state_2 = remove_from_head(&q->data);
    return deserialize(serial_state_2);
    //return (struct game_state){0}; 
}

int number_of_moves(struct game_state start) 
{ 
    struct queue q = {0};
    enqueue(&q, start);
    while(q.data.head != NULL)
    {
        struct game_state current = dequeue(&q);

        if (is_solved(current))
        {
            return current.num_steps;
        }
        struct game_state next_move[4];
        size_t num_moves = generate_moves(current, next_move);

        for(size_t i = 0; i < num_moves; i++)
        {
            enqueue(&q, next_move[i]);
        }
    }
    return -1; 

}
