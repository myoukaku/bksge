/**
 *	@file	load_dispatch.hpp
 *
 *	@brief	load_dispatch の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_SERIALIZATION_DETAIL_LOAD_DISPATCH_HPP
#define BKSGE_SERIALIZATION_DETAIL_LOAD_DISPATCH_HPP

#include <bksge/serialization/detail/serialize_dispatch.hpp>
#include <bksge/serialization/version.hpp>
#include <bksge/serialization/nvp.hpp>
#include <type_traits>
#include <utility>	// declval

namespace bksge
{

namespace serialization
{

namespace detail
{

class load_dispatch
{
private:
	template <typename Archive, typename T>
	struct is_load_version_free_invocable
	{
	private:
		template <typename A2, typename T2>
		static auto test(int) -> decltype(
			load(std::declval<A2&>(), std::declval<T2&>(), std::declval<bksge::serialization::version_t>()),
			std::true_type());

		template <typename A2, typename T2>
		static auto test(...)->std::false_type;

		using type = decltype(test<Archive, T>(0));

	public:
		static const bool value = type::value;
	};

	template <typename Archive, typename T>
	struct is_load_free_invocable
	{
	private:
		template <typename A2, typename T2>
		static auto test(int) -> decltype(
			load(std::declval<A2&>(), std::declval<T2&>()),
			std::true_type());

		template <typename A2, typename T2>
		static auto test(...)->std::false_type;

		using type = decltype(test<Archive, T>(0));

	public:
		static const bool value = type::value;
	};

	struct load_array
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T& t)
		{
			ar.load_array(t);
		}
	};

	struct load_arithmetic
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T& t)
		{
			ar.load_arithmetic(t);
		}
	};

	struct load_enum
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T& t)
		{
			ar.load_enum(t);
		}
	};

	struct load_pointer
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T& t)
		{
			ar.load_pointer(t);
		}
	};

	struct load_null_pointer
	{
		template <typename Archive, typename T>
		static void invoke(Archive&, T& t)
		{
			t = nullptr;
		}
	};

	struct load_nvp
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T& t)
		{
			ar.load_nvp(const_cast<typename std::remove_const<T>::type&>(t));
		}
	};

	struct load_version_free
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T& t, bksge::serialization::version_t version)
		{
			load(ar, t, version);
		}
	};

	struct load_free
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T& t, bksge::serialization::version_t)
		{
			load(ar, t);
		}
	};

	struct load_object
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T& t)
		{
			using type =
				typename std::conditional<
					access::is_load_version_memfun_invocable<Archive, T>::value,
					access::load_version_memfun,

				typename std::conditional<
					access::is_load_memfun_invocable<Archive, T>::value,
					access::load_memfun,

				typename std::conditional<
					is_load_version_free_invocable<Archive, T>::value,
					load_version_free,

				typename std::conditional<
					is_load_free_invocable<Archive, T>::value,
					load_free,

				serialize_dispatch
			>::type>::type>::type>::type;

			bksge::serialization::version_t version;
			ar.load(version);
			type::invoke(ar, t, version);
		}
	};

public:
	template <typename Archive, typename T>
	static void invoke(Archive& ar, T& t)
	{
		using type =
			typename std::conditional<
				std::is_array<T>::value,
				load_array,

			typename std::conditional<
				std::is_arithmetic<T>::value,
				load_arithmetic,

			typename std::conditional<
				std::is_enum<T>::value,
				load_enum,

			typename std::conditional<
				std::is_pointer<T>::value,
				load_pointer,

			typename std::conditional<
				std::is_null_pointer<T>::value,
				load_null_pointer,

			typename std::conditional<
				is_nvp<T>::value,
				load_nvp,

			load_object
		>::type>::type>::type>::type>::type>::type;

		type::invoke(ar, t);
	}
};

}	// namespace detail

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_SERIALIZATION_DETAIL_LOAD_DISPATCH_HPP
