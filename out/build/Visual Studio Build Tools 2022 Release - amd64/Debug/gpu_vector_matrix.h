#ifndef GPU_VECTOR_MATRIX_H
#define GPU_VECTOR_MATRIX_H

#define load_vertical_vector_stried_16(__DST__, __SRC__, __COLSIZE__, __COLNDX__, __ROWSIZE__, __ROWNDX__, __BLOCK__)                 \
    {                                                                                                                                 \
        (__DST__)[0] = ((__BLOCK__) + 0 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 0, (__COLNDX__))];    \
        print_line((__DST__)[0]);                                                                                                     \
        (__DST__)[1] = ((__BLOCK__) + 1 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 1, (__COLNDX__))];    \
        print_line((__DST__)[1]);                                                                                                     \
        (__DST__)[2] = ((__BLOCK__) + 2 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 2, (__COLNDX__))];    \
        print_line((__DST__)[2]);                                                                                                     \
        (__DST__)[3] = ((__BLOCK__) + 3 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 3, (__COLNDX__))];    \
        print_line((__DST__)[3]);                                                                                                     \
        (__DST__)[4] = ((__BLOCK__) + 4 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 4, (__COLNDX__))];    \
        print_line((__DST__)[4]);                                                                                                     \
        (__DST__)[5] = ((__BLOCK__) + 5 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 5, (__COLNDX__))];    \
        print_line((__DST__)[5]);                                                                                                     \
        (__DST__)[6] = ((__BLOCK__) + 6 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 6, (__COLNDX__))];    \
        print_line((__DST__)[6]);                                                                                                     \
        (__DST__)[7] = ((__BLOCK__) + 7 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 7, (__COLNDX__))];    \
        print_line((__DST__)[7]);                                                                                                     \
        (__DST__)[8] = ((__BLOCK__) + 8 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 8, (__COLNDX__))];    \
        print_line((__DST__)[8]);                                                                                                     \
        (__DST__)[9] = ((__BLOCK__) + 9 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 9, (__COLNDX__))];    \
        print_line((__DST__)[9]);                                                                                                     \
        (__DST__)[10] = ((__BLOCK__) + 10 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 10, (__COLNDX__))]; \
        print_line((__DST__)[10]);                                                                                                    \
        (__DST__)[11] = ((__BLOCK__) + 11 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 11, (__COLNDX__))]; \
        print_line((__DST__)[11]);                                                                                                    \
        (__DST__)[12] = ((__BLOCK__) + 12 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 12, (__COLNDX__))]; \
        print_line((__DST__)[12]);                                                                                                    \
        (__DST__)[13] = ((__BLOCK__) + 13 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 13, (__COLNDX__))]; \
        print_line((__DST__)[13]);                                                                                                    \
        (__DST__)[14] = ((__BLOCK__) + 14 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 14, (__COLNDX__))]; \
        print_line((__DST__)[14]);                                                                                                    \
        (__DST__)[15] = ((__BLOCK__) + 15 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 15, (__COLNDX__))]; \
        print_line((__DST__)[15]);                                                                                                    \
    }

