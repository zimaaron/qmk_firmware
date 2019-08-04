# diverge4

A split 5x7 keyboard with 3 thumb keys. Made by [Unikeyboard](https://unikeyboard.io).

This qmk keyboard setup is minimally adapted from [IslandMan93s work on the diverge3](https://github.com/qmk/qmk_firmware/tree/master/keyboards/diverge3)

Keyboard Maintainer: [zimaaron](https://github.com/zimaaron)  
Hardware Supported: ARM-Cortex SAMD21G18A
Hardware Availability: [Diverge 4](https://unikeyboard.io/product/diverge/)

Make example for this keyboard (after setting up your build environment):

    make diverge4:default

Or for the [Colemak modDH](https://colemakmods.github.io/mod-dh/) layout:

    make diverge4:colemak

See [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) then the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information.

# Reflashing Animus
Reflashing the stock firmware is pretty easy. Just follow the same steps in the [original guide](https://imgur.com/a/8UapN). You will have to manually reset the Pro Micro (by shorting the GND and RST pins) during the upload step. Then reapply your keymap through Arbites.