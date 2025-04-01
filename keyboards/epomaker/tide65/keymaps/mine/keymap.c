// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "os_detection.h"
#include "rgb_record/rgb_record.h"

#define M_WINMD SAFE_RANGE
#define M_MACMD SAFE_RANGE+1

void set_os_mode(bool mac_mode) {
    keymap_config.swap_lalt_lgui = mac_mode;
    keymap_config.swap_ralt_rgui = mac_mode;
}

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            set_os_mode(true);
            break;
        default:
            set_os_mode(false);
            break;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case M_WINMD:
                set_os_mode(false); // Force Windows mode
                return false;
            case M_MACMD:
                set_os_mode(true); // Force macOS mode
                return false;
        }
    }
    return true;
}

enum layers {
    _BL = 0,    // Base Layer
    _FL,        // Function Layer
    _EL         // Escape Layer
    _CL,        // Caps Lock Layer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BL] = LAYOUT( /* Base */
                 LT(3, KC_ESC),   KC_1,      KC_2,      KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,       KC_MINS,  KC_EQL,   KC_BSPC,   KC_MUTE,
                 KC_TAB,          KC_Q,      KC_W,      KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_DEL,
                 LT(2, KC_CAPS),  KC_A,      KC_S,      KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,    KC_QUOT,            KC_ENT,    KC_PGUP,
                 KC_LSFT,         KC_Z,      KC_X,      KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,               KC_SLSH,  KC_RSFT,  KC_UP,     KC_PGDN,
                 KC_LCTL,         KC_LGUI,   KC_LALT,   KC_SPC,   KC_SPC,   KC_SPC,   KC_SPC,                       KC_RALT,              MO(1),    KC_LEFT,  KC_DOWN,   KC_RGHT
                 ),

    [_FL] = LAYOUT( /* Layer 1 - Function Layer */
                  KC_GRV,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  _______,  _______,
                 _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_HOME,  KC_SCRL,  _______,  _______,
                 _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,            _______,  _______,
                 _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,
                 _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,            _______,  _______,  _______,  _______
                ),

    [_EL] = LAYOUT( /* Layer 2 - Escape Hold */
                _______,  _______,       _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
                _______,  _______,       _______,  LGUI(KC_E), _______,  LCTL(LSFT(KC_ESC)), _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_MEDIA_PREV_TRACK,
                _______,  C(S(A(KC_A))), KC_PSCR,  _______,    _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,            _______,  KC_MEDIA_PLAY_PAUSE,
                _______,  _______,       _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,            _______,  _______,  _______,  KC_MEDIA_NEXT_TRACK,
                _______,  _______,       _______,  _______,    _______,  _______,            _______,                      _______,            _______,  _______,  _______,  _______
                ),

    [_CL] = LAYOUT( /* Layer 3 - Caps-lock Hold */
                QK_BOOT,   KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_USB,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RM_TOGG,
                _______,  _______,  M_WINMD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   QK_RBT,  _______,
                _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
                _______,  _______,  _______,  _______,  _______,  HS_BATQ,  _______,  M_MACMD,  _______,  _______,            _______,  _______,  RM_SPDU,  _______,
                _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,            _______,  RM_PREV,  RM_SPDD,  RM_NEXT
                ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [2] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [3] = { ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
};
#endif

const uint16_t PROGMEM rgbrec_default_effects[RGBREC_CHANNEL_NUM][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        HS_GREEN, ________,   ________,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, ________,   HS_GREEN,   ________, ________, ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, HS_GREEN,   HS_GREEN,   HS_GREEN, ________, ________, ________, ________, ________, ________, ________,   ________,           ________,  ________,
        ________, ________,   ________,   ________, ________, ________, ________, ________, ________, ________,             ________, ________, HS_GREEN,  ________,
        ________, ________,   ________,   ________, ________, ________, ________,                     ________,             ________, HS_GREEN, HS_GREEN,  HS_GREEN),

    [1] = LAYOUT(
        ________, HS_RED,     HS_RED,     HS_RED,   HS_RED,   HS_RED,   ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        HS_RED,   HS_RED,     HS_RED,     HS_RED,   HS_RED,   ________, ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, HS_RED,     HS_RED,     HS_RED,   ________, HS_RED,   ________, ________, ________, ________, ________,   ________,           ________,  ________,
        HS_RED,   ________,   ________,   ________, ________, HS_RED,   ________, ________, ________, ________,             ________, ________, ________,  ________,
        HS_RED,   ________,   HS_RED,     ________, ________, ________, ________,                     ________,             ________, ________, ________,  ________),

    [2] = LAYOUT(
        ________, HS_BLUE,    HS_BLUE,    HS_BLUE,  HS_BLUE,  HS_BLUE,  HS_BLUE,  HS_BLUE,  ________, ________, ________,   ________, ________, ________,  ________,
        ________, HS_BLUE,    HS_BLUE,    HS_BLUE,  HS_BLUE,  HS_BLUE,  ________, ________, ________, ________, ________,   ________, ________, ________,  ________,
        ________, HS_BLUE,    HS_BLUE,    HS_BLUE,  HS_BLUE,  HS_BLUE,  ________, ________, ________, ________, ________,   ________,           ________,  ________,
        ________, ________,   ________,   HS_BLUE,  HS_BLUE,  ________, ________, ________, ________, ________,             ________, ________, ________,  ________,
        ________, ________,   ________,   ________, ________, ________, ________,                     ________,             ________, ________, ________,  ________),
};

bool rgb_matrix_indicators_user(void) {
    // Check if Caps Lock is active
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(0, 0, 255, 0);
        rgb_matrix_set_color(1, 0, 255, 0);
        rgb_matrix_set_color(2, 0, 255, 0);
        rgb_matrix_set_color(3, 0, 255, 0);
    }
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case _FL:
            for (uint8_t i = 11; i < 23; i++) {
                rgb_matrix_set_color(i, RGB_BLUE);
            }
            break;
        case _CL:
            rgb_matrix_set_color(11, RGB_BLUE); // BT1
            rgb_matrix_set_color(12, RGB_BLUE); // BT2
            rgb_matrix_set_color(13, RGB_BLUE); // BT3
            rgb_matrix_set_color(14, RGB_BLUE); // 2.4GHz
            rgb_matrix_set_color(15, RGB_BLUE); // USB
            rgb_matrix_set_color(27, RGB_BLUE); // Right
            rgb_matrix_set_color(28, RGB_BLUE); // Down
            rgb_matrix_set_color(29, RGB_BLUE); // Up
            rgb_matrix_set_color(56, RGB_BLUE); // Left
            rgb_matrix_set_color(42, RGB_BLUE); // W
            rgb_matrix_set_color(62, RGB_BLUE); // M
            break;
        case _EL:
            rgb_matrix_set_color(41, RGB_BLUE); // E
            rgb_matrix_set_color(44, RGB_BLUE); // A
            rgb_matrix_set_color(45, RGB_BLUE); // S
            rgb_matrix_set_color(39, RGB_BLUE); // T
            rgb_matrix_set_color(24, RGB_BLUE); // Music Prev
            rgb_matrix_set_color(25, RGB_BLUE); // Music Play/Pause
            rgb_matrix_set_color(26, RGB_BLUE); // Music Next
            break;
        default:
            break;
    }
    return true;
}


// clang-format on
