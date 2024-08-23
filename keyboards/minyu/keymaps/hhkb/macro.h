#include QMK_KEYBOARD_H

#ifdef CUSTOM_MACRO_OPEN

enum custom_keycodes {
    KB_TOGG = SAFE_RANGE,
    PWD_MACRO
};

bool keyboard_locked = false; // 键盘锁定状态标志

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keyboard_locked && keycode != KB_TOGG) {
        return false;
    }

    switch (keycode) {
        case KB_TOGG:
            if (record->event.pressed) {
                keyboard_locked = !keyboard_locked; // 切换锁定状态
            }
            return false; // 阻止进一步处理此按键
            break;

        case PWD_MACRO:
            if (record->event.pressed) {
#    ifdef USER_PASSWD
                // 发送密码并确认
                SEND_STRING(USER_PASSWD);
                tap_code(KC_ENT);

                // 退回到上一行（发送 Shift + Up Arrow）
                register_mods(MOD_LSFT);   // 按住 Shift 键
                tap_code(KC_UP);           // 按下 Up Arrow
                unregister_mods(MOD_LSFT); // 释放 Shift 键

                // 清除密码（发送 Ctrl + K，或者发送退格键）
                /* register_mods(MOD_LCTL);   // 按住 Ctrl 键 */
                /* tap_code(KC_K);            // 按下 K 键 (在某些终端或编辑器中，Ctrl+K 清除行内容) */
                /* unregister_mods(MOD_LCTL); // 释放 Ctrl 键 */

                for (int i = 0; i < strlen(USER_PASSWD); i++) {
                    tap_code(KC_BSPC);
                }
#    endif

                return false; // 阻止进一步处理此按键
            }
            break;
    }

    return true;
}

#else

#    define KB_TOGG KC_NO
#    define PWD_MACRO KC_NO

#endif
