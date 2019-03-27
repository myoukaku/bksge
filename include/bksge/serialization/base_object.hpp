/**
 *	@file	base_object.hpp
 *
 *	@brief	base_object の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_SERIALIZATION_BASE_OBJECT_HPP
#define BKSGE_SERIALIZATION_BASE_OBJECT_HPP

#include <bksge/serialization/access.hpp>

namespace bksge
{

namespace serialization
{

template <typename Base, typename Derived>
class base_object
{
public:
	explicit base_object(Derived& d)
		: m_derived(&d)
	{}

private:
	friend class bksge::serialization::access;

	template <typename Archive>
	void serialize(Archive& ar)
	{
		ar & *(static_cast<Base*>(m_derived));
	}

private:
	Derived*	m_derived;
};

template <typename Base, typename Derived>
inline base_object<Base, Derived> const
make_base_object(Derived& d)
{
	return base_object<Base, Derived>(d);
}

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_SERIALIZATION_BASE_OBJECT_HPP
