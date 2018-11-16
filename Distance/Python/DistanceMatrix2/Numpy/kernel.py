import numpy as np

class Kernel:

    def __init__ (this, dimension, nsample1, nsample2):
        this.dimension = dimension
        this.nsample1 = nsample1
        this.nsample2 = nsample2

    # Data initialization
    def init (this, p1, p2, p3):
        this.alpha = p1 ** np.arange(this.dimension)
        this.points1 = np.arange(this.nsample1)[:,np.newaxis] + p2 * np.arange(this.dimension)[np.newaxis,:]
        this.points2 = np.arange(this.nsample2)[:,np.newaxis] + p3 * np.arange(this.dimension)[np.newaxis,:]

    # Kernel
    def run(this):
        this.result = np.sqrt( np.sum(
              np.square(this.points1[:,np.newaxis,:] - this.points2[np.newaxis,:,:])
            * this.alpha[np.newaxis,np.newaxis,:], 2) )

    # Checksum
    def checksum(this):
        return np.sum(this.result)

