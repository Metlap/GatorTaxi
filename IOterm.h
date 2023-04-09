#pragma once
#include <vector>
#ifndef IOTERM_H
#define IOTERM_H

enum actions {
	Print,
	Insert,
	GetNextRide,
	CancelRide,
	UpdateTrim
};
class IOterm {
public:
	int action;
	std::vector<int> parameters;
};

#endif // !IOTERM_H
