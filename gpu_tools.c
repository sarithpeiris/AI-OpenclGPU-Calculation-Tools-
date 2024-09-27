#include "gpu_tools.h"

platform_devices_t *device = NULL;

const char *const files_rnn[] = {
    "gpu_general.h",
    "gpu_vector_matrix.h",
    "gpu_vector_matrix_T.h",
    "gpu_rnn_v1.cl"};

const char *const files_ann[] = {
    "gpu_general.h",
    "gpu_matrix_matrix.h",
    "gpu_matrix_matrix_T.h",
    "gpu_ann.cl"};

const char *const files_vm[] = {
    "gpu_general.h",
    "gpu_vector_matrix.h",
    "gpu_vector_matrix_T.h",
    "gpu_vm.cl"};

const char *const files_mm[] = {
    "gpu_general.h",
    "gpu_matrix_matrix.h",
    "gpu_matrix_matrix_T.h",
    "gpu_mm.cl"};

const char *const hashDefineString = "-D__M__=%d "
                                     "-D__N__=%d "
                                     "-D__K__=%d "
                                     "-D__Z__=%d "
                                     "-DTILE=%d "
                                     "-DACT=%d ";

// Find a GPU or CPU associated with the first available platform
cl_device_id create_device(cl_int platformID, cl_int deviceID, cl_int *err)
{

    cl_device_id *dev = NULL;
    static cl_int numPlatforms = 0, numDevices = 0;
    cl_platform_id *platform = NULL;

    if (!numPlatforms)
    {
        /* Identify a platform */
        *err = clGetPlatformIDs(1, NULL, &numPlatforms);
        clCheckErr(*err, return NULL);

        assert(!((platform = calloc(numPlatforms, sizeof(cl_platform_id))) == NULL));
        assert(!((device = calloc(numPlatforms, sizeof(platform_devices_t))) == NULL));

        *err = clGetPlatformIDs(numPlatforms, platform, NULL);
        clCheckErr(*err, return NULL);

        for (cl_int pltNdx = 0; pltNdx < numPlatforms; pltNdx++)
        {
            *err = clGetDeviceIDs(platform[pltNdx], CL_DEVICE_TYPE_GPU, 1, NULL, &numDevices);
            clCheckErr(*err, return NULL);

            assert(!((dev = calloc(numDevices, sizeof(cl_device_id))) == NULL));

            *err = clGetDeviceIDs(platform[pltNdx], CL_DEVICE_TYPE_GPU, numDevices, dev, NULL);
            clCheckErr(*err, return NULL);

            device[pltNdx].platform = platform[pltNdx];
            device[pltNdx].devs = dev;
        }

        free(platform);
    }

    if (((platformID >= numPlatforms) || (platformID < 0)) || ((deviceID >= numDevices) || (deviceID < 0)))
    {
        *err = CL_INVALID_ARG_INDEX;
        clCheckErr(*err, return NULL);
    }

    return device[platformID].devs[deviceID];
}

// set #define constants for the program
// sizeArr[0] --> row size of left oprend
// sizeArr[1] --> column size of left oprend
// sizeArr[2] --> column size of right oprend
filebuff_t program_hashconstant_string(
    cl_int sizeArr[SIZEARR],
    cl_int tileSize,
    actvcodes_t activationFunCode,
    cl_int *err)
{
    cl_int returnSize = 0, size = 0;
    cl_char *string = NULL;
    filebuff_t returnString = {0};

    assert(!((returnSize = snprintf(NULL, 0,
                                    hashDefineString,
                                    sizeArr[0],
                                    sizeArr[1],
                                    sizeArr[2],
                                    sizeArr[3],
                                    tileSize,
                                    activationFunCode)) < 1));

    assert(!((string = calloc(returnSize + 1, sizeof(cl_char))) == NULL));

    assert(!((size = snprintf(string, returnSize,
                              hashDefineString,
                              sizeArr[0],
                              sizeArr[1],
                              sizeArr[2],
                              sizeArr[3],
                              tileSize,
                              activationFunCode)) < returnSize));

    returnString.buffer = string;
    returnString.size = returnSize;

    return returnString;
}

