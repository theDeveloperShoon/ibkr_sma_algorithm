#include "Backtester.hpp"
#include "Algorithm.h"
#include "MarketTick.hpp"

Backtester::Backtester() {
	// Constructor implementation
}

Backtester::~Backtester() {
	// Destructor implementation
}

void Backtester::runTest(
	Algorithm& algorithm,
	const std::vector<MarketTick>& marketData,
	std::function<void(const MarketTick&, STATE)> callback
) {
	for (const auto& tick : marketData) {
		STATE state = algorithm.update(tick);
		if (callback) {
			callback(tick, state);
		}
	}
}

void Backtester::retrieveDatabaseData() {
	// Retrieve data from the database for backtesting
}