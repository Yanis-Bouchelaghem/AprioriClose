#pragma once
#include <chrono>

template<typename T>
class Timer
{
public:
	Timer()
	{
		last = std::chrono::steady_clock::now();
	}
	long long Mark()
	{
		const auto old = last;
		last = std::chrono::steady_clock::now();
		const auto difference = std::chrono::duration_cast<T>(last - old);
		return difference.count();
	}
private:
	std::chrono::steady_clock::time_point last;
};
