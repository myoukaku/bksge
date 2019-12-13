/**
 *	@file	nvp.hpp
 *
 *	@brief	nvp の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SERIALIZATION_NVP_HPP
#define BKSGE_FND_SERIALIZATION_NVP_HPP

#include <type_traits>
#include <utility>

namespace bksge
{

namespace serialization
{

template <typename T>
class nvp
{
public:
	explicit nvp(char const* name, T& t)
		: m_pair(name, t)
	{}

	char const* name() const
	{
		return m_pair.first;
	}

	T const& value() const
	{
		return m_pair.second;
	}

	T& value()
	{
		return m_pair.second;
	}

private:
	std::pair<char const*, T&>	m_pair;
};

template <typename T>
inline nvp<T> const
make_nvp(char const* name, T& t)
{
	return nvp<T>(name, t);
}

template <typename T>
struct is_nvp : public std::false_type {};

template <typename T>
struct is_nvp<nvp<T>> : public std::true_type {};

template <typename T>
struct is_nvp<nvp<T> const> : public std::true_type {};

template <typename T>
struct is_nvp<nvp<T> volatile> : public std::true_type {};

template <typename T>
struct is_nvp<nvp<T> const volatile> : public std::true_type {};

}	// namespace serialization

}	// namespace bksge

#include <bksge/fnd/preprocessor/stringize.hpp>

#define BKSGE_SERIALIZATION_NVP(name) \
	bksge::serialization::make_nvp(BKSGE_PP_STRINGIZE(name), name)

#endif // BKSGE_FND_SERIALIZATION_NVP_HPP
