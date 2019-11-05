/* Copyright 2018 REPLACE_WITH_YOUR_NAME
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef DELTAINTEGRALE_DACTYL_H
#define DELTAINTEGRALE_DACTYL_H

#include "quantum.h"

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    k00,k01,k02,k03,k04,k05,                                            \
    k10,k11,k12,k13,k14,k15,                                            \
    k20,k21,k22,k23,k24,k25,                                            \
    k30,k31,k32,k33,k34,k35,                                            \
    k40,k41,k42,k43,k44,                                                \
                            k55,k50,                                    \
                                k54,                                    \
                        k53,k52,k51,                                    \
                                                                        \
            k06,k07,k08,k09,k0A,k0B,                                    \
            k16,k17,k18,k19,k1A,k1B,                                    \
            k26,k27,k28,k29,k2A,k2B,                                    \
            k36,k37,k38,k39,k3A,k3B,                                    \
                k47,k48,k49,k4A,k4B,                                    \
    k5B,k56,                                                            \
    k57,                                                                \
    k5A,k59,k58 )                                                       \
                                                                        \
   /* matrix positions */                                               \
   {                                                                    \
    { k00, k01, k02, k03, k04, k05   }, \
    { k10, k11, k12, k13, k14, k15   }, \
    { k20, k21, k22, k23, k24, k25   }, \
    { k30, k31, k32, k33, k34, k35   }, \
    { k40, k41, k42, k43, k44, KC_NO }, \
    { k55, k54, k53, k52, k51, k50   }, \
    { k0B, k0A, k09, k08, k07, k06   }, \
    { k1B, k1A, k19, k18, k17, k16   }, \
    { k2B, k2A, k29, k28, k27, k26   }, \
    { k3B, k3A, k39, k38, k37, k36   }, \
    { k4B, k4A, k49, k48, k47, KC_NO }, \
    { k5B, k5A, k59, k58, k57, k56   }  \
   }

#endif
