#pragma once
#include "types.hpp"

struct Path {
    unsigned short num_points = 0; // Max points is something like 7 or so points
    Point points[10]; // Pre-allocate the number of points

private:
    unsigned short curr_index = 0;

public:
    Point GetNextPoint();

    unsigned short GetRemainingPoints() const;

    bool empty() const;
};

Path SelectPath(unsigned int& Arrangement);