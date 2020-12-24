/**
 *	@file	text_oarchive.hpp
 *
 *	@brief	text_oarchive の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SERIALIZATION_TEXT_OARCHIVE_HPP
#define BKSGE_FND_SERIALIZATION_TEXT_OARCHIVE_HPP

#include <bksge/fnd/serialization/detail/save_dispatch.hpp>
#include <bksge/fnd/serialization/detail/pointer_saver.hpp>
#include <bksge/fnd/serialization/nvp.hpp>
#include <bksge/fnd/serialization/base_object.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstdint/intmax_t.hpp>
#include <bksge/fnd/cstdint/uintmax_t.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/unordered_map/unordered_map.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/limits.hpp>
#include <iomanip>
#include <ostream>

namespace bksge
{

namespace serialization
{

class text_oarchive_impl_base
{
public:
	virtual ~text_oarchive_impl_base()
	{}

	virtual void save_arithmetic(bksge::intmax_t) = 0;
	virtual void save_arithmetic(bksge::uintmax_t) = 0;
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

	void save_arithmetic(bksge::intmax_t t) override
	{
		m_os << t << " ";
	}
	void save_arithmetic(bksge::uintmax_t t) override
	{
		m_os << t << " ";
	}
	void save_arithmetic(float t) override
	{
		save_float(t);
	}
	void save_arithmetic(double t) override
	{
		save_float(t);
	}
	void save_arithmetic(long double t) override
	{
		save_float(t);
	}

private:
	template <typename T>
	void save_float(T t)
	{
		auto const digits = bksge::numeric_limits<T>::max_digits10;
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
		for (bksge::size_t i = 0; i < m_pointer_list.size(); ++i)
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

	template <typename T, bksge::size_t N>
	void save_array(T const (&t)[N])
	{
		for (bksge::size_t i = 0; i < N; ++i)
		{
			*this << t[i];
		}
	}

	template <typename T, bksge::enable_if_t<std::is_floating_point<T>::value>* = nullptr>
	void save_arithmetic(T const& t)
	{
		m_impl->save_arithmetic(t);
	}

	template <typename T, bksge::enable_if_t<std::is_integral<T>::value>* = nullptr>
	void save_arithmetic(T const& t)
	{
		save_integral(t);
	}

	template <typename T, bksge::enable_if_t<std::is_unsigned<T>::value>* = nullptr>
	void save_integral(T const& t)
	{
		m_impl->save_arithmetic(static_cast<bksge::uintmax_t>(t));
	}

	template <typename T, bksge::enable_if_t<std::is_signed<T>::value>* = nullptr>
	void save_integral(T const& t)
	{
		m_impl->save_arithmetic(static_cast<bksge::intmax_t>(t));
	}

	template <typename T>
	void save_enum(T const& t)
	{
		m_impl->save_arithmetic(static_cast<bksge::uintmax_t>(t));
	}

	template <typename T>
	void save_pointer(T const& t)
	{
		m_pointer_list.push_back(detail::pointer_saver<text_oarchive>(t));
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
	bksge::unique_ptr<text_oarchive_impl_base>			m_impl;
	bksge::unordered_map<const void*, bksge::size_t>	m_tracking;
	bksge::vector<detail::pointer_saver<text_oarchive>>	m_pointer_list;

	friend class bksge::serialization::detail::save_dispatch;
};

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_FND_SERIALIZATION_TEXT_OARCHIVE_HPP
