#include <iostream>
#include "map.h"
#include "position.h"
#include "move.h"

int main() {
    Position position = init_position();

    Move move = {
        .from_file = 2,
        .from_rank = 2,
        .to_file = 4,
        .to_rank = 6,
        .orientation = Orientation::NE
    };

    map_plotter(position);

    make_move(position, move);

    map_plotter(position);

    return 0;
}