#include <iostream>
#include "map.h"
#include "position.h"

bool map_obstacles[16][16] = {
    {0},
    {0,0,0,0,0,1,1,0,0,0,0,0,1,1,1},
    {0,0,0,0,0,1,0,0,1,1},
    {0,0,1,0,0,0,0,0,1,1,},
    {0,0,1,0,0,0,0,0,1,0,0,0,1,1,1},
    {0,0,0,0,0,1,0,0,0,0,0,0,0,1,1},
    {0,0,0,0,0,1,0,0,0,0,1},
    {0,0,0,0,1,1,0,0,0,0,1,1},
    {0,0,0,0,1,1,0,0,0,0,1,1},
    {0,0,0,0,0,1,0,0,0,0,1},
    {0,1,1,0,0,0,0,0,0,0,1},
    {0,1,1,1,0,0,0,1,0,0,0,0,0,1},
    {0,0,0,0,0,0,1,1,0,0,0,0,0,1},
    {0,0,0,0,0,0,1,1,0,0,1},
    {0,1,1,1,0,0,0,0,0,1,1},
    {0}
};

void map_plotter(const Position& current_position) {
    std::cout << '\n';
    for (int rank = 15; rank >= 0; rank--) {

        for (int file = 0; file <=15; file++) {

            if (map_obstacles[file][rank]) {
                std::cout << "#";
            }

            else if (current_position.board[file][rank].piece_type != PieceType::Empty) {
                // Check if the square is occupied by a tank
                std::cout << "T";
            }

            else {
                std::cout << "_";
            }
        }

        std::cout << '\n';
    }
}