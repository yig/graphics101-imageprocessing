#!/usr/bin/env python

from __future__ import print_function, division

def print_one( binary, name, filters ):
    various = '''%(binary)s grey %(name)s.png %(name)s-reference/%(name)s-grey.png
%(binary)s box 0 %(name)s.png %(name)s-reference/%(name)s-box0.png
%(binary)s box 3 %(name)s.png %(name)s-reference/%(name)s-box3.png
%(binary)s box 25 %(name)s.png %(name)s-reference/%(name)s-box25.png
%(binary)s edges %(name)s.png %(name)s-reference/%(name)s-edges.png
%(binary)s sharpen 1 5 %(name)s.png %(name)s-reference/%(name)s-sharpen-1-5.png
%(binary)s sharpen 2 5 %(name)s.png %(name)s-reference/%(name)s-sharpen-2-5.png
%(binary)s sharpen 2 10 %(name)s.png %(name)s-reference/%(name)s-sharpen-2-10.png
%(binary)s scale 100 100 %(name)s.png %(name)s-reference/%(name)s-scale-100.png
%(binary)s scale 50 100 %(name)s.png %(name)s-reference/%(name)s-scale-50w.png
%(binary)s scale 10 100 %(name)s.png %(name)s-reference/%(name)s-scale-10w.png
%(binary)s scale 100 50 %(name)s.png %(name)s-reference/%(name)s-scale-50h.png
%(binary)s scale 100 10 %(name)s.png %(name)s-reference/%(name)s-scale-10h.png
%(binary)s scale 50 50 %(name)s.png %(name)s-reference/%(name)s-scale-50.png
%(binary)s scale 10 10 %(name)s.png %(name)s-reference/%(name)s-scale-10.png
%(binary)s scale 200 200 %(name)s.png %(name)s-reference/%(name)s-scale-200.png
%(binary)s scale 50 200 %(name)s.png %(name)s-reference/%(name)s-scale-50w-200h.png
%(binary)s scale 200 50 %(name)s.png %(name)s-reference/%(name)s-scale-200w-50h.png'''
    
    print( various % { "binary": binary, "name": name } )
    
    for filter in filters:
        print( "%(binary)s convolve filters/%(filter)s.png %(name)s.png %(name)s-reference/%(name)s-convolve-%(filter)s.png" % { "binary": binary, "name": name, "filter": filter } )

if __name__ == '__main__':
    import sys
    
    # name, width, height = sys.argv[1:4]
    # width = int(width)
    # height = int(height)
    # filters = sys.argv[4:]
    
    images = [
        "balls",
        "bananas",
        "wave",
        "wikipedia",
        "puppy2",
        "dot",
        
        # "puppy",
        # "bumps",
        # "bubbles",
        # "london",
        # "london2"
        ]
    filters = "identity", "box3", "box25", "linear", "quadratic", "direction", "heart"
    
    binary = "../../build-imageprocessing-clang-Release/imageprocessing"
    
    ## Try things like:
    # python reference_gen.py | parallel
    # python reference_gen.py | grep scale | parallel
    # python reference_gen.py puppy2 | grep scale | parallel
    
    ## If images are specified on the command line, that overrides the defaults.
    if len( sys.argv ) > 1:
        images = sys.argv[1:]
    
    for name in images:
        print_one( binary, name, filters )
        print()
