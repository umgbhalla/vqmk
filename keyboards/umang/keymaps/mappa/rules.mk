
BOOTMAGIC_ENABLE = yes
SRC += display.c


SRC += ui/ui.c \
       ui/ui_Screen1.c \
       ui/thintel15.qff.c \

QUANTUM_PAINTER_ENABLE = yes
QUANTUM_PAINTER_DRIVERS += st7735_spi
CONSOLE_ENABLE = yes
LTO_ENABLE = yes
SERIAL_DRIVER = vendor
EXTRAKEY_ENABLE  = yes
RAW_ENABLE = yes
