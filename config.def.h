/* See LICENSE f/le for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 8;        /* gaps between windows */
static const unsigned int snap      = 8;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int showsystray        = 0;        /* 0 means no systray */
static const int focusonwheel       = 0;        /* 0 means focus on click */

/* systray settings */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/

/* fonts */
static const char *fonts[] = { "monospace:size=10",
                               "Siji" };

/* default colorscheme */
static char normbordercolor[] = "#444444";
static char normbgcolor[]     = "#222222";
static char normfgcolor[]     = "#bbbbbb";
static char selbordercolor[]  = "#005577";
static char selbgcolor[]      = "#005577";
static char selfgcolor[]      = "#eeeeee";
static char *colors[][3]      = {
	/*               fg           bg           border  */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
	[SchemeHid]  = { selbgcolor,  normbgcolor, selbgcolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

/* scratchpads */
typedef struct {
	const char *name;
	const void *cmd;
} Sp;

const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };

static Sp scratchpads[] = {
	/* name      cmd */
	{ "spterm",  spcmd1 },
};

static const unsigned int ulinepad	   = 0;	/* horizontal padding between the underline and tag */
static const unsigned int ulinestroke  = 1;	/* thickness / height of the underline */
static const unsigned int ulinevoffset = 0;	/* how far above the bottom of the bar the line should appear */
static const int ulineall 		       = 0;	/* 1 to show underline on all tags, 0 for just the active ones */

static const char ptagf[] = "[%s: %s]";	/* format of a tag label */
static const char etagf[] = "%s";	    /* format of an empty tag */
static const int lcaselbl = 1;		    /* 1 means make tag label lowercase */	

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class       instance    title       tags mask     isfloating   monitor */
    { "mpv",       NULL,       NULL,       0,            1,           -1 },
    { "LibreWolf", NULL,       NULL,       1 << 8,       0,           -1 },
    { "Chromium",  NULL,       NULL,       1 << 8,       0,           -1 },
    { NULL,		   "spterm",   NULL,	   SPTAG(0),	 1,		 	  -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int decorhints  = 1;    /* 1 means respect decoration hints */

static const Layout layouts[] = {
	/* symbol    arrange function */
	{ " \ue002",  tile },    /* slave clients arranged on the left */
	{ " \ue006",  NULL },    /* no layout function means floating behavior */
	{ " \ue000",  monocle }, /* one client per monitor */
	{ " \ue26b",  deck },    /* slave clients arranged in deck */
};

/* key definitions */
#define MODKEY Mod4Mask

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
	/* signum           function */
	{ "focusstack",     focusstack },
	{ "setmfact",       setmfact },
	{ "togglebar",      togglebar },
	{ "togglefloating", togglefloating },
	{ "focusmon",       focusmon },
	{ "tagmon",         tagmon },
	{ "zoom",           zoom },
	{ "view",           view },
	{ "viewall",        viewall },
	{ "viewex",         viewex },
	{ "toggleview",     view },
	{ "toggleviewex",   toggleviewex },
	{ "tag",            tag },
	{ "tagall",         tagall },
	{ "tagex",          tagex },
	{ "toggletag",      tag },
	{ "toggletagex",    toggletagex },
	{ "killclient",     killclient },
	{ "quit",           quit },
	{ "setlayout",      setlayout },
	{ "setlayoutex",    setlayoutex },
	{ "pushup",         pushup },
	{ "pushdown",       pushdown },
	{ "transfer",       transfer },
	{ "setgaps",        setgaps },
	{ "xrdb",           xrdb },
	{ "togglefullscr",  togglefullscr },
	{ "shiftview",      shiftview },
	{ "togglescratch",  togglescratch },
};
