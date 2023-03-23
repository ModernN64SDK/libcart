/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"
#include "ci.h"

int ci_card_rd_dram(void *dram, u32 lba, u32 count)
{
    char *addr = dram;
    __cart_acs_get();
    __ci_sync();
    while (count-- > 0)
    {
        __cart_wr(CI_LBA_REG, lba);
        __cart_wr(CI_COMMAND_REG, CI_RD_BUFFER);
        if (__ci_sync())
        {
            __cart_wr(CI_COMMAND_REG, CI_ABORT);
            __ci_sync();
            __cart_wr(CI_COMMAND_REG, CI_SD_RESET);
            __ci_sync();
            __cart_acs_rel();
            return -1;
        }
        __cart_buf_rd(addr, CI_BASE_REG|CI_BUFFER_REG, 512);
        addr += 512;
        lba++;
    }
    __cart_acs_rel();
    return 0;
}
