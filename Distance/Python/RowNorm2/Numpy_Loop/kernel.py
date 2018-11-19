import numpy as np
import math

class Kernel:

    def __init__ (this, dimension, nsample1, nsample2):
        this.dimension = dimension
        this.nrow = nsample1

    # Data initialization
    def init (this, p1, p2, p3):
        this.alpha = p1 ** np.arange(this.dimension)
        this.array = np.arange(this.nrow)[:,np.newaxis] + p2 * np.arange(this.dimension)[np.newaxis,:]
        this.result = np.empty([this.nrow])

    # Kernel
    def run(this):
        for i in range(this.nrow):
            sqr_norm = 0.
            for d in range(this.dimension):
                sqr_norm += this.array[i, d]**2 * this.alpha[d]

            this.result[i] = math.sqrt(sqr_norm)

    # Checksum
    def checksum(this):
        return np.sum(this.result)
