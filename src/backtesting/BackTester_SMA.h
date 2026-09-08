#include "State.h"
#include "SMA.h"

#include <functional>
#include <string>
#include <print>
#include <iostream>

class BackTester_SMA{
public:
	BackTester_SMA();
	~BackTester_SMA();
	void runTest(
		SMA& sma,
		std::function<void(SMA&)> callback
	);
	void retrieveDatabaseData();

	template <typename T>
	void readCSV(T& returnObject, const std::string& filename);

	template <typename T>
	void readCSV(T& returnObject, const std::string& filename, bool reverse);

	void calculateMovingAverages(const std::vector<double>& data, std::size_t window, std::vector<double>& returnVector);
	[[nodiscard]] std::vector<double> calculateMovingAverages(const std::vector<double>& data, std::size_t window);
};

#include "glaze/glaze.hpp"

template <typename T>
void BackTester_SMA::readCSV(T& returnObject, const std::string& filename) {
	readCSV<T>(returnObject, filename, false);

	// Read data from a CSV file for backtesting
	//glz::read_csv<glz::colwise>(/*filename, columnCount*/);
} 

template <typename T>
void BackTester_SMA::readCSV(T& returnObject, const std::string& filename, bool reverse) {
	std::string buffer{};
	auto ec = glz::read_file_csv<glz::colwise>(returnObject, filename, buffer);
	if (ec) {
		std::println(
			std::cerr,
			"Error reading CSV file: {}. Error code: {}",
			filename,
			glz::format_error(ec, buffer)
		);
	} else {
		std::println("CSV file read successfully: {}", filename);
	}

	if (reverse) {
		// Reverse the data in the returnObject
		glz::for_each_field(returnObject, [](auto& field) {
			using FIELD_TYPE = std::remove_cvref_t<decltype(field)>;

			if constexpr (std::ranges::bidirectional_range<FIELD_TYPE>) {
				std::ranges::reverse(field);
			}
		});
	}
}