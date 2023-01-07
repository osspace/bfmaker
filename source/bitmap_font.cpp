#include "bitmap_font.h"
#include <iostream>

BitmapFont::BitmapFont(size_t row, size_t col) {
    row_ = row;
    col_ = col;
    size_t count = row * col;
    bitmap_.resize((count + 7) / 8, 0);
}

BitmapFont::BitmapFont(const FT_Bitmap& ft_bitmap) {
    FT_Int rows = ft_bitmap.rows;
    FT_Int cols = ft_bitmap.width;
    *this = BitmapFont(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (ft_bitmap.buffer[i * cols + j])
                set(i, j);
        }
    }
}

BitmapFont::~BitmapFont() {}

size_t BitmapFont::row() const {
    return row_;
}

size_t BitmapFont::col() const {
    return col_;
}

size_t BitmapFont::byte_size() const {
    return bitmap_.size();
}

void BitmapFont::set(size_t i, size_t j) {
    size_t pos = i * col_ + j;
    size_t base = pos / 8;
    size_t offset = pos % 8;
    bitmap_[base] |= (1 << offset);
}

void BitmapFont::set_bitmap(uint8_t* byte_stream) {
    for (int i = 0; i < bitmap_.size(); i++) {
        bitmap_[i] = byte_stream[i];
    }
}

bool BitmapFont::value(size_t i, size_t j) const {
    size_t pos = i * col_ + j;
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
    std::cout << (int)this->delta_x << " " << (int)this->delta_y << std::endl;
    for (size_t i = 0; i < row_; i++) {
        for (size_t j = 0; j < col_; j++) {
            putchar(value(i, j) == false ? ' ' : '*');
        }
        putchar('\n');
    }
}
