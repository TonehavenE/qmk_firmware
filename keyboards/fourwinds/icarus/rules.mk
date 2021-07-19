# Build Options
MCU = STM32F411

BOOTLOADER = stm32-dfu

BOOTMAGIC_ENABLE = lite # Virtual DIP switch configuration
KEYBOARD_SHARED_EP = yes # USB endpoints
MOUSEKEY_ENABLE = no  # Mouse keys
EXTRAKEY_ENABLE = yes  # Audio control and System control
CONSOLE_ENABLE = no    # Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration
SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = no      # USB Nkey Rollover
AUDIO_ENABLE = no
RGBLIGHT_ENABLE = no
# OLED_DRIVER_ENABLE = yes

# LAYOUTS = ortho_4x5
# F_CPU = 16000000