#define load_horizontal_vector_stried_16(__DST__, __SRC__, __COLSIZE__, __COLNDX__, __ROWSIZE__, __ROWNDX__, __BLOCK__)               \
    {                                                                                                                                 \
        (__DST__)[0] = ((__BLOCK__) + 0 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 0)];    \
        print_line((__DST__)[0]);                                                                                                     \
        (__DST__)[1] = ((__BLOCK__) + 1 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 1)];    \
        print_line((__DST__)[1]);                                                                                                     \
        (__DST__)[2] = ((__BLOCK__) + 2 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 2)];    \
        print_line((__DST__)[2]);                                                                                                     \
        (__DST__)[3] = ((__BLOCK__) + 3 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 3)];    \
        print_line((__DST__)[3]);                                                                                                     \
        (__DST__)[4] = ((__BLOCK__) + 4 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 4)];    \
        print_line((__DST__)[4]);                                                                                                     \
        (__DST__)[5] = ((__BLOCK__) + 5 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 5)];    \
        print_line((__DST__)[5]);                                                                                                     \
        (__DST__)[6] = ((__BLOCK__) + 6 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 6)];    \
        print_line((__DST__)[6]);                                                                                                     \
        (__DST__)[7] = ((__BLOCK__) + 7 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 7)];    \
        print_line((__DST__)[7]);                                                                                                     \
        (__DST__)[8] = ((__BLOCK__) + 8 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 8)];    \
        print_line((__DST__)[8]);                                                                                                     \
        (__DST__)[9] = ((__BLOCK__) + 9 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 9)];    \
        print_line((__DST__)[9]);                                                                                                     \
        (__DST__)[10] = ((__BLOCK__) + 10 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 10)]; \
        print_line((__DST__)[10]);                                                                                                    \
        (__DST__)[11] = ((__BLOCK__) + 11 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 11)]; \
        print_line((__DST__)[11]);                                                                                                    \
        (__DST__)[12] = ((__BLOCK__) + 12 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 12)]; \
        print_line((__DST__)[12]);                                                                                                    \
        (__DST__)[13] = ((__BLOCK__) + 13 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 13)]; \
        print_line((__DST__)[13]);                                                                                                    \
        (__DST__)[14] = ((__BLOCK__) + 14 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 14)]; \
        print_line((__DST__)[14]);                                                                                                    \
        (__DST__)[15] = ((__BLOCK__) + 15 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 15)]; \
        print_line((__DST__)[15]);                                                                                                    \
    }

#define load_vertical_vector_stried_8(__DST__, __SRC__, __COLSIZE__, __COLNDX__, __ROWSIZE__, __ROWNDX__, __BLOCK__)               \
    {                                                                                                                              \
                                                                                                                                   \
        (__DST__)[0] = ((__BLOCK__) + 0 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 0, (__COLNDX__))]; \
        print_line((__DST__)[0]);                                                                                                  \
        (__DST__)[1] = ((__BLOCK__) + 1 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 1, (__COLNDX__))]; \
        print_line((__DST__)[1]);                                                                                                  \
        (__DST__)[2] = ((__BLOCK__) + 2 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 2, (__COLNDX__))]; \
        print_line((__DST__)[2]);                                                                                                  \
        (__DST__)[3] = ((__BLOCK__) + 3 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 3, (__COLNDX__))]; \
        print_line((__DST__)[3]);                                                                                                  \
        (__DST__)[4] = ((__BLOCK__) + 4 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 4, (__COLNDX__))]; \
        print_line((__DST__)[4]);                                                                                                  \
        (__DST__)[5] = ((__BLOCK__) + 5 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 5, (__COLNDX__))]; \
        print_line((__DST__)[5]);                                                                                                  \
        (__DST__)[6] = ((__BLOCK__) + 6 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 6, (__COLNDX__))]; \
        print_line((__DST__)[6]);                                                                                                  \
        (__DST__)[7] = ((__BLOCK__) + 7 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 7, (__COLNDX__))]; \
        print_line((__DST__)[7]);                                                                                                  \
    }

#define load_horizontal_vector_stried_8(__DST__, __SRC__, __COLSIZE__, __COLNDX__, __ROWSIZE__, __ROWNDX__, __BLOCK__)             \
    {                                                                                                                              \
                                                                                                                                   \
        (__DST__)[0] = ((__BLOCK__) + 0 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 0)]; \
        print_line((__DST__)[0]);                                                                                                  \
        (__DST__)[1] = ((__BLOCK__) + 1 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 1)]; \
        print_line((__DST__)[1]);                                                                                                  \
        (__DST__)[2] = ((__BLOCK__) + 2 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 2)]; \
        print_line((__DST__)[2]);                                                                                                  \
        (__DST__)[3] = ((__BLOCK__) + 3 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 3)]; \
        print_line((__DST__)[3]);                                                                                                  \
        (__DST__)[4] = ((__BLOCK__) + 4 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 4)]; \
        print_line((__DST__)[4]);                                                                                                  \
        (__DST__)[5] = ((__BLOCK__) + 5 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 5)]; \
        print_line((__DST__)[5]);                                                                                                  \
        (__DST__)[6] = ((__BLOCK__) + 6 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 6)]; \
        print_line((__DST__)[6]);                                                                                                  \
        (__DST__)[7] = ((__BLOCK__) + 7 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 7)]; \
        print_line((__DST__)[7]);                                                                                                  \
    }

