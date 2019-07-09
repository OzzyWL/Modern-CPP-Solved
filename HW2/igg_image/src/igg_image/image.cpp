#include "image.h"
#include "io_tools.h"
#include <typeinfo>
#include <math.h>

// Define all methods.
igg::Image::Image() {

std::cout << "Empty consturctor called" << std::endl;
} 


igg::Image::Image(const int rows, const int cols): rows_{rows}, cols_{cols} {

std::cout << "A consturctor called" << std::endl;

}

int& igg::Image::at(int const row, int const col)  {
// std::cout << "*at* function called" << std::endl;

// I want to access data_ already stored in my Class so
// Basically if every row is stored sequentially in data
// I want the row parm + total cols = to get count of all pixels before current row
// and then just add the col param for my column place 

// std::cout << data_[cols_ * row  + col ] << std::endl;

return data_[(cols_ * row) + col];

}

int igg::Image::at(const int row, const int col) const{

std::cout << "CONST *at* function called" << std::endl;

std::vector<std::vector<int>> vector_2d(rows_, std::vector<int>(cols_, -1));

// //Make sure your image stores pixel data in row-major order, i.e. every row is stored sequentially in data
for(int ii = 0; ii < rows_; ii++) {
	for(int jj = 0; jj < cols_; jj++) {
			vector_2d[ii][jj] = data_[ii+jj];
			// // std::cout << vector_2d[ii][jj] << std::endl;
	}
}

// std::cout << vector_2d[row][col] << std::endl;
// std::cout << typeid(vector_2d[row][col]).name() << std::endl;
return vector_2d[row][col];
}

bool igg::Image::FillFromPgm(const std::string& file_name){
std::cout << "FillFromPgm function called" << std::endl;

// I want to access data_ in my Class so first transfer it to class
// with the help of library
igg::io_tools::ImageData image_data; 
image_data = igg::io_tools::ReadFromPgm(file_name);

// fill other data from image_data to struct image class 
rows_ = image_data.rows;
cols_ = image_data.cols;
max_val_ = image_data.max_val;

// A loop to copy elements of 	old vector into new vector  
// uint to be only positive
for (uint i=0; i < image_data.data.size(); i++) 
	data_.push_back(image_data.data[i]);

// print out all data
// for(auto t=data_.begin(); t!=data_.end(); ++t)
// 	std::cout << *t << '\n';

if (data_.empty())
	return false;
else
	return true;
}

void igg::Image::WriteToPgm(const std::string& file_name){
std::cout << "WriteToPgm function called" << std::endl;

igg::io_tools::ImageData image_data;

// A loop to copy elements of old vector into new vector  
// uint to be only positive
for (uint d=0; d < data_.size(); d++) 
	image_data.data.push_back(data_[d]);

// fill other data from image class to image_data struct
image_data.rows = rows_;
image_data.cols = cols_;
image_data.max_val = max_val_;

// for(auto t=image_data.data.begin(); t!=image_data.data.end(); ++t)
// 	std::cout << *t << '\n';

igg::io_tools::WriteToPgm(image_data, file_name);

}

// TODO: check/fix precision of float numbers 
std::vector<float> igg::Image::ComputeHistogram(int bins){

std::cout << "ComputeHistogram function called" << std::endl;

std::vector<float> pixels_values;

for (double bb = 1; bb <= bins ; bb++)
{
	int pixels_counter = 0; // restart counter each bin
	for (int idx = 0; idx <= rows_*cols_ ; idx++)
	{	
		// assume start filling bins from left so bb++ and bins always const
		if (data_[idx] < bb * 255.0 / bins){
			// I need to bound the pixels counted on BOTH sides og bin
			// make sure it works for first and last bins
			if (data_[idx] >= (bb - 1) * 255.0 / bins) {
				pixels_counter++;
			}
		}
		// std::cout << "pixel val: " << data_[idx] << std::endl;
		// std::cout << "calc val: " << idx * 255.0 / bins << std::endl;
		// std::cout << "counter: " << pixels_counter << std::endl;
		// std::cout << "curr bin: " << bb << std::endl;
	}
// each bin change push pixels couted
pixels_values.push_back(pixels_counter);

}

return pixels_values;

}

void igg::Image::DownScale(int scale){

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
		data_.push_back( at(ii, jj) );
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

void igg::Image::UpScale(int scale){

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
		data_.push_back( at(orig_ii, orig_jj) );
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
