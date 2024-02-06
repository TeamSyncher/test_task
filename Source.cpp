#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include "eventHandler.h"

using std::string;
using std::to_string;
using std::cout;
using std::regex;
using std::regex_match;
using std::smatch;
using std::getline;
using std::stoi;


int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout << "Need file to read!";
		return 0;
	}
	std::fstream fin(argv[1]);
	if (fin.is_open() == false)
	{
		std::cout << "Problem with file.\n";
		return 0;
	}
	smatch res;
	regex numReg("[1-9]\\d*");

	regex opClReg("(([01]\\d)|([2][0-3])):([0-5]\\d) (([01]\\d)|([2][0-3])):([0-5]\\d)");

	regex eventReg("((([01]\\d)|([2][0-3])):([0-5]\\d)) (((([134]) ([0-9a-z-_]+)))|((2) ([0-9a-z-_]+) ([1-9]\\d*)))");
	int quan, opTime, clTime, price;
	string buf;
	getline(fin, buf);
	if (!regex_match(buf, numReg))
	{
		cout << 1;
		return 0;
	}
	quan = stoi(buf);
	getline(fin, buf);
	if (!regex_match(buf, opClReg))
	{
		cout << 2;
		return 0;
	}
	opTime = strTime2Int(buf.substr(0, 5));
	clTime = strTime2Int(buf.substr(6));
	getline(fin, buf);
	if (!regex_match(buf, numReg))
	{
		cout << 3;
		return 0;
	}
	price = stoi(buf);
	eventHandler logs(quan, opTime, clTime, price);
	for (int i = 4; getline(fin, buf); ++i)
	{
		if (!regex_match(buf, eventReg))
		{
			cout << i;
			return 0;
		}
	}

	fin.clear();
	fin.seekg(0, std::ios_base::beg);
	getline(fin, buf);
	getline(fin, buf);
	getline(fin, buf);
	cout << intTime2Str(opTime) << '\n';
	for (;getline(fin, buf);)
	{
		regex_match(buf, res, eventReg);
		int timeOfEvent = strTime2Int(res.str(1));
		int typeOfEvent = res.str(9).size() != 0 ? stoi(res.str(9)) : stoi(res.str(12));
		string nameOfClient = typeOfEvent == 2 ? res.str(13) : res.str(10);
		int idOfPc = typeOfEvent == 2 ? stoi(res.str(14)) - 1 : -1;
		switch (typeOfEvent)
		{
			case 1:
				logs.clientEnter(nameOfClient, timeOfEvent);
				break;
			case 2:
				logs.clientTakesPc(nameOfClient, timeOfEvent, idOfPc);
				break;
			case 3:
				logs.clientWaits(nameOfClient, timeOfEvent);
				break;
			case 4:
				logs.clientGone(nameOfClient, timeOfEvent);
				break;
		}
	}
	logs.endOfDay();
}