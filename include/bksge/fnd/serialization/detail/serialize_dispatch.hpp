/**
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
#include <type_traits>
#include <utility>	// declval

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
			serialize(std::declval<A2&>(), std::declval<T2&>(), std::declval<bksge::serialization::version_t>()),
			std::true_type());

		template <typename A2, typename T2>
		static auto test(...)->std::false_type;

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
			serialize(std::declval<A2&>(), std::declval<T2&>()),
			std::true_type());

		template <typename A2, typename T2>
		static auto test(...)->std::false_type;

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
			typename std::conditional<
				access::is_serialize_version_memfun_invocable<Archive, T>::value,
				access::serialize_version_memfun,

			typename std::conditional<
				access::is_serialize_memfun_invocable<Archive, T>::value,
				access::serialize_memfun,

			typename std::conditional<
				is_serialize_version_free_invocable<Archive, T>::value,
				serialize_version_free,

			typename std::conditional<
				is_serialize_free_invocable<Archive, T>::value,
				serialize_free,

			serialize_fallback
		>::type>::type>::type>::type;

		type::invoke(ar, t, version);
	}
};

}	// namespace detail

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_FND_SERIALIZATION_DETAIL_SERIALIZE_DISPATCH_HPP
