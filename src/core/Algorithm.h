#pragma once
#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "State.h"
#include "MarketTick.hpp"

class Algorithm {
public:
	virtual ~Algorithm() = default;

	virtual STATE update(const MarketTick& tick) = 0;
	virtual STATE getState() const = 0;
	virtual void reset() = 0;
};

#endif // !ALGORITHM_H
