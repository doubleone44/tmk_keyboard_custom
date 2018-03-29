#include "keymap_common.h"
#include "rgb_led.h"

// Default
#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[KEYMAPS_COUNT][MATRIX_SIZE] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_SIZE] PROGMEM = {
#endif
    /* Keymap 0: Default Layer
     * ,-----------------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Psc|Pus|Del  |
     * |-----------------------------------------------------------------|
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Hom  |
     * |-----------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   \ |PgUp |
     * |-----------------------------------------------------------------|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |PgDn |
     * |---------------------------------------------------------,---.   |
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift  |Up|End  |
     * |-----------------------------------------------------------------|
     * |Ctrl|Gui |Alt |         Space          |Alt |Gui |Fn0|Lf|Do|Ri   |
     * `-----------------------------------------------------------------'
     */
    KEYMAP_ANSI_XD84(
        ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, PSCR,PAUS, DEL,  \
        GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,      HOME, \
        TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,      PGUP, \
        CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,       PGDN, \
        LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,    RSFT,       UP,  END,  \
        LCTL,LGUI,LALT,               SPC,                RALT,RGUI,FN0, LEFT, DOWN,RGHT),
};

/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[FN_ACTIONS_COUNT] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
const uint16_t fn_actions[] PROGMEM = {
#endif
};

#ifdef KEYMAP_IN_EEPROM_ENABLE
uint16_t keys_count(void) {
    return sizeof(keymaps) / sizeof(keymaps[0]) * MATRIX_SIZE;
}

uint16_t fn_actions_count(void) {
    return sizeof(fn_actions) / sizeof(fn_actions[0]);
}
#endif

#ifndef NO_ACTION_FUNCTION
enum function_id {
    AF_RGB_LED = 0
};

enum rgb_led_id {
    AF_RGB_LED_TOGGLE = 0,
    AF_RGB_LED_DECREASE,
    AF_RGB_LED_INCREASE,
    AF_RGB_LED_STEP,
    AF_RGB_LED_DECREASE_BRIGHTNESS,
    AF_RGB_LED_INCREASE_BRIGHTNESS
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
#ifdef RGB_LED_ENABLE
#define RGB_LED_BRIGHTNESS_STEP ((RGB_LED_BRIGHTNESS_MAX - RGB_LED_BRIGHTNESS_MIN) / 8)
    if (record->event.pressed) {
        switch (id) {
            case AF_RGB_LED:
                switch (opt) {
                    case AF_RGB_LED_TOGGLE:
                        rgb_led_toggle();
                        break;
                    case AF_RGB_LED_DECREASE:
                        rgb_led_decrease();
                        break;
                    case AF_RGB_LED_INCREASE:
                        rgb_led_increase();
                        break;
                    case AF_RGB_LED_STEP:
                        rgb_led_step();
                        break;
                    case AF_RGB_LED_DECREASE_BRIGHTNESS:
                        rgb_led_decrease_brightness(RGB_LED_BRIGHTNESS_STEP, true);
                        break;
                    case AF_RGB_LED_INCREASE_BRIGHTNESS:
                        rgb_led_increase_brightness(RGB_LED_BRIGHTNESS_STEP, true);
                        break;
                }
                break;
        }
    }
#endif
}
#endif