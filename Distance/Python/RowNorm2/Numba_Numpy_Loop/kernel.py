import numpy as np
import math
from numba import njit, prange

@njit(parallel=True)
def kernel_run(array, alpha, result):
    for i in prange(array.shape[0]):
        sqr_norm = 0.
        for d in range(array.shape[1]):
            sqr_norm += array[i, d]**2 * alpha[d]

        result[i] = math.sqrt(sqr_norm)


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
        kernel_run(this.array, this.alpha, this.result)

    # Checksum
    def checksum(this):
        return np.sum(this.result)
