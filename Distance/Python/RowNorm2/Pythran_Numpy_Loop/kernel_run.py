import numpy as np
import math

#pythran export kernel_run(float[:,:], float[], float[])
def kernel_run(array, alpha, result):
    #omp parallel for
    for i in range(array.shape[0]):
        sqr_norm = 0.
        for d in range(array.shape[1]):
            sqr_norm += array[i, d]**2 * alpha[d]

        result[i] = math.sqrt(sqr_norm)

