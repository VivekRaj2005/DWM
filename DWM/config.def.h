/* See LICENSE file for copyright and license details. */

/* appearance */
#include <X11/X.h>
#include <X11/Xutil.h>
#include <X11/XF86keysym.h>

static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char dmenufont[]       = "monospace:size=10";
static const char col_cyan[]        = "#005577";
static const char *fonts[] = {"Ubuntu:weight=bold:size=14:antialias=true:hinting=true", "Hack:size=8:antialias=true:autohint=true", "JoyPixels:size=10:antialias=true:autohint=true" }; 
/* Monokai Color Palette */
static const char col_gray1[]       = "#272822"; // Dark Charcoal (Background)
static const char col_gray2[]       = "#3e3d32"; // Darker Olive/Gray (Inactive Border)
static const char col_gray3[]       = "#f8f8f2"; // Off-white (Text)
static const char col_gray4[]       = "#272822"; // Dark (Selected text for contrast)
static const char col_yellow[]      = "#e6db74"; // Classic Monokai Yellow (Accent)

static const char *colors[][3]      = {
    /* fg           bg           border   */
    [SchemeNorm] = { col_gray3,   col_gray1,   col_gray2 },
    [SchemeSel]  = { col_gray4,   col_yellow,  col_yellow },
};

/* tagging */
static const char *tags[] = { "", "󰾔", "", "", "", "", "", "", "󰋒" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    {"Gimp", NULL, NULL, 0, 1, -1},
    {"Firefox", NULL, NULL, 1 << 8, 0, -1},
    {"rofi", NULL, NULL, 0, 1, -1},
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/usr/bin/alacritty", "-c", cmd, NULL } }
/* Define individual commands */
static const char *nitrocmd[]  = { "nitrogen", "--restore", NULL };
static const char *picomcmd[] = {"picom", "-f", NULL};
static const char *dwmblocks[] = {"dwmblocks", NULL};

/* Group them into an array of pointers to those arrays */
/* Note the 'const char **' type - this is an array of string arrays */
static const char **autostartcmd[] = {
    nitrocmd, picomcmd,
    dwmblocks,
    NULL /* The terminator */
};
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m",      dmenumon, "-fn",    dmenufont, "-nb",     col_gray1,
    "-nf",       col_gray3, "-sb",    col_cyan, "-sf",     col_gray4, NULL};
static const char *roficmd[] = { "rofi", "-show", "drun", NULL }; 
static const char *termcmd[]  = { "alacritty", "-e", "zsh", NULL };
static const char *upvol[]   = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%+",      NULL };
static const char *downvol[] = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "5%-",      NULL };
static const char *mutevol[] = {"wpctl", "set-mute", "@DEFAULT_AUDIO_SINK@",
                                "toggle", NULL};
static const char *brupcmd[]   = { "/home/vivek/.local/bin/smooth_brightness", "+", NULL };
static const char *brdowncmd[] = { "/home/vivek/.local/bin/smooth_brightness", "-", NULL };

static const Key keys[] =
    {
        /* modifier                     key        function        argument */
        {MODKEY, XK_d, spawn, {.v = roficmd}},
        {MODKEY | ShiftMask, XK_d, spawn, {.v = dmenucmd}},
        {MODKEY, XK_Return, spawn, {.v = termcmd}},
        {MODKEY, XK_b, togglebar, {0}},
        {MODKEY | ShiftMask, XK_h, rotatestack, {.i = +1}},
        {MODKEY | ShiftMask, XK_l, rotatestack, {.i = -1}},
        {MODKEY, XK_h, focusstack, {.i = +1}},
        {MODKEY, XK_l, focusstack, {.i = -1}},
        {MODKEY, XK_j, setmfact, {.f = -0.05}},
        {MODKEY, XK_k, setmfact, {.f = +0.05}},
        {MODKEY, XK_Return, zoom, {0}},
        {MODKEY, XK_Tab, view, {0}},
        {MODKEY | ShiftMask, XK_q, killclient, {0}},
        {MODKEY, XK_t, setlayout, {.v = &layouts[0]}},
        {MODKEY, XK_f, setlayout, {.v = &layouts[1]}},
        {MODKEY, XK_m, setlayout, {.v = &layouts[2]}},
        {MODKEY, XK_space, setlayout, {0}},
        {MODKEY | ShiftMask, XK_space, togglefloating, {0}},
        {MODKEY, XK_0, view, {.ui = ~0}},
        {MODKEY | ShiftMask, XK_0, tag, {.ui = ~0}},
        {MODKEY, XK_comma, focusmon, {.i = -1}},
        {MODKEY, XK_period, focusmon, {.i = +1}},
        {MODKEY | ShiftMask, XK_comma, tagmon, {.i = -1}},
        {MODKEY | ShiftMask, XK_period, tagmon, {.i = +1}},
        TAGKEYS(XK_1, 0) TAGKEYS(XK_2, 1) TAGKEYS(XK_3, 2) TAGKEYS(XK_4, 3)
            TAGKEYS(XK_5, 4) TAGKEYS(XK_6, 5) TAGKEYS(XK_7, 6) TAGKEYS(XK_8, 7)
                TAGKEYS(XK_9, 8){MODKEY | ShiftMask, XK_e, quit, {0}},
        {MODKEY | ShiftMask, XK_r, quit, {1}},
        /* Key                Modifier      Key             Function Argument */
        {0, XF86XK_AudioLowerVolume, spawn, {.v = downvol}},
        {0, XF86XK_AudioMute, spawn, {.v = mutevol}},
        {0, XF86XK_AudioRaiseVolume, spawn, {.v = upvol}},
/* modifier             key                         function        argument */
{ 0,                    XF86XK_MonBrightnessUp,     spawn,          {.v = brupcmd } },
{ 0,                    XF86XK_MonBrightnessDown,   spawn,          {.v = brdowncmd } },
    };

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