// Create program from a file and compile it
cl_program build_program(
    cl_context ctx,
    cl_device_id dev,
    const filebuff_t *source,
    const filebuff_t *hashConstants,
    cl_int *err)
{
    char options[OPTIONSIZE] = {'\0'};
    char *program_log = NULL;
    size_t log_size = 0;
    cl_program prgm = NULL;

    // Create program from file
    prgm = clCreateProgramWithSource(ctx, 1, (const char **)&source->buffer, &source->size, err);
    clCheckErr(*err, return NULL);

    // Build program
    assert(!((snprintf(options, OPTIONSIZE, "%s -Werror -cl-std=CL2.0", hashConstants->buffer)) < 1));

    *err = clBuildProgram(prgm, 1, &dev, options, NULL, NULL);

    if (*err < 0)
    {

        // Find size of log and print to std input
        clGetProgramBuildInfo(prgm, dev, CL_PROGRAM_BUILD_LOG,
                              0, NULL, &log_size);
        program_log = (char *)malloc(log_size + 1);
        program_log[log_size] = '\0';
        clGetProgramBuildInfo(prgm, dev, CL_PROGRAM_BUILD_LOG,
                              log_size + 1, program_log, NULL);
        printf("%s\n", program_log);
        free(program_log);
        clCheckErr(*err, return NULL);
    }

    return prgm;
}

cl_kernel select_kernel(kernelcodes_t krnlCode, cl_program prgm, cl_int *err)
{
    cl_kernel k = NULL;
    char krnlName[KERNEL_NAME_SIZE] = {'\0'};
    switch (krnlCode)
    {
    case _RNN_V00_:
        strncpy(krnlName, "_RNN_V00_", KERNEL_NAME_SIZE);
        break;

    case _RNN_V10_:
        strncpy(krnlName, "_RNN_V10_", KERNEL_NAME_SIZE);
        break;

    case _RNN_V20_:
        strncpy(krnlName, "_RNN_V20_", KERNEL_NAME_SIZE);
        break;

    case _RNN_V30_:
        strncpy(krnlName, "_RNN_V30_", KERNEL_NAME_SIZE);
        break;

    case _VM_V00_:
        strncpy(krnlName, "_VM_V00_", KERNEL_NAME_SIZE);
        break;

    case _VM_V10_:
        strncpy(krnlName, "_VM_V10_", KERNEL_NAME_SIZE);
        break;

    case _VM_V20_:
        strncpy(krnlName, "_VM_V20_", KERNEL_NAME_SIZE);
        break;

    case _VM_V30_:
        strncpy(krnlName, "_VM_V30_", KERNEL_NAME_SIZE);
        break;

    case _ANN_V00_:
        strncpy(krnlName, "_ANN_V00_", KERNEL_NAME_SIZE);
        break;

    case _ANN_V10_:
        strncpy(krnlName, "_ANN_V10_", KERNEL_NAME_SIZE);
        break;

    case _ANN_V20_:
        strncpy(krnlName, "_ANN_V20_", KERNEL_NAME_SIZE);
        break;

    case _ANN_V30_:
        strncpy(krnlName, "_ANN_V30_", KERNEL_NAME_SIZE);
        break;

    case _MM_V00_:
        strncpy(krnlName, "_MM_V00_", KERNEL_NAME_SIZE);
        break;

    case _MM_V10_:
        strncpy(krnlName, "_MM_V10_", KERNEL_NAME_SIZE);
        break;

    case _MM_V20_:
        strncpy(krnlName, "_MM_V20_", KERNEL_NAME_SIZE);
        break;

    case _MM_V30_:
        strncpy(krnlName, "_MM_V30_", KERNEL_NAME_SIZE);
        break;
    }

    k = clCreateKernel(prgm, krnlName, err);
    printf("%s kernel selected!\n", krnlName);

    return k;
}

