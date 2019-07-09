#include "image.h"


int main(){

	igg::Image image(512,512);
	igg::Image image2;

	//(2)
	//------------------------------
	bool is_filled = image.FillFromPgm("../data/lena.ascii.pgm");
	std::cout << "The function FillFromPgm got a vector (TRUE=1): " << is_filled << std::endl;

	image.WriteToPgm("../data/lena.ascii_WRITTEN.pgm");
	//------------------------------


	// //(1)
	//-----------------------------
	int row = 333;
	int col = 333;

	const igg::Image& image_ref = image;

	int val = image_ref.at(row,col);
	std::cout << "STORED pixel value BEFORE modification is: " << val << std::endl;

	std::cout << "Extracted Pixel BEFORE modification is: " << image_ref.at(row, col) << std::endl;
	
	image.at(row,col) = 255;
	std::cout << "Extracted Pixel AFTER modification is: " << image_ref.at(row, col) << std::endl;

	//------------------------------
	


	//(3)
	std::cout << "------Histogram------" << std::endl;

	//------------------------------
	std::vector<float> hist_vec_floats;
 	hist_vec_floats = image.ComputeHistogram(4);

	for(auto t=hist_vec_floats.begin(); t!=hist_vec_floats.end(); ++t)
		std::cout << *t << '\n';
	// //------------------------------

	//(4)
	//------------------------------
	std::cout << "------Scaling------" << std::endl;
	// DownScale only works with divisors of image cols and rows size
	image.DownScale(2);
	image.WriteToPgm("../data/lena.ascii_WRITTEN_DOWN_scaled.pgm");

	image.UpScale(4);
	image.WriteToPgm("../data/lena.ascii_WRITTEN_UP_scaled.pgm");
	// //------------------------------


	return 0;
}
