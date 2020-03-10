/**
 *	@file	pointer_saver.hpp
 *
 *	@brief	pointer_saver の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SERIALIZATION_DETAIL_POINTER_SAVER_HPP
#define BKSGE_FND_SERIALIZATION_DETAIL_POINTER_SAVER_HPP

#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace serialization
{

namespace detail
{

template <typename Archive>
class pointer_saver
{
public:
	template <typename T>
	explicit pointer_saver(T*& ptr)
		: m_impl(new Impl<T>(ptr))
	{}

	pointer_saver(pointer_saver const&) = delete;

	pointer_saver(pointer_saver&& rhs) BKSGE_NOEXCEPT_OR_NOTHROW
		: m_impl(bksge::move(rhs.m_impl))
	{}

	const void* get_address() const
	{
		return m_impl->get_address();
	}

	void save(Archive& ar)
	{
		m_impl->save(ar);
	}

private:
	class ImplBase
	{
	public:
		virtual ~ImplBase(){}
		virtual const void* get_address() const = 0;
		virtual void save(Archive& ar) = 0;
	};

	template <typename T>
	class Impl : public ImplBase
	{
	public:
		explicit Impl(T*& ptr) : m_ptr(ptr) {}

		virtual const void* get_address() const
		{
			return m_ptr;
		}

		virtual void save(Archive& ar)
		{
			ar & *m_ptr;
		}

	private:
		Impl& operator=(Impl const&) = delete;

		T*&	m_ptr;
	};

	bksge::unique_ptr<ImplBase> m_impl;
};

}	// namespace detail

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_FND_SERIALIZATION_DETAIL_POINTER_SAVER_HPP
