/**
 *	@file	save_dispatch.hpp
 *
 *	@brief	save_dispatch の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_SERIALIZATION_DETAIL_SAVE_DISPATCH_HPP
#define BKSGE_SERIALIZATION_DETAIL_SAVE_DISPATCH_HPP

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

class save_dispatch
{
private:
	template <typename Archive, typename T>
	struct is_save_version_free_invocable
	{
	private:
		template <typename A2, typename T2>
		static auto test(int) -> decltype(
			save(std::declval<A2&>(), std::declval<T2 const&>(), std::declval<bksge::serialization::version_t>()),
			std::true_type());

		template <typename A2, typename T2>
		static auto test(...)->std::false_type;

		using type = decltype(test<Archive, T>(0));

	public:
		static const bool value = type::value;
	};

	template <typename Archive, typename T>
	struct is_save_free_invocable
	{
	private:
		template <typename A2, typename T2>
		static auto test(int) -> decltype(
			save(std::declval<A2&>(), std::declval<T2 const&>()),
			std::true_type());

		template <typename A2, typename T2>
		static auto test(...)->std::false_type;

		using type = decltype(test<Archive, T>(0));

	public:
		static const bool value = type::value;
	};

	struct save_array
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T const& t)
		{
			ar.save_array(t);
		}
	};

	struct save_arithmetic
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T const& t)
		{
			ar.save_arithmetic(t);
		}
	};

	struct save_enum
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T const& t)
		{
			ar.save_enum(t);
		}
	};

	struct save_pointer
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T const& t)
		{
			ar.save_pointer(t);
		}
	};

	struct save_null_pointer
	{
		template <typename Archive, typename T>
		static void invoke(Archive&, T const&)
		{
		}
	};

	struct save_nvp
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T const& t)
		{
			ar.save_nvp(t);
		}
	};

	struct save_version_free
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T const& t, bksge::serialization::version_t version)
		{
			save(ar, t, version);
		}
	};

	struct save_free
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T const& t, bksge::serialization::version_t)
		{
			save(ar, t);
		}
	};

	struct save_object
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T const& t)
		{
			using type =
				typename std::conditional<
					access::is_save_version_memfun_invocable<Archive, T>::value,
					access::save_version_memfun,

				typename std::conditional<
					access::is_save_memfun_invocable<Archive, T>::value,
					access::save_memfun,

				typename std::conditional<
					is_save_version_free_invocable<Archive, T>::value,
					save_version_free,

				typename std::conditional<
					is_save_free_invocable<Archive, T>::value,
					save_free,

				serialize_dispatch
			>::type>::type>::type>::type;

			auto const version = detail::Version<T>::value;
			ar.save(version);
			type::invoke(ar, t, version);
		}
	};

public:
	template <typename Archive, typename T>
	static void invoke(Archive& ar, T const& t)
	{
		using type =
			typename std::conditional<
				std::is_array<T>::value,
				save_array,

			typename std::conditional<
				std::is_arithmetic<T>::value,
				save_arithmetic,

			typename std::conditional<
				std::is_enum<T>::value,
				save_enum,

			typename std::conditional<
				std::is_pointer<T>::value,
				save_pointer,

			typename std::conditional<
				std::is_null_pointer<T>::value,
				save_null_pointer,

			typename std::conditional<
				is_nvp<T>::value,
				save_nvp,

			save_object
		>::type>::type>::type>::type>::type>::type;

		type::invoke(ar, t);
	}
};

}	// namespace detail

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_SERIALIZATION_DETAIL_SAVE_DISPATCH_HPP
