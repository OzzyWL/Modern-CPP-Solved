// Copyright Igor Bogoslavskyi, year 2018.
// In case of any problems with the code please contact me.
// Email: igor.bogoslavskyi@uni-bonn.de.

#pragma once

#include <vector>
#include "io_strategies/strategy.h"


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
  Image(const IoStrategy& s);
  Image(const int rows, const int cols, const IoStrategy& s);
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
  const IoStrategy& strategy_;
};

}  // namespace igg
