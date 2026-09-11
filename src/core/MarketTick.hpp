#pragma once
#ifndef MARKETTICK_HPP
#define MARKETTICK_HPP

#include <string>

struct MarketTick {
	std::string date;
	double open;
	double high;
	double low;
	double close;
};

#endif // !MARKETTICK_HPP
