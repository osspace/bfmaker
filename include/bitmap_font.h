#ifndef _BFMAKER_SOURCE_BITMAP_FONT_H
#define _BFMAKER_SOURCE_BITMAP_FONT_H

#include <fstream>
#include <vector>
#include <ft2build.h>
#include <freetype/freetype.h>

class BitmapFont {
public:
    BitmapFont() = default;
    BitmapFont(int32_t height, int32_t width);
    ~BitmapFont();

public:
    void set(size_t i, size_t j);
    void set_bitmap(const FT_Bitmap& ft_bitmap, int delta_x, int delta_y);

    bool value(size_t i, size_t j) const;

    std::vector<uint8_t> bitmap();

    void show() const;

public:
    int32_t bbox_height_;
    int32_t bbox_width_;
    int32_t height_;
    int32_t width_;
    int32_t offset_x_;
    int32_t offset_y_;
    std::vector<uint8_t> bitmap_;
};

#endif   // end of _BFMAKER_SOURCE_BITMAP_FONT_H
