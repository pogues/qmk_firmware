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
#include <stdio.h>
#include "features/casemodes.h"
#include "features/num_word.h"
#include "features/compose.h"
#include "features/custom_shift_keys.h"

enum userspace_layers {
    LCMK = 0,
    LSYM = 1,
    LNUM = 2,
    LFUN = 3,
    LMOV = 4,
    LMOV2 = 5,
    LMSE = 6,
};

// the layer mask
#define L_COLEMAK LCMK
#define LMASK_SYM (1 << LSYM)
#define LMASK_NUM (1 << LNUM)
#define LMASK_FUN (1 << LFUN)
#define LMASK_MOV (1 << LMOV)
#define LMASK_MOV2 (1 << LMOV2)
#define LMASK_MSE (1 << LMSE)

// rename some keys here to allow for the difference in keymap between US and GB
#define MY_PIPE LSFT(KC_NUBS)
#define MY_TILD KC_PIPE
#define MY_AT KC_DQUO
#define MY_DQUO LSFT(KC_2)
#define MY_GBP KC_HASH      // just shift-3
#define ALT_TAB ALT_T(KC_TAB)

// one shot mod and layer keys to make the map shorter
#define OSM_ALT OSM(MOD_LALT)
#define OSM_GUI OSM(MOD_LGUI)
#define OSM_CTL OSM(MOD_LCTL)
#define OSM_SFT OSM(MOD_LSFT)

#define CTL_BSP CTL_T(KC_BSPC)
#define SFT_SPC SFT_T(KC_SPC)
#define SFT_BSP SFT_T(KC_BSPC)
#define CTL_SPC CTL_T(KC_SPC)
#define CTL_Z CTL_T(KC_Z)
#define CTL_SLS CTL_T(KC_SLSH)

#define CTL_W CTL_T(KC_W)
#define CTL_Y CTL_T(KC_Y)
#define SFT_Z SFT_T(KC_Z)
#define SFT_SLS SFT_T(KC_SLSH)
#define SFT_QUO SFT_T(KC_QUOT)

enum custom_keycodes {
    MY_COMP = SAFE_RANGE,
};

// tap dance key enumaration
enum {
    TD_LNUM,
    TD_LSYM,
};

