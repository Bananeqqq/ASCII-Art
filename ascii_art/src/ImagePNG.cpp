#include "ImagePNG.hpp"
#include "png.h"


bool ImagePNG::load(const std::string& filename) {

    FILE *file = fopen(filename.c_str(), "rb");
    if (!file) {
        return false;
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png) {
        fclose(file);
        return false;
    }

    png_infop info = png_create_info_struct(png);
    if (!info) {
        png_destroy_read_struct(&png, nullptr, nullptr);
        fclose(file);
        return false;
    }

    if (setjmp(png_jmpbuf(png))) { //Error handling
        png_destroy_read_struct(&png, &info, nullptr);
        fclose(file);
        return false;
    }

    png_init_io(png, file);
    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);

    int color_type = png_get_color_type(png, info);

    switch(color_type){
        case PNG_COLOR_TYPE_RGB: //RGB -> RGBA
            png_set_add_alpha(png, 0xFF, PNG_FILLER_AFTER);
            break;
        case PNG_COLOR_TYPE_GRAY:
        case PNG_COLOR_TYPE_GRAY_ALPHA: //Gray -> RGBA
            if (png_get_bit_depth(png, info) < 8 && color_type == PNG_COLOR_TYPE_GRAY)
                png_set_expand_gray_1_2_4_to_8(png);
            png_set_gray_to_rgb(png);
            png_set_add_alpha(png, 0xFF, PNG_FILLER_AFTER);
            break;
        case PNG_COLOR_TYPE_PALETTE: //Palette -> RGBA
            png_set_palette_to_rgb(png);
            break;
        default:
            break;
    }

    if (png_get_valid(png, info, PNG_INFO_tRNS)) {  //tRNS -> RGBA
        png_set_tRNS_to_alpha(png);
    }

    png_read_update_info(png, info);

    std::vector<png_bytep> row_pointers(height);
    std::vector<png_byte> row(height * width * 4);
    for (unsigned int i = 0; i < height; ++i) {
        row_pointers[i] = &row[i * width * 4];
    }

    png_read_image(png, row_pointers.data());
    data.assign(row.begin(), row.end());

    png_destroy_read_struct(&png, &info, nullptr);
    fclose(file);

    return true;
}
