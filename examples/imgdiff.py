from __future__ import print_function, division
from numpy import *
from PIL import Image
import os, sys

args = list(sys.argv[1:])
def usage():
    print( "Usage:", sys.argv[0], "image1.png image2.png output.png", file = sys.stderr )
    sys.exit(-1)

if len( args ) != 3: usage()

inpath1 = args[0]
inpath2 = args[1]
outpath = args[2]

print( "Loading:", inpath1 )
img1 = asarray( Image.open( inpath1 ).convert('RGB') ).astype( int )
print( "Loading:", inpath2 )
img2 = asarray( Image.open( inpath2 ).convert('RGB') ).astype( int )

if img1.shape != img2.shape:
    print( "ERROR: Image dimensions don't match:", img1.shape, "!=", img2.shape, file = sys.stderr )
    usage()

difference = abs( img1 - img2 )
Image.fromarray( difference.astype( uint8 ) ).save( outpath )
print( "Saved:", outpath )
