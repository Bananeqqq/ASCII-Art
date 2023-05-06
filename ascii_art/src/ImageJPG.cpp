#include "ImageJPG.hpp"
#include <jpeglib.h>


bool ImageJPG::load(const std::string& filename) {

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
    jpeg_start_decompress(&cinfo);

    width = cinfo.output_width;
    height = cinfo.output_height;
    data.resize(width * height * num_channels);

    std::vector<unsigned char> row(width * num_channels);
    while(cinfo.output_scanline < cinfo.output_height) {
        unsigned char *rowptr = row.data();
        jpeg_read_scanlines(&cinfo, &rowptr, 1);

        std::copy(row.begin(), row.end(), data.begin() + cinfo.output_scanline * width * num_channels - row.size());
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(file);

    return true;
}