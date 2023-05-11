#include "Controller.hpp"
#include <iostream>
#include "ImagePNG.hpp"
#include "ImageJPG.hpp"
#include "OutputPresentation.hpp"
#include "OutputFile.hpp"
#include <algorithm>
#include "FilterFlip.hpp"
#include "FilterRotate.hpp"

Controller::Controller(int argc, char *argv[]) : config(argc, argv){
    if (!config.parseCommandLine()){
        std::cout << "Controller: Error while parsing" << std::endl;
        return;
    }
    std::cout << "----Controlleros----" << std::endl;

    run();
}

void Controller::run() {
    loadImages();
    applyFilters();
    convertToAscii();
    outputImages();
}


void Controller::loadImages() {
    for (auto &img : config.getImages()){
        if (img.image_path.find(".png") != std::string::npos){
            images.emplace_back(std::make_unique<ImagePNG>(), img);
        }
        else if (img.image_path.find(".jpg") != std::string::npos){
            images.emplace_back(std::make_unique<ImageJPG>(), img);
        }
        else {
            std::cout << "Controller: Error while loading images" << std::endl;
            return;
        }
        std::cout << "loading: " << img.image_path << std::endl;
        images.back().first->load(img.image_path);
    }
}

void Controller::applyFilters() {
    std::cout << "applying filters" << std::endl;
    std::vector<Filter*> filters;

}


void Controller::convertToAscii() {
    for (auto &image : images){
        image.first->imgToAscii(image.second.scale, image.second.charset, image.second.brightness);
    }
}


void Controller::outputImages() {
    std::cout << "output" << std::endl;
    std::string out = config.getOutputType();
    std::unique_ptr<Output> output;

    if (out == "screen"){
        output = std::make_unique<OutputPresentation>();
    }
    else if (out == "file"){
        output = std::make_unique<OutputFile>();
    }
    else {
        for (auto &image : images){
            std::cout << image.first->ascii_image << std::endl;
        }
    }

    output->output(images, config.getOutputPath());
}