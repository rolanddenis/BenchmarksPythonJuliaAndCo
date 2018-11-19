import numpy as np

#pythran export kernel_run(float[:,:], float[])
def kernel_run(array, alpha):
    return np.sqrt( np.sum( np.square(array) * alpha[np.newaxis,:], 1) )