cl_int kernel_arguments(cl_kernel k, Tensor_t *tensorArrPtr[], const count)
{
    cl_int err = 0;
    for (int i = 0; i < count; i++)
    {
        err = clSetKernelArg(k, i, sizeof(cl_mem), &tensorArrPtr[i]->buff);
        clCheckErr(err, return err);
    }
    return err;
}

// initialize ann kernels
// Output =  A  *  B  +  c
// Output<M x K>   ---> [0]
// A<M x N>        ---> [1]
// B<N x K>        ---> [2]
// c<K>             ---> [3]
// Note: if Output is NULL then function will create and allocate memory for Output tensor
cl_int ann(cl_context c, cl_device_id d, kernel_ret_t *krnlRrtnPtr, actvcodes_t actvCode, Tensor_t *tensorArr[ANN_TENSOR_ARR_SIZE], cl_int tileSize)
{
    cl_short _Output_ = 0, _A_ = 1, _B_ = 2, _c_ = 3;
    cl_int err = 0;
    filebuff_t source = {0}, constants = {0};
    kernel_ret_t* k = krnlRrtnPtr;
    cl_program p = NULL;
    cl_kernel krnl = NULL;
    cl_int i = 0;
    kernelcodes_t code = _ANN_V00_;

    // main oprends cannot be NULL
    assert(!(tensorArr[_A_] == NULL));
    assert(!(tensorArr[_B_] == NULL));

    if (!tensorArr[_c_])
    {
        err = mm(c, d, krnlRrtnPtr, actvCode, (Tensor_t *[MM_TENSOR_ARR_SIZE]){tensorArr[_Output_], tensorArr[_A_], tensorArr[_B_]}, tileSize);
    }

    if (tensorArr[_A_]->transpose)
    {
        TRANSPOSE(*tensorArr[_A_]);
        code ^= 1;
    }
    if (tensorArr[_B_]->transpose)
    {
        TRANSPOSE(*tensorArr[_B_]);
        code ^= 2;
    }

    if (!tensorArr[_Output_])
    {
        assert(!((tensorArr[_Output_] = calloc(1, sizeof(Tensor_t))) == NULL));
        tensorArr[_Output_] = tensor_shape(c, tensorArr[_A_]->dim[_ROW_], tensorArr[_B_]->dim[_COLUMN_]);
    }

    assert(!(tensorArr[_A_]->dim[_COLUMN_] != tensorArr[_B_]->dim[_ROW_]));
    assert(!(tensorArr[_B_]->dim[_COLUMN_] != tensorArr[_c_]->dim[_COLUMN_]));
    assert(!(tensorArr[_Output_]->dim[_COLUMN_] != tensorArr[_B_]->dim[_COLUMN_]));
    assert(!(tensorArr[_Output_]->dim[_ROW_] != tensorArr[_A_]->dim[_ROW_]));

    source = read_files("r", 4, files_ann);
    constants = program_hashconstant_string(
        (cl_int[SIZEARR]){tensorArr[_A_]->dim[_ROW_], tensorArr[_A_]->dim[_COLUMN_], tensorArr[_B_]->dim[_COLUMN_], 0},
        tileSize,
        actvCode,
        &err);
    if ((err))
    {
        free(source.buffer);
        free(constants.buffer);
        clCheckErr(err, return err);
    }

    p = build_program(c, d, &source, &constants, &err);
    if ((err))
    {
        free(source.buffer);
        free(constants.buffer);
        clCheckErr(err, return err);
    }

    krnl = select_kernel(code, p, &err);
    clCheckErr(err, return err);

    for (i = 0; i < ANN_TENSOR_ARR_SIZE; i++)
    {
        err = clSetKernelArg(krnl, i, sizeof(cl_mem), &tensorArr[i]->buff);
        clCheckErr(err, return err);
    }

    k->k = krnl;

    k->gW[0] = ((tensorArr[_A_]->dim[_ROW_] / tileSize) + 1) * tileSize;
    k->gW[1] = ((tensorArr[_B_]->dim[_COLUMN_] / tileSize) + 1) * tileSize;
    k->lW[0] = tileSize;
    k->lW[1] = tileSize;

    k->dim = 2;

    k->output = tensorArr[_Output_];

    clRelease(p);
    free(source.buffer);
    free(constants.buffer);

    if (tensorArr[_A_]->transpose)
        TRANSPOSE(*tensorArr[_A_]);
    if (tensorArr[_B_]->transpose)
        TRANSPOSE(*tensorArr[_B_]);

    return err;
}

