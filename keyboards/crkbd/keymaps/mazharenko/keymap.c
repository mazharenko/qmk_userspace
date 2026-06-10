#include "action.h"
#include "action_layer.h"
#include "action_util.h"
#include "keycodes.h"
#include "keymap.h"
#include <stdint.h>
#include "keymap_russian.h"
#include "keymap_us.h"
#include "modifiers.h"
#include "process_key_override.h"
#include "quantum.h"
#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _RU,
    _PUN,
    _FUN,
    _CMD
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

#define OS_LCAS OSM(MOD_LCTL | MOD_LALT | MOD_LSFT)

enum td {
    TD_SLASHES,
    TD_SEMI_COLON,
    TD_QUOTES
};

enum {
    HASHROCKET = SAFE_RANGE,
    RGB_VAD_NOEEPROM,
    RGB_VAI_NOEEPROM,
    GO_RU,
    GO_EN
};

// disable shift - to break the habit of typing KC_LABK and KC_RABK here
const key_override_t disable_shift_dot = ko_make_with_layers(MOD_MASK_SHIFT, KC_DOT, KC_DOT, 1 << _BASE);
const key_override_t disable_shift_comma = ko_make_with_layers(MOD_MASK_SHIFT, KC_COMM, KC_COMM, 1 << _BASE);

const key_override_t *key_overrides[] = {
    &disable_shift_dot,
    &disable_shift_comma,
    NULL
};

void dance_quotes(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code16(KC_DOUBLE_QUOTE);
    } else if (state->count == 2) {
        tap_code16(KC_QUOTE);
    } else if (state->count == 3) {
        tap_code16(KC_GRAVE);
    } else {
        reset_tap_dance (state);
    }
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_SLASHES] = ACTION_TAP_DANCE_DOUBLE(KC_BACKSLASH, KC_PIPE),
    [TD_SEMI_COLON] = ACTION_TAP_DANCE_DOUBLE(KC_SEMICOLON, KC_COLON),
    [TD_QUOTES] = ACTION_TAP_DANCE_FN(dance_quotes)
};


