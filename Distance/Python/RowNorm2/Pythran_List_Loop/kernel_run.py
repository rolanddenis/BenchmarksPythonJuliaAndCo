import numpy as np
import math

#pythran export kernel_run(float list list, float list, float list)
def kernel_run(array, alpha, result):
    #omp parallel for
    for i in range(len(array)):
        sqr_norm = 0.
        for d in range(len(alpha)):
            sqr_norm += array[i][d]**2 * alpha[d]

        result[i] = math.sqrt(sqr_norm)

