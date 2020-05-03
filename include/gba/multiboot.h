#ifndef GUARD_GBA_MULTIBOOT_H
#define GUARD_GBA_MULTIBOOT_H

#define MULTIBOOT_NCHILD        3       // Maximum number of slaves
#define MULTIBOOT_HEADER_SIZE   0xc0    // Header size
#define MULTIBOOT_SEND_SIZE_MIN 0x100   // Minimum transmission size
#define MULTIBOOT_SEND_SIZE_MAX 0x40000 // Maximum transmission size

struct MultiBootParam
{
    uint32_t system_work[5];
    uint8_t handshake_data;
    uint8_t padding;
    uint16_t handshake_timeout;
    uint8_t probe_count;
    uint8_t client_data[MULTIBOOT_NCHILD];
    uint8_t palette_data;
    uint8_t response_bit;
    uint8_t client_bit;
    uint8_t reserved1;
    const uint8_t *boot_srcp;
    const uint8_t *boot_endp;
    const uint8_t *masterp;
    uint8_t *reserved2[MULTIBOOT_NCHILD];
    uint32_t system_work2[4];
    uint8_t sendflag;
    uint8_t probe_target_bit;
    uint8_t check_wait;
    uint8_t server_type;
};

#define MULTIBOOT_ERROR_04                0x04
#define MULTIBOOT_ERROR_08                0x08
#define MULTIBOOT_ERROR_0c                0x0c
#define MULTIBOOT_ERROR_40                0x40
#define MULTIBOOT_ERROR_44                0x44
#define MULTIBOOT_ERROR_48                0x48
#define MULTIBOOT_ERROR_4c                0x4c
#define MULTIBOOT_ERROR_80                0x80
#define MULTIBOOT_ERROR_84                0x84
#define MULTIBOOT_ERROR_88                0x88
#define MULTIBOOT_ERROR_8c                0x8c
#define MULTIBOOT_ERROR_NO_PROBE_TARGET   0x50
#define MULTIBOOT_ERROR_NO_DLREADY        0x60
#define MULTIBOOT_ERROR_BOOT_FAILURE      0x70
#define MULTIBOOT_ERROR_HANDSHAKE_FAILURE 0x71

#define MULTIBOOT_CONNECTION_CHECK_WAIT 15

#define MULTIBOOT_SERVER_TYPE_NORMAL 0
#define MULTIBOOT_SERVER_TYPE_QUICK  1

#define MULTIBOOT_HANDSHAKE_TIMEOUT 400

#endif // GUARD_GBA_MULTIBOOT_H
