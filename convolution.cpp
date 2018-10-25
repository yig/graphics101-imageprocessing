#include "convolution.h"

#include <cassert>
#include <cstdlib>
#include <cmath>

using namespace graphics101;

namespace {
// Returns `value` clamped to lie in the range [min,max].
template< typename T >
inline T clamp( const T& value, const T& min, const T& max ) {
    return std::min( max, std::max( min, value ) );
}

// Your helper functions go here.

// NOTE: These are only suggestions!
// void convolve1D( int length, const QRgb* input, int input_stride, QRgb* output, int output_stride, const std::vector< int >& filter, bool normalize = true ) {}
// void resample1D( const QRgb* input, int input_length, int input_stride, QRgb* output, int output_length, int output_stride, const std::function<real(real)>& filter, real filter_radius, bool normalize = true ) {}

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
void greyscale( const QImage& input, QImage& output ) {
    assert( input.format() == QImage::Format_ARGB32 );
    
    // Your code goes here.
    
    // Allocate an output image the same size as the input.
    output = QImage( input.width(), input.height(), QImage::Format_ARGB32 );
    
    // Three ways to write it:
    // 1 Using input.pixel() and output.setPixel()
    // 2 Using scanLine() to iterate over rows.
    // 3 Using scanLine() to iterate over columns.
    // I have written all three below.
    
    
    // 1 Using input.pixel()
    for( int j = 0; j < input.height(); ++j ) {
        for( int i = 0; i < input.width(); ++i ) {
            // To access the i-th pixel, multiply i by the stride.
            const QRgb pix = input.pixel( i,j );
            
            // The grey value is just the average of red, green, and blue.
            // Perceptually, green is more important, but this is a fine approximation.
            const int grey = ( qRed(pix) + qGreen(pix) + qBlue(pix) )/3;
            
            output.setPixel( i,j, qRgb( grey, grey, grey ) );
        }
    }
    
    
    // 2 Using scanLine() to iterate over each row.
    for( int j = 0; j < input.height(); ++j ) {
        
        // Get a pointer to the pixels in each row.
        // Pixels in a row are adjacent.
        // Pixels in a column are separated by a stride of input.bytesPerLine()/4.
        const QRgb* row_in = (const QRgb*)input.scanLine( j );
        const int stride_in = 1;
        
        QRgb* row_out = (QRgb*)output.scanLine( j );
        const int stride_out = 1;
        
        for( int i = 0; i < input.width(); ++i ) {
            // To access the i-th pixel, multiply i by the stride.
            const QRgb pix = row_in[ i*stride_in ];
            
            // The grey value is just the average of red, green, and blue.
            // Perceptually, green is more important, but this is a fine approximation.
            const int grey = ( qRed(pix) + qGreen(pix) + qBlue(pix) )/3;
            
            row_out[ i*stride_out ] = qRgb( grey, grey, grey );
        }
    }
    
    
    // 3 Using scanLine() to iterate over each column.
    for( int i = 0; i < input.width(); ++i ) {
        
        // Get a pointer to the pixels in each column.
        // Pixels in a row are adjacent.
        // Pixels in a column are separated by a stride of input.bytesPerLine()/4.
        const QRgb* col_in = ((const QRgb*)input.scanLine(0)) + i;
        const int stride_in = input.bytesPerLine()/4;
        
        QRgb* col_out = ((QRgb*)output.scanLine(0)) + i;
        const int stride_out = output.bytesPerLine()/4;
        
        for( int j = 0; j < input.height(); ++j ) {
            // To access the j-th pixel, multiply j by the stride.
            const QRgb pix = col_in[ j*stride_in ];
            
            // The grey value is just the average of red, green, and blue.
            // Perceptually, green is more important, but this is a fine approximation.
            const int grey = ( qRed(pix) + qGreen(pix) + qBlue(pix) )/3;
            
            col_out[ j*stride_out ] = qRgb( grey, grey, grey );
        }
    }
}

// Subtracts `input1` from `input2`, saving the absolute value of the result into `output`.
// This function assumes that the dimensions of input1 and input2 match.
void difference( const QImage& input1, const QImage& input2, QImage& output ) {
    assert( input1.format() == QImage::Format_ARGB32 );
    assert( input2.format() == QImage::Format_ARGB32 );
    assert( input1.width() == input2.width() );
    assert( input1.height() == input2.height() );
    
    // Your code goes here.
    
    // Allocate an output image the same size as the input.
    output = QImage( input1.width(), input1.height(), QImage::Format_ARGB32 );
    
    // 1 Using input.pixel()
    for( int j = 0; j < input1.height(); ++j ) {
        for( int i = 0; i < input1.width(); ++i ) {
            const QRgb pix1 = input1.pixel( i,j );
            const QRgb pix2 = input2.pixel( i,j );
            
            const int rdiff = abs( int( qRed  (pix1) ) - int( qRed  (pix2) ) );
            const int gdiff = abs( int( qGreen(pix1) ) - int( qGreen(pix2) ) );
            const int bdiff = abs( int( qBlue (pix1) ) - int( qBlue (pix2) ) );
            
            output.setPixel( i,j, qRgb( rdiff, gdiff, bdiff ) );
        }
    }
}

// Applies a box blur with `radius` to `input`, saving the result
// into `output`.
void blur_box( const QImage& input, int radius, QImage& output ) {
    assert( input.format() == QImage::Format_ARGB32 );
    assert( radius >= 0 );

    // Your code goes here.
    output = input;
}

// Scales the `input` image to the new dimensions, saving the result
// into `output`.
void scale( const QImage& input, int new_width, int new_height, QImage& output ) {
    assert( input.format() == QImage::Format_ARGB32 );
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
void convolve( const QImage& input, const QImage& filter, QImage& output ) {
    assert( input.format() == QImage::Format_ARGB32 );
    assert( filter.format() == QImage::Format_ARGB32 );
    // We assume that the filter is all gray.
    // We won't assert(), because it's described as a slow function.
    // assert( filter.allGray() );

    // Your code goes here.
    output = input;

    // Debug with the identity filter
    // QImage filter = QImage( 1,1, QImage::Format_ARGB32 );
    // filter.fill(qRgb(255,255,255));
}

// Sharpens the `input` image by moving `amount` away from a blur with `radius`.
// Saves the result into `output`.
void sharpen( const QImage& input, real amount, int radius, QImage& output ) {
    assert( input.format() == QImage::Format_ARGB32 );
    assert( radius >= 0 );

    // Your code goes here.
    output = input;
}

// Performs edge detection on the `input` image. Stores the result into `output`.
void edge_detect( const QImage& input, QImage& output ) {
    assert( input.format() == QImage::Format_ARGB32 );

    // Your code goes here.
    output = input;
}

void ensureNotIndexed( QImage& image ) {
    if( image.format() != QImage::Format_ARGB32 ) image = image.convertToFormat( QImage::Format_ARGB32 );

}

}
