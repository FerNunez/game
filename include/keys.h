// KEYS
/*enum class KeyStatus
{
    NONE,
    PRESSED,
    RELEASED
};

enum class KeyModifier
{
    NONE,
    NUM,
    CAPS,
    MOD_LCTRL,
    MOD_RCTRL,
    MOD_RSHIFT,
    MOD_LSHIFT,
    MOD_RALT,
    MOD_LALT,
    MOD_CTRL,
    MOD_SHIFT,
    ALT
};

enum KeyName
{
    BACKSPACE = 0,
    TAB,
    CLEAR,
    RETURN,
    PAUSE,
    ESCAPE,
    SPACE,
    EXCLAIM,
    QUOTEDBL,
    HASH,
    DOLLAR,
    AMPERSAND,
    QUOTE,
    LEFTPAREN,
    RIGHTPAREN,
    ASTERISK,
    PLUS,
    COMMA,
    MINUS,
    PERIOD,
    SLASH,
    NUM_0,
    NUM_1,
    NUM_2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6,
    NUM_7,
    NUM_8,
    NUM_9,
    COLON,
    SEMICOLON,
    LESS,
    EQUALS,
    GREATER,
    QUESTION,
    AT,
    LEFTBRACKET,
    BACKSLASH,
    RIGHTBRACKET,
    CARET,
    UNDERSCORE,
    BACKQUOTE,
    a,
    b,
    c,
    d,
    e,
    f,
    g,
    h,
    i,
    j,
    k,
    l,
    m,
    n,
    o,
    p,
    q,
    r,
    s,
    t,
    u,
    v,
    w,
    x,
    y,
    z,
    DELETE,
    KP0,
    KP1,
    KP2,
    KP3,
    KP4,
    KP5,
    KP6,
    KP7,
    KP8,
    KP9,
    KP_PERIOD,
    KP_DIVIDE,
    KP_MULTIPLY,
    KP_MINUS,
    KP_PLUS,
    KP_ENTER,
    KP_EQUALS,
    UP,
    DOWN,
    RIGHT,
    LEFT,
    INSERT,
    HOME,
    END,
    PAGEUP,
    PAGEDOWN,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    NUMLOCK,
    CAPSLOCK,
    SCROLLOCK,
    RSHIFT,
    LSHIFT,
    RCTRL,
    LCTRL,
    RALT,
    LALT,
    RMETA,
    LMETA,
    LSUPER,
    RSUPER,
    MODE,
    HELP,
    PRINT,
    SYSREQ,
    BREAK,
    MENU,
    POWER,
    EURO,
    _NUMBER_OF_KEYS
};

struct Key
{
    KeyName key_name;
    KeyStatus key_status = KeyStatus::NONE;
    KeyModifier key_modifier = KeyModifier::NONE;
};*/


