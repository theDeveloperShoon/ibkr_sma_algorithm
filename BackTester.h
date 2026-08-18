#include "State.h"
#include "SMA.h"

#include <functional>

class BackTester_SMA {
public:
	BackTester_SMA();
	~BackTester_SMA();
	void runTest(
		SMA sma,
		std::function<void(SMA)> callback
	);
	void retrieveDatabaseData();

	template <typename T>
	void readCSV(T& returnObject, const std::string& filename, const int columnCount);
};

#include "glaze/glaze.hpp"

template <typename T>
void BackTester_SMA::readCSV(T& returnObject, const std::string& filename, const int columnCount) {

	glz::read_csv<glz::colwise>(returnObject, filename);
	// Read data from a CSV file for backtesting
	//glz::read_csv<glz::colwise>(/*filename, columnCount*/);
}