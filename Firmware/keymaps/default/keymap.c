#include QMK_KEYBOARD_H

// ============================================================
//  SFX12 HACKPAD — KEYMAP (ROW-BASED ASSIGNMENT)
// ============================================================
//
//  PHYSICAL LAYOUT
//
//  [ ENC  ]              [ K01    ]  [ K02    ]     ← ROW 0: Apps
//           [ K03    ]  [ K04    ]  [ K05    ]  [ K06    ]  ← ROW 1: Apps
//           [ K07    ]  [ K08    ]  [ K09    ]  [ K10    ]  ← ROW 2: Shortcuts
//                       [ K11    ]  [ K12    ]              ← ROW 3: RGB
//
//  ROW 0 (ENC, K01, K02) → App launchers
//  ROW 1 (K03–K06)       → App launchers
//  ROW 2 (K07–K10)       → PC Shortcuts
//  ROW 3 (K11, K12)      → RGB Control
//
//  ENCODER: CCW = Vol Down | CW = Vol Up | Button = N/A
//
// ── APP ASSIGNMENTS (by priority rank) ──────────────────────
//
//  K01: Photoshop      / Premiere Pro    (1st, 3rd)
//  K02: Discord        / After Effects   (2nd, 5th)
//  K03: Fusion 360     / VS Code         (4th, 6th)
//  K04: KiCad          / Arduino IDE     (7th, 8th)
//  K05: YouTube Music  / WhatsApp        (9th, 10th)
//  K06: Illustrator    / Streamlabs      (11th, 12th)
//
// ── SHORTCUT ASSIGNMENTS ────────────────────────────────────
//
//  K07: Task Manager   / Settings (Win+I)
//  K08: GPU Refresh    / Audio Output Switch
//  K09: Mic Mute       / Screenshot (Win+Shift+S)
//  K10: Lock PC        / Show Desktop
//
// ── RGB ─────────────────────────────────────────────────────
//
//  K11: RGB Toggle
//  K12: RGB Mode cycle
//
// ============================================================

// ── Tap Dance IDs ───────────────────────────────────────────
enum tap_dance_keys {
    // Row 0 + Row 1 — Apps
    TD_PS_PR,      // K01: Photoshop / Premiere Pro
    TD_DC_AE,      // K02: Discord / After Effects
    TD_F360_VSC,   // K03: Fusion 360 / VS Code
    TD_KCD_ARD,    // K04: KiCad / Arduino IDE
    TD_YTM_WA,     // K05: YouTube Music / WhatsApp
    TD_AI_SL,      // K06: Illustrator / Streamlabs

    // Row 2 — Shortcuts
    TD_TSK_SET,    // K07: Task Manager / Settings
    TD_GPU_AU,     // K08: GPU Refresh / Audio Switch
    TD_MUTE_SS,    // K09: Mic Mute / Screenshot
    TD_LOCK_DSK,   // K10: Lock PC / Show Desktop
};

// ── App launch helpers ──────────────────────────────────────

// Win+R → run command (for apps registered in PATH)
static void launch_run(const char *cmd) {
    register_code(KC_LGUI);
    tap_code(KC_R);
    unregister_code(KC_LGUI);
    wait_ms(400);
    send_string(cmd);
    tap_code(KC_ENT);
}

// Win key → search (for apps without a run command)
static void launch_search(const char *name) {
    tap_code(KC_LGUI);
    wait_ms(500);
    send_string(name);
    wait_ms(600);
    tap_code(KC_ENT);
}

// Run a PowerShell script saved in the user profile folder
static void run_ps_script(const char *script) {
    register_code(KC_LGUI);
    tap_code(KC_R);
    unregister_code(KC_LGUI);
    wait_ms(400);
    send_string("powershell -ExecutionPolicy Bypass -File \"%USERPROFILE%\\");
    send_string(script);
    send_string("\"");
    tap_code(KC_ENT);
}

// ── Tap Dance callbacks ─────────────────────────────────────

// K01 — Photoshop (1tap) / Premiere Pro (2tap)
void td_ps_pr_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1)      launch_run("photoshop");
    else if (state->count == 2) launch_run("Adobe Premiere Pro");
}

// K02 — Discord (1tap) / After Effects (2tap)
void td_dc_ae_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1)      launch_run("discord");
    else if (state->count == 2) launch_run("afterfx");
}

// K03 — Fusion 360 (1tap) / VS Code (2tap)
void td_f360_vsc_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1)      launch_search("Fusion 360");
    else if (state->count == 2) launch_run("code");
}

