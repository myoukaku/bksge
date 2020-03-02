/**
 *	@file	save_dispatch.hpp
 *
 *	@brief	save_dispatch の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SERIALIZATION_DETAIL_SAVE_DISPATCH_HPP
#define BKSGE_FND_SERIALIZATION_DETAIL_SAVE_DISPATCH_HPP

#include <bksge/fnd/serialization/detail/serialize_dispatch.hpp>
#include <bksge/fnd/serialization/version.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_null_pointer.hpp>
#include <bksge/fnd/type_traits/is_array.hpp>
#include <bksge/fnd/type_traits/is_arithmetic.hpp>
#include <bksge/fnd/type_traits/is_enum.hpp>
#include <bksge/fnd/type_traits/is_pointer.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
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
			bksge::true_type());

		template <typename A2, typename T2>
		static auto test(...)->bksge::false_type;

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
			bksge::true_type());

		template <typename A2, typename T2>
		static auto test(...)->bksge::false_type;

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
				bksge::conditional_t<
					access::is_save_version_memfun_invocable<Archive, T>::value,
					access::save_version_memfun,

				bksge::conditional_t<
					access::is_save_memfun_invocable<Archive, T>::value,
					access::save_memfun,

				bksge::conditional_t<
					is_save_version_free_invocable<Archive, T>::value,
					save_version_free,

				bksge::conditional_t<
					is_save_free_invocable<Archive, T>::value,
					save_free,

				serialize_dispatch
			>>>>;

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
			bksge::conditional_t<
				bksge::is_array<T>::value,
				save_array,

			bksge::conditional_t<
				bksge::is_arithmetic<T>::value,
				save_arithmetic,

			bksge::conditional_t<
				bksge::is_enum<T>::value,
				save_enum,

			bksge::conditional_t<
				bksge::is_pointer<T>::value,
				save_pointer,

			bksge::conditional_t<
				bksge::is_null_pointer<T>::value,
				save_null_pointer,

			bksge::conditional_t<
				is_nvp<T>::value,
				save_nvp,

			save_object
		>>>>>>;

		type::invoke(ar, t);
	}
};

}	// namespace detail

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_FND_SERIALIZATION_DETAIL_SAVE_DISPATCH_HPP
