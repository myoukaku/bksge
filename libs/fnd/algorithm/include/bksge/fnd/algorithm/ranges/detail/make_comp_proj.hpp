/**
 *	@file	make_comp_proj.hpp
 *
 *	@brief	ranges::detail::make_comp_proj の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_DETAIL_MAKE_COMP_PROJ_HPP
#define BKSGE_FND_ALGORITHM_RANGES_DETAIL_MAKE_COMP_PROJ_HPP

#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

namespace detail
{

template <typename Comp, typename Proj>
struct CompProjT
{
	Comp& m_comp;
	Proj& m_proj;

	template <typename T, typename U>
	BKSGE_CXX14_CONSTEXPR bool operator()(T&& lhs, U&& rhs) const
	{
		return bksge::invoke(m_comp,
			bksge::invoke(m_proj, std::forward<T>(lhs)),
			bksge::invoke(m_proj, std::forward<U>(rhs)));
	}
};

template <typename Comp, typename Proj>
BKSGE_CXX14_CONSTEXPR CompProjT<Comp, Proj>
make_comp_proj(Comp& comp, Proj& proj)
{
	return CompProjT<Comp, Proj>{comp, proj};
}

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_DETAIL_MAKE_COMP_PROJ_HPP