layer_state_t previous_layer_state;
layer_state_t layer_state_set_user(layer_state_t state) {

    if (IS_LAYER_ON_STATE(default_layer_state, _RU)) {
        if (IS_LAYER_ON_STATE(state, _PUN) && IS_LAYER_OFF_STATE(previous_layer_state, _PUN))
        {
            uint8_t os_mods = get_oneshot_mods();
            clear_oneshot_mods();
            tap_code16(KC_F13);
            set_oneshot_mods(os_mods);
        }
        if (IS_LAYER_ON_STATE(previous_layer_state, _PUN) && IS_LAYER_OFF_STATE(state, _PUN))
        {
            uint8_t os_mods = get_oneshot_mods();
            clear_oneshot_mods();
            tap_code16(KC_F14);
            set_oneshot_mods(os_mods);
        }
    }
    previous_layer_state = state;
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_ESC:
            if (get_oneshot_mods()){
                clear_oneshot_mods();
                return false;
            }
            break;
        // prevent one shot keys from working as normal mods
    //    case OS_LCTL:
    //        add_oneshot_mods(MOD_BIT(KC_LCTL));
    //        return false;
    //    case OS_LALT:
    //        add_oneshot_mods(MOD_BIT(KC_LALT));
    //        return false;
    //    case OS_LGUI:
    //        add_oneshot_mods(MOD_BIT(KC_LGUI));
    //        return false;
    //    case OS_LSFT:
    //        add_oneshot_mods(MOD_BIT(KC_LSFT));
    //        return false;
        case HASHROCKET:
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            return false;
        case RGB_VAI_NOEEPROM:
            rgb_matrix_increase_val_noeeprom();
            return false;
        case RGB_VAD_NOEEPROM:
            rgb_matrix_decrease_val_noeeprom();
            return false;
        case GO_EN:
            set_single_default_layer(_BASE);
            tap_code16(KC_F13);
            return false;
        case GO_RU:
            set_single_default_layer(_RU);
            tap_code16(KC_F14);
            return false;
    }

    return true;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------------------------.  ,----------------------------------------------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,             KC_R,    KC_T,          XXXXXXX,                   KC_MUTE,    KC_Y,             KC_U,    KC_I,    KC_O,      KC_P, XXXXXXX,
  //|--------+--------+--------+--------+-----------------+--------+-----------------|  |-----------------------+--------+-----------------+--------+--------+----------+--------|
      OS_LCTL,    KC_A,    KC_S,    KC_D,             KC_F,    KC_G,          XXXXXXX,                   XXXXXXX,    KC_H,             KC_J,    KC_K,    KC_L,    KC_DLR, KC_CIRC,
  //|--------+--------+--------+--------+-----------------+--------+-----------------'  `-----------------------+--------+-----------------+--------+--------+----------+--------|
        GO_EN,    KC_Z,    KC_X,    KC_C,             KC_V,    KC_B,                                                 KC_N,             KC_M, KC_COMM,  KC_DOT,   KC_AMPR,   GO_RU,
  //|--------+--------+--------+--------+-----------------+--------+-----------------.  ,-----------------------+--------+-----------------+--------+--------+----------+--------|
                                          LT(_FUN, KC_TAB),  KC_SPC, LT(_PUN, KC_ENT),    LT(_PUN, KC_BACKSPACE), OS_LSFT, LT(_FUN, KC_DEL)
                                      //`--------------------------------------------'  `--------------------------------------------------'

  ),

  [_RU] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,   RU_BE,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,   RU_HA,    _______, _______, _______, _______, _______,  RU_ZHE,    RU_E,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      _______, _______, RU_COMM,  RU_DOT,   RU_YU, _______,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,   _______, _______,  _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_PUN] = LAYOUT_split_3x6_3_ex2(
  //,----------------------------------------------------------------------------------------------.  ,------------------------------------------------------------------------------.
        KC_MINUS, XXXXXXX,           KC_LABK,   KC_LCBR,          KC_RCBR,         KC_RABK, XXXXXXX,    XXXXXXX,    KC_P1,            KC_P2,  KC_P3,     KC_EXLM, KC_PERCENT, XXXXXXX,
  //|-----------+--------+------------------+----------+-----------------+----------------+--------|  |--------+---------+-----------------+-------+------------+-----------+--------|
      KC_KP_PLUS,   KC_AT, TD(TD_SEMI_COLON),   KC_LBRC,          KC_RBRC,   TD(TD_QUOTES), XXXXXXX,      KC_P0,    KC_P4,            KC_P5,  KC_P6, KC_QUESTION,    KC_ASTR, XXXXXXX,
  //|-----------+--------+------------------+----------+-----------------+----------------+--------'  `--------+---------+-----------------+-------+------------+-----------+--------|
        KC_EQUAL, XXXXXXX,          KC_SLASH,   KC_LPRN,          KC_RPRN,  TD(TD_SLASHES),                         KC_P7,            KC_P8,  KC_P9,  HASHROCKET,    KC_HASH, XXXXXXX,
  //|-----------+--------+------------------+----------+-----------------+----------------+--------.  ,--------+---------+-----------------+-------+------------+-----------+--------|
                                                         LT(_FUN, KC_TAB),         _______, _______,    _______,  _______, LT(_FUN, KC_DEL)
                                                     //`-------------------------------------------'  `------------------------------------'
  ),

  [_FUN] = LAYOUT_split_3x6_3_ex2(
  //,----------------------------------------------------------------------.  ,------------------------------------------------------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,    KC_F6,       XXXXXXX,                KC_MUTE, KC_MEDIA_NEXT_TRACK, KC_HOME,   KC_PAGE_UP,   XXXXXXX,   XXXXXXX,  XXXXXXX,
  //--------+--------+--------+---------+--------+---------+--------------|  |--------------------+--------------------+--------+-------------+----------+----------+---------|
       OS_LCS, OS_LCTL, OS_LALT,  OS_LGUI, OS_LSFT,  OS_LCAS,       XXXXXXX,    KC_MEDIA_PLAY_PAUSE,             KC_LEFT, KC_DOWN,        KC_UP,  KC_RIGHT, KC_INSERT,  XXXXXXX,
  //|--------+--------+--------+---------+--------+---------+--------------'  `--------------------+--------------------+--------+-------------+----------+----------+---------|
        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,                                         KC_MEDIA_PREV_TRACK,  KC_END, KC_PAGE_DOWN,   XXXXXXX,   XXXXXXX,  XXXXXXX,
  //|--------+--------+--------+---------+--------+---------+--------------.  ,--------------------+--------------------+--------+-------------+----------+----------+---------|
                                           _______,  _______, KC_ENT,          KC_ENT,             _______, _______
                                       //`---------------------------------'  `--------------------------------------------------'
  ),


  [_CMD] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, _______, XXXXXXX,   XXXXXXX, _______,  XXXXXXX
                                      //`--------------------------'  `--------------------------'
  ),

};

