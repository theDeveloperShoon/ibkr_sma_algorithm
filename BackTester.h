#include "State.h"
#include "SMA.h"

#include <functional>
#include <string>

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
void BackTester_SMA::readCSV(T& returnObject, const std::string& filename, [[maybe_unused]] const int columnCount) {
	std::string buffer{};
	auto ec = glz::read_file_csv<glz::colwise>(returnObject, filename, buffer);

	//if (!ec) {
	//	std::println("CSV file read successfully: {}", filename);
	//}

	// Read data from a CSV file for backtesting
	//glz::read_csv<glz::colwise>(/*filename, columnCount*/);
} 