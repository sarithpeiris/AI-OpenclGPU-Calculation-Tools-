
// Output = A * B + c
__kernel void _ANN_V00_(__global real_t* __Output, __constant real_t *__A, __constant real_t *__B, __constant real_t* __c){
  __local real_t sub__A[TILE][TILE];
  __local real_t sub__B[TILE][TILE];
  int gCol = get_global_id(1);
  int gRow = get_global_id(0);
  int lCol = get_local_id(1);
  int lRow = get_local_id(0);
  real_t sum = 0.0f;

  for(int i = 0, tx = 0; i <= __N__ / TILE; i++, tx = i * TILE)
  {
    load_mini_matrix_horizontal_2D(sub__A, __A, __N__, tx, __M__, gRow, lCol, lRow, tx);
    load_mini_matrix_vertical_2D(sub__B, __B, __K__, gCol, __N__, tx, lCol, lRow, tx);

    barrier(CLK_LOCAL_MEM_FENCE);
    mini_matrix_dot(sum, sub__A, sub__B, lCol, lRow, TILE);
    barrier(CLK_LOCAL_MEM_FENCE);

  }
  __Output[NDX2D(__K__, gRow, gCol)] = sum + __c[gCol];

}

// Output = A(t) * B + c
__kernel void _ANN_V10_(__global real_t* __Output, __constant real_t *__A, __constant real_t *__B, __constant real_t* __c){
  __local real_t sub__A[TILE][TILE];
  __local real_t sub__B[TILE][TILE];
  int gCol = get_global_id(1);
  int gRow = get_global_id(0);
  int lCol = get_local_id(1);
  int lRow = get_local_id(0);
  real_t sum = 0.0f;

  for(int i = 0, tx = 0; i <= __N__ / TILE; i++, tx = i * TILE)
  {
    load_mini_matrix_horizontal_2D_T(sub__A, __A, __N__, tx, __M__, gRow, lCol, lRow, tx);
    load_mini_matrix_vertical_2D(sub__B, __B, __K__, gCol, __N__, tx, lCol, lRow, tx);

    barrier(CLK_LOCAL_MEM_FENCE);
    mini_matrix_dot(sum, sub__A, sub__B, lCol, lRow, TILE);
    barrier(CLK_LOCAL_MEM_FENCE);

  }
  __Output[NDX2D(__K__, gRow, gCol)] = sum + __c[gCol];

}

// Output = A * B(t) + c
__kernel void _ANN_V20_(__global real_t* __Output, __constant real_t *__A, __constant real_t *__B, __constant real_t* __c){
  __local real_t sub__A[TILE][TILE];
  __local real_t sub__B[TILE][TILE];
  int gCol = get_global_id(1);
  int gRow = get_global_id(0);
  int lCol = get_local_id(1);
  int lRow = get_local_id(0);
  real_t sum = 0.0f;

  for(int i = 0, tx = 0; i <= __N__ / TILE; i++, tx = i * TILE)
  {
    load_mini_matrix_horizontal_2D(sub__A, __A, __N__, tx, __M__, gRow, lCol, lRow, tx);
    load_mini_matrix_vertical_2D_T(sub__B, __B, __K__, gCol, __N__, tx, lCol, lRow, tx);

    barrier(CLK_LOCAL_MEM_FENCE);
    mini_matrix_dot(sum, sub__A, sub__B, lCol, lRow, TILE);
    barrier(CLK_LOCAL_MEM_FENCE);

  }
  __Output[NDX2D(__K__, gRow, gCol)] = sum + __c[gCol];

}

// Output = A(t) * B(t) + c
__kernel void _ANN_V30_(__global real_t* __Output, __constant real_t *__A, __constant real_t *__B, __constant real_t* __c){
  __local real_t sub__A[TILE][TILE];
  __local real_t sub__B[TILE][TILE];
  int gCol = get_global_id(1);
  int gRow = get_global_id(0);
  int lCol = get_local_id(1);
  int lRow = get_local_id(0);
  real_t sum = 0.0f;

  for(int i = 0, tx = 0; i <= __N__ / TILE; i++, tx = i * TILE)
  {
    load_mini_matrix_horizontal_2D_T(sub__A, __A, __N__, tx, __M__, gRow, lCol, lRow, tx);
    load_mini_matrix_vertical_2D_T(sub__B, __B, __K__, gCol, __N__, tx, lCol, lRow, tx);

    barrier(CLK_LOCAL_MEM_FENCE);
    mini_matrix_dot(sum, sub__A, sub__B, lCol, lRow, TILE);
    barrier(CLK_LOCAL_MEM_FENCE);

  }
  __Output[NDX2D(__K__, gRow, gCol)] = sum + __c[gCol];

}