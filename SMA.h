#include "State.h"

class SMA
{
public: 
	SMA();
	SMA(double theta);
	~SMA();

	void setTheta(double theta);

	template <typename Self>
	void operator()(Self& self, double shortMA, double longMA);

private:
	double m_theta;
	STATE m_state;
};