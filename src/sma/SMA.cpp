#include "SMA.h"

#include <vector>
#include <ranges>

SMA::SMA() : m_theta(0.0), m_state(NONE)
{
}

SMA::SMA(double theta) : m_theta(theta), m_state(NONE)
{
}

SMA::SMA(double theta, std::size_t shortMAWindow, std::size_t longMAWindow)
	: m_theta(theta), m_shortMAWindow(shortMAWindow), m_longMAWindow(longMAWindow), m_state(NONE)
{
}

SMA::~SMA()
{
}

void SMA::setTheta(double theta)
{
	m_theta = theta;
}

//STATE SMA::getState() const
//{
//	return m_state;
//}

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
	if (m_ticks.size() >= m_shortMAWindow)
	{
		for(const MarketTick& tick : m_ticks | std::views::drop(m_ticks.size() - m_shortMAWindow))
		{
			ma += tick.close;
		}
		ma /= static_cast<double>(m_shortMAWindow);
	}
	return ma;
}

double SMA::calculateLongMA() const
{
	double ma = 0.0;
	if (m_ticks.size() >= m_longMAWindow)
	{
		for(const MarketTick& tick : m_ticks | std::views::drop(m_ticks.size() - m_longMAWindow))
		{
			ma += tick.close;
		}
		ma /= static_cast<double>(m_longMAWindow);
	}
	return ma;
}