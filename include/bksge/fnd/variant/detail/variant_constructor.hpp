/**
 *	@file	variant_constructor.hpp
 *
 *	@brief	variant_constructor の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_CONSTRUCTOR_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_CONSTRUCTOR_HPP

#include <bksge/fnd/variant/detail/variant_alt.hpp>
#include <bksge/fnd/variant/detail/variant_destructor.hpp>
#include <bksge/fnd/variant/detail/visitation.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4702);	// 制御が渡らないコードです。

namespace bksge
{

namespace variant_detail
{

template <typename Traits>
class variant_constructor : public variant_destructor<Traits>
{
private:
	using base_type = variant_destructor<Traits>;
	using index_t = typename base_type::index_t;

public:
	using base_type::base_type;
	using base_type::operator=;

protected:
	template <std::size_t I, typename T, typename... Args>
	static T& construct_alt(variant_alt<I, T>& a, Args&&... args)
	{
		::new ((void*)bksge::addressof(a))
			variant_alt<I, T>(bksge::in_place, bksge::forward<Args>(args)...);
		return a.m_value;
	}

private:
	struct Visitor
	{
		template <typename LhsAlt, typename RhsAlt>
		void operator()(LhsAlt& lhs_alt, RhsAlt&& rhs_alt) const
		{
			construct_alt(
				lhs_alt,
				bksge::forward<RhsAlt>(rhs_alt).m_value);
		}
	};

protected:
	template <typename Rhs>
	static void generic_construct(variant_constructor& lhs, Rhs&& rhs)
	{
		lhs.destroy();
		if (!rhs.valueless_by_exception())
		{
			visitation::base_t::visit_alt_at(rhs.index(), Visitor{}, lhs, bksge::forward<Rhs>(rhs));
			lhs.m_index = static_cast<index_t>(rhs.index());
		}
	}
};


}	// namespace variant_detail

}	// namespace bksge

BKSGE_WARNING_POP();

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_CONSTRUCTOR_HPP
