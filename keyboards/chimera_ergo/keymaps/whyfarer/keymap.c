// this is the style you want to emulate.
// This is the canonical layout file for the Quantum project. If you want to add another keyboard,

#include QMK_KEYBOARD_H
#include "whyfarer.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum chimera_ergo_layers
{
  _QWERTY,
  _CAPS,
  _NUMPAD,
  _SYMBOLS,
  _MACROS,
  _NAVIG
};

enum custom_keycodes {
  SC_INCL = SAFE_RANGE,
  SC_PULL,
  SC_PUSH,
  SC_SCAP,
  SC_SCOF
};

#define SC_NAV MO(_NAVIG)

#define SC_S_NS LT(_NUMSYM,  KC_SPC)
#define SC_B_NS LT(_NUMSYM,  KC_BSPC)
#define SC_D_NS LT(_NUMSYM,  KC_DEL)

#define SC_B_TR MT(MOD_LCTL, KC_RBRC)
#define SC_SPLT MT(MOD_LALT, KC_MINS)
#define SC_SPRT MT(MOD_LALT, KC_1)
#define SC_GBRC MT(MOD_RGUI, KC_RBRC)
#define SC_MESC LT(_MACROS, KC_ESC)
#define SC_CAD LALT(LCTL(KC_DEL))

#define LONGPRESS_DELAY 150
//#define LAYER_TOGGLE_DELAY 300

/*
 * The `LAYOUT_crkbd_base` macro is a template to allow the use of identical
 * modifiers for the default layouts (eg QWERTY, Colemak, Dvorak, etc), so
 * that there is no need to set them up for each layout, and modify all of
 * them if I want to change them.  This helps to keep consistency and ease
 * of use. K## is a placeholder to pass through the individual keycodes
 */

#define LAYOUT_chimergo_base( \
    K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, \
    K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, \
    K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, \
    K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A  \
  ) \
  LAYOUT_wrapper( \
    KC_CAPS, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, KC_BSPC, \
    KC_ESC,  K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, KC_TAB,  \
    KC_ENT,  K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, KC_ENT,  \
    SC_NAV,  K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, SC_NAV,  \
                    SC_B_NS, SC_S_NS, SC_S_NS, SC_B_NS                  \
  )
#define LAYOUT_chimergo_base_wrapper(...)       LAYOUT_chimergo_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_COLEMAK] = LAYOUT_chimergo_base_wrapper(
    _________________NUMBER_LEFT_______________, _________________NUMBER_RIGHT______________,	    
    _________________COLEMAK_L1________________, _________________COLEMAK_R1________________,
    _________________COLEMAK_L2________________, _________________COLEMAK_R2________________,
    _________________COLEMAK_L3________________, _________________COLEMAK_R3________________
  ),

  [_NUMSYM] = LAYOUT(
    _________________NUMBER_LEFT_______________, _________________NUMBER_RIGHT______________,	    
    _________________NUMSYM_L1_________________, _________________NUMSYM_R1_________________,
    _________________NUMSYM_L2_________________, _________________NUMSYM_R2_________________,
    _________________NUMSYM_L3_________________, _________________NUMSYM_R3_________________
  ),

  [_NAV] = LAYOUT(
    _________________NUMBER_LEFT_______________, _________________NUMBER_RIGHT______________,	    
    _________________NAV_L1____________________, _________________NAV_R1____________________,
    _________________NAV_L2____________________, _________________NAV_R2____________________,
    _________________NAV_L3____________________, _________________NAV_R3____________________
  ),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
    /* include some kind of library or header */
    case SC_INCL:
      if (record->event.pressed) {
        SEND_STRING("#include <>");
        tap_code(KC_LEFT);
      }
      return false;
    case SC_PULL:
      if (record->event.pressed) {
        SEND_STRING("git pull");
        tap_code(KC_ENT);
      }
      return false;
    case SC_PUSH:
      if (record->event.pressed) {
        SEND_STRING("git push");
        tap_code(KC_ENT);
      }
      return false;
    case SC_SCAP:
      if (record->event.pressed) {
        layer_on(_CAPS);
        tap_code(KC_CAPS);
      }
      return false;
    case SC_SCOF:
      if (record->event.pressed) {
        layer_off(_CAPS);
        tap_code(KC_CAPS);
      }
      return false;
    default:
      return true;
  }
  return true;
};

void matrix_scan_user(void) {
    uint8_t layer = biton32(layer_state);

    switch (layer) {
      case _QWERTY:
          set_led_green;
          break;
        case _CAPS:
      set_led_white;
      break;
        case _NUMPAD:
            set_led_blue;
            break;
        case _SYMBOLS:
            set_led_red;
            break;
        case _NAV:
      set_led_magenta;
      break;
        case _MACROS:
      set_led_cyan;
      break;
       default:
            set_led_green;
            break;
    }
};