// initialize rnn kernels
// A[h + 1] = (A[h] * B) + (C * D) + e
// A<(M + 1) x K>   ---> [0]
// B<K x K>         ---> [1]
// C<M x N>         ---> [2]
// D<N x K>         ---> [3]
// e<1 x K>             ---> [4]
// Note: function will create and allocate memory for kernel[0] Output tensor
cl_int rnn(cl_context c, cl_device_id d, kernel_ret_t *krnlRrtnPtr, actvcodes_t actvCode, Tensor_t *tensorArr[RNN_TENSOR_ARR_SIZE], cl_int tileSize)
{
    cl_short _A_ = 0, _B_ = 1, _C_ = 2, _D_ = 3, _d_ = 4;
    cl_int err = 0;
    filebuff_t source = {0}, constants = {0};
    kernel_ret_t *k = krnlRrtnPtr;
    cl_program p = NULL;
    cl_kernel krnl = NULL;
    cl_int i = 0;
    kernelcodes_t code = _RNN_V00_;
    Tensor_t *mmOutput = NULL;
    Tensor_t *tnsrArr[RNN_TENSOR_ARR_SIZE - 1] = {0};

    // main oprends cannot be NULL
    assert(!(tensorArr[_A_] == NULL)); // A
    assert(!(tensorArr[_B_] == NULL)); // B
    assert(!(tensorArr[_C_] == NULL)); // C
    assert(!(tensorArr[_D_] == NULL)); // D
    assert(!(tensorArr[_d_] == NULL)); // d

    err = mm(c, d, &k[0], _NO_ACTV_, (Tensor_t *[MM_TENSOR_ARR_SIZE]){NULL, tensorArr[_C_], tensorArr[_D_]}, tileSize);
    clCheckErr(err, return err);

    mmOutput = k[0].output;

    if (tensorArr[_A_]->transpose)
    {
        TRANSPOSE(*tensorArr[_A_]);
        code ^= 1;
    }
    if (tensorArr[_B_]->transpose)
    {
        TRANSPOSE(*tensorArr[_B_]);
        code ^= 2;
    }

    assert(!((tensorArr[_A_]->dim[_COLUMN_] != tensorArr[_B_]->dim[_ROW_])));
    assert(!((tensorArr[_A_]->dim[_COLUMN_] != tensorArr[_B_]->dim[_COLUMN_])));
    assert(!((tensorArr[_A_]->dim[_ROW_] - 1 != mmOutput->dim[_ROW_])));
    assert(!((tensorArr[_B_]->dim[_COLUMN_] != mmOutput->dim[_COLUMN_])));
    assert(!((tensorArr[_B_]->dim[_COLUMN_] != tensorArr[_d_]->dim[_COLUMN_])));

    source = read_files("r", 4, files_rnn);
    constants = program_hashconstant_string(
        (cl_int[SIZEARR]){tensorArr[_A_]->dim[_ROW_], tensorArr[_A_]->dim[_COLUMN_], tensorArr[_B_]->dim[_COLUMN_], 0},
        tileSize,
        actvCode,
        &err);
    if ((err))
    {
        free(source.buffer);
        free(constants.buffer);
        clCheckErr(err, return err);
    }

    p = build_program(c, d, &source, &constants, &err);
    if ((err))
    {
        free(source.buffer);
        free(constants.buffer);
        clCheckErr(err, return err);
    }

    krnl = select_kernel(code, p, &err);
    clCheckErr(err, return err);

    tnsrArr[0] = tensorArr[_A_];
    tnsrArr[1] = tensorArr[_B_];
    tnsrArr[2] = mmOutput;
    tnsrArr[3] = tensorArr[_d_];

    for (i = 0; i < RNN_TENSOR_ARR_SIZE - 1; i++)
    {
        err = clSetKernelArg(krnl, i, sizeof(cl_mem), &tnsrArr[i]->buff);
        clCheckErr(err, return err);
    }

    k[1].k = krnl;

    k[1].gW[0] = ((tensorArr[_B_]->dim[_COLUMN_] / tileSize) + 1) * tileSize;
    k[1].lW[0] = tileSize;

    k[1].dim = 1;

    k[1].output = tensorArr[_A_];

    clRelease(p);
    free(source.buffer);
    free(constants.buffer);

    if (tensorArr[_A_]->transpose)
        TRANSPOSE(*tensorArr[_A_]);
    if (tensorArr[_B_]->transpose)
        TRANSPOSE(*tensorArr[_B_]);

    return err;
}

