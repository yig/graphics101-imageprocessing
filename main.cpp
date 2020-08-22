#include "convolution.h"

#include <iostream> // std::cout and std::cerr
#include <cassert> // assert()
#include <fstream>
#include <sstream>
#include <vector>

using namespace graphics101;

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

bool run_one_command( const std::vector< std::string >& args ) {
    if( args.empty() ) return false;
    
    const std::string command( args.front() );
    if( command == "box" ) {
        if( args.size() != 4 ) return false;
        
        bool success;
        const int radius = strto<int>( args[1], success );
        if( !success || radius < 0 ) return false;
        const std::string& inpath( args[2] );
        const std::string& outpath( args[3] );
        
        Image input;
        if( !input.load( inpath ) ) {
            std::cerr << "Error loading input image: " << inpath << '\n';
            return false;
        }
        Image output;
        blur_box( input, radius, output );
        output.save( outpath );
        std::cout << "Saved: " << outpath << std::endl;
    }
    else if( command == "scale" ) {
        if( args.size() != 5 ) return false;
        
        bool success;
        const real width_percent = strto<real>( args[1], success );
        if( !success ) return false;
        const real height_percent = strto<real>( args[2], success );
        if( !success ) return false;
        
        if( width_percent <= 0 || height_percent <= 0 ) return false;
        
        const std::string& inpath( args[3] );
        const std::string& outpath( args[4] );
        
        Image input;
        if( !input.load( inpath ) ) {
            std::cerr << "Error loading input image: " << inpath << '\n';
            return false;
        }

        // Add 0.5 to get rounding when we cast from floating point to integer.
        const int width = std::max( 1, int( (width_percent/100)*input.width() + 0.5 ) );
        const int height = std::max( 1, int( (height_percent/100)*input.height() + 0.5 ) );

        Image output;
        scale( input, width, height, output );
        output.save( outpath );
        std::cout << "Saved: " << outpath << std::endl;
    }
    else if( command == "convolve" ) {
        if( args.size() != 4 ) return false;
        
        const std::string& filterpath( args[1] );
        const std::string& inpath( args[2] );
        const std::string& outpath( args[3] );
        
        Image filter;
        if( !filter.load( filterpath ) ) {
            std::cerr << "Error loading filter image: " << filterpath << '\n';
            return false;
        }
        {
            Image tmp;
            greyscale( filter, tmp );
            filter = tmp;
        }
        Image input;
        if( !input.load( inpath ) ) {
            std::cerr << "Error loading input image: " << inpath << '\n';
            return false;
        }
        Image output;
        convolve( input, filter, output );
        output.save( outpath );
        std::cout << "Saved: " << outpath << std::endl;
    }
    else if( command == "sharpen" ) {
        if( args.size() != 5 ) return false;
        
        bool success;
        const real amount = strto<real>( args[1], success );
        if( !success ) return false;
        const int radius = strto<int>( args[2], success );
        if( !success || radius < 0 ) return false;
        const std::string& inpath( args[3] );
        const std::string& outpath( args[4] );
        
        Image input;
        if( !input.load( inpath ) ) {
            std::cerr << "Error loading input image: " << inpath << '\n';
            return false;
        }
        Image output;
        sharpen( input, amount, radius, output );
        output.save( outpath );
        std::cout << "Saved: " << outpath << std::endl;
    }
    else if( command == "edges" ) {
        if( args.size() != 3 ) return false;
        
        const std::string& inpath( args[1] );
        const std::string& outpath( args[2] );
        
        Image input;
        if( !input.load( inpath ) ) {
            std::cerr << "Error loading input image: " << inpath << '\n';
            return false;
        }
        Image output;
        edge_detect( input, output );
        output.save( outpath );
        std::cout << "Saved: " << outpath << std::endl;
    }
    else if( command == "grey" ) {
        if( args.size() != 3 ) return false;
        
        const std::string& inpath( args[1] );
        const std::string& outpath( args[2] );
        
        Image input;
        if( !input.load( inpath ) ) {
            std::cerr << "Error loading input image: " << inpath << '\n';
            return false;
        }
        Image output;
        greyscale( input, output );
        output.save( outpath );
        std::cout << "Saved: " << outpath << std::endl;
    }
    else if( command == "difference" ) {
        if( args.size() != 4 ) return false;
        
        const std::string& inpath1( args[1] );
        const std::string& inpath2( args[2] );
        const std::string& outpath( args[3] );
        
        Image image1;
        if( !image1.load( inpath1 ) ) {
            std::cerr << "Error loading input image 1: " << inpath1 << '\n';
            return false;
        }
        Image image2;
        if( !image2.load( inpath2 ) ) {
            std::cerr << "Error loading input image 2: " << inpath2 << '\n';
            return false;
        }
        
        if( image1.width() != image2.width() || image1.height() != image2.height() ) {
            std::cerr << "Error: Input images have different dimensions.\n";
            return false;
        }
        
        Image output;
        difference( image1, image2, output );
        output.save( outpath );
        std::cout << "Saved: " << outpath << std::endl;
    }
    else if( command == "batch" ) {
        if( args.size() != 2 ) return false;
        
        const std::string& commands_path( args[1] );
        // Open the file.
        std::ifstream commands( commands_path );
        if( !commands ) {
            std::cerr << "ERROR: Unable to access path: " << commands_path << '\n';
            return false;
        }
        while( !( commands >> std::ws ).eof() ) {
            // Get each line.
            std::string line;
            std::getline( commands, line );
            
            // Skip blank lines.
            if( line.empty() ) continue;
            
            // Get the words.
            std::istringstream linestream( line );
            std::vector< std::string > words;
            while( !( linestream >> std::ws ).eof() ) {
                std::string word;
                linestream >> word;
                words.push_back( word );
            }
            assert( !words.empty() );
            
            // Skip lines that start with a `#`. Treat those as comments.
            if( words.front().front() == '#' ) continue;
            
            // Call run_one() recursively.
            run_one_command( words );
        }
    }
    else {
        return false;
    }
    
    return true;
}

}


void usage( const char* argv0 ) {
    std::cerr << "Usage: " << argv0 << " box radius input_image.png image_out.png\n";
    std::cerr << "Usage: " << argv0 << " scale width_percent height_percent input_image.png image_out.png\n";
    std::cerr << "Usage: " << argv0 << " convolve filter.png input_image.png image_out.png\n";
    std::cerr << "Usage: " << argv0 << " sharpen amount radius input_image.png image_out.png\n";
    std::cerr << "Usage: " << argv0 << " edges input_image.png image_out.png\n";
    std::cerr << "Usage: " << argv0 << " grey input_image.png image_out.png\n";
    std::cerr << "Usage: " << argv0 << " difference input_image1.png input_image2.png image_out.png\n";
    std::cerr << "Usage: " << argv0 << " batch commands.txt\n";
    std::exit(-1);
}

int main( int argc, char* argv[] ) {
    // Create a vector of strings from the command line arguments.
    std::vector< std::string > args( argv+1, argv+argc );
    
    if( !run_one_command( args ) ) usage( argv[0] );
    
    return 0;
}
