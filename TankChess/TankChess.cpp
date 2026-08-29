#include <iostream>
#include "map.h"
#include "position.h"

int main() {
    Position initial_position = init_position();

    map_plotter(initial_position);
    return 0;
}