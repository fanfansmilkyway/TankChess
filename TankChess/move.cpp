#include <iostream>
#include <vector>
#include <cstdint>
#include <array>
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

std::array<int, 2> orientation_to_vector(Orientation orientation) {
    switch (orientation) {
        case Orientation::N: return { 0,1 };
        case Orientation::NE: return { 1,1 };
        case Orientation::E: return { 1,0 };
        case Orientation::SE: return { 1,-1 };
        case Orientation::S: return { 0,-1 };
        case Orientation::SW: return { -1,-1 };
        case Orientation::W: return { -1,0 };
        case Orientation::NW: return { -1,1 };
    };
}

std::vector<Move> generate_legal_moves(const Position& position, const int file, const int rank) {
    // Identify the tank type first
    int speed = 0;
    Orientation orientation = position.board[file][rank].orientation;
    std::vector<Move> legal_moves;
    switch (position.board[file][rank].piece_type) {
        case PieceType::Heavy:
            speed = 3;
            break;
        case PieceType::Medium:
            speed = 4;
            break;
        case PieceType::Light:
            speed = 5;
            break;
        case PieceType::Commander_Light:
            speed = 5;
            break;
    }
// There's four kinds of movements: forward, rotate clockwise, rotate counter-clockwise and backward
// I. Backward
    int new_file = file - orientation_to_vector(orientation)[0];
    int new_rank = rank - orientation_to_vector(orientation)[1];
    Move backward_move = { file, rank, new_file, new_rank, orientation };
    legal_moves.push_back(backward_move);

    return legal_moves;
}

bool check_if_move_legal(const Position& position, const Move& move) {
    return true;
}


bool make_move(Position& position, const Move& move) {
    if (!check_if_move_legal(position, move)) {  // Check if the move is legal
        std::cout << "Illegal Move!";
        return false;
    }
    position.board[move.to_file][move.to_rank] = position.board[move.from_file][move.from_rank]; 
    position.board[move.to_file][move.to_rank].orientation = move.orientation; // Change the target square as the move orders

    position.board[move.from_file][move.from_rank].piece_type = PieceType::Empty; // Set the original square to empty
    position.board[move.from_file][move.from_rank].side = Side::None;

    position.side_to_move = (position.side_to_move == Side::White) ? Side::Black : Side::White; // Change the side to move
    return true;
}