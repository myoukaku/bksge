/**
 *	@file	optional_hash_call_base.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_HASH_CALL_BASE_HPP
#define BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_HASH_CALL_BASE_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/functional/hash.hpp>
#include <bksge/fnd/optional/optional.hpp>
#include <bksge/fnd/detail/enable_hash_call.hpp>
#include <bksge/fnd/type_traits/remove_const.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <
	typename T,
	bool = bksge::detail::enable_hash_call<T>::value
>
struct optional_hash_call_base
{
	using U = bksge::remove_const_t<T>;

	bksge::size_t operator()(optional<T> const& t) const
		BKSGE_NOEXCEPT_IF_EXPR(bksge::hash<U>{}(*t))
	{
		BKSGE_CONSTEXPR auto magic_disengaged_hash = static_cast<bksge::size_t>(-3333);
		return t ? bksge::hash<U>{}(*t) : magic_disengaged_hash;
	}
};

template <typename T>
struct optional_hash_call_base<T, false>
{
private:
	// Private rather than deleted to be non-trivially-copyable.
	optional_hash_call_base(optional_hash_call_base&&);
	~optional_hash_call_base();
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_OPTIONAL_DETAIL_OPTIONAL_HASH_CALL_BASE_HPP
