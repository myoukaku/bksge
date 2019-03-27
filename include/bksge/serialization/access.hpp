/**
 *	@file	access.hpp
 *
 *	@brief	access の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_SERIALIZATION_ACCESS_HPP
#define BKSGE_SERIALIZATION_ACCESS_HPP

#include <bksge/serialization/version.hpp>
#include <type_traits>
#include <utility>	// declval

namespace bksge
{

namespace serialization
{

class access
{
public:
	template <typename Archive, typename T>
	struct is_save_version_memfun_invocable
	{
	private:
		template <typename A2, typename T2>
		static auto test(int) -> decltype(
			std::declval<T2>().save(
				std::declval<A2&>(),
				std::declval<bksge::serialization::version_t>()),
			std::true_type());

		template <typename A2, typename T2>
		static auto test(...)->std::false_type;

		using type = decltype(test<Archive, T>(0));

	public:
		static const bool value = type::value;
	};

	template <typename Archive, typename T>
	struct is_save_memfun_invocable
	{
	private:
		template <typename A2, typename T2>
		static auto test(int) -> decltype(
			std::declval<T2>().save(
				std::declval<A2&>()),
			std::true_type());

		template <typename A2, typename T2>
		static auto test(...)->std::false_type;

		using type = decltype(test<Archive, T>(0));

	public:
		static const bool value = type::value;
	};

	template <typename Archive, typename T>
	struct is_load_version_memfun_invocable
	{
	private:
		template <typename A2, typename T2>
		static auto test(int) -> decltype(
			std::declval<typename std::remove_const<T2>::type>().load(
				std::declval<A2&>(),
				std::declval<bksge::serialization::version_t>()),
			std::true_type());

		template <typename A2, typename T2>
		static auto test(...)->std::false_type;

		using type = decltype(test<Archive, T>(0));

	public:
		static const bool value = type::value;
	};

	template <typename Archive, typename T>
	struct is_load_memfun_invocable
	{
	private:
		template <typename A2, typename T2>
		static auto test(int) -> decltype(
			std::declval<typename std::remove_const<T2>::type>().load(
				std::declval<A2&>()),
			std::true_type());

		template <typename A2, typename T2>
		static auto test(...)->std::false_type;

		using type = decltype(test<Archive, T>(0));

	public:
		static const bool value = type::value;
	};

	template <typename Archive, typename T>
	struct is_serialize_version_memfun_invocable
	{
	private:
		template <typename A2, typename T2>
		static auto test(int) -> decltype(
			std::declval<T2>().serialize(
				std::declval<A2&>(),
				std::declval<bksge::serialization::version_t>()),
			std::true_type());

		template <typename A2, typename T2>
		static auto test(...)->std::false_type;

		using type = decltype(test<Archive, T>(0));

	public:
		static const bool value = type::value;
	};

	template <typename Archive, typename T>
	struct is_serialize_memfun_invocable
	{
	private:
		template <typename A2, typename T2>
		static auto test(int) -> decltype(
			std::declval<T2>().serialize(
				std::declval<A2&>()),
			std::true_type());

		template <typename A2, typename T2>
		static auto test(...)->std::false_type;

		using type = decltype(test<Archive, T>(0));

	public:
		static const bool value = type::value;
	};

	struct save_version_memfun
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T const& t, bksge::serialization::version_t version)
		{
			t.save(ar, version);
		}
	};

	struct save_memfun
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T const& t, bksge::serialization::version_t)
		{
			t.save(ar);
		}
	};

	struct load_version_memfun
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T& t, bksge::serialization::version_t version)
		{
			t.load(ar, version);
		}
	};

	struct load_memfun
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T& t, bksge::serialization::version_t)
		{
			t.load(ar);
		}
	};

	struct serialize_version_memfun
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T const& t, bksge::serialization::version_t version)
		{
			const_cast<typename std::remove_const<T>::type&>(t).serialize(ar, version);
		}
	};

	struct serialize_memfun
	{
		template <typename Archive, typename T>
		static void invoke(Archive& ar, T const& t, bksge::serialization::version_t)
		{
			const_cast<typename std::remove_const<T>::type&>(t).serialize(ar);
		}
	};
};

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_SERIALIZATION_ACCESS_HPP
