#include "image.h"
#include <iostream>
#include <typeinfo>
#include <math.h>

namespace igg {


void Image::Image::SetIoStrategy(const std::shared_ptr<IoStrategy>& strategy_ptr) {
std::cout << "Method SetIoStrategy called" << std::endl;
// Make your program exit with code 1 when calling any of 
// the above functions ReadFromDisk and Write-
// ToDisk while the strategy is not set.
if(!strategy_ptr) {
// only enters if some_ptr == nullptr
std::cout << "Please first set wanted strategy exit(1)" << std::endl;
exit(1);
}
// can copy shared pointer
Image::strategy_ptr_ = strategy_ptr;
//std::cout << strategy_ptr.use_count() << std::endl;

}

Image::Image(const int rows, const int cols): rows_{rows}, cols_{cols}{

std::cout << "constructor 2 inputs called" << std::endl;
std::cout << "rows: " << rows  << " and cols: "<< cols << std::endl;
}

Image::Image() {
std::cout << "constructor 0 input called" << std::endl;
}

Image::Pixel& Image::at(const int row, const int col)  {
// std::cout << "*at* function called" << std::endl;

return data_[(cols_ * row) + col];
}

Image::Pixel Image::at(const int row, const int col) const{

// std::cout << "CONST *at* function called" << std::endl;

// REMEMBER: data_ is a vector of Pixel objects so need a2d 
//vectors for r g b channels OR 3 1d vectors that output 
//vec[(cols_ * row) + col] so to make sure image stores pixel 
//data in row-major order, i.e. every row is stored sequentially 
//in data 
// I WANT = to output a PIXEL struct with rgb int values
std::vector<int> r_vec_;
std::vector<int> g_vec_;
std::vector<int> b_vec_;
r_vec_.reserve(cols_*rows_);  
g_vec_.reserve(cols_*rows_);  
b_vec_.reserve(cols_*rows_); 

for ( auto& pixel : data_ ){
    //each row get 3 values for rgb values
    r_vec_.push_back(pixel.red);
    g_vec_.push_back(pixel.green);
    b_vec_.push_back(pixel.blue);
}

Pixel wanted_pixel;
wanted_pixel.red = r_vec_[(cols_ * row) + col];
wanted_pixel.green = g_vec_[(cols_ * row) + col];
wanted_pixel.blue = b_vec_[(cols_ * row) + col];

return wanted_pixel;

}
void Image::DownScale(int scale){

std::cout << "DownScale function called" << std::endl;

// TODO: make it work for non multiples of img size
// for now give error message
if (rows_ % scale != 0 && cols_ % scale != 0 ) {
std::cout << "\n---ERROR: image does not scale by scale factor."
 << " IMAGE will be distorted!!!---\n" << std::endl;
}

for(int ii = 0; ii < rows_; ii+=scale) {
	for(int jj = 0; jj < cols_; jj+=scale) {
		// call method from within class - the called method 
		// returns an int value when given x,y coords in method 
		// it is processed as row-major order so 1st = (0,0)
        Image::Pixel pix = at(ii, jj);
        data_.push_back({pix.red, pix.green,pix.blue });
	}
}

std::cout << "size before delete: "<< data_.size() << std::endl;
// // erase the first X elements, i.e.- all original data:
data_.erase(data_.begin(),data_.begin()+(rows_*cols_));

// fill other data from image_data to struct image class 
rows_ =  floor(rows_ / scale);
cols_ = floor(cols_ / scale);
// assume max_val_ does not change

std::cout << "size after delete: "<< data_.size() << std::endl;

std::cout << "expected size: "<< rows_*cols_<< std::endl;

}

void Image::UpScale(int scale){

std::cout << "UpScale function called" << std::endl;
std::cout << "size before scaling: " << data_.size() << std::endl;

int new_rows = floor(rows_ * scale);
int new_cols = floor(cols_ * scale);
int orig_ii;
int orig_jj;

// better to write it down for an easy example in a tabele like  
// for example 4x4 downscaled to 2x2 and see what happens
for(int new_ii = 0; new_ii < new_rows; new_ii++) {
	for(int new_jj = 0; new_jj < new_cols; new_jj++) {
		//  orig_ii          new_ii 
		// ---------  =  ---------------
		// orig_rows     orig_rows*scale 
		
		orig_ii = int( floor( (new_ii *rows_) / (rows_ * scale) ) );
		orig_jj = int( floor( (new_jj *cols_)  / (cols_ * scale) ) );
		
		// call method from within class - the called method 
		// returns an int value when given x,y coords in method 
		// it is processed as row-major order so 1st = (0,0)
        Image::Pixel pix = at(orig_ii, orig_jj);
        data_.push_back({pix.red, pix.green,pix.blue });
	}
}

std::cout << "size before delete: "<< data_.size() << std::endl;
// // erase the first X elements, i.e.- all original data:
data_.erase(data_.begin(),data_.begin()+(rows_*cols_));

std::cout << "size after delete: "<< data_.size() << std::endl;

// fill other data from image_data to struct image class 
rows_ = new_rows;
cols_ = new_cols;
// assume max_val_ does not change

}

// strategy's methods
bool Image::ReadFromDisk(const std::string& file_name) { 

ImageData image_data; 
// this line calls the wanted referenced strategy defined in constructor
image_data = strategy_ptr_-> Read(file_name); 

// fill other data from image_data to struct image class 
rows_ = image_data.rows;
cols_ = image_data.cols;
max_val_ = image_data.max_val;

for(int idx = 0; idx < rows_* cols_; idx++){
    data_.push_back({image_data.data[0][idx], image_data.data[1][idx], image_data.data[2][idx]});
}

if (file_name.empty()){
    return false;
    std::cout <<"Bad filename, maybe file does not exist in right directory? " << file_name << std::endl;
}
else{
    std::cout <<"Filename Read was: "<< file_name << std::endl;
    return true;
    }
}

void Image::WriteToDisk(const std::string& file_name, ImageData image_data) { 

std::cout << "Image class stored pixels: " << data_.size() << std::endl;

// fill other data from image_data to struct image class (can image_data be empty?)
image_data.rows = rows();
image_data.cols = cols();
image_data.max_val = max_val_;
// std::cout <<"image_data.data: " << typeid(image_data.data).name() << std::endl;

// remember that image_data.data is a vector of int vectors
std::vector<std::vector<int>> vector_2d( rows_ * cols_* 3 );

for (auto& pixel : data_){
    vector_2d[0].push_back(pixel.red);    
    vector_2d[1].push_back(pixel.green);    
    vector_2d[2].push_back(pixel.blue); 
}

image_data.data = vector_2d;

// std::cout <<"size image_data.data: " << image_data.data.size() << std::endl;
// std::cout <<"capacity image_data.data: " << image_data.data.capacity() << std::endl;
// std::cout << "Image class stored pixels: " << data_.size() << std::endl;

strategy_ptr_-> Write(file_name, image_data); 

std::cout <<"filename to write: "<< file_name << std::endl;
}

}
