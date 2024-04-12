// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include <inttypes.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/user_events.h>

const char *data_file = "/sys/kernel/tracing/user_events_data";

static int event_reg(int fd, const char *command, int *write, volatile int *enabled)
{
    struct user_reg reg = {0};

    reg.size = sizeof(reg);
    reg.enable_bit = 31;
    reg.enable_size = sizeof(*enabled);
    reg.enable_addr = (__u64)enabled;
    reg.name_args = (__u64)command;

    if (ioctl(fd, DIAG_IOCSREG, &reg) == -1)
        return -1;

    *write = reg.write_index;

    return 0;
}

int main()
{
    int data_fd, write1, write2, enabled1, enabled2;
    __u32 count = 0;

    data_fd = open(data_file, O_RDWR);

    if (event_reg(data_fd, "MyProviderName_L4K1 u8 eventheader_flags;u8 version;u16 id;u16 tag;u8 opcode;u8", &write1, &enabled1) == -1)
    {
        printf("error user_events: %s\n", strerror(errno));
        return errno;
    }

    if (event_reg(data_fd, "MyProviderName_L4K1 u8 eventheader_flags;u8 version;u16 id;u16 tag;u8 opcode;u8", &write2, &enabled2) == -1)
    {
        printf("error user_events: %s\n", strerror(errno));
        return errno;
    }

    return 0;
}