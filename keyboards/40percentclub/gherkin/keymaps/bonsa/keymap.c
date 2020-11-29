#include QMK_KEYBOARD_H

#define FN1_K     	LT(1, KC_K)
#define FN2_V     	LT(2, KC_V)
#define GUI_C       	LGUI_T(KC_C)
#define CTL_Z       	CTL_T(KC_Z)
#define ALT_X       	ALT_T(KC_X)
#define ALT_COMM       	ALGR_T(KC_COMM)
#define CTL_DOT       	RCTL_T(KC_DOT)
#define SHIFT_N     	RSFT_T(KC_N)
#define SHIFT_T     	LSFT_T(KC_T)


enum combos {
    EI_ENT,
    RS_SPC
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_3x10(
    KC_Q,     KC_W,    KC_F,   KC_P,    KC_B,      KC_J,     KC_L,     KC_U,        KC_Y,      KC_SCLN,
    KC_A,     KC_R,    KC_S,   SHIFT_T, KC_G,      KC_M,     SHIFT_N,  KC_E,        KC_I,      KC_O,
    CTL_Z,    ALT_X,   GUI_C,  KC_D,    FN2_V,     FN1_K,    KC_H,     ALT_COMM,    CTL_DOT,   KC_SLSH
  ),

  [1] = LAYOUT_ortho_3x10(
    KC_BSLS,  KC_7,    KC_8,   KC_9,    KC_PLUS,   KC_EXLM,  KC_AT,     KC_HASH,    KC_DLR,    KC_PERC,
    KC_DOT,   KC_4,    KC_5,   KC_6,    KC_MINS,   KC_LPRN,  KC_RPRN,   KC_LBRC,    KC_RBRC,   KC_DOT,
    KC_0,     KC_1,    KC_2,   KC_3,    KC_ASTR,   KC_CIRC,  KC_BSPC,   KC_EQL,     KC_QUOT,   KC_GRV
  ),

  [2] = LAYOUT_ortho_3x10(
    RESET,     KC_F1,  KC_F2,  KC_F3,   _______,   KC_PSCR,  KC_HOME,   KC_END,     KC_PGUP,   KC_BRIU,
    KC_LALT,   KC_F4,  KC_F5,  KC_F6,   KC_END,    KC_LEFT,  KC_DOWN,   KC_UP,      KC_RGHT,   KC_BRID,
    KC_LCTL,   KC_F7,  KC_F8,  KC_F9,   KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_COMM,    KC_DOT,    KC_BSLS
  ),
  

};

const uint16_t PROGMEM ei_combo[] = {KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM rs_combo[] = {KC_R, KC_S, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
    [EI_ENT] = COMBO(ei_combo, KC_ENT),
    [RS_SPC] = COMBO(rs_combo, KC_SPC)
};

