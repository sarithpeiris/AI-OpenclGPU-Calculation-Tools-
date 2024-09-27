#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <windows.h>
#include <wincrypt.h>
#include <string.h>
#include <stdarg.h>

#define real_t float

#define CL_TARGET_OPENCL_VERSION 300
#include <CL/cl.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#define FLT_EVAL_METHOD 0
#define _CRT_SILENCE_NONCONFORMING_TGMATH_H
#include <tgmath.h>

#define NDX2D(COLSIZE, rowNdx, colNdx) (((COLSIZE) * (rowNdx)) + (colNdx))
#define NDX2DT(ROWSIZE, rowNdx, colNdx) (((ROWSIZE) * (colNdx)) + (rowNdx))

#define TRANSPOSE(TENSOR)                              \
    {                                                  \
        (TENSOR).dim[_ROW_] ^= (TENSOR).dim[_COLUMN_]; \
        (TENSOR).dim[_COLUMN_] ^= (TENSOR).dim[_ROW_]; \
        (TENSOR).dim[_ROW_] ^= (TENSOR).dim[_COLUMN_]; \
    }

#define _COLUMN_ 0
#define _ROW_ 1


typedef enum actvcodes_
{
    _NO_ACTV_,
    _SOFTMAX_,
    _TANH_,
    _SIGMOID_
} actvcodes_t;

typedef struct Tensor_
{
    real_t *tensor;
    int dim[2];
    int elements;
    int sizeInBytes;
    cl_mem buff;
    real_t *memmap;
    FILE *fp;
    bool transpose;
} Tensor_t;



#include "tools.h"
#include "gpu_tools.h"
#endif // NEURAL_NETWORK_H