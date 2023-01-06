#ifndef _BFMAKER_SOURCE_BITMAP_FONT_H
#define _BFMAKER_SOURCE_BITMAP_FONT_H

#include <fstream>
#include <vector>

class BitmapFont {
public:
    BitmapFont() = default;
    BitmapFont(size_t row, size_t col);
    ~BitmapFont();

public:
    size_t row() const;
    size_t col() const;
    size_t byte_size() const;

    void set(size_t i, size_t j);
    void set_bitmap(uint8_t* byte_stream);
    bool value(size_t i, size_t j) const;

    std::vector<uint8_t> bitmap();

    friend std::ifstream& operator>>(std::ifstream& in_fstream, BitmapFont& font_bitmap);
    friend std::ofstream& operator<<(std::ofstream& out_fstream, const BitmapFont& font_bitmap);

    void show() const;

private:
    size_t row_;
    size_t col_;
    std::vector<uint8_t> bitmap_;
};

#endif   // end of _BFMAKER_SOURCE_BITMAP_FONT_H
