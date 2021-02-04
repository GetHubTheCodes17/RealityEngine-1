// Copyright Reality Engine. All Rights Reserved.

#pragma once

#include <random>
#include <array>

#include "Core/Platform.h"

namespace reality {
	class Randomizer {
	public:
		template <class T>
		auto GetInt(T min, T max);
		template <class T>
		auto GetReal(T min, T max);
		template <class T, std::size_t Size>
		void GetInts(T min, T max, std::array<T, Size>& out);
		template <class T, std::size_t Size>
		void GetReals(T min, T max, std::array<T, Size>& out);

	private:
		std::random_device m_Device;
		std::mt19937 m_Engine{ m_Device() };
	};

	RE_CORE extern Randomizer* g_Randomizer;
}

template <class T>
auto reality::Randomizer::GetInt(T min, T max) {
	return std::uniform_int_distribution<T>{ min, max }(m_Engine);
}

template <class T>
auto reality::Randomizer::GetReal(T min, T max) {
	return std::uniform_real_distribution<T>{ min, max }(m_Engine);
}

template <class T, std::size_t Size>
void reality::Randomizer::GetInts(T min, T max, std::array<T, Size>& out) {
	const std::uniform_int_distribution<T> randomSeed{ min, max };
	for (auto& elem : out) {
		elem = randomSeed(m_Engine);
	}
}

template <class T, std::size_t Size>
void reality::Randomizer::GetReals(T min, T max, std::array<T, Size>& out) {
	const std::uniform_real_distribution<T> randomSeed{ min, max };
	for (auto& elem : out) {
		elem = randomSeed(m_Engine);
	}
}