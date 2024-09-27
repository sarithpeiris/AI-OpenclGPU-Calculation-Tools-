
//////////////////////////////////////////////////////////////////////////////////////////////

// A[h + 1] = A[h] * B + C + d
__kernel void _RNN_V00_(__global real_t *__A, __constant real_t *__B, __constant real_t *__C, __constant real_t *__d) {

  if (get_global_id(0) >= __K__)
    return;

  __local real_t sub__a[TILE];
  __local real_t sub__B[TILE][TILE];
  int gId_x = get_global_id(0);
  int lId_x = get_local_id(0);
  real_t sum = 0.0f, value = 0.0f;

  barrier(CLK_LOCAL_MEM_FENCE);
  for (int rowNdx = 0; rowNdx < __M__ - 1; rowNdx++) {
    sum = 0.0f;
    for (int i = 0, tx = 0; i <= __N__ / TILE; i++, tx = i * TILE) {

      value = 0.0f;
      barrier(CLK_LOCAL_MEM_FENCE);
      load_horizontal_vector_stried(sub__a, __A, __N__, tx, __M__, rowNdx, tx);
      load_vertical_vector_stried(sub__B[lId_x], __B, __K__, gId_x, __N__, tx, tx);
      barrier(CLK_LOCAL_MEM_FENCE);

      barrier(CLK_LOCAL_MEM_FENCE);
      value = vector_dot(sub__a, sub__B[lId_x]);
      sum += value;
      barrier(CLK_LOCAL_MEM_FENCE);

      barrier(CLK_LOCAL_MEM_FENCE);
      __A[NDX2D(__K__, rowNdx + 1, gId_x)] = sum + __C[NDX2D(__K__, rowNdx, gId_x)] + __d[gId_x];
      barrier(CLK_LOCAL_MEM_FENCE);
    }
  }
  barrier(CLK_LOCAL_MEM_FENCE);
}

// A[h + 1] = A[h](t) * B + C + d
__kernel void _RNN_V10_(__global real_t *__A, __constant real_t *__B, __constant real_t *__C, __constant real_t *__d) {

  if (get_global_id(0) >= __K__)
    return;

  __local real_t sub__a[TILE];
  __local real_t sub__B[TILE][TILE];
  int gId_x = get_global_id(0);
  int lId_x = get_local_id(0);
  real_t sum = 0.0f, value = 0.0f;

  barrier(CLK_LOCAL_MEM_FENCE);
  for (int rowNdx = 0; rowNdx < __M__ - 1; rowNdx++) {
    sum = 0.0f;
    for (int i = 0, tx = 0; i <= __N__ / TILE; i++, tx = i * TILE) {

      value = 0.0f;
      barrier(CLK_LOCAL_MEM_FENCE);
      load_horizontal_vector_stried(sub__a, __A, __N__, tx, __M__, rowNdx, tx);
      load_vertical_vector_stried(sub__B[lId_x], __B, __K__, gId_x, __N__, tx, tx);
      barrier(CLK_LOCAL_MEM_FENCE);

      barrier(CLK_LOCAL_MEM_FENCE);
      value = vector_dot(sub__a, sub__B[lId_x]);
      sum += value;
      barrier(CLK_LOCAL_MEM_FENCE);

      barrier(CLK_LOCAL_MEM_FENCE);
      __A[NDX2DT(__K__, rowNdx + 1, gId_x)] = sum + __C[NDX2D(__K__, rowNdx, gId_x)] + __d[gId_x];
      barrier(CLK_LOCAL_MEM_FENCE);
    }
  }
  barrier(CLK_LOCAL_MEM_FENCE);
}

// A[h + 1] = A[h] * B(t) + C + d
__kernel void _RNN_V20_(__global real_t *__A, __constant real_t *__B, __constant real_t *__C, __constant real_t *__d) {

  if (get_global_id(0) >= __K__)
    return;

  __local real_t sub__a[TILE];
  __local real_t sub__B[TILE][TILE];
  int gId_x = get_global_id(0);
  int lId_x = get_local_id(0);
  real_t sum = 0.0f, value = 0.0f;

  barrier(CLK_LOCAL_MEM_FENCE);
  for (int rowNdx = 0; rowNdx < __M__ - 1; rowNdx++) {
    sum = 0.0f;
    for (int i = 0, tx = 0; i <= __N__ / TILE; i++, tx = i * TILE) {

      value = 0.0f;
      barrier(CLK_LOCAL_MEM_FENCE);
      load_horizontal_vector_stried(sub__a, __A, __N__, tx, __M__, rowNdx, tx);
      load_vertical_vector_stried(sub__B[lId_x], __B, __K__, gId_x, __N__, tx, tx);
      barrier(CLK_LOCAL_MEM_FENCE);

      barrier(CLK_LOCAL_MEM_FENCE);
      value = vector_dot(sub__a, sub__B[lId_x]);
      sum += value;
      barrier(CLK_LOCAL_MEM_FENCE);

      barrier(CLK_LOCAL_MEM_FENCE);
      __A[NDX2D(__K__, rowNdx + 1, gId_x)] = sum + __C[NDX2D(__K__, rowNdx, gId_x)] + __d[gId_x];
      barrier(CLK_LOCAL_MEM_FENCE);
    }
  }
  barrier(CLK_LOCAL_MEM_FENCE);
}

// A[h + 1] = A[h](t) * B(t) + C + d
__kernel void _RNN_V30_(__global real_t *__A, __constant real_t *__B, __constant real_t *__C, __constant real_t *__d) {

  if (get_global_id(0) >= __K__)
    return;

  __local real_t sub__a[TILE];
  __local real_t sub__B[TILE][TILE];
  int gId_x = get_global_id(0);
  int lId_x = get_local_id(0);
  real_t sum = 0.0f, value = 0.0f;

  barrier(CLK_LOCAL_MEM_FENCE);
  for (int rowNdx = 0; rowNdx < __M__ - 1; rowNdx++) {
    sum = 0.0f;
    for (int i = 0, tx = 0; i <= __N__ / TILE; i++, tx = i * TILE) {

      value = 0.0f;
      barrier(CLK_LOCAL_MEM_FENCE);
      load_horizontal_vector_stried(sub__a, __A, __N__, tx, __M__, rowNdx, tx);
      load_vertical_vector_stried(sub__B[lId_x], __B, __K__, gId_x, __N__, tx, tx);
      barrier(CLK_LOCAL_MEM_FENCE);

      barrier(CLK_LOCAL_MEM_FENCE);
      value = vector_dot(sub__a, sub__B[lId_x]);
      sum += value;
      barrier(CLK_LOCAL_MEM_FENCE);

      barrier(CLK_LOCAL_MEM_FENCE);
      __A[NDX2DT(__K__, rowNdx + 1, gId_x)] = sum + __C[NDX2D(__K__, rowNdx, gId_x)] + __d[gId_x];
      barrier(CLK_LOCAL_MEM_FENCE);
    }
  }
  barrier(CLK_LOCAL_MEM_FENCE);
}

//////////////////////////////////////////////////////////////////////////


