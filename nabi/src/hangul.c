/* Nabi - X Input Method server for hangul
 * Copyright (C) 2003 Choe Hwanjin
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <wchar.h>

#include "hangul.h"

#include "ucs2ksc.h"

#define HCF 0x115f	/* hangul choseong filler */
#define HJF 0x1160	/* hangul jungseong filler */

#define hangul_is_choseong(ch)	((ch) >= 0x1100 && (ch) <= 0x1159)
#define hangul_is_jungseong(ch)	((ch) >= 0x1161 && (ch) <= 0x11a2)
#define hangul_is_jongseong(ch)	((ch) >= 0x11a7 && (ch) <= 0x11f9)

wchar_t
hangul_choseong_to_cjamo(wchar_t ch)
{
    static wchar_t table[] = {
	0x3131,	    /* 0x1100 */
	0x3132,	    /* 0x1101 */
	0x3134,	    /* 0x1102 */
	0x3137,	    /* 0x1103 */
	0x3138,	    /* 0x1104 */
	0x3139,	    /* 0x1105 */
	0x3141,	    /* 0x1106 */
	0x3142,	    /* 0x1107 */
	0x3143,	    /* 0x1108 */
	0x3145,	    /* 0x1109 */
	0x3146,	    /* 0x110a */
	0x3147,	    /* 0x110b */
	0x3148,	    /* 0x110c */
	0x3149,	    /* 0x110d */
	0x314a,	    /* 0x110e */
	0x314b,	    /* 0x110f */
	0x314c,	    /* 0x1110 */
	0x314d,	    /* 0x1111 */
	0x314e	    /* 0x1112 */
    };
    if (ch < 0x1100 || ch > 0x1112)
	return ch;
    return table[ch - 0x1100];
}

wchar_t
hangul_jungseong_to_cjamo(wchar_t ch)
{
    static wchar_t table[] = {
	0x314f,	    /* 0x1161 */
	0x3150,	    /* 0x1162 */
	0x3151,	    /* 0x1163 */
	0x3152,	    /* 0x1164 */
	0x3153,	    /* 0x1165 */
	0x3154,	    /* 0x1166 */
	0x3155,	    /* 0x1167 */
	0x3156,	    /* 0x1168 */
	0x3157,	    /* 0x1169 */
	0x3158,	    /* 0x116a */
	0x3159,	    /* 0x116b */
	0x315a,	    /* 0x116c */
	0x315b,	    /* 0x116d */
	0x315c,	    /* 0x116e */
	0x315d,	    /* 0x116f */
	0x315e,	    /* 0x1170 */
	0x315f,	    /* 0x1171 */
	0x3160,	    /* 0x1172 */
	0x3161,	    /* 0x1173 */
	0x3162,	    /* 0x1174 */
	0x3163	    /* 0x1175 */
    };
    if (ch < 0x1161 || ch > 0x1175)
	return 0;
    return table[ch - 0x1161];
}

wchar_t
hangul_jongseong_to_cjamo(wchar_t ch)
{
    static wchar_t table[] = {
	0x3131,	    /* 0x11a8 */
	0x3132,	    /* 0x11a9 */
	0x3133,	    /* 0x11aa */
	0x3134,	    /* 0x11ab */
	0x3135,	    /* 0x11ac */
	0x3136,	    /* 0x11ad */
	0x3137,	    /* 0x11ae */
	0x3139,	    /* 0x11af */
	0x313a,	    /* 0x11b0 */
	0x313b,	    /* 0x11b1 */
	0x313c,	    /* 0x11b2 */
	0x313d,	    /* 0x11b3 */
	0x313e,	    /* 0x11b4 */
	0x313f,	    /* 0x11b5 */
	0x3140,	    /* 0x11b6 */
	0x3141,	    /* 0x11b7 */
	0x3142,	    /* 0x11b8 */
	0x3144,	    /* 0x11b9 */
	0x3145,	    /* 0x11ba */
	0x3146,	    /* 0x11bb */
	0x3147,	    /* 0x11bc */
	0x3148,	    /* 0x11bd */
	0x314a,	    /* 0x11be */
	0x314b,	    /* 0x11bf */
	0x314c,	    /* 0x11c0 */
	0x314d,	    /* 0x11c1 */
	0x314e	    /* 0x11c2 */
    };
    if (ch < 0x11a8 || ch > 0x11c2)
	return 0;
    return table[ch - 0x11a8];
}

