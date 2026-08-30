#pragma once
#include "position.h"
#include <cstdint>

struct Move {
	std::uint8_t from_file;
	std::uint8_t from_rank;

	std::uint8_t to_file;
	std::uint8_t to_rank;

	Orientation orientation;
	// About orientation: 0 for north, 
};

Orientation rotate(Orientation orientation, int amount);

void make_move(Position& position, const Move& move); // Change the input position to the new position after a move is made