import math

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
        this.result = [ math.sqrt( sum( v*v*a for v,a in zip(row, this.alpha) ) ) for row in this.array ]

    # Checksum
    def checksum(this):
        return sum(this.result)
