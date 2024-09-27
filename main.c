#include "neuralnetwork.h"

// test mm and ann OK!
/*
#define M 4
#define N 5
#define K 3

int main(void)
{
    cl_int err = 0;
    cl_device_id d = create_device(0, 0, &err);
    clCheckErr(err, exit(err));

    cl_context c = clCreateContext(NULL, 1, &d, NULL, NULL, &err);
    clCheckErr(err, exit(err));

    cl_command_queue q = clCreateCommandQueue(c, d, 0, &err);
    clCheckErr(err, exit(err));

    Tensor_t *A = tensor_shape(c, M, N);
    Tensor_t *B = tensor_shape(c, N, K);
    Tensor_t *Output = tensor_shape(c, M, K);

    err = device_mem_write(q, A, 0, A->elements, 0.2f);
    clCheckErr(err, exit(err));
    err = device_mem_write(q, B, 0, B->elements, 0.7f);
    clCheckErr(err, exit(err));

    kernel_ret_t krnl = {0};
    err = mm(c, d, &krnl, _TANH_, (Tensor_t *[]){Output, A, B}, TILE_2);
    clCheckErr(err, exit(err));

    for (int i = 0; i < 2; i++)
    {
        printf("Iteration: %d\n", i);
        err = clEnqueueNDRangeKernel(
            q,
            krnl.k,
            krnl.dim,
            NULL,
            krnl.gW,
            krnl.lW,
            0,
            NULL,
            NULL);
        clCheckErr(err, exit(err));

        err = clFinish(q);
        clCheckErr(err, exit(err));

        device_mem_print(q, *krnl.output);

        err = device_mem_write(q, B, 0, B->elements, 2.7f);
        clCheckErr(err, exit(err));
    }

    printRefCount(c);
    printRefCount(d);
    printRefCount(q);
    printRefCount(krnl.k);
    printRefCount(A->buff);
    printRefCount(B->buff);
    printRefCount(Output->buff);

    // Release Host memory objects
    mem_deallocate(A);
    mem_deallocate(B);
    mem_deallocate(Output);

    // Release OpenCL working objects.
    clRelease(krnl.k);
    clRelease(q);
    clRelease(d);
    clRelease(c);

    // Release Host working objects
    free(device->devs);
    free(device);

    puts("OK");
    _CrtDumpMemoryLeaks();

    return 0;
}
 */

// test vm OK!
/*
#define M 1
#define N 3
#define K 3

#define TILE 2

int main(void)
{
    cl_int err = 0;
    cl_device_id d = create_device(0, 0, &err);
    clCheckErr(err, exit(err));

    cl_context c = clCreateContext(NULL, 1, &d, NULL, NULL, &err);
    clCheckErr(err, exit(err));

    cl_command_queue q = clCreateCommandQueue(c, d, 0, &err);
    clCheckErr(err, exit(err));

    Tensor_t *A = tensor_shape(c, M, K);
    Tensor_t *B = tensor_shape(c, K, K);
    Tensor_t *Output = tensor_shape(c, M, K);

    err = device_mem_write(q, A, 0, A->elements, 0.2f);
    clCheckErr(err, exit(err));
    err = device_mem_write(q, B, 0, B->elements, 0.7f);
    clCheckErr(err, exit(err));

    // A.transpose = true;
    //  B.transpose = true;
    kernel_ret_t krnl = {0};
    err = vm(c, d, &krnl, _TANH_, (Tensor_t *[]){Output, A, B}, TILE_2);
    clCheckErr(err, exit(err));

    for (int i = 0; i < 1; i++)
    {
        printf("Iteration: %d\n", i);
        err = clEnqueueNDRangeKernel(
            q,
            krnl.k,
            krnl.dim,
            NULL,
            krnl.gW,
            krnl.lW,
            0,
            NULL,
            NULL);
        clCheckErr(err, exit(err));

        err = clFinish(q);
        clCheckErr(err, exit(err));

        device_mem_print(q, *krnl.output);

        err = device_mem_write(q, B, 0, B->elements, 2.7f);
        clCheckErr(err, exit(err));
    }

    printRefCount(c);
    printRefCount(d);
    printRefCount(q);
    printRefCount(krnl.k);
    printRefCount(A->buff);
    printRefCount(B->buff);
    printRefCount(Output->buff);

    // Release OpenCL working objects.
    clRelease(krnl.k);
    clRelease(q);
    clRelease(d);
    clRelease(c);

    // Release Host memory objects
    mem_deallocate(A);
    mem_deallocate(B);
    mem_deallocate(Output);

    // Release Host working objects
    free(device->devs);
    free(device);

    puts("OK");
    _CrtDumpMemoryLeaks();

    return 0;
}
 */

