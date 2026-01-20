/* Copyright 2022 Duccio Breschi <ducciobreschi@gmail.com>
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

enum layers {
  _COLEMAK,
  _QWERTY,
  _LOWER,
  _RAISE,
  _PROGRAM,
  _NUMPAD,
};

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  LOWER,
  RAISE,
  PROGRAM,
  NUMPAD
};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

bool is_ctl_tab_active = false;
uint16_t ctl_tab_timer = 0;

enum {
  TD_BS_LS = 0,
  TD_TIL_GR,
};

tap_dance_action_t tap_dance_actions[] = {
  [TD_BS_LS] = ACTION_TAP_DANCE_DOUBLE(KC_BACKSLASH, LSFT(KC_BACKSLASH)),
  [TD_TIL_GR] = ACTION_TAP_DANCE_DOUBLE(KC_GRAVE, LSFT(KC_GRAVE)),
};
// -----

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
#define NUM_BSP LT(_NUMPAD,KC_BSPC)
#define PRO_SPC LT(_PROGRAM,KC_SPC)

// LAYOUT_split_3x5_3

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Del  |   Q  |   W  |   F  |   P  |   B  |   J  |   L  |   U  |   Y  |   ;  | PRTSC|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   A  |   R  |   S  |   T  |   G  |   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |   Z  |   X  |   C  |   D  |   V  |   K  |   M  |   ,  |   .  |   /  |  WIN |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | ESC  |BKSPC |LOWER | Raise|Space |  Tab |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_split_3x5_3(
    KC_Q,  KC_W,  KC_F,     KC_P,    KC_B,          KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCLN,
    GUI_A, ALT_R, CTL_S,    SHFT_T,  KC_G,          KC_M,    SFT_N,   CTL_E,   ALT_I,  GUI_O,
    KC_Z,  KC_X,  KC_C,     KC_D,    KC_V,          KC_K,    KC_H,    KC_COMM, KC_DOT, KC_SLSH,
                  KC_ESC,   NUM_BSP, LOW_ENT,       RSE_DEL, PRO_SPC, KC_TAB
),

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Del  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | PRTSC|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |  WIN |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | ESC  |BKSPC |LOWER | Raise|Space |  Tab |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_split_3x5_3(
    KC_Q, KC_W, KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
    KC_A, KC_S, KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN,
    KC_Z, KC_X, KC_C,    KC_V,    KC_B,            KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH,
                KC_ESC,  NUM_BSP, LOW_ENT,         RSE_DEL, PRO_SPC, KC_TAB
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      | PRSC |CTRL-W|  F8  |WIN-E |      |      | HOME |  UP  |  END | PGUP |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | C-S-K|CTRL-H|CTRL-J|      |      | LEFT | DOWN | RIGHT| PGDN |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | SHIFT| CTRL |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_split_3x5_3(
    KC_PSCR, LCTL(KC_W), KC_F8,      LGUI(KC_E), KC_TRNS,         KC_TRNS, KC_HOME, KC_UP,   KC_END,  KC_PGUP,
    KC_TRNS, RCS(KC_K),  LCTL(KC_H), LCTL(KC_J), KC_TRNS,         KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
    KC_F5,   KC_F2,      KC_LSFT,    KC_LCTL,    KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS,    KC_TRNS,    KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS
 ),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |   `  |      |      |   ~  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_split_3x5_3(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,   KC_PERC,         KC_CIRC, KC_AMPR,        KC_ASTR, KC_LPRN, KC_RPRN,
    KC_1,    KC_2,    KC_3,    KC_4,     KC_5,            KC_6,    KC_7,           KC_8,    KC_9,    KC_0,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_GRAVE, KC_TRNS,         KC_TRNS, LSFT(KC_GRAVE), KC_RBRC, KC_TRNS, KC_TRNS,
                      KC_TRNS, KC_TRNS,  KC_TRNS,         KC_TRNS, KC_TRNS,        KC_TRNS
),

/* Program
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |   \  |      |      |   |  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |   [  |   {  |   (  |      |      |   )  |   }  |   ]  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |   &  |   #  |      |      |   %  |   $  |   ^  |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_PROGRAM] = LAYOUT_split_3x5_3(
    KC_TRNS, KC_TRNS, KC_TRNS,       KC_BACKSLASH, KC_TRNS,        KC_TRNS, LSFT(KC_BACKSLASH), KC_TRNS,       KC_TRNS, KC_TRNS,
    KC_TRNS, KC_LBRC, LSFT(KC_LBRC), KC_LPRN,      KC_TRNS,        KC_TRNS, KC_RPRN,            LSFT(KC_RBRC), KC_RBRC, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_AMPR,       KC_HASH,      KC_TRNS,        KC_TRNS, KC_PERC,            KC_DLR,        KC_CIRC, KC_TRNS,
                      KC_TRNS,       KC_TRNS,      KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS
),

/* Numpad
 * ,-----------------------------------------------------------------------------------.
 * |      |  =   |   7  |   8  |   9  |   +  |      |  F1  |  F2  |  F3  |  F4  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  .   |   4  |   5  |   6  |   -  |      |  F5  |  F6  |  F7  |  F8  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  0   |   1  |   2  |   3  |   *  |      |  F9  |  F10 |  F11 |  F12 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_split_3x5_3(
    KC_EQUAL, KC_7, KC_8,    KC_9,    KC_PLUS,            KC_TRNS, KC_F1,   KC_F2,  KC_F3,  KC_F4,
    KC_DOT,   KC_4, KC_5,    KC_6,    KC_PMNS,            KC_TRNS, KC_F5,   KC_F6,  KC_F7,  KC_F8,
    KC_0,     KC_1, KC_2,    KC_3,    KC_PAST,            KC_TRNS, KC_F9,   KC_F10, KC_F11, KC_F12,
                    KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS
)

};

//Combos

//Combo list
enum combos {
  CSC_EXCL,
  FP_ATSYM,
  DOTSL_QMRK,
  UNDRSCR,
  MINUS,
  LPARAN,
  RPARAN,
  S_QUOT,
  D_QUOT,
  C_SCLN,
  BG_CTLO,
  GV_CTLS,
  XC_CTLC,
  CD_CTLV,
  ZC_CTLX,
  XD_CTLZ,
  ZX_DEL,
  JL_CPLK,
  WF_ESC,
  QW_TAB,
  FS_MB1,
  WR_MB3,
  QA_MB2,
  DT_WHD,
  PT_WHU,
  COMBO_LENGTH
};

//Dynamic combo count
uint16_t COMBO_LEN = COMBO_LENGTH;

//characters
const uint16_t PROGMEM comdot_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM fp_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM sldot_combo[] = {KC_SLSH, KC_DOT, COMBO_END};
const uint16_t PROGMEM dv_combo[] = {KC_D, KC_V, COMBO_END};
const uint16_t PROGMEM pb_combo[] = {KC_P, KC_B, COMBO_END};
const uint16_t PROGMEM wp_combo[] = {KC_W, KC_P, COMBO_END};
const uint16_t PROGMEM ly_combo[] = {KC_L, KC_Y, COMBO_END};
const uint16_t PROGMEM hcom_combo[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM hdot_combo[] = {KC_H, KC_DOT, COMBO_END};
const uint16_t PROGMEM ysc_combo[] = {KC_Y, KC_SCLN, COMBO_END};

//actions
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM wf_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM bg_combo[] = {KC_B, KC_G, COMBO_END};
const uint16_t PROGMEM gv_combo[] = {KC_G, KC_V, COMBO_END};
const uint16_t PROGMEM xc_combo[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM cd_combo[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM zc_combo[] = {KC_Z, KC_C, COMBO_END};
const uint16_t PROGMEM xd_combo[] = {KC_X, KC_D, COMBO_END};
const uint16_t PROGMEM zx_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM jl_combo[] = {KC_J, KC_L, COMBO_END};

//function keys

//mouse buttons
const uint16_t PROGMEM fs_combo[] = {KC_F, LCTL_T(KC_S), COMBO_END};
const uint16_t PROGMEM wr_combo[] = {KC_W, LALT_T(KC_R), COMBO_END};
const uint16_t PROGMEM qa_combo[] = {KC_Q, LGUI_T(KC_A), COMBO_END};
const uint16_t PROGMEM dt_combo[] = {KC_D, LSFT_T(KC_T), COMBO_END};
const uint16_t PROGMEM pt_combo[] = {KC_P, LSFT_T(KC_T), COMBO_END};

//layer switching


combo_t key_combos[] = {
  //characters
  [CSC_EXCL] = COMBO(comdot_combo, KC_EXLM),
  [FP_ATSYM] = COMBO(fp_combo, KC_AT),
  [DOTSL_QMRK] = COMBO(sldot_combo, KC_QUES),
  [UNDRSCR] = COMBO(dv_combo, LSFT(KC_MINUS)),
  [MINUS] = COMBO(pb_combo, KC_MINUS),
  [LPARAN] = COMBO(wp_combo, KC_LPRN),
  [RPARAN] = COMBO(ly_combo, KC_RPRN),
  [S_QUOT] = COMBO(hcom_combo, KC_QUOT),
  [D_QUOT] = COMBO(hdot_combo, LSFT(KC_QUOT)),
  [C_SCLN] = COMBO(ysc_combo, LSFT(KC_SCLN)),
  //actions
  [WF_ESC] = COMBO(wf_combo, KC_ESC),
  [QW_TAB] = COMBO(qw_combo, KC_TAB),
  [BG_CTLO] = COMBO(bg_combo, LCTL(KC_O)),
  [GV_CTLS] = COMBO(gv_combo, LCTL(KC_S)),
  [XC_CTLC] = COMBO(xc_combo, LCTL(KC_C)),
  [CD_CTLV] = COMBO(cd_combo, LCTL(KC_V)),
  [ZC_CTLX] = COMBO(zc_combo, LCTL(KC_X)),
  [XD_CTLZ] = COMBO(xd_combo, LCTL(KC_Z)),
  [ZX_DEL] = COMBO(zx_combo, KC_DEL),
  [JL_CPLK] = COMBO(jl_combo, KC_CAPS),
  //function keys

  //mouse buttons
  [FS_MB1] = COMBO(fs_combo, MS_BTN1),
  [WR_MB3] = COMBO(wr_combo, MS_BTN3),
  [QA_MB2] = COMBO(qa_combo, MS_BTN2),
  [DT_WHD] = COMBO(dt_combo, MS_WHLD),
  [PT_WHU] = COMBO(pt_combo, MS_WHLU),
  //layer switch

};

//Encoder stuff, ctrl shift tab on right, alt shift tab on left
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
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
    } else if (index == 1) { /* Second encoder */
        if (!is_alt_tab_active) {
             is_alt_tab_active = true;
             register_code(KC_LALT);
        }
        if (clockwise) {
            alt_tab_timer = timer_read();
            tap_code16(KC_TAB);
        } else {
            alt_tab_timer = timer_read();
            tap_code16(S(KC_TAB));
        }
    }
	return false;
}

void matrix_scan_user(void) {
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
