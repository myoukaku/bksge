/**
 *	@file	text_oarchive.hpp
 *
 *	@brief	text_oarchive の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_SERIALIZATION_TEXT_OARCHIVE_HPP
#define BKSGE_SERIALIZATION_TEXT_OARCHIVE_HPP

#include <bksge/serialization/detail/save_dispatch.hpp>
#include <bksge/serialization/detail/pointer_saver.hpp>
#include <bksge/serialization/nvp.hpp>
#include <bksge/serialization/base_object.hpp>
#include <cstddef>
#include <iomanip>
#include <limits>
#include <memory>
#include <ostream>
#include <unordered_map>
#include <vector>

namespace bksge
{

namespace serialization
{

class text_oarchive_impl_base
{
public:
	virtual ~text_oarchive_impl_base()
	{}

	virtual void save_arithmetic(bool) = 0;
	virtual void save_arithmetic(char) = 0;
	virtual void save_arithmetic(wchar_t) = 0;
	virtual void save_arithmetic(signed char) = 0;
	virtual void save_arithmetic(unsigned char) = 0;
	virtual void save_arithmetic(signed short) = 0;
	virtual void save_arithmetic(unsigned short) = 0;
	virtual void save_arithmetic(signed int) = 0;
	virtual void save_arithmetic(unsigned int) = 0;
	virtual void save_arithmetic(signed long) = 0;
	virtual void save_arithmetic(unsigned long) = 0;
	virtual void save_arithmetic(signed long long) = 0;
	virtual void save_arithmetic(unsigned long long) = 0;
	virtual void save_arithmetic(float) = 0;
	virtual void save_arithmetic(double) = 0;
	virtual void save_arithmetic(long double) = 0;
};

template <typename OStream>
class text_oarchive_impl
	: public text_oarchive_impl_base
{
public:
	explicit text_oarchive_impl(OStream& os)
		: m_os(os)
	{}

	void save_arithmetic(bool t) override
	{
		m_os << t << " ";
	}
	void save_arithmetic(char t) override
	{
		save_arithmetic(static_cast<short int>(t));
	}
	void save_arithmetic(wchar_t t) override
	{
		static_assert(sizeof(wchar_t) <= sizeof(unsigned int), "");
		save_arithmetic(static_cast<unsigned int>(t));
	}
	void save_arithmetic(signed char t) override
	{
		save_arithmetic(static_cast<short int>(t));
	}
	void save_arithmetic(unsigned char t) override
	{
		save_arithmetic(static_cast<short unsigned int>(t));
	}
	void save_arithmetic(signed short t) override
	{
		m_os << t << " ";
	}
	void save_arithmetic(unsigned short t) override
	{
		m_os << t << " ";
	}
	void save_arithmetic(signed int t) override
	{
		m_os << t << " ";
	}
	void save_arithmetic(unsigned int t) override
	{
		m_os << t << " ";
	}
	void save_arithmetic(signed long t) override
	{
		m_os << t << " ";
	}
	void save_arithmetic(unsigned long t) override
	{
		m_os << t << " ";
	}
	void save_arithmetic(signed long long t) override
	{
		m_os << t << " ";
	}
	void save_arithmetic(unsigned long long t) override
	{
		m_os << t << " ";
	}
	void save_arithmetic(float t) override
	{
		auto const digits = std::numeric_limits<float>::max_digits10;
		m_os << std::setprecision(digits) << std::scientific << t << " ";
	}
	void save_arithmetic(double t) override
	{
		auto const digits = std::numeric_limits<double>::max_digits10;
		m_os << std::setprecision(digits) << std::scientific << t << " ";
	}
	void save_arithmetic(long double t) override
	{
		auto const digits = std::numeric_limits<long double>::max_digits10;
		m_os << std::setprecision(digits) << std::scientific << t << " ";
	}

private:
	text_oarchive_impl& operator=(text_oarchive_impl const&) = delete;

	OStream&	m_os;
};

class text_oarchive
{
public:
	template <typename CharT, typename Traits>
	explicit text_oarchive(std::basic_ostream<CharT, Traits>& os)
		: m_impl(new text_oarchive_impl<std::basic_ostream<CharT, Traits>>(os))
	{
		m_tracking[nullptr] = 0;
	}

	~text_oarchive()
	{
		// ※このループ中にm_pointer_listに要素が追加されて、
		// 　イテレータが無効になる可能性があるので、
		// 　Range-based For や イテレータでループはできない
		for (std::size_t i = 0; i < m_pointer_list.size(); ++i)
		{
			auto&& ptr = m_pointer_list[i];

			auto it = m_tracking.find(ptr.get_address());

			if (it != m_tracking.end())
			{
				save(it->second);
			}
			else
			{
				save(m_tracking.size()+1);
				ptr.save(*this);
			}
		}
	}

	template <typename T>
	text_oarchive& operator<<(T const& t)
	{
		object_tracking(t);
		save(t);
		return *this;
	}

	template <typename T>
	text_oarchive& operator&(T const& t)
	{
		return *this << t;
	}

private:
	template <typename T>
	void save(T const& t)
	{
		bksge::serialization::detail::save_dispatch::invoke(*this, t);
	}

	template <typename T, std::size_t N>
	void save_array(T const (&t)[N])
	{
		for (std::size_t i = 0; i < N; ++i)
		{
			*this << t[i];
		}
	}

	template <typename T>
	void save_arithmetic(T const& t)
	{
		m_impl->save_arithmetic(t);
	}

	template <typename T>
	void save_enum(T const& t)
	{
		m_impl->save_arithmetic(t);
	}

	template <typename T>
	void save_pointer(T const& t)
	{
		m_pointer_list.push_back(detail::pointer_saver<text_oarchive>(const_cast<T&>(t)));
	}

	template <typename T>
	void save_nvp(nvp<T> const& t)
	{
		*this << t.value();
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
	std::unique_ptr<text_oarchive_impl_base>	      m_impl;
	std::unordered_map<const void*, std::size_t>	  m_tracking;
	std::vector<detail::pointer_saver<text_oarchive>> m_pointer_list;

	friend class bksge::serialization::detail::save_dispatch;
};

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_SERIALIZATION_TEXT_OARCHIVE_HPP
