#include "ImageJPG.hpp"
#include <jpeglib.h>


bool ImageJPG::load(const std::string& filename, bool inverted) {

    FILE *file = fopen(filename.c_str(), "rb");
    if (!file) {
        return false;
    }

    jpeg_decompress_struct cinfo;
    jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, file);

    if (jpeg_read_header(&cinfo, TRUE) != JPEG_HEADER_OK) {
        fclose(file);
        return false;
    }

    cinfo.out_color_space = JCS_GRAYSCALE;
    jpeg_start_decompress(&cinfo);


    width = cinfo.output_width;
    height = cinfo.output_height;

    data.resize(width * height);
    while(cinfo.output_scanline < cinfo.output_height) {
        unsigned char* buffer[1];
        buffer[0] = data.data() + cinfo.output_scanline * width;

        jpeg_read_scanlines(&cinfo, buffer, 1);
        if(inverted) {
            for(unsigned int i = 0; i < width; ++i) {
                buffer[0][i] = 255 - buffer[0][i];
            }
        }
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(file);

    return true;
}