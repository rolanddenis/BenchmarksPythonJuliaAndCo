import numpy as np
import math

#pythran export kernel_run(float list list, float list)
def kernel_run(array, alpha):
    return [ math.sqrt( sum( v*v*a for v,a in zip(row, alpha) ) ) for row in array ]

