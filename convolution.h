#ifndef __convolution_h__
#define __convolution_h__

#include <QImage>

namespace graphics101 {

// NOTE: All of these functions, except ensureNotIndex() assume
//       that the QImage::format() is QImage::Format_ARGB32.
//       This allows direct pixel access.

typedef float real;

// Converts the `input` image to greyscale, saving the result into `output`.
void greyscale( const QImage& input, QImage& output );

// Subtracts `input1` from `input2`, saving the absolute value of the result into `output`.
// This function assumes that the dimensions of input1 and input2 match.
void difference( const QImage& input1, const QImage& input2, QImage& output );

// Applies a box blur with `radius` to `input`, saving the result
// into `output`.
void blur_box( const QImage& input, int radius, QImage& output );

// Scales the `input` image to the new dimensions, saving the result
// into `output`.
void scale( const QImage& input, int new_width, int new_height, QImage& output );

// Convolves the `input` image with `filter`, saving the result into `output`.
// NOTE: This function assumes that `filter` is greyscale (has the same
//       values for red, green, and blue).
void convolve( const QImage& input, const QImage& filter, QImage& output );

// Sharpens the `input` image by moving `amount` away from a blur with `radius`.
// Saves the result into `output`.
void sharpen( const QImage& input, real amount, int radius, QImage& output );

// Performs edge detection on the `input` image. Stores the result into `output`.
void edge_detect( const QImage& input, QImage& output );

// If necessary, modifies image to be the non-indexed RGBA format (QImage::Format_ARGB32).
// This is useful even for greyscale images, because QImage's with the format
// QImage::Format_Grayscale8 are considered indexed and don't support direct pixel access.
void ensureNotIndexed( QImage& image );

}

#endif /* __convolution_h__ */
