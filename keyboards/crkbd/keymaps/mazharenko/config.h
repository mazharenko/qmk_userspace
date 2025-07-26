#pragma once

#define SPLIT_LAYER_STATE_ENABLE
#define PERMISSIVE_HOLD
#define FLOW_TAP_TERM 150
#define MAX_DEFERRED_EXECUTORS 10
#define RGB_MATRIX_VAL_STEP 4
#define RGB_MATRIX_HUE_STEP 4


/**/
/*
#define LAYOUT_split_3x6_3_ex2_rgb(k0A_r, k0A_g, k0A_b, \
 k0B_r, k0B_g, k0B_b, \
 k0C_r, k0C_g, k0C_b, \
 k0D_r, k0D_g, k0D_b, \
 k0E_r, k0E_g, k0E_b, \
 k0F_r, k0F_g, k0F_b, \
 k0G_r, k0G_g, k0G_b, \
 k4G_r, k4G_g, k4G_b, \
 k4F_r, k4F_g, k4F_b, \
 k4E_r, k4E_g, k4E_b, \
 k4D_r, k4D_g, k4D_b, \
 k4C_r, k4C_g, k4C_b, \
 k4B_r, k4B_g, k4B_b, \
 k4A_r, k4A_g, k4A_b, \
 k1A_r, k1A_g, k1A_b, \
 k1B_r, k1B_g, k1B_b, \
 k1C_r, k1C_g, k1C_b, \
 k1D_r, k1D_g, k1D_b, \
 k1E_r, k1E_g, k1E_b, \
 k1F_r, k1F_g, k1F_b, \
 k1G_r, k1G_g, k1G_b, \
 k5G_r, k5G_g, k5G_b, \
 k5F_r, k5F_g, k5F_b, \
 k5E_r, k5E_g, k5E_b, \
 k5D_r, k5D_g, k5D_b, \
 k5C_r, k5C_g, k5C_b, \
 k5B_r, k5B_g, k5B_b, \
 k5A_r, k5A_g, k5A_b, \
 k2A_r, k2A_g, k2A_b, \
 k2B_r, k2B_g, k2B_b, \
 k2C_r, k2C_g, k2C_b, \
 k2D_r, k2D_g, k2D_b, \
 k2E_r, k2E_g, k2E_b, \
 k2F_r, k2F_g, k2F_b, \
 k6F_r, k6F_g, k6F_b, \
 k6E_r, k6E_g, k6E_b, \
 k6D_r, k6D_g, k6D_b, \
 k6C_r, k6C_g, k6C_b, \
 k6B_r, k6B_g, k6B_b, \
 k6A_r, k6A_g, k6A_b, \
 k3D_r, k3D_g, k3D_b, \
 k3E_r, k3E_g, k3E_b, \
 k3F_r, k3F_g, k3F_b, \
 k7F_r, k7F_g, k7F_b, \
 k7E_r, k7E_g, k7E_b, \
 k7D_r, k7D_g, k7D_b) { \
    { (struct rgb_t){k0A_r,k0A_g,k0A_b}, (struct rgb_t){k0B_r,k0B_g,k0B_b}, (struct rgb_t){k0C_r,k0C_g,k0C_b}, (struct rgb_t){k0D_r,k0D_g,k0D_b}, (struct rgb_t){k0E_r,k0E_g,k0E_b}, (struct rgb_t){k0F_r,k0F_g,k0F_b}, (struct rgb_t){k0G_r,k0G_g,k0G_b} }, \
    { (struct rgb_t){k1A_r,k1A_g,k1A_b}, (struct rgb_t){k1B_r,k1B_g,k1B_b}, (struct rgb_t){k1C_r,k1C_g,k1C_b}, (struct rgb_t){k1D_r,k1D_g,k1D_b}, (struct rgb_t){k1E_r,k1E_g,k1E_b}, (struct rgb_t){k1F_r,k1F_g,k1F_b}, (struct rgb_t){k1G_r,k1G_g,k1G_b} }, \
    { (struct rgb_t){k2A_r,k2A_g,k2A_b}, (struct rgb_t){k2B_r,k2B_g,k2B_b}, (struct rgb_t){k2C_r,k2C_g,k2C_b}, (struct rgb_t){k2D_r,k2D_g,k2D_b}, (struct rgb_t){k2E_r,k2E_g,k2E_b}, (struct rgb_t){k2F_r,k2F_g,k2F_b}, (struct rgb_t){RGB_OFF} }, \
    { (struct rgb_t){RGB_OFF},           (struct rgb_t){RGB_OFF},           (struct rgb_t){RGB_OFF},           (struct rgb_t){k3D_r,k3D_g,k3D_b}, (struct rgb_t){k3E_r,k3E_g,k3E_b}, (struct rgb_t){k3F_r,k3F_g,k3F_b}, (struct rgb_t){RGB_OFF} }, \
    { (struct rgb_t){k4A_r,k4A_g,k4A_b}, (struct rgb_t){k4B_r,k4B_g,k4B_b}, (struct rgb_t){k4C_r,k4C_g,k4C_b}, (struct rgb_t){k4D_r,k4D_g,k4D_b}, (struct rgb_t){k4E_r,k4E_g,k4E_b}, (struct rgb_t){k4F_r,k4F_g,k4F_b}, (struct rgb_t){k4G_r,k4G_g,k4G_b} }, \
    { (struct rgb_t){k5A_r,k5A_g,k5A_b}, (struct rgb_t){k5B_r,k5B_g,k5B_b}, (struct rgb_t){k5C_r,k5C_g,k5C_b}, (struct rgb_t){k5D_r,k5D_g,k5D_b}, (struct rgb_t){k5E_r,k5E_g,k5E_b}, (struct rgb_t){k5F_r,k5F_g,k5F_b}, (struct rgb_t){k5G_r,k5G_g,k5G_b} }, \
    { (struct rgb_t){k6A_r,k6A_g,k6A_b}, (struct rgb_t){k6B_r,k6B_g,k6B_b}, (struct rgb_t){k6C_r,k6C_g,k6C_b}, (struct rgb_t){k6D_r,k6D_g,k6D_b}, (struct rgb_t){k6E_r,k6E_g,k6E_b}, (struct rgb_t){k6F_r,k6F_g,k6F_b}, (struct rgb_t){RGB_OFF} }, \
    { (struct rgb_t){RGB_OFF},           (struct rgb_t){RGB_OFF},           (struct rgb_t){RGB_OFF},           (struct rgb_t){k7D_r,k7D_g,k7D_b}, (struct rgb_t){k7E_r,k7E_g,k7E_b}, (struct rgb_t){k7F_r,k7F_g,k7F_b}, (struct rgb_t){RGB_OFF} } \
}
*/
