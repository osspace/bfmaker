#include "bitmap_font.h"
#include <iostream>

BitmapFont::BitmapFont(int32_t row, int32_t col) {
    bbox_height_ = row;
    bbox_width_ = col;
    bitmap_.resize((row * col + 7) / 8, 0);
}

BitmapFont::~BitmapFont() {}

void BitmapFont::set(size_t i, size_t j) {
    size_t pos = i * bbox_width_ + j;
    size_t base = pos / 8;
    size_t offset = pos % 8;
    bitmap_[base] |= (1 << offset);
}

void BitmapFont::set_bitmap(const FT_Bitmap& ft_bitmap, int delta_x, int delta_y) {
    int rows = ft_bitmap.rows;
    int cols = ft_bitmap.width;

    width_ = cols;
    height_ = rows;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (ft_bitmap.buffer[i * cols + j]) {
                set(i + delta_y, j + delta_x);
            }
        }
    }
}

bool BitmapFont::value(size_t i, size_t j) const {
    size_t pos = i * bbox_width_ + j;
    size_t base = pos / 8;
    size_t offset = pos % 8;
    return bitmap_[base] & (1 << offset);
}

std::vector<uint8_t> BitmapFont::bitmap() {
    return bitmap_;
}

void BitmapFont::show() const {
    for (size_t i = 0; i < bbox_height_; i++) {
        for (size_t j = 0; j < bbox_width_; j++) {
            putchar(value(i, j) == false ? '0' : '*');
        }
        putchar('\n');
    }
}
