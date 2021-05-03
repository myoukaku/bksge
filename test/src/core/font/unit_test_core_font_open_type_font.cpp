/**
 *	@file	unit_test_core_font_open_type_font.cpp
 *
 *	@brief	OpenTypeFont のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/core/font/open_type_font.hpp>
#include <gtest/gtest.h>

#include <fstream>
#include <vector>
#include <cstdint>
#include <cstddef>

GTEST_TEST(FontTest, OpenTypeFontTest)
{
	const char* file_name = "NotoSansCJKjp-Regular.otf";
	std::ifstream ifs(file_name, std::ios::binary | std::ios::ate);

	std::size_t const size = ifs.tellg();
	ifs.seekg(0);

	std::vector<std::uint8_t> buf(size);
	ifs.read((char*)buf.data(), size);

	bksge::OpenTypeFont font(buf.data(), buf.size());
}
