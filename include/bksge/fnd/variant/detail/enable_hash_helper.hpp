/**
 *	@file	enable_hash_helper.hpp
 *
 *	@brief	enable_hash_helper の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_ENABLE_HASH_HELPER_HPP
#define BKSGE_FND_VARIANT_DETAIL_ENABLE_HASH_HELPER_HPP

#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_invocable_r.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <cstddef>
#include <functional>

namespace bksge
{

namespace variant_detail
{

template <typename Key, typename Hash = std::hash<Key>>
using has_enabled_hash = bksge::conjunction<
    bksge::is_copy_constructible<Hash>,
    bksge::is_move_constructible<Hash>,
    bksge::is_invocable_r<std::size_t, Hash, Key const&>,
    bksge::is_default_constructible<Hash>
>;

template <typename Type, typename>
using enable_hash_helper_imp = Type;

template <typename Type, typename... Keys>
using enable_hash_helper =
	enable_hash_helper_imp<
		Type,
		bksge::enable_if_t<
			bksge::conjunction<has_enabled_hash<Keys>...>::value
		>
	>;

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_ENABLE_HASH_HELPER_HPP
