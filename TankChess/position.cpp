#include "position.h"
#include <iostream>

extern bool map_obstacles[16][16] = {
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

Position init_position() {
	Position position;

	position.board[2][2] = { PieceType::Light, Side::White };
	position.board[5][2] = { PieceType::Light, Side::White };
	position.board[9][2] = { PieceType::Light, Side::White };
	position.board[12][2] = { PieceType::Light, Side::White };

	position.board[5][0] = { PieceType::Medium, Side::White };
	position.board[7][2] = { PieceType::Medium, Side::White };
	position.board[9][0] = { PieceType::Medium, Side::White };

	position.board[2][0] = { PieceType::Heavy, Side::White };
	position.board[12][0] = { PieceType::Heavy, Side::White };

	position.board[7][0] = { PieceType::Commander_Light, Side::White };

	position.board[3][13] = { PieceType::Light, Side::Black };
	position.board[6][13] = { PieceType::Light, Side::Black };
	position.board[10][13] = { PieceType::Light, Side::Black };
	position.board[13][13] = { PieceType::Light, Side::Black };

	position.board[6][15] = { PieceType::Medium, Side::Black };
	position.board[8][13] = { PieceType::Medium, Side::Black };
	position.board[10][15] = { PieceType::Medium, Side::Black };

	position.board[3][15] = { PieceType::Heavy, Side::Black };
	position.board[13][15] = { PieceType::Heavy, Side::Black };

	position.board[8][15] = { PieceType::Commander_Light, Side::Black };

	position.side_to_move = Side::White;
	return position;
};

void position_plotter(const Position& current_position) {
	std::cout << '\n';
	for (int rank = 15; rank >= 0; rank--) {

		for (int file = 0; file <= 15; file++) {

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

bool if_square_occupied(const Position& position, const int file, const int rank) {
	// Check if occupied by obstacle, true for occupied
	if (map_obstacles[file][rank]) {
		return true; // occupied by obstacle
	}
	if (position.board[file][rank].piece_type != PieceType::Empty) {
		return true; // occupied by tank
	}
	else {
		return false;
	}
}