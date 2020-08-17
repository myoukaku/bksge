/**
 *	@file	dangling.hpp
 *
 *	@brief	ranges::dangling の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DANGLING_HPP
#define BKSGE_FND_RANGES_DANGLING_HPP

namespace bksge
{

namespace ranges
{

struct dangling
{
	constexpr dangling() noexcept = default;

	template <typename... Args>
	constexpr dangling(Args&&...) noexcept {}
};

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DANGLING_HPP