// test rnn OK!
/*
#define M 3
#define N 5
#define K 3

#define TILE 2

int main(void)
{
    cl_int err = 0;
    cl_device_id d = create_device(0, 0, &err);
    clCheckErr(err, exit(err));

    cl_context c = clCreateContext(NULL, 1, &d, NULL, NULL, &err);
    clCheckErr(err, exit(err));

    cl_command_queue q = clCreateCommandQueue(c, d, 0, &err);
    clCheckErr(err, exit(err));

    Tensor_t *A = tensor_shape(c, M + 1, K);
    Tensor_t *B = tensor_shape(c, K, K);
    Tensor_t *C = tensor_shape(c, M, N);
    Tensor_t *D = tensor_shape(c, N, K);
    Tensor_t *e = tensor_shape(c, 1, K);

    err = device_mem_write(q, A, 0, K, 0.7f);
    clCheckErr(err, exit(err));
    err = device_mem_write(q, B, 0, B->elements, 1.7f);
    clCheckErr(err, exit(err));
    err = device_mem_write(q, C, 0, C->elements, 2.7f);
    clCheckErr(err, exit(err));
    err = device_mem_write(q, D, 0, D->elements, 3.7f);
    clCheckErr(err, exit(err));
    err = device_mem_write(q, e, 0, e->elements, 4.7f);
    clCheckErr(err, exit(err));

    // A.transpose = true;
    // B.transpose = true;
    kernel_ret_t krnl[2] = {0};
    err = rnn(c, d, krnl, _TANH_, (Tensor_t *[]){A, B, C, D, e}, TILE_2);
    clCheckErr(err, exit(err));

    for (int i = 0; i < 1; i++)
    {
        printf("Iteration: %d\n", i);
        err = clEnqueueNDRangeKernel(
            q,
            krnl[0].k,
            krnl[0].dim,
            NULL,
            krnl[0].gW,
            krnl[0].lW,
            0,
            NULL,
            NULL);
        clCheckErr(err, exit(err));

        err = clFinish(q);
        clCheckErr(err, exit(err));

        device_mem_print(q, *krnl[0].output);

        err = clEnqueueNDRangeKernel(
            q,
            krnl[1].k,
            krnl[1].dim,
            NULL,
            krnl[1].gW,
            krnl[1].lW,
            0,
            NULL,
            NULL);
        clCheckErr(err, exit(err));

        err = clFinish(q);
        clCheckErr(err, exit(err));

        device_mem_print(q, *krnl[1].output);

        // err = device_mem_write(q, &B, 0, B->elements, 2.7f);
        // clCheckErr(err, exit(err));
    }

    printRefCount(c);
    printRefCount(d);
    printRefCount(q);
    printRefCount(krnl[0].k);
    printRefCount(krnl[1].k);
    printRefCount(A->buff);
    printRefCount(B->buff);

    // Release OpenCL working objects.
    clRelease(krnl[0].k);
    clRelease(krnl[1].k);
    clRelease(q);
    clRelease(d);
    clRelease(c);

    // Release Host memory objects
    mem_deallocate(krnl[0].output);
    mem_deallocate(krnl[1].output);
    mem_deallocate(B);
    mem_deallocate(C);
    mem_deallocate(D);
    mem_deallocate(e);

    // Release Host working objects
    free(device->devs);
    free(device);

    puts("OK");
    _CrtDumpMemoryLeaks();

    return 0;
}
 */


