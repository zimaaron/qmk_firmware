#pragma once // only use this file once in compilation

// Use custom magic number so that when switching branches, EEPROM always gets reset
#define EECONFIG_MAGIC_NUMBER (uint16_t)0x1337

// this makes it possible to do rolling combos (zx) with keys that
// convert to other keys on hold (z becomes ctrl when you hold it,
// and when this option isn't enabled, z rapidly followed by x
// actually sends Ctrl-x. That's bad.)
#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 200 // duration of hold longer than which a key press will be treated as a hold

/*

// lights from /users/drashna/config.h

#ifdef RGBLIGHT_ENABLE
#    undef RGBLIGHT_ANIMATIONS
#    if defined(__AVR__) && !defined(__AVR_AT90USB1286__)
#        define RGBLIGHT_SLEEP
#        define RGBLIGHT_EFFECT_BREATHING
#        define RGBLIGHT_EFFECT_SNAKE
#        define RGBLIGHT_EFFECT_KNIGHT
#    else
#        define RGBLIGHT_ANIMATIONS
#    endif
#endif  // RGBLIGHT_ENABLE

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES  // reacts to keypresses (will slow down matrix scan by a lot)
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (not recommened)
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED true  // turn off effects when suspended
// #   define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
// #   define EECONFIG_RGB_MATRIX (uint32_t *)16

#    if defined(__AVR__) && !defined(__AVR_AT90USB1286__)
#        define DISABLE_RGB_MATRIX_ALPHAS_MODS
#        define DISABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#        define DISABLE_RGB_MATRIX_BREATHING
#        define DISABLE_RGB_MATRIX_BAND_SAT
#        define DISABLE_RGB_MATRIX_BAND_VAL
#        define DISABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#        define DISABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#        define DISABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#        define DISABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#        define DISABLE_RGB_MATRIX_CYCLE_ALL
#        define DISABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#        define DISABLE_RGB_MATRIX_CYCLE_UP_DOWN
#        define DISABLE_RGB_MATRIX_CYCLE_OUT_IN
// #       define DISABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#        define DISABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#        define DISABLE_RGB_MATRIX_DUAL_BEACON
#        define DISABLE_RGB_MATRIX_CYCLE_PINWHEEL
#        define DISABLE_RGB_MATRIX_CYCLE_SPIRAL
#        define DISABLE_RGB_MATRIX_RAINBOW_BEACON
#        define DISABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#        define DISABLE_RGB_MATRIX_RAINDROPS
#        define DISABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// #       define DISABLE_RGB_MATRIX_TYPING_HEATMAP
#        define DISABLE_RGB_MATRIX_DIGITAL_RAIN
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#        define DISABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#        define DISABLE_RGB_MATRIX_SPLASH
#        define DISABLE_RGB_MATRIX_MULTISPLASH
#        define DISABLE_RGB_MATRIX_SOLID_SPLASH
#        define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#    endif  // AVR
#endif      // RGB_MATRIX_ENABLE

*/

/* Disable unused and unneeded features to reduce on firmware size */
#ifdef LOCKING_SUPPORT_ENABLE
#    undef LOCKING_SUPPORT_ENABLE
#endif
#ifdef LOCKING_RESYNC_ENABLE
#    undef LOCKING_RESYNC_ENABLE
#endif
