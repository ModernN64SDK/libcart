/******************************************************************************/
/*               libcart - Nintendo 64 flash cartridge library                */
/*                    Copyright (C) 2022 - 2023 devwizard                     */
/*     This project is licensed under the terms of the MIT license.  See      */
/*     LICENSE for more information.                                          */
/******************************************************************************/

#include <cart.h>
#include "cartint.h"

int cart_card_rd_cart(u32 cart, u32 lba, u32 count)
{
    static int (*const card_rd_cart[CART_MAX])(u32 cart, u32 lba, u32 count) =
    {
        ci_card_rd_cart,
        edx_card_rd_cart,
        ed_card_rd_cart,
        sc_card_rd_cart,
    };
    if (cart_type < 0) return -1;
    return card_rd_cart[cart_type](cart, lba, count);
}
