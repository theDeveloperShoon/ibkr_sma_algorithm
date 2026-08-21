#pragma once
#ifndef SMA_H

#include "State.h"

class SMA
{
public: 
	SMA();
	SMA(double theta);
	~SMA();

	void setTheta(double theta);

	template <typename Self>
	void operator()(this Self&& self, double shortMA, double longMA)
	{
		if (self.m_state == NONE)
		{
			if (shortMA > (longMA * (1.0 + self.m_theta)))
			{
				self.m_state = BUY;
			}
			else if (shortMA < (longMA * (1.0 - self.m_theta)))
			{
				self.m_state = SELL;
			}
			else
			{
				self.m_state = NONE;
			}
		}
	}

private:
	double m_theta;
	STATE m_state;
};

#endif // !SMA_H

