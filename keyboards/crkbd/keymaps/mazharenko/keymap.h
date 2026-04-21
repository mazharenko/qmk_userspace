#define LAYOUT_split_3x6_3_ex2_hsv(k0A, k0B, k0C, k0D, k0E, k0F, k0G, k4G, k4F, k4E, k4D, k4C, k4B, k4A, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k5G, k5F, k5E, k5D, k5C, k5B, k5A, k2A, k2B, k2C, k2D, k2E, k2F, k6F, k6E, k6D, k6C, k6B, k6A, k3D, k3E, k3F, k7F, k7E, k7D) { \
    { k0A, k0B, k0C, k0D, k0E, k0F, k0G }, \
    { k1A, k1B, k1C, k1D, k1E, k1F, k1G }, \
    { k2A, k2B, k2C, k2D, k2E, k2F, (struct hsv_t){HSV_OFF} }, \
    { (struct hsv_t){HSV_OFF}, (struct hsv_t){HSV_OFF}, (struct hsv_t){HSV_OFF}, k3D, k3E, k3F, (struct hsv_t){HSV_OFF} }, \
    { k4A, k4B, k4C, k4D, k4E, k4F, k4G }, \
    { k5A, k5B, k5C, k5D, k5E, k5F, k5G }, \
    { k6A, k6B, k6C, k6D, k6E, k6F, (struct hsv_t){HSV_OFF} }, \
    { (struct hsv_t){HSV_OFF}, (struct hsv_t){HSV_OFF}, (struct hsv_t){HSV_OFF}, k7D, k7E, k7F, (struct hsv_t){HSV_OFF} } \
}


#define LAYOUT_split_3x6_3_ex2_hsv_mods(k0A, k0B, k0C, k0D, k0E, k0F, k0G, k4G, k4F, k4E, k4D, k4C, k4B, k4A, k1A, k1B, k1C, k1D, k1E, k1F, k1G, k5G, k5F, k5E, k5D, k5C, k5B, k5A, k2A, k2B, k2C, k2D, k2E, k2F, k6F, k6E, k6D, k6C, k6B, k6A, k3D, k3E, k3F, k7F, k7E, k7D) { \
    { (uint8_t)k0A, (uint8_t)k0B, (uint8_t)k0C, (uint8_t)k0D, (uint8_t)k0E, (uint8_t)k0F, (uint8_t)k0G }, \
    { (uint8_t)k1A, (uint8_t)k1B, (uint8_t)k1C, (uint8_t)k1D, (uint8_t)k1E, (uint8_t)k1F, (uint8_t)k1G }, \
    { (uint8_t)k2A, (uint8_t)k2B, (uint8_t)k2C, (uint8_t)k2D, (uint8_t)k2E, (uint8_t)k2F, (uint8_t)0 }, \
    { (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)k3D, (uint8_t)k3E, (uint8_t)k3F, (uint8_t)0 }, \
    { (uint8_t)k4A, (uint8_t)k4B, (uint8_t)k4C, (uint8_t)k4D, (uint8_t)k4E, (uint8_t)k4F, (uint8_t)k4G }, \
    { (uint8_t)k5A, (uint8_t)k5B, (uint8_t)k5C, (uint8_t)k5D, (uint8_t)k5E, (uint8_t)k5F, (uint8_t)k5G }, \
    { (uint8_t)k6A, (uint8_t)k6B, (uint8_t)k6C, (uint8_t)k6D, (uint8_t)k6E, (uint8_t)k6F, (uint8_t)0 }, \
    { (uint8_t)0, (uint8_t)0, (uint8_t)0, (uint8_t)k7D, (uint8_t)k7E, (uint8_t)k7F, (uint8_t)0 } \
}
