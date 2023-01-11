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

    if (FT_Set_Pixel_Sizes(face_, pixel, pixel))
        exit(1);
    if (FT_Load_Char(face_, unicode,
                     /*FT_LOAD_RENDER|*/ FT_LOAD_FORCE_AUTOHINT |
                         (true ? FT_LOAD_TARGET_NORMAL : FT_LOAD_MONOCHROME | FT_LOAD_TARGET_MONO))) {
        exit(1);
    }
    // 得到字模
    FT_Glyph glyph;
    // 把字形图像从字形槽复制到新的FT_Glyph对象glyph中。这个函数返回一个错误码并且设置glyph。
    if (FT_Get_Glyph(face_->glyph, &glyph))
        exit(1);

    FT_BBox bbox;
    FT_Glyph_Get_CBox(glyph, FT_GLYPH_BBOX_TRUNCATE, &bbox);

    int32_t height = face_->glyph->bitmap.rows;
    int32_t width = face_->glyph->bitmap.width;
    int32_t box_height = bbox.yMax - bbox.yMin + 1;
    // if (height > pixel || bbox.yMin >= 0 || width > pixel || box_height > pixel) {
    //     return BitmapFont(pixel);
    // }

    int32_t delta_x = face_->glyph->bitmap_left;   // 计算x的偏移量
    int32_t delta_y = max_bearing_y - bbox.yMax;   // 利用最大值计算y的偏移量
    std::cout << delta_x << " " << delta_y << std::endl;
    std::cout << max_bearing_y << std::endl;
    std::cout << height << " " << width << std::endl;
    BitmapFont bitmap = BitmapFont(pixel);
    bitmap.set_bitmap(face_->glyph->bitmap, delta_x, delta_y);

    std::cout << 1 << std::endl;
    return bitmap;
}

int32_t BitmapFontMaker::get_max_bearing_y(int32_t pixel) {
    int32_t max_bearing_y = 0;
    for (uint16_t unicode = 0; unicode < static_cast<uint16_t>(-1); unicode++) {
        if (FT_Set_Pixel_Sizes(face_, pixel, pixel))
            exit(1);
        if (FT_Load_Char(face_, unicode,
                         /*FT_LOAD_RENDER|*/ FT_LOAD_FORCE_AUTOHINT |
                             (true ? FT_LOAD_TARGET_NORMAL : FT_LOAD_MONOCHROME | FT_LOAD_TARGET_MONO))) {
            exit(1);
        }
        // 得到字模
        FT_Glyph glyph;
        // 把字形图像从字形槽复制到新的FT_Glyph对象glyph中。这个函数返回一个错误码并且设置glyph。
        if (FT_Get_Glyph(face_->glyph, &glyph))
            exit(1);
        FT_BBox bbox;
        FT_Glyph_Get_CBox(glyph, FT_GLYPH_BBOX_TRUNCATE, &bbox);

        int32_t height = face_->glyph->bitmap.rows;
        int32_t width = face_->glyph->bitmap.width;
        int32_t box_height = bbox.yMax - bbox.yMin + 1;
        // if (height > pixel || bbox.yMin >= 0 || width > pixel || box_height > pixel)
        //     continue;
        max_bearing_y = std::max(max_bearing_y, (int)face_->glyph->bitmap.rows);
        if (max_bearing_y == 18) {
            std::cout << bbox.yMax << " " << bbox.yMin << std::endl;
            exit(0);
        }
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
