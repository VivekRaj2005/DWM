/* See LICENSE file for copyright and license details. */
/* appearance */
static unsigned int compositor     = 1;   // 1 Means autostart compositor 
static const unsigned int borderpx = 2;   /* border pixel of windows */
static const unsigned int gappx    = 4;   /* Gaps */ 
static const unsigned int snap     = 32;  /* snap pixel */
static const int showbar           = 1;   /* 0 means no bar */
static const int topbar            = 1;   /* 0 means bottom bar */
static const int horizpadbar       = 6;   /* horizontal padding for statusbar */
static const int vertpadbar        = 7;   /* vertical padding for statusbar */
static const char *fonts[]     = {"UbuntuMono:size=9:antialias=true:autohint=true",
                                  "JoyPixels:size=7:antialias=true:autohint=true"};
static const char col_1[]  = "#000000"; /* background color of bar */
static const char col_2[]  = "#282c34"; /* border color unfocused windows */
static const char col_3[]  = "#d7d7d7";
static const char col_4[]  = "#282c34"; /* border color focused windows and tags */
static const char col_5[]  = "#5b005e"; /* Bar Select Color */
static const char *colors[][3]        = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_3, col_1, col_2 },
	[SchemeSel]  = { col_3, col_5, col_4 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                    instance    title       tags mask     isfloating   monitor */
	{ "Nm-connection-editor",       NULL,       NULL,       0,            1,           -1 },
	{ "Qalculate-gtk",              NULL,       NULL,       0,            1,           -1 },
	{ "confirmreset",               NULL,       NULL,       0,            1,           -1 },
	{ "makebranch",                 NULL,       NULL,       0,            1,           -1 },
	{ "maketag",                    NULL,       NULL,       0,            1,           -1 },
    { "Nwgbar",                     NULL,       NULL,       0,            1,           -1 },
    { "Rofi",                      NULL,       NULL,       0,            1,           -1 },
    { "ssh-askpass",                NULL,       NULL,       0,            1,           -1 },
	{ NULL,                         NULL,       "branchdialog",       0,            1,           -1 },
	{ NULL,                         NULL,       "pinentry",       0,            1,           -1 },
	{ "Tk",                         NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ " ",      tile },    /* first entry is default */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Commands */
static char dmenumon[2]          = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]    = { "rofi", "-show", "drun" ,"-theme", "~/.config/rofi/sidebar.rasi", NULL };
static const char *termcmd[]     = { "alacritty", "-e", "zsh", NULL };
static const char *webbrowser[]  = { "brave", NULL };
static const char *upvol[]       = { "/usr/bin/pactl", "set-sink-volume", "0", "+5%",     NULL };
static const char *downvol[]     = { "/usr/bin/pactl", "set-sink-volume", "0", "-5%",     NULL };
static const char *mutevol[]     = { "/usr/bin/pactl", "set-sink-mute",   "0", "toggle",  NULL };
static const char *lockscreen[]  = { "alacritty", "-e", "$HOME/.local/bin/lock", ">>", "log.txt", NULL };
static const char *termpowoff[]  = { "/home/vivek/.local/bin/powerrofi" };
static const char *screenshcmd[] = { "gnome-screenshot", "--interactive", NULL };
static const char *projectmanager[] = { "/home/vivek/.local/bin/projectrofi", NULL };

static Key keys[] = {
	/* modifier              key        function        argument */
    // Application Launches
	{ MODKEY,               XK_d,        spawn,             {.v = dmenucmd } },
	{ MODKEY,               XK_o,        spawn,             {.v = projectmanager} },
	{ MODKEY,               XK_w,        randomWallpaper,   {0} },
	{ MODKEY,               XK_Return,   spawn,             {.v = termcmd } },
    { MODKEY | ALTKEY,      XK_f,        spawn,             SHCMD("emacsclient -c -a 'emacs' --eval '(dired nil)'") },
    { MODKEY | ALTKEY,      XK_w,        spawn,             {.v = webbrowser } },
    { MODKEY | ALTKEY,      XK_q,        spawn,             {.v = lockscreen} },
    { MODKEY | ALTKEY,      XK_s,        spawn,             {.v = screenshcmd} },
    { MODKEY | ALTKEY,      XK_p,        togglecompositor,  {0}},

    // Stack Manupulation
	{ MODKEY|ShiftMask,     XK_k,        rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,     XK_j,        rotatestack,    {.i = -1 } },
	{ MODKEY,               XK_k,        focusstack,     {.i = +1 } },
	{ MODKEY,               XK_j,        focusstack,     {.i = -1 } },
	{ MODKEY,               XK_h,        setmfact,       {.f = -0.05} },
	{ MODKEY,               XK_l,        setmfact,       {.f = +0.05} },
	{ MODKEY,               XK_space,    zoom,           {0} },
	{ MODKEY|ShiftMask,     XK_q,        killclient,     {0} },

    // All Tags
	{ MODKEY,               XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,     XK_0,      tag,            {.ui = ~0 } },

    // Tag Keys
	TAGKEYS(                XK_1,                      0)
	TAGKEYS(                XK_2,                      1)
	TAGKEYS(                XK_3,                      2)
	TAGKEYS(                XK_4,                      3)
	TAGKEYS(                XK_5,                      4)
	TAGKEYS(                XK_6,                      5)
	TAGKEYS(                XK_7,                      6)
	TAGKEYS(                XK_8,                      7)
	TAGKEYS(                XK_9,                      8)
    
    // Media Keys
	{ 0,                    XF86XK_AudioLowerVolume, spawn, {.v = downvol } },
	{ 0,                    XF86XK_AudioMute,        spawn, {.v = mutevol } },
	{ 0,                    XF86XK_AudioRaiseVolume, spawn, {.v = upvol   } },

    // Quit or Restart
	{ MODKEY|ShiftMask,     XK_e,	        quit,		        {0} },
    { MODKEY,               XK_p,           spawn,              {.v = termpowoff}},
    { MODKEY,               XK_r,           quit,               {1} },
 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click           event mask   button          function        argument */
	{ ClkStatusText,   0,           Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,    MODKEY,      Button1,        movemouse,      {0} },
	{ ClkClientWin,    MODKEY,      Button2,        togglefloating, {0} },
	{ ClkClientWin,    MODKEY,      Button3,        resizemouse,    {0} },
	{ ClkTagBar,       0,           Button1,        view,           {0} },
	{ ClkTagBar,       0,           Button3,        toggleview,     {0} },
	{ ClkTagBar,       MODKEY,      Button1,        tag,            {0} },
	{ ClkTagBar,       MODKEY,      Button3,        toggletag,      {0} },
};


