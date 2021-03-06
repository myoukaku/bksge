﻿/**
 *	@file	type_id.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_FND_VARIANT_TYPE_ID_HPP
#define UNIT_TEST_FND_VARIANT_TYPE_ID_HPP

#include <typeinfo>

namespace bksge_variant_test
{

// TypeID - Represent a unique identifier for a type. TypeID allows equality
// comparisons between different types.
struct TypeID
{
	friend bool operator==(TypeID const& LHS, TypeID const& RHS)
	{
		return LHS.m_id == RHS.m_id;
	}
	friend bool operator!=(TypeID const& LHS, TypeID const& RHS)
	{
		return LHS.m_id != RHS.m_id;
	}

	//bksge::string name() const
	//{
	//	return demangle(m_id);
	//}

	//void dump() const
	//{
	//	bksge::string s = name();
	//	std::printf("TypeID: %s\n", s.c_str());
	//}

private:
	explicit constexpr TypeID(const char* xid) : m_id(xid) {}

	TypeID(const TypeID&) = delete;
	TypeID& operator=(TypeID const&) = delete;

	const char* const m_id;
	template <typename T> friend TypeID const& makeTypeIDImp();
};

// makeTypeID - Return the TypeID for the specified type 'T'.
template <typename T>
inline TypeID const& makeTypeIDImp()
{
	static const TypeID id(typeid(T).name());
	return id;
}

template <typename T>
struct TypeWrapper {};

template <typename T>
inline TypeID const& makeTypeID()
{
	return makeTypeIDImp<TypeWrapper<T>>();
}

template <typename ...Args>
struct ArgumentListID {};

// makeArgumentID - Create and return a unique identifier for a given set
// of arguments.
template <typename ...Args>
inline TypeID const& makeArgumentID()
{
	return makeTypeIDImp<ArgumentListID<Args...>>();
}

#if 0

// COMPARE_TYPEID(...) is a utility macro for generating diagnostics when
// two typeid's are expected to be equal
#define COMPARE_TYPEID(LHS, RHS) CompareTypeIDVerbose(#LHS, LHS, #RHS, RHS)

inline bool CompareTypeIDVerbose(const char* LHSString, TypeID const* LHS,
	const char* RHSString, TypeID const* RHS)
{
	if (*LHS == *RHS)
	{
		return true;
	}
	std::printf("TypeID's not equal:\n");
	std::printf("%s: %s\n----------\n%s: %s\n",
		LHSString, LHS->name().c_str(),
		RHSString, RHS->name().c_str());
	return false;
}

#endif

}	// namespace bksge_variant_test

#endif // UNIT_TEST_FND_VARIANT_TYPE_ID_HPP
