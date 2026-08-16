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
	T readCSV(const std::string& filename, const int columnCount);
};