from __future__ import print_function, division

from numpy import *
from PIL import Image
import sys, os

size, = sys.argv[1:]
size = int( size )

arr = zeros( ( size, size, 3 ) )

'''
def products():
    ts = linspace( 0, 1, size+1 )[1:]
    
    ts *= pi
    
    ts *= ts
    
    # arr[:,:,:] = ( cos( ts )/ts )[newaxis,:,newaxis] * ( sin( ts )/ts )[:,newaxis,newaxis]
    arr[:,:,:] = ( cos( ts ) )[newaxis,:,newaxis] * ( cos( ts ) )[:,newaxis,newaxis]
    
    arr *= 0.5
    arr += 0.5
'''

def apply( f, arr ):
    for i in range(size):
        for j in range(size):
            s = float(i)/size
            t = float(j)/size
            arr[i,j] = f(s,t)
    
    arr *= 0.5
    arr += 0.5

def circles( s,t ):
    return sin( pi*2*sqrt( s*s + t*t ) )

def circles_sinc( s,t ):
    r = 2*pi*2*sqrt( s*s + t*t )
    # r *= r
    
    # avoid zero
    # r += 1e-5
    
    return sin( r**2 )

# apply( circles, arr )
apply( circles_sinc, arr )

outpath = os.path.splitext( os.path.split(__file__)[-1] )[0] + '.png'
Image.fromarray( (( arr )*255).astype(uint8).clip(0,255) ).save( outpath )
print( "Saved:", outpath )
