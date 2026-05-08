/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int topbar = 1;                      /* -b  option; if 0, dmenu appears at bottom     */
/* -fn option overrides fonts[0]; default X11 font or font set */
static const char *fonts[] = {
	"monospace:size=15"
};
static const char *prompt      = NULL;      /* -p  option; prompt to the left of input field */
static const char *colors[SchemeLast][2] = {
	/* fg         bg       */
	[SchemeNorm] = { "#f8f8f2", "#272822" }, /* Off-white text on dark charcoal */
	[SchemeSel]  = { "#272822", "#f92672" }, /* Dark charcoal text on Monokai Pink */
	[SchemeOut]  = { "#000000", "#a6e22e" }, /* Black text on Monokai Green */
};
/* -l option; if nonzero, dmenu uses vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
