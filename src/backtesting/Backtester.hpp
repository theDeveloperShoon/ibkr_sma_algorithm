#pragma once
#ifndef BACKTESTER_HPP
#define BACKTESTER_HPP

#include "Algorithm.h"
#include "MarketTick.hpp"
#include <functional>
#include <string>
#include <print>
#include <iostream>

#include <glaze/glaze.hpp>

class Backtester {
public:
	Backtester();
	~Backtester();
	
	void runTest(
		Algorithm& algorithm,
		const std::vector<MarketTick>& marketData,
		std::function<void(const MarketTick&, STATE)> callback = nullptr
	);
	
	void retrieveDatabaseData();

	template <typename T>
	void readCSV(T& returnObject, const std::string& filename) {
		readCSV<T>(returnObject, filename, false);
	}
	
	template <typename T>
	void readCSV(T& returnObject, const std::string& filename, bool reverse) {
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
			glz::for_each_field(returnObject, [](auto& field) {
				using FIELD_TYPE = std::remove_cvref_t<decltype(field)>;

				if constexpr (std::ranges::bidirectional_range<FIELD_TYPE>) {
					std::ranges::reverse(field);
				}
			});
		}


	}
};

#endif // !BACKTESTER_HPP
