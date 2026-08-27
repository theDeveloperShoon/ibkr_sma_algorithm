// IBKR_CMAKE_MEAN_REVERSION.cpp : Defines the entry point for the application.
//

#include "main.h"


#include "EWrapper.h"
#include "EClientSocket.h"
#include "EReaderOSSignal.h"
#include "EReaderSignal.h"
#include "EReader.h"

#include "SMA.h"
#include "BackTester.h"
#include "State.h"

#include <print>
#include <thread>
#include <algorithm>
#include <ranges>
#include <cmath>

#include <cpr/cpr.h>
#include <magic_enum/magic_enum.hpp>

using namespace std;

const unsigned MAX_ATTEMPTS = 50;
const unsigned SLEEP_TIME = 10; // milliseconds
const std::string DATA_DIRECTORY = std::string(CSV_DIRECTORY) + "/LMT_history1.csv";

struct csvData {
	std::vector<std::string> Date;
	std::vector<double> Open;
	std::vector<double> High;
	std::vector<double> Low;
	std::vector<double> Close;
	std::vector<double> AdjClose;
	std::vector<std::string> Volume;
};

struct purchaseData {
	std::string date;
	double price;
	int shares;
};

template<typename... Vectors>
	requires (std::ranges::bidirectional_range<Vectors> && ...)
void reverseAll(Vectors&... vecs) {
	(std::ranges::reverse(vecs), ...);
}

int main()
{
	const size_t longWindow = 50;

	SMA sma(0.01);
	BackTester_SMA backTester;
	csvData data;

	std::println("Reading CSV file: {}", DATA_DIRECTORY);
	backTester.readCSV(data, DATA_DIRECTORY);
	
	std::vector<double> longMAValues(data.Open.size()-longWindow+1, 0.0);
	backTester.calculateMovingAverages(data.Open, longWindow, longMAValues);

	std::vector<double> shortMAValues(data.Open.size() - longWindow+1, 0.0);
	double shortMA = 0.0;
	for (auto [index, price] : std::views::enumerate(data.Open)) {
		if (index > longWindow - 1)
		{
			shortMA = (price + data.Close[index - 1]) / 2.0;
			shortMAValues[index - longWindow] = shortMA;
		}
	}

	std::println("Long MA Size: {}, Short MA Size: {}", longMAValues.size(), shortMAValues.size());

	const std::size_t sizeDifference = data.Open.size() - longMAValues.size();
	std::println("Size Difference: {}", sizeDifference);

	backTester.runTest(sma, [&data, &longMAValues, &shortMAValues](SMA& simpleMovingAverage) {
		STATE previousState = simpleMovingAverage.getState();
		double capital = 10000.0;
		purchaseData purchase = { "", 0.0, 0 };
		

		for (size_t i = 0; i < longMAValues.size(); ++i) {
			double longMA = longMAValues[i];
			double shortMA = shortMAValues[i];
			simpleMovingAverage(shortMA, longMA);

			if (simpleMovingAverage.getState() != previousState) {
				//std::println("State: {}", magic_enum::enum_name(simpleMovingAverage.getState()));
				if(simpleMovingAverage.getState() == BUY) {
					double priceAShare = data.Open[i + 49];
					double shares = floor(capital / priceAShare);
					purchase = { data.Date[i + 49], priceAShare, static_cast<int>(shares) };
					capital -= priceAShare * shares;

					std::println(
						"[Buy] Bought {}  shares at ${} on Date: {} | Short MA: {}, Long MA: {}", 
						shares, priceAShare, data.Date[i + 49], shortMA, longMA
					);
				} else if (simpleMovingAverage.getState() == SELL) {
					if (purchase.shares > 0) {
						double priceAShare = data.Open[i + 49];
						double value = (priceAShare) * purchase.shares;
						capital += value;
						std::println(
							"[Sell] Sold {} shares at ${} on Date: {} | Short MA: {}, Long MA: {}", 
							purchase.shares, data.Open[i + 49], data.Date[i + 49], shortMA, longMA
						);
						purchase = { "", 0.0, 0 };
					}
				}
			}
			previousState = simpleMovingAverage.getState();
		}

		if(purchase.shares > 0) {
			double priceAShare = data.Open[data.Open.size() - 1];
			double value = (priceAShare) * purchase.shares;
			capital += value;
			purchase = { "", 0.0, 0 };
		}

		std::println("Final Capital: {}", capital);

	});

	return 0;
}
