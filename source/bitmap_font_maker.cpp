#include "bitmap_font_maker.h"

std::unordered_map<int32_t, int32_t> BitmapFontMaker::pixel_to_max_bearing_y = {};

BitmapFontMaker::BitmapFontMaker(std::string font_input_path) {
    // 初始化库
    if (FT_Init_FreeType(&library_))
        exit(1);
    // 创建face对象
    if (FT_New_Face(library_, font_input_path.c_str(), 0, &face_))
        exit(1);
}

BitmapFontMaker::~BitmapFontMaker() {
    if (face_)
        FT_Done_Face(face_);
    if (library_)
        FT_Done_FreeType(library_);
}

static std::unordered_map<int32_t, int32_t> pixel_to_max_bearing_y;

BitmapFont BitmapFontMaker::get_unicode_bitmap(uint16_t unicode, int32_t pixel) {
    if (!pixel_to_max_bearing_y.count(pixel))
        pixel_to_max_bearing_y[pixel] = get_max_bearing_y(pixel);
    int32_t max_bearing_y = pixel_to_max_bearing_y[pixel];

    if (FT_Set_Char_Size(face_, FT_F26Dot6(pixel << 6), FT_F26Dot6(pixel << 6), 72, 72))
        exit(1);
    slot_ = face_->glyph;
    if (FT_Load_Char(face_, unicode, FT_LOAD_RENDER))
        exit(1);

    BitmapFont bitmap = BitmapFont(face_->glyph->bitmap);
    bitmap.delta_x = face_->glyph->bitmap_left;                      // 计算x的偏移量
    bitmap.delta_y = max_bearing_y - face_->glyph->bitmap_top - 1;   // 利用最大值计算y的偏移量
    return bitmap;
}

int32_t BitmapFontMaker::get_max_bearing_y(int32_t pixel) {
    int32_t max_bearing_y = 0;
    for (uint16_t unicode = 0; unicode < static_cast<uint16_t>(-1); unicode++) {
        if (FT_Set_Pixel_Sizes(face_, pixel, pixel))
            exit(1);

        if (FT_Load_Char(face_, unicode, FT_LOAD_RENDER))
            exit(1);

        max_bearing_y = std::max(max_bearing_y, face_->glyph->bitmap_top);
    }
    return max_bearing_y;
}

std::vector<BitmapFont> BitmapFontMaker::get_all_unicode_bitmap(int32_t pixel) {
    std::vector<BitmapFont> ret_bitmap_ary = {};
    for (uint16_t unicode = 0; unicode < static_cast<uint16_t>(-1); unicode++) {
        auto bitmap = get_unicode_bitmap(unicode, pixel);
        ret_bitmap_ary.push_back(bitmap);
    }
    return ret_bitmap_ary;
}
