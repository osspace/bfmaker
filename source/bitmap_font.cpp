#include "bitmap_font.h"
#include <iostream>

BitmapFont::BitmapFont(int32_t pixel) {
    pixel_ = pixel;
    bitmap_.resize((pixel * pixel + 7) / 8, 0);
}

BitmapFont::~BitmapFont() {}

void BitmapFont::set(size_t i, size_t j) {
    size_t pos = i * pixel_ + j;
    size_t base = pos / 8;
    size_t offset = pos % 8;
    bitmap_[base] |= (1 << offset);
}

void BitmapFont::set_bitmap(const FT_Bitmap& ft_bitmap, int delta_x, int delta_y) {
    int rows = ft_bitmap.rows;
    int cols = ft_bitmap.width;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (ft_bitmap.buffer[i * cols + j]) {
                set(i + delta_y, j + delta_x);
            }
        }
    }
}

bool BitmapFont::value(size_t i, size_t j) const {
    size_t pos = i * pixel_ + j;
    size_t base = pos / 8;
    size_t offset = pos % 8;
    return bitmap_[base] & (1 << offset);
}

std::vector<uint8_t> BitmapFont::bitmap() {
    return bitmap_;
}

std::ifstream& operator>>(std::ifstream& in_fstream, BitmapFont& font_bitmap) {
    for (auto& val : font_bitmap.bitmap_) {
        in_fstream >> val;
    }

    return in_fstream;
}

std::ofstream& operator<<(std::ofstream& out_fstream, const BitmapFont& font_bitmap) {
    for (const auto& val : font_bitmap.bitmap_) {
        out_fstream << val;
    }
    return out_fstream;
}

void BitmapFont::show() const {
    for (size_t i = 0; i < pixel_; i++) {
        for (size_t j = 0; j < pixel_; j++) {
            putchar(value(i, j) == false ? '0' : '*');
        }
        putchar('\n');
    }
}
