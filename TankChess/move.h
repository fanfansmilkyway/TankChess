#pragma once
#include "position.h"
#include <vector>
#include <cstdint>

struct Move {
	int from_file;
	int from_rank;

	int to_file;
	int to_rank;

	Orientation orientation;
	// About orientation: 0 for north, 
};

int move_announcer(Move move);

std::array<int, 2> orientation_to_vector(Orientation orientation);

Orientation rotate(Orientation orientation, int amount);

std::vector<Move> generate_legal_moves(const Position& position, const int file, const int rank);

bool check_if_move_legal(const Position& position, const Move& move); // Return false if the move is not legal, true for is legal

bool make_move(Position& position, const Move& move); // Change the input position to the new position after a move is made
// Return false if the move cannot be made due to rules, and position won't be changed