#include "Controller.hpp"
#include <iostream>
#include "ImagePNG.hpp"
#include "ImageJPG.hpp"
#include "OutputPresentation.hpp"
#include "OutputFile.hpp"
#include "OutputImage.hpp"
#include <algorithm>
#include "FilterFlip.hpp"
#include "FilterRotate.hpp"

Controller::Controller(int argc, char *argv[])
    try : config(argc, argv) {
        config.parseCommandLine();

        std::cout << "----Controlleros----" << std::endl;
        run();
    }
    catch (std::exception &e) {
    }


void Controller::run() {
    if (!loadImages()){
        std::cout << "Controller: Error while loading images" << std::endl;
        return;
    }
//    applyFilters();
    convertToAscii();
    outputImages();
}


bool Controller::loadImages() {
    for (auto &img : config.getImages()){
        if (img.image_path.find(".png") != std::string::npos){
            images.emplace_back(std::make_unique<ImagePNG>(), img);
        }
        else if (img.image_path.find(".jpg") != std::string::npos){
            images.emplace_back(std::make_unique<ImageJPG>(), img);
        }
        else {
            std::cout << "Controller: Error while loading images" << std::endl;
            return false;
        }
        images.back().first->load(img.image_path, img.invert);
        std::cout << "loaded: " << img.image_path << std::endl;
    }
    return true;
}

void Controller::applyFilters() {
    std::vector<Filter*> filters;
    for (auto &image : images) {

        if (image.second.rotate) {
            filters.push_back(new FilterRotate());
        }

        if (image.second.flip_horizontal || image.second.flip_vertical) {
            filters.push_back(new FilterFlip());
        }

        for (Filter* filter : filters) {
            filter->apply(image);
        }

        for (Filter* filter : filters) {
            delete filter;
        }
        filters.clear();
    }
}


void Controller::convertToAscii() {
    for (auto &image : images){
        if (image.second.charset.empty()){
            image.second.charset = " .'`^,:;Il!i><~+_-?][}{1)(|/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";
            std::cout << "No charset specified, using default: \"" << image.second.charset << "\""<< std::endl;
        }
        image.first->imgToAscii(image.second.scale, image.second.charset, image.second.brightness);
    }
}


void Controller::outputImages() {
    std::string out = config.getOutputType();
    std::unique_ptr<Output> output;

    if (out == "screen") {
        output = std::make_unique<OutputPresentation>();
    }
    else if (out == "file") {
        output = std::make_unique<OutputFile>();
    }
    else if (out == "console"){
        for (auto &image : images) {
            std::cout << image.first->ascii_image << std::endl;
        }
    }
    else if (out == "image"){
        output = std::make_unique<OutputImage>();
    }
    else {
        std::cout << "Controller: Error while outputting images, output type not found." << std::endl;
        return;
    }


    if (output) {
        bool o = output->output(images, config.getOutputPath());
        if (!o) {
            std::cout << "Controller: Error while outputting images" << std::endl;
            return;
        }
    }
}