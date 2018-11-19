import math
from numba import jit

@jit()
def kernel_run(array, alpha):
    return [ math.sqrt( sum( v*v*a for v,a in zip(row, alpha) ) ) for row in array ]


class Kernel:

    def __init__ (this, dimension, nsample1, nsample2):
        this.dimension = dimension
        this.nrow = nsample1

    # Data initialization
    def init (this, p1, p2, p3):
        this.alpha = [ p1 ** d for d in range(this.dimension) ]
        this.array = [ [ i + p2*d for d in range(this.dimension) ] for i in range(this.nrow) ]

    # Kernel
    def run(this):
        this.result = kernel_run(this.array, this.alpha)

    # Checksum
    def checksum(this):
        return sum(this.result)
