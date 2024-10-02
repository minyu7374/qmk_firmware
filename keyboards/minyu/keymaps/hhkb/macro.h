#include QMK_KEYBOARD_H

#ifdef CUSTOM_MACRO_OPEN

enum custom_keycodes {
    KB_TOGG = SAFE_RANGE,

    // CK == custom key
    // CK_PWD_ ... 扩展不同的密码
    CK_PWD_USER,
    CK_PWD_ROOT
};

bool keyboard_locked = false; // 键盘锁定状态标志

#    define CK_PWD(x) CK_PWD_##x
#    define SEND_PASSWD(passwd)                                \
        {                                                      \
            /* 发送密码并确认 */                               \
            /* 使用SEND_STRING借助PSTR将静态字符串放入Flash */ \
            SEND_STRING(passwd);                               \
            tap_code(KC_ENT);                                  \
                                                               \
            /* 退回到上一行(发送 Shift + Up Arrow) */          \
            register_mods(MOD_LSFT);                           \
            tap_code(KC_UP);                                   \
            unregister_mods(MOD_LSFT);                         \
                                                               \
            /* 清除密码(发送等长退格键或Ctrl+K) */             \
            /* 使用sizeof而非strlen保证编译器优化 */           \
            for (int i = 0; i < sizeof(passwd) - 1; i++) {     \
                tap_code(KC_BSPC);                             \
            }                                                  \
        }

void ck_pwd_hander(enum custom_keycodes keycode) {
    // 编译时脚本会保证密码的宏要么不设置，要么是非空字符串，这里不做其他判断
    switch (keycode) {
        case CK_PWD_USER:
#    ifdef USER_PASSWD
            SEND_PASSWD(USER_PASSWD);
#    endif
            break;

        case CK_PWD_ROOT:
#    ifdef ROOT_PASSWD
            SEND_PASSWD(ROOT_PASSWD);
#    endif
            break;
        default:
            return;
    }
}

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

        case CK_PWD_USER:
        case CK_PWD_ROOT:
            if (record->event.pressed) {
                ck_pwd_hander(keycode);
                return false; // 阻止进一步处理此按键
            }
            break;
    }

    return true;
}

#else

#    define KB_TOGG KC_NO
#    define CK_PWD(x) KC_NO

#endif
