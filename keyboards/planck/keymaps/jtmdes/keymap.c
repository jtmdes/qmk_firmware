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

#include QMK_KEYBOARD_H
#include "g/keymap_combo.h"
#include "muse.h"

enum planck_layers {
  _COLEMAK,
  _QWERTY,
  _LOWER,
  _RAISE,
  _NUMPAD,
  _MOUSE,
  _ADJUST
};

enum planck_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  BACKLIT
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

// Left-hand home row mods
#define GUI_A LGUI_T(KC_A)
#define ALT_R LALT_T(KC_R)
#define CTL_S LCTL_T(KC_S)
#define SHFT_T LSFT_T(KC_T)

// Right-hand home row mods
#define SFT_N RSFT_T(KC_N)
#define CTL_E RCTL_T(KC_E)
#define ALT_I LALT_T(KC_I)
#define GUI_O RGUI_T(KC_O)

// Layer Taps
#define LOW_ENT LT(_LOWER,KC_ENT)
#define RSE_DEL LT(_RAISE,KC_DEL)
#define NUM_ESC LT(_NUMPAD,KC_ESC)
#define MSE_BKS LT(_MOUSE,KC_BSPC)

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool is_ctl_tab_active = false;
uint16_t ctl_tab_timer = 0;

enum {
  TD_CLN_SCLN = 0,
  TD_QUOT,
  TD_J_CAPS,
  TD_Y_WIN_E,
  TD_MINUS_US,
  TD_BS_LS,
  TD_EQ_PLUS,
  TD_TIL_GR,
  TD_LB_LC,
  TD_RB_RC,
  TD_LBRKT,
  TD_RBRKT
};

void dance_lbrk_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_LPRN);
    } else if (state->count == 2) {
		register_code(KC_LSFT);
        register_code(KC_LBRC);
    } else {
		register_code(KC_LBRC);
    }
}

void dance_lbrk_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_LPRN);
    } else if (state->count == 2) {
        unregister_code(KC_LSFT);
		unregister_code(KC_LBRC);
    } else {
		unregister_code(KC_LBRC);
	}
}

void dance_rbrk_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(KC_RPRN);
    } else if (state->count == 2) {
		register_code(KC_RSFT);
        register_code(KC_RBRC);
    } else {
		register_code(KC_RBRC);
    }
}

