﻿/**
 *	@file	text_iarchive.hpp
 *
 *	@brief	text_iarchive の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SERIALIZATION_TEXT_IARCHIVE_HPP
#define BKSGE_FND_SERIALIZATION_TEXT_IARCHIVE_HPP

#include <bksge/fnd/serialization/detail/load_dispatch.hpp>
#include <bksge/fnd/serialization/detail/pointer_loader.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/base_object.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <cstddef>
#include <cstdint>
#include <istream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <type_traits>

namespace bksge
{

namespace serialization
{

class text_iarchive_impl_base
{
public:
	virtual ~text_iarchive_impl_base()
	{
	}

	virtual void load_arithmetic(std::intmax_t&) = 0;
	virtual void load_arithmetic(std::uintmax_t&) = 0;
	virtual void load_arithmetic(float&) = 0;
	virtual void load_arithmetic(double&) = 0;
	virtual void load_arithmetic(long double&) = 0;
};

template <typename IStream>
class text_iarchive_impl
	: public text_iarchive_impl_base
{
public:
	explicit text_iarchive_impl(IStream& is)
		: m_is(is)
	{}

	void load_arithmetic(std::intmax_t& t) override
	{
		m_is >> t;
	}
	void load_arithmetic(std::uintmax_t& t) override
	{
		m_is >> t;
	}
	void load_arithmetic(float& t) override
	{
		m_is >> t;
	}
	void load_arithmetic(double& t) override
	{
		m_is >> t;
	}
	void load_arithmetic(long double& t) override
	{
		m_is >> t;
	}

private:
	text_iarchive_impl& operator=(text_iarchive_impl const&) = delete;

	IStream&	m_is;
};

class text_iarchive
{
public:
	template <typename CharT, typename Traits>
	explicit text_iarchive(std::basic_istream<CharT, Traits>& is)
		: m_impl(new text_iarchive_impl<std::basic_istream<CharT, Traits>>(is))
	{
		m_tracking[nullptr] = 0;
	}

	~text_iarchive()
	{
		// ※このループ中にm_pointer_listに要素が追加されて、
		// 　イテレータが無効になる可能性があるので、
		// 　Range-based For や イテレータでループはできない
		for (std::size_t i = 0; i < m_pointer_list.size(); ++i)
		{
			auto&& ptr = m_pointer_list[i];

			std::size_t id;
			load(id);

			bool found = false;

			for (auto&& it : m_tracking)
			{
				if (it.second == id)
				{
					ptr.set_address(it.first);
					found = true;
					break;
				}
			}

			if (!found)
			{
				ptr.load(*this);
			}
		}
	}

	template <typename T>
	text_iarchive& operator>>(T& t)
	{
		object_tracking(t);
		load(t);
		return *this;
	}

	template <typename T>
	text_iarchive& operator&(T& t)
	{
		return *this >> t;
	}

private:
	template <typename T>
	void load(T& t)
	{
		bksge::serialization::detail::load_dispatch::invoke(*this, t);
	}

	template <typename T, std::size_t N>
	void load_array(T (&t)[N])
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			*this >> t[i];
		}
	}

	template <typename T, bksge::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
	void load_arithmetic(T& t)
	{
		m_impl->load_arithmetic(t);
	}

	template <typename T, bksge::enable_if_t<std::is_integral<T>::value>* = nullptr>
	void load_arithmetic(T& t)
	{
		load_integral(t);
	}

	template <typename T, bksge::enable_if_t<std::is_unsigned<T>::value>* = nullptr>
	void load_integral(T& t)
	{
		std::uintmax_t i;
		m_impl->load_arithmetic(i);
		t = static_cast<T>(i);
	}

	template <typename T, bksge::enable_if_t<std::is_signed<T>::value>* = nullptr>
	void load_integral(T& t)
	{
		std::intmax_t i;
		m_impl->load_arithmetic(i);
		t = static_cast<T>(i);
	}

	template <typename T>
	void load_enum(T& t)
	{
		std::uintmax_t i;
		m_impl->load_arithmetic(i);
		t = static_cast<T>(i);
	}

	template <typename T>
	void load_pointer(T& t)
	{
		m_pointer_list.push_back(detail::pointer_loader<text_iarchive>(t));
	}

	template <typename T>
	void load_nvp(nvp<T>& t)
	{
		*this >> t.value();
	}

	template <typename T>
	void object_tracking(T const& t)
	{
		auto it = m_tracking.find(&t);
		if (it == m_tracking.end())
		{
			m_tracking[&t] = m_tracking.size();
		}
	}

	template <typename T>
	void object_tracking(nvp<T> const&)
	{
	}

	template <typename B, typename D>
	void object_tracking(base_object<B, D> const&)
	{
	}

private:
	std::unique_ptr<text_iarchive_impl_base>	       m_impl;
	std::unordered_map<const void*, std::size_t>	   m_tracking;
	std::vector<detail::pointer_loader<text_iarchive>> m_pointer_list;

	friend class bksge::serialization::detail::load_dispatch;
};

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_FND_SERIALIZATION_TEXT_IARCHIVE_HPP