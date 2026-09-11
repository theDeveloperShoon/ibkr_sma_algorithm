#include "OldSMA.hpp"

OLDSMA::OLDSMA() : m_theta(0.0), m_state(NONE)
{
}

OLDSMA::OLDSMA(double theta) : m_theta(theta), m_state(NONE)
{
}

OLDSMA::~OLDSMA()
{
}

void OLDSMA::setTheta(double theta)
{
	m_theta = theta;
}

STATE OLDSMA::getState() const
{
	return m_state;
}