// initialize vector matrix kernels
// Output =  a  *  B
// Output<1 x K>   ---> [0]
// a<1 x N>        ---> [1]
// B<N x K>        ---> [2]
// Note: if Output is NULL then function will create and allocate memory for Output tensor
cl_int vm(cl_context c, cl_device_id d, kernel_ret_t *krnlRrtnPtr, actvcodes_t actvCode, Tensor_t *tensorArr[VM_TENSOR_ARR_SIZE], cl_int tileSize)
{
    cl_short _Output_ = 0, _a_ = 1, _B_ = 2;
    cl_int err = 0;
    filebuff_t source = {0}, constants = {0};
    kernel_ret_t* k = krnlRrtnPtr;
    cl_program p = NULL;
    cl_kernel krnl = NULL;
    cl_int i = 0;
    kernelcodes_t code = _VM_V00_;

    // main oprends cannot be NULL
    assert(!(tensorArr[_a_] == NULL)); // a
    assert(!(tensorArr[_B_] == NULL)); // B

    if (tensorArr[_a_]->transpose)
    {
        TRANSPOSE(*tensorArr[_a_]);
        code ^= 1;
    }
    if (tensorArr[_B_]->transpose)
    {
        TRANSPOSE(*tensorArr[_B_]);
        code ^= 2;
    }

    if (!tensorArr[_Output_])
    {
        assert(!((tensorArr[_Output_] = calloc(1, sizeof(Tensor_t))) == NULL));
        tensorArr[_Output_] = tensor_shape(c, tensorArr[_a_]->dim[_ROW_], tensorArr[_B_]->dim[_COLUMN_]);
    }

    assert(!(tensorArr[_a_]->dim[_COLUMN_] != tensorArr[_B_]->dim[_ROW_]));
    assert(!(tensorArr[_Output_]->dim[_COLUMN_] != tensorArr[_B_]->dim[_COLUMN_]));
    assert(!(tensorArr[_Output_]->dim[_ROW_] != tensorArr[_a_]->dim[_ROW_]));

    source = read_files("r", 4, files_vm);
    constants = program_hashconstant_string(
        (cl_int[SIZEARR]){tensorArr[_a_]->dim[_ROW_], tensorArr[_a_]->dim[_COLUMN_], tensorArr[_B_]->dim[_COLUMN_], 0},
        tileSize,
        actvCode,
        &err);
    if ((err))
    {
        free(source.buffer);
        free(constants.buffer);
        clCheckErr(err, return err);
    }

    p = build_program(c, d, &source, &constants, &err);
    if ((err))
    {
        free(source.buffer);
        free(constants.buffer);
        clCheckErr(err, return err);
    }

    krnl = select_kernel(code, p, &err);
    clCheckErr(err, return err);

    for (i = 0; i < VM_TENSOR_ARR_SIZE; i++)
    {
        err = clSetKernelArg(krnl, i, sizeof(cl_mem), &tensorArr[i]->buff);
        clCheckErr(err, return err);
    }

    k->k = krnl;

    k->gW[0] = ((tensorArr[_B_]->dim[_COLUMN_] / tileSize) + 1) * tileSize;
    k->lW[0] = tileSize;

    k->dim = 1;

    k->output = tensorArr[_Output_];

    clRelease(p);
    free(source.buffer);
    free(constants.buffer);

    if (tensorArr[_a_]->transpose)
        TRANSPOSE(*tensorArr[_a_]);
    if (tensorArr[_B_]->transpose)
        TRANSPOSE(*tensorArr[_B_]);

    return err;
}

