/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "pogues.h"


void set_mods_lights(uint16_t keycode, bool active);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // colemak-dh
    [LCMK] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX,   CTL_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,   CTL_Y, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
               KC_Q,    KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O, MY_COMP,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,   SFT_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H, KC_COMM,  KC_DOT, SFT_SLS, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               KC_LGUI, MO(LNUM), MOV_SPC,    SFT_BSP, MO(LSYM), KC_LALT
                                            //`--------------------------'  `--------------------------'
    ),
    [LSYM] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, KC_QUES, KC_LPRN, KC_RPRN, KC_PERC,                      KC_EXLM, MY_PIPE, KC_UNDS,   MY_AT, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              KC_NO, MY_TILD,  KC_GRV, KC_LBRC, KC_RBRC, KC_ASTR,                      KC_NUHS, MY_DQUO, KC_QUOT, KC_SCLN, KC_COLN, KC_NUBS,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,  KC_EQL,  MY_GBP, KC_LCBR, KC_RCBR, KC_SLSH,                      KC_AMPR,   KC_LT,   KC_GT,  KC_DLR, KC_CIRC, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               _______, _______, CTL_SPC,     _______,  _______, _______
                                            //`--------------------------'  `--------------------------'
    ),
    [LNUM] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX,  KC_INS, KC_UNDS,   KC_NO, KC_PERC,                      KC_PLUS,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              KC_NO, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT, KC_ASTR,                      KC_MINS,    KC_4,    KC_5,    KC_6, KC_ASTR, KC_PERC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, KC_BSPC,  KC_SPC, KC_COMM,  KC_DOT, KC_SLSH,                       KC_EQL,    KC_1,    KC_2,    KC_3, KC_SLSH, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, _______,  _______,     KC_0,  _______, _______
                                            //`--------------------------'  `--------------------------'
    ),
    [LFUN] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                       KC_F10,   KC_F7,   KC_F8,   KC_F9, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              KC_NO, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT,   KC_NO,                       KC_F11,   KC_F4,   KC_F5,   KC_F6,   KC_NO,   KC_NO,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                       KC_F12,   KC_F1,   KC_F2,   KC_F3,   KC_NO, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, _______,   KC_SPC,     _______, _______, _______
                                            //`--------------------------'  `--------------------------'
    ),
    [LMOV] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, ALT_TAB, RGB_VAD, RGB_VAI, RGB_TOG,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              KC_NO, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT,   KC_NO,                      KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT,  KC_ENT, KC_DEL,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, C(KC_Z), C(KC_X), C(KC_C),   KC_NO, C(KC_V),                        KC_NO,  KC_TAB, KC_PGDN, KC_PGUP,   KC_NO, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______,    KC_NO, _______,     _______,   KC_NO, _______
                                            //`--------------------------'  `--------------------------'
    ),
    [LMSE] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX,  KC_ESC,  KC_TAB,   KC_NO,   KC_NO,                        KC_NO,   KC_NO, KC_MS_U,   KC_NO, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              KC_NO, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT,   KC_NO,                      KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,  KC_DEL,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, C(KC_Z), C(KC_X), C(KC_C),   KC_NO, C(KC_V),                      KC_WH_D,   KC_NO,   KC_NO,   KC_NO,   KC_NO, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                _______,TO(LCMK),  KC_SPC,   KC_BTN1,  KC_BTN2, KC_BTN3
                                            //`--------------------------'  `--------------------------'
    ),
};


/******************************************************************************
 * user specific key processing
 ******************************************************************************/

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_achordion(keycode, record)) {
        return false;
    }
    if (!process_compose(keycode, record, MY_COMP)) {
        return false;
    }
    if (!process_case_modes(keycode, record)) {
        return false;
    }

    // set the mods lights the same as the one shots
    set_mods_lights(keycode, record->event.pressed);

    return true;
}


void matrix_scan_user(void) {
    achordion_task();
}

/*******************************************************************************
 * quick tap term keys (requires QUICK_TAP_TERM_PER_KEY set) a return of non 0
 * will enable tap then hold to autorepeat (which I generally dont want) but this
 * is required to get the ONESHOT_TAP_TOGGLE working
 *******************************************************************************/
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case OSM_SFT:
        case OSM_CTL:
        case OSM_GUI:
        case OSM_ALT:
            // make the one shot mod tap toggle work...
            return QUICK_TAP_TERM;
        default:
            // all others off (so the hold key is done on tap/hold rather than autorepeat)
            return 0;
    }
}

/*******************************************************************************
 * hold on other key (requires HOLD_ON_OTHER_KEY_PER_KEY set) a return of true
 * will mean that the hold action is triggered as soon as another key is pressed
 * (so D(k) D(anything) U(k) will cause hold_k and anything to be pressed)
 * a return of false will use the default behaviour from other settings
 *******************************************************************************/
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_Y:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

