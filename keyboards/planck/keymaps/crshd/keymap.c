/* Copyright 2015-2017 Jack Humbert
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

#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _MAC,
  _WIN,
  _UML,
  _NUMPAD,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  MAC = SAFE_RANGE,
  WIN,
  BACKLIT,
  EXT_PLV,
  UMLAUT_A,
  UMLAUT_O,
  UMLAUT_U,
  UMLAUT_S
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define CTLSC LCTL_T(KC_ESC)
#define SHENTER RSFT_T(KC_ENT)
#define OSHYPR OSM(KC_HYPR)
#define UML MO(_UML)
#define NUMPAD MO(_NUMPAD)
#define MODS_SHIFT_MASK (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT))

bool g_NumLockOn = false;

void send_altcode(uint16_t mask, keyrecord_t *record) {
  static uint8_t lalt_mask;
  lalt_mask = keyboard_report->mods & KC_LALT;

  bool bNumLockWasOn = g_NumLockOn;

  static uint16_t kp[4];

  kp[0] = mask / 1000;
  kp[1] = mask / 100 - kp[0] * 100;
  kp[2] = mask / 10 - kp[0] * 1000 - kp[1] * 10;
  kp[3] = mask - kp[0] * 1000 - kp[1] * 100 - kp[2] * 10;

  for (uint8_t i=0; i<=3; i++) {
    switch(kp[i]) {
      case 0:
        kp[i] = KC_KP_0; break;
      case 1:
        kp[i] = KC_KP_1; break;
      case 2:
        kp[i] = KC_KP_2; break;
      case 3:
        kp[i] = KC_KP_3; break;
      case 4:
        kp[i] = KC_KP_4; break;
      case 5:
        kp[i] = KC_KP_5; break;
      case 6:
        kp[i] = KC_KP_6; break;
      case 7:
        kp[i] = KC_KP_7; break;
      case 8:
        kp[i] = KC_KP_8; break;
      case 9:
        kp[i] = KC_KP_9; break;
    }
  }

  if (!lalt_mask) {
    register_code(KC_LALT);
    send_keyboard_report();
  }

  if (!bNumLockWasOn) {
    register_code(KC_LNUM);
    send_keyboard_report();
  }

  add_key(kp[0]);
  send_keyboard_report();
  del_key(kp[0]);
  send_keyboard_report();
  add_key(kp[1]);
  send_keyboard_report();
  del_key(kp[1]);
  send_keyboard_report();
  add_key(kp[2]);
  send_keyboard_report();
  del_key(kp[2]);
  send_keyboard_report();
  add_key(kp[3]);
  send_keyboard_report();
  del_key(kp[3]);
  send_keyboard_report();

  if (!lalt_mask) {
    unregister_code(KC_LALT);
  }

  send_keyboard_report();

  if (!bNumLockWasOn) {
    unregister_code(KC_LNUM);
    send_keyboard_report();
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_MAC] = {
  {KC_TAB,  KC_Q,    KC_W,   KC_E,    KC_R,  KC_T,    KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC},
  {CTLSC,   KC_A,    KC_S,   KC_D,    KC_F,  KC_G,    KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,    KC_X,   KC_C,    KC_V,  KC_B,    KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, SHENTER},
  {OSHYPR,  KC_LCTL, NUMPAD, KC_LALT, LOWER, KC_LGUI, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

[_WIN] = {
  {KC_TAB,  KC_Q, KC_W,   KC_E,    KC_R,  KC_T,    KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC},
  {CTLSC,   KC_A, KC_S,   KC_D,    KC_F,  KC_G,    KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z, KC_X,   KC_C,    KC_V,  KC_B,    KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, SHENTER},
  {OSHYPR,  UML,  NUMPAD, KC_LALT, LOWER, KC_LGUI, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

[_UML] = {
  {_______, _______,  _______,  _______, _______, _______, _______, UMLAUT_U, _______, UMLAUT_O, _______, _______},
  {_______, UMLAUT_A, UMLAUT_S, _______, _______, _______, _______, _______,  _______, _______,  _______, _______},
  {_______, _______,  _______,  _______, _______, _______, _______, _______,  _______, _______,  _______, _______},
  {_______, _______,  _______,  _______, _______, _______, _______, _______,  _______, _______,  _______, _______}
},

[_NUMPAD] = {
  {_______, _______, _______, _______, _______, _______, _______, KC_KP_7, KC_KP_8,   KC_KP_9,     KC_KP_MINUS,    _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_KP_4, KC_KP_5,   KC_KP_6,     KC_KP_PLUS,     _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_KP_1, KC_KP_2,   KC_KP_3,     KC_KP_ASTERISK, _______},
  {_______, _______, _______, _______, _______, _______, _______, KC_KP_0, KC_KP_DOT, KC_KP_EQUAL, KC_KP_SLASH,    _______}
},

[_LOWER] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC},
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_EQL,     KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), KC_MINS, KC_LBRC, KC_RBRC, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______,    KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},

[_RAISE] = {
  {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC},
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY}
},

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|Plover|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = {
  {_______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL },
  {_______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, MAC,     WIN,      _______, _______, _______},
  {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______},
  {_______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______}
}
};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint8_t shift_mask;
  shift_mask = get_mods()&MODS_SHIFT_MASK;

  if (record->event.pressed) {
    switch(keycode) {
      case MAC:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_MAC);
        }
        return false;
        break;
      case WIN:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_WIN);
        }
        return false;
        break;
      case BACKLIT:
        if (record->event.pressed) {
          register_code(KC_RSFT);
          #ifdef BACKLIGHT_ENABLE
            backlight_step();
          #endif
          PORTE &= ~(1<<6);
        } else {
          unregister_code(KC_RSFT);
          PORTE |= (1<<6);
        }
        return false;
        break;
      case UMLAUT_A:
        if (shift_mask) {
          unregister_code(KC_LSFT);
          unregister_code(KC_RSFT);
          send_keyboard_report();

          send_altcode(196, record);

          if (shift_mask &MOD_BIT(KC_LSFT)) register_code(KC_LSFT);
          if (shift_mask &MOD_BIT(KC_RSFT)) register_code(KC_RSFT);

          send_keyboard_report();
        } else {
          send_altcode(228, record);
        }
        return false; break;
      case UMLAUT_O:
        if (shift_mask) {
          unregister_code(KC_LSFT);
          unregister_code(KC_RSFT);
          send_keyboard_report();

          send_altcode(214, record);

          if (shift_mask &MOD_BIT(KC_LSFT)) register_code(KC_LSFT);
          if (shift_mask &MOD_BIT(KC_RSFT)) register_code(KC_RSFT);

          send_keyboard_report();
        } else {
          send_altcode(246, record);
        }
        return false; break;
      case UMLAUT_U:
        if (shift_mask) {
          unregister_code(KC_LSFT);
          unregister_code(KC_RSFT);
          send_keyboard_report();

          send_altcode(220, record);

          if (shift_mask &MOD_BIT(KC_LSFT)) register_code(KC_LSFT);
          if (shift_mask &MOD_BIT(KC_RSFT)) register_code(KC_RSFT);

          send_keyboard_report();
        } else {
          send_altcode(252, record);
        }
        return false; break;
      case UMLAUT_S:
        send_altcode(223, record);
        return false; break;
    }
  }

  return true;
}


bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
