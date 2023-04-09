#pragma once
#include <vector>
#ifndef IOTERM_H
#define IOTERM_H

enum actions {
	Print,
	Insert,
	GetNextRide,
	CancelRide,
	UpdateTrip
};
class IOterm {
public:
	int action;
	std::vector<int> parameters;
};

#endif // !IOTERM_H
