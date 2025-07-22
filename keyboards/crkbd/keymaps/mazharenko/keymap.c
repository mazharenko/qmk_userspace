#include "keycodes.h"
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
    UNI_HASH = KC_3, // #
    UNI_AT = KC_2, // @
};

enum hrm_keycodes {
    SMTD_KEYCODES_BEGIN = SAFE_RANGE,
    HOME_A1,
    HOME_S1,
    HOME_D1,
    HOME_F1,
    HOME_J1,
    HOME_K1,
    HOME_L1,
    HOME_SCLN1,
    SMTD_KEYCODES_END,
};

#include "sm_td.h"

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
    HASHROCKET,
    TD_QUOTES
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

void dance_quotes(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_BACKSLASH);
    } else if (state->count == 2) {
        tap_code16(KC_GRAVE);
    } else if (state->count == 3) {
        tap_code16(RALT(KC_NONUS_BACKSLASH));
    } else {
        reset_tap_dance (state);
    }
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_SLASHES] = ACTION_TAP_DANCE_FN(dance_slashes),
    [TD_SEMI_COLON] = ACTION_TAP_DANCE_DOUBLE(UNI_SEMICOLON, UNI_COLON),
    [TD_QUOTES] = ACTION_TAP_DANCE_FN(dance_quotes)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_smtd(keycode, record)) {
        return false;
    }
    switch (keycode) {
        case HASHROCKET:
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            return false;
    }

    return true;
}

void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(HOME_A1, KC_A, KC_LEFT_CTRL)
        SMTD_MT(HOME_S1, KC_S, KC_LEFT_ALT)
        SMTD_MT(HOME_D1, KC_D, KC_LEFT_GUI)
        SMTD_MT(HOME_F1, KC_F, KC_LSFT)
        SMTD_MT(HOME_J1, KC_J, KC_LSFT)
        SMTD_MT(HOME_K1, KC_K, KC_LEFT_GUI)
        SMTD_MT(HOME_L1, KC_L, KC_LEFT_ALT)
        SMTD_MT(HOME_SCLN1, KC_SCLN, KC_LEFT_CTRL)
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3_ex2(
  //,---------------------------------------------------------------------------.  ,-----------------------------------------------------------------------------------.
       KC_ESC,    KC_Q,  HOME_W,    KC_E,          KC_R,    KC_T,        XXXXXXX,                 KC_MUTE,    KC_Y,          KC_U,    KC_I,  HOME_O,      KC_P, KC_LBRC,
  //|--------+--------+--------+--------+--------------+--------+---------------|  |---------------------+--------+--------------+--------+--------+----------+--------|
      KC_RBRC,  HOME_A,  HOME_S,  HOME_D,        HOME_F,    KC_G,        XXXXXXX,                 XXXXXXX,    KC_H,        HOME_J,  HOME_K,  HOME_L, HOME_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------------+--------+---------------'  `---------------------+--------+--------------+--------+--------+----------+--------|
       KC_F13,    KC_Z,    KC_X,    KC_C,          KC_V,    KC_B,                                             KC_N,          KC_M, KC_COMM,  KC_DOT,   KC_SLSH,  KC_F14,
  //|--------+--------+--------+--------+--------------+--------+---------------.  ,---------------------+--------+--------------+--------+--------+----------+--------|
                                          LT(2, KC_TAB),  KC_SPC,  LT(1, KC_ENT),     LT(1, KC_BACKSPACE),  KC_SPC, LT(2, KC_DEL)
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------------------.  ,--------------------------------------------------------------------------------------------.
         XXXXXXX,  KC_P7, RALT_T(KC_P8), KC_P9,         XXXXXXX,   KC_MINUS, XXXXXXX,    XXXXXXX,      TD(TD_SLASHES),         UNI_LCUR,   UNI_RCUR,   RALT_T(UNI_EXLM), UNI_PERCENT, XXXXXXX,
  //|------------+------+--------------+------+----------------+--------------+--------|  |-----------+-----------------+-----------------+-----------+-----------+------------+--------|
      KC_KP_PLUS,  KC_P4,         KC_P5, KC_P6, LSFT_T(XXXXXXX),       TD(TD_QUOTES), XXXXXXX,    XXXXXXX,              UNI_AT, UNI_LBRC,   UNI_RBRC,   UNI_QUES,    UNI_ASTR, XXXXXXX,
  //|------------+------+--------------+------+----------------+--------------+--------'  `-----------+-----------------+-----------------+-----------+-----------+------------+--------|
      KC_KP_EQUAL, KC_P1,         KC_P2, KC_P3,           KC_P0,       XXXXXXX,                        TD(TD_SEMI_COLON),       UNI_LPAREN, UNI_RPAREN, HASHROCKET,    UNI_HASH, XXXXXXX,
  //|------------+------+--------------+------+----------------+--------------+--------.  ,-----------+-----------------+-----------------+-----------+-----------+------------+--------|
                                        LT(3, KC_TAB),       _______, _______,       _______,          _______, LT(3, KC_DEL)
                                     //`-------------------------------------'  `--------------------------------------------'
  ),

  [2] = LAYOUT_split_3x6_3_ex2(
  //,-------------------------------------------------------------------------.  ,---------------------------------------------------------------------------.
        KC_TAB,  KC_F7,    KC_F8,  KC_F9,   KC_F10,  XXXXXXX,     XXXXXXX,          XXXXXXX,  XXXXXXX,   KC_HOME,  KC_PAGE_UP,  XXXXXXX,  XXXXXXX,  KC_BSPC,
  //|-----------+---------+---------+---------+----------+---------+-----------|  |------------+---------+----------+---------+---------+---------+---------|
       KC_LCTL,  KC_F4,  KC_F5,  KC_F6,  KC_F11,  XXXXXXX,     XXXXXXX,          XXXXXXX,  KC_LEFT,    KC_DOWN,  KC_UP,  KC_RIGHT,  KC_INSERT,   XXXXXXX,
  //|-----------+---------+---------+---------+----------+---------+-----------'  `------------+---------+----------+---------+---------+---------+---------|
       KC_LSFT,  KC_F1,  KC_F2,  KC_F3,  KC_F12,  XXXXXXX,                                  XXXXXXX,  KC_END,   KC_PAGE_DOWN,  XXXXXXX,  XXXXXXX,  XXXXXXX,
  //|-----------+---------+---------+---------+----------+---------+-----------.  ,------------+---------+----------+---------+---------+---------+---------|
                                        _______,    _______,    LT(3, KC_ENT),        LT(3, KC_ENT),    _______,   _______
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

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [1] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [2] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(KC_BRID, KC_BRIU), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [3] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
};

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