wchar_t
hangul_choseong_to_jongseong(wchar_t ch)
{
    static wchar_t table[] = {
      0x11a8,  /* choseong kiyeok      -> jongseong kiyeok      */
      0x11a9,  /* choseong ssangkiyeok -> jongseong ssangkiyeok */
      0x11ab,  /* choseong nieun       -> jongseong nieun       */
      0x11ae,  /* choseong tikeut      -> jongseong tikeut      */
      0x0,     /* choseong ssangtikeut -> jongseong tikeut      */
      0x11af,  /* choseong rieul       -> jongseong rieul       */
      0x11b7,  /* choseong mieum       -> jongseong mieum       */
      0x11b8,  /* choseong pieup       -> jongseong pieup       */
      0x0,     /* choseong ssangpieup  -> jongseong pieup       */
      0x11ba,  /* choseong sios        -> jongseong sios        */
      0x11bb,  /* choseong ssangsios   -> jongseong ssangsios   */
      0x11bc,  /* choseong ieung       -> jongseong ieung       */
      0x11bd,  /* choseong cieuc       -> jongseong cieuc       */
      0x0,     /* choseong ssangcieuc  -> jongseong cieuc       */
      0x11be,  /* choseong chieuch     -> jongseong chieuch     */
      0x11bf,  /* choseong khieukh     -> jongseong khieukh     */
      0x11c0,  /* choseong thieuth     -> jongseong thieuth     */
      0x11c1,  /* choseong phieuph     -> jongseong phieuph     */
      0x11c2   /* choseong hieuh       -> jongseong hieuh       */
    };
    if (ch < 0x1100 || ch > 0x1112)
	return 0;
    return table[ch - 0x1100];
}

wchar_t
hangul_jongseong_to_choseong(wchar_t ch)
{
    static wchar_t table[] = {
      0x1100,  /* jongseong kiyeok        -> choseong kiyeok       */
      0x1101,  /* jongseong ssangkiyeok   -> choseong ssangkiyeok  */
      0x1109,  /* jongseong kiyeok-sios   -> choseong sios         */
      0x1102,  /* jongseong nieun         -> choseong nieun        */
      0x110c,  /* jongseong nieun-cieuc   -> choseong cieuc        */
      0x1112,  /* jongseong nieun-hieuh   -> choseong hieuh        */
      0x1103,  /* jongseong tikeut        -> choseong tikeut       */
      0x1105,  /* jongseong rieul         -> choseong rieul        */
      0x1100,  /* jongseong rieul-kiyeok  -> choseong kiyeok       */
      0x1106,  /* jongseong rieul-mieum   -> choseong mieum        */
      0x1107,  /* jongseong rieul-pieup   -> choseong pieup        */
      0x1109,  /* jongseong rieul-sios    -> choseong sios         */
      0x1110,  /* jongseong rieul-thieuth -> choseong thieuth      */
      0x1111,  /* jongseong rieul-phieuph -> choseong phieuph      */
      0x1112,  /* jongseong rieul-hieuh   -> choseong hieuh        */
      0x1106,  /* jongseong mieum         -> choseong mieum        */
      0x1107,  /* jongseong pieup         -> choseong pieup        */
      0x1109,  /* jongseong pieup-sios    -> choseong sios         */
      0x1109,  /* jongseong sios          -> choseong sios         */
      0x110a,  /* jongseong ssangsios     -> choseong ssangsios    */
      0x110b,  /* jongseong ieung         -> choseong ieung        */
      0x110c,  /* jongseong cieuc         -> choseong cieuc        */
      0x110e,  /* jongseong chieuch       -> choseong chieuch      */
      0x110f,  /* jongseong khieukh       -> choseong khieukh      */
      0x1110,  /* jongseong thieuth       -> choseong thieuth      */
      0x1111,  /* jongseong phieuph       -> choseong phieuph      */
      0x1112   /* jongseong hieuh         -> choseong hieuh        */
    };
    if (ch < 0x11a8 || ch > 0x11c2)
	return 0;
    return table[ch - 0x11a8];
}

