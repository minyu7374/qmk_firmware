#pragma once

/* dual-role键行为设定，参考：docs/tap_hold.md */

// Hold判定阈值，默认200，降低阈值，可加速Hold反应
// 提高阈值避免误激发Hold（同时可以更好的触发重复点击功能 QUICK_TAP_TERM 上限为TAPPING_TERM）
#define TAPPING_TERM 400

// 开启针对键值设置独立阈值
// #define TAPPING_TERM_PER_KEY

// Tap-Hold决策模式，默认不受其他按键影响
// 宽松按住模式 +A+B-B-A 触发Hold
#define PERMISSIVE_HOLD
// 激进模式 +A+B-B-A +A+B-A-B 都会触发Hold
// #define HOLD_ON_OTHER_KEY_PRESS

// 如果你按住一个双重功能按键并在没有按下其他键的情况下松开它，无论是否超过 TAPPING_TERM，系统都会发送点击功能对应的按键代码
#define RETRO_TAPPING
#define DUMMY_MOD_NEUTRALIZER_KEYCODE KC_F18
// #define MODS_TO_NEUTRALIZE {MOD_BIT(KC_RGUI), MOD_BIT(KC_RALT), MOD_BIT(KC_RSFT), MOD_BIT(KC_RCTL)}
#define MODS_TO_NEUTRALIZE {MOD_BIT(KC_RGUI)}

/* 以下为个人定义宏 */
// #define CUSTOM_MACRO_OPEN
// #define COMBO_OPEN

// #define USER_PASSWD "{user_passwd}"
// #define ROOT_PASSWD "{root_passwd}"
