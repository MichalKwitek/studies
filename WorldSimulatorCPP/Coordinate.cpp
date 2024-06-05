#include "Coordinate.h"

std::ostream& operator<<(std::ostream& out, const Coordinate& coord)
{
	out << "(" << coord.x << "," << coord.y << ")";
	return out;
}

bool Coordinate::operator<(const Coordinate& o) const {
	return x < o.x || (x == o.x && y < o.y);
}

bool Coordinate::operator==(const Coordinate& o) const {
	if (x == o.x && y == o.y) {
		return true;
	}
	else {
		return false;
	}
}

bool Coordinate::operator!=(const Coordinate& o) const {
	return !(*this == o); // Implement != using operator==
}
