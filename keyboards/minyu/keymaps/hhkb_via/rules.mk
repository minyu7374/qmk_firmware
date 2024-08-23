# via相关
VIA_ENABLE = yes
VIA_QMK_SUPPORT_ENABLE = yes
VIA_JSON = via_info.json
# DYNAMIC_KEYMAP_LAYER_COUNT = 5

LTO_ENABLE = yes

# 开发时使用，对于没有reset物理按钮的板子，方便进dfu
# . This is great for boards that don't have a physical reset button, giving you a way to jump into the bootloader
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite

COMBO_ENABLE = yes
KEY_LOCK_ENABLE = yes

MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
REPEAT_KEY_ENABLE = yes

CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work

MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend

RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
