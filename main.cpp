#include "convolution.h"

#include <iostream> // std::cout and std::cerr
#include <cassert> // assert()
#include <sstream>

namespace
{
// Converts a string to the templated type.
template< typename T >
inline T strto( const std::string& str )
// Explicitly constructing the result (result = T(); instead of result;) means that
// built-in types (int, float, etc) will default to 0, and so return that in case of error.
{ std::istringstream converter( str ); T result = T(); converter >> result; return result; }
template< typename T >
inline T strto( const std::string& str, bool& success )
// Explicitly constructing the result (result = T(); instead of result;) means that
// built-in types (int, float, etc) will default to 0, and so return that in case of error.
// Optional output parameter `success` tells the caller this explicitly.
{ std::istringstream converter( str ); T result = T(); success = bool(converter >> result); return result; }

}


using namespace graphics101;

void usage( const char* argv0 ) {
    std::cerr << "Usage: " << argv0 << " box radius input_image.png image_out.png\n";
    std::cerr << "Usage: " << argv0 << " scale width_percent height_percent input_image.png image_out.png\n";
    std::cerr << "Usage: " << argv0 << " convolve filter.png input_image.png image_out.png\n";
    std::cerr << "Usage: " << argv0 << " sharpen amount radius input_image.png image_out.png\n";
    std::cerr << "Usage: " << argv0 << " edges input_image.png image_out.png\n";
    std::cerr << "Usage: " << argv0 << " grey input_image.png image_out.png\n";
    std::exit(-1);
}

int main( int argc, char* argv[] ) {
    if( argc == 1 ) usage( argv[0] );
    
    const std::string command( argv[1] );
    if( command == "box" ) {
        if( argc != 5 ) usage( argv[0] );
        
        bool success;
        const int radius = strto<int>( argv[2], success );
        if( !success || radius < 0 ) usage( argv[0] );
        const char* inpath( argv[3] );
        const char* outpath( argv[4] );
        
        QImage input;
        if( !input.load( inpath ) ) {
            std::cerr << "Error loading input image: " << inpath << '\n';
            usage( argv[0] );
        }
        ensureNotIndexed( input );
        QImage output;
        blur_box( input, radius, output );
        output.save( outpath );
        std::cout << "Saved: " << outpath << std::endl;
    }
    else if( command == "scale" ) {
        if( argc != 6 ) usage( argv[0] );
        
        bool success;
        const real width_percent = strto<real>( argv[2], success );
        if( !success ) usage( argv[0] );
        const real height_percent = strto<real>( argv[3], success );
        if( !success ) usage( argv[0] );
        
        if( width_percent <= 0 || height_percent <= 0 ) usage( argv[0] );
        
        const char* inpath( argv[4] );
        const char* outpath( argv[5] );
        
        QImage input;
        if( !input.load( inpath ) ) {
            std::cerr << "Error loading input image: " << inpath << '\n';
            usage( argv[0] );
        }
        ensureNotIndexed( input );

        // Add 0.5 to get rounding when we cast from floating point to integer.
        const int width = std::max( 1, int( (width_percent/100)*input.width() + 0.5 ) );
        const int height = std::max( 1, int( (height_percent/100)*input.height() + 0.5 ) );

        QImage output;
        scale( input, width, height, output );
        output.save( outpath );
        std::cout << "Saved: " << outpath << std::endl;
    }
    else if( command == "convolve" ) {
        if( argc != 5 ) usage( argv[0] );
        
        const char* filterpath( argv[2] );
        const char* inpath( argv[3] );
        const char* outpath( argv[4] );
        
        QImage filter;
        if( !filter.load( filterpath ) ) {
            std::cerr << "Error loading filter image: " << filterpath << '\n';
            usage( argv[0] );
        }
        ensureNotIndexed( filter );
        {
            QImage tmp;
            greyscale( filter, tmp );
            filter = tmp;
        }
        QImage input;
        if( !input.load( inpath ) ) {
            std::cerr << "Error loading input image: " << inpath << '\n';
            usage( argv[0] );
        }
        ensureNotIndexed( input );
        QImage output;
        convolve( input, filter, output );
        output.save( outpath );
        std::cout << "Saved: " << outpath << std::endl;
    }
    else if( command == "sharpen" ) {
        if( argc != 6 ) usage( argv[0] );
        
        bool success;
        const real amount = strto<real>( argv[2], success );
        if( !success ) usage( argv[0] );
        const int radius = strto<int>( argv[3], success );
        if( !success || radius < 0 ) usage( argv[0] );
        const char* inpath( argv[4] );
        const char* outpath( argv[5] );
        
        QImage input;
        if( !input.load( inpath ) ) {
            std::cerr << "Error loading input image: " << inpath << '\n';
            usage( argv[0] );
        }
        ensureNotIndexed( input );
        QImage output;
        sharpen( input, amount, radius, output );
        output.save( outpath );
        std::cout << "Saved: " << outpath << std::endl;
    }
    else if( command == "edges" ) {
        if( argc != 4 ) usage( argv[0] );
        
        const char* inpath( argv[2] );
        const char* outpath( argv[3] );
        
        QImage input;
        if( !input.load( inpath ) ) {
            std::cerr << "Error loading input image: " << inpath << '\n';
            usage( argv[0] );
        }
        ensureNotIndexed( input );
        QImage output;
        edge_detect( input, output );
        output.save( outpath );
        std::cout << "Saved: " << outpath << std::endl;
    }
    else if( command == "grey" ) {
        if( argc != 4 ) usage( argv[0] );
        
        const char* inpath( argv[2] );
        const char* outpath( argv[3] );
        
        QImage input;
        if( !input.load( inpath ) ) {
            std::cerr << "Error loading input image: " << inpath << '\n';
            usage( argv[0] );
        }
        ensureNotIndexed( input );
        QImage output;
        greyscale( input, output );
        output.save( outpath );
        std::cout << "Saved: " << outpath << std::endl;
    }
    else {
        usage( argv[0] );
    }
    
    return 0;
}
