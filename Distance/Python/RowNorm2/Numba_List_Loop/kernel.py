import math
from numba import jit

@jit()
def kernel_run(array, alpha, result):
    for i in range(len(array)):
        sqr_norm = 0.
        for d in range(len(alpha)):
            sqr_norm += array[i][d]**2 * alpha[d]

        result[i] = math.sqrt(sqr_norm)


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
        kernel_run(this.array, this.alpha, this.result)

    # Checksum
    def checksum(this):
        return sum(this.result)
