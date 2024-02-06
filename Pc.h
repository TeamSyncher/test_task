#pragma once
#include<string>


class Pc final
{
public:
	Pc();
	Pc(const Pc& rhs) = delete;
	Pc& operator=(const Pc& rhs) = delete;
	~Pc() = default;

public:
	bool isBusy() const;
	void pushClient(const std::string& nameClient, int startTime);
	void popClient(int endTime);
	int getTime() const;
	int getSells() const;

private:
	bool busy;
	std::string curClient;
	int curStart;
	int time;
	int sells; // amount of sessions with full price
};
