#include "pogues.h"


static bool vscode = true;
uint8_t vscode_compose_mapping(uint16_t* sequence, uint8_t sequence_len);
uint8_t qzdev_compose_mapping(uint16_t* sequence, uint8_t sequence_len);

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
        case OSL(LNUM):
        case OSL(LSYM):
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
        case MOV_SPC:
        case SFT_BSP:
            // Immediately select the hold action when another key is pressed.
            // for the shift mod and mov layer
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

// configure the caps_word settings
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
        case KC_MINS:
        case KC_DOT:
        case KC_SLSH:
        case KC_NUBS:   // UK |
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

void toggle_dev_env(void) {
    // TODO move out and look at lighting options?
    vscode = !vscode;
}

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
        { caps_word_toggle(); }
    )

    // quit window manager
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_Q),
        { SEND_STRING(SS_LGUI(SS_LSFT("q"))); }
    )

    // start window manager menu (launcher)
    COMPOSE_MAPPING(
        COMPOSE_INPUT(MOV_SPC),
        { SEND_STRING(SS_LGUI(SS_LSFT("l"))); }
    )
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_SPC),
        { SEND_STRING(SS_LGUI(SS_LSFT("l"))); }
    )

    // set the mode to qzdev or vscode
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_M),
        { toggle_dev_env(); }
    )

    if (vscode) {
        return vscode_compose_mapping(sequence, sequence_len);
    } else {
        return qzdev_compose_mapping(sequence, sequence_len);
    }
}

uint8_t vscode_compose_mapping(uint16_t* sequence, uint8_t sequence_len) {
    // open file (quick open/goto file)
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_O),
        // for some reason this does not wor{ SEND_STRING(SS_LCTL(SS_LALT("o"))); }
        { tap_code(KC_F13); }
    )
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_Y),
        { SEND_STRING(SS_LCTL("p")); }
    )
    // command pallet
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_P),
        { SEND_STRING(SS_LCTL(SS_LSFT("p"))); }
    )

    // run script
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_R, KC_S),
        { tap_code(KC_F9); }   // changed to match qzdev
    )
    // run selected text
    //COMPOSE_MAPPING(
        //COMPOSE_INPUT(KC_R, KC_T),
        //{ SEND_STRING(SS_LSFT(SS_TAP(X_ENT))); }
    //)
    COMPOSE_MAPPING_MEH(KC_R, KC_T, "r")    // run text

    // Guesses that we can add shortcuts to vscode for these...
    // diff current
    COMPOSE_MAPPING_MEH(KC_D, KC_C, "g")
    // diff approved
    COMPOSE_MAPPING_MEH(KC_D, KC_A, "v")
    // diff prod
    COMPOSE_MAPPING_MEH(KC_D, KC_P, "p")
    // diff head
    COMPOSE_MAPPING_MEH(KC_D, KC_H, "h")  // note "e" did not work as a mapping in vscode somehow
    // diff against version
    COMPOSE_MAPPING_MEH(KC_D, KC_V, "d")

    // vc blame
    COMPOSE_MAPPING_MEH(KC_V, KC_B, "b")
    // vc log
    COMPOSE_MAPPING_MEH(KC_V, KC_L, "l")    // not set up yet
    // vc commit
    COMPOSE_MAPPING_MEH(KC_V, KC_C, "c")    // not set up yet
    // vc request review
    COMPOSE_MAPPING_MEH(KC_V, KC_R, "w")    // not set up yet
    // push to
    COMPOSE_MAPPING_MEH(KC_V, KC_P, "s")    // not set up yet
    // vc update
    COMPOSE_MAPPING_MEH(KC_V, KC_U, "u")    // not set up yet

    // focus on the shell
    COMPOSE_MAPPING_CTL_SFT(KC_F, KC_S, "d")
    // focus on the editor
    COMPOSE_MAPPING_CTL(KC_F, KC_E, SS_TAP(X_1))
    // toggle between shell/editor
    COMPOSE_MAPPING_CTL(KC_F, KC_F, "`")
    // search the open buffers (ctrl-tab)
    COMPOSE_MAPPING_CTL(KC_F, KC_B, SS_TAP(X_TAB))
    // switch (focus) between code/test  (vim "alternate")
    COMPOSE_MAPPING_CTL(KC_F, KC_A, "t")
    // toggle zen mode
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_F, KC_Z),
        { SEND_STRING(SS_LCTL("k") "z"); }
    )
    // focus on the terminal
    COMPOSE_MAPPING_MEH(KC_F, KC_T, "t")


    // show/hide the left pane
    COMPOSE_MAPPING_MEH(KC_S, KC_L, "x")
    // show/hide the right pane
    COMPOSE_MAPPING_MEH(KC_S, KC_R, "z")
    // show/hide the bottom pane
    COMPOSE_MAPPING_MEH(KC_S, KC_R, "y")

    // assume we are called last
    return COMPOSE_ERROR;
}

uint8_t qzdev_compose_mapping(uint16_t* sequence, uint8_t sequence_len) {
    // hold the mappings that apply to qzdev, must be called last
    // open a file
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_O),
        { SEND_STRING(SS_LCTL(SS_LSFT("o"))); }
    )

    // diff current
    COMPOSE_MAPPING_CTL_SFT(KC_D, KC_C, "g")
    // diff approved
    COMPOSE_MAPPING_CTL_SFT(KC_D, KC_A, "v")
    // diff prod
    COMPOSE_MAPPING_CTL_SFT(KC_D, KC_P, "p")
    // diff head
    COMPOSE_MAPPING_CTL_SFT(KC_D, KC_H, "e")
    // diff against version
    COMPOSE_MAPPING_CTL_SFT(KC_D, KC_V, "d")

    // vc blame
    COMPOSE_MAPPING_CTL_SFT(KC_V, KC_B, "b")
    // vc log
    COMPOSE_MAPPING_CTL_SFT(KC_V, KC_L, "l")
    // vc commit
    //COMPOSE_MAPPING_CTL_SFT(KC_V, KC_C, "c")
    // vc request review
    //COMPOSE_MAPPING_CTL_SFT(KC_V, KC_R, "w")
    // push to
    //COMPOSE_MAPPING_CTL_SFT(KC_V, KC_P, "s")
    // vc update
    //COMPOSE_MAPPING_CTL_SFT(KC_V, KC_U, "u")

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
    // run selected text
    COMPOSE_MAPPING(
        COMPOSE_INPUT(KC_R, KC_T),
        { SEND_STRING(SS_LALT(SS_TAP(X_F9))); }
    )


    // focus commands
    // focus on the shell
    COMPOSE_MAPPING_ALT(KC_F, KC_S, "s")
    // focus on the editor
    COMPOSE_MAPPING_ALT(KC_F, KC_E, "t")
    // toggle between shell/editor
    COMPOSE_MAPPING_ALT(KC_F, KC_F, SS_TAP(X_GRV))
    // select an open buffer
    COMPOSE_MAPPING_CTL(KC_F, KC_B, "b")

    // assume we are called last
    return COMPOSE_ERROR;
}




/******************************************************************************
 * compose end
 ******************************************************************************/