// initialize matrix matrix kernels
// Output =  A  *  B
// Output<M x K>   ---> [0]
// A<M x N>        ---> [1]
// B<N x K>        ---> [2]
// Note: if Output is NULL then function will create and allocate memory for Output tensor
cl_int mm(cl_context c, cl_device_id d, kernel_ret_t *krnlRrtnPtr, actvcodes_t actvCode, Tensor_t *tensorArr[MM_TENSOR_ARR_SIZE], cl_int tileSize)
{
    cl_short _Output_ = 0, _A_ = 1, _B_ = 2;
    cl_int err = 0;
    filebuff_t source = {0}, constants = {0};
    kernel_ret_t* k = krnlRrtnPtr;
    cl_program p = NULL;
    cl_kernel krnl = NULL;
    cl_int i = 0;
    kernelcodes_t code = _MM_V00_;

    // main oprends cannot be NULL
    assert(!(tensorArr[_A_] == NULL)); // A
    assert(!(tensorArr[_B_] == NULL)); // B

    if (tensorArr[_A_]->transpose)
    {
        TRANSPOSE(*tensorArr[_A_]);
        code ^= 1;
    }
    if (tensorArr[_B_]->transpose)
    {
        TRANSPOSE(*tensorArr[_B_]);
        code ^= 2;
    }

    if (!tensorArr[_Output_])
    {
        tensorArr[_Output_] = tensor_shape(c, tensorArr[_A_]->dim[_ROW_], tensorArr[_B_]->dim[_COLUMN_]);
    }

    assert(!(tensorArr[_A_]->dim[_COLUMN_] != tensorArr[_B_]->dim[_ROW_]));
    assert(!(tensorArr[_Output_]->dim[_COLUMN_] != tensorArr[_B_]->dim[_COLUMN_]));
    assert(!(tensorArr[_Output_]->dim[_ROW_] != tensorArr[_A_]->dim[_ROW_]));

    source = read_files("r", 4, files_mm);
    constants = program_hashconstant_string(
        (cl_int[SIZEARR]){tensorArr[_A_]->dim[_ROW_], tensorArr[_A_]->dim[_COLUMN_], tensorArr[_B_]->dim[_COLUMN_], 0},
        tileSize,
        actvCode,
        &err);
    if ((err))
    {
        free(source.buffer);
        free(constants.buffer);
        clCheckErr(err, return err);
    }

    p = build_program(c, d, &source, &constants, &err);
    if ((err))
    {
        free(source.buffer);
        free(constants.buffer);
        clCheckErr(err, return err);
    }

    krnl = select_kernel(code, p, &err);
    clCheckErr(err, return err);

    for (i = 0; i < MM_TENSOR_ARR_SIZE; i++)
    {
        err = clSetKernelArg(krnl, i, sizeof(cl_mem), &tensorArr[i]->buff);
        clCheckErr(err, return err);
    }

    k->k = krnl;

    k->gW[0] = ((tensorArr[_A_]->dim[_ROW_] / tileSize) + 1) * tileSize;
    k->gW[1] = ((tensorArr[_B_]->dim[_COLUMN_] / tileSize) + 1) * tileSize;
    k->lW[0] = tileSize;
    k->lW[1] = tileSize;

    k->dim = 2;

    k->output = tensorArr[_Output_];

    clRelease(p);
    free(source.buffer);
    free(constants.buffer);

    if (tensorArr[_A_]->transpose)
        TRANSPOSE(*tensorArr[_A_]);
    if (tensorArr[_B_]->transpose)
        TRANSPOSE(*tensorArr[_B_]);

    return err;
}

