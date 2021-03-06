﻿/**
 *	@file	serialize_dispatch.hpp
 *
 *	@brief	serialize_dispatch の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SERIALIZATION_DETAIL_SERIALIZE_DISPATCH_HPP
#define BKSGE_FND_SERIALIZATION_DETAIL_SERIALIZE_DISPATCH_HPP

#include <bksge/fnd/serialization/access.hpp>
#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/utility/declval.hpp>

namespace bksge
{

namespace serialization
{

namespace detail
{

class serialize_dispatch
{
private:
	template <typename Archive, typename T>
	struct is_serialize_version_free_invocable
	{
	private:
		template <typename A2, typename T2>
		static auto test(int) -> decltype(
			serialize(bksge::declval<A2&>(), bksge::declval<T2&>(), bksge::declval<bksge::serialization::version_t>()),
			bksge::true_type());

		template <typename A2, typename T2>
		static auto test(...)->bksge::false_type;

		using type = decltype(test<Archive, T>(0));

	public:
		static const bool value = type::value;
	};

	template <typename Archive, typename T>
	struct is_serialize_free_invocable
	{
	private:
		template <typename A2, typename T2>
		static auto test(int) -> decltype(
			serialize(bksge::declval<A2&>(), bksge::declval<T2&>()),
			bksge::true_type());

		template <typename A2, typename T2>
		static auto test(...)->bksge::false_type;

		using type = decltype(test<Archive, T>(0));

	public:
		static const bool value = type::value;
	};

	struct serialize_version_free
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T const& t, bksge::serialization::version_t version)
		{
			serialize(ar, const_cast<T&>(t), version);
		}
	};

	struct serialize_free
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T const& t, bksge::serialization::version_t)
		{
			serialize(ar, const_cast<T&>(t));
		}
	};

	struct serialize_fallback
	{
		template <typename Archive, typename T, bool Dummy = false>
		static void invoke(Archive&, T const&, bksge::serialization::version_t)
		{
			static_assert(Dummy, "This type is not serializable.");
		}
	};

public:
	template <typename Archive, typename T>
	static void invoke(Archive& ar, T const& t, bksge::serialization::version_t version)
	{
		using type =
			bksge::conditional_t<
				access::is_serialize_version_memfun_invocable<Archive, T>::value,
				access::serialize_version_memfun,

			bksge::conditional_t<
				access::is_serialize_memfun_invocable<Archive, T>::value,
				access::serialize_memfun,

			bksge::conditional_t<
				is_serialize_version_free_invocable<Archive, T>::value,
				serialize_version_free,

			bksge::conditional_t<
				is_serialize_free_invocable<Archive, T>::value,
				serialize_free,

			serialize_fallback
		>>>>;

		type::invoke(ar, t, version);
	}
};

}	// namespace detail

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_FND_SERIALIZATION_DETAIL_SERIALIZE_DISPATCH_HPP
