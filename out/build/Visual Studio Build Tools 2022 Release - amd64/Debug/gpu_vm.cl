
// Output = a * B
__kernel void _VM_V00_(__global real_t* __Output, __constant real_t *__a, __constant real_t *__B){
  
  __local real_t sub__a[TILE];
  __local real_t sub__B[TILE][TILE];
  int gId_x = get_global_id(0);
  int lId_x = get_local_id(0);
  real_t sum = 0.0f;

  for(int i = 0, tx = 0; i <= __N__ / TILE; i++, tx = i * TILE)
  {
    barrier(CLK_LOCAL_MEM_FENCE);
    load_horizontal_vector_stried(sub__a, __a, __N__, tx, __M__, 0, tx);
    load_vertical_vector_stried(sub__B[lId_x], __B, __K__, gId_x, __N__, tx, tx);


    barrier(CLK_LOCAL_MEM_FENCE);
    sum += vector_dot(sub__a, sub__B[lId_x]);

  }
  __Output[NDX2D(__K__, 0, gId_x)] = sum;

}

// Output = a(t) * B
__kernel void _VM_V10_(__global real_t* __Output, __constant real_t *__a, __constant real_t *__B){
  
  
  __local real_t sub__a[TILE];
  __local real_t sub__B[TILE][TILE];
  int gId_x = get_global_id(0);
  int lId_x = get_local_id(0);
  real_t sum = 0.0f;

  for(int i = 0, tx = 0; i <= __N__ / TILE; i++, tx = i * TILE)
  {
    barrier(CLK_LOCAL_MEM_FENCE);
    load_horizontal_vector_stried_T(sub__a, __a, __N__, tx, __M__, 0, tx);
    load_vertical_vector_stried(sub__B[lId_x], __B, __K__, gId_x, __N__, tx, tx);


    barrier(CLK_LOCAL_MEM_FENCE);
    sum += vector_dot(sub__a, sub__B[lId_x]);

  }

  __Output[NDX2D(__K__, 0, gId_x)] = sum;

}

// Output = a * B(t)
__kernel void _VM_V20_(__global real_t* __Output, __constant real_t *__a, __constant real_t *__B){
  
  
  __local real_t sub__a[TILE];
  __local real_t sub__B[TILE][TILE];
  int gId_x = get_global_id(0);
  int lId_x = get_local_id(0);
  real_t sum = 0.0f;

  for(int i = 0, tx = 0; i <= __N__ / TILE; i++, tx = i * TILE)
  {
    barrier(CLK_LOCAL_MEM_FENCE);
    load_horizontal_vector_stried(sub__a, __a, __N__, tx, __M__, 0, tx);
    load_vertical_vector_stried_T(sub__B[lId_x], __B, __K__, gId_x, __N__, tx, tx);


    barrier(CLK_LOCAL_MEM_FENCE);
    sum += vector_dot(sub__a, sub__B[lId_x]);

  }

  __Output[NDX2D(__K__, 0, gId_x)] = sum;

}

// Output = a(t) * B(t)
__kernel void _VM_V30_(__global real_t* __Output, __constant real_t *__a, __constant real_t *__B){
  
  
  __local real_t sub__a[TILE];
  __local real_t sub__B[TILE][TILE];
  int gId_x = get_global_id(0);
  int lId_x = get_local_id(0);
  real_t sum = 0.0f;

  for(int i = 0, tx = 0; i <= __N__ / TILE; i++, tx = i * TILE)
  {
    barrier(CLK_LOCAL_MEM_FENCE);
    load_horizontal_vector_stried_T(sub__a, __a, __N__, tx, __M__, 0, tx);
    load_vertical_vector_stried_T(sub__B[lId_x], __B, __K__, gId_x, __N__, tx, tx);


    barrier(CLK_LOCAL_MEM_FENCE);
    sum += vector_dot(sub__a, sub__B[lId_x]);

  }

  __Output[NDX2D(__K__, 0, gId_x)] = sum;

}