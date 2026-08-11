#include "SMA.h"

SMA::SMA() : m_theta(0.0), m_state(NONE)
{
}

SMA::SMA(double theta) : m_theta(theta), m_state(NONE)
{
}

SMA::~SMA()
{
}

void SMA::setTheta(double theta)
{
	m_theta = theta;
}

template <typename Self>
void SMA::operator()(Self& self, double shortMA, double longMA)
{
	if (m_state == NONE)
	{
		if (shortMA > (longMA*(1.0 + m_theta)))
		{
			self.m_state = BUY;
		}
		else if (shortMA < (longMA * (1.0 - m_theta)))
		{
			self.m_state = SELL;
		}
		else
		{
			self.m_state = NONE;
		}
	}
}