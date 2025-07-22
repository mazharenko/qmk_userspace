#include QMK_KEYBOARD_H

enum uni_keycodes {
    UNI_LBRC = RALT(S(KC_LBRC)), // [
    UNI_RBRC = RALT(S(KC_RBRC)), // ]
    UNI_LCUR = RALT(KC_LBRC), // {
    UNI_RCUR = RALT(KC_RBRC), // }
    UNI_EXLM = KC_1, // !
    UNI_PERCENT = KC_5, // %
    UNI_QUES = KC_7, // ?
    UNI_ASTR = KC_8, // *
    UNI_COLON = KC_4, // ;
    UNI_SEMICOLON = KC_6, // :,
    UNI_LPAREN = KC_9, // (
    UNI_RPAREN = KC_0, // )
    UNI_HASH = KC_3, //
};

// home row mods
#define HOME_A LCTL_T(KC_A)
#define HOME_S LALT_T(KC_S)
#define HOME_D LGUI_T(KC_D)
#define HOME_F LSFT_T(KC_F)
#define HOME_J LSFT_T(KC_J)
#define HOME_K LGUI_T(KC_K)
#define HOME_L LALT_T(KC_L)
#define HOME_SCLN LCTL_T(KC_SCLN)
#define HOME_W RALT_T(KC_W)
#define HOME_O RALT_T(KC_O)

enum {
    TD_SLASHES,
    TD_SEMI_COLON,
    HASHROCKET
};

void dance_slashes(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(S(KC_BACKSLASH));
    } else if (state->count == 2) {
        tap_code16(S(KC_SEMICOLON));
    } else if (state->count == 3) {
        tap_code16(S(KC_QUOT));
    } else {
        reset_tap_dance (state);
    }
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_SLASHES] = ACTION_TAP_DANCE_FN(dance_slashes),
    [TD_SEMI_COLON] = ACTION_TAP_DANCE_DOUBLE(UNI_SEMICOLON, UNI_COLON)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HASHROCKET:
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            return false;
    }

    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3_ex2(
  //,---------------------------------------------------------------------------.  ,-----------------------------------------------------------------------------------.
       KC_ESC,    KC_Q,  HOME_W,    KC_E,          KC_R,    KC_T,        KC_LCTL,                 KC_RCTL,    KC_Y,          KC_U,    KC_I,  HOME_O,      KC_P, KC_LBRC,
  //|--------+--------+--------+--------+--------------+--------+---------------|  |---------------------+--------+--------------+--------+--------+----------+--------|
      KC_RBRC,  HOME_A,  HOME_S,  HOME_D,        HOME_F,    KC_G,        KC_LALT,                 KC_RALT,    KC_H,        HOME_J,  HOME_K,  HOME_L, HOME_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------------+--------+---------------'  `---------------------+--------+--------------+--------+--------+----------+--------|
       KC_F13,    KC_Z,    KC_X,    KC_C,          KC_V,    KC_B,                                             KC_N,          KC_M, KC_COMM,  KC_DOT,   KC_SLSH,  KC_F14,
  //|--------+--------+--------+--------+--------------+--------+---------------.  ,---------------------+--------+--------------+--------+--------+----------+--------|
                                          LT(2, KC_TAB),  KC_SPC,  LT(1, KC_ENT),     LT(1, KC_BACKSPACE),  KC_SPC, LT(2, KC_DEL)
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3_ex2(
  //,------------------------------------------------------------------------.  ,------------------------------------------------------------------------------------------.
         XXXXXXX,  KC_P7, KC_P8, KC_P9,       XXXXXXX,   KC_KP_MINUS, XXXXXXX,    XXXXXXX,      TD(TD_SLASHES),      UNI_LCUR,   UNI_RCUR,   UNI_EXLM, UNI_PERCENT, XXXXXXX,
  //|------------+------+------+------+--------------+--------------+--------|  |-----------+-----------------+--------------+-----------+-----------+------------+--------|
      KC_KP_PLUS,  KC_P4, KC_P5, KC_P6,       XXXXXXX,       XXXXXXX, XXXXXXX,    XXXXXXX,               KC_2,       UNI_LBRC,   UNI_RBRC,   UNI_QUES,    UNI_ASTR, XXXXXXX,
  //|------------+------+------+------+--------------+--------------+--------'  `-----------+-----------------+--------------+-----------+-----------+------------+--------|
      KC_KP_EQUAL, KC_P1, KC_P2, KC_P3,         KC_P0,       XXXXXXX,                        TD(TD_SEMI_COLON),    UNI_LPAREN, UNI_RPAREN, HASHROCKET,    UNI_HASH, XXXXXXX,
  //|------------+------+------+------+--------------+--------------+--------.  ,-----------+-----------------+--------------+-----------+-----------+------------+--------|
                                        LT(3, KC_TAB),       _______, _______,       _______,          _______, LT(3, KC_DEL)
                                     //`-------------------------------------'  `--------------------------------------------'
  ),

  [2] = LAYOUT_split_3x6_3_ex2(
  //,-------------------------------------------------------------------------.  ,---------------------------------------------------------------------------.
        KC_TAB,  KC_EXLM,    KC_AT,  KC_HASH,   KC_DLR,  KC_PERC,     KC_LCTL,          KC_RCTL,  KC_CIRC,   KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_BSPC,
  //|-----------+---------+---------+---------+----------+---------+-----------|  |------------+---------+----------+---------+---------+---------+---------|
       KC_LCTL,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,     KC_LALT,          KC_RALT,  KC_MINS,    KC_EQL,  KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_GRV,
  //|-----------+---------+---------+---------+----------+---------+-----------'  `------------+---------+----------+---------+---------+---------+---------|
       KC_LSFT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,                       KC_UNDS,  KC_PLUS,   KC_LCBR,  KC_RCBR,  KC_PIPE,  KC_TILD,
  //|-----------+---------+---------+---------+----------+---------+-----------.  ,------------+---------+----------+---------+---------+---------+---------|
                                        KC_LGUI,    _______,    KC_SPC,        KC_ENT,    _______,   KC_RGUI
                                     //`----------------------------'  `----------------------------'
  ),


  [3] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RGUI
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [1] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [2] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [3] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
};
#endif

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_AZURE);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i < led_max; i++) {
        switch(get_highest_layer(layer_state|default_layer_state)) {
            case 2:
                rgb_matrix_set_color(i, RGB_BLUE);
                break;
            case 1:
                rgb_matrix_set_color(i, RGB_YELLOW);
                break;
            default:
                break;
        }
    }
    return false;
}