#define ENCODER_NONE { XXXXXXX, XXXXXXX }

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_BASE] = { ENCODER_NONE, ENCODER_NONE, ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_NONE, },
  [_RU] = { ENCODER_NONE, ENCODER_NONE, ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_NONE, },
  [_PUN] = { ENCODER_NONE, ENCODER_NONE, ENCODER_CCW_CW(KC_BRID, KC_BRIU), ENCODER_NONE, },
  [_FUN] = { ENCODER_NONE, ENCODER_NONE, ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_NONE, },
  [_CMD] = { ENCODER_NONE, ENCODER_NONE, ENCODER_CCW_CW(RGB_VAD_NOEEPROM, RGB_VAI_NOEEPROM), ENCODER_NONE, },
};


#define HSV_BASE(hd) {162+hd, 180, 180}
#define HSV_BASE_FULL(hd) {162+hd, 180, 255}
#define HSV_ACC1 {31, 255, 255}
#define HSV_ACC2 {8, 255, 255}


const hsv_t PROGMEM matrix_colors[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3_ex2_hsv(
  //,-----------------------------------------------------------------------------------------------.  ,------------------------------------------------------------------------------------------------.
         HSV_ACC2,  HSV_BASE(4),  HSV_BASE(8), HSV_BASE(12),  HSV_BASE(16), HSV_BASE(20),  {HSV_OFF},      HSV_ACC2,  HSV_BASE(32), HSV_BASE(36), HSV_BASE(40), HSV_BASE(44), HSV_BASE(48),    {HSV_OFF},
  //|------------+-------------+-------------+-------------+--------------+-------------+-----------|  |-----------+--------------+-------------+-------------+-------------+-------------+-------------|
      HSV_BASE(4),  HSV_BASE(8), HSV_BASE(12), HSV_BASE(16),  HSV_BASE(20), HSV_BASE(24),  {HSV_OFF},     {HSV_OFF},  HSV_BASE(32), HSV_BASE(40), HSV_BASE(44), HSV_BASE(48), HSV_BASE(52), HSV_BASE(56),
  //|------------+-------------+-------------+-------------+--------------+-------------+-----------'  `-----------+--------------+-------------+-------------+-------------+-------------+-------------|
        {HSV_RED}, HSV_BASE(12), HSV_BASE(16), HSV_BASE(20),  HSV_BASE(24), HSV_BASE(28),                             HSV_BASE(40), HSV_BASE(44), HSV_BASE(48), HSV_BASE(52), HSV_BASE(56), HSV_BASE(60),
  //|------------+-------------+-------------+-------------+--------------+-------------+-----------.  ,-----------+--------------+-------------+-------------+-------------+-------------+-------------|
                                                                  HSV_ACC2, HSV_BASE(28),   HSV_ACC1,      HSV_ACC1,  HSV_BASE(44),     HSV_ACC2
                                                         //`----------------------------------------'  `----------------------------------------'
  ),
  [_RU] = LAYOUT_split_3x6_3_ex2_hsv(
  //,-------------------------------------------------------------------------------------------------.  ,------------------------------------------------------------------------------------------------.
         HSV_ACC2,  HSV_BASE(4),  HSV_BASE(8), HSV_BASE(12),  HSV_BASE(16), HSV_BASE(20),    {HSV_OFF},      HSV_ACC2,  HSV_BASE(32), HSV_BASE(36), HSV_BASE(40), HSV_BASE(44), HSV_BASE(48), HSV_BASE(52),
  //|------------+-------------+-------------+-------------+--------------+-------------+-------------|  |-----------+--------------+-------------+-------------+-------------+-------------+-------------|
      HSV_BASE(4),  HSV_BASE(8), HSV_BASE(12), HSV_BASE(16),  HSV_BASE(20), HSV_BASE(24), HSV_BASE(28),     {HSV_OFF},  HSV_BASE(32), HSV_BASE(40), HSV_BASE(44), HSV_BASE(48), HSV_BASE(52), HSV_BASE(56),
  //|------------+-------------+-------------+-------------+--------------+-------------+-------------'  `-----------+--------------+-------------+-------------+-------------+-------------+-------------|
      HSV_BASE(8), HSV_BASE(12), HSV_BASE(16), HSV_BASE(20),  HSV_BASE(24), HSV_BASE(28),                               HSV_BASE(40), HSV_BASE(44), HSV_BASE(48), HSV_BASE(52), HSV_BASE(56),    {HSV_RED},
  //|------------+-------------+-------------+-------------+--------------+-------------+-------------.  ,-----------+--------------+-------------+-------------+-------------+-------------+-------------|
                                                                  HSV_ACC2, HSV_BASE(28),     HSV_ACC1,      HSV_ACC1,  HSV_BASE(44),     HSV_ACC2
                                                         //`------------------------------------------'  `----------------------------------------'
  ),

    [_PUN] = LAYOUT_split_3x6_3_ex2_hsv(
  //,-----------------------------------------------------------------------------------------.  ,-----------------------------------------------------------------------------------------------------------.
      HSV_BASE(0),   {HSV_OFF},     HSV_ACC2,   HSV_ACC2,   HSV_ACC2,     HSV_ACC2,  {HSV_OFF},            HSV_ACC2, HSV_BASE_FULL(32),  HSV_BASE_FULL(36), HSV_BASE_FULL(40),  HSV_ACC1, HSV_ACC1, {HSV_OFF},
  //|------------+------------+-------------+-----------+-----------+-------------+-----------|  |-----------------+------------------+-------------------+------------------+----------+---------+----------|
      HSV_BASE(4), HSV_BASE(8), HSV_BASE(12),   HSV_ACC2,   HSV_ACC2, HSV_BASE(24),  {HSV_OFF},   HSV_BASE_FULL(32), HSV_BASE_FULL(36),  HSV_BASE_FULL(40), HSV_BASE_FULL(44),  HSV_ACC1, HSV_ACC1, {HSV_OFF},
  //|------------+------------+-------------+-----------+-----------+-------------+-----------'  `-----------------+------------------+-------------------+------------------+=---------+---------+----------|
      HSV_BASE(8),   {HSV_OFF}, HSV_BASE(16),   HSV_ACC2,   HSV_ACC2, HSV_BASE(28),                                  HSV_BASE_FULL(40),  HSV_BASE_FULL(44), HSV_BASE_FULL(48),  HSV_ACC1, HSV_ACC1, {HSV_OFF},
  //|------------+------------+-------------+-----------+-----------+-------------+-----------.  ,-----------------+------------------+-------------------+------------------+----------+--------------------|
                                                            HSV_ACC2, HSV_BASE(28),   HSV_ACC1,            HSV_ACC1,      HSV_BASE(44),           HSV_ACC2
                                                      //`-------------------------------------'  `--------------------------------------------------------'
  ),

    [_FUN] = LAYOUT_split_3x6_3_ex2_hsv(
  //,----------------------------------------------------------------------------------------------.  ,----------------------------------------------------------------------------------------.
      HSV_BASE(0),  HSV_BASE(4),  HSV_BASE(8), HSV_BASE(12),  HSV_BASE(16), HSV_BASE(20), {HSV_OFF},     HSV_ACC1,     HSV_ACC1, HSV_BASE(32), HSV_BASE(36), {HSV_OFF},    {HSV_OFF}, {HSV_OFF},
  //|------------+-------------+-------------+-------------+--------------+-------------+----------|  |----------+-------------+-------------+-------------+----------+-------------+----------|
         HSV_ACC1,     HSV_ACC2,     HSV_ACC2,     HSV_ACC2,      HSV_ACC2,     HSV_ACC1, {HSV_OFF},     HSV_ACC1,     HSV_ACC2,     HSV_ACC2,     HSV_ACC2,  HSV_ACC2, HSV_BASE(52), {HSV_OFF},
  //|------------+-------------+-------------+-------------+--------------+-------------+----------'  `----------+-------------+-------------+-------------+----------+-------------+----------|
      HSV_BASE(8), HSV_BASE(12), HSV_BASE(16), HSV_BASE(20),  HSV_BASE(24), HSV_BASE(28),                              HSV_ACC1, HSV_BASE(44), HSV_BASE(48), {HSV_OFF},    {HSV_OFF}, {HSV_OFF},
  //|------------+-------------+-------------+-------------+--------------+-------------+----------.  ,----------+-------------+-------------+-------------+----------+-------------+----------|
                                                                  HSV_ACC2, HSV_BASE(28),  HSV_ACC1,     HSV_ACC1, HSV_BASE(44),     HSV_ACC2
                                                          //`--------------------------------------'  `--------------------------------------'
  ),

    [_CMD] = LAYOUT_split_3x6_3_ex2_hsv(
  //,------------------------------------------------------------------------------------.  ,-------------------------------------------------------------------------------------.
        HSV_ACC2,  {HSV_OFF},  {HSV_OFF},  {HSV_OFF},   {HSV_OFF},  {HSV_OFF},  {HSV_OFF},      HSV_ACC2,   {HSV_OFF},   {HSV_OFF},  {HSV_OFF},  {HSV_OFF},  {HSV_OFF},  {HSV_OFF},
  //|-----------+-----------+-----------+-----------+------------+-----------+-----------|  |-----------+------------+------------+-----------+-----------+-----------+-----------|
       {HSV_OFF},  {HSV_OFF},  {HSV_OFF},  {HSV_OFF},   {HSV_OFF},  {HSV_OFF},  {HSV_OFF},     {HSV_OFF},   {HSV_OFF},   {HSV_OFF},  {HSV_OFF},  {HSV_OFF},  {HSV_OFF},  {HSV_OFF},
  //|-----------+-----------+-----------+-----------+------------+-----------+-----------'  `-----------+------------+------------+-----------+-----------+-----------+-----------|
       {HSV_OFF},  {HSV_OFF},  {HSV_OFF},  {HSV_OFF},   {HSV_OFF},  {HSV_OFF},                              {HSV_OFF},   {HSV_OFF},  {HSV_OFF},  {HSV_OFF},  {HSV_OFF},  {HSV_OFF},
  //|-----------+-----------+-----------+-----------+------------+-----------+-----------.  ,-----------+------------+------------+-----------+-----------+-----------+-----------|
                                                        {HSV_OFF},  {HSV_OFF},  {HSV_OFF},     {HSV_OFF},   {HSV_OFF},   {HSV_OFF}
                                                   //`-----------------------------------'  `-------------------------------------'
  ),
};


