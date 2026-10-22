#include <gtest/gtest.h>

#include "core/MovingAverage.hpp"

#include <vector>
#include <ranges>
#include <numeric>

TEST(MovingAverageUnit, CalculatesExpectedValues) {
	std::vector<double> data = { 1.0, 2.0, 3.0, 4.0, 5.0 };
	auto ma = calculateMovingAverages(data, 3);

	std::vector<double> expected{ 
		(1 + 2 + 3) / 3.0, 
		(2 + 3 + 4) / 3.0, 
		(3 + 4 + 5) / 3.0 
	};
	
	
	ASSERT_EQ(ma.size(), expected.size());
	for (auto [actual, exp] : std::views::zip(ma, expected)) {
		ASSERT_DOUBLE_EQ(actual, exp);
	}
}

TEST(MovingAverageUnit, ReturnsEmptyWhenWindowZero) {
	std::vector<double> data = {1.0, 2.0, 3.0};
	auto ma = calculateMovingAverages(data, 0);
	ASSERT_TRUE(ma.empty());
}

TEST(MovingAverageUnit, ReturnsEmptyWhenDataEmpty) {
	std::vector<double> data;
	auto ma = calculateMovingAverages(data, 3);
	ASSERT_TRUE(ma.empty());
}

TEST(MovingAverageUnit, ReturnsEmptyWhenWindowGreaterThanData) {
	std::vector<double> data = { 1.0, 2.0 };
	auto ma = calculateMovingAverages(data, 3);
	ASSERT_TRUE(ma.empty());
}

TEST(MovingAverageUnit, FullWindowReturnsSingleAverage) {
	std::vector<double> data = { 1.0, 2.0, 3.0 };
	auto ma = calculateMovingAverages(data, 3);
	ASSERT_EQ(ma.size(), 1u);
	ASSERT_DOUBLE_EQ(ma[0], (1 + 2 + 3) / 3.0);
}

TEST(MovingAverageUnnit, HandlesLargeData) {
	std::vector<double> data(10000);
	std::iota(data.begin(), data.end(), 1.0); // Fill with values 1.0 to 10000.0
	auto ma = calculateMovingAverages(data, 100);
	ASSERT_EQ(ma.size(), 9901u); // 10000 - 100 + 1
}