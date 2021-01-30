#include "convolution.h"

#include <cassert>
#include <cstdlib>
#include <cmath>
#include <functional> // std::function
#include <vector>

using namespace graphics101;

namespace {
// Returns `value` clamped to lie in the range [min,max].
template< typename T >
inline T clamp( const T& value, const T& min, const T& max ) {
    return std::min( max, std::max( min, value ) );
}

// Your helper functions go here.

// NOTE: These are only suggestions!
// void convolve1D( int length, const ColorRGBA8* input, int input_stride, ColorRGBA8* output, int output_stride, const std::vector< int >& filter, bool normalize = true ) {}
// void resample1D( const ColorRGBA8* input, int input_length, int input_stride, ColorRGBA8* output, int output_length, int output_stride, const std::function<real(real)>& filter, real filter_radius, bool normalize = true ) {}

// To use this as a function taking only the x parameter, wrap it in a "lambda".
//     real radius = 2.0;
//     auto triangle_without_radius_parameter = [radius]( real x ) { return triangle( radius, x ); }
// Now we can call:
//     triangle_without_radius_parameter( x );
// or pass `triangle_without_radius_parameter` as an argument to a function taking a
// std::function<real(real)> parameter.
inline real triangle( real radius, real x ) {
    // Your code goes here.
    
    return 0;
}

}

namespace graphics101 {

// Converts each pixel to greyscale, saving the result into `output`.
void greyscale( const Image& input, Image& output ) {
    
    // Your code goes here.
    
    // Allocate an output image the same size as the input.
    output = Image( input.width(), input.height() );
    
    // Three ways to write it:
    // 1 Using input.pixel() and output.pixel()
    // 2 Using scanline() to iterate over rows.
    // 3 Using scanline() to iterate over columns.
    // I have written all three below.
    
    
    // 1 Using input.pixel()
    for( int j = 0; j < input.height(); ++j ) {
        for( int i = 0; i < input.width(); ++i ) {
            // The pixel() method gives direct access to the pixel at row i and column j.
            const ColorRGBA8 pix = input.pixel( i,j );
            
            // The grey value is just the average of red, green, and blue.
            // Perceptually, green is more important, but this is a fine approximation.
            const int grey = ( pix.r + pix.g + pix.b )/3;
            
            output.pixel( i,j ) = ColorRGBA8( grey, grey, grey );
        }
    }
    
    
    // 2 Using scanline() to iterate over each row.
    for( int j = 0; j < input.height(); ++j ) {
        
        // Get a pointer to the pixels in each row.
        // Pixels in a row are adjacent.
        // Pixels in a column are separated by a stride of input.width().
        const ColorRGBA8* row_in = input.scanline( j );
        const int stride_in = 1;
        
        ColorRGBA8* row_out = output.scanline( j );
        const int stride_out = 1;
        
        for( int i = 0; i < input.width(); ++i ) {
            // To access the i-th pixel, multiply i by the stride.
            const ColorRGBA8 pix = row_in[ i*stride_in ];
            
            // The grey value is just the average of red, green, and blue.
            // Perceptually, green is more important, but this is a fine approximation.
            const int grey = ( pix.r + pix.g + pix.b )/3;
            
            row_out[ i*stride_out ] = ColorRGBA8( grey, grey, grey );
        }
    }
    
    
    // 3 Using scanline() to iterate over each column.
    for( int i = 0; i < input.width(); ++i ) {
        
        // Get a pointer to the pixels in each column.
        // Pixels in a row are adjacent.
        // Pixels in a column are separated by a stride of input.width().
        const ColorRGBA8* col_in = input.scanline(0) + i;
        const int stride_in = input.width();
        
        ColorRGBA8* col_out = output.scanline(0) + i;
        const int stride_out = output.width();
        
        for( int j = 0; j < input.height(); ++j ) {
            // To access the j-th pixel, multiply j by the stride.
            const ColorRGBA8 pix = col_in[ j*stride_in ];
            
            // The grey value is just the average of red, green, and blue.
            // Perceptually, green is more important, but this is a fine approximation.
            const int grey = ( pix.r + pix.g + pix.b )/3;
            
            col_out[ j*stride_out ] = ColorRGBA8( grey, grey, grey );
        }
    }
}

// Subtracts `input1` from `input2`, saving the absolute value of the result into `output`.
// This function assumes that the dimensions of input1 and input2 match.
void difference( const Image& input1, const Image& input2, Image& output ) {
    assert( input1.width() == input2.width() );
    assert( input1.height() == input2.height() );
    
    // Your code goes here.
    
    // Allocate an output image the same size as the input.
    output = Image( input1.width(), input1.height() );
    
    // 1 Using input.pixel()
    for( int j = 0; j < input1.height(); ++j ) {
        for( int i = 0; i < input1.width(); ++i ) {
            const ColorRGBA8 pix1 = input1.pixel( i,j );
            const ColorRGBA8 pix2 = input2.pixel( i,j );
            
            const int rdiff = abs( int( pix1.r ) - int( pix2.r ) );
            const int gdiff = abs( int( pix1.g ) - int( pix2.g ) );
            const int bdiff = abs( int( pix1.b ) - int( pix2.b ) );
            
            output.pixel( i,j ) = ColorRGBA8( rdiff, gdiff, bdiff );
        }
    }
}

// Applies a box blur with `radius` to `input`, saving the result
// into `output`.
void blur_box( const Image& input, int radius, Image& output ) {
    assert( radius >= 0 );

    // Your code goes here.
    output = input;
}

// Scales the `input` image to the new dimensions, saving the result
// into `output`.
void scale( const Image& input, int new_width, int new_height, Image& output ) {
    assert( input.width() > 0 );
    assert( input.height() > 0 );
    assert( new_width > 0 );
    assert( new_height > 0 );

    // Your code goes here.
    output = input;
}

// Convolves the `input` image with `filter`, saving the result into `output`.
// NOTE: This function assumes that `filter` is greyscale (has the same
//       values for red, green, and blue).
void convolve( const Image& input, const Image& filter, Image& output ) {
    // We assume that the filter is all gray.
    
    // Your code goes here.
    output = input;

    // Debug with the identity filter
    // Image filter = Image( 1,1 );
    // filter.fill(ColorRGBA8(255,255,255));
}

// Sharpens the `input` image by moving `amount` away from a blur with `radius`.
// Saves the result into `output`.
void sharpen( const Image& input, real amount, int radius, Image& output ) {
    assert( radius >= 0 );

    // Your code goes here.
    output = input;
}

// Performs edge detection on the `input` image. Stores the result into `output`.
void edge_detect( const Image& input, Image& output ) {

    // Your code goes here.
    output = input;
}

}
