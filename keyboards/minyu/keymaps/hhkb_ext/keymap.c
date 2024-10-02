#include QMK_KEYBOARD_H
#include "macro.h"
#include "combo.h"

enum layer_tag {
    _BL = 0,
    _RFN,
    _LFN,
    _MOUSE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base layer
     * ,-----------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  `|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Bspc |
     * |-----------------------------------------------------------|
     * |LCtrl |  A|  S|  D|  F|  G|  H|  J|  K|  L|  :|  '|Return  |
     * |-----------------------------------------------------------|
     * |LShift |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|RShift|Del |  RShift = Up
     * |-----------------------------------------------------------|
     * |LFn |LAlt|LGui |          Space          |RGui |RAlt |RFn  |  RGui/RAlt/RFn = Left Down Right
     * `-----------------------------------------------------------'
     */
    [_BL] = LAYOUT_60_tsangan_hhkb(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, MT(MOD_RSFT, KC_UP), KC_DEL,
        MO(_LFN), KC_LALT, KC_LGUI, KC_SPC, MT(MOD_RGUI, KC_LEFT), MT(MOD_RALT, KC_DOWN), LT(_RFN, KC_RGHT)),

    /* HHKB Right Fn layer
     * ,-----------------------------------------------------------.
     * |Slep|F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Hlp|Pow|
     * |-----------------------------------------------------------|
     * |Caps |Nxt|Prv|Stp|Ply|Sel|   |   |Psc|Slk|Pus|Up |Ins|Del  |     -*- 代表按键透传, 主要准对功能按键(下同)
     * |-----------------------------------------------------------|
     * | -*-  |VoD|VoU|Mut|Ejc|  |RPWD|   |Hom|PgU|Lef|Rig|  -*-   |
     * |-----------------------------------------------------------|
     * |  -*-   |TGm|Tkb|Nkr|Lck|Clr|Rep|   |End|PgD|Dow|  -*- |-*-|
     * |-----------------------------------------------------------|
     * | -*- |-*-| -*- |                        |Wake  |Menu | -*- |
     * `-----------------------------------------------------------'
     */
    [_RFN] = LAYOUT_60_tsangan_hhkb(
        KC_SLEP, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_HELP, KC_KB_POWER,
        KC_CAPS, KC_MNXT, KC_MPRV, KC_MSTP, KC_MPLY, KC_MSEL, KC_NO, KC_NO, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP, KC_INS, KC_DEL,
        KC_TRNS, KC_VOLD, KC_VOLU, KC_MUTE, KC_EJCT, KC_NO, CK_PWD(ROOT), KC_NO, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_TRNS,
        KC_TRNS, TG(_MOUSE), KB_TOGG, NK_TOGG, QK_LOCK, EE_CLR, QK_REP, KC_NO, KC_END, KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_WAKE, KC_APP, KC_TRNS),

    /* HHKB Left Fn layer
     * ,-----------------------------------------------------------.
     * |Slep|F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Hlp|Pow|
     * |-----------------------------------------------------------|
     * |Caps |   |Up |Stp|Ply|Hom|   |   |Psc|Slk|Pus|Up |Ins|Del  |
     * |-----------------------------------------------------------|
     * | -*-  |Lef|Dow|Rig|End|  |UPWD|   |Hom|PgU|Lef|Rig|  -*-   |
     * |-----------------------------------------------------------|
     * |  -*-   |TGm|Tkb|Nkr|Lck|Clr|Rep|   |End|PgD|Dow|  -*- |-*-|
     * |-----------------------------------------------------------|
     * | -*- |-*-| -*- |                        |Wake  |Menu | -*- |
     * `-----------------------------------------------------------'
     */
    [_LFN] = LAYOUT_60_tsangan_hhkb(
        KC_SLEP, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_HELP, KC_KB_POWER,
        KC_CAPS, KC_NO, KC_UP, KC_MSTP, KC_MPLY, KC_HOME, KC_NO, KC_NO, KC_PSCR, KC_SCRL, KC_PAUS, KC_UP, KC_INS, KC_DEL,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_NO, CK_PWD(USER), KC_NO, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT, KC_TRNS,
        KC_TRNS, TG(_MOUSE), KB_TOGG, NK_TOGG, QK_LOCK, EE_CLR, QK_REP, KC_NO, KC_END, KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_WAKE, KC_APP, KC_TRNS),

    /* Mouse layer
     * ,-----------------------------------------------------------.
     * |-*-| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|   |   |
     * |-----------------------------------------------------------|
     * | -*- |   |McU|   |Ac0|   |Ac2|Ac1|Ac0|Ac1|Ac2|McU|   | -*- |
     * |-----------------------------------------------------------|
     * |  -*- |McL|McD|McR|Ac1|   |MwL|MwD|MwU|MwR|McL|McR|  -*-   |
     * |-----------------------------------------------------------|
     * |   -*-  |TGm|   |   |Ac2|Mb3|Mb2|Mb1|Mb4|Mb5|McD|  -*- |-*-|
     * |-----------------------------------------------------------'
     * | -*- |-*-| -*- |           Mb1          |  -*- |Menu | -*- |
     * `-----------------------------------------------------------'
     * Mc: Mouse Cursor / Mb: Mouse Button / Mw: Mouse Wheel
     * */
    [_MOUSE] = LAYOUT_60_tsangan_hhkb(
        KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO,
        KC_TRNS, KC_NO, KC_MS_U, KC_NO, KC_ACL0, KC_NO, KC_ACL2, KC_ACL1, KC_ACL0, KC_ACL1, KC_ACL2, KC_MS_U, KC_NO, KC_TRNS,
        KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_ACL1, KC_NO, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_MS_L, KC_MS_R, KC_TRNS,
        KC_TRNS, TG(_MOUSE), KC_NO, KC_NO, KC_ACL2, KC_BTN3, KC_BTN2, KC_BTN1, KC_BTN4, KC_BTN5, KC_MS_D, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_BTN1, KC_TRNS, KC_APP, KC_TRNS),
};
