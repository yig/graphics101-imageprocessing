#!/usr/bin/env python

from __future__ import print_function, division

def print_one( name, filters ):
    various = '''grey %(name)s.png %(name)s-reference/%(name)s-grey.png
box 0 %(name)s.png %(name)s-reference/%(name)s-box0.png
box 3 %(name)s.png %(name)s-reference/%(name)s-box3.png
box 25 %(name)s.png %(name)s-reference/%(name)s-box25.png
edges %(name)s.png %(name)s-reference/%(name)s-edges.png
sharpen 1 5 %(name)s.png %(name)s-reference/%(name)s-sharpen-1-5.png
sharpen 2 5 %(name)s.png %(name)s-reference/%(name)s-sharpen-2-5.png
sharpen 2 10 %(name)s.png %(name)s-reference/%(name)s-sharpen-2-10.png
scale 100 100 %(name)s.png %(name)s-reference/%(name)s-scale-100.png
scale 50 100 %(name)s.png %(name)s-reference/%(name)s-scale-50w.png
scale 10 100 %(name)s.png %(name)s-reference/%(name)s-scale-10w.png
scale 100 50 %(name)s.png %(name)s-reference/%(name)s-scale-50h.png
scale 100 10 %(name)s.png %(name)s-reference/%(name)s-scale-10h.png
scale 50 50 %(name)s.png %(name)s-reference/%(name)s-scale-50.png
scale 10 10 %(name)s.png %(name)s-reference/%(name)s-scale-10.png
scale 200 200 %(name)s.png %(name)s-reference/%(name)s-scale-200.png
scale 50 200 %(name)s.png %(name)s-reference/%(name)s-scale-50w-200h.png
scale 200 50 %(name)s.png %(name)s-reference/%(name)s-scale-200w-50h.png'''
    
    print( various % { "name": name } )
    
    for filter in filters:
        print( "convolve filters/%(filter)s.png %(name)s.png %(name)s-reference/%(name)s-convolve-%(filter)s.png" % { "name": name, "filter": filter } )

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
        "puppy",
        "dot",
        
        # "puppy2",
        # "bumps",
        # "bubbles",
        # "london",
        # "london2"
        ]
    filters = "identity", "box3", "box25", "linear", "quadratic", "direction", "heart"
    
    ## Try things like:
    # python reference_gen.py | parallel
    # python reference_gen.py | grep scale | parallel
    # python reference_gen.py puppy | grep scale | parallel
    
    ## If images are specified on the command line, that overrides the defaults.
    if len( sys.argv ) > 1:
        images = sys.argv[1:]
    
    for name in images:
        print_one( name, filters )
        print()
