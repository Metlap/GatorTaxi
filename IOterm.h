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
	//Operation to be performed (Eg print, insert, getNextride etc.,)
	int action;
	//Parameters of that action
	std::vector<int> parameters;
};

#endif // !IOTERM_H
