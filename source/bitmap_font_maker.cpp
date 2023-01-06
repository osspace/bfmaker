#include "bitmap_font_maker.h"

BitmapFontMaker::BitmapFontMaker(std::string font_input_path, int32_t pixel) {
    // 初始化库
    error_ = FT_Init_FreeType(&library_);
    if (error_)
        return;
    // 创建face对象
    error_ = FT_New_Face(library_, font_input_path.c_str(), 0, &face_);
    if (error_)
        return;
    // 设置字体像素
    error_ = FT_Set_Char_Size(face_, FT_F26Dot6(pixel << 6), FT_F26Dot6(pixel << 6), 72, 72);
    if (error_)
        return;
    slot_ = face_->glyph;
}

BitmapFontMaker::~BitmapFontMaker() {
    if (face_)
        FT_Done_Face(face_);
    if (library_)
        FT_Done_FreeType(library_);
}

BitmapFont BitmapFontMaker::BitmapFontMaker::draw_bitmap(FT_Bitmap* bitmap) {
    FT_Int rows = bitmap->rows;
    FT_Int cols = bitmap->width;
    BitmapFont ret_bitmap(rows, cols);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (bitmap->buffer[i * cols + j])
                ret_bitmap.set(i, j);
        }
    }
    return ret_bitmap;
}

BitmapFont BitmapFontMaker::get_unicode_bitmap(uint16_t unicode) {
    error_ = FT_Load_Char(face_, unicode, FT_LOAD_RENDER);
    if (error_)
        return {};

    auto bitmap = draw_bitmap(&slot_->bitmap);
    return bitmap;
}

std::vector<BitmapFont> BitmapFontMaker::get_all_unicode_bitmap() {
    std::vector<BitmapFont> ret_bitmap_ary = {};
    for (uint16_t unicode = 0; unicode < static_cast<uint16_t>(-1); unicode++) {
        auto&& bitmap = get_unicode_bitmap(unicode);
        ret_bitmap_ary.push_back(bitmap);
    }
    return ret_bitmap_ary;
}
