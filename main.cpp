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
	SMA sma(0.01);

	BackTester_SMA backTester;


	csvData data;

	std::println("Reading CSV file: {}", DATA_DIRECTORY);
	backTester.readCSV(data, DATA_DIRECTORY);

	reverseAll(data.Date, data.Open, data.High, data.Low, data.Close, data.AdjClose, data.Volume);
	
	double longSum = 0.0;
	std::vector<double> longMAValues(data.Open.size()-50, 0.0);

	for (auto [index,price] : std::views::enumerate(data.Open)) {
		if (index > 49)
		{
			longMAValues[index - 50] = longSum / 50.0;
			longSum -= data.Open[index - 50];
			//double longMA = longSum / 50.0;
			//double shortMA = std::accumulate(data.Open.begin() + index - 9, data.Open.begin() + index + 1, 0.0) / 10.0;
			//sma(shortMA, longMA);
		}
		longSum += price;
	}

	std::vector<double> shortMAValues(data.Open.size() - 50, 0.0);
	double shortMA = 0.0;
	for (auto [index, price] : std::views::enumerate(data.Open)) {
		if (index > 49)
		{
			shortMA = (price + data.Close[index - 1]) / 2.0;
			shortMAValues[index - 50] = shortMA;
		}
	}

	std::println("Long MA Size: {}, Short MA Size: {}", longMAValues.size(), shortMAValues.size());


	//for (const auto& ma : longMAValues) {
	//	std::println("Long MA: {}", ma);
	//}



	backTester.runTest(sma, [&data, &longMAValues, &shortMAValues](SMA& simpleMovingAverage) {
		//for (const std::string& date : data.Date) {
		//	std::println("Date: {}", date);
		//}
		STATE previousState = simpleMovingAverage.getState();
		double capital = 10000.0;
		purchaseData purchase = { "", 0.0, 0 };
		

		for (size_t i = 0; i < longMAValues.size(); ++i) {
			double longMA = longMAValues[i];
			double shortMA = shortMAValues[i];
			simpleMovingAverage(shortMA, longMA);
			//std::println("State: {}", magic_enum::enum_name(simpleMovingAverage.getState()));
			if (simpleMovingAverage.getState() != previousState) {
				if(simpleMovingAverage.getState() == BUY) {
					double priceAShare = data.Open[i + 50];
					double shares = floor(capital / priceAShare);
					purchase = { data.Date[i + 50], priceAShare, static_cast<int>(shares) };
					capital -= priceAShare * shares;

					std::println("[Purchase] Bought {}  shares at ${} on Date: {} | Short MA: {}, Long MA: {}", shares, priceAShare, data.Date[i + 50], shortMA, longMA);
				}
				else if (simpleMovingAverage.getState() == SELL) {
					if (purchase.shares > 0) {
						double priceAShare = data.Open[i + 50];
						double value = (priceAShare) * purchase.shares;
						capital += value;
						std::println("[Sell] Sold {} shares at ${} on Date: {} | Short MA: {}, Long MA: {}", purchase.shares, data.Open[i + 50], data.Date[i + 50], shortMA, longMA);
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
		
		//simpleMovingAverage(1.0, 2.0);
		// Callback function logic here
	});

	//cpr::Response r = cpr::Get(cpr::Url{ "https://epic-clinking-curliness.ngrok-free.dev/users" });

	//if (r.status_code == 200)
	//{
	//	std::println("Successfully sent request to the server. Status code: {}", r.status_code);
	//}
	//else
	//{
	//	std::println("Failed to send request to the server. Status code: {}", r.status_code);
	//}

	return 0;
	//int clientId = 0;
	//unsigned attempt = 0;
	//std::println("Starting IBKR C++ Mean Reversion Application {}...", attempt);
	//for (;;)
	//{
	//	++attempt;

	//	CWMR_Client client;

	//	client.connect("127.0.0.1", 7497, clientId);

	//	while (client.isConnected())
	//	{
	//		client.processMessages();
	//	}

	//	if (attempt >= MAX_ATTEMPTS)
	//	{
	//		break;
	//	}

	//	std::println("Sleeping {} seconds before next attempt", SLEEP_TIME);
	//	std::this_thread::sleep_for(std::chrono::seconds(SLEEP_TIME));
	//}

	//std::println("Exiting IBKR C++ Mean Reversion Application after {} attempts", attempt);
	//
	//return 0;
}
