#include "tools.h"

real_t W_Max = 0.9f, W_Min = -0.9f;

void tensor_random_gen(real_t *memPtr, const int elements, real_t rangeMax, real_t rangeMin, int *err)
{
    BYTE randomBytes[sizeof(unsigned short)];
    HCRYPTPROV hcrypto = 0;
    real_t value = 0.0f;

    if (CryptAcquireContext(&hcrypto, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
    {
        for (int i = 0; i < elements; i++)
        {
            if (CryptGenRandom(hcrypto, sizeof(randomBytes), randomBytes))
            {
                value = ((real_t)(*(unsigned short *)randomBytes) / USHRT_MAX);
                if (rangeMin != 0.0f)
                    value *= (rangeMax * 2) + rangeMin;
                else
                    value *= (rangeMax - rangeMin);
                memPtr[i] = value;
            }
            else
            {
                *err = -1;
                printf("Error Genarating random number.");
            }
        }

        CryptReleaseContext(hcrypto, 0);
        clCheckErr(*err, return);
    }
    else
    {
        *err = -1;
        printf("Error Accquring cryptographic context.\n");
        clCheckErr(*err, return);
    }
}

Tensor_t* tensor_shape(cl_context c, int row, int col)
{

    Tensor_t *t = NULL;
    int err = 0;
    assert(!((t = calloc(1, sizeof(Tensor_t))) == NULL));
    t->dim[_ROW_] = row;
    t->dim[_COLUMN_] = col;
    t->elements = t->dim[_ROW_] * t->dim[_COLUMN_];
    t->sizeInBytes = t->elements * sizeof(real_t);
    t->buff = clCreateBuffer(c, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, t->sizeInBytes, NULL, &err);
    clCheckErr(err, exit(err));

    return t;
}

Tensor_t tensor_copy(Tensor_t *source, int offset_top, int offset_bottom)
{
    assert(!((offset_bottom + offset_top) > source->dim[_ROW_]));

    Tensor_t tensor = {0};
    if (!offset_top && !offset_bottom) // normal copy
    {
        tensor = *source;
    }
    else if (offset_top && !offset_bottom) // top to bottom
    {
        tensor.tensor = source->tensor + (offset_top * source->dim[_COLUMN_]);
        tensor.dim[_ROW_] = source->dim[_ROW_] - offset_top;
    }
    else if (!offset_top && offset_bottom) // bottom to top
    {
        tensor.dim[_ROW_] = source->dim[_ROW_] - offset_bottom;
    }
    else // crop
    {
        tensor.tensor = source->tensor + (offset_top * source->dim[_COLUMN_]);
        tensor.dim[_ROW_] = source->dim[_ROW_] - (offset_top + offset_bottom);
    }

    tensor.buff = source->buff;
    tensor.dim[_COLUMN_] = source->dim[_COLUMN_];
    tensor.elements = tensor.dim[_ROW_] * tensor.dim[_COLUMN_];

    return tensor;
}

void mem_deallocate(Tensor_t *tensor)
{
    if(!tensor)
        return;

    if (tensor->tensor)
    {
        free(tensor->tensor);
        tensor->tensor = NULL;
    }

    if (tensor->buff)
    {
        clRelease(tensor->buff);
        tensor->buff = NULL;
    }

    free(tensor);
    tensor = NULL;
}

void populate(real_t *memPtr, int offset, int numelem, real_t initvalue)
{
    real_t value = 0.0f;

    for (int i = 0; i < numelem; i++)
    {
        value = initvalue + i;
        memPtr[i] = value;
    }
    puts("");
}

void host_mem_read(real_t *memPtr, const int rows, const int col, bool transpose)
{
    assert(!(memPtr == NULL));

    int maxDigitsBeforeDecimal = 0,
        digitsBeforeDecimal = 0,
        i = 0,
        j = 0;
    real_t temp = 0.0f;

    if (!transpose)
    {
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < col; j++)
            {
                digitsBeforeDecimal = 0;
                temp = memPtr[NDX2D(col, i, j)];

                while (temp >= 1.0f)
                {
                    digitsBeforeDecimal++;
                    temp /= 10.0f;
                }
                maxDigitsBeforeDecimal = (digitsBeforeDecimal > maxDigitsBeforeDecimal) ? digitsBeforeDecimal : maxDigitsBeforeDecimal;
            }
        }

        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < col; j++)
            {
                printf("%*.*f ", maxDigitsBeforeDecimal + 3, 2, memPtr[NDX2D(col, i, j)]);
            }
            puts("");
        }
    }
    else
    {
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < col; j++)
            {
                digitsBeforeDecimal = 0;
                temp = memPtr[NDX2DT(col, i, j)];

                while (temp >= 1.0f)
                {
                    digitsBeforeDecimal++;
                    temp /= 10.0f;
                }
                maxDigitsBeforeDecimal = (digitsBeforeDecimal > maxDigitsBeforeDecimal) ? digitsBeforeDecimal : maxDigitsBeforeDecimal;
            }
        }

        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < col; j++)
            {
                printf("%*.*f ", maxDigitsBeforeDecimal + 3, 2, memPtr[NDX2DT(col, i, j)]);
            }
            puts("");
        }
    }
}

filebuff_t read_files(const char *mode, const int numfiles, const char *const *filesArr)
{
    FILE *fp = NULL;
    long int bufferSize = 0;
    long int mainBufferSize = 0;
    char **buffer = NULL;
    char *mainBuffer = NULL, *tmpBuffer = NULL;
    long int *readSize = NULL;
    filebuff_t source = {0};

    assert(!((buffer = calloc(numfiles, sizeof(char *))) == NULL));
    assert(!((readSize = calloc(numfiles, sizeof(long int))) == NULL));

    for (int i = 0; i < numfiles; i++)
    {
        fp = NULL;

        assert(!((fp = fopen(filesArr[i], mode)) == NULL));
        assert(!((fseek(fp, 0, SEEK_END)) != 0));
        assert(!((bufferSize = ftell(fp)) == -1L));
        rewind(fp);
        assert(!((buffer[i] = calloc(bufferSize + 1, sizeof(char))) == NULL));
        readSize[i] = (long int)fread(buffer[i], sizeof(char), bufferSize + 1, fp);
        assert(!((feof(fp)) != 0) || !((ferror(fp)) != 0));
        fclose(fp);

        readSize[i] += 4;
        mainBufferSize += readSize[i];
    }

    assert(!((mainBuffer = (char *)calloc(mainBufferSize, sizeof(char))) == NULL));
    tmpBuffer = mainBuffer;

    for (int i = 0; i < numfiles; i++)
    {
        bufferSize = 0;
        assert(!((bufferSize = snprintf(tmpBuffer, readSize[i], "%s\n", buffer[i])) < 1));
        tmpBuffer += bufferSize;
        free(buffer[i]);
    }

    free(buffer);
    free(readSize);

    source.buffer = mainBuffer;
    source.size = mainBufferSize;

    return source;
}
