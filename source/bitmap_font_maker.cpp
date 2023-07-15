#include "bitmap_font_maker.h"

BitmapFontMaker::BitmapFontMaker(std::string in_font_path, int32_t pixel) {
    // 初始化库
    if (FT_Init_FreeType(&ft_library_))
        exit(1);
    // 创建face对象
    if (FT_New_Face(ft_library_, in_font_path.c_str(), 0, &ft_face_))
        exit(1);
    if (FT_Set_Pixel_Sizes(ft_face_, pixel, pixel))
        exit(1);
}

BitmapFontMaker::~BitmapFontMaker() {
    if (ft_face_)
        FT_Done_Face(ft_face_);
    if (ft_library_)
        FT_Done_FreeType(ft_library_);
}

BitmapFont BitmapFontMaker::get_unicode_bitmap(FT_BBox max_ft_bbox, uint16_t unicode) {
    int32_t max_bbox_height = max_ft_bbox.yMax - max_ft_bbox.yMin;
    int32_t max_bbox_width = max_ft_bbox.xMax - max_ft_bbox.xMin;

    if (FT_Load_Char(ft_face_, unicode, FT_LOAD_RENDER))
        exit(1);
    // 得到字模
    FT_Glyph glyph;
    // 把字形图像从字形槽复制到新的FT_Glyph对象glyph中。这个函数返回一个错误码并且设置glyph。
    if (FT_Get_Glyph(ft_face_->glyph, &glyph))
        exit(1);

    FT_BBox ft_bbox;
    FT_Glyph_Get_CBox(glyph, FT_GLYPH_BBOX_TRUNCATE, &ft_bbox);

    int32_t delta_x = ft_bbox.xMin - max_ft_bbox.xMin;   // 计算x的偏移量
    int32_t delta_y = max_ft_bbox.yMax - ft_bbox.yMax;   // 利用最大值计算y的偏移量
    // std::cout << delta_x << " " << delta_y << std::endl;
    BitmapFont bitmap = BitmapFont(max_bbox_height, max_bbox_width);
    bitmap.set_bitmap(ft_face_->glyph->bitmap, delta_x, delta_y);
    return bitmap;
}

std::vector<BitmapFont> BitmapFontMaker::get_all_unicode_bitmap() {
    std::vector<BitmapFont> ret_bitmap_ary = {};
    FT_BBox max_ft_bbox = get_max_ft_bbox();
    for (uint16_t unicode = 0; unicode < static_cast<uint16_t>(-1); unicode++) {
        // printf("%d\n", unicode);
        auto bitmap = get_unicode_bitmap(max_ft_bbox, unicode);
        ret_bitmap_ary.push_back(bitmap);
    }
    return ret_bitmap_ary;
}

FT_BBox BitmapFontMaker::get_max_ft_bbox() {
    FT_BBox max_ft_bbox;
    max_ft_bbox.xMax = INT_MIN;
    max_ft_bbox.yMax = INT_MIN;
    max_ft_bbox.xMin = INT_MAX;
    max_ft_bbox.yMin = INT_MAX;
    for (int32_t unicode = 1; unicode < (1 << 16); unicode++) {
        if (FT_Load_Char(ft_face_, unicode, FT_LOAD_RENDER)) {
            exit(1);
        }
        FT_Glyph glyph;
        if (FT_Get_Glyph(ft_face_->glyph, &glyph))
            exit(1);

        FT_BBox ft_bbox;
        FT_Glyph_Get_CBox(glyph, FT_GLYPH_BBOX_TRUNCATE, &ft_bbox);

        max_ft_bbox.xMax = std::max(max_ft_bbox.xMax, ft_bbox.xMax);
        max_ft_bbox.yMax = std::max(max_ft_bbox.yMax, ft_bbox.yMax);
        max_ft_bbox.xMin = std::min(max_ft_bbox.xMin, ft_bbox.xMin);
        max_ft_bbox.yMin = std::min(max_ft_bbox.yMin, ft_bbox.yMin);
    }
    return max_ft_bbox;
}