// run the configured kernel
cl_int start_kernel(cl_command_queue q, kernel_ret_t *krnlStructure)
{
    cl_int err = 0;
    err = clEnqueueNDRangeKernel(
        q,
        krnlStructure->k,
        (cl_uint)krnlStructure->dim,
        NULL,
        krnlStructure->gW,
        krnlStructure->lW,
        0,
        NULL,
        NULL);
    clCheckErr(err, return err);

    err = clFinish(q);
    clCheckErr(err, return err);

    return err;
}

cl_int device_mem_write(cl_command_queue q, Tensor_t *tensorPtr, int offset, int numElements, real_t initValue)
{
    cl_int err = 0;
    tensorPtr->memmap = (real_t *)clEnqueueMapBuffer(q, tensorPtr->buff, CL_TRUE, CL_MAP_WRITE_INVALIDATE_REGION, 0, tensorPtr->sizeInBytes, 0, NULL, NULL, &err);
    clCheckErr(err, return err);
    err = clFinish(q);
    clCheckErr(err, return err);

    if (fpclassify(initValue) == FP_ZERO)
    {
        tensor_random_gen(tensorPtr->memmap, tensorPtr->elements, W_Max, W_Min, &err);
        clCheckErr(err, return err);
    }
    else
        populate(tensorPtr->memmap, offset, numElements, initValue);

    err = clEnqueueUnmapMemObject(q, tensorPtr->buff, (void *)tensorPtr->memmap, 0, NULL, NULL);
    clCheckErr(err, return err);
    err = clFinish(q);
    clCheckErr(err, return err);

    tensorPtr->memmap = NULL;

    return err;
}

cl_int device_mem_copy(cl_command_queue q, Tensor_t *tensorPtr)
{
    cl_int err = 0;

    if (!tensorPtr->tensor)
        assert(!((tensorPtr->tensor = calloc(tensorPtr->elements, sizeof(real_t))) == NULL));

    tensorPtr->memmap = clEnqueueMapBuffer(q, tensorPtr->buff, CL_TRUE, CL_MAP_READ, 0, tensorPtr->sizeInBytes, 0, NULL, NULL, &err);
    clCheckErr(err, return err);
    err = clFinish(q);
    clCheckErr(err, return err);

    assert(!((memcpy(tensorPtr->tensor, tensorPtr->memmap, tensorPtr->sizeInBytes)) == NULL));

    err = clEnqueueUnmapMemObject(q, tensorPtr->buff, tensorPtr->memmap, 0, NULL, NULL);
    clCheckErr(err, return err);
    err = clFinish(q);
    clCheckErr(err, return err);

    tensorPtr->memmap = NULL;

    return err;
}

