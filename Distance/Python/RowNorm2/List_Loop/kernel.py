import math

class Kernel:

    def __init__ (this, dimension, nsample1, nsample2):
        this.dimension = dimension
        this.nrow = nsample1

    # Data initialization
    def init (this, p1, p2, p3):
        this.alpha = [ p1 ** d for d in range(this.dimension) ]
        this.array = [ [ i + p2*d for d in range(this.dimension) ] for i in range(this.nrow) ]
        this.result = [0.] * this.nrow

    # Kernel
    def run(this):
        for i in range(this.nrow):
            sqr_norm = 0.
            for d in range(this.dimension):
                sqr_norm += this.array[i][d]**2 * this.alpha[d]

            this.result[i] = math.sqrt(sqr_norm)

    # Checksum
    def checksum(this):
        return sum(this.result)
