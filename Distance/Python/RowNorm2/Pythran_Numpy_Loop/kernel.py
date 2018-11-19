import numpy as np
from kernel_run import kernel_run

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

