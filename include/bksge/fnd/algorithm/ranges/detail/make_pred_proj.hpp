/**
 *	@file	make_pred_proj.hpp
 *
 *	@brief	ranges::detail::make_pred_proj の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_DETAIL_MAKE_PRED_PROJ_HPP
#define BKSGE_FND_ALGORITHM_RANGES_DETAIL_MAKE_PRED_PROJ_HPP

#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

template <typename Pred, typename Proj>
struct PredProjT
{
	Pred& m_pred;
	Proj& m_proj;

	template <typename T>
	BKSGE_CXX14_CONSTEXPR bool operator()(T&& arg) const
	{
		return bksge::invoke(m_pred,
			bksge::invoke(m_proj, bksge::forward<T>(arg)));
	}
};

template <typename Pred, typename Proj>
BKSGE_CXX14_CONSTEXPR PredProjT<Pred, Proj>
make_pred_proj(Pred& pred, Proj& proj)
{
	return PredProjT<Pred, Proj>{pred, proj};
}

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_DETAIL_MAKE_PRED_PROJ_HPP