const custom_shift_key_t custom_shift_keys[] = {
    {KC_DOT , KC_COLN}, // Shift . is :
    {KC_COMM, KC_SCLN}, // Shift , is ;
    {SFT_SLS, KC_QUOT}, // Shift / is '
    // {SFT_QUO, MY_DQUO}, // shift ' is "
    // {CTL_BSP, KC_DEL}  // shift backspace is delete
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);


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
                                           // thumb keys.   originally had SFT_SPC and CTL_BSP on inner thumbs but mistyped space/shift alot
                                           // tried swapping to be CTL_SPC and SFT_BSP but hit ctrl too often accidentally TODO reconsider
                                           // tried no dual role keys on inner thumbs but found shift/backspace ok
                                           // now have no dual role key on space and use dual role alphas for that
                                           KC_LGUI, TD(TD_LNUM), KC_SPC,    SFT_BSP, TD(TD_LSYM), KC_LALT
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
                                               _______, _______, CTL_SPC,    _______,  _______, _______
                                            //`--------------------------'  `--------------------------'
    ),
    [LNUM] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX,   KC_NO, KC_UNDS,   KC_NO, KC_PERC,                      KC_PLUS,    KC_7,    KC_8,    KC_9, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              KC_NO, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT, KC_ASTR,                      KC_MINS,    KC_4,    KC_5,    KC_6,  KC_ENT, KC_BSPC,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,   KC_NO,   KC_NO, KC_COMM,  KC_DOT, KC_SLSH,                       KC_EQL,    KC_1,    KC_2,    KC_3, KC_SLSH, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, _______,  _______,     KC_0,  _______, _______
                                            //`--------------------------'  `--------------------------'
    ),
    [LFUN] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                       KC_F10,   KC_F7,   KC_F8,   KC_F9, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
           TO(LCMK), OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT,   KC_NO,                       KC_F11,   KC_F4,   KC_F5,   KC_F6,  KC_ENT,  KC_DEL,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                       KC_F12,   KC_F1,   KC_F2,   KC_F3,  KC_TAB, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, TO(LCMK), _______,     KC_F10,    KC_NO, _______
                                            //`--------------------------'  `--------------------------'
    ),
    // LMOV is entered by the combo of fu, LMOV2 is the same but entered with the tristate layer on num/sym 
    [LMOV] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, ALT_TAB,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_UP,   KC_NO, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
           TO(LCMK), OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT,   KC_NO,                      KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END, KC_DEL,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, C(KC_Z), C(KC_X), C(KC_C),   KC_NO, C(KC_V),                        KC_NO, KC_HOME, KC_PGDN, KC_PGUP,  KC_TAB, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                              _______, TO(LCMK), _______,     _______,    KC_NO, _______
                                            //`--------------------------'  `--------------------------'
    ),
    [LMOV2] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX, ALT_TAB,   KC_NO,   KC_NO,   KC_NO,                        KC_NO,   KC_NO,   KC_UP,   KC_NO, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              KC_NO, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT,   KC_NO,                      KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,  KC_END, KC_DEL,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX, C(KC_Z), C(KC_X), C(KC_C),   KC_NO, C(KC_V),                        KC_NO, KC_HOME, KC_PGDN, KC_PGUP,  KC_TAB, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                               _______, _______, _______,     _______,  _______, _______
                                            //`--------------------------'  `--------------------------'
    ),
    [LMSE] = LAYOUT_split_3x6_3(
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            XXXXXXX, XXXXXXX,   RESET,   KC_NO,   KC_NO, KC_BTN1,                        KC_NO,   KC_NO, KC_MS_U,   KC_NO, XXXXXXX, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
              KC_NO, OSM_ALT, OSM_GUI, OSM_CTL, OSM_SFT, KC_BTN1,                      KC_WH_U, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,  KC_DEL,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            XXXXXXX,TO(LCMK), KC_BTN3, KC_BTN2, KC_BTN1, KC_BTN2,                      KC_WH_D,   KC_NO,   KC_NO,   KC_NO,   KC_NO, XXXXXXX,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                _______,TO(LCMK), _______,   KC_BTN1,  KC_BTN2, KC_BTN3
                                            //`--------------------------'  `--------------------------'
    )
};


/******************************************************************************
 * user specific key processing
 ******************************************************************************/
bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (!process_compose(keycode, record, MY_COMP)) {
        return false;
    }
    if (!process_case_modes(keycode, record)) {
        return false;
    }
    if (!process_record_num_word(keycode, record, LNUM)) {
        return false;
    }
    if (!process_custom_shift_keys(keycode, record)) {
        return false;
    }

    return true;
}


/******************************************************************************
 * combo keys
 ******************************************************************************/
enum combo_keys {
    // naming is combo _ hand _ fingers (r=ring, m=middle, i=index) _ row (t=top, b=bottom) _ key
    // left hand only
    WF_ESC,
    CD_TAB,
    // right hand only
    UY_DEL,
    NUM_89_DEL,  // same as UY on num layer
    HCOM_ENT,
    NUM_12_ENT,  // same as H, on num layer
    JY_CTLBSP,

