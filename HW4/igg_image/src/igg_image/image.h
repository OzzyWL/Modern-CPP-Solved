// Copyright Igor Bogoslavskyi, year 2018.
// In case of any problems with the code please contact me.
// Email: igor.bogoslavskyi@uni-bonn.de.

#pragma once

#include <vector>
#include "io_strategies/strategy.h"
#include <memory>

namespace igg {

class Image {
 public:
  /// A struct within class Image that defines a pixel.
  struct Pixel {
    int red;
    int green;
    int blue;
  };

  // TODO: fill public interface.
  //The main method to connect pointer to wanted strategy
  void SetIoStrategy(const std::shared_ptr<IoStrategy>& strategy_ptr);
  
  Image();
  Image(const int rows, const int cols);
  int rows() const{return rows_;}
  int cols() const{return cols_;}

  Pixel at(const int rows, const int cols) const;
  // const because just extract values

  // without const this is actually a completely different function 
  Pixel& at(const int rows, const int cols) ;

  void DownScale(int scale);
  void UpScale(int scale);

  // strategy's methods
  // if fun(const ....) const; then CAN NOT change object 
  //( which means I can not assign to Image class)
  bool ReadFromDisk(const std::string& file_name);
  // ImageData set to NON const so can modify it based on class
  void WriteToDisk(const std::string& file_name, ImageData image_data);

 private:
  int rows_ = 0;
  int cols_ = 0;
  int max_val_ = 255;
  std::vector<Pixel> data_;
  // TODO: add missing private members when needed.
  std::shared_ptr<IoStrategy> strategy_ptr_ = nullptr;
};

}  // namespace igg
