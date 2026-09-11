#pragma once
#ifndef OLDSMA_H
#define OLDSMA_H

#include "State.h"

class OLDSMA
{
public:
	OLDSMA();
	OLDSMA(double theta);
	~OLDSMA();

	void setTheta(double theta);
	STATE getState() const;

	template <typename Self>
	void operator()(this Self&& self, double shortMA, double longMA)
	{

		//if (self.m_state == NONE)
		//{
		if (shortMA > (longMA * (1.0 + self.m_theta)))
		{
			self.m_state = BUY;
		}
		else if (shortMA < (longMA * (1.0 - self.m_theta)))
		{
			self.m_state = SELL;
		}
		//}
		//else if (self.m_state == BUY)
		//{
		//	if (shortMA < (longMA * (1.0 - self.m_theta)))
		//	{
		//		self.m_state = SELL;
		//	}
		//}
		//else if (self.m_state == SELL)
		//{
		//	if (shortMA > (longMA * (1.0 + self.m_theta)))
		//	{
		//		self.m_state = BUY;
		//	}
		//	else if (shortMA < (longMA * (1.0 - self.m_theta)))
		//	{
		//		self.m_state = SELL;
		//	}
		//	else
		//	{
		//		self.m_state = NONE;
		//	}
		//
		//}
	}

private:
	double m_theta;
	STATE m_state;
};

#endif // !OLDSMA_H
