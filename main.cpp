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

#include <print>
#include <thread>

#include <cpr/cpr.h>

using namespace std;

const unsigned MAX_ATTEMPTS = 50;
const unsigned SLEEP_TIME = 10; // milliseconds

struct csvData {
	std::vector<std::string> Date;
	std::vector<double> Open;
	std::vector<double> High;
	std::vector<double> Low;
	std::vector<double> Close;
	std::vector<double> AdjClose;
	std::vector<std::string> Volume;
};

int main()
{
	SMA sma(0.01);

	BackTester_SMA backTester;


	csvData data;
	std::println("Reading CSV file: {}", CSV_DIRECTORY "/VOO_1d_data.csv");
	backTester.readCSV(data, CSV_DIRECTORY "/VOO_1d_data.csv", 7);

	for (const std::string& date : data.Date) {
		std::println("Date: {}", date);
	}
	//backTester.runTest(sma, [](SMA sma) {
	//	sma(sma, 1.0, 2.0);
	//	// Callback function logic here
	//});

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
