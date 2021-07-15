/**
 *	@file	sample_open_type_font_main.cpp
 *
 *	@brief	OpenTypeFont のサンプル
 *
 *	@author	myoukaku
 */

#include <bksge/core/font/open_type_font.hpp>
#include <bksge/fnd/vector.hpp>
#include <fstream>
#include <iostream>
#include <cstddef>
#include <cstdint>

int main()
{
	const char* file_name = "NotoSansCJKjp-Black.otf";
//	const char* file_name = "NotoSansCJKjp-Bold.otf";
//	const char* file_name = "NotoSansCJKjp-Regular.otf";
//	const char* file_name = "font.ttf";
	std::ifstream ifs(file_name, std::ios::binary | std::ios::ate);

	auto const size = static_cast<std::size_t>(ifs.tellg());
	ifs.seekg(0);

	bksge::vector<std::uint8_t> buf(size);
	ifs.read((char*)buf.data(), size);

	bksge::OpenTypeFont font(buf.data(), buf.size());

	for (std::uint32_t i = 0; i <= 0xFFFF; ++i)
	{
		std::cout << font.GetGlyphIndex(i) << std::endl;
	}

	return 0;
}
