#include <gtest/gtest.h>
#include "sma/SMA.h"
#include "core/MarketTick.hpp"
#include "core/State.h"

TEST(SMASignalsUnit, ResetTest)
{
	SMA sma(0.01);
	sma.setShortMAWindow(1);
	sma.setLongMAWindow(2);

	std::vector<MarketTick> marketData{
		{"2023-01-01", 100.0, 101.0, 99.0, 100.0},
		{"2023-01-02", 110.0, 102.0, 100.0, 110.0},
		{"2023-01-03", 90.0, 103.0, 101.0, 120.0},
		{"2023-01-04", 105.0, 104.0, 102.0, 130.0},
		{"2023-01-05", 105.0, 105.0, 103.0, 140.0}
	};

	// Feed test inputs
	EXPECT_EQ(sma.update(marketData[0]), STATE::NONE);
	EXPECT_EQ(sma.update(marketData[1]), STATE::BUY);
	EXPECT_EQ(sma.update(marketData[2]), STATE::SELL);
	EXPECT_EQ(sma.update(marketData[3]), STATE::BUY);
	EXPECT_EQ(sma.update(marketData[4]), STATE::NONE);

	// Reset and verify values were cleared
	sma.reset();

	// If reset is working correctly, the state should be NONE rather than buy
	EXPECT_EQ(sma.update(marketData[4]), STATE::NONE);
}

TEST(SMASignalsUnit, BuyAndSellScenarios)
{
	SMA sma(0.01);
	sma.setShortMAWindow(2);
	sma.setLongMAWindow(3);


}