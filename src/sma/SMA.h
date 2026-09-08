#pragma once
#ifndef SMA_H

#include "MarketTick.hpp"
#include "Algorithm.h"
#include "State.h"

#include <vector>

class SMA : public Algorithm
{
public: 
	SMA();
	SMA(double theta);
	~SMA();

	void setTheta(double theta);
	[[nodiscard]] STATE getState() const override { return m_state; }
	STATE update(const MarketTick& tick) override;
	void reset() override;

	template <typename Self>
	void operator()(this Self&& self, double shortMA, double longMA)
	{

	}

private:
	double calculateShortMA() const;
	double calculateLongMA() const;

	double m_theta;
	STATE m_state;
	std::vector<MarketTick> m_ticks;
};

#endif // !SMA_H

