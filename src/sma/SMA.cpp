#include "SMA.h"

#include <vector>
#include <ranges>
#include <iostream>

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

	double shortMA = calculateShortMA();
	double longMA = calculateLongMA();

	if (shortMA > (longMA * (1.0 + m_theta)))
	{
		m_state = BUY;
	}
	else if (shortMA < (longMA * (1.0 - m_theta)))
	{
		m_state = SELL;
	}
	else {
		m_state = NONE;
	}

	return m_state;
}

void SMA::reset()
{
	m_state = NONE;
}

double SMA::calculateOldOneDayMA() const
{
	double ma = m_ticks.back().open;
	if (m_ticks.size() >= 2)
	{
		ma = (m_ticks[m_ticks.size() - 2].close + m_ticks[m_ticks.size() - 1].open) / 2.0;
	}
	return ma;
}

double SMA::calculateShortMA() const
{
	double ma = m_ticks.back().open;
	if (m_ticks.size() >= m_shortMAWindow)
	{
		ma = 0.0;
		for(const MarketTick& tick : m_ticks | std::views::drop(m_ticks.size() - m_shortMAWindow))
		{
			ma += tick.open;
		}
		ma /= static_cast<double>(m_shortMAWindow);
	}
	return ma;
}

double SMA::calculateLongMA() const
{
	double ma = m_ticks.back().open;
	if (m_ticks.size() >= m_longMAWindow)
	{
		ma = 0.0;
		for(const MarketTick& tick : m_ticks | std::views::drop(m_ticks.size() - m_longMAWindow))
		{
			ma += tick.open;
		}
		ma /= static_cast<double>(m_longMAWindow);
	}
	return ma;
}