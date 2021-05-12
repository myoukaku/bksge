/**
 *	@file	sample_open_type_font_main.cpp
 *
 *	@brief	OpenTypeFont のサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/font/open_type_font.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <fstream>
#include <iostream>

int main()
{
	const char* file_name = "NotoSansCJKjp-Black.otf";
//	const char* file_name = "NotoSansCJKjp-Bold.otf";
//	const char* file_name = "NotoSansCJKjp-Regular.otf";
//	const char* file_name = "font.ttf";
	std::ifstream ifs(file_name, std::ios::binary | std::ios::ate);

	bksge::size_t const size = ifs.tellg();
	ifs.seekg(0);

	bksge::vector<bksge::uint8_t> buf(size);
	ifs.read((char*)buf.data(), size);

	bksge::OpenTypeFont font(buf.data(), buf.size());

	for (bksge::uint32_t i = 0; i <= 0xFFFF; ++i)
	{
		std::cout << font.GetGlyphIndex(i) << std::endl;
	}

	return 0;
}
