/**
 *	@file	cmp_cat.hpp
 *
 *	@brief	cmp_cat の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_COMPARE_DETAIL_CMP_CAT_HPP
#define BKSGE_FND_COMPARE_DETAIL_CMP_CAT_HPP

namespace bksge
{

namespace cmp_cat
{

using type = signed char;

enum class Ord : type { equivalent = 0, less = -1, greater = 1 };

enum class Ncmp : type { unordered = 2 };

struct unspec
{
	constexpr unspec(unspec*) noexcept {}
};

}	// namespace cmp_cat

}	// namespace bksge

#endif // BKSGE_FND_COMPARE_DETAIL_CMP_CAT_HPP
