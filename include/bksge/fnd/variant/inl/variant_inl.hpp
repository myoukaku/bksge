/**
 *	@file	variant_inl.hpp
 *
 *	@brief	variant の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_INL_VARIANT_INL_HPP
#define BKSGE_FND_VARIANT_INL_VARIANT_INL_HPP

#include <bksge/fnd/variant/variant.hpp>
#include <bksge/fnd/variant/detail/visitation.hpp>
#include <bksge/fnd/functional/equal_to.hpp>
#include <bksge/fnd/functional/not_equal_to.hpp>
#include <bksge/fnd/functional/greater.hpp>
#include <bksge/fnd/functional/greater_equal.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/functional/less_equal.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace variant_detail
{

template <typename Operator>
struct convert_to_bool
{
	template <typename T1, typename T2>
	BKSGE_CONSTEXPR bool operator()(T1&& t1, T2&& t2) const
	{
		static_assert(bksge::is_convertible<decltype(Operator{}(bksge::forward<T1>(t1), bksge::forward<T2>(t2))), bool>::value,
			"the relational operator does not return a type which is implicitly convertible to bool");
		return Operator{}(bksge::forward<T1>(t1), bksge::forward<T2>(t2));
	}
};

}	// namespace variant_detail

template <typename... Types>
inline BKSGE_CONSTEXPR bool
operator==(variant<Types...> const& lhs, variant<Types...> const& rhs)
{
	using variant_detail::visitation::variant_t;
	using F = variant_detail::convert_to_bool<bksge::equal_to<>>;
	return
		(lhs.index() != rhs.index())   ? false :
		(lhs.valueless_by_exception()) ? true  :
		variant_t::visit_value_at(lhs.index(), F{}, lhs, rhs);
}

template <typename... Types>
inline BKSGE_CONSTEXPR bool
operator!=(variant<Types...> const& lhs, variant<Types...> const& rhs)
{
	using variant_detail::visitation::variant_t;
	using F = variant_detail::convert_to_bool<bksge::not_equal_to<>>;
	return
		(lhs.index() != rhs.index())   ? true  :
		(lhs.valueless_by_exception()) ? false :
		variant_t::visit_value_at(lhs.index(), F{}, lhs, rhs);
}

template <typename... Types>
inline BKSGE_CONSTEXPR bool
operator<(variant<Types...> const& lhs, variant<Types...> const& rhs)
{
	using variant_detail::visitation::variant_t;
	using F = variant_detail::convert_to_bool<bksge::less<>>;
	return
		(rhs.valueless_by_exception()) ? false :
		(lhs.valueless_by_exception()) ? true  :
		(lhs.index() < rhs.index())    ? true  :
		(lhs.index() > rhs.index())    ? false :
		variant_t::visit_value_at(lhs.index(), F{}, lhs, rhs);
}

template <typename... Types>
inline BKSGE_CONSTEXPR bool
operator>(variant<Types...> const& lhs, variant<Types...> const& rhs)
{
	using variant_detail::visitation::variant_t;
	using F = variant_detail::convert_to_bool<bksge::greater<>>;
	return
		(lhs.valueless_by_exception()) ? false :
		(rhs.valueless_by_exception()) ? true  :
		(lhs.index() > rhs.index())    ? true  :
		(lhs.index() < rhs.index())    ? false :
		variant_t::visit_value_at(lhs.index(), F{}, lhs, rhs);
}

template <typename... Types>
inline BKSGE_CONSTEXPR bool
operator<=(variant<Types...> const& lhs, variant<Types...> const& rhs)
{
	using variant_detail::visitation::variant_t;
	using F = variant_detail::convert_to_bool<bksge::less_equal<>>;
	return
		(lhs.valueless_by_exception()) ? true  :
		(rhs.valueless_by_exception()) ? false :
		(lhs.index() < rhs.index())    ? true  :
		(lhs.index() > rhs.index())    ? false :
		variant_t::visit_value_at(lhs.index(), F{}, lhs, rhs);
}

template <typename... Types>
inline BKSGE_CONSTEXPR bool
operator>=(variant<Types...> const& lhs, variant<Types...> const& rhs)
{
	using variant_detail::visitation::variant_t;
	using F = variant_detail::convert_to_bool<bksge::greater_equal<>>;
	return
		(rhs.valueless_by_exception()) ? true  :
		(lhs.valueless_by_exception()) ? false :
		(lhs.index() > rhs.index())    ? true  :
		(lhs.index() < rhs.index())    ? false :
		variant_t::visit_value_at(lhs.index(), F{}, lhs, rhs);
}

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_INL_VARIANT_INL_HPP
