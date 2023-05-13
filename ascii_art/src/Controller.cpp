#include "Controller.hpp"
#include <iostream>
#include "ImagePNG.hpp"
#include "ImageJPG.hpp"
#include "OutputPresentation.hpp"
#include "OutputFile.hpp"
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
    if (!convertToAscii()) {
        std::cout << "Controller: Error while converting to ascii" << std::endl;
        return;
    }
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
    std::cout << "applying filters" << std::endl;
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


bool Controller::convertToAscii() {
    std::cout << "converting to ascii" << std::endl;
    for (auto &image : images){
        if (image.second.charset.empty()){
            std::cout << "Controller: Error while converting to ascii, charset not found." << std::endl;
            return false;
        }
        image.first->imgToAscii(image.second.scale, image.second.charset, image.second.brightness);
    }
    return true;
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
    else {
        std::cout << "Controller: Error while outputting images, output type not found." << std::endl;
        return;
    }


    if (output) {
        output->output(images, config.getOutputPath());
    }
}