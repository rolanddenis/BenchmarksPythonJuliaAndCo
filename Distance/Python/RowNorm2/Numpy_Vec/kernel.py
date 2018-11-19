import numpy as np

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
        this.result = np.sqrt( np.sum( np.square(this.array) * this.alpha[np.newaxis,:], 1) )

    # Checksum
    def checksum(this):
        return np.sum(this.result)
