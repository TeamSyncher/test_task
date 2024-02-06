#include "timeFunctions.h"

int strTime2Int(const std::string& s)
{
	return std::stoi(s.substr(0, 2)) * 60 + std::stoi(s.substr(3));
}

std::string intTime2Str(int time)
{
	std::string hours = time / 60 < 10 ? std::string(1, '0') + std::to_string(time / 60) : std::to_string(time / 60);
	std::string minutes = time % 60 < 10 ? std::string(1, '0') + std::to_string(time % 60) : std::to_string(time % 60);
	return hours + std::string(1, ':') + minutes;
}