// K04 — KiCad (1tap) / Arduino IDE (2tap)
void td_kcd_ard_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1)      launch_search("KiCad");
    else if (state->count == 2) launch_search("Arduino IDE");
}

// K05 — YouTube Music (1tap) / WhatsApp (2tap)
void td_ytm_wa_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1)      launch_run("https://music.youtube.com");
    else if (state->count == 2) launch_search("WhatsApp");
}

// K06 — Illustrator (1tap) / Streamlabs (2tap)
void td_ai_sl_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1)      launch_run("illustrator");
    else if (state->count == 2) launch_search("Streamlabs");
}

// K07 — Task Manager (1tap) / Settings (2tap)
void td_tsk_set_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        // Ctrl+Shift+Esc
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        tap_code(KC_ESC);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
    } else if (state->count == 2) {
        // Win+I
        register_code(KC_LGUI);
        tap_code(KC_I);
        unregister_code(KC_LGUI);
    }
}

// K08 — GPU Refresh (1tap) / Audio Output Switch (2tap)
void td_gpu_au_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        // Alt+Ctrl+Shift+B
        register_code(KC_LALT);
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        tap_code(KC_B);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
        unregister_code(KC_LALT);
    } else if (state->count == 2) {
        // Runs switch_audio.ps1 — see README for setup
        run_ps_script("switch_audio.ps1");
    }
}

// K09 — Mic Mute (1tap) / Screenshot Win+Shift+S (2tap)
void td_mute_ss_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        tap_code(KC_MUTE);
    } else if (state->count == 2) {
        // Win+Shift+S = Snipping Tool
        register_code(KC_LGUI);
        register_code(KC_LSFT);
        tap_code(KC_S);
        unregister_code(KC_LSFT);
        unregister_code(KC_LGUI);
    }
}

// K10 — Lock PC (1tap) / Show Desktop (2tap)
void td_lock_dsk_fn(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        // Win+L
        register_code(KC_LGUI);
        tap_code(KC_L);
        unregister_code(KC_LGUI);
    } else if (state->count == 2) {
        // Win+D
        register_code(KC_LGUI);
        tap_code(KC_D);
        unregister_code(KC_LGUI);
    }
}

// ── Tap Dance table ─────────────────────────────────────────
tap_dance_action_t tap_dance_actions[] = {
    [TD_PS_PR]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_ps_pr_fn,    NULL),
    [TD_DC_AE]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_dc_ae_fn,    NULL),
    [TD_F360_VSC]= ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_f360_vsc_fn, NULL),
    [TD_KCD_ARD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_kcd_ard_fn,  NULL),
    [TD_YTM_WA]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_ytm_wa_fn,   NULL),
    [TD_AI_SL]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_ai_sl_fn,    NULL),
    [TD_TSK_SET] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_tsk_set_fn,  NULL),
    [TD_GPU_AU]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_gpu_au_fn,   NULL),
    [TD_MUTE_SS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_mute_ss_fn,  NULL),
    [TD_LOCK_DSK]= ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lock_dsk_fn, NULL),
};

// ── Keymap ───────────────────────────────────────────────────
//
//  Matrix (4 rows × 4 cols), unused positions = KC_NO
//
//  [0][0]=ENC(N/A) [0][1]=K01      [0][2]=K02      [0][3]=KC_NO
//  [1][0]=K03      [1][1]=K04      [1][2]=K05      [1][3]=K06
//  [2][0]=K07      [2][1]=K08      [2][2]=K09      [2][3]=K10
//  [3][0]=KC_NO    [3][1]=K11      [3][2]=K12      [3][3]=KC_NO
//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
    //  ── ROW 0: Apps ──────────────────────────────────────────────────────
        KC_NO,           TD(TD_PS_PR),    TD(TD_DC_AE),    KC_NO,
    //  ── ROW 1: Apps ──────────────────────────────────────────────────────
        TD(TD_F360_VSC), TD(TD_KCD_ARD),  TD(TD_YTM_WA),   TD(TD_AI_SL),
    //  ── ROW 2: Shortcuts ─────────────────────────────────────────────────
        TD(TD_TSK_SET),  TD(TD_GPU_AU),   TD(TD_MUTE_SS),  TD(TD_LOCK_DSK),
    //  ── ROW 3: RGB ───────────────────────────────────────────────────────
        KC_NO,           RGB_TOG,         RGB_MOD,          KC_NO
    )
};

// ── Encoder ──────────────────────────────────────────────────
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif
