#include QMK_KEYBOARD_H

// 设置成不易误触的组合键
const uint16_t PROGMEM boot_combo[] = {KC_SPC, KC_B, COMBO_END};

combo_t key_combos[] = {
    COMBO(boot_combo, QK_BOOT),
};
