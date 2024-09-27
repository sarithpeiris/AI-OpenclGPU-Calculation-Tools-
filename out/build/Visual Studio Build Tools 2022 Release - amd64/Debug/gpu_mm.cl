
// Output = A * B
__kernel void _MM_V00_(__global real_t* __Output, __constant real_t *__A, __constant real_t *__B){
  

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

  if(gRow < __M__ && gCol < __K__)
      __Output[NDX2D(__K__, gRow, gCol)] = sum;
}

// Output = A(t) * B
__kernel void _MM_V10_(__global real_t* __Output, __constant real_t *__A, __constant real_t *__B){
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

  if(gRow < __M__ && gCol < __K__)
      __Output[NDX2D(__K__, gRow, gCol)] = sum;
}

// Output = A * B(t)
__kernel void _MM_V20_(__global real_t* __Output, __constant real_t *__A, __constant real_t *__B){
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

  if(gRow < __M__ && gCol < __K__)
      __Output[NDX2D(__K__, gRow, gCol)] = sum;

}

// Output = A(t) * B(t)
__kernel void _MM_V30_(__global real_t* __Output, __constant real_t *__A, __constant real_t *__B){
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

  if(gRow < __M__ && gCol < __K__)
      __Output[NDX2D(__K__, gRow, gCol)] = sum;

}

