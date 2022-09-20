/*  Copyright 2003-2004 Stephane Dallongeville
    Copyright 2004 Theo Berkau

    This file is part of Yabause.

    Yabause is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Yabause is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Yabause; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

/*********************************************************************************
 * GEN68K.H :
 *
 * C68K generator include file
 *
 ********************************************************************************/

#ifndef _GEN68K_H_
#define _GEN68K_H_

#ifdef __cplusplus
extern "C" {
#endif

// setting
///////////

// structure definition
////////////////////////

typedef struct {
    uint32_t    name;
    uint32_t    mask;
    uint32_t    match;
} c68k_ea_info_struc;

typedef struct __c68k_op_info_struc {
    int8_t      op_name[8 + 1];
    uint16_t    op_base;
    uint16_t    op_mask;
    int8_t      size_type;
    int8_t      size_sft;
    int8_t      eam_sft;
    int8_t      reg_sft;
    int8_t      eam2_sft;
    int8_t      reg2_sft;
    int8_t      ea_supported[12 + 1];
    int8_t      ea2_supported[12 + 1];
    void (*genfunc)(void);
} c68k_op_info_struc;


#ifdef __cplusplus
}
#endif

#endif  // _GEN68K_H_