/********************************************************************************
 * achordion configuration
 ********************************************************************************/

/********************************************************************************
 * achordion_chord is called as the main config point.  return true to decide the
 * action as hold, false for a tap.
 ********************************************************************************/
bool achordion_chord(
    uint16_t tap_hold_keycode,
    keyrecord_t* tap_hold_record,
    uint16_t other_keycode,
    keyrecord_t* other_record
) {
    switch (tap_hold_keycode) {
        // shift and movement layer are on tap-hold keys and we want the hold to take
        // precedence even on same hands
        case MOV_SPC:
        case SFT_BSP:
            return true;
            break;

        // for the top right control we want "y " to take precedence over ctrl-space
        // and ctrl-v to take precedence over "yv"
        case CTL_Y:
            if (other_keycode == MOV_SPC) { return false; }
            if (other_keycode == KC_V) {return true; }
            break;
    }

    // Otherwise, follow the opposite hands rule.
    return achordion_opposite_hands(tap_hold_record, other_record);
}

// let achordion run for 800ms only
uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
    // switch (tap_hold_keycode) {
    //     case HOME_SC:
    //     case HOME_Z:
    //         return 0;  // Bypass Achordion for these keys.
    // }

    return 800;  // Otherwise use a timeout of 800 ms.
}

// achordion_eager_mod determines which mods are applied while waiting for the tap-hold
// to be resolved.  useful for ctrl-click for instance
bool achordion_eager_mod(uint8_t mod) {
    switch (mod) {
      // Eagerly apply Shift and Ctrl mods.
      case MOD_LSFT:
      case MOD_RSFT:
      case MOD_LCTL:
      case MOD_RCTL:
          return true;

      default:
          return false;
  }
}


/******************************************************************************
 * combo keys
 ******************************************************************************/
enum combo_keys {
    // left hand only
    WF_ESC,
    CD_TAB,
    ZX_Q,           // trial on zx for q - skeletyl

    RESET_COMBO,    // put the board into bootloader mode

    // right hand only
    UY_DEL,
    HCOM_ENT,
    JY_CTLBSP,
    DOTSLSH_COMPOSE,  // trial compose on right lower ring/pinkie for skeletyl

