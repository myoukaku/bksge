/**
 *	@file	serialize_test.hpp
 *
 *	@brief	
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_SERIALIZE_TEST_HPP
#define UNIT_TEST_SERIALIZE_TEST_HPP

#include <bksge/fnd/serialization/text_oarchive.hpp>
#include <bksge/fnd/serialization/text_iarchive.hpp>
//#include <bksge/fnd/serialization/xml_oarchive.hpp>
//#include <bksge/fnd/serialization/xml_iarchive.hpp>
//#include <bksge/fnd/serialization/binary_oarchive.hpp>
//#include <bksge/fnd/serialization/binary_iarchive.hpp>

namespace
{

template <typename OArchive, typename IArchive, typename Stream, typename T>
void SerializeTest(T const& value)
{
	Stream s;
	{
		OArchive oa(s);
		oa << BKSGE_SERIALIZATION_NVP(value);
	}
	{
		T tmp;
		IArchive ia(s);
		ia >> BKSGE_SERIALIZATION_NVP(tmp);

		EXPECT_EQ(value, tmp);
	}
}

}	// namespace

#endif // UNIT_TEST_SERIALIZE_TEST_HPP
