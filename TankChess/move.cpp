#include "move.h"

Orientation rotate(Orientation orientation, int amount)
// amount + for clockwise, - for counter-clockwise
{
    int value = static_cast<int>(orientation);

    value = (value + amount) % 8;

    if (value < 0)
        value += 8;

    return static_cast<Orientation>(value);
}

void make_move(Position& position, const Move& move) {
    position.board[move.to_file][move.to_rank] = position.board[move.from_file][move.from_rank]; 
    position.board[move.to_file][move.to_rank].orientation = move.orientation; // Change the target square as the move orders

    position.board[move.from_file][move.from_rank].piece_type = PieceType::Empty; // Set the original square to empty

    position.side_to_move = (position.side_to_move == Side::White) ? Side::Black : Side::White; // Change the side to move
}