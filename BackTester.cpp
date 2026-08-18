#include "BackTester.h"

#include "glaze/glaze.hpp"

BackTester_SMA::BackTester_SMA() {
	// Constructor implementation
}

BackTester_SMA::~BackTester_SMA() {
	// Destructor implementation
}

void BackTester_SMA::runTest(SMA sma, std::function<void(SMA)> callback) {
	// Run the backtest logic here
	// For example, you can simulate some data and call the callback with the SMA object
	callback(sma);
}

void BackTester_SMA::retrieveDatabaseData() {
	// Retrieve data from the database for backtesting
}

// TEST: filename = "VOO_1d_data.csv", columnCount = 7
//template <typename T>
//T BackTester_SMA::readCSV(T returnObject, const std::string& filename, const int columnCount) {
//	glz::read_csv<glz::colwise>(returnObject, filename);
//	return returnObject;
//	// Read data from a CSV file for backtesting
//	//glz::read_csv<glz::colwise>(/*filename, columnCount*/);
//}