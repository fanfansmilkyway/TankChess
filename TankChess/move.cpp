#include <iostream>
#include <vector>
#include <cstdint>
#include <array>
#include "move.h"
#include "position.h"

int move_announcer(Move move) {
    int from_file = move.from_file;
    int from_rank = move.from_rank;
    int to_file = move.to_file;
    int to_rank = move.to_rank;
    Orientation o = move.orientation;
    std::string orientation;

    switch (o) {
    case Orientation::N: orientation = "N"; break;
    case Orientation::S: orientation = "S"; break;
    case Orientation::E: orientation = "E"; break;
    case Orientation::W: orientation = "W"; break;
    case Orientation::NE: orientation = "NE"; break;
    case Orientation::NW: orientation = "NW"; break;
    case Orientation::SE: orientation = "SE"; break;
    case Orientation::SW: orientation = "SW"; break;
    }

    if (from_file == to_file && from_rank == to_rank) {
        // Stand-still rotation
        std::cout << "\n";
        std::cout << "(" << from_file << "," << from_rank << ")" << "/" << orientation;
        return 0;
    }
    else {
        std::cout << "\n";
        std::cout << "(" << from_file << "," << from_rank << ")" << ">" << "(" << to_file << "," << to_rank << ")" << "/" << orientation;
        return 0;
    }
}

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

std::vector<Move> generate_legal_moves_for_heavy(const Position& position, const int file, const int rank) {
    std::vector<Move> legal_moves;

    // Some help values
    Orientation o = position.board[file][rank].orientation;
    Orientation o_cw1 = rotate(o, 1); std::array<int, 2> v_cw1 = orientation_to_vector(o_cw1);
    Orientation o_cw2 = rotate(o, 2); std::array<int, 2> v_cw2 = orientation_to_vector(o_cw2);
    Orientation o_cw3 = rotate(o, 3); std::array<int, 2> v_cw3 = orientation_to_vector(o_cw3);
    Orientation o_ccw1 = rotate(o, -1); std::array<int, 2> v_ccw1 = orientation_to_vector(o_ccw1);
    Orientation o_ccw2 = rotate(o, -2); std::array<int, 2> v_ccw2 = orientation_to_vector(o_ccw2);
    Orientation o_ccw3 = rotate(o, -3); std::array<int, 2> v_ccw3 = orientation_to_vector(o_ccw3);
    std::array<int, 2> v_o = orientation_to_vector(o);
    
    // Stand-still rotations
    legal_moves.push_back({ file, rank, file, rank, o_cw1 });
    legal_moves.push_back({ file, rank, file, rank, o_cw2 });
    legal_moves.push_back({ file, rank, file, rank, o_cw3 });
    legal_moves.push_back({ file, rank, file, rank, o_ccw1 });
    legal_moves.push_back({ file, rank, file, rank, o_ccw2 });
    legal_moves.push_back({ file, rank, file, rank, o_ccw3 }); 

    if (!if_square_occupied(position, file - v_o[0], rank - v_o[1])) {
        // Backward Move
        legal_moves.push_back({ file, rank, file - v_o[0], rank - v_o[1], o });
    }
    
    switch (o) {
    case Orientation::N: case Orientation::S: case Orientation::E: case Orientation::W: { // I. Orthogonal. Coordinates are in Tank Chess handbook: Move Map
        // Immediate Neighbors
        int D1_file = file + v_cw2[0]; int D1_rank = rank + v_cw2[1];
        if (!if_square_occupied(position, D1_file, D1_rank)) {
            legal_moves.push_back({ file, rank, D1_file, D1_rank, o_cw2 });
        }

        int B1_file = file + v_ccw2[0]; int B1_rank = rank + v_ccw2[1];
        if (!if_square_occupied(position, B1_file, B1_rank)) {
            legal_moves.push_back({ file, rank, B1_file, B1_rank, o_ccw2 });
        }

        int C2_file = file + v_o[0]; int C2_rank = rank + v_o[1];
        if (!if_square_occupied(position, C2_file, C2_rank)) {
            legal_moves.push_back({ file, rank, C2_file, C2_rank, o });
            legal_moves.push_back({ file, rank, C2_file, C2_rank, o_cw1 });
            legal_moves.push_back({ file, rank, C2_file, C2_rank, o_cw2 });
            legal_moves.push_back({ file, rank, C2_file, C2_rank, o_ccw1 });
            legal_moves.push_back({ file, rank, C2_file, C2_rank, o_ccw2 });
            // Chained B3, D3, C3
            int B3_file = C2_file + v_ccw1[0]; int B3_rank = C2_rank + v_ccw1[1];
            if (!if_square_occupied(position, B3_file, B3_rank)) { legal_moves.push_back({ file, rank, B3_file, B3_rank, o_ccw1 }); }
            int D3_file = C2_file + v_cw1[0]; int D3_rank = C2_rank + v_cw1[1];
            if (!if_square_occupied(position, D3_file, D3_rank)) { legal_moves.push_back({ file, rank, D3_file, D3_rank, o_cw1 }); }
            int C3_file = C2_file + v_o[0]; int C3_rank = C2_rank + v_o[1];
            if (!if_square_occupied(position, C3_file, C3_rank)) { 
                legal_moves.push_back({ file, rank, C3_file, C3_rank, o }); legal_moves.push_back({ file, rank, C3_file, C3_rank, o_cw1 });legal_moves.push_back({ file, rank, C3_file, C3_rank, o_ccw1 });
                int C4_file = C3_file + v_o[0]; int C4_rank = C3_rank + v_o[1];
                legal_moves.push_back({ file, rank, C4_file, C4_rank, o });
            }
        }

        int D2_file = file + v_cw1[0]; int D2_rank = rank + v_cw1[1];
        if (!if_square_occupied(position, D2_file, D2_rank)) {
            legal_moves.push_back({ file, rank, D2_file, D2_rank, o });
            legal_moves.push_back({ file, rank, D2_file, D2_rank, o_cw1 });
            legal_moves.push_back({ file, rank, D2_file, D2_rank, o_cw2 });
        }

        int B2_file = file + v_ccw1[0]; int B2_rank = rank + v_ccw1[1];
        if (!if_square_occupied(position, B2_file, B2_rank)) {
            legal_moves.push_back({ file, rank, B2_file, B2_rank, o });
            legal_moves.push_back({ file, rank, B2_file, B2_rank, o_ccw1 });
            legal_moves.push_back({ file, rank, B2_file, B2_rank, o_ccw2 });
        }

        return legal_moves;
    }
    }
}

std::vector<Move> generate_legal_moves(const Position& position, const int file, const int rank) {
    Orientation orientation = position.board[file][rank].orientation;
    switch (position.board[file][rank].piece_type) {
        case PieceType::Heavy:
            return generate_legal_moves_for_heavy(position, file, rank);
            break;
        case PieceType::Medium:
            break;
        case PieceType::Light:
            break;
        case PieceType::Commander_Light:
            break;
    }
// There's four kinds of movements: forward, rotate clockwise, rotate counter-clockwise and backward
// I. Backward
    std::array<int, 2> orientation_vector = orientation_to_vector(orientation);
    int new_file = file - orientation_vector[0];
    int new_rank = rank - orientation_vector[1];
    Move backward_move = { file, rank, new_file, new_rank, orientation };
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