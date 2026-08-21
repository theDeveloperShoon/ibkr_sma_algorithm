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

