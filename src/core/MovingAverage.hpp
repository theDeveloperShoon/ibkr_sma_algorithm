#pragma once
#ifndef MOVINGAVERAGE_HPP
#define MOVINGAVERAGE_HPP

#include <iostream>
#include <vector>
#include <print>
#include <ranges>

void calculateMovingAverages(
	const std::vector<double>& data,
	std::size_t window,
	std::vector<double>& returnVector
) {
	if (data.size() < window || window == 0) {
		returnVector.clear();
		std::println(std::cerr,"Error: Data size is smaller than the window size or window size is zero.");
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



[[nodiscard]] std::vector<double> calculateMovingAverages(const std::vector<double>& data, std::size_t window)
{
	std::vector<double> movingAverages;
	calculateMovingAverages(data, window, movingAverages);
	return movingAverages;

}

#endif // !MOVINGAVERAGE_HPP
