#include <stdio.h>
#include <nds_intrinsic.h>
#include <stdint.h>

/* SIMD Unsigned 8-bit Multiply */
static int simd_umul8_test(void)
{
    uint32_t a = 0x05050505;
    uint32_t b = 0x02020202;
    uint64_t c = 0x000a000a000a000a;
    uint64_t result = __nds__umul8(a, b);

    if(result != c)
        return -1;

    uint8x4_t v_a = {0x08, 0x08, 0x08, 0x08};
    uint8x4_t v_b = {0x02, 0x02, 0x02, 0x02};
    uint16x4_t v_c = {0x0010, 0x0010, 0x0010, 0x0010};

    uint16x4_t v_result = __nds__v_umul8(v_a, v_b);

    for(uint32_t i = 0; i < 4; i++)
    {
        if(v_result[i] != v_c[i])
            return -1;
    }

    return 0;
}

int main(void)
{
    int ret;
    printf("DSP SIMD UMUL8 TEST\n");
    ret = simd_umul8_test();
    if(ret)
        printf("DSP SIMD UMUL8 TEST FAIL\n");
    else
        printf("DSP SIMD UMUL8 TEST PASS\n");
    return 0;
}
