#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "backtesting/Backtester.hpp"
#include "core/Algorithm.h"
#include "core/MarketTick.hpp"
#include "core/State.h"

#include <vector>
#include <string>

class TestAlgorithm : public Algorithm {
public:
	explicit TestAlgorithm(std::vector<STATE> state_sequence) :
		m_state_sequence(std::move(state_sequence)), m_state(STATE::NONE) {
	}

	STATE update(const MarketTick& tick) override {
		if (m_index < m_state_sequence.size()) {
			m_state = m_state_sequence[m_index++];
		}
		else {
			m_state = STATE::NONE;
		}
		return m_state;
	}

	STATE getState() const override {
		return m_state;
	}

	void reset() override {
		m_index = 0;
		m_state = STATE::NONE;
	}

private:
	std::vector<STATE> m_state_sequence;
	std::size_t m_index = 0;
	STATE m_state{ STATE::NONE };
};


//TEST(BacktesterUnit, MovinngAverageSmall) {
//	Backtester backtester;
//	std::vector<double> data = { 1.0, 2.0, 3.0, 4.0, 5.0 };
//	auto ma = backtester.calculateMovingAverages(data, 3);
//	std::vector<double> expect{ (1 + 2 + 3) / 3.0,(2 + 3 + 4) / 3.0,(3 + 4 + 5) / 3.0 };
//	ASSERT_EQ(ma.size(), expect.size());
//	for (size_t i = 0;i < ma.size();++i) EXPECT_DOUBLE_EQ(ma[i], expect[i]);
//}

TEST(BacktesterUnit, RunTestInvokesCallbackForEachTickInOrder) {
	Backtester backtester;
	TestAlgorithm testAlgorithm({ STATE::BUY, STATE::SELL, STATE::NONE });

	std::vector<MarketTick> marketData{
		{"2020-01-01", 100.0, 101.0, 99.0, 100.0},
		{"2020-01-02", 101.0, 102.0, 100.0, 101.0},
		{"2020-01-03", 102.0, 103.0, 101.0, 102.0}
	};

	std::vector<STATE> callbackStates;
	std::vector<std::string> callbackDates;

	backtester.runTest(testAlgorithm, marketData, [&](const MarketTick& tick, STATE state) {
		callbackStates.push_back(state);
		callbackDates.push_back(tick.date);
	});
	ASSERT_EQ(callbackStates.size(), 3);
	EXPECT_EQ(callbackStates[0], STATE::BUY);
	EXPECT_EQ(callbackStates[1], STATE::SELL);
	EXPECT_EQ(callbackStates[2], STATE::NONE);

	EXPECT_EQ(callbackDates[0], "2020-01-01");
	EXPECT_EQ(callbackDates[1], "2020-01-02");
	EXPECT_EQ(callbackDates[2], "2020-01-03");
}

TEST(BacktesterUnit, RunTestsAllowsNullCallback) {
	Backtester backtester;
	std::vector<MarketTick> marketData = {
		{"2020-01-01", 100.0, 101.0, 99.0, 100.0},
		{"2020-01-02", 101.0, 102.0, 100.0, 101.0}
	};
	std::vector<STATE> expectedStates = { STATE::BUY, STATE::SELL};
	TestAlgorithm testAlgorithm(expectedStates);
	EXPECT_NO_THROW(backtester.runTest(testAlgorithm, marketData, nullptr));
	EXPECT_EQ(testAlgorithm.getState(), STATE::SELL);
}