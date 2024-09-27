#include "neuralnetwork.h"

#ifndef TOOLS_H
#define TOOLS_H

extern real_t W_Max, W_Min;

typedef struct filebuff
{
    char *buffer;
    size_t size;
} filebuff_t;

void mem_deallocate(Tensor_t *tensor);
void tensor_random_gen(real_t *memPtr, const int elements, real_t rangeMax, real_t rangeMin, int *err);
Tensor_t *tensor_shape(cl_context c, int row, int col);
Tensor_t tensor_copy(Tensor_t *source, int offset_top, int offset_bottom);
void populate(real_t *memPtr, int offset, int numelem, real_t initvalue);
void host_mem_read(real_t *memPtr, const int rows, const int col, bool transpose);
filebuff_t read_files(const char *mode, const int numfiles, const char *const *filesArr);

#define host_mem_print(tensor)                                                                                  \
    {                                                                                                           \
        printf("\n" #tensor "\n");                                                                              \
        host_mem_read((tensor).tensor, (tensor).dim[_ROW_], (tensor).tensor.dim[_COLUMN_], (tensor).transpose); \
    }

#endif // TOOLS_H