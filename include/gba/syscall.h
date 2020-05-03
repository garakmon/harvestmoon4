#ifndef GUARD_GBA_SYSCALL_H
#define GUARD_GBA_SYSCALL_H

#define RESET_EWRAM      0x01
#define RESET_IWRAM      0x02
#define RESET_PALETTE    0x04
#define RESET_VRAM       0x08
#define RESET_OAM        0x10
#define RESET_SIO_REGS   0x20
#define RESET_SOUND_REGS 0x40
#define RESET_REGS       0x80
#define RESET_ALL        0xFF

void SoftReset(uint32_t resetFlags);

void RegisterRamReset(uint32_t resetFlags);

void VBlankIntrWait(void);

uint16_t Sqrt(uint32_t num);

uint16_t ArcTan2(int16_t x, int16_t y);

#define CPU_SET_SRC_FIXED 0x01000000
#define CPU_SET_16BIT     0x00000000
#define CPU_SET_32BIT     0x04000000

void CpuSet(const void *src, void *dest, uint32_t control);

#define CPU_FAST_SET_SRC_FIXED 0x01000000

void CpuFastSet(const void *src, void *dest, uint32_t control);

void BgAffineSet(struct BgAffineSrcData *src, struct BgAffineDstData *dest, int32_t count);

void ObjAffineSet(struct ObjAffineSrcData *src, void *dest, int32_t count, int32_t offset);

void LZ77UnCompWram(const void *src, void *dest);

void LZ77UnCompVram(const void *src, void *dest);

void RLUnCompWram(const void *src, void *dest);

void RLUnCompVram(const void *src, void *dest);

int MultiBoot(struct MultiBootParam *mp);

int32_t Div(int32_t num, int32_t denom);

#endif // GUARD_GBA_SYSCALL_H
