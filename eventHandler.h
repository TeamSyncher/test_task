#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <iostream>
#include <algorithm>
#include "timeFunctions.h"
#include "pcPull.h"



class eventHandler final
{
public:
	eventHandler(int quan_, int opTime_, int clTime_, int price);
public:
	void clientEnter(const std::string& name, int time);
	void clientTakesPc(const std::string& name, int time, int idOfPc);
	void clientWaits(const std::string& name, int time);
	void clientGone(const std::string& name, int time);
	void endOfDay();
private:
	void notOpenYet(int time);
	void youShallNotPass(int time);
	void clientUnknown(int time);
	void placeIsBusy(int time);
	void iCanWaitNoLonger(int time);
private:
	void clientGoneGen(const std::string& name, int time);
	void clientTakesPcGen(const std::string& name, int time, int idOfPc);
private:
	pcPull pcs;
	int opTime, clTime;
	int quan;
	int price;
	int nowBusy;
	std::queue<std::string> queueClient;
	std::unordered_set<std::string> inClub;
	std::unordered_map<std::string, int> clientPc;

};