cl_int device_mem_read(cl_command_queue q, cl_mem buff, real_t *memPtr, const int rows, const int col, bool transpose)
{
    cl_int err = 0,
           maxDigitsBeforeDecimal = 0,
           digitsBeforeDecimal = 0,
           i = 0,
           j = 0;
    cl_long temp = 0;

    memPtr = clEnqueueMapBuffer(q, buff, CL_TRUE, CL_MAP_READ, 0, sizeof(real_t) * (rows * col), 0, NULL, NULL, &err);
    clCheckErr(err, return err);
    err = clFinish(q);
    clCheckErr(err, return err);

    if (!transpose)
    {
        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < col; j++)
            {
                digitsBeforeDecimal = 0;
                temp = (cl_long)memPtr[NDX2D(col, i, j)];

                while (temp != 0)
                {
                    digitsBeforeDecimal++;
                    temp /= 10;
                }
                maxDigitsBeforeDecimal = (digitsBeforeDecimal > maxDigitsBeforeDecimal) ? digitsBeforeDecimal : maxDigitsBeforeDecimal;
            }
        }

        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < col; j++)
            {
                printf("%*.*f ", maxDigitsBeforeDecimal, 2, memPtr[NDX2D(col, i, j)]);
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
                temp = (cl_long)memPtr[NDX2DT(col, i, j)];

                while (temp != 0)
                {
                    digitsBeforeDecimal++;
                    temp /= 10;
                }
                maxDigitsBeforeDecimal = (digitsBeforeDecimal > maxDigitsBeforeDecimal) ? digitsBeforeDecimal : maxDigitsBeforeDecimal;
            }
        }

        for (i = 0; i < rows; i++)
        {
            for (j = 0; j < col; j++)
            {
                printf("%*.*f ", maxDigitsBeforeDecimal, 2, memPtr[NDX2DT(col, i, j)]);
            }
            puts("");
        }
    }

    err = clEnqueueUnmapMemObject(q, buff, memPtr, 0, NULL, NULL);
    clCheckErr(err, return err);
    err = clFinish(q);
    clCheckErr(err, return err);

    memPtr = NULL;

    return err;
}

cl_int clRefCountContext(cl_context c)
{
    cl_int err = 0, refCount = 0;
    err = clGetContextInfo(c, CL_CONTEXT_REFERENCE_COUNT, sizeof(refCount), &refCount, NULL);
    clCheckErr(err, NULL);
    return refCount;
}

cl_int clRefCountCommandQueue(cl_command_queue q)
{
    cl_int err = 0, refCount = 0;
    err = clGetCommandQueueInfo(q, CL_QUEUE_REFERENCE_COUNT, sizeof(refCount), &refCount, NULL);
    clCheckErr(err, NULL);
    return refCount;
}

cl_int clRefCountDevice(cl_device_id d)
{
    cl_int err = 0, refCount = 0;
    err = clGetDeviceInfo(d, CL_DEVICE_REFERENCE_COUNT, sizeof(refCount), &refCount, NULL);
    clCheckErr(err, NULL);
    return refCount;
}

cl_int clRefCountProgram(cl_program p)
{
    cl_int err = 0, refCount = 0;
    err = clGetProgramInfo(p, CL_PROGRAM_REFERENCE_COUNT, sizeof(refCount), &refCount, NULL);
    clCheckErr(err, NULL);
    return refCount;
}

cl_int clRefCountMemObject(cl_mem m)
{
    cl_int err = 0, refCount = 0;
    err = clGetMemObjectInfo(m, CL_MEM_REFERENCE_COUNT, sizeof(refCount), &refCount, NULL);
    clCheckErr(err, NULL);
    return refCount;
}

cl_int clRefCountEvent(cl_event e)
{
    cl_int err = 0, refCount = 0;
    err = clGetEventInfo(e, CL_EVENT_REFERENCE_COUNT, sizeof(refCount), &refCount, NULL);
    clCheckErr(err, NULL);
    return refCount;
}

cl_int clRefCountKernel(cl_kernel k)
{
    cl_int err = 0, refCount = 0;
    err = clGetKernelInfo(k, CL_KERNEL_REFERENCE_COUNT, sizeof(refCount), &refCount, NULL);
    clCheckErr(err, NULL);
    return refCount;
}
