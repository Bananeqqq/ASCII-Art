#ifndef ASCII_ART_IMAGE_HPP
#define ASCII_ART_IMAGE_HPP

#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/**
 * @brief "Abstract" base class for different image types (png, jpg, ...)
 *
 * @details This class is used to load the image from the given path, convert it to ascii and optionally create a texture from it.
 * Derived classes are ImagePNG and ImageJPG and they must implement the load method.
 */
class Image {
public:
    Image(unsigned int width, unsigned int height) : width(width), height(height) {
        ascii_image = "";
    }
    virtual ~Image() = default;

    /**
     * @brief Pure virtual method for loading the image from given path and saving the pixels to the data vector
     * @param filename The path to the image
     * @param inverted Whether to invert the image or not
     * @return true if the image was loaded successfully
     */
    virtual bool load(const std::string& filename, bool inverted) = 0;

    /**
     * @brief Convert the image to ascii and save it to the ascii_image string
     * @param scaleFactor The scale factor to apply to the image
     * @param charset The charset (density) to use for the ascii image
     * @param brightness The brightness to apply to the image
     */
    void imgToAscii(const double scaleFactor, const std::string charset, double brightness);


    /**
     * @brief Create a texture from the ascii image which can be rendered to the screen or saved to a png file
     * @param renderer Pointer to the SDL_Renderer object which will be used to create the SDL_Texture
     * @param font Pointer to the TTF_Font object used for rendering text to the texture
     * @param font_size Size of the font used for rendering text to the texture
     * @param scale The scaling factor to apply to the texture
     * @return SDL_Texture* Newly created SDL_Texture object from the ascii string
     */
    SDL_Texture* createTexture(SDL_Renderer* renderer, TTF_Font* font, int font_size, double scale) const;

    unsigned int width;
    unsigned int height;

    /**
     * @brief The data of the image (pixels)
     */
    std::vector<unsigned char> data;

    /**
     * @brief The ascii image stored as a string
     */
    std::string ascii_image;
};


#endif //ASCII_ART_IMAGE_HPP
