/*! \file    actions.hpp
 *  \brief   This file contains prototypes of functions that implement the action words.
 *  \author  Peter Chapin <chapinp@proton.me>
 */

#ifndef ACTIONS_HPP
#define ACTIONS_HPP

#include "ClacStack.hpp"

extern void do_bin         ( ClacStack & );
extern void do_clear       ( ClacStack & );
extern void do_dec         ( ClacStack & );
extern void do_deg         ( ClacStack & );
extern void do_drop        ( ClacStack & );
extern void do_dropn       ( ClacStack & );
extern void do_dup         ( ClacStack & );
extern void do_dupn        ( ClacStack & );
extern void do_fix         ( ClacStack & );
extern void do_eng         ( ClacStack & );
extern void do_eval        ( ClacStack & );
extern void do_grad        ( ClacStack & );
extern void do_hex         ( ClacStack & );
extern void do_info        ( ClacStack & );
extern void do_oct         ( ClacStack & );
extern void do_polar       ( ClacStack & );
extern void do_purge       ( ClacStack & );
extern void do_rad         ( ClacStack & );
extern void do_read        ( ClacStack & );
extern void do_rec         ( ClacStack & );
extern void do_roll_down   ( ClacStack & );
extern void do_roll_up     ( ClacStack & );
extern void do_rot         ( ClacStack & );
extern void do_run         ( ClacStack & );
extern void do_sci         ( ClacStack & );
extern void do_store       ( ClacStack & );
extern void do_stws        ( ClacStack & );
extern void do_swap        ( ClacStack & );
// extern void do_sys         ( ClacStack & );
extern void do_write       ( ClacStack & );

extern void do_shift_left  ( ClacStack & );
extern void do_shift_right ( ClacStack & );
// extern void do_ashift_right( ClacStack & );

extern void do_off         ( ClacStack & );

#endif