    // both hands, not using pl / fu any more due to typing mishits
    WY_LMSE,

    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM combo_esc[] = {CTL_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM combo_reset[] = {KC_ESC, KC_TAB, COMBO_END};
const uint16_t PROGMEM combo_del[] = {KC_U, CTL_Y, COMBO_END};
const uint16_t PROGMEM combo_ent[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_bspc[] = {KC_J, CTL_Y, COMBO_END};
const uint16_t PROGMEM combo_q[] = {SFT_Z, KC_X, COMBO_END};
const uint16_t PROGMEM combo_compose[] = {KC_DOT, SFT_SLS, COMBO_END};
const uint16_t PROGMEM combo_mouse[] = {CTL_W, CTL_Y, COMBO_END};

combo_t key_combos[] = {
    [WF_ESC] = COMBO(combo_esc, KC_ESC),
    [CD_TAB] = COMBO(combo_tab, KC_TAB),
    [ZX_Q] = COMBO(combo_q, KC_Q),

    [UY_DEL] = COMBO(combo_del, KC_DEL),
    [HCOM_ENT] = COMBO(combo_ent, KC_ENT),
    [JY_CTLBSP] = COMBO(combo_bspc, LCTL(KC_BSPC)),
    [DOTSLSH_COMPOSE] = COMBO(combo_compose, MY_COMP),
#ifdef MOUSEKEY_ENABLE
    [RESET_COMBO] = COMBO(combo_reset, QK_BOOTLOADER),
    [WY_LMSE] = COMBO(combo_mouse, TO(LMSE)),
#endif
};

/******************************************************************************
 * combo keys end
 ******************************************************************************/

/*******************************************************************************
 * RGB lighting on layer change
 * following are the LED numbers (in code it looks like we need to index one lower)
 * |------|------|------|------|------|------|            |------|------|------|------|------|
 * |  25  |  24  |  19  |  18  |  11  |  10  |            |      |      |      |      |      |
 * |------|------|------|------|------|------|            |------|------|------|------|------|
 * |  26  |  23  |  20  |  17  |  12  |  9   |            |      |      |      |      |      |
 * |------|------|------|------|------|------|            |------|------|------|------|------|
 * |  27  |  22  |  21  |  16  |  13  |  8   |            |      |      |      |      |      |
 * |------|------|------|------|------|------|            |------|------|------|------|------|
 *                      |  15  |  14  |  7   |            |      |      |
 *                      |------|------|------|            |------|------|
 *
 * reverse
 *      |------|------|------|
 *      |   1  |   2  |   3  |
 *      |------|------|------|
 *      |   4  |   5  |   6  |
 *      |------|------|------|
 *
 * to set colours on the modifier keys use the below.  RHS is 38, 43, 46, 49 for the numbers
    //{11, 1, HSV_BLUE},    // gui
    //{16, 1, HSV_GREEN},   // alt
    //{19, 1, HSV_ORANGE},  // ctrl
    //{22, 1, HSV_RED},     // shift
 ******************************************************************************/

#define THUMB_KEYS(colour) RGBLIGHT_LAYER_SEGMENTS( \
    { 6, 1, HSV_ ##colour}, \
    {13, 2, HSV_ ##colour}, \
    {33, 1, HSV_ ##colour}, \
    {40, 2, HSV_ ##colour} \
);
#define INNER_KEYS(colour) RGBLIGHT_LAYER_SEGMENTS( \
    {7, 3, HSV_ ##colour}, \
    {34, 3, HSV_ ##colour} \
);
#define INDEX_KEYS(colour) RGBLIGHT_LAYER_SEGMENTS( \
    {10, 3, HSV_ ##colour}, \
    {37, 3, HSV_ ##colour} \
);
#define MIDDLE_KEYS(colour) RGBLIGHT_LAYER_SEGMENTS( \
    {15, 3, HSV_ ##colour}, \
    {42, 3, HSV_ ##colour} \
);
#define RING_KEYS(colour) RGBLIGHT_LAYER_SEGMENTS( \
    {18, 3, HSV_ ##colour}, \
    {45, 3, HSV_ ##colour} \
);
#define PINKIE_KEYS(colour) RGBLIGHT_LAYER_SEGMENTS( \
    {21, 3, HSV_ ##colour}, \
    {48, 3, HSV_ ##colour} \
);

const rgblight_segment_t PROGMEM layer_default_lights[] = THUMB_KEYS(OFF)
const rgblight_segment_t PROGMEM layer_numpad_lights[] = THUMB_KEYS(ORANGE)
const rgblight_segment_t PROGMEM layer_symbols_lights[] = THUMB_KEYS(PURPLE)
const rgblight_segment_t PROGMEM layer_motion_lights[] = THUMB_KEYS(BLUE)
const rgblight_segment_t PROGMEM layer_functions_lights[] = THUMB_KEYS(RED)
const rgblight_segment_t PROGMEM layer_mouse_lights[] = THUMB_KEYS(WHITE)

const rgblight_segment_t PROGMEM oneshot_ctrl_active[] = MIDDLE_KEYS(BLUE)
const rgblight_segment_t PROGMEM oneshot_shift_active[] = INDEX_KEYS(GREEN)
const rgblight_segment_t PROGMEM oneshot_gui_active[] = RING_KEYS(RED)
const rgblight_segment_t PROGMEM oneshot_alt_active[] = PINKIE_KEYS(PURPLE)

// was INNER_KEYS(GREEN) but as this is similar to shift moved it to index.
const rgblight_segment_t PROGMEM caps_word_lights[] = INDEX_KEYS(GREEN)

const rgblight_segment_t PROGMEM compose_mode_lights[] = INNER_KEYS(ORANGE)
const rgblight_segment_t PROGMEM compose_cancel_lights[] = INNER_KEYS(RED)
const rgblight_segment_t PROGMEM compose_success_lights[] = INNER_KEYS(BLUE)

const rgblight_segment_t PROGMEM layer_no_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 54, HSV_OFF}
);

enum lighting_layers {
    RGBL_NO = 0,
    RGBL_DEFAULT,
    RGBL_SYMBOLS,
    RGBL_NUMPAD,
    RGBL_FUNCTIONS,
    RGBL_MOTION,
    RGBL_MOUSE,
    RGBL_CAPS_WORD,
    RGBL_COMPOSE,
    RGBL_COMPOSE_OK,
    RGBL_COMPOSE_CXL,
    RGBL_OSM_CTL,
    RGBL_OSM_SFT,
    RGBL_OSM_GUI,
    RGBL_OSM_ALT,
};

// now we need the array of layers
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    [RGBL_NO] = layer_no_lights,
    [RGBL_DEFAULT] = layer_default_lights,
    [RGBL_SYMBOLS] = layer_symbols_lights,
    [RGBL_NUMPAD] = layer_numpad_lights,
    [RGBL_FUNCTIONS] = layer_functions_lights,
    [RGBL_MOTION] = layer_motion_lights,
    [RGBL_MOUSE] = layer_mouse_lights,
    [RGBL_CAPS_WORD] = caps_word_lights,
    [RGBL_COMPOSE] = compose_mode_lights,
    [RGBL_COMPOSE_OK] = compose_success_lights,
    [RGBL_COMPOSE_CXL] = compose_cancel_lights,
    [RGBL_OSM_CTL] = oneshot_ctrl_active,
    [RGBL_OSM_SFT] = oneshot_shift_active,
    [RGBL_OSM_GUI] = oneshot_gui_active,
    [RGBL_OSM_ALT] = oneshot_alt_active
);

void keyboard_post_init_user(void) {
    //enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_set_layer_state(RGBL_NO, true);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // check the tristate layer and update
    state = update_tri_layer_state(state, LNUM, LSYM, LFUN);
    // TODO - find out why the below is not working..
    //state = update_tri_layer_state(state, LSYM, LMOV, LMSE);

    // set the led status to indicate layer
    rgblight_set_layer_state(RGBL_DEFAULT, layer_state_cmp(state, LCMK));
    rgblight_set_layer_state(RGBL_SYMBOLS, layer_state_cmp(state, LSYM));
    rgblight_set_layer_state(RGBL_NUMPAD, layer_state_cmp(state, LNUM));
    rgblight_set_layer_state(RGBL_FUNCTIONS, layer_state_cmp(state, LFUN));
    rgblight_set_layer_state(RGBL_MOTION, layer_state_cmp(state, LMOV));
    rgblight_set_layer_state(RGBL_MOUSE, layer_state_cmp(state, LMSE));
    return state;
}

void oneshot_mods_changed_user(uint8_t mods) {
    rgblight_set_layer_state(RGBL_OSM_CTL, mods & MOD_MASK_CTRL);
    rgblight_set_layer_state(RGBL_OSM_SFT, mods & MOD_MASK_SHIFT);
    rgblight_set_layer_state(RGBL_OSM_GUI, mods & MOD_MASK_GUI);
    rgblight_set_layer_state(RGBL_OSM_ALT, mods & MOD_MASK_ALT);
}


void oneshot_locked_mods_changed_user(uint8_t mods) {
    rgblight_set_layer_state(RGBL_OSM_CTL, mods & MOD_MASK_CTRL);
    rgblight_set_layer_state(RGBL_OSM_SFT, mods & MOD_MASK_SHIFT);
    rgblight_set_layer_state(RGBL_OSM_GUI, mods & MOD_MASK_GUI);
    rgblight_set_layer_state(RGBL_OSM_ALT, mods & MOD_MASK_ALT);
}

/*******************************************************************************
 * lighting changes for modifiers (including one shot...)
 *******************************************************************************/
void set_mods_lights(uint16_t keycode, bool active) {
    switch (keycode) {
        case KC_LSFT:
        case SFT_BSP:
        case SFT_Z:
        case SFT_SLS:
            rgblight_set_layer_state(RGBL_OSM_SFT, active);
            break;
        case KC_LCTL:
        case CTL_Y:
        case CTL_W:
            rgblight_set_layer_state(RGBL_OSM_CTL, active);
            break;
        case KC_LGUI:
            rgblight_set_layer_state(RGBL_OSM_GUI, active);
            break;
        case KC_LALT:
            rgblight_set_layer_state(RGBL_OSM_ALT, active);
            break;
    }
}
/******************************************************************************
 * compose key rgb lighting
 ******************************************************************************/
void compose_start(void) {
    rgblight_set_layer_state(RGBL_COMPOSE, true);
}


void compose_end(uint8_t state) {
    rgblight_set_layer_state(RGBL_COMPOSE, false);
    // show cancelled and error as the same state- we can only cancel by hitting the compose again
    if (state == COMPOSE_ERROR || state == COMPOSE_CANCELLED) {
        rgblight_blink_layer(RGBL_COMPOSE_CXL, 900);
    } else {
        // the compose action was activated
        rgblight_blink_layer(RGBL_COMPOSE_OK, 900);
    }
}
/******************************************************************************
 * compose end
 ******************************************************************************/


/*******************************************************************************
 * case_mode/caps word rgb lighting
 *******************************************************************************/
/* for now find the case mode too much mental overhead, generally want it for
 * this_style or THIS_STYLE but easy enough to hit the _!
void case_mode_set_user(bool active) {
    rgblight_set_layer_state(RGBL_SNAKE_CASE, active);
}*/

void caps_word_set_user(bool active) {
    rgblight_set_layer_state(RGBL_CAPS_WORD, active);
}
/******************************************************************************
 * case_mode end
 ******************************************************************************/


/*******************************************************************************
 * END RGB lighting on layer change
 ******************************************************************************/

