/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {"Ubuntu:weight=bold:size=14:antialias=true:hinting=true", "Hack:size=8:antialias=true:autohint=true", "JoyPixels:size=10:antialias=true:autohint=true" }; 
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
    /* fg          bg          */
    [SchemeNorm]          = { "#f8f8f2", "#272822" }, // Soft White on Dark Charcoal
    [SchemeSel]           = { "#f8f8f2", "#75715e" }, // White on Stone Grey
    [SchemeSelHighlight]  = { "#f92672", "#75715e" }, // Pink Highlight on Grey
    [SchemeNormHighlight] = { "#ae81ff", "#272822" }, // Purple Highlight on Dark
    [SchemeOut]           = { "#000000", "#a6e22e" }, // Black on Neon Green
    [SchemeOutHighlight]  = { "#f92672", "#a6e22e" }, // Pink on Neon Green
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
