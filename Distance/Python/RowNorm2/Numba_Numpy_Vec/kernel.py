import numpy as np
from numba import jit

@jit()
def kernel_run(array, alpha):
    return np.sqrt( np.sum( np.square(array) * alpha[np.newaxis,:], 1) )

"""
@njit()
def kernel_run(array, alpha):
    return np.sqrt( np.sum( np.square(array) * alpha.reshape(1, alpha.shape[0]), 1) )
"""

class Kernel:

    def __init__ (this, dimension, nsample1, nsample2):
        this.dimension = dimension
        this.nrow = nsample1

    # Data initialization
    def init (this, p1, p2, p3):
        this.alpha = p1 ** np.arange(this.dimension)
        this.array = np.arange(this.nrow)[:,np.newaxis] + p2 * np.arange(this.dimension)[np.newaxis,:]

    # Kernel
    def run(this):
        this.result = kernel_run(this.array, this.alpha)

    # Checksum
    def checksum(this):
        return np.sum(this.result)