    // both hands
    FU_LMOV,
    WY_LFUN,
    PL_LMSE,
    
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM combo_wf[] = {CTL_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_cd[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM combo_uy[] = {KC_U, CTL_Y, COMBO_END};
const uint16_t PROGMEM combo_89[] = {KC_8, KC_9, COMBO_END};
const uint16_t PROGMEM combo_hcom[] = {KC_H, KC_COMM, COMBO_END};
const uint16_t PROGMEM combo_12[] = {KC_1, KC_2, COMBO_END};
const uint16_t PROGMEM combo_jy[] = {KC_J, CTL_Y, COMBO_END};
const uint16_t PROGMEM combo_fu[] = {KC_F, KC_U, COMBO_END};
const uint16_t PROGMEM combo_wy[] = {CTL_W, CTL_Y, COMBO_END};
const uint16_t PROGMEM combo_pl[] = {KC_P, KC_L, COMBO_END};

combo_t key_combos[] = {
    [WF_ESC] = COMBO(combo_wf, KC_ESC),
    [CD_TAB] = COMBO(combo_cd, KC_TAB),

    [UY_DEL] = COMBO(combo_uy, KC_DEL),
    [NUM_89_DEL] = COMBO(combo_89, KC_DEL),
    [HCOM_ENT] = COMBO(combo_hcom, KC_ENT),
    [NUM_12_ENT] = COMBO(combo_12, KC_ENT),
    [JY_CTLBSP] = COMBO(combo_jy, LCTL(KC_BSPC)),

    [FU_LMOV] = COMBO(combo_fu, TO(LMOV)),
    [WY_LFUN] = COMBO(combo_wy, TO(LFUN)),
    [PL_LMSE] = COMBO(combo_pl, TO(LMSE)),
};

/******************************************************************************
 * combo keys end
 ******************************************************************************/


/******************************************************************************
 * compose key mapping function
 ******************************************************************************/
uint8_t compose_mapping(uint16_t* sequence, uint8_t sequence_len) {
    // NOTE that the COMPOSE_MAPPING will return if there is a full or partial
    // match to the sequence.

    /**********************************************************************
     * general
     *********************************************************************/
    // caps word
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_C),
        { toggle_caps_word(); }
    )
    // snake_case
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_S),
        { enable_xcase_with(KC_UNDS); }
    )
    // camelCase
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_K),
        { enable_xcase_with(OSM(MOD_LSFT)); }
    )
    // path (/) case
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_P),
        { enable_xcase_with(KC_SLSH); }
    )
    // quit dwm
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_Q),
        { SEND_STRING(SS_LGUI(SS_LSFT("q"))); }
    )

    /**********************************************************************
     * copy paste
     *********************************************************************/
    // copy all
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_A, KC_C),
        { SEND_STRING(SS_LCTL("ac")); }
    )
    // cut all
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_A, KC_X),
        { SEND_STRING(SS_LCTL("ax")); }
    )
    // paste
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_A, KC_P),
        { SEND_STRING(SS_LCTL("v")); }
    )

    /**********************************************************************
     * qzdev
     *********************************************************************/
    // open a file
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_O),
        { SEND_STRING(SS_LCTL(SS_LSFT("o"))); }
    )

    /**********************************************************************
     * qzdev diff
     *********************************************************************/
    // diff current
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_C),
        { SEND_STRING(SS_LCTL(SS_LSFT("g"))); }
    )
    // diff approved
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_A),
        { SEND_STRING(SS_LCTL(SS_LSFT("v"))); }
    )
    // diff prod
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_P),
        { SEND_STRING(SS_LCTL(SS_LSFT("p"))); }
    )
    // diff head
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_H),
        { SEND_STRING(SS_LCTL(SS_LSFT("e"))); }
    )
    // diff against version
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_D, KC_V),
        { SEND_STRING(SS_LCTL(SS_LSFT("d"))); }
    )

    /**********************************************************************
     * qzdev vc
     *********************************************************************/
    // vc blame
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_B),
        { SEND_STRING(SS_LCTL(SS_LSFT("b"))); }
    )

    // vc log
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_L),
        { SEND_STRING(SS_LCTL(SS_LSFT("l"))); }
    )

    // vc commit
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_C),
        { SEND_STRING(SS_LCTL(SS_LSFT("c"))); }
    )

    // vc request review
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_R),
        { SEND_STRING(SS_LCTL(SS_LSFT("w"))); }
    )

    // push to
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_P),
        { SEND_STRING(SS_LCTL(SS_LSFT("s"))); }
    )

    // vc update
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_V, KC_U),
        { SEND_STRING(SS_LCTL(SS_LSFT("u"))); }
    )

    /**********************************************************************
     * qzdev run test
     *********************************************************************/
    // run test function
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_T, KC_F),
        { SEND_STRING(SS_LCTL(SS_TAP(X_F10))); }
    )
    // run test class
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_T, KC_C),
        { SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_F10)))); }
    )
    // run test module
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_T, KC_S),
        { SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_F10)))); }
    )

    /**********************************************************************
     * qzdev run
     *********************************************************************/
    // run script
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_R, KC_S),
        { tap_code(KC_F9); }
    )
    // run script with restart
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_R, KC_R),
        { SEND_STRING(SS_LCTL(SS_TAP(X_F9))); }
    )

    return COMPOSE_ERROR;
}


