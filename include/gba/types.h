#ifndef GUARD_GBA_TYPES_H
#define GUARD_GBA_TYPES_H

struct BgCnt
{
    uint16_t priority:2;
    uint16_t charBaseBlock:2;
    uint16_t dummy:2;
    uint16_t mosaic:1;
    uint16_t palettes:1;
    uint16_t screenBaseBlock:5;
    uint16_t areaOverflowMode:1;
    uint16_t screenSize:2;
};
typedef volatile struct BgCnt vBgCnt;

struct PlttData
{
    uint16_t r:5; // red
    uint16_t g:5; // green
    uint16_t b:5; // blue
    uint16_t unused_15:1;
};

struct OamData
{
    /*0x00*/ uint32_t y:8;
    /*0x01*/ uint32_t affineMode:2;  // 0x1, 0x2 -> 0x4
             uint32_t objMode:2;     // 0x4, 0x8 -> 0xC
             uint32_t mosaic:1;      // 0x10
             uint32_t bpp:1;         // 0x20
             uint32_t shape:2;       // 0x40, 0x80 -> 0xC0

    /*0x02*/ uint32_t x:9;
             uint32_t matrixNum:5;   // bits 3/4 are h-flip/v-flip if not in affine mode
             uint32_t size:2;        // 0x4000, 0x8000 -> 0xC000

    /*0x04*/ uint16_t tileNum:10;    // 0x3FF
             uint16_t priority:2;    // 0x400, 0x800 -> 0xC00
             uint16_t paletteNum:4;
    /*0x06*/ uint16_t affineParam;
};

#define ST_OAM_HFLIP     0x08
#define ST_OAM_VFLIP     0x10
#define ST_OAM_MNUM_FLIP_MASK 0x18

#define ST_OAM_OBJ_NORMAL 0
#define ST_OAM_OBJ_BLEND  1
#define ST_OAM_OBJ_WINDOW 2

#define ST_OAM_AFFINE_OFF    0
#define ST_OAM_AFFINE_NORMAL 1
#define ST_OAM_AFFINE_ERASE  2
#define ST_OAM_AFFINE_DOUBLE 3

#define ST_OAM_AFFINE_ON_MASK     1
#define ST_OAM_AFFINE_DOUBLE_MASK 2

#define ST_OAM_4BPP 0
#define ST_OAM_8BPP 1

#define ST_OAM_SQUARE      0
#define ST_OAM_H_RECTANGLE 1
#define ST_OAM_V_RECTANGLE 2

#define ST_OAM_SIZE_0   0
#define ST_OAM_SIZE_1   1
#define ST_OAM_SIZE_2   2
#define ST_OAM_SIZE_3   3

#define SPRITE_SIZE_8x8     ((ST_OAM_SIZE_0 << 2) | (ST_OAM_SQUARE))
#define SPRITE_SIZE_16x16   ((ST_OAM_SIZE_1 << 2) | (ST_OAM_SQUARE))
#define SPRITE_SIZE_32x32   ((ST_OAM_SIZE_2 << 2) | (ST_OAM_SQUARE))
#define SPRITE_SIZE_64x64   ((ST_OAM_SIZE_3 << 2) | (ST_OAM_SQUARE))

#define SPRITE_SIZE_16x8    ((ST_OAM_SIZE_0 << 2) | (ST_OAM_H_RECTANGLE))
#define SPRITE_SIZE_32x8    ((ST_OAM_SIZE_1 << 2) | (ST_OAM_H_RECTANGLE))
#define SPRITE_SIZE_32x16   ((ST_OAM_SIZE_2 << 2) | (ST_OAM_H_RECTANGLE))
#define SPRITE_SIZE_64x32   ((ST_OAM_SIZE_3 << 2) | (ST_OAM_H_RECTANGLE))

#define SPRITE_SIZE_8x16    ((ST_OAM_SIZE_0 << 2) | (ST_OAM_V_RECTANGLE))
#define SPRITE_SIZE_8x32    ((ST_OAM_SIZE_1 << 2) | (ST_OAM_V_RECTANGLE))
#define SPRITE_SIZE_16x32   ((ST_OAM_SIZE_2 << 2) | (ST_OAM_V_RECTANGLE))
#define SPRITE_SIZE_32x64   ((ST_OAM_SIZE_3 << 2) | (ST_OAM_V_RECTANGLE))

#define SPRITE_SIZE(dim)  ((SPRITE_SIZE_##dim >> 2) & 0x03)
#define SPRITE_SHAPE(dim) (SPRITE_SIZE_##dim & 0x03)

struct BgAffineSrcData
{
    int32_t texX;
    int32_t texY;
    int16_t scrX;
    int16_t scrY;
    int16_t sx;
    int16_t sy;
    uint16_t alpha;
};

struct BgAffineDstData
{
    int16_t pa;
    int16_t pb;
    int16_t pc;
    int16_t pd;
    int32_t dx;
    int32_t dy;
};

struct ObjAffineSrcData
{
    int16_t xScale;
    int16_t yScale;
    uint16_t rotation;
};

// Multi-player SIO Control Structure
struct SioMultiCnt
{
    uint16_t baudRate:2;    // baud rate
    uint16_t si:1;          // SI terminal
    uint16_t sd:1;          // SD terminal
    uint16_t id:2;          // ID
    uint16_t error:1;       // error flag
    uint16_t enable:1;      // SIO enable
    uint16_t unused_11_8:4;
    uint16_t mode:2;        // communication mode (should equal 2)
    uint16_t intrEnable:1;  // IRQ enable
    uint16_t unused_15:1;
    uint16_t data;          // data
};

#define ST_SIO_MULTI_MODE 2 // Multi-player communication mode

// baud rate
#define ST_SIO_9600_BPS   0 //   9600 bps
#define ST_SIO_38400_BPS  1 //  38400 bps
#define ST_SIO_57600_BPS  2 //  57600 bps
#define ST_SIO_115200_BPS 3 // 115200 bps

#endif // GUARD_GBA_TYPES_H