#define load_vertical_vector_stried_4(__DST__, __SRC__, __COLSIZE__, __COLNDX__, __ROWSIZE__, __ROWNDX__, __BLOCK__)               \
    {                                                                                                                              \
                                                                                                                                   \
        (__DST__)[0] = ((__BLOCK__) + 0 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 0, (__COLNDX__))]; \
        print_line((__DST__)[0]);                                                                                                  \
        (__DST__)[1] = ((__BLOCK__) + 1 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 1, (__COLNDX__))]; \
        print_line((__DST__)[1]);                                                                                                  \
        (__DST__)[2] = ((__BLOCK__) + 2 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 2, (__COLNDX__))]; \
        print_line((__DST__)[2]);                                                                                                  \
        (__DST__)[3] = ((__BLOCK__) + 3 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 3, (__COLNDX__))]; \
        print_line((__DST__)[3]);                                                                                                  \
    }

#define load_horizontal_vector_stried_4(__DST__, __SRC__, __COLSIZE__, __COLNDX__, __ROWSIZE__, __ROWNDX__, __BLOCK__)             \
    {                                                                                                                              \
                                                                                                                                   \
        (__DST__)[0] = ((__BLOCK__) + 0 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 0)]; \
        print_line((__DST__)[0]);                                                                                                  \
        (__DST__)[1] = ((__BLOCK__) + 1 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 1)]; \
        print_line((__DST__)[1]);                                                                                                  \
        (__DST__)[2] = ((__BLOCK__) + 2 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 2)]; \
        print_line((__DST__)[2]);                                                                                                  \
        (__DST__)[3] = ((__BLOCK__) + 3 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 3)]; \
        print_line((__DST__)[3]);                                                                                                  \
    }

#define load_vertical_vector_stried_2(__DST__, __SRC__, __COLSIZE__, __COLNDX__, __ROWSIZE__, __ROWNDX__, __BLOCK__)               \
    {                                                                                                                              \
                                                                                                                                   \
        (__DST__)[0] = ((__BLOCK__) + 0 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 0, (__COLNDX__))]; \
        print_line((__DST__)[0]);                                                                                                  \
        (__DST__)[1] = ((__BLOCK__) + 1 >= (__ROWSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__BLOCK__) + 1, (__COLNDX__))]; \
        print_line((__DST__)[1]);                                                                                                  \
    }

#define load_horizontal_vector_stried_2(__DST__, __SRC__, __COLSIZE__, __COLNDX__, __ROWSIZE__, __ROWNDX__, __BLOCK__)             \
    {                                                                                                                              \
                                                                                                                                   \
        (__DST__)[0] = ((__BLOCK__) + 0 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 0)]; \
        print_line((__DST__)[0]);                                                                                                  \
        (__DST__)[1] = ((__BLOCK__) + 1 >= (__COLSIZE__)) ? 0.0f : (__SRC__)[NDX2D((__COLSIZE__), (__ROWNDX__), (__BLOCK__) + 1)]; \
        print_line((__DST__)[1]);                                                                                                  \
    }

#if TILE == 16
#define load_vertical_vector_stried(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__) \
    load_vertical_vector_stried_16(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__);
#define load_horizontal_vector_stried(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__) \
    load_horizontal_vector_stried_16(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__);

#elif TILE == 8
#define load_vertical_vector_stried(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__) \
    load_vertical_vector_stried_8(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__);
#define load_horizontal_vector_stried(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__) \
    load_horizontal_vector_stried_8(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__);

#elif TILE == 4
#define load_vertical_vector_stried(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__) \
    load_vertical_vector_stried_4(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__);
#define load_horizontal_vector_stried(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__) \
    load_horizontal_vector_stried_4(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__);

#elif TILE == 2
#define load_vertical_vector_stried(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__) \
    load_vertical_vector_stried_2(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__);
#define load_horizontal_vector_stried(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__) \
    load_horizontal_vector_stried_2(__DST__, __SRC__, __SRC_COL_SIZE__, __SRC_COL_NDX__, __SRC_ROW_SIZE__, __SRC_ROW_NDX__, __BLOCK__);
#endif

#endif // GPU_VECTOR_MATRIX_H