void compose_start(void) {
    rgblight_set_layer_state(8, true);
}


void compose_end(uint8_t state) {
    rgblight_set_layer_state(8, false);
    if (state == COMPOSE_ERROR) {
        rgblight_blink_layer(9, 900);
    } else if (state == COMPOSE_CANCELLED) {
        rgblight_blink_layer(10, 900);
    } else {
        // the compose action was activated
        rgblight_blink_layer(15, 900);
    }
}
/******************************************************************************
 * compose end
 ******************************************************************************/


/*******************************************************************************
 * caps word mode
 *******************************************************************************/
void caps_word_set_user(bool active) {
    rgblight_set_layer_state(7, active);
}


/*******************************************************************************
* Tap Dance definitions
*******************************************************************************/
typedef struct {
    bool is_press_action;
    uint8_t step;
} td_tap_t;

static td_tap_t dance_state_lnum = {.is_press_action = true, .step = 0};
static td_tap_t dance_state_lsym = {.is_press_action = true, .step = 0};

// simplified dance steps to indicate held, one tap or two
enum {
    SINGLE_TAP = 1,
    DOUBLE_TAP,
    HELD,
};


uint8_t current_dance_step(qk_tap_dance_state_t *state) {
    if (state->pressed) {
        return HELD;
    }
    if (state->count == 1) {
        return SINGLE_TAP;
    } else {  // everything over one is taken as double
        return DOUBLE_TAP;
    }
}

/* no common layer_dance_finished as we are using numword not a one shot */

void layer_dance_reset(uint8_t layer,  td_tap_t *tap_state, qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (tap_state->step) {
        case SINGLE_TAP:
        case DOUBLE_TAP:
            break;
        case HELD:
            layer_off(layer);
            break;
    }
    tap_state->step = 0;
}

/** 
 * for the num layer
 *   single tap enters num_word mode, or exits if we are in num_word mode or the number layer
 *   double tap enters the layer as TO(layer)
 *   hold enters the layer as MO(layer) until released
 */
void tapdance_lnum_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state_lnum.step = current_dance_step(state);
    switch (dance_state_lnum.step) {
        case SINGLE_TAP:
            if (is_num_word_enabled()) {
                disable_num_word(LNUM);
            } else if (layer_state_is(LNUM)) {
                layer_off(LNUM);
            } else {
                enable_num_word(LNUM);
            }
            break;
        case DOUBLE_TAP:
        case HELD:
            layer_on(LNUM);
            break;
    }
}


void tapdance_lnum_reset(qk_tap_dance_state_t *state, void *user_data) {
    layer_dance_reset(LNUM, &dance_state_lnum, state, user_data);
}


/* 
 * for the symbol layer
 *   single tap enters the layer as one shot, or exits if we are in the layer
 *   double tap enters the layer as TO(layer)
 *   hold enters the layer as MO(layer) until released
 */
void tapdance_lsym_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state_lsym.step = current_dance_step(state);
    switch (dance_state_lsym.step) {
        case SINGLE_TAP:
            // if we are in the layer, exit, otherwise toggle the one shot mod
            if (layer_state_is(LSYM)) {
                layer_off(LSYM);
            } else {
                set_oneshot_layer(LSYM, ONESHOT_START);
                clear_oneshot_layer_state(ONESHOT_PRESSED);
            }
            break;
        case DOUBLE_TAP:
        case HELD:
            layer_on(LSYM);
            break;
    }
}


void tapdance_lsym_reset(qk_tap_dance_state_t *state, void *user_data) {
    layer_dance_reset(LSYM, &dance_state_lsym, state, user_data);
}


qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_LNUM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tapdance_lnum_finished, tapdance_lnum_reset),
    [TD_LSYM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, tapdance_lsym_finished, tapdance_lsym_reset)
};

