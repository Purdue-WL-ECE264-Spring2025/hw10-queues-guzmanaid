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

bool is_state_visited(uint64_t visited[], size_t num_visited, uint64_t key) {
    for (size_t i = 0; i < num_visited; i++) {
        if (visited[i] == key) return true;
    }
    return false;
}

int number_of_moves(struct game_state start) {
    struct queue q = {0};
    enqueue(&q, start);

    uint64_t visited[100000] = {0}; // simple array for seen states
    size_t visited_count = 0;

    while (q.data.head != NULL) {
        struct game_state current = dequeue(&q);

        // Check if it's solved inline (no is_solved())
        int correct = 1;
        bool solved = true;
        for (int i = 0; i < 4 && solved; i++) {
            for (int j = 0; j < 4; j++) {
                if (i == 3 && j == 3) {
                    if (current.tiles[i][j] != 0) {
                        solved = false;
                        break;
                    }
                } else {
                    if (current.tiles[i][j] != correct++) {
                        solved = false;
                        break;
                    }
                }
            }
        }

        if (solved) return current.num_steps;

        int row = current.empty_row;
        int col = current.empty_col;

        // Try moves in all 4 directions
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int new_row = row + dr[i];
            int new_col = col + dc[i];

            if (new_row >= 0 && new_row < 4 && new_col >= 0 && new_col < 4) {
                struct game_state next = current;

                // Swap empty tile with neighbor
                next.tiles[row][col] = next.tiles[new_row][new_col];
                next.tiles[new_row][new_col] = 0;
                next.empty_row = new_row;
                next.empty_col = new_col;
                next.num_steps++;

                uint64_t key = serialize(next);
                if (!is_state_visited(visited, visited_count, key)) {
                    visited[visited_count++] = key;
                    enqueue(&q, next);
                }
            }
        }
    }

    return -1; // No solution found
}
// int number_of_moves(struct game_state start) 
// { 
//     struct queue q = {0};
//     enqueue(&q, start);
//     while(q.data.head != NULL)
//     {
//         struct game_state current = dequeue(&q);

//         if (is_solved(current))
//         {
//             return current.num_steps;
//         }
//         struct game_state next_move[4];
//         size_t num_moves = generate_moves(current, next_move);

//         for(size_t i = 0; i < num_moves; i++)
//         {
//             enqueue(&q, next_move[i]);
//         }
//     }
//     return -1; 

// }
