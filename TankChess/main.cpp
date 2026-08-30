#include <iostream>
#include "position.h"
#include "move.h"

int main() {
    Position position = init_position();

    Move move = {
        .from_file = 2,
        .from_rank = 2,
        .to_file = 2,
        .to_rank = 5,
        .orientation = Orientation::NE
    };

    position_plotter(position);

    make_move(position, move);

    position_plotter(position);
    
    std::cout << static_cast<int>(generate_legal_moves(position, 12, 2)[0].to_rank);
    return 0;
}