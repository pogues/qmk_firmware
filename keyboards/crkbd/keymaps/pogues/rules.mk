MOUSEKEY_ENABLE = yes     # Mouse keys
RGBLIGHT_ENABLE = yes    # Enable WS2812 RGB underlight.
OLED_ENABLE     = no
OLED_DRIVER     = SSD1306
COMBO_ENABLE    = yes
TAP_DANCE_ENABLE = yes

# nkro did work but is not needed
NKRO_ENABLE     = no
# not using system control or audio control
EXTRAKEY_ENABLE = no

# link time optimization to make the binary smaller
LTO_ENABLE      = yes

SRC += features/caps_word.c
SRC += features/layer_lock.c
SRC += features/custom_shift_keys.c	
SRC += features/compose.c
