#include "ImageJPG.hpp"
#include <jpeglib.h>
#include <iostream>
#include <setjmp.h>

/**
 * @brief Structure for custom error handling in libjpeg
 *
 * This struct is used to override the default error handling behaviour of libjpeg.
 * It contains an instance of `jmp_buf` which is used to return control to a set point in the case of an error.
 *
 * @note this error handling was inspired by https://github.com/LuaDist/libjpeg/blob/master/example.c
 * and https://stackoverflow.com/questions/19857766/error-handling-in-libjpeg
 */
struct my_error_mgr {
    jpeg_error_mgr pub;
    jmp_buf setjmp_buffer;
};


/**
 * @brief Custom error handler for libjpeg
 *
 * This function overrides the default error handling behaviour of libjpeg.
 * In case of an error, it outputs an error message and performs a long jump
 * to the point in the code specified by the setjmp_buffer in the my_error_mgr
 * instance associated with `cinfo`.
 *
 * @param cinfo A pointer to a common libjpeg object. Its `err` field is expected
 * to point to a `my_error_mgr` instance.
 *
 * @note this error handling was inspired by https://github.com/LuaDist/libjpeg/blob/master/example.c
 * and https://stackoverflow.com/questions/19857766/error-handling-in-libjpeg
 */
void err_exit(j_common_ptr cinfo) {
    my_error_mgr* myerr = (my_error_mgr*) cinfo->err;
    (*cinfo->err->output_message) (cinfo);
    longjmp(myerr->setjmp_buffer, 1);
}


bool ImageJPG::load(const std::string &filename, bool inverted)
{

    FILE *file = fopen(filename.c_str(), "rb");
    if (!file)
    {
        return false;
    }

    jpeg_decompress_struct cinfo;
    my_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr.pub);
    jerr.pub.error_exit = err_exit;

    if (setjmp(jerr.setjmp_buffer))
    {
        jpeg_destroy_decompress(&cinfo);
        fclose(file);
        return false;
    }

    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, file);

    if (jpeg_read_header(&cinfo, TRUE) != JPEG_HEADER_OK)
    {
        jpeg_destroy_decompress(&cinfo);
        fclose(file);
        return false;
    }

    cinfo.out_color_space = JCS_GRAYSCALE;
    jpeg_start_decompress(&cinfo);

    width = cinfo.output_width;
    height = cinfo.output_height;

    data.resize(width * height);
    while (cinfo.output_scanline < cinfo.output_height)
    {
        unsigned char *buffer[1];
        buffer[0] = data.data() + cinfo.output_scanline * width;

        jpeg_read_scanlines(&cinfo, buffer, 1);
        if (inverted)
        {
            for (unsigned int i = 0; i < width; ++i)
            {
                buffer[0][i] = 255 - buffer[0][i];
            }
        }
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(file);

    return true;
}