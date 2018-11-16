import numpy as np
import numexpr as ne

class Kernel:

    def __init__ (this, dimension, nsample1, nsample2):
        this.dimension = dimension
        this.nrow = nsample1

    # Data initialization
    def init (this, p1, p2, p3):
        this.alpha = p1 ** np.arange(this.dimension)
        this.array = np.arange(this.nrow)[:,np.newaxis] + p2 * np.arange(this.dimension)[np.newaxis,:]
        #ne.set_vml_num_threads(ne.detect_number_of_cores())

    # Kernel
    def run(this):
        #this.result = np.sqrt( np.sum( np.square(this.array) * this.alpha[np.newaxis,:], 1) )
        alpha = this.alpha[np.newaxis,:]
        array = this.array
        #result = ne.evaluate("sum( (array**2) * alpha, 1 )")
        this.result = np.sqrt( ne.evaluate("sum( (array**2) * alpha, 1 )") )
        #result = np.sum( np.square(this.array) * this.alpha[np.newaxis,:], 1)
        #this.result = ne.evaluate("sqrt(result)")

    # Checksum
    def checksum(this):
        return np.sum(this.result)
