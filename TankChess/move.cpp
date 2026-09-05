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

std::vector<Move> generate_legal_moves_for_medium(const Position& position, const int file, const int rank) {
    std::vector<Move> legal_moves;

    // Helper Variables
    Orientation o = position.board[file][rank].orientation; std::array<int, 2> v_o = orientation_to_vector(o);
    Orientation o_cw1 = rotate(o, 1); std::array<int, 2> v_cw1 = orientation_to_vector(o_cw1);
    Orientation o_cw2 = rotate(o, 2); std::array<int, 2> v_cw2 = orientation_to_vector(o_cw2);
    Orientation o_cw3 = rotate(o, 3); std::array<int, 2> v_cw3 = orientation_to_vector(o_cw3);
    Orientation o_ccw1 = rotate(o, -1); std::array<int, 2> v_ccw1 = orientation_to_vector(o_ccw1);
    Orientation o_ccw2 = rotate(o, -2); std::array<int, 2> v_ccw2 = orientation_to_vector(o_ccw2);
    Orientation o_ccw3 = rotate(o, -3); std::array<int, 2> v_ccw3 = orientation_to_vector(o_ccw3);
    Orientation o_rev = rotate(o, 4); std::array<int, 2> v_rev = orientation_to_vector(o_rev);

    bool if_D3_occupied = true;
    bool if_E3_occupied = true;
    bool if_C3_occupied = true;

    // Stand-still rotations
    legal_moves.push_back({ file, rank, file, rank, o_cw1 });
    legal_moves.push_back({ file, rank, file, rank, o_cw2 });
    legal_moves.push_back({ file, rank, file, rank, o_cw3 });
    legal_moves.push_back({ file, rank, file, rank, o_ccw1 });
    legal_moves.push_back({ file, rank, file, rank, o_ccw2 });
    legal_moves.push_back({ file, rank, file, rank, o_ccw3 });
    legal_moves.push_back({ file, rank, file, rank, o_rev });

    // Backward
    int D1_file = file - v_o[0]; int D1_rank = rank - v_o[1];
    if (!if_square_occupied(position, D1_file, D1_rank)) {
        legal_moves.push_back({ file, rank, D1_file, D1_rank, o });
    }

    int D3_file = file + v_o[0]; int D3_rank = rank + v_o[1];
    if (!if_square_occupied(position, D3_file, D3_rank)) {
        legal_moves.push_back({ file, rank, D3_file, D3_rank, o });
        legal_moves.push_back({ file, rank, D3_file, D3_rank, o_cw1 });
        legal_moves.push_back({ file, rank, D3_file, D3_rank, o_cw2 });
        legal_moves.push_back({ file, rank, D3_file, D3_rank, o_cw3 });
        legal_moves.push_back({ file, rank, D3_file, D3_rank, o_ccw1 });
        legal_moves.push_back({ file, rank, D3_file, D3_rank, o_ccw2 });
        legal_moves.push_back({ file, rank, D3_file, D3_rank, o_ccw3 });
        if_D3_occupied = false;
    }

    int E2_file = file + v_cw2[0]; int E2_rank = rank + v_cw2[1];
    if (!if_square_occupied(position, E2_file, E2_rank)) {
        legal_moves.push_back({ file, rank, E2_file, E2_rank, o_cw1 });
        legal_moves.push_back({ file, rank, E2_file, E2_rank, o_cw2 });
        legal_moves.push_back({ file, rank, E2_file, E2_rank, o_cw3 });

        // F2
        int F2_file = E2_file + v_cw2[0]; int F2_rank = E2_rank + v_cw2[1];
        if (!if_square_occupied(position, F2_file, F2_rank)) {
            legal_moves.push_back({ file, rank, F2_file, F2_rank, o_cw2 });
        }
    }

    int C2_file = file + v_ccw2[0]; int C2_rank = rank + v_ccw2[1];
    if (!if_square_occupied(position, E2_file, E2_rank)) {
        legal_moves.push_back({ file, rank, C2_file, C2_rank, o_ccw1 });
        legal_moves.push_back({ file, rank, C2_file, C2_rank, o_ccw2 });
        legal_moves.push_back({ file, rank, C2_file, C2_rank, o_ccw3 });

        // B2
        int B2_file = C2_file + v_ccw2[0]; int B2_rank = C2_rank + v_ccw2[1];
        if (!if_square_occupied(position, B2_file, B2_rank)) {
            legal_moves.push_back({ file, rank, B2_file, B2_rank, o_ccw2 });
        }
    }

    int E3_file = file + v_cw1[0]; int E3_rank = rank + v_cw1[1];
    if (!if_square_occupied(position, E3_file, E3_rank)) {
        legal_moves.push_back({ file, rank, E3_file, E3_rank, o_cw1 });
        legal_moves.push_back({ file, rank, E3_file, E3_rank, o_cw2 });
        legal_moves.push_back({ file, rank, E3_file, E3_rank, o_cw3 });
        legal_moves.push_back({ file, rank, E3_file, E3_rank, o_ccw1 });
        legal_moves.push_back({ file, rank, E3_file, E3_rank, o });
        if_D3_occupied = false;

        // F3
        int F3_file = E3_file + v_cw2[0]; int F3_rank = E3_rank + v_cw2[1];
        if (!if_square_occupied(position, F3_file, F3_rank)) {
            legal_moves.push_back({ file, rank, F3_file, F3_rank, o_cw2 });
        }

        // F4
        int F4_file = E3_file + v_cw1[0]; int F4_rank = D3_rank + v_cw1[1];
        if (!if_square_occupied(position, F4_file, F4_rank)) {
            legal_moves.push_back({ file, rank, F4_file, F4_rank, o });
            legal_moves.push_back({ file, rank, F4_file, F4_rank, o_cw1 });
            legal_moves.push_back({ file, rank, F4_file, F4_rank, o_cw2 });

            int G5_file = F4_file + v_cw1[0]; int G5_rank = F4_rank + v_cw1[1];
            if (!if_square_occupied(position, G5_file, G5_rank)) {
                legal_moves.push_back({ file, rank, G5_file, G5_rank, o_cw1 });
            }
        }
    }

    int C3_file = file + v_ccw1[0]; int C3_rank = rank + v_ccw1[1];
    if (!if_square_occupied(position, C3_file, C3_rank)) {
        legal_moves.push_back({ file, rank, C3_file, C3_rank, o_ccw1 });
        legal_moves.push_back({ file, rank, C3_file, C3_rank, o_ccw2 });
        legal_moves.push_back({ file, rank, C3_file, C3_rank, o_ccw3 });
        legal_moves.push_back({ file, rank, C3_file, C3_rank, o_cw1 });
        legal_moves.push_back({ file, rank, C3_file, C3_rank, o });
        if_C3_occupied = false;

        // B3
        int B3_file = C3_file + v_ccw2[0]; int B3_rank = C3_rank + v_ccw2[1];
        if (!if_square_occupied(position, B3_file, B3_rank)) {
            legal_moves.push_back({ file, rank, B3_file, B3_rank, o_ccw2 });
        }

        // B4
        int B4_file = C3_file + v_ccw1[0]; int B4_rank = C3_rank + v_ccw1[1];
        if (!if_square_occupied(position, B4_file, B4_rank)) {
            legal_moves.push_back({ file, rank, B4_file, B4_rank, o });
            legal_moves.push_back({ file, rank, B4_file, B4_rank, o_ccw1 });
            legal_moves.push_back({ file, rank, B4_file, B4_rank, o_ccw2 });

            // A5
            int A5_file = B4_file + v_ccw1[0]; int A5_rank = B4_rank + v_ccw1[1];
            if (!if_square_occupied(position, A5_file, A5_rank)) {
                legal_moves.push_back({ file, rank, A5_file, A5_rank, o_ccw1 });
            }
        }
    }

    int E1_file = file + v_cw3[0]; int E1_rank = rank + v_cw3[1];
    if (!if_square_occupied(position, E1_file, E1_rank)) {
        legal_moves.push_back({ file, rank, E1_file, E1_rank, o_cw3 });
    }

    int C1_file = file + v_ccw3[0]; int C1_rank = rank + v_ccw3[1];
    if (!if_square_occupied(position, C1_file, C1_rank)) {
        legal_moves.push_back({ file, rank, C1_file, C1_rank, o_ccw3 });
    }

    // E4 & F5
    // Chained Relationships
    int E4_file = D3_file + v_cw1[0]; int E4_rank = D3_rank + v_cw1[1];
    if (!if_square_occupied(position, E4_file, E4_rank)) {
        if (!if_D3_occupied) {
            legal_moves.push_back({ file, rank, E4_file, E4_rank, o });
            legal_moves.push_back({ file, rank, E4_file, E4_rank, o_cw1 });
            legal_moves.push_back({ file, rank, E4_file, E4_rank, o_cw2 });

            // F5
            int F5_file = E4_file + v_cw1[0]; int F5_rank = E4_rank + v_cw1[1];
            if (!if_square_occupied(position, F5_file, F5_rank)){ legal_moves.push_back({ file, rank, F5_file , F5_rank , o_cw1 }); }

        } else {
            if (!if_E3_occupied) {
                legal_moves.push_back({ file, rank, E4_file, E4_rank, o });
            }
        }
    }

    // C4 & B5
    int C4_file = D3_file + v_ccw1[0]; int C4_rank = D3_rank + v_ccw1[1];
    if (!if_square_occupied(position, C4_file, C4_rank)) {
        if (!if_D3_occupied) {
            legal_moves.push_back({ file, rank, C4_file, C4_rank, o });
            legal_moves.push_back({ file, rank, C4_file, C4_rank, o_ccw1 });
            legal_moves.push_back({ file, rank, C4_file, C4_rank, o_ccw2 });

            // B5
            int B5_file = C4_file + v_ccw1[0]; int B5_rank = C4_rank + v_ccw1[1];
            if (!if_square_occupied(position, B5_file, B5_rank)) { legal_moves.push_back({ file, rank, B5_file , B5_rank , o_ccw1 }); }

        }
        else {
            if (!if_C3_occupied) {
                legal_moves.push_back({ file, rank, C4_file, C4_rank, o });
            }
        }
    }

    // D4 & D5 & D6, E5 & C5
    int D4_file = D3_file + v_o[0]; int D4_rank = D3_rank + v_o[1];
    if (!if_D3_occupied && !if_square_occupied(position, D4_file, D4_rank)) {
        legal_moves.push_back({ file, rank, D4_file, D4_rank, o });
        legal_moves.push_back({ file, rank, D4_file, D4_rank, o_cw1 });
        legal_moves.push_back({ file, rank, D4_file, D4_rank, o_cw2 });
        legal_moves.push_back({ file, rank, D4_file, D4_rank, o_ccw1 });
        legal_moves.push_back({ file, rank, D4_file, D4_rank, o_ccw2 });

        int E5_file = D4_file + v_cw1[0]; int E5_rank = D4_rank + v_cw1[1];
        if (!if_square_occupied(position, E5_file, E5_rank)) {
            legal_moves.push_back({ file, rank, E5_file, E5_rank, o_cw1 });
        }

        int C5_file = D4_file + v_ccw1[0]; int C5_rank = D4_rank + v_ccw1[1];
        if (!if_square_occupied(position, C5_file, C5_rank)) {
            legal_moves.push_back({ file, rank, C5_file, C5_rank, o_ccw1 });
        }

        int D5_file = D4_file + v_o[0]; int D5_rank = D4_rank + v_o[1];
        if (!if_square_occupied(position, D5_file, D5_rank)) {
            legal_moves.push_back({ file, rank, D5_file, D5_rank, o });
            legal_moves.push_back({ file, rank, D5_file, D5_rank, o_cw1 });
            legal_moves.push_back({ file, rank, D5_file, D5_rank, o_ccw1 });

            int D6_file = D5_file + v_o[0]; int D6_rank = D5_rank + v_o[1];
            if (!if_square_occupied(position, D6_file, D6_rank)) {
                legal_moves.push_back({ file, rank, D6_file, D6_rank, o });
            }
        }
    }

    return legal_moves;
}

std::vector<Move> generate_legal_moves(const Position& position, const int file, const int rank) {
    Orientation orientation = position.board[file][rank].orientation;
    switch (position.board[file][rank].piece_type) {
        case PieceType::Heavy:
            return generate_legal_moves_for_heavy(position, file, rank);
            break;
        case PieceType::Medium:
            return generate_legal_moves_for_medium(position, file, rank);
            break;
        case PieceType::Light:
            break;
        case PieceType::Commander_Light:
            break;
    }
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