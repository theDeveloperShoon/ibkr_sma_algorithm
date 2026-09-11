#include "BackTester_SMA.h"

#include <ranges>
#include <iostream>

#include "glaze/glaze.hpp"

BackTester_SMA::BackTester_SMA() {
	// Constructor implementation
}

BackTester_SMA::~BackTester_SMA() {
	// Destructor implementation
}

void BackTester_SMA::runTest(OLDSMA& sma, std::function<void(OLDSMA&)> callback) {
	// Run the backtest logic here
	// For example, you can simulate some data and call the callback with the SMA object
	callback(sma);
}

void BackTester_SMA::retrieveDatabaseData() {
	// Retrieve data from the database for backtesting
}

void BackTester_SMA::calculateMovingAverages(const std::vector<double>& data, std::size_t window, std::vector<double>& returnVector) {
	// Calculate moving averages and store them in returnVector
	if (data.size() < window || window == 0) {
		returnVector.clear();
		std::println(std::cerr, "Error: Data size is smaller than the window size or window size is zero.");
		return;
	}

	const std::size_t resultSize = data.size() - window + 1;
	returnVector.resize(resultSize);

	const auto signedWindow = static_cast<std::ptrdiff_t>(window);

	double sum = 0.0;
	for (auto [index, price] : std::views::enumerate(data)) {
		sum += price;
		if (index >= signedWindow - 1) {
			returnVector[index - signedWindow + 1] = sum / static_cast<double>(signedWindow);
			sum -= data[index - signedWindow + 1];
		}
	}

}

[[nodiscard]] std::vector<double> BackTester_SMA::calculateMovingAverages(const std::vector<double>& data, std::size_t window) {
	// Calculate moving averages and return them as a vector
	std::vector<double> movingAverages;
	calculateMovingAverages(data, window, movingAverages);
	return movingAverages;
}

// TEST: filename = "VOO_1d_data.csv", columnCount = 7
//template <typename T>
//T BackTester_SMA::readCSV(T returnObject, const std::string& filename, const int columnCount) {
//	glz::read_csv<glz::colwise>(returnObject, filename);
//	return returnObject;
//	// Read data from a CSV file for backtesting
//	//glz::read_csv<glz::colwise>(/*filename, columnCount*/);
//}