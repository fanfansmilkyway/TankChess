#pragma once
#include <cstdint>


extern bool map_obstacles[16][16];


enum class Orientation {
    N = 0,
    NE = 1,
    E = 2,
    SE = 3,
    S = 4,
    SW = 5,
    W = 6,
    NW = 7
    // Values are assigned in clockwise order
};

// We call Tanks, Destroyed Tanks(Obstacle) 'pieces'. Values are their speeds.
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
    Orientation orientation = (side == Side::White) ? Orientation::N : Orientation::S; // White's orientation is North by default
};

struct Position
{
    Piece board[16][16];
    Side side_to_move = Side::White;
};

Position init_position(); // Return the default initial position of 16x16 map

Position init_debug_position();

void position_plotter(const Position& current_position); // Plot the map to terminal

bool if_square_occupied(const Position& position, const int file, const int rank); // Check whether the square if available to go to becaused of being occupied by obstacle or tank