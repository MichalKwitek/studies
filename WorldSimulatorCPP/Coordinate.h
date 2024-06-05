#pragma once
#include <iostream>
struct Coordinate {
	int x;
	int y;
	friend std::ostream& operator<<(std::ostream& out, const Coordinate& coord);
	bool operator<(const Coordinate& o) const;
	bool operator==(const Coordinate& o) const;
	bool operator!=(const Coordinate& o) const;
};
