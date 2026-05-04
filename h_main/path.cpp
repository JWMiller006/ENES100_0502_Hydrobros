#include "path.hpp"
#include "Arduino.h"
#include "types.hpp"

Point Path::GetNextPoint() {
    if (curr_index < num_points) {
        return points[curr_index++];
    }

    // Return some default point or handle the end of the path as needed
    return Point(-1.0f, -1.0f);
}

unsigned short Path::GetRemainingPoints() const {
    return num_points - (curr_index + 1);
}

bool Path::empty() const {
    return curr_index >= num_points;
}

Path SelectPath(unsigned int& Arrangement) {
    Path path{};

    if (Arrangement == Unknown) {
        Serial.println("Error: No valid arrangement detected! Returning empty path.");
        return path;
    }

    if (Arrangement & Inverse) {
        if ((Arrangement & (A | B)) == (A | B)) {
            path.points[0] = gPoints[PO3];
            path.points[1] = gPoints[L3];
            path.points[2] = gPoints[L1];
            path.points[3] = gPoints[PL];
            // path.points[4] = gPoints[PF];
            path.num_points = 5;
            Arrangement |= F;
        } else if (Arrangement & A) {
            path.points[0] = gPoints[PEU];
            path.points[1] = gPoints[L2];
            path.points[2] = gPoints[L1];
            path.points[3] = gPoints[PL];
            // path.points[4] = gPoints[PF];
            path.num_points = 5;
            // We don't know where the
            //      bottom one is, but we
            //      don't need to. It doesn't
            //      matter since we already
            //      have a path through it
            Arrangement |= E | F | C;
        } else if (Arrangement & B) {
            path.points[0] = gPoints[PO3];
            path.points[1] = gPoints[L3];
            path.points[2] = gPoints[L2];
            path.points[3] = gPoints[PG];
            path.points[4] = gPoints[PL];
            // path.points[5] = gPoints[PF];
            path.num_points = 6;
            // We don't know where the
            //      bottom one is, but we
            //      don't need to. It doesn't
            //      matter since we already
            //      have a path through it
            Arrangement |= D | C | F;
        } else {
            path.points[0] = gPoints[PEU];
            path.points[1] = gPoints[L2];
            path.points[2] = gPoints[L3];
            path.points[3] = gPoints[PO6];
            path.points[4] = gPoints[PG];
            path.points[5] = gPoints[PL];
            // path.points[6] = gPoints[PF];
            path.num_points = 7;
            // We can assume that the bottom
            //      one is closer since we
            //      know the other ones are
            //      farther away
            Arrangement |= C | D | E;
        }
    } else {
        if ((Arrangement & (B | C)) == (B | C)) {
            path.points[0] = gPoints[PO1];
            path.points[1] = gPoints[L1];
            path.points[2] = gPoints[L2];
            path.points[3] = gPoints[PG];
            path.points[4] = gPoints[PL];
            // path.points[5] = gPoints[PF];
            path.num_points = 6;
            // We know that the final
            //      obstacle is farther since
            //      we know the other two are
            //      closer
            Arrangement |= D;
        } else if (Arrangement & C) {
            path.points[0] = gPoints[PEU];
            path.points[1] = gPoints[PO2];
            path.points[2] = gPoints[L2];
            path.points[3] = gPoints[L3];
            path.points[4] = gPoints[PO6];
            path.points[5] = gPoints[PG];
            path.points[6] = gPoints[PL];
            // path.points[7] = gPoints[PF];
            path.num_points = 8;
            // We don't know where the top
            //      obstacle is, but we don't
            //      need to since we already
            //      have a path
            Arrangement |= A | D | E;
        } else if (Arrangement & B) {
            path.points[0] = gPoints[PO3];
            path.points[1] = gPoints[L3];
            path.points[2] = gPoints[L2];
            path.points[3] = gPoints[PG];
            path.points[4] = gPoints[PL];
            // path.points[5] = gPoints[PF];
            path.num_points = 6;
            // We don't know where the top
            //      obstacle is, but we don't
            //      need to since we already
            //      have a path
            Arrangement |= A | D | F;
        } else {
            path.points[0] = gPoints[PEU];
            path.points[1] = gPoints[L2];
            path.points[2] = gPoints[L1];
            path.points[3] = gPoints[PL];
            // path.points[4] = gPoints[PF];
            path.num_points = 5;
            // We know the top one is closer since
            //      we know the other two are farther
            Arrangement |= A | E | F;
        }
    }

    return path;
}
