#include QMK_KEYBOARD_H

enum layers{
  _BASE,
  _COLEMAKDHM,
  _NUM_SYM,
  _NAV,
};

enum combos {
	OP_BSPC,
    EI_ENT
};

enum custom_keycodes {
    MACRO = SAFE_RANGE,
};

#define KC_NUM_SPC LT(_NUM_SYM, KC_SPC)
#define KC_SF LSFT_T(KC_F)
#define KC_SJ RSFT_T(KC_J)
#define KC_NAV_BSPC LT(_NAV, KC_BSPC)
#define KC_TS LSFT_T(KC_T)
#define KC_NS LSFT_T(KC_N)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
        KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,           KC_MPLY,       KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,
        KC_A,   KC_S,   KC_D,   KC_SF,  KC_G,                          KC_H,   KC_SJ,  KC_K,    KC_L,   KC_ENT,
        KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,                          KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,
                        KC_LCTL,  KC_NAV_BSPC,                          KC_NUM_SPC,   KC_LALT
  ), 

  [_COLEMAKDHM] = LAYOUT(
        KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,         KC_ESC,          KC_J,   KC_L,   KC_U,    KC_Y,   KC_SCLN,
        KC_A,   KC_R,   KC_S,   KC_TS,  KC_G,                          KC_M,   KC_NS,  KC_E,    KC_I,   KC_O,
        KC_Z,   KC_X,   KC_C,   KC_D,   KC_V,                          KC_K,   KC_H,   KC_TRNS, KC_TRNS, KC_TRNS,
                        KC_TRNS,  KC_TRNS,                             KC_TRNS,     KC_TRNS
  ),

  [_NUM_SYM] = LAYOUT(
        KC_BSLS,   KC_7,   KC_8,   KC_9,   KC_PLUS,        KC_MUTE,      KC_EXLM,     KC_AT,     KC_HASH,     KC_DLR,     KC_PERC,
        KC_DOT,    KC_4,   KC_5,   KC_6,   KC_MINS,                      KC_LPRN,     KC_RPRN,   KC_LBRC,     KC_RBRC,    KC_SCLN,
        KC_0,      KC_1,   KC_2,   KC_3,   KC_ASTR,                      KC_CIRC,     KC_MSEL,   KC_EQL,      KC_QUOT,    KC_GRV,
                           KC_TAB, KC_TRNS,                              KC_TRNS,        KC_TRNS
  ),

  [_NAV] = LAYOUT(
        RESET,     KC_F1,  KC_F2,  KC_F3,   TG(_COLEMAKDHM),       MACRO,       KC_PSCR,  KC_HOME,    KC_END,     KC_PGUP,  KC_BRID,
        KC_LALT,   KC_F4,  KC_F5,  KC_F6,   KC_END,                             KC_LEFT,  KC_DOWN,    KC_UP,      KC_RGHT,  KC_BRIU,
        KC_LCTL,   KC_F7,  KC_F8,  KC_F9,   KC_TRNS,                            KC_TRNS,  KC_TRNS,    KC_COMM,    KC_DOT,   KC_BSLS,
                           KC_TRNS,  KC_TRNS,                                   KC_TRNS,       KC_TRNS
  ),
};

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (biton32(layer_state))  {
            case _NUM_SYM:
                if (clockwise) {
                    if (!is_alt_tab_active) {
                        is_alt_tab_active = true;
                        register_code(KC_LALT);
                    } 
                    alt_tab_timer = timer_read();
                    tap_code16(KC_TAB);
                } else {
                    tap_code16(S(KC_TAB));
                }
                break;
    default:
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
        break;
    }
}
}

const uint16_t PROGMEM op_combo[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM qw_combo[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM ei_combo[] = {KC_E, KC_I, COMBO_END};


combo_t key_combos[COMBO_COUNT] = {
    [OP_BSPC] = COMBO(op_combo, KC_BSPC),
    [QW_ESC] = COMBO(qw_combo, KC_ESC),
    [EI_ENT] = COMBO(ei_combo, KC_ENT)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MACRO:
      if (record->event.pressed) {
        SEND_STRING(":kek:");
      }
      break;
  }
  return true;
};