//SDLK_BACKSPACE
//  SDLK_TAB
//    SDLK_CLEAR
//      SDLK_RETURN
//        SDLK_PAUSE
//          SDLK_ESCAPE
//            SDLK_SPACE
//              SDLK_EXCLAIM
//                SDLK_QUOTEDBL
//                  SDLK_HASH
//                    SDLK_DOLLAR
//                      SDLK_AMPERSAND
//                        SDLK_QUOTE
//                          SDLK_LEFTPAREN
//                            SDLK_RIGHTPAREN
//                              SDLK_ASTERISK
//                                SDLK_PLUS
//                                  SDLK_COMMA
//                                    SDLK_MINUS
//                                      SDLK_PERIOD
//                                        SDLK_SLASH
//                                          SDLK_0
//                                            SDLK_1
//                                              SDLK_2
//                                                SDLK_3
//                                                  SDLK_4
//                                                    SDLK_5
//                                                      SDLK_6
//                                                        SDLK_7
//                                                          SDLK_8
//                                                            SDLK_9
//                                                              SDLK_COLON
//                                                                SDLK_SEMICOLON
//                                                                  SDLK_LESS
//                                                                    SDLK_EQUALS
//                                                                      SDLK_GREATER
//                                                                        SDLK_QUESTION
//                                                                          SDLK_AT
//                                                                            SDLK_LEFTBRACKET
//                                                                              SDLK_BACKSLASH
//                                                                                SDLK_RIGHTBRACKET
//                                                                                  SDLK_CARET
//                                                                                    SDLK_UNDERSCORE
//                                                                                      SDLK_BACKQUOTE
//                                                                                        SDLK_a
//                                                                                          SDLK_b
//                                                                                            SDLK_c
//                                                                                              SDLK_d
//                                                                                                SDLK_e
//                                                                                                  SDLK_f
//                                                                                                    SDLK_g
//                                                                                                      SDLK_h
//                                                                                                        SDLK_i
//                                                                                                          SDLK_j
//                                                                                                            SDLK_k
//                                                                                                              SDLK_l
//                                                                                                                SDLK_m
//                                                                                                                  SDLK_n
//                                                                                                                    SDLK_o
//                                                                                                                      SDLK_p
//                                                                                                                        SDLK_q
//                                                                                                                          SDLK_r
//                                                                                                                            SDLK_s
//                                                                                                                              SDLK_t
//                                                                                                                                SDLK_u
//                                                                                                                                  SDLK_v
//                                                                                                                                    SDLK_w
//                                                                                                                                      SDLK_x
//                                                                                                                                        SDLK_y
//                                                                                                                                          SDLK_z
//                                                                                                                                            SDLK_DELETE
//                                                                                                                                              SDLK_KP0
//                                                                                                                                                SDLK_KP1
//                                                                                                                                                  SDLK_KP2
//                                                                                                                                                    SDLK_KP3
//                                                                                                                                                      SDLK_KP4
//                                                                                                                                                        SDLK_KP5
//                                                                                                                                                          SDLK_KP6
//                                                                                                                                                            SDLK_KP7
//                                                                                                                                                              SDLK_KP8
//                                                                                                                                                                SDLK_KP9
//                                                                                                                                                                  SDLK_KP_PERIOD
//                                                                                                                                                                    SDLK_KP_DIVIDE
//                                                                                                                                                                      SDLK_KP_MULTIPLY
//                                                                                                                                                                        SDLK_KP_MINUS
//                                                                                                                                                                          SDLK_KP_PLUS
//                                                                                                                                                                            SDLK_KP_ENTER
//                                                                                                                                                                              SDLK_KP_EQUALS
//                                                                                                                                                                                SDLK_UP
//                                                                                                                                                                                  SDLK_DOWN
//                                                                                                                                                                                    SDLK_RIGHT
//                                                                                                                                                                                      SDLK_LEFT
//                                                                                                                                                                                        SDLK_INSERT
//                                                                                                                                                                                          SDLK_HOME
//                                                                                                                                                                                            SDLK_END
//                                                                                                                                                                                              SDLK_PAGEUP
//                                                                                                                                                                                                SDLK_PAGEDOWN
//                                                                                                                                                                                                  SDLK_F1
//                                                                                                                                                                                                    SDLK_F2
//                                                                                                                                                                                                      SDLK_F3
//                                                                                                                                                                                                        SDLK_F4
//                                                                                                                                                                                                          SDLK_F5
//                                                                                                                                                                                                            SDLK_F6
//                                                                                                                                                                                                              SDLK_F7
//                                                                                                                                                                                                                SDLK_F8
//                                                                                                                                                                                                                  SDLK_F9
//                                                                                                                                                                                                                    SDLK_F10
//                                                                                                                                                                                                                      SDLK_F11
//                                                                                                                                                                                                                        SDLK_F12
//                                                                                                                                                                                                                          SDLK_F13
//                                                                                                                                                                                                                            SDLK_F14
//                                                                                                                                                                                                                              SDLK_F15
//                                                                                                                                                                                                                                SDLK_NUMLOCK
//                                                                                                                                                                                                                                  SDLK_CAPSLOCK
//                                                                                                                                                                                                                                    SDLK_SCROLLOCK
//                                                                                                                                                                                                                                      SDLK_RSHIFT
//                                                                                                                                                                                                                                        SDLK_LSHIFT
//                                                                                                                                                                                                                                          SDLK_RCTRL
//                                                                                                                                                                                                                                            SDLK_LCTRL
//                                                                                                                                                                                                                                              SDLK_RALT
//                                                                                                                                                                                                                                                SDLK_LALT
//                                                                                                                                                                                                                                                  SDLK_RMETA
//                                                                                                                                                                                                                                                    SDLK_LMETA
//                                                                                                                                                                                                                                                      SDLK_LSUPER
//                                                                                                                                                                                                                                                        SDLK_RSUPER
//                                                                                                                                                                                                                                                          SDLK_MODE
//                                                                                                                                                                                                                                                            SDLK_HELP
//                                                                                                                                                                                                                                                              SDLK_PRINT
//                                                                                                                                                                                                                                                                SDLK_SYSREQ
//                                                                                                                                                                                                                                                                  SDLK_BREAK
//                                                                                                                                                                                                                                                                    SDLK_MENU
//                                                                                                                                                                                                                                                                      SDLK_POWER
//                                                                                                                                                                                                                                                                        SDLK_EURO
