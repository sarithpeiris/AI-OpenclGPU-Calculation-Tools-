#include "neuralnetwork.h"

#ifndef GPU_TOOLS_H
#define GPU_TOOLS_H

#define SIZEARR 4
#define OPTIONSIZE 200
#define RNN_TENSOR_ARR_SIZE 5
#define ANN_TENSOR_ARR_SIZE 4
#define VM_TENSOR_ARR_SIZE 3
#define MM_TENSOR_ARR_SIZE 3
#define WORK_DIMS 3
#define KERNEL_NAME_SIZE 50

#define TILE_2 2
#define TILE_4 4
#define TILE_8 8
#define TILE_16 16

typedef struct platform_devices
{
    cl_platform_id platform;
    cl_device_id *devs;
} platform_devices_t;

typedef struct kernel_return
{
    cl_kernel k;
    size_t gW[WORK_DIMS], lW[WORK_DIMS], dim;
    Tensor_t *output;
    size_t krnlUsageCount;
} kernel_ret_t;

typedef enum kernel_codes
{
    _RNN_V00_, // A[h + 1] = A[h] * B + C + d
    _RNN_V10_, // A[h + 1] = A[h](t) * B + C + d
    _RNN_V20_, // A[h + 1] = A[h] * B(t) + C + d
    _RNN_V30_, // A[h + 1] = A[h](t) * B(t) + C + d

    _VM_V00_, // Output = a * B
    _VM_V10_, // Output = a(t) * B
    _VM_V20_, // Output = a * B(t)
    _VM_V30_, // Output = a(t) * B(t)

    _ANN_V00_, // Output = A * B + c
    _ANN_V10_, // Output = A(t) * B + c
    _ANN_V20_, // Output = A * B(t) + c
    _ANN_V30_, // Output = A(t) * B(t) + c

    _MM_V00_, // Output = A * B
    _MM_V10_, // Output = A(t) * B
    _MM_V20_, // Output = A * B(t)
    _MM_V30_  // Output = A(t) * B(t)

} kernelcodes_t;

extern platform_devices_t *device;
extern const char *const files_rnn[];
extern const char *const files_ann[];
extern const char *const files_vm[];
extern const char *const files_mm[];
extern const char *const hashDefineString;

cl_program build_program(
    cl_context ctx,
    cl_device_id dev,
    const filebuff_t *source,
    const filebuff_t *hashConstants,
    cl_int *err);
cl_device_id create_device(cl_int platformID, cl_int deviceID, cl_int *err);
filebuff_t program_hashconstant_string(
    cl_int sizeArr[SIZEARR],
    cl_int tileSize,
    actvcodes_t activationFunCode,
    cl_int *err);
cl_kernel select_kernel(kernelcodes_t krnlCode, cl_program prgm, cl_int *err);
cl_int ann(cl_context c, cl_device_id d, kernel_ret_t *krnlRrtnPtr, actvcodes_t actvCode, Tensor_t *tensorArr[ANN_TENSOR_ARR_SIZE], cl_int tileSize);
cl_int rnn(cl_context c, cl_device_id d, kernel_ret_t *krnlRrtnPtr, actvcodes_t actvCode, Tensor_t *tensorArr[RNN_TENSOR_ARR_SIZE], cl_int tileSize);
cl_int vm(cl_context c, cl_device_id d, kernel_ret_t *krnlRrtnPtr, actvcodes_t actvCode, Tensor_t *tensorArr[VM_TENSOR_ARR_SIZE], cl_int tileSize);
cl_int mm(cl_context c, cl_device_id d, kernel_ret_t *krnlRrtnPtr, actvcodes_t actvCode, Tensor_t *tensorArr[MM_TENSOR_ARR_SIZE], cl_int tileSize);
cl_int start_kernel(cl_command_queue q, kernel_ret_t *krnlStructure);
cl_int device_mem_write(cl_command_queue q, Tensor_t *tensorPtr, int offset, int numElements, real_t initValue);
cl_int device_mem_copy(cl_command_queue q, Tensor_t *tensorPtr);
cl_int device_mem_read(cl_command_queue q, cl_mem buff, real_t *memPtr, const int rows, const int col, bool transpose);
cl_int clRefCountContext(cl_context c);
cl_int clRefCountCommandQueue(cl_command_queue q);
cl_int clRefCountDevice(cl_device_id d);
cl_int clRefCountProgram(cl_program p);
cl_int clRefCountMemObject(cl_mem m);
cl_int clRefCountEvent(cl_event e);
cl_int clRefCountKernel(cl_kernel k);

#define clRefCount(X) _Generic((X),           \
    cl_context: clRefCountContext,            \
    cl_command_queue: clRefCountCommandQueue, \
    cl_device_id: clRefCountDevice,           \
    cl_program: clRefCountProgram,            \
    cl_mem: clRefCountMemObject,              \
    cl_event: clRefCountEvent,                \
    cl_kernel: clRefCountKernel)((X))

#define clRelease(X) _Generic((X),           \
    cl_context: clReleaseContext,            \
    cl_command_queue: clReleaseCommandQueue, \
    cl_device_id: clReleaseDevice,           \
    cl_program: clReleaseProgram,            \
    cl_mem: clReleaseMemObject,              \
    cl_event: clReleaseEvent,                \
    cl_kernel: clReleaseKernel)((X))

#ifdef NO_PRINT_ERR
#define clCheckErr(ERROR_NO) ((void)0)
#else
#define clCheckErr(ERROR_NO, ERROR_MODE)                                       \
    {                                                                          \
        if ((ERROR_NO) != CL_SUCCESS || (ERROR_NO) < 0)                        \
        {                                                                      \
            printf("Err code: %d\n%s,(%d)\n", (ERROR_NO), __FILE__, __LINE__); \
            ERROR_MODE;                                                        \
        }                                                                      \
    }
#endif

#define printRefCount(REF_ARG)                                                                         \
    {                                                                                                  \
        printf("Ref Count of " #REF_ARG ": %d\n%s,(%d)\n", clRefCount((REF_ARG)), __FILE__, __LINE__); \
    }

#define device_mem_print(q, tensor)                                                                                            \
    {                                                                                                                          \
        printf("\n" #tensor "\n");                                                                                             \
        device_mem_read((q), (tensor).buff, (tensor).memmap, (tensor).dim[_ROW_], (tensor).dim[_COLUMN_], (tensor).transpose); \
    }

#endif // GPU_TOOLS_H
