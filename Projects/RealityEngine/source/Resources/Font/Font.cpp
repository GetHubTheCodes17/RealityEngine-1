// Copyright Reality Engine. All Rights Reserved.

#include "Resources/Font/Font.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "Core/Tools/Logger.h"

reality::Font::Font(FontSettings settings) {
	FT_LibraryRec_* library{};
	if (FT_Init_FreeType(&library)) {
		RE_LOG_WARNING("Failed to initialize the Freetype Library");
		return;
	}
	const auto path{ settings.Path };

	FT_FaceRec_* Face{};
	if (FT_New_Face(library, path.c_str(), 0, &Face)) {
		RE_LOG_WARNING("Cannot load the Font %s", path.c_str());
		return;
	}
	FT_Set_Pixel_Sizes(Face, 0, settings.PixelSize);

	for (uint8 c{}; c < Characters.size(); ++c) {
		if (FT_Load_Char(Face, c, FT_LOAD_RENDER)) {
			RE_LOG_WARNING("Cannot load the Glyph %c", c);
			continue;
		}
		const auto width{ Face->glyph->bitmap.width }, height{ Face->glyph->bitmap.rows };
		Characters[c].Buffer = std::make_unique<uint8[]>(width * height);
		std::memcpy(Characters[c].Buffer.get(), Face->glyph->bitmap.buffer,(std::size_t)(width) * height);
		Characters[c].Size = { (float)width, (float)height };
		Characters[c].Bearing = { (float)Face->glyph->bitmap_left, (float)Face->glyph->bitmap_top };
		Characters[c].Advance = (unsigned)Face->glyph->advance.x;
	}
	FT_Done_FreeType(library);
}

bool reality::Font::IsExtensionSupported(std::string_view extension) {
	return extension == ".ttf" || extension == ".cff" || extension == ".woff" || extension == ".fnt";
}
