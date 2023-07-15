set_languages("cxx20", {cflags = "-finput-charset=utf-8"})

add_rules("mode.debug", "mode.release")
target("test")
    set_kind("binary")
    add_files("/source/test.cpp")

    add_linkdirs("/lib")
    add_links("freetype")

    add_includedirs("/include/")
    add_includedirs("/freetype/include")

    -- 添加其他源文件
    add_files("/source/bitmap_font.cpp")
    add_files("/source/bitmap_font_maker.cpp")

target("maker")
    set_kind("binary")
    add_files("/source/maker.cpp")

    add_linkdirs("/lib")
    add_links("freetype")

    add_includedirs("/include/")
    add_includedirs("/freetype/include")

    -- 添加其他源文件
    add_files("/source/bitmap_font.cpp")
    add_files("/source/bitmap_font_maker.cpp")

target("parser")
    set_kind("binary")
    add_files("/source/parser.cpp")

    add_linkdirs("/lib")
    add_links("freetype")

    add_includedirs("/include/")
    add_includedirs("/freetype/include")

    -- 添加其他源文件
    add_files("/source/bitmap_font.cpp")
    add_files("/source/bitmap_font_maker.cpp")