const uint8_t PROGMEM matrix_mods_colors[MATRIX_ROWS][MATRIX_COLS] =
    LAYOUT_split_3x6_3_ex2_hsv_mods(
  //,------------------------------------------------------------------------------.  ,-------------------------------------------------------------------------------------.
               0,             0,            0,            0,              0,  0,  0,             0,           0,           0,          0,          0,          0,          0,
  //|-----------+--------------+-------------+-------------+---------------+---+---|  |-----------+------------+------------+-----------+-----------+-----------+-----------|
               0, MOD_MASK_CTRL, MOD_MASK_ALT, MOD_MASK_GUI, MOD_MASK_SHIFT,  0,  0,             0,           0,           0,          0,          0,          0,          0,
  //|-----------+--------------+-------------+-------------+---------------+---+---'  `-----------+------------+------------+-----------+-----------+-----------+-----------|
               0,             0,            0,            0,              0,  0,                              0,           0,          0,          0,          0,          0,
  //|-----------+--------------+-------------+-------------+---------------+---+---.  ,-----------+------------+------------+-----------+-----------+-----------+-----------|
                                                                          0,  0,  0,             0, MOD_MASK_SHIFT,           0
                                                         //`-----------------------'  `-------------------------------------'
  );

void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state | default_layer_state);
    uint8_t oneshot_mods = get_oneshot_mods();

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index != NO_LED) {
                hsv_t hsv = matrix_colors[layer][row][col];

                uint8_t mod = matrix_mods_colors[row][col];
                if (oneshot_mods & mod) {
                    hsv = (hsv_t){HSV_RED};
                }

                uint8_t g_v = (uint32_t)rgb_matrix_config.hsv.v * 100 / RGB_MATRIX_MAXIMUM_BRIGHTNESS;
                hsv.h = hsv.h + rgb_matrix_config.hsv.h;
                hsv.v = (uint32_t)hsv.v * g_v / 100;
                rgb_t rgb = hsv_to_rgb(hsv);
                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
            }
        }
    }
    return false;
}
