﻿/**
 *	@file	pointer_loader.hpp
 *
 *	@brief	pointer_loader の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_SERIALIZATION_DETAIL_POINTER_LOADER_HPP
#define BKSGE_SERIALIZATION_DETAIL_POINTER_LOADER_HPP

#include <bksge/config.hpp>
#include <memory>	// unique_ptr
#include <type_traits>
#include <utility>

namespace bksge
{

namespace serialization
{

namespace detail
{

template <typename Archive>
class pointer_loader
{
public:
	template <typename T>
	explicit pointer_loader(T*& ptr)
		: m_impl(new Impl<T>(ptr))
	{}

	pointer_loader(pointer_loader const&) = delete;

	pointer_loader(pointer_loader&& rhs) BKSGE_NOEXCEPT_OR_NOTHROW
		: m_impl(std::move(rhs.m_impl))
	{}

	void set_address(void const* ptr)
	{
		m_impl->set_address(ptr);
	}

	void load(Archive& ar)
	{
		m_impl->load(ar);
	}

private:
	class ImplBase
	{
	public:
		virtual ~ImplBase(){}
		virtual void set_address(void const* ptr) = 0;
		virtual void load(Archive& ar) = 0;
	};

	template <typename T>
	class Impl : public ImplBase
	{
	public:
		explicit Impl(T*& ptr) : m_ptr(ptr) {}

		virtual void set_address(void const* ptr)
		{
			m_ptr = static_cast<T*>(const_cast<void*>(ptr));
		}

		virtual void load(Archive& ar)
		{
			using type = typename std::remove_cv<T>::type;
			type* ptr = new type();
			ar & *ptr;
			m_ptr = ptr;
		}

	private:
		Impl& operator=(Impl const&) = delete;

		T*&	m_ptr;
	};

	std::unique_ptr<ImplBase> m_impl;
};

}	// namespace detail

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_SERIALIZATION_DETAIL_POINTER_LOADER_HPP
