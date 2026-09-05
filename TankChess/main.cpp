#include <iostream>
#include <ctime>
#include "position.h"
#include "move.h"

// Tank Chess Engine
// Made by Fan Shiyuan

int main() {
    std::clock_t clk_start = std::clock();

    Position position = init_position();

    Move move = { 2,2,2,4,Orientation::NE };
    make_move(position, move);
       
    position_plotter(position);
    
    std::vector<Move> moves = generate_legal_moves(position, 5, 0);
    for (const Move& move : moves) {
        move_announcer(move);
    }

    std::cout << "\n\n" << "Total Moves Found: " << moves.size();





    // Estimate runtime
    std::clock_t clk_end = std::clock();
    double elapsed_seconds = static_cast<double>(clk_end - clk_start) / CLOCKS_PER_SEC;
    std::cout << "\n\n" << "CPU Time taken: " << elapsed_seconds << " seconds\n";
    return 0;
}