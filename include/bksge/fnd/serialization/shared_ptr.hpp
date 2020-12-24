/**
 *	@file	shared_ptr.hpp
 *
 *	@brief	bksge::shared_ptr のシリアライズ
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SERIALIZATION_SHARED_PTR_HPP
#define BKSGE_FND_SERIALIZATION_SHARED_PTR_HPP

#include <bksge/fnd/memory/shared_ptr.hpp>

namespace bksge
{

namespace serialization
{

template <typename Archive, typename T>
inline void
save(Archive& ar, bksge::shared_ptr<T> const& t)
{
	T* p = t.get();
	ar << p;
}

template <typename T>
struct shared_ptr_helper
{
	bksge::shared_ptr<T>& m_shared_ptr;
	T**					m_ptr;

	void operator()()
	{
		m_shared_ptr.reset(*m_ptr);
		delete m_ptr;
	}
};

template <typename Archive, typename T>
inline void
load(Archive& ar, bksge::shared_ptr<T>& t)
{
	T** p = new T*();
	ar >> *p;
	ar.register_on_destroy(shared_ptr_helper<T>{t, p});
}

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_FND_SERIALIZATION_SHARED_PTR_HPP
