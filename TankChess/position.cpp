#include "position.h"

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