void
hangul_jongseong_dicompose(wchar_t ch, wchar_t* jong, wchar_t* cho)
{
static wchar_t table[][2] = {
    { 0,      0x1100 }, /* jong kiyeok	      = cho  kiyeok               */
    { 0x11a8, 0x1100 }, /* jong ssangkiyeok   = jong kiyeok + cho kiyeok  */
    { 0x11a8, 0x1109 }, /* jong kiyeok-sios   = jong kiyeok + cho sios    */
    { 0,      0x1102 }, /* jong nieun	      = cho  nieun                */
    { 0x11ab, 0x110c }, /* jong nieun-cieuc   = jong nieun  + cho cieuc   */
    { 0x11ab, 0x1112 }, /* jong nieun-hieuh   = jong nieun  + cho hieuh   */
    { 0,      0x1103 }, /* jong tikeut	      = cho  tikeut               */
    { 0,      0x1105 }, /* jong rieul         = cho  rieul                */
    { 0x11af, 0x1100 }, /* jong rieul-kiyeok  = jong rieul  + cho kiyeok  */
    { 0x11af, 0x1106 }, /* jong rieul-mieum   = jong rieul  + cho mieum   */
    { 0x11af, 0x1107 }, /* jong rieul-pieup   = jong rieul  + cho pieup   */
    { 0x11af, 0x1109 }, /* jong rieul-sios    = jong rieul  + cho sios    */
    { 0x11af, 0x1110 }, /* jong rieul-thieuth = jong rieul  + cho thieuth */
    { 0x11af, 0x1111 }, /* jong rieul-phieuph = jong rieul  + cho phieuph */
    { 0x11af, 0x1112 }, /* jong rieul-hieuh   = jong rieul  + cho hieuh   */
    { 0,      0x1106 }, /* jong mieum         = cho  mieum                */
    { 0,      0x1107 }, /* jong pieup         = cho  pieup                */
    { 0x11b8, 0x1109 }, /* jong pieup-sios    = jong pieup  + cho sios    */
    { 0,      0x1109 }, /* jong sios          = cho  sios                 */
    { 0x11ba, 0x1109 }, /* jong ssangsios     = jong sios   + cho sios    */
    { 0,      0x110b }, /* jong ieung         = cho  ieung                */
    { 0,      0x110c }, /* jong cieuc         = cho  cieuc                */
    { 0,      0x110e }, /* jong chieuch       = cho  chieuch              */
    { 0,      0x110f }, /* jong khieukh       = cho  khieukh              */
    { 0,      0x1110 }, /* jong thieuth       = cho  thieuth              */
    { 0,      0x1111 }, /* jong phieuph       = cho  phieuph              */
    { 0,      0x1112 }  /* jong hieuh         = cho  hieuh                */
};
    *jong = table[ch - 0x11a8][0];
    *cho  = table[ch - 0x11a8][1];
}

wchar_t
hangul_jamo_to_syllable(wchar_t choseong, wchar_t jungseong, wchar_t jongseong)
{
    static wchar_t hangul_base    = 0xac00;
    static wchar_t choseong_base  = 0x1100;
    static wchar_t jungseong_base = 0x1161;
    static wchar_t jongseong_base = 0x11a7;
    static int njungseong = 21;
    static int njongseong = 28;
    wchar_t ch;

    /* we use 0x11a7 like a Jongseong filler */
    if (jongseong == 0)
	jongseong = 0x11a7;         /* Jongseong filler */

    if (!(choseong  >= 0x1100 && choseong  <= 0x1112))
	return 0;
    if (!(jungseong >= 0x1161 && jungseong <= 0x1175))
	return 0;
    if (!(jongseong >= 0x11a7 && jongseong <= 0x11c2))
	return 0;

    choseong  -= choseong_base;
    jungseong -= jungseong_base;
    jongseong -= jongseong_base;

    ch = ((choseong * njungseong) + jungseong) * njongseong + jongseong
	+ hangul_base;
    return ch;
}

wchar_t
hangul_ucs_to_ksc(wchar_t choseong, wchar_t jungseong, wchar_t jongseong)
{
    wchar_t ch;
    
    ch = hangul_jamo_to_syllable(choseong, jungseong, jongseong);
    if (ch < 0xac00 || ch > 0xd7a3)
	return 0x0;
    return ucs_to_ksc5601_table[ch - 0xac00];
}

/* vim: set ts=8 sts=4 sw=4 : */
