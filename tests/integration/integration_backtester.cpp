#include <vector>
#include <gtest/gtest.h>
#include "backtesting/Backtester.hpp"
#include "sma/SMA.h"
#include "core/MarketTick.hpp"
#include "core/STATE.h"


TEST(BacktesterIntegration, SMAIntegration) {
	Backtester backtester;
	SMA sma(0.01);
	sma.setShortMAWindow(2);
	sma.setLongMAWindow(3);

	std::vector<MarketTick> marketData = {
		{"2020-01-01", 100.0, 100.0, 0.0, 100.0},
		{"2020-01-02", 101.0, 101.0, 0.0, 101.0},
		{"2020-01-03", 110.0, 102.0, 0.0, 110.0},
		{"2020-01-04", 90.0, 103.0, 0.0, 115.0}
	};

	std::vector<STATE> expectedStates = { STATE::NONE, STATE::NONE, STATE::BUY, STATE::NONE };

	std::vector<STATE> actualStates;
	backtester.runTest(sma, marketData, [&](const MarketTick&, STATE state) {
		actualStates.push_back(state);
		});
	ASSERT_EQ(actualStates.size(), expectedStates.size());
	for (size_t i = 0; i < actualStates.size(); ++i) {
		EXPECT_EQ(actualStates[i], expectedStates[i]);
	}
}