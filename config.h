/* See LICENSE file for copyright and license details. */

/* custom */
#include <X11/XF86keysym.h>
#include "layouts/bstack.c"

/* appearance */
static const char font[]            = "-*-terminus-*-*-*-*-*-*-*-*-*-*-*-*";
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 10;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */

static const char normbordercolor[] = "#1a1a1a";
static const char normfgcolor[]     = "#c0c0c0";
static const char selbordercolor[]  = "#5f7b8a";
static const char selbgcolor[]      = "#121212";
static const char normbgcolor[]     = "#121212";
static const char selfgcolor[]      = "#ff92bb";

/*
static const char normbordercolor[] = "#343434";
static const char normfgcolor[]     = "#424648";
static const char selbordercolor[]  = "#b698b8";
static const char selbgcolor[]      = "#050d12";
static const char normbgcolor[]     = "#050d12";
static const char selfgcolor[]      = "#b698b8";
*/

//static const char selbgcolor[]      = "#003333";
//static const char normbgcolor[]     = "#003333";

/* light 
static const char normbordercolor[] = "#7a6967";
static const char normbgcolor[]     = "#d7d4cb";
static const char normfgcolor[]     = "#7a6967";
static const char selbordercolor[]  = "#ea6868";
static const char selfgcolor[]      = "#7a6967";
static const char selbgcolor[]      = "#d7d4cb";
*/

/* blue
static const char selfgcolor[]      = "#1d626c";
static const char selbgcolor[]      = "#021011";
static const char selbordercolor[]  = "#1d626c";
static const char normfgcolor[]     = "#ff669d";
static const char normbordercolor[] = "#10353b";
static const char normbgcolor[]     = "#021011";
*/

/* tagging */
static const char *tags[] = { "1-term", "2-web", "3-chat", "4" ,"5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */	
	{ "Chromium", NULL,	  NULL,	      1 << 1,	    False,	 -1},
	{ "Zathura",  NULL,	  NULL,	      1 << 3,	    False,	 -1},
	{ "MPlayer",  NULL,	  NULL,	      1 << 4,	    False,	 -1},
	{ "Gimp",     NULL,       NULL,       1 << 5,       True,   	 -1},
	{ "Thunar",   NULL,	  NULL,	      1 << 6,	    True,	 -1},
	{ "Wicd-client.py",NULL,  NULL,       0,            True,	 -1},
};

/* layout(s) */
static const float mfact      = 0.55; /* factor of master area size [0.05..0.95] */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[_]",      bstack },
	{ "[M]",      monocle },
	{ "[~]",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvtc", NULL };
static const char *suspend[] = { "sudo", "pm-suspend", NULL };
static const char *slock[] = { "slock", NULL };
static const char *volmute[] = { "/home/edma2/bin/dvol2.sh", "-t", NULL };
static const char *volraise[] = { "/home/edma2/bin/dvol2.sh", "-i", "1", NULL };
static const char *vollower[] = { "/home/edma2/bin/dvol2.sh", "-d", "1", NULL };
static const char *mpdpause[] = { "mpc", "toggle", NULL };
static const char *mpdstop[] = { "mpc", "stop", NULL };
static const char *mpdnext[] = { "mpc", "next", NULL };
static const char *mpdprev[] = { "mpc", "prev", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ 0,				XF86XK_AudioMute, spawn,   	{.v = volmute } }, 			
	{ 0,				XF86XK_AudioLowerVolume, spawn, {.v = vollower } }, 			
	{ 0,				XF86XK_AudioRaiseVolume, spawn, {.v = volraise } }, 			
	{ 0,				XF86XK_AudioPlay, spawn,   	{.v = mpdpause } }, 			
	{ 0,				XF86XK_AudioPrev, spawn,   	{.v = mpdprev } }, 			
	{ 0,				XF86XK_AudioNext, spawn,   	{.v = mpdnext } }, 			
	{ 0,				XF86XK_AudioStop, spawn,   	{.v = mpdstop } }, 			
	{ 0,				XF86XK_ScreenSaver, spawn, 	{.v = slock } }, 			
	{ 0,				XF86XK_Sleep, spawn,       	{.v = suspend } }, 			
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,    		XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
