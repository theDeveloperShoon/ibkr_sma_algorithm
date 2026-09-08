#include "SMA.h"

#include <vector>
#include <ranges>

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

STATE SMA::getState() const
{
	return m_state;
}

STATE SMA::update(const MarketTick& tick)
{
	m_ticks.push_back(tick);

	double shortMA = tick.close; // Placeholder for actual short-term moving average calculation
	double longMA = tick.close;  // Placeholder for actual long-term moving average calculation

	if (shortMA > (longMA * (1.0 + m_theta)))
	{
		m_state = BUY;
	}
	else if (shortMA < (longMA * (1.0 - m_theta)))
	{
		m_state = SELL;
	}

	return m_state;
}

void SMA::reset()
{
	m_state = NONE;
}

double SMA::calculateShortMA() const
{

	double ma = 0.0;
	if (m_ticks.size() >= 2)
	{
		//for(auto tick : m_ticks | std::views::take(2))
		//{
		//	ma += tick.close;
		//}
		//ma /= 2;
	}
	return ma;
}

double SMA::calculateLongMA() const
{
	// Placeholder for actual long-term moving average calculation
	return 0.0;
}