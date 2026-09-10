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
	SMA(double theta, std::size_t shortMAWindow, std::size_t longMAWindow);
	~SMA();

	void setTheta(double theta);

	[[nodiscard]] STATE getState() const override { return m_state; }
	STATE update(const MarketTick& tick) override;
	void reset() override;

	void setShortMAWindow(std::size_t window) { m_shortMAWindow = window; }
	void setLongMAWindow(std::size_t window) { m_longMAWindow = window; }

private:
	double calculateShortMA() const;
	double calculateLongMA() const;

	double m_theta;

	std::size_t m_shortMAWindow = 2; // Default short-term moving average window size
	std::size_t m_longMAWindow = 50;  // Default long-term moving average window size

	STATE m_state;
	std::vector<MarketTick> m_ticks;
};

#endif // !SMA_H

