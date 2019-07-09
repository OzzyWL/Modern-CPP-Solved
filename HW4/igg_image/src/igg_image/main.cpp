#include "io_strategies/dummy_strategy.h"
#include "io_strategies/png_strategy.h"
#include "io_strategies/ppm_strategy.h"
#include <typeinfo>

#include "image.h"

using namespace igg;

int main(){

// set pointer to wanted strategy
auto ppm_strategy_ptr = std::shared_ptr <PpmIoStrategy> (new PpmIoStrategy());

Image image_ppm;
image_ppm.SetIoStrategy(ppm_strategy_ptr);
ImageData imageData;

image_ppm.ReadFromDisk("../data/pbmlib.ascii.ppm");

const Image& image_ppm_ref = image_ppm;
const int row = 150;
const int col = 75;
Image::Pixel pix = image_ppm_ref.at(row,col);

std::cout <<"Wanted Pixel BEFORE modification contains: "<< std::endl; 
std::cout << "Red: " << pix.red <<  " Green: " << pix.green << " Blue: " <<  pix.blue << std::endl;

image_ppm.at(row,col) = {255, 255, 255};
// image_ppm.at(row,col).red = 222;

Image::Pixel pix2 = image_ppm_ref.at(row,col);

std::cout << "Wanted Pixel AFTER modification contains: " << std::endl;
std::cout << "Red: " << pix2.red <<  " Green: " << pix2.green << " Blue: " <<  pix2.blue << std::endl;

image_ppm.WriteToDisk("../data/ppm_file_WRITTEN.ppm", imageData);
//------------------------------
std::cout << "------Scaling------" << std::endl;
// DownScale only works with divisors of image cols and rows size
image_ppm.DownScale(2);
image_ppm.WriteToDisk("../data/ppm_file_DOWN_scaled.ppm", imageData);

image_ppm.UpScale(4);
image_ppm.WriteToDisk("../data/ppm_file_UP_scaled.ppm", imageData);

// //------------------------------
// PPM CHECK//

// Note: 
// if I call strategy through constructor 
// I will overwrite data in Image class!!!

// PNG CHECK//
// set pointer to wanted strategy
auto png_strategy_ptr = std::shared_ptr <PngIoStrategy> (new PngIoStrategy());
//std::cout << png_strategy_ptr.use_count() << std::endl;

Image image_png(300, 300);
image_png.SetIoStrategy(png_strategy_ptr);
ImageData imageData_png;

image_png.ReadFromDisk("../data/santa.png");

const Image& image_png_ref = image_png;
const int row_png = 150;
const int col_png = 75;
Image::Pixel pix_png = image_png_ref.at(row_png,col_png);

std::cout <<"Wanted Pixel BEFORE modification contains: "<< std::endl; 
std::cout << "Red: " << pix_png.red <<  " Green: " << pix_png.green << " Blue: " <<  pix_png.blue << std::endl;

image_png.at(row_png,col_png) = {255, 255, 255};
// image_png.at(row,col).red = 222;

Image::Pixel pix_png2 = image_png_ref.at(row_png,col_png);

std::cout << "Wanted Pixel AFTER modification contains: " << std::endl;
std::cout << "Red: " << pix_png2.red <<  " Green: " << pix_png2.green << " Blue: " <<  pix_png2.blue << std::endl;


image_png.WriteToDisk("../data/santa_WRITTEN.png", imageData_png);
// PNG CHECK//

//------------------------------
std::cout << "------Scaling------" << std::endl;
// DownScale only works with divisors of image cols and rows size
image_png.DownScale(2);
image_png.WriteToDisk("../data/santa_DOWN_scaled.png", imageData_png);

image_png.UpScale(4);
image_png.WriteToDisk("../data/santa_UP_scaled.png", imageData_png);

// //------------------------------

return 0;
}
