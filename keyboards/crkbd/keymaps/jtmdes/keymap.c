#include QMK_KEYBOARD_H

enum layers {
  _COLEMAK,
  _QWERTY,
  _ASETNIOP,
  _LOWER,
  _RAISE,
  _NUMPAD,
  _ADJUST
};

enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  QWERTY,
  ASETNIOP,
  LOWER,
  RAISE,
  NUMPAD,
  ADJUST
};

enum combo_events {
  CSC_EXCL,
  FP_ATSYM,
  DOTSL_QMRK,
  WP_TAB,
  QW_F5,
  WF_F2,
  ZX_F8,
  //Asetniop combos
  C_B,
  C_Q,
  C_D,
  C_G,
  C_F,
  C_M,
  C_K,
  C_J,
  C_L,
  C_W,
  C_P,
  C_H,
  C_C,
  C_U,
  C_X,
  C_V,
  C_Y,
  C_Z,
  C_COMM,
  C_DOT,
  C_XCL,
  C_QUES,
  C_TAB,
  C_ENT,
  C_BS,
  C_QUOT,
  C_COLN,
  C_DASH,
  C_LBRK,
  C_RBRK
};

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
 * | Shift|   A  |   R  |   S  |   T  |   G  |   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |   Z  |   X  |   C  |   D  |   V  |   K  |   M  |   ,  |   .  |   /  |  WIN |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      | ESC  |BKSPC |LOWER | Raise|Space |  Tab |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_split_3x6_3(
    KC_DEL,  KC_Q,  KC_W,  KC_F,    KC_P,    KC_B,          TD(TD_J_CAPS), KC_L,   KC_U,    KC_Y,   TD(TD_CLN_SCLN), KC_PSCR,
    KC_LSFT, GUI_A, ALT_R, CTL_S,   SHFT_T,  KC_G,          KC_M,          SFT_N,  CTL_E,   ALT_I,  GUI_O,           TD(TD_QUOT),
    KC_LCTL, KC_Z,  KC_X,  KC_C,    KC_D,    KC_V,          KC_K,          KC_H,   KC_COMM, KC_DOT, KC_SLSH,         KC_RGUI,
                           NUM_ESC, KC_BSPC, LOW_ENT,       RSE_DEL,       KC_SPC, KC_TAB
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
[_QWERTY] = LAYOUT_split_3x6_3(
    KC_DEL,  KC_Q, KC_W, KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,   KC_I,    KC_O,   KC_P,    KC_PSCR,
    KC_LSFT, KC_A, KC_S, KC_D,    KC_F,    KC_G,            KC_H,    KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT,
    KC_LCTL, KC_Z, KC_X, KC_C,    KC_V,    KC_B,            KC_N,    KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_RGUI,
                         NUM_ESC, KC_BSPC, LOW_ENT,         RSE_DEL, KC_SPC, KC_TAB
),

/* Asetniop
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   A  |   R  |   S  |   T  |      |      |   N  |   E  |   I  |   O  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |SHIFT |LOWER | Raise|SPACE |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ASETNIOP] = LAYOUT_split_3x6_3(
 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
 _______, KC_A,    KC_R,    KC_S,    KC_T,    _______, _______, KC_N,    KC_E,    KC_I,    KC_O,    _______,
 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                            _______, KC_LSFT, LOW_ENT, RSE_DEL, KC_SPC,  _______
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
[_LOWER] = LAYOUT_split_3x6_3(
    KC_TRNS, KC_TRNS,      LCTL(KC_E), LCTL(KC_H), LCTL(KC_J),         KC_TRNS,     KC_TRNS, KC_HOME, KC_UP,   KC_END,  KC_PGUP, KC_TRNS,
    KC_TRNS, LCTL(KC_TAB), RCS(KC_K),  LCTL(KC_C), LCTL(KC_V),         KC_TRNS,     KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_TRNS,
    KC_F1,   KC_F2,        KC_F3,      KC_F4,      KC_F5,              KC_F6,       KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
                           KC_TRNS,    KC_TRNS,    KC_TRNS,            MO(_ADJUST), KC_RSFT, KC_RCTL
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
[_RAISE] = LAYOUT_split_3x6_3(
    KC_TRNS, KC_EXLM, KC_AT,         KC_HASH,      KC_DLR,          KC_PERC,              KC_CIRC, KC_AMPR,        KC_ASTR,      KC_LPRN,      KC_RPRN, KC_TRNS,
    KC_TRNS, KC_1,    KC_2,          KC_3,         KC_P4,           KC_5,                 KC_6,    KC_7,           KC_8,         KC_9,         KC_0,    KC_TRNS,
    KC_TRNS, KC_TRNS, TD(TD_TIL_GR), TD(TD_LBRKT), TD(TD_MINUS_US), KC_TRNS,              KC_TRNS, TD(TD_EQ_PLUS), TD(TD_RBRKT), TD(TD_BS_LS), KC_TRNS, KC_TRNS,
                                     KC_TRNS,      KC_TRNS,         MO(_ADJUST),          KC_TRNS, KC_RSFT,        KC_TRNS
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
[_NUMPAD] = LAYOUT_split_3x6_3(
    KC_TRNS, KC_7, KC_8, KC_9,    KC_PLUS, KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_DOT,  KC_4, KC_5, KC_6,    KC_PMNS, KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_0,    KC_1, KC_2, KC_3,    KC_PAST, KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                         KC_TRNS, KC_TRNS, KC_TRNS,                    KC_TRNS, KC_TRNS, KC_TRNS
),

/* Adjust
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      | DEL  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      | Reset|Colemk|Qwerty|ASETNIOP|      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_split_3x6_3(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,       KC_TRNS, KC_DEL,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              RESET,   DF(_COLEMAK), DF(_QWERTY), DF(_ASETNIOP), KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS, KC_TRNS,      KC_TRNS,     KC_TRNS,       KC_TRNS, KC_TRNS,
                               KC_TRNS, KC_TRNS, KC_TRNS,              KC_TRNS, KC_TRNS,      KC_TRNS
) 

};

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

const uint16_t PROGMEM f2_combo[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM f5_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM f8_combo[] = {KC_Z, KC_X, COMBO_END};
const uint16_t PROGMEM excl_combo[] = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t PROGMEM atsym_combo[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM qmrk_combo[] = {KC_DOT, KC_SLSH, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_W, KC_P, COMBO_END};
//Asetniop combos
const uint16_t PROGMEM B_combo[] = {KC_T, KC_N, COMBO_END};
const uint16_t PROGMEM Q_combo[] = {KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM D_combo[] = {KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM G_combo[] = {KC_T, KC_I, COMBO_END};
const uint16_t PROGMEM F_combo[] = {KC_R, KC_S, COMBO_END};
const uint16_t PROGMEM M_combo[] = {KC_S, KC_N, COMBO_END};
const uint16_t PROGMEM K_combo[] = {KC_R, KC_N, COMBO_END};
const uint16_t PROGMEM J_combo[] = {KC_A, KC_N, COMBO_END};
const uint16_t PROGMEM L_combo[] = {KC_N, KC_O, COMBO_END};
const uint16_t PROGMEM W_combo[] = {KC_A, KC_R, COMBO_END};
const uint16_t PROGMEM P_combo[] = {KC_A, KC_T, COMBO_END};
const uint16_t PROGMEM H_combo[] = {KC_N, KC_E, COMBO_END};
const uint16_t PROGMEM C_combo[] = {KC_R, KC_T, COMBO_END};
const uint16_t PROGMEM U_combo[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM X_combo[] = {KC_A, KC_S, COMBO_END};
const uint16_t PROGMEM V_combo[] = {KC_T, KC_E, COMBO_END};
const uint16_t PROGMEM Y_combo[] = {KC_N, KC_I, COMBO_END};
const uint16_t PROGMEM Z_combo[] = {KC_R, KC_E, COMBO_END};
const uint16_t PROGMEM COMM_combo[] = {KC_S, KC_E, COMBO_END};
const uint16_t PROGMEM DOT_combo[] = {KC_R, KC_I, COMBO_END};
const uint16_t PROGMEM XCL_combo[] = {KC_E, KC_O, COMBO_END};
const uint16_t PROGMEM QUES_combo[] = {KC_T, KC_O, COMBO_END};
const uint16_t PROGMEM TAB2_combo[] = {KC_A, KC_R, KC_S, KC_T, COMBO_END};
const uint16_t PROGMEM ENT_combo[] = {KC_N, KC_E, KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM BS_combo[] = {KC_A, KC_O, COMBO_END};
const uint16_t PROGMEM QUOT_combo[] = {KC_S, KC_O, COMBO_END};
const uint16_t PROGMEM COLN_combo[] = {KC_I, KC_O, COMBO_END};
const uint16_t PROGMEM DASH_combo[] = {KC_S, KC_I, COMBO_END};
const uint16_t PROGMEM LBRK_combo[] = {KC_R, KC_O, COMBO_END};
const uint16_t PROGMEM RBRK_combo[] = {KC_S, KC_P, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [WF_F2] = COMBO(f2_combo, KC_F2),
  [QW_F5] = COMBO(f5_combo, KC_F5),
  [ZX_F8] = COMBO(f8_combo, KC_F8),
  [CSC_EXCL] = COMBO(excl_combo, KC_EXLM),
  [FP_ATSYM] = COMBO(atsym_combo, KC_AT),
  [DOTSL_QMRK] = COMBO(qmrk_combo, KC_QUES),
  [WP_TAB] = COMBO(tab_combo, KC_TAB),
  //Asetniop combos
  [C_B] = COMBO(B_combo, KC_B),
  [C_Q] = COMBO(Q_combo, KC_Q),
  [C_D] = COMBO(D_combo, KC_D),
  [C_G] = COMBO(G_combo, KC_G),
  [C_F] = COMBO(F_combo, KC_F),
  [C_M] = COMBO(M_combo, KC_M),
  [C_K] = COMBO(K_combo, KC_K),
  [C_J] = COMBO(J_combo, KC_J),
  [C_L] = COMBO(L_combo, KC_L),
  [C_W] = COMBO(W_combo, KC_W),
  [C_P] = COMBO(P_combo, KC_P),
  [C_H] = COMBO(H_combo, KC_H),
  [C_C] = COMBO(C_combo, KC_C),
  [C_U] = COMBO(U_combo, KC_U),
  [C_X] = COMBO(X_combo, KC_X),
  [C_V] = COMBO(V_combo, KC_V),
  [C_Y] = COMBO(Y_combo, KC_Y),
  [C_Z] = COMBO(Z_combo, KC_Z),
  [C_COMM] = COMBO(COMM_combo, KC_COMM),
  [C_DOT] = COMBO(DOT_combo, KC_DOT),
  [C_XCL] = COMBO(XCL_combo, KC_EXLM),
  [C_QUES] = COMBO(QUES_combo, KC_SLSH),
  [C_TAB] = COMBO(TAB2_combo, KC_TAB),
  [C_ENT] = COMBO(ENT_combo, KC_ENT),
  [C_BS] = COMBO(BS_combo, KC_BSPC),
  [C_QUOT] = COMBO(QUOT_combo, KC_QUOT),
  [C_COLN] = COMBO(COLN_combo, KC_SCLN),
  [C_DASH] = COMBO(DASH_combo, KC_MINUS),
  [C_LBRK] = COMBO(LBRK_combo, KC_LPRN),
  [C_RBRK] = COMBO(RBRK_combo, KC_RPRN)
};

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