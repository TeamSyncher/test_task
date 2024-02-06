#pragma once
#include <vector>
#include "Pc.h"

class pcPull
{
public:
	using pull = std::vector<Pc>;
	explicit pcPull(int quan);
	pcPull(const pcPull& rhs) = delete;
	pcPull& operator=(const pcPull& rhs) = delete;
	~pcPull() = default;

public:
	Pc& operator[](int i);

private:
	pull pcs;
};