/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "ci.h"

int ci_card_wr_dram(const void *dram, u32 lba, u32 count)
{
    const char *addr = dram;
    __cart_acs_get();
    __ci_sync();
    while (count-- > 0)
    {
        __cart_buf_wr(addr, CI_BASE_REG|CI_BUFFER_REG, 512);
        __cart_wr(CI_LBA_REG, lba);
        __cart_wr(CI_COMMAND_REG, CI_WR_BUFFER);
        if (__ci_sync())
        {
            __cart_wr(CI_COMMAND_REG, CI_ABORT);
            __ci_sync();
            __cart_wr(CI_COMMAND_REG, CI_SD_RESET);
            __ci_sync();
            __cart_acs_rel();
            return -1;
        }
        addr += 512;
        lba++;
    }
    __cart_acs_rel();
    return 0;
}
