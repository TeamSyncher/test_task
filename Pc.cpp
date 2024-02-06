#include "Pc.h"

Pc::Pc():busy(false), curClient(""), curStart(-1), time(0), sells(0) {}

bool Pc::isBusy() const { return busy; }

void Pc::pushClient(const std::string& nameClient, int startTime)
{
	if (busy) throw "busy!!!";
	busy = true;
	curClient = nameClient;
	curStart = startTime;
}

void Pc::popClient(int endTime)
{
	if (!busy) throw "no client 2 pop!!!";
	int sumTime = endTime - curStart;
	time += sumTime;
	sells += sumTime / 60 + static_cast<int>(sumTime % 60 != 0);
	busy = false;
}

int Pc::getTime() const { return time; }

int Pc::getSells() const { return sells; }

