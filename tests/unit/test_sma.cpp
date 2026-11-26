#include <gtest/gtest.h>
#include "sma/SMA.h"
#include "core/MarketTick.hpp"

TEST(SMAUnit, StateTransitions) {
	SMA sma(0.01); // Create an SMA with a theta of 0.01
	sma.setShortMAWindow(2); // Set short MA window to 2
	sma.setLongMAWindow(3); // Set long MA window to 3

	MarketTick tick1{ "2020-01-01", 100.0, 100, 0, 100 }; // Openn: 100.0, Close: 100.0
	MarketTick tick2{ "2020-01-02", 101.0, 101, 0, 101 }; // Open: 101.0, Close: 101.0
	MarketTick tick3{ "2020-01-03", 110.0, 102, 0, 110 }; // Open: 102.0, Close: 102.0


	EXPECT_EQ(sma.update(tick1), STATE::NONE); // First tick, NONE
	EXPECT_EQ(sma.update(tick2), STATE::NONE); // Second tick, still NONE
	EXPECT_EQ(sma.update(tick3), STATE::BUY); // Third tick, should transition to BUY

	sma.reset(); // Reset the SMA
	EXPECT_EQ(sma.getState(), STATE::NONE); // After reset, state should be NONE
}