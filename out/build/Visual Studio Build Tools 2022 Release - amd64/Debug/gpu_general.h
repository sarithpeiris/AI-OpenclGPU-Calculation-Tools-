#ifndef GPU_GENERAL_H
#define GPU_GENERAL_H

#define real_t float
#define NDX2D(COLSIZE, rowNdx, colNdx) (((COLSIZE) * (rowNdx)) + (colNdx))
#define NDX2DT(ROWSIZE, rowNdx, colNdx) (((ROWSIZE) * (colNdx)) + (rowNdx))

#ifdef PRINT_ELEMENT
#define print_line(name) printf("" #name ":%f\n", name)
#else
#define print_line(name) ((void)0)
#endif

#define vector_dot_16(__a__, __b__)                                                                                      \
    (((__a__)[0] * (__b__)[0]) + ((__a__)[1] * (__b__)[1]) + ((__a__)[2] * (__b__)[2]) + ((__a__)[3] * (__b__)[3]) +     \
     ((__a__)[4] * (__b__)[4]) + ((__a__)[5] * (__b__)[5]) + ((__a__)[6] * (__b__)[6]) + ((__a__)[7] * (__b__)[7]) +     \
     ((__a__)[8] * (__b__)[8]) + ((__a__)[9] * (__b__)[9]) + ((__a__)[10] * (__b__)[10]) + ((__a__)[11] * (__b__)[11]) + \
     ((__a__)[12] * (__b__)[12]) + ((__a__)[13] * (__b__)[13]) + ((__a__)[14] * (__b__)[14]) + ((__a__)[15] * (__b__)[15]));
#define vector_dot_8(__a__, __b__)                                                                                   \
    (((__a__)[0] * (__b__)[0]) + ((__a__)[1] * (__b__)[1]) + ((__a__)[2] * (__b__)[2]) + ((__a__)[3] * (__b__)[3]) + \
     ((__a__)[4] * (__b__)[4]) + ((__a__)[5] * (__b__)[5]) + ((__a__)[6] * (__b__)[6]) + ((__a__)[7] * (__b__)[7]));
#define vector_dot_4(__a__, __b__) \
    (((__a__)[0] * (__b__)[0]) + ((__a__)[1] * (__b__)[1]) + ((__a__)[2] * (__b__)[2]) + ((__a__)[3] * (__b__)[3]));
#define vector_dot_2(__a__, __b__) \
    (((__a__)[0] * (__b__)[0]) + ((__a__)[1] * (__b__)[1]));

#if TILE == 16
#define vector_dot(__A__, __B__) vector_dot_16(__A__, __B__);
#elif TILE == 8
#define vector_dot(__A__, __B__) vector_dot_8(__A__, __B__);
#elif TILE == 4
#define vector_dot(__A__, __B__) vector_dot_4(__A__, __B__);
#elif TILE == 2
#define vector_dot(__A__, __B__) vector_dot_2(__A__, __B__);
#endif

#define mini_matrix_dot(SUM, __A__, __B__, __LOCAL_COLNDX__, __LOCAL_ROWNDX__, BLOCK_SIZE)                        \
    {                                                                                                           \
        for (int _matrix_dot_i_ = 0; _matrix_dot_i_ < (BLOCK_SIZE); _matrix_dot_i_++)                           \
        {                                                                                                       \
            (SUM) += (__A__)[(__LOCAL_ROWNDX__)][_matrix_dot_i_] * (__B__)[_matrix_dot_i_][(__LOCAL_COLNDX__)]; \
        }                                                                                                       \
    }

#endif // GPU_GENERAL_H
