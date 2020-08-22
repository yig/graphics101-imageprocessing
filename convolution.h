#ifndef __convolution_h__
#define __convolution_h__

#include "image.h"

namespace graphics101 {

typedef float real;

// Converts the `input` image to greyscale, saving the result into `output`.
void greyscale( const Image& input, Image& output );

// Subtracts `input1` from `input2`, saving the absolute value of the result into `output`.
// This function assumes that the dimensions of input1 and input2 match.
void difference( const Image& input1, const Image& input2, Image& output );

// Applies a box blur with `radius` to `input`, saving the result
// into `output`.
void blur_box( const Image& input, int radius, Image& output );

// Scales the `input` image to the new dimensions, saving the result
// into `output`.
void scale( const Image& input, int new_width, int new_height, Image& output );

// Convolves the `input` image with `filter`, saving the result into `output`.
// NOTE: This function assumes that `filter` is greyscale (has the same
//       values for red, green, and blue).
void convolve( const Image& input, const Image& filter, Image& output );

// Sharpens the `input` image by moving `amount` away from a blur with `radius`.
// Saves the result into `output`.
void sharpen( const Image& input, real amount, int radius, Image& output );

// Performs edge detection on the `input` image. Stores the result into `output`.
void edge_detect( const Image& input, Image& output );

}

#endif /* __convolution_h__ */