/*******************************************************************************
* Tap Dance end
*******************************************************************************/

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

const rgblight_segment_t PROGMEM layer_default_lights[] = THUMB_KEYS(OFF)
const rgblight_segment_t PROGMEM layer_numpad_lights[] = THUMB_KEYS(ORANGE)
const rgblight_segment_t PROGMEM layer_symbols_lights[] = THUMB_KEYS(GREEN)
const rgblight_segment_t PROGMEM layer_motion_lights[] = THUMB_KEYS(BLUE)
const rgblight_segment_t PROGMEM layer_functions_lights[] = THUMB_KEYS(PURPLE)
const rgblight_segment_t PROGMEM layer_mouse_lights[] = THUMB_KEYS(MAGENTA)

const rgblight_segment_t PROGMEM oneshot_ctrl_active[] = RGBLIGHT_LAYER_SEGMENTS({8, 1, HSV_BLUE});
const rgblight_segment_t PROGMEM oneshot_shift_active[] = RGBLIGHT_LAYER_SEGMENTS({9, 1, HSV_GREEN});
const rgblight_segment_t PROGMEM oneshot_gui_active[] = RGBLIGHT_LAYER_SEGMENTS({35, 1, HSV_ORANGE});
const rgblight_segment_t PROGMEM oneshot_alt_active[] = RGBLIGHT_LAYER_SEGMENTS({36, 1, HSV_PURPLE});

const rgblight_segment_t PROGMEM caps_word_lights[] = INNER_KEYS(GREEN)

const rgblight_segment_t PROGMEM compose_mode_lights[] = INNER_KEYS(ORANGE)
const rgblight_segment_t PROGMEM compose_fail_lights[] = INNER_KEYS(RED)
const rgblight_segment_t PROGMEM compose_cancel_lights[] = INNER_KEYS(PURPLE)
const rgblight_segment_t PROGMEM compose_success_lights[] = INNER_KEYS(BLUE)

const rgblight_segment_t PROGMEM layer_no_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 54, HSV_OFF}
);

// now we need the array of layers
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_no_lights,
    layer_default_lights,
    layer_symbols_lights,
    layer_numpad_lights,
    layer_functions_lights,
    layer_motion_lights,
    layer_mouse_lights,
    caps_word_lights,
    compose_mode_lights,
    compose_fail_lights,
    compose_cancel_lights,
    oneshot_ctrl_active,
    oneshot_shift_active,
    oneshot_gui_active,
    oneshot_alt_active,
    compose_success_lights
);

void keyboard_post_init_user(void) {
    //enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_set_layer_state(0, true);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // check for the tristate layer
    state = update_tri_layer_state(state, LNUM, LSYM, LMOV2);

    // set the led status to indicate layer
    rgblight_set_layer_state(1, layer_state_cmp(state, LCMK));
    rgblight_set_layer_state(2, layer_state_cmp(state, LSYM));
    rgblight_set_layer_state(3, layer_state_cmp(state, LNUM));
    rgblight_set_layer_state(4, layer_state_cmp(state, LFUN));
    rgblight_set_layer_state(5, layer_state_cmp(state, LMOV) || layer_state_cmp(state, LMOV2));
    rgblight_set_layer_state(6, layer_state_cmp(state, LMSE));
    return state;
}

void oneshot_mods_changed_user(uint8_t mods) {
    rgblight_set_layer_state(11, false);
    rgblight_set_layer_state(12, false);
    rgblight_set_layer_state(13, false);
    rgblight_set_layer_state(14, false);

    if (mods & MOD_MASK_SHIFT) {
        rgblight_set_layer_state(12, true);
    }
    if (mods & MOD_MASK_CTRL) {
        rgblight_set_layer_state(11, true);
    }
    if (mods & MOD_MASK_ALT) {
        rgblight_set_layer_state(14, true);
    }
    if (mods & MOD_MASK_GUI) {
        rgblight_set_layer_state(13, true);
    }
}
/*******************************************************************************
 * END RGB lighting on layer change
 ******************************************************************************/

