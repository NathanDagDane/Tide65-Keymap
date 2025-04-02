// Copyright 2024 SDK (@sdk66)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "os_detection.h"
#include "rgb_record/rgb_record.h"

#define M_WINMD SAFE_RANGE
#define M_MACMD SAFE_RANGE+1

enum layers {
    _BL = 0,    // Base Layer
    _FL,        // Function Layer
    _EL,        // Escape Layer
    _MBL,       // Base Layer (Mac)
    _MFL,       // Function Layer (Mac)
    _MEL,       // Escape Layer (Mac)
    _CL         // Caps Lock Layer
};

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            tap_code16(TO(_BL));
            break;
        default:
            tap_code16(TO(_MBL));
            break;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BL] = LAYOUT( /* Base */
                 LT(_EL, KC_ESC), KC_1,      KC_2,      KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,       KC_MINS,  KC_EQL,   KC_BSPC,   KC_MUTE,
                 KC_TAB,          KC_Q,      KC_W,      KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_DEL,
                 LT(_CL, KC_CAPS),KC_A,      KC_S,      KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,    KC_QUOT,            KC_ENT,    KC_PGUP,
                 KC_LSFT,         KC_Z,      KC_X,      KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,               KC_SLSH,  KC_RSFT,  KC_UP,     KC_PGDN,
                 KC_LCTL,         KC_LGUI,   KC_LALT,   KC_SPC,   KC_SPC,   KC_SPC,   KC_SPC,                       KC_RALT,              MO(_FL),  KC_LEFT,  KC_DOWN,   KC_RGHT
                 ),

    [_FL] = LAYOUT( /* Layer 1 - Function Layer */
                  KC_GRV,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  _______,  _______,
                 _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_HOME,  KC_SCRL,  _______,  _______,
                 _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,            _______,  _______,
                 _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,
                 _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,            _______,  _______,  _______,  _______
                ),

    [_EL] = LAYOUT( /* Layer 2 - Escape Hold */
                _______,  _______,       _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,  _______,       _______,  _______,  _______,  _______,
                _______,  _______,       _______,  LGUI(KC_E), _______,  LCTL(LSFT(KC_ESC)), _______,  _______,  _______,  _______,  A(C(S(KC_F9))),_______,  _______,  _______,  KC_MEDIA_PREV_TRACK,
                _______,  C(S(A(KC_A))), KC_PSCR,  _______,    _______,  _______,            _______,  _______,  _______,  _______,  _______,       _______,            _______,  KC_MEDIA_PLAY_PAUSE,
                _______,  _______,       _______,  _______,    _______,  _______,            _______,  _______,  _______,  _______,                 _______,  _______,  _______,  KC_MEDIA_NEXT_TRACK,
                _______,  _______,       _______,  _______,    _______,  _______,            _______,                      _______,                 _______,  _______,  _______,  _______
                ),

    [_MBL] = LAYOUT( /* Layer 3 - Base (Mac) */
                 LT(_MEL, KC_ESC),KC_1,      KC_2,      KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,       KC_MINS,  KC_EQL,   KC_BSPC,   KC_MUTE,
                 KC_TAB,          KC_Q,      KC_W,      KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_LBRC,  KC_RBRC,  KC_BSLS,   KC_DEL,
                 LT(_CL, KC_CAPS),KC_A,      KC_S,      KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,    KC_QUOT,            KC_ENT,    KC_PGUP,
                 KC_LSFT,         KC_Z,      KC_X,      KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,               KC_SLSH,  KC_RSFT,  KC_UP,     KC_PGDN,
                 KC_LCTL,         KC_LALT,   KC_LCMD,   KC_SPC,   KC_SPC,   KC_SPC,   KC_SPC,                       KC_RALT,              MO(_MFL), KC_LEFT,  KC_DOWN,   KC_RGHT
                 ),

    [_MFL] = LAYOUT( /* Layer 4 - Function Layer (Mac) */
                  KC_GRV,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,  _______,  _______,
                 _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_HOME,  KC_SCRL,  _______,  _______,
                 _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,            _______,  _______,
                 _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,
                 _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,            _______,  _______,  _______,  _______
                ),

    [_MEL] = LAYOUT( /* Layer 5 - Escape Hold (Mac) */
                _______,  _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
                _______,  _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_MEDIA_PREV_TRACK,
                _______,  _______, KC_PSCR,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  KC_MEDIA_PLAY_PAUSE,
                _______,  _______, _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  KC_MEDIA_NEXT_TRACK,
                _______,  _______, _______,  _______,  _______,  _______,  _______,                      _______,            _______,  _______,  _______,  _______
                ),

    [_CL] = LAYOUT( /* Layer 3 - Caps-lock Hold */
                QK_BOOT,   KC_BT1,   KC_BT2,   KC_BT3,   KC_2G4,   KC_USB,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_TOG,
                _______,  _______,  TO(_BL),  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   QK_RBT,  _______,
                _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
                _______,  _______,  _______,  _______,  _______,  HS_BATQ,  _______,  TO(_MBL), _______,  _______,            _______,  _______,  RGB_SPD,  _______,
                _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,            _______,  RGB_RMOD, RGB_SPI,  RGB_MOD
                ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BL] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FL] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [_EL] = { ENCODER_CCW_CW(A(KC_F11), A(KC_F12)) },
    [_MBL] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_MFL] = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [_MEL] = { ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [_CL] = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
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
        rgb_matrix_set_color(0, 255, 0, 0);
        rgb_matrix_set_color(1, 255, 0, 0);
        rgb_matrix_set_color(2, 255, 0, 0);
        rgb_matrix_set_color(3, 255, 0, 0);
    }
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case _FL:
        case _MFL:
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
        case _MEL:
            rgb_matrix_set_color(41, RGB_BLUE); // E
            rgb_matrix_set_color(45, RGB_BLUE); // S
            rgb_matrix_set_color(66, RGB_BLUE); // C
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
