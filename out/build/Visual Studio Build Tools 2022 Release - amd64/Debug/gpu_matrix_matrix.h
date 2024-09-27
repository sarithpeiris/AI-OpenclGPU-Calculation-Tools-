#ifndef GPU_MATRIX_MATRIX_H
#define GPU_MATRIX_MATRIX_H

#define load_mini_matrix_horizontal_2D(__DST__, __SRC__, __SRC_COLSIZE__, __SRC_COLNDX__, __SRC_ROWSIZE__, __SRC_ROWNDX__, __SRC_LOCAL_COLNDX__, __SRC_LOCAL_ROWNDX__, __BLOCK__)                                                                                              \
    {                                                                                                                                                                                                                                                                          \
        (__DST__)[(__SRC_LOCAL_ROWNDX__)][(__SRC_LOCAL_COLNDX__)] = ((__BLOCK__) + (__SRC_LOCAL_COLNDX__) < (__SRC_COLSIZE__) && (__SRC_ROWNDX__) < (__SRC_ROWSIZE__)) ? (__SRC__)[(NDX2D((__SRC_COLSIZE__), (__SRC_ROWNDX__), (__BLOCK__) + (__SRC_LOCAL_COLNDX__)))] : 0.0f; \
    }

#define load_mini_matrix_vertical_2D(__DST__, __SRC__, __SRC_COLSIZE__, __SRC_COLNDX__, __SRC_ROWSIZE__, __SRC_ROWNDX__, __SRC_LOCAL_COLNDX__, __SRC_LOCAL_ROWNDX__, __BLOCK__)                                                                                                \
    {                                                                                                                                                                                                                                                                          \
        (__DST__)[(__SRC_LOCAL_ROWNDX__)][(__SRC_LOCAL_COLNDX__)] = ((__BLOCK__) + (__SRC_LOCAL_ROWNDX__) < (__SRC_ROWSIZE__) && (__SRC_COLNDX__) < (__SRC_COLSIZE__)) ? (__SRC__)[(NDX2D((__SRC_COLSIZE__), (__BLOCK__) + (__SRC_LOCAL_ROWNDX__), (__SRC_COLNDX__)))] : 0.0f; \
    }

#endif // GPU_MATRIX_MATRIX_H
