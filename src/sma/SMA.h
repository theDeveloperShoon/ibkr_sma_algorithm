#pragma once
#ifndef SMA_H

#include "MarketTick.hpp"
#include "Algorithm.h"
#include "State.h"

class SMA : public Algorithm
{
public: 
	SMA();
	SMA(double theta);
	~SMA();

	void setTheta(double theta);
	[[nodiscard]] STATE getState() const override { return m_state; }
	STATE update(const MarketTick& tick) override {
		return m_state;
	};
	void reset() override;

	template <typename Self>
	void operator()(this Self&& self, double shortMA, double longMA)
	{
		if (shortMA > (longMA * (1.0 + self.m_theta)))
		{
			self.m_state = BUY;
		}
		else if (shortMA < (longMA * (1.0 - self.m_theta)))
		{
			self.m_state = SELL;
		}
	}

private:
	double m_theta;
	STATE m_state;
};

#endif // !SMA_H

