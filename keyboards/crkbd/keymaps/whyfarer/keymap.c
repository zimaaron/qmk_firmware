#include "whyfarer.h"
#include QMK_KEYBOARD_H

extern uint8_t is_master;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif
#ifdef OLED_DRIVER_ENABLE
#    define KEYLOGGER_LENGTH 5
static uint32_t oled_timer                       = 0;
static char     keylog_str[KEYLOGGER_LENGTH + 1] = {"\n"};
static uint16_t log_timer                        = 0;
// clang-format off
static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',  // 0x
    'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1', '2',  // 1x
    '3', '4', '5', '6', '7', '8', '9', '0',  20,  19,  27,  26,  22, '-', '=', '[',  // 2x
    ']','\\', '#', ';','\'', '`', ',', '.', '/', 128, ' ', ' ', ' ', ' ', ' ', ' ',  // 3x
    ' ', ' ', ' ', ' ', ' ', ' ', 'P', 'S', ' ', ' ', ' ', ' ',  16, ' ', ' ', ' ',  // 4x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 5x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 6x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 7x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 8x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // 9x
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ax
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Bx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Cx
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Dx
    'C', 'S', 'A', 'C', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',  // Ex
    ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '        // Fx
};

void add_keylog(uint16_t keycode);
#endif


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _COLEMAK 0
#define _NUMBER  1 // numsym layer 1 (only different thumb keys from layer 2)
#define _SYMBOL  2 // numsym layer 2 (only different thumb keys from layer 1)
#define _NAVIG   3 
#define _ADJUST  4

/*
enum custom_keycodes {
  COLEMAK = SAFE_RANGE,
  NUMBER,
  SYMBOL,
  NAVIG,
  ADJUST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};
*/

// define some custom keys
#define CK_NAV MO(_NAVIG)
#define CK_E_NAV LT(_NAVIG, KC_ENT)
#define CK_T_NAV LT(_NAVIG, KC_TAB)

#define CK_S_NUM LT(_NUMBER,  KC_SPC)

#define CK_B_SYM LT(_SYMBOL,  KC_BSPC)

#define CK_T_NAV LT(_NAVIG,   KC_TAB)
#define CK_B_NAV LT(_NAVIG,   KC_BSPC)
#define CK_E_NAV LT(_NAVIG,   KC_ENT)
#define CK_S_NAV LT(_NAVIG,   KC_SPC)
#define CK_D_NAV LT(_NAVIG,   KC_DEL)

/*
 * The `LAYOUT_crkbd_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes.
 * The layers are defined in qmk_firmware/users/whyfarer/wrappers.h
 */

#define LAYOUT_crkbd_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, \
              K33, K34, K35, K36, K37, K38 \
  ) \
  LAYOUT_wrapper( \
    KC_ESC,    K01,    K02,     K03,      K04,     K05,            K06,     K07,     K08,     K09,     K0A,     KC_ESC, \
    KC_TAB,    K11,    K12,     K13,      K14,     K15,            K16,     K17,     K18,     K19,     K1A,     KC_ENT, \
    CK_E_NAV,  K21,    K22,     K23,      K24,     K25,            K26,     K27,     K28,     K29,     K2A,     CK_T_NAV, \
                                K33,      K34,     K35,            K36,     K37,     K38 \
  )
#define LAYOUT_crkbd_base_wrapper(...)       LAYOUT_crkbd_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = LAYOUT_crkbd_base_wrapper(
    _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
    _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
    _________________COLEMAK_L3________________, _________________COLEMAK_R3________________,
                   CK_S_NAV, CK_B_SYM, CK_D_NAV, CK_E_NAV, CK_S_NUM, CK_B_NAV
  ),

  [_NUMBER] = LAYOUT_crkbd_base_wrapper(
    _________________NUMBER_L1_________________, _________________NUMBER_R1_________________,
    _________________NUMBER_L2_________________, _________________NUMBER_R2_________________,
    _________________NUMBER_L3_________________, _________________NUMBER_R3_________________,
                   CK_S_NAV, CK_B_SYM, CK_D_NAV, CK_T_NAV, CK_S_NUM, CK_B_NAV
  ),
  
  [_SYMBOL] = LAYOUT_crkbd_base_wrapper(
    _________________SYMBOL_L1_________________, _________________SYMBOL_R1_________________,
    _________________SYMBOL_L2_________________, _________________SYMBOL_R2_________________,
    _________________SYMBOL_L3_________________, _________________SYMBOL_R3_________________,
                   CK_S_NAV, CK_B_SYM, CK_D_NAV, CK_T_NAV, CK_S_NUM, CK_B_NAV
  ),

  [_NAVIG] = LAYOUT_crkbd_base_wrapper(
    _________________NAV_L1____________________, _________________NAV_R1____________________,
    _________________NAV_L2____________________, _________________NAV_R2____________________,
    _________________NAV_L3____________________, _________________NAV_R3____________________,
                   CK_S_NAV, CK_B_SYM, CK_D_NAV, KC_MS_BTN3, KC_MS_BTN1, KC_MS_BTN2
  ),

 
};
// clang-format on

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

/* bool process_record_user(uint16_t keycode, keyrecord_t *record) { */
/*   if (record->event.pressed) { */
/* #ifdef SSD1306OLED */
/*     set_keylog(keycode, record); */
/* #endif */
/*     // set_timelog(); */
/*   } */

/*   switch (keycode) { */
/*     case QWERTY: */
/*       if (record->event.pressed) { */
/*         persistent_default_layer_set(1UL<<_QWERTY); */
/*       } */
/*       return false; */
/*     case LOWER: */
/*       if (record->event.pressed) { */
/*         layer_on(_LOWER); */
/*         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
/*       } else { */
/*         layer_off(_LOWER); */
/*         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
/*       } */
/*       return false; */
/*     case RAISE: */
/*       if (record->event.pressed) { */
/*         layer_on(_RAISE); */
/*         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
/*       } else { */
/*         layer_off(_RAISE); */
/*         update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST); */
/*       } */
/*       return false; */
/*     case ADJUST: */
/*         if (record->event.pressed) { */
/*           layer_on(_ADJUST); */
/*         } else { */
/*           layer_off(_ADJUST); */
/*         } */
/*         return false; */
/*     case RGB_MOD: */
/*       #ifdef RGBLIGHT_ENABLE */
/*         if (record->event.pressed) { */
/*           rgblight_mode(RGB_current_mode); */
/*           rgblight_step(); */
/*           RGB_current_mode = rgblight_config.mode; */
/*         } */
/*       #endif */
/*       return false; */
/*     case RGBRST: */
/*       #ifdef RGBLIGHT_ENABLE */
/*         if (record->event.pressed) { */
/*           eeconfig_update_rgblight_default(); */
/*           rgblight_enable(); */
/*           RGB_current_mode = rgblight_config.mode; */
/*         } */
/*       #endif */
/*       break; */
/*   } */
/*   return true; */
/* } */
