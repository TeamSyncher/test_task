#include "eventHandler.h"

eventHandler::eventHandler(int quan_, int opTime_, int clTime_, int price_) : pcs(quan_), opTime(opTime_), clTime(clTime_), quan(quan_), price(price_), nowBusy(0) {}

void eventHandler::clientEnter(const std::string& name, int time)
{
	std::cout << intTime2Str(time) << " 1 " << name << '\n';
	if (inClub.find(name) != inClub.end())
	{
		youShallNotPass(time);
		return;
	}
	if (time < opTime || time > clTime)
	{
		notOpenYet(time);
		return;
	}
	inClub.insert(name);
}

void eventHandler::clientTakesPc(const std::string& name, int time, int idOfPc)
{
	std::cout << intTime2Str(time) << " 2 " << name << ' ' << idOfPc + 1 << '\n';
	if (inClub.find(name) == inClub.end())
	{
		clientUnknown(time);
		return;
	}
	if (pcs[idOfPc].isBusy())
	{
		placeIsBusy(time);
		return;
	}
	auto it = clientPc.find(name);
	if (it != clientPc.end())
	{
		pcs[it->second].popClient(time);
		clientPc.erase(it);
		--nowBusy;
	}
	pcs[idOfPc].pushClient(name, time);
	clientPc[name] = idOfPc;
	++nowBusy;
}

void eventHandler::clientWaits(const std::string& name, int time)
{
	std::cout << intTime2Str(time) << " 3 " << name << '\n';
	if (inClub.find(name) == inClub.end())
	{
		clientUnknown(time);
		return;
	}
	if (nowBusy < quan)
	{
		iCanWaitNoLonger(time);
		return;
	}
	if (queueClient.size() > quan)
	{
		clientGoneGen(name, time);
		return;
	}
	queueClient.push(name);
}

void eventHandler::clientGone(const std::string& name, int time)
{
	std::cout << intTime2Str(time) << " 4 " << name << '\n';
	if (inClub.find(name) == inClub.end())
	{
		clientUnknown(time);
		return;
	}
	if (clientPc.find(name) == clientPc.end())
	{
		std::cout << "UB!!!\n";
		std::abort();
		return;
	}
	int idOfPc = clientPc[name];
	pcs[idOfPc].popClient(time);
	clientPc.erase(name);
	inClub.erase(name);
	--nowBusy;
	if (!queueClient.empty())
	{
		const std::string newClient = queueClient.front();
		queueClient.pop();
		clientTakesPcGen(newClient, time, idOfPc);
	}
}

void eventHandler::endOfDay()
{
	std::vector<std::string> clientsToSort;
	for (const std::string& name : inClub) clientsToSort.push_back(name);
	std::sort(clientsToSort.begin(), clientsToSort.end());
	for (std::string& name : clientsToSort) clientGoneGen(name, clTime);
	std::cout << intTime2Str(clTime) << '\n';
	for (int i = 0; i < quan; ++i)
	{
		std::cout << i + 1 << ' ' << pcs[i].getSells() * price << ' ' << intTime2Str(pcs[i].getTime()) << '\n';
	}
}

void eventHandler::notOpenYet(int time)
{
	std::cout << intTime2Str(time) << " 13 " << "notOpenYet\n";
}

void eventHandler::youShallNotPass(int time)
{
	std::cout << intTime2Str(time) << " 13 " << "youShallNotPass\n";
}

void eventHandler::clientUnknown(int time)
{
	std::cout << intTime2Str(time) << " 13 " << "clientUnknown\n";
}

void eventHandler::placeIsBusy(int time)
{
	std::cout << intTime2Str(time) << " 13 " << "placeIsBusy\n";
}

void eventHandler::iCanWaitNoLonger(int time)
{
	std::cout << intTime2Str(time) << " 13 " << "iCanWaitNoLonger\n";
}

void eventHandler::clientGoneGen(const std::string& name, int time)
{
	auto its = inClub.find(name);
	auto itm = clientPc.find(name);
	if (its == inClub.end())
	{
		std::cout << "UB!!!!\n";
		std::abort();
	}
	if (itm != clientPc.end())
	{
		pcs[itm->second].popClient(time);
		--nowBusy;
		clientPc.erase(itm);
	}
	inClub.erase(its);
	std::cout << intTime2Str(time) << " 11 " << name << '\n';

}

void eventHandler::clientTakesPcGen(const std::string& name, int time, int idOfPc)
{
	if (pcs[idOfPc].isBusy())
	{
		std::cout << "UB!!!\n";
		std::abort();
	}
	clientPc[name] = idOfPc;
	pcs[idOfPc].pushClient(name, time);
	++nowBusy;
	std::cout << intTime2Str(time) << " 12 " << name << ' ' << idOfPc + 1 << '\n';
}
