#pragma once

// We call Tanks, Destroyed Tanks(Obstacle) 'pieces'
enum class PieceType
{
    Empty,
    Light,
    Medium,
    Heavy,
    Commander_Light,
    Destroyed_Tank
};

enum class Side
{
    None,
    White,
    Black
};

struct Piece
{
    PieceType piece_type = PieceType::Empty;
    Side side = Side::None;
};

struct Position
{
    Piece board[16][16];
    Side side_to_move = Side::White;
};

Position init_position(); // Return the default initial position of 16x16 map