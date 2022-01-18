/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 10;        /* gaps between windows */
static const unsigned int snap      = 0;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Iosevka:pixelsize=14:antialias=true:autohint=true", "-wuncon-siji-medium-r-normal--10-100-75-75-c-80-iso10646-1"};
static const char dmenufont[]       = "Iosevka:pixelsize=14:antialias=true:autohint=true";
static const char col_gray[]        = "#121317";
static const char col_fgwhite[]     = "#D6DEEB";
static const char col_main[]        = "#313439";
static const char *colors[][3]      = {
        /*               fg           bg         border   */
        [SchemeNorm] = { col_fgwhite, col_gray,  col_gray },
        [SchemeSel]  = { col_fgwhite, col_main,  col_main },
};
static const XPoint stickyicon[]    = { {0,0}, {4,0}, {4,8}, {2,6}, {0,8}, {0,0} }; /* represents the icon as an array of vertices */
static const XPoint stickyiconbb    = {4,8};  /* defines the bottom right corner of the polygon's bounding box (speeds up scaling) */

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
  /* xprop(1):
  ¦*  WM_CLASS(STRING) = instance, class
  ¦*  WM_NAME(STRING) = title
  ¦*/
  /* class      instance    title            tags mask     isfloating   monitor */
  { "St",       "st",       "pulsemixer",    0,            1,           -1 },
};


/* layout(s) */
static const float mfact        = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 0; /* 1 will force focus on the fullscreen window */

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
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* dwm commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-b", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray, "-nf", col_fgwhite, "-sb", col_main, "-sf", col_fgwhite, NULL };
static const char *termcmd[]  = { "st", NULL };

/* for volume keybinds */
#include <X11/XF86keysym.h>

/* move windows up and down the stack */
#include "movestack.c"

static Key keys[] = {
	/* modifier                     key                       function        argument */
	{ MODKEY,                       XK_z,                     spawn,          SHCMD("boomer") },
	{ MODKEY,                       XK_x,                     spawn,          SHCMD("xkill") },
	{ MODKEY|ShiftMask,             XK_l,                     spawn,          SHCMD("bosskey") },
  { MODKEY|ShiftMask,             XK_s,                     spawn,          SHCMD("flameshot gui") },
	{ MODKEY|Mod1Mask,              XK_c,                     spawn,          SHCMD("st cava") },
	{ MODKEY|Mod1Mask,              XK_h,                     spawn,          SHCMD("st htop") },
	{ MODKEY|Mod1Mask,              XK_g,                     spawn,          SHCMD("st gotop") },
	{ MODKEY|Mod1Mask,              XK_m,                     spawn,          SHCMD("st ncmpcpp") },
	{ MODKEY|Mod1Mask,              XK_w,                     spawn,          SHCMD("st -e sh -c 'weather; exec zsh'") },
	{ MODKEY|Mod1Mask,              XK_n,                     spawn,          SHCMD("st -e sh -c 'neofetch; exec zsh'") },
  { 0,                            XF86XK_AudioLowerVolume,  spawn,          SHCMD("pamixer --allow-boost -d 5; kill -39 $(pidof dwmblocks)") },
  { 0,                            XF86XK_AudioMute,         spawn,          SHCMD("pamixer -t; kill -39 $(pidof dwmblocks)")},
  { 0,                            XF86XK_AudioRaiseVolume,  spawn,          SHCMD("pamixer --allow-boost -i 5; kill -39 $(pidof dwmblocks)") },
  { 0,                            XF86XK_AudioPlay,         spawn,          SHCMD("playerctl play-pause") },
  { 0,                            XF86XK_AudioNext,         spawn,          SHCMD("playerctl next") },
  { 0,                            XF86XK_AudioPrev,         spawn,          SHCMD("playerctl previous") },
	{ 0,                            XK_F8,                    spawn,          SHCMD("st pulsemixer") },
  { MODKEY,                       XK_d,                     spawn,          {.v = dmenucmd} },
  { MODKEY,                       XK_Return,                spawn,          {.v = termcmd} },
	{ MODKEY|ShiftMask,             XK_Return,                zoom,           {0} },
	{ MODKEY,                       XK_b,                     togglebar,      {0} },
	{ MODKEY,                       XK_s,                     togglesticky,   {0} },
	{ MODKEY|ShiftMask,             XK_f,                     togglefloating, {0} },
	{ MODKEY,                       XK_j,                     focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                     focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,                     movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,                     movestack,      {.i = -1 } },
	{ MODKEY,                       XK_i,                     incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,                     incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                     setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                     setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,                   view,           {0} },
	{ MODKEY,                       XK_q,                     killclient,     {0} },
	{ MODKEY,                       XK_t,                     setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,                     setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,                     setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,                 setlayout,      {0} },
	{ MODKEY,                       XK_0,                     view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                     tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                 focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                 tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                                     0)
	TAGKEYS(                        XK_2,                                     1)
	TAGKEYS(                        XK_3,                                     2)
	TAGKEYS(                        XK_4,                                     3)
	TAGKEYS(                        XK_5,                                     4)
	TAGKEYS(                        XK_6,                                     5)
	TAGKEYS(                        XK_7,                                     6)
	TAGKEYS(                        XK_8,                                     7)
	TAGKEYS(                        XK_9,                                     8)
	{ MODKEY|ShiftMask,             XK_e,                     quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