void dance_rbrk_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(KC_RPRN);
    } else if (state->count == 2) {
        unregister_code(KC_RSFT);
		unregister_code(KC_RBRC);
    } else {
		unregister_code(KC_RBRC);
	}
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CLN_SCLN] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, LSFT(KC_SCLN)),
  [TD_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, LSFT(KC_QUOT)),
  [TD_J_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_J, KC_CAPS),
  [TD_Y_WIN_E] = ACTION_TAP_DANCE_DOUBLE(KC_Y, LGUI(KC_E)),
  [TD_MINUS_US] = ACTION_TAP_DANCE_DOUBLE(KC_MINUS, LSFT(KC_MINUS)),
  [TD_BS_LS] = ACTION_TAP_DANCE_DOUBLE(KC_BSLASH, LSFT(KC_BSLASH)),
  [TD_EQ_PLUS] = ACTION_TAP_DANCE_DOUBLE(KC_EQUAL, LSFT(KC_EQUAL)),
  [TD_TIL_GR] = ACTION_TAP_DANCE_DOUBLE(KC_GRAVE, LSFT(KC_GRAVE)),
  [TD_LB_LC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRACKET, LSFT(KC_LBRACKET)),
  [TD_RB_RC] = ACTION_TAP_DANCE_DOUBLE(KC_RBRACKET, LSFT(KC_RBRACKET)),
  [TD_LBRKT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lbrk_finished, dance_lbrk_reset),
  [TD_RBRKT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_rbrk_finished, dance_rbrk_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Del  |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  | PRTSC|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   R  |   S  |   T  |   G  |   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   D  |   V  |   K  |   M  |   ,  |   .  |   /  |  UP  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  | ESC  |BKSPC |LOWER | Raise|Space |  Tab | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */

[_COLEMAK] = LAYOUT_planck_grid(
    KC_DEL,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    TD(TD_J_CAPS), KC_L,   KC_U,    KC_Y,    TD(TD_CLN_SCLN), KC_PSCR,
    KC_TAB,  GUI_A,   ALT_R,   CTL_S,   SHFT_T,  KC_G,    KC_M,          SFT_N,  CTL_E,   ALT_I,   GUI_O,           TD(TD_QUOT),
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,          KC_H,   KC_COMM, KC_DOT,  KC_SLSH,         KC_UP,
    KC_LCTL, KC_LALT, KC_LGUI, NUM_ESC, MSE_BKS, LOW_ENT, RSE_DEL,       KC_SPC, KC_TAB,  KC_LEFT, KC_DOWN,         KC_RGHT
),

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Del  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | PRTSC|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |  UP  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  | GUI  | ESC  |BKSPC |LOWER | Raise|Space |  Tab | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_DEL,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_PSCR,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_UP,
    KC_LCTL, KC_LALT, KC_LGUI, NUM_ESC, KC_BSPC, LOW_ENT, RSE_DEL, KC_SPC, KC_TAB,  KC_LEFT, KC_DOWN, KC_RGHT
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |CTRL-E|CTRL-H|CTRL-J|      |      | HOME |  UP  |  END | PGUP |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | C-S-K| COPY |PASTE |      |      | LEFT | DOWN | RIGHT| PGDN |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  |  F10 | F11  | F12  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Shift|      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TRNS, KC_TRNS, LCTL(KC_E), LCTL(KC_H), LCTL(KC_J), KC_TRNS, KC_TRNS, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_TRNS,
    KC_TRNS, KC_TRNS, RCS(KC_K),  LCTL(KC_C), LCTL(KC_V), KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_TRNS,
    KC_F1,   KC_F2,   KC_F3,      KC_F4,      KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS, KC_RSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |  `~  |  [{  |  -_  |      |      |  =+  |   ]} |  \|  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_TRNS, KC_EXLM, KC_AT,         KC_HASH,      KC_DLR,          KC_PERC, KC_CIRC, KC_AMPR,        KC_ASTR,      KC_LPRN,      KC_RPRN, KC_TRNS,
    KC_TRNS, KC_1,    KC_2,          KC_3,         KC_4,            KC_5,    KC_6,    KC_7,           KC_8,         KC_9,         KC_0,    KC_TRNS,
    KC_TRNS, KC_TRNS, TD(TD_TIL_GR), TD(TD_LBRKT), TD(TD_MINUS_US), KC_TRNS, KC_TRNS, TD(TD_EQ_PLUS), TD(TD_RBRKT), TD(TD_BS_LS), KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS,      KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS,      KC_TRNS,      KC_TRNS, KC_TRNS
),

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |      |   7  |   8  |   9  |   +  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  .   |   4  |   5  |   6  |   -  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  0   |   1  |   2  |   3  |   *  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_planck_grid(
 KC_TRNS, KC_7,    KC_8,    KC_9,    KC_PPLS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_DOT,  KC_4,    KC_5,    KC_6,    KC_PMNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_0,    KC_1,    KC_2,    KC_3,    KC_PAST, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
 ),

/* Mouse
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_MOUSE] = LAYOUT_planck_grid(
    KC_TRNS, KC_5,    KC_6,    KC_7,    KC_8,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_1,    KC_2,    KC_3,    KC_4,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* Adjust (Lower + Raise)
 *                      v------------------------RGB CONTROL--------------------v
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|Debug | RGB  |RGBMOD| HUE+ | HUE- | SAT+ | SAT- |BRGTH+|BRGTH-|  Del |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|AGnorm|AGswap|Colemk|Qwerty|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    _______, RESET,   DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI,  RGB_VAD, KC_DEL ,
    _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, COLEMAK, QWERTY,   _______, _______, _______,
    _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______,  _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
	case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
  }
  return true;
}

void encoder_update(bool clockwise) {
  if (IS_LAYER_ON(_LOWER)) {
    if (clockwise) {
      tap_code16(C(KC_LEFT));
    } else {
      tap_code16(C(KC_RIGHT));
    }
  } else if (IS_LAYER_ON(_NUMPAD)) {
	if (!is_alt_tab_active) {
      is_alt_tab_active = true;
      register_code(KC_LALT);
    }
	if (clockwise) {
      alt_tab_timer = timer_read();
      tap_code16(S(KC_TAB));
    } else {
      alt_tab_timer = timer_read();
      tap_code16(KC_TAB);
    }
  } else {
	if (!is_ctl_tab_active) {
      is_ctl_tab_active = true;
      register_code(KC_LCTL);
    }
    if (clockwise) {
      ctl_tab_timer = timer_read();
      tap_code16(S(KC_TAB));
    } else {
      ctl_tab_timer = timer_read();
      tap_code16(KC_TAB);
    }
  }
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0: {
#ifdef AUDIO_ENABLE
            static bool play_sound = false;
#endif
            if (active) {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_song); }
#endif
                layer_on(_ADJUST);
            } else {
#ifdef AUDIO_ENABLE
                if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
                layer_off(_ADJUST);
            }
#ifdef AUDIO_ENABLE
            play_sound = true;
#endif
            break;
        }
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif

  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 750) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
  if (is_ctl_tab_active) {
    if (timer_elapsed(ctl_tab_timer) > 750) {
      unregister_code(KC_LCTL);
      is_ctl_tab_active = false;
    }
  }
}

/*void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case CSC_EXCL:
      if (pressed) {
        tap_code16(LSFT(KC_1));
      }
      break;
    case FP_ATSYM:
      if (pressed) {
        tap_code16(LSFT(KC_2));
      }
      break;
  }
}*/

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
