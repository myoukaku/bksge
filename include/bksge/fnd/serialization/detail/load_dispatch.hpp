/**
 *	@file	load_dispatch.hpp
 *
 *	@brief	load_dispatch の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SERIALIZATION_DETAIL_LOAD_DISPATCH_HPP
#define BKSGE_FND_SERIALIZATION_DETAIL_LOAD_DISPATCH_HPP

#include <bksge/fnd/serialization/detail/serialize_dispatch.hpp>
#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_null_pointer.hpp>
#include <bksge/fnd/type_traits/is_array.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/type_traits/is_enum.hpp>
#include <bksge/fnd/type_traits/is_pointer.hpp>
#include <bksge/fnd/type_traits/remove_const.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
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
			bksge::true_type());

		template <typename A2, typename T2>
		static auto test(...)->bksge::false_type;

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
			bksge::true_type());

		template <typename A2, typename T2>
		static auto test(...)->bksge::false_type;

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
			ar.load_nvp(const_cast<bksge::remove_const_t<T>&>(t));
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
				bksge::conditional_t<
					access::is_load_version_memfun_invocable<Archive, T>::value,
					access::load_version_memfun,

				bksge::conditional_t<
					access::is_load_memfun_invocable<Archive, T>::value,
					access::load_memfun,

				bksge::conditional_t<
					is_load_version_free_invocable<Archive, T>::value,
					load_version_free,

				bksge::conditional_t<
					is_load_free_invocable<Archive, T>::value,
					load_free,

				serialize_dispatch
			>>>>;

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
			bksge::conditional_t<
				bksge::is_array<T>::value,
				load_array,

			bksge::conditional_t<
				bksge::is_arithmetic<T>::value,
				load_arithmetic,

			bksge::conditional_t<
				bksge::is_enum<T>::value,
				load_enum,

			bksge::conditional_t<
				bksge::is_pointer<T>::value,
				load_pointer,

			bksge::conditional_t<
				bksge::is_null_pointer<T>::value,
				load_null_pointer,

			bksge::conditional_t<
				is_nvp<T>::value,
				load_nvp,

			load_object
		>>>>>>;

		type::invoke(ar, t);
	}
};

}	// namespace detail

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_FND_SERIALIZATION_DETAIL_LOAD_DISPATCH_HPP
