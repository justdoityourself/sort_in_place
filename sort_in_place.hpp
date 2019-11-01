	
#pragma once

#include <array>

#include "statistics.hpp"

using namespace std;

namespace atk
{
	template< typename S, size_t D = 1, typename T, size_t L> void PrintAnalysis(const array<T, L> & block)
	{
		StatisticalLookup<S, L> lookup;
		StatisticalGraph<S, L> statistics;

		GenerateStatisticalLookup(block, lookup);
		lookup.GenerateStatisticalGraph(statistics, block);

		lookup.PrintGraphContentsAscii(block,2);
		lookup.PrintGraph(block,2);
	}
}