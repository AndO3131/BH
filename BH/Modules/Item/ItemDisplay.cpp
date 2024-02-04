#include "ItemDisplay.h"
#include "Item.h"
#include "../../Drawing/Stats/StatsDisplay.h"
#include <cctype>
#include <vector>
#include <string>

// All the types able to be combined with the + operator
#define COMBO_STATS					\
	{L"LIFE", STAT_MAXHP},			\
	{L"MANA", STAT_MAXMANA},			\
	{L"STR", STAT_STRENGTH},			\
	{L"DEX", STAT_DEXTERITY},		\
	{L"CRES", STAT_COLDRESIST},		\
	{L"FRES", STAT_FIRERESIST},		\
	{L"LRES", STAT_LIGHTNINGRESIST},	\
	{L"PRES", STAT_POISONRESIST},	\
	{L"MINDMG", STAT_MINIMUMDAMAGE},	\
	{L"MAXDMG", STAT_MAXIMUMDAMAGE}, \
	{L"EDEF", STAT_ENHANCEDDEFENSE},	\
	{L"EDAM", STAT_ENHANCEDMAXIMUMDAMAGE}, \
	{L"FCR", STAT_FASTERCAST},		\
	{L"AR", STAT_ATTACKRATING},		\
	{L"STAT3", STAT_VITALITY},		\
	{L"STAT60", STAT_LIFELEECH},		\
	{L"STAT62", STAT_MANALEECH},		\
	{L"REPLIFE", STAT_REPLENISHLIFE},

// For ignoring size
std::vector<std::string> colorreps =
{
	"\xc3\xbf\x63\x30",
	"\xc3\xbf\x63\x31",
	"\xc3\xbf\x63\x32",
	"\xc3\xbf\x63\x33",
	"\xc3\xbf\x63\x34",
	"\xc3\xbf\x63\x35",
	"\xc3\xbf\x63\x36",
	"\xc3\xbf\x63\x37",
	"\xc3\xbf\x63\x38",
	"\xc3\xbf\x63\x39",
	"\xc3\xbf\x63\x3b",
	"\xc3\xbf\x63\x3a",
	"\xc3\xbf\x63\x06",
	"\xc3\xbf\x63\x07",
	"\xc3\xbf\x63\x09",
	"\xc3\xbf\x63\x0C"
};

// All colors here must also be defined in MAP_COLOR_REPLACEMENTS
#define COLOR_REPLACEMENTS	\
	{L"WHITE", "\xc3\xbf\x63\x30"},		\
	{L"RED", "\xc3\xbf\x63\x31"},		\
	{L"GREEN", "\xc3\xbf\x63\x32"},		\
	{L"BLUE", "\xc3\xbf\x63\x33"},		\
	{L"GOLD", "\xc3\xbf\x63\x34"},		\
	{L"GRAY", "\xc3\xbf\x63\x35"},		\
	{L"BLACK", "\xc3\xbf\x63\x36"},		\
	{L"TAN", "\xc3\xbf\x63\x37"},			\
	{L"ORANGE", "\xc3\xbf\x63\x38"},		\
	{L"YELLOW", "\xc3\xbf\x63\x39"},		\
	{L"PURPLE", "\xc3\xbf\x63\x3b"},		\
	{L"DARK_GREEN", "\xc3\xbf\x63\x3a"},	\
	{L"CORAL", "\xc3\xbf\x63\x06"},		\
	{L"SAGE", "\xc3\xbf\x63\x07"},		\
	{L"TEAL", "\xc3\xbf\x63\x09"},		\
	{L"LIGHT_GRAY", "\xc3\xbf\x63\x0C"}

#define MAP_COLOR_WHITE     0x20

#define MAP_COLOR_REPLACEMENTS	\
	{L"WHITE", 0x20},		\
	{L"RED", 0x0A},			\
	{L"GREEN", 0x84},		\
	{L"BLUE", 0x97},			\
	{L"GOLD", 0x0D},			\
	{L"GRAY", 0xD0},			\
	{L"BLACK", 0x00},		\
	{L"TAN", 0x5A},			\
	{L"ORANGE", 0x60},		\
	{L"YELLOW", 0x0C},		\
	{L"PURPLE", 0x9B},		\
	{L"DARK_GREEN", 0x76}, \
	{L"CORAL", 0x66}, \
	{L"SAGE", 0x82}, \
	{L"TEAL", 0xCB}, \
	{L"LIGHT_GRAY", 0xD6}

std::map<std::wstring, int> code_to_dwtxtfileno = {
		{L"hax", 0},
		{L"axe", 1},
		{L"2ax", 2},
		{L"mpi", 3},
		{L"wax", 4},
		{L"lax", 5},
		{L"bax", 6},
		{L"btx", 7},
		{L"gax", 8},
		{L"gix", 9},
		{L"wnd", 10},
		{L"ywn", 11},
		{L"bwn", 12},
		{L"gwn", 13},
		{L"clb", 14},
		{L"scp", 15},
		{L"gsc", 16},
		{L"wsp", 17},
		{L"spc", 18},
		{L"mac", 19},
		{L"mst", 20},
		{L"fla", 21},
		{L"whm", 22},
		{L"mau", 23},
		{L"gma", 24},
		{L"ssd", 25},
		{L"scm", 26},
		{L"sbr", 27},
		{L"flc", 28},
		{L"crs", 29},
		{L"bsd", 30},
		{L"lsd", 31},
		{L"wsd", 32},
		{L"2hs", 33},
		{L"clm", 34},
		{L"gis", 35},
		{L"bsw", 36},
		{L"flb", 37},
		{L"gsd", 38},
		{L"dgr", 39},
		{L"dir", 40},
		{L"kri", 41},
		{L"bld", 42},
		{L"tkf", 43},
		{L"tax", 44},
		{L"bkf", 45},
		{L"bal", 46},
		{L"jav", 47},
		{L"pil", 48},
		{L"ssp", 49},
		{L"glv", 50},
		{L"tsp", 51},
		{L"spr", 52},
		{L"tri", 53},
		{L"brn", 54},
		{L"spt", 55},
		{L"pik", 56},
		{L"bar", 57},
		{L"vou", 58},
		{L"scy", 59},
		{L"pax", 60},
		{L"hal", 61},
		{L"wsc", 62},
		{L"sst", 63},
		{L"lst", 64},
		{L"cst", 65},
		{L"bst", 66},
		{L"wst", 67},
		{L"sbw", 68},
		{L"hbw", 69},
		{L"lbw", 70},
		{L"cbw", 71},
		{L"sbb", 72},
		{L"lbb", 73},
		{L"swb", 74},
		{L"lwb", 75},
		{L"lxb", 76},
		{L"mxb", 77},
		{L"hxb", 78},
		{L"rxb", 79},
		{L"gps", 80},
		{L"ops", 81},
		{L"gpm", 82},
		{L"opm", 83},
		{L"gpl", 84},
		{L"opl", 85},
		{L"d33", 86},
		{L"g33", 87},
		{L"leg", 88},
		{L"hdm", 89},
		{L"hfh", 90},
		{L"hst", 91},
		{L"msf", 92},
		{L"9ha", 93},
		{L"9ax", 94},
		{L"92a", 95},
		{L"9mp", 96},
		{L"9wa", 97},
		{L"9la", 98},
		{L"9ba", 99},
		{L"9bt", 100},
		{L"9ga", 101},
		{L"9gi", 102},
		{L"9wn", 103},
		{L"9yw", 104},
		{L"9bw", 105},
		{L"9gw", 106},
		{L"9cl", 107},
		{L"9sc", 108},
		{L"9qs", 109},
		{L"9ws", 110},
		{L"9sp", 111},
		{L"9ma", 112},
		{L"9mt", 113},
		{L"9fl", 114},
		{L"9wh", 115},
		{L"9m9", 116},
		{L"9gm", 117},
		{L"9ss", 118},
		{L"9sm", 119},
		{L"9sb", 120},
		{L"9fc", 121},
		{L"9cr", 122},
		{L"9bs", 123},
		{L"9ls", 124},
		{L"9wd", 125},
		{L"92h", 126},
		{L"9cm", 127},
		{L"9gs", 128},
		{L"9b9", 129},
		{L"9fb", 130},
		{L"9gd", 131},
		{L"9dg", 132},
		{L"9di", 133},
		{L"9kr", 134},
		{L"9bl", 135},
		{L"9tk", 136},
		{L"9ta", 137},
		{L"9bk", 138},
		{L"9b8", 139},
		{L"9ja", 140},
		{L"9pi", 141},
		{L"9s9", 142},
		{L"9gl", 143},
		{L"9ts", 144},
		{L"9sr", 145},
		{L"9tr", 146},
		{L"9br", 147},
		{L"9st", 148},
		{L"9p9", 149},
		{L"9b7", 150},
		{L"9vo", 151},
		{L"9s8", 152},
		{L"9pa", 153},
		{L"9h9", 154},
		{L"9wc", 155},
		{L"8ss", 156},
		{L"8ls", 157},
		{L"8cs", 158},
		{L"8bs", 159},
		{L"8ws", 160},
		{L"8sb", 161},
		{L"8hb", 162},
		{L"8lb", 163},
		{L"8cb", 164},
		{L"8s8", 165},
		{L"8l8", 166},
		{L"8sw", 167},
		{L"8lw", 168},
		{L"8lx", 169},
		{L"8mx", 170},
		{L"8hx", 171},
		{L"8rx", 172},
		{L"qf1", 173},
		{L"qf2", 174},
		{L"ktr", 175},
		{L"wrb", 176},
		{L"axf", 177},
		{L"ces", 178},
		{L"clw", 179},
		{L"btl", 180},
		{L"skr", 181},
		{L"9ar", 182},
		{L"9wb", 183},
		{L"9xf", 184},
		{L"9cs", 185},
		{L"9lw", 186},
		{L"9tw", 187},
		{L"9qr", 188},
		{L"7ar", 189},
		{L"7wb", 190},
		{L"7xf", 191},
		{L"7cs", 192},
		{L"7lw", 193},
		{L"7tw", 194},
		{L"7qr", 195},
		{L"7ha", 196},
		{L"7ax", 197},
		{L"72a", 198},
		{L"7mp", 199},
		{L"7wa", 200},
		{L"7la", 201},
		{L"7ba", 202},
		{L"7bt", 203},
		{L"7ga", 204},
		{L"7gi", 205},
		{L"7wn", 206},
		{L"7yw", 207},
		{L"7bw", 208},
		{L"7gw", 209},
		{L"7cl", 210},
		{L"7sc", 211},
		{L"7qs", 212},
		{L"7ws", 213},
		{L"7sp", 214},
		{L"7ma", 215},
		{L"7mt", 216},
		{L"7fl", 217},
		{L"7wh", 218},
		{L"7m7", 219},
		{L"7gm", 220},
		{L"7ss", 221},
		{L"7sm", 222},
		{L"7sb", 223},
		{L"7fc", 224},
		{L"7cr", 225},
		{L"7bs", 226},
		{L"7ls", 227},
		{L"7wd", 228},
		{L"72h", 229},
		{L"7cm", 230},
		{L"7gs", 231},
		{L"7b7", 232},
		{L"7fb", 233},
		{L"7gd", 234},
		{L"7dg", 235},
		{L"7di", 236},
		{L"7kr", 237},
		{L"7bl", 238},
		{L"7tk", 239},
		{L"7ta", 240},
		{L"7bk", 241},
		{L"7b8", 242},
		{L"7ja", 243},
		{L"7pi", 244},
		{L"7s7", 245},
		{L"7gl", 246},
		{L"7ts", 247},
		{L"7sr", 248},
		{L"7tr", 249},
		{L"7br", 250},
		{L"7st", 251},
		{L"7p7", 252},
		{L"7o7", 253},
		{L"7vo", 254},
		{L"7s8", 255},
		{L"7pa", 256},
		{L"7h7", 257},
		{L"7wc", 258},
		{L"6ss", 259},
		{L"6ls", 260},
		{L"6cs", 261},
		{L"6bs", 262},
		{L"6ws", 263},
		{L"6sb", 264},
		{L"6hb", 265},
		{L"6lb", 266},
		{L"6cb", 267},
		{L"6s7", 268},
		{L"6l7", 269},
		{L"6sw", 270},
		{L"6lw", 271},
		{L"6lx", 272},
		{L"6mx", 273},
		{L"6hx", 274},
		{L"6rx", 275},
		{L"ob1", 276},
		{L"ob2", 277},
		{L"ob3", 278},
		{L"ob4", 279},
		{L"ob5", 280},
		{L"am1", 281},
		{L"am2", 282},
		{L"am3", 283},
		{L"am4", 284},
		{L"am5", 285},
		{L"ob6", 286},
		{L"ob7", 287},
		{L"ob8", 288},
		{L"ob9", 289},
		{L"oba", 290},
		{L"am6", 291},
		{L"am7", 292},
		{L"am8", 293},
		{L"am9", 294},
		{L"ama", 295},
		{L"obb", 296},
		{L"obc", 297},
		{L"obd", 298},
		{L"obe", 299},
		{L"obf", 300},
		{L"amb", 301},
		{L"amc", 302},
		{L"amd", 303},
		{L"ame", 304},
		{L"amf", 305},
};

std::map<int, int> maptiers = {
	{ITEM_TYPE_PVP_MAP, 0},
	{ITEM_TYPE_T1_MAP, 1},
	{ITEM_TYPE_T2_MAP, 2},
	{ITEM_TYPE_T3_MAP, 3},
	{ITEM_TYPE_T4_MAP, 4},
	{ITEM_TYPE_T5_MAP, 5},
};

enum AttributeFlagTypes
{
	ITEMFLAG_BASE,
	ITEMFLAG_WEAPON,
	ITEMFLAG_ARMOR,
	ITEMFLAG_MISC
};

enum Operation
{
	EQUAL,
	GREATER_THAN,
	LESS_THAN,
	BETWEEN,
	NONE
};

enum FilterCondition
{
	COND_AND,
	COND_OR,
	COND_ETH,
	COND_SOCK,
	COND_SET,
	COND_MAG,
	COND_RARE,
	COND_UNI,
	COND_AMAZON,
	COND_SORCERESS,
	COND_NECROMANCER,
	COND_PALADIN,
	COND_BARBARIAN,
	COND_DRUID,
	COND_ASSASSIN,
	COND_CRAFTALVL,
	COND_PREFIX,
	COND_SUFFIX,
	COND_AUTOMOD,
	COND_MAPID,
	COND_MAPTIER,
	COND_CRAFT,
	COND_RW,
	COND_NMAG,
	COND_SUP,
	COND_INF,
	COND_NORM,
	COND_EXC,
	COND_ELT,
	COND_CLASS,
	COND_ID,
	COND_ILVL,
	COND_QLVL,
	COND_ALVL,
	COND_CLVL,
	COND_FILTLVL,
	COND_DIFF,
	COND_RUNE,
	COND_GOLD,
	COND_GEMMED,
	COND_GEMTYPE,
	COND_GEM,
	COND_ED,
	COND_EDEF,
	COND_EDAM,
	COND_DEF,
	COND_MAXDUR,
	COND_RES,
	COND_FRES,
	COND_CRES,
	COND_LRES,
	COND_PRES,
	COND_IAS,
	COND_FCR,
	COND_FHR,
	COND_FBR,
	COND_LIFE,
	COND_MANA,
	COND_QTY,
	COND_GOODSK,
	COND_GOODTBSK,
	COND_FOOLS,
	COND_LVLREQ,
	COND_ARPER,
	COND_MFIND,
	COND_GFIND,
	COND_STR,
	COND_DEX,
	COND_FRW,
	COND_MINDMG,
	COND_MAXDMG,
	COND_AR,
	COND_DTM,
	COND_MAEK,
	COND_REPLIFE,
	COND_REPQUANT,
	COND_REPAIR,
	COND_ARMOR,
	COND_BELT,
	COND_CHEST,
	COND_HELM,
	COND_SHIELD,
	COND_GLOVES,
	COND_BOOTS,
	COND_CIRC,
	COND_DRU,
	COND_BAR,
	COND_DIN,
	COND_NEC,
	COND_SIN,
	COND_SOR,
	COND_ZON,
	COND_SHOP,
	COND_EQUIPPED,
	COND_1H,
	COND_2H,
	COND_AXE,
	COND_MACE,
	COND_CLUB,
	COND_TMACE,
	COND_HAMMER,
	COND_SWORD,
	COND_DAGGER,
	COND_THROWING,
	COND_JAV,
	COND_SPEAR,
	COND_POLEARM,
	COND_BOW,
	COND_XBOW,
	COND_STAFF,
	COND_WAND,
	COND_SCEPTER,
	COND_WEAPON,
	COND_SK,
	COND_OS,
	COND_CHSK,
	COND_CLSK,
	COND_ALLSK,
	COND_TABSK,
	COND_STAT,
	COND_CHARSTAT,
	COND_MULTI,
	COND_PRICE,
	COND_ITEMCODE,
	COND_ADD,

	COND_NULL
};

std::map<std::wstring, FilterCondition> condition_map =
{
	{L"AND", COND_AND},
	{L"&&", COND_AND},
	{L"OR", COND_OR},
	{L"||", COND_OR},
	{L"ETH", COND_ETH},
	{L"SOCK", COND_SOCK},
	{L"SOCKETS", COND_SOCK},
	{L"SET", COND_SET},
	{L"MAG", COND_MAG},
	{L"RARE", COND_RARE},
	{L"UNI", COND_UNI},
	{L"AMAZON", COND_AMAZON},
	{L"SORCERESS", COND_SORCERESS},
	{L"NECROMANCER", COND_NECROMANCER},
	{L"PALADIN", COND_PALADIN},
	{L"BARBARIAN", COND_BARBARIAN},
	{L"DRUID", COND_DRUID},
	{L"ASSASSIN", COND_ASSASSIN},
	{L"CRAFTALVL", COND_CRAFTALVL},
	{L"PREFIX", COND_PREFIX},
	{L"SUFFIX", COND_SUFFIX},
	{L"AUTOMOD", COND_AUTOMOD},
	{L"MAPID", COND_MAPID},
	{L"MAPTIER", COND_MAPTIER},
	{L"CRAFT", COND_CRAFT},
	{L"RW", COND_RW},
	{L"NMAG", COND_NMAG},
	{L"SUP", COND_SUP},
	{L"INF", COND_INF},
	{L"NORM", COND_NORM},
	{L"EXC", COND_EXC},
	{L"ELT", COND_ELT},
	{L"CLASS", COND_CLASS},
	{L"ID", COND_ID},
	{L"ILVL", COND_ILVL},
	{L"QLVL", COND_QLVL},
	{L"ALVL", COND_ALVL},
	{L"CLVL", COND_CLVL},
	{L"FILTLVL", COND_FILTLVL},
	{L"DIFF", COND_DIFF},
	{L"RUNE", COND_RUNE},
	{L"GOLD", COND_GOLD},
	{L"GEMMED", COND_GEMMED},
	{L"GEMTYPE", COND_GEMTYPE},
	{L"GEM", COND_GEM},
	{L"GEMLEVEL", COND_GEM},
	{L"ED", COND_ED},
	{L"EDEF", COND_EDEF},
	{L"EDAM", COND_EDAM},
	{L"DEF", COND_DEF},
	{L"MAXDUR", COND_MAXDUR},
	{L"RES", COND_RES},
	{L"FRES", COND_FRES},
	{L"CRES", COND_CRES},
	{L"LRES", COND_LRES},
	{L"PRES", COND_PRES},
	{L"IAS", COND_IAS},
	{L"FCR", COND_FCR},
	{L"FHR", COND_FHR},
	{L"FBR", COND_FBR},
	{L"LIFE", COND_LIFE},
	{L"MANA", COND_MANA},
	{L"QTY", COND_QTY},
	{L"GOODSK", COND_GOODSK},
	{L"GOODTBSK", COND_GOODTBSK},
	{L"FOOLS", COND_FOOLS},
	{L"LVLREQ", COND_LVLREQ},
	{L"ARPER", COND_ARPER},
	{L"MFIND", COND_MFIND},
	{L"GFIND", COND_GFIND},
	{L"STR", COND_STR},
	{L"DEX", COND_DEX},
	{L"FRW", COND_FRW},
	{L"MINDMG", COND_MINDMG},
	{L"MAXDMG", COND_MAXDMG},
	{L"AR", COND_AR},
	{L"DTM", COND_DTM},
	{L"MAEK", COND_MAEK},
	{L"REPLIFE", COND_REPLIFE},
	{L"REPQUANT", COND_REPQUANT},
	{L"REPAIR", COND_REPAIR},
	{L"ARMOR", COND_ARMOR},
	{L"BELT", COND_BELT},
	{L"CHEST", COND_CHEST},
	{L"HELM", COND_HELM},
	{L"SHIELD", COND_SHIELD},
	{L"GLOVES", COND_GLOVES},
	{L"BOOTS", COND_BOOTS},
	{L"CIRC", COND_CIRC},
	{L"DRU", COND_DRU},
	{L"BAR", COND_BAR},
	{L"DIN", COND_DIN},
	{L"NEC", COND_NEC},
	{L"SIN", COND_SIN},
	{L"SOR", COND_SOR},
	{L"ZON", COND_ZON},
	{L"SHOP", COND_SHOP},
	{L"EQUIPPED", COND_EQUIPPED},
	{L"1H", COND_1H},
	{L"2H", COND_2H},
	{L"AXE", COND_AXE},
	{L"MACE", COND_MACE},
	{L"CLUB", COND_CLUB},
	{L"TMACE", COND_TMACE},
	{L"HAMMER", COND_HAMMER},
	{L"SWORD", COND_SWORD},
	{L"DAGGER", COND_DAGGER},
	{L"THROWING", COND_THROWING},
	{L"JAV", COND_JAV},
	{L"SPEAR", COND_SPEAR},
	{L"POLEARM", COND_POLEARM},
	{L"BOW", COND_BOW},
	{L"XBOW", COND_XBOW},
	{L"STAFF", COND_STAFF},
	{L"WAND", COND_WAND},
	{L"SCEPTER", COND_SCEPTER},
	{L"EQ1", COND_HELM},
	{L"EQ2", COND_CHEST},
	{L"EQ3", COND_SHIELD},
	{L"EQ4", COND_GLOVES},
	{L"EQ5", COND_BOOTS},
	{L"EQ6", COND_BELT},
	{L"EQ7", COND_CIRC},
	{L"CL1", COND_DRU},
	{L"CL2", COND_BAR},
	{L"CL3", COND_DIN},
	{L"CL4", COND_NEC},
	{L"CL5", COND_SIN},
	{L"CL6", COND_SOR},
	{L"CL7", COND_ZON},
	{L"WEAPON", COND_WEAPON},
	{L"WP1", COND_AXE},
	{L"WP2", COND_MACE},
	{L"WP3", COND_SWORD},
	{L"WP4", COND_DAGGER},
	{L"WP5", COND_THROWING},
	{L"WP6", COND_JAV},
	{L"WP7", COND_SPEAR},
	{L"WP8", COND_POLEARM},
	{L"WP9", COND_BOW},
	{L"WP10", COND_XBOW},
	{L"WP11", COND_STAFF},
	{L"WP12", COND_WAND},
	{L"WP13", COND_SCEPTER},
	{L"ALLSK", COND_ALLSK},
	{L"PRICE", COND_PRICE},
	// These have a number as part of the key, handled separately
	//{"SK", COND_SK},
	//{"OS", COND_OS},
	//{"CHSK", COND_CHSK},
	//{"CLSK", COND_CLSK},
	//{"TABSK", COND_TABSK},
	//{"STAT", COND_STAT},
	//{"CHARSTAT", COND_CHARSTAT},
	//{"MULTI", COND_MULTI},

};

std::map<std::string, int> stat_id_map =
{
	{"EDEF", STAT_ENHANCEDDEFENSE},
	{"EDAM", STAT_ENHANCEDMAXIMUMDAMAGE},
	{"DEF", STAT_DEFENSE},
	{"FRES", STAT_FIRERESIST},
	{"CRES", STAT_COLDRESIST},
	{"LRES", STAT_LIGHTNINGRESIST},
	{"PRES", STAT_POISONRESIST},
	{"IAS", STAT_IAS},
	{"FCR", STAT_FASTERCAST},
	{"FHR", STAT_FASTERHITRECOVERY},
	{"FBR", STAT_FASTERBLOCK},
	{"LIFE", STAT_MAXHP},
	{"MANA", STAT_MAXMANA},
	{"ARPER", STAT_TOHITPERCENT},
	{"MFIND", STAT_MAGICFIND},
	{"GFIND", STAT_GOLDFIND},
	{"STR", STAT_STRENGTH},
	{"DEX", STAT_DEXTERITY},
	{"FRW", STAT_FASTERRUNWALK},
	{"MINDMG", STAT_MINIMUMDAMAGE},
	{"MAXDMG", STAT_MAXIMUMDAMAGE},
	{"AR", STAT_ATTACKRATING},
	{"DTM", STAT_DAMAGETOMANA},
	{"MAEK", STAT_MANAAFTEREACHKILL},
	{"REPLIFE", STAT_REPLENISHLIFE},
	{"REPQUANT", STAT_REPLENISHESQUANTITY},
	{"REPAIR", STAT_REPAIRSDURABILITY},
};

SkillReplace skills[] = {
	COMBO_STATS
};

std::map<std::wstring, int>   UnknownItemCodes;
vector<pair<wstring, wstring>> rules;
vector<Rule*>                RuleList;
vector<Rule*>                MapRuleList;
vector<Rule*>                IgnoreRuleList;
BYTE                         LastConditionType;

TrueCondition* trueCondition = new TrueCondition();
FalseCondition* falseCondition = new FalseCondition();

// Helper function to get a list of strings
vector<wstring> split(const wstring& s,
	wchar_t          delim)
{
	vector<wstring> result;
	wstringstream   ss(s);
	wstring         item;
	while (getline(ss, item, delim)) { result.push_back(item); }
	return result;
}

// Helper function to join a list of string
template <typename C>
std::string join(C const& strings,
	std::string const& delim)
{
	std::ostringstream ostr;
	auto               last = std::prev(std::end(strings));
	std::copy(
		std::begin(strings),
		last,
		std::ostream_iterator<std::string>(ostr, delim.c_str())
	);
	ostr << *last;
	return ostr.str();
}

int ShopNPCs[] = {
	NPCID_Akara,	// Act 1
	NPCID_Gheed,	// Act 1
	NPCID_Charsi,	// Act 1
	NPCID_Elzix,	// Act 2
	NPCID_Drognan,	// Act 2
	NPCID_Fara,		// Act 2
	NPCID_Lysander,	// Act 2
	NPCID_Hratli,	// Act 3
	NPCID_Alkor,	// Act 3
	NPCID_Ormus,	// Act 3
	NPCID_Asheara,	// Act 3
	NPCID_Jamella,	// Act 4
	NPCID_Halbu,	// Act 4
	NPCID_Larzuk,	// Act 5
	NPCID_Malah,	// Act 5
	NPCID_Anya		// Act 5
};

char* GemLevels[] = {
	"NONE",
	"Chipped",
	"Flawed",
	"Normal",
	"Flawless",
	"Perfect"
};

char* GemTypes[] = {
	"NONE",
	"Amethyst",
	"Diamond",
	"Emerald",
	"Ruby",
	"Sapphire",
	"Topaz",
	"Skull"
};

bool IsGem(ItemAttributes* attrs) { return (attrs->miscFlags & ITEM_GROUP_GEM) > 0; }

BYTE GetGemLevel(ItemAttributes* attrs)
{
	if (attrs->miscFlags & ITEM_GROUP_CHIPPED) { return 1; }
	else if (attrs->miscFlags & ITEM_GROUP_FLAWED) { return 2; }
	else if (attrs->miscFlags & ITEM_GROUP_REGULAR) { return 3; }
	else if (attrs->miscFlags & ITEM_GROUP_FLAWLESS) { return 4; }
	else if (attrs->miscFlags & ITEM_GROUP_PERFECT) { return 5; }
	return 0;
}

char* GetGemLevelString(BYTE level) { return GemLevels[level]; }

BYTE GetGemType(ItemAttributes* attrs)
{
	if (attrs->miscFlags & ITEM_GROUP_AMETHYST) { return 1; }
	else if (attrs->miscFlags & ITEM_GROUP_DIAMOND) { return 2; }
	else if (attrs->miscFlags & ITEM_GROUP_EMERALD) { return 3; }
	else if (attrs->miscFlags & ITEM_GROUP_RUBY) { return 4; }
	else if (attrs->miscFlags & ITEM_GROUP_SAPPHIRE) { return 5; }
	else if (attrs->miscFlags & ITEM_GROUP_TOPAZ) { return 6; }
	else if (attrs->miscFlags & ITEM_GROUP_SKULL) { return 7; }
	return 0;
}

char* GetGemTypeString(BYTE type) { return GemTypes[type]; }

bool IsRune(ItemAttributes* attrs)
{
	return (attrs->miscFlags & ITEM_GROUP_RUNE) > 0;
	//char* code = attrs->code;
	//return (code[0] == 'r' && std::isdigit(code[1]) && std::isdigit(code[2]));
}

BYTE RuneNumberFromItemCode(char* code) { return (BYTE)(((code[1] - '0') * 10) + code[2] - '0'); }

BYTE RuneNumberFromItemCode(wchar_t* code) { return (BYTE)(((code[1] - L'0') * 10) + code[2] - L'0'); }

// Find the item description. This code is called only when there's a cache miss
string ItemDescLookupCache::make_cached_T(UnitItemInfo* uInfo)
{
	string new_name;
	for (vector<Rule*>::const_iterator it = RuleList.begin(); it != RuleList.end(); it++)
	{
		if ((*it)->Evaluate(uInfo))
		{
			SubstituteNameVariables(uInfo, new_name, (*it)->action.description, FALSE);
			if ((*it)->action.stopProcessing) { break; }
		}
	}
	return new_name;
}

string ItemDescLookupCache::to_str(const string& name)
{
	size_t      start_pos = 0;
	std::string itemName(name);
	while ((start_pos = itemName.find('\n', start_pos)) != std::string::npos)
	{
		itemName.replace(start_pos, 1, " - ");
		start_pos += 3;
	}
	return itemName;
}

// Find the item name. This code is called only when there's a cache miss
string ItemNameLookupCache::make_cached_T(UnitItemInfo* uInfo,
	const string& name)
{
	string new_name(name);
	for (vector<Rule*>::const_iterator it = RuleList.begin(); it != RuleList.end(); it++)
	{
		if ((*it)->Evaluate(uInfo))
		{
			SubstituteNameVariables(uInfo, new_name, (*it)->action.name, TRUE);
			if ((*it)->action.stopProcessing) { break; }
		}
	}
	return new_name;
}

string ItemNameLookupCache::to_str(const string& name)
{
	size_t      start_pos = 0;
	std::string itemName(name);
	while ((start_pos = itemName.find('\n', start_pos)) != std::string::npos)
	{
		itemName.replace(start_pos, 1, " - ");
		start_pos += 3;
	}
	return itemName;
}

vector<Action> MapActionLookupCache::make_cached_T(UnitItemInfo* uInfo)
{
	vector<Action> actions;
	for (vector<Rule*>::const_iterator it = RuleList.begin(); it != RuleList.end(); it++) { if ((*it)->Evaluate(uInfo)) { actions.push_back((*it)->action); } }
	return actions;
}

string MapActionLookupCache::to_str(const vector<Action>& actions)
{
	string name;
	for (auto& action : actions) { name += (string)UnicodeToAnsi(action.name.c_str()) + " "; }
	return name;
}

// least recently used cache for storing a limited number of item names
ItemDescLookupCache  item_desc_cache(RuleList);
ItemNameLookupCache  item_name_cache(RuleList);
MapActionLookupCache map_action_cache(MapRuleList);

void GetItemName(UnitItemInfo* uInfo,
	string& name)
{
	string new_name = item_name_cache.Get(uInfo, name);
	if (new_name == "" && Item::GetFilterLevel() == 0) {
		return;
	}
	name.assign(new_name);
}

void SubstituteNameVariables(UnitItemInfo* uInfo,
	string& name,
	const wstring& action_name,
	BOOL          bLimit)
{
	char origName[MAX_ITEM_TEXT_SIZE], sockets[4], code[5], ilvl[4], alvl[4], craftalvl[4], runename[16] = "", runenum[4] = "0";
	char gemtype[16] = "", gemlevel[16] = "", sellValue[16] = "", statVal[16] = "", qty[4] = "";
	char lvlreq[4], wpnspd[4], rangeadder[4], allres[4], ed[4];

	UnitAny* item = uInfo->item;
	ItemsTxt* txt = D2COMMON_GetItemText(item->dwTxtFileNo);
	char* szCode = txt->szCode;  // TODO: uInfo already has this, can we remove?
	code[0] = szCode[0];
	code[1] = szCode[1] != ' ' ? szCode[1] : 0;
	code[2] = szCode[2] != ' ' ? szCode[2] : 0;
	code[3] = szCode[3] != ' ' ? szCode[3] : 0;
	code[4] = '\0';

	int fRes = D2COMMON_GetUnitStat(item, STAT_FIRERESIST, 0);
	int lRes = D2COMMON_GetUnitStat(item, STAT_LIGHTNINGRESIST, 0);
	int cRes = D2COMMON_GetUnitStat(item, STAT_COLDRESIST, 0);
	int pRes = D2COMMON_GetUnitStat(item, STAT_POISONRESIST, 0);
	int minres = 0;
	if (fRes && lRes && cRes && pRes)
	{
		minres = min(min(fRes, lRes), min(cRes, pRes));
	}
	sprintf_s(allres, "%d", minres);

	// Either enhanced defense or enhanced damage depending on item type
	WORD stat;
	if (uInfo->attrs->armorFlags & ITEM_GROUP_ALLARMOR) { stat = STAT_ENHANCEDDEFENSE; }
	else
	{
		// Normal %ED will have the same value for STAT_ENHANCEDMAXIMUMDAMAGE and STAT_ENHANCEDMINIMUMDAMAGE
		stat = STAT_ENHANCEDMAXIMUMDAMAGE;
	}
	DWORD     value = 0;
	StatList* pStatList = D2COMMON_GetStatList(uInfo->item, NULL, 0x40);
	if (pStatList)
	{
		value += D2COMMON_GetStatValueFromStatList(pStatList, stat, 0);
	}
	sprintf_s(ed, "%d", value);

	auto qlvl_int = uInfo->attrs->qualityLevel;
	auto ilvl_int = item->pItemData->dwItemLevel;
	auto mlvl_int = uInfo->attrs->magicLevel;
	auto alvl_int = GetAffixLevel(
		ilvl_int,
		qlvl_int,
		mlvl_int
	);
	auto clvl_int = D2COMMON_GetUnitStat(D2CLIENT_GetPlayerUnit(), STAT_LEVEL, 0);

	sprintf_s(sockets, "%d", D2COMMON_GetUnitStat(item, STAT_SOCKETS, 0));
	sprintf_s(ilvl, "%d", ilvl_int);
	sprintf_s(alvl, "%d", alvl_int);
	sprintf_s(origName, "%s", name.c_str());

	auto craft_alvl = GetAffixLevel(
		(int)(0.5 * clvl_int) + (int)(0.5 * ilvl_int),
		qlvl_int,
		mlvl_int
	);
	sprintf_s(craftalvl, "%d", craft_alvl);

	sprintf_s(lvlreq, "%d", GetRequiredLevel(uInfo->item));
	sprintf_s(wpnspd, "%d", txt->dwspeed); //Add these as matchable stats too, maybe?
	sprintf_s(rangeadder, "%d", txt->brangeadder);
	sprintf_s(qty, "%d", D2COMMON_GetUnitStat(item, STAT_AMMOQUANTITY, 0));

	bool inShop = false;
	if (item->pItemData->pOwnerInventory != 0 && // Skip on ground items
		find(begin(ShopNPCs), end(ShopNPCs), item->pItemData->pOwnerInventory->pOwner->dwTxtFileNo) != end(ShopNPCs))
		inShop = true;

	UnitAny* pUnit = D2CLIENT_GetPlayerUnit();
	if (pUnit && txt->bquest == 0) { sprintf_s(sellValue, "%d", D2COMMON_GetItemPrice(pUnit, item, D2CLIENT_GetDifficulty(), (DWORD)D2CLIENT_GetQuestInfo(), 0x201, 1)); }

	ItemAttributes* attrs = ItemAttributeMap[code];  // TODO: uInfo already has this, can we replace?
	if (IsRune(attrs))
	{
		sprintf_s(runenum, "%d", RuneNumberFromItemCode(code));
		// TODO: removes " Rune" from the rune name. Pretty likely to break on non-english strings
		sprintf_s(runename, attrs->name.substr(0, attrs->name.find(' ')).c_str());
	}
	else if (IsGem(attrs))
	{
		sprintf_s(gemlevel, "%s", GetGemLevelString(GetGemLevel(uInfo->attrs)));
		sprintf_s(gemtype, "%s", GetGemTypeString(GetGemType(uInfo->attrs)));
	}
	ActionReplace replacements[] = {
		{ L"NAME", origName },
		{ L"SOCKETS", sockets },
		{ L"RUNENUM", runenum },
		{ L"RUNENAME", runename },
		{ L"GEMLEVEL", gemlevel },
		{ L"GEMTYPE", gemtype },
		{ L"ILVL", ilvl },
		{ L"ALVL", alvl },
		{ L"CRAFTALVL", craftalvl },
		{ L"LVLREQ", lvlreq },
		{ L"WPNSPD", wpnspd },
		{ L"RANGE", rangeadder },
		{ L"CODE", code },
		{ L"NL", "\n" },
		{ L"PRICE", sellValue },
		{ L"QTY", qty },
		{ L"RES", allres},
		{ L"ED", ed},
		COLOR_REPLACEMENTS
	};
	int nColorCodesSize = 0;
	name.assign(UnicodeToAnsi(action_name.c_str()));
	for (int n = 0; n < sizeof(replacements) / sizeof(replacements[0]); n++)
	{
		while (name.find("%" + (string)UnicodeToAnsi(replacements[n].key.c_str()) + "%") != string::npos)
		{
			if (bLimit && replacements[n].key == L"NL")
			{
				// Allow %NL% on identified, magic+ item names, and items within shops
				if ((uInfo->item->pItemData->dwFlags & ITEM_IDENTIFIED) > 0 &&
					(uInfo->item->pItemData->dwQuality >= ITEM_QUALITY_MAGIC || (uInfo->item->pItemData->dwFlags & ITEM_RUNEWORD) > 0) ||
					inShop)
				{
					name.replace(name.find("%" + (string)UnicodeToAnsi(replacements[n].key.c_str()) + "%"), replacements[n].key.length() + 2, replacements[n].value);
				}
				// Remove it on everything else
				else
				{
					name.replace(name.find("%" + (string)UnicodeToAnsi(replacements[n].key.c_str()) + "%"), replacements[n].key.length() + 2, "");
				}
			}
			else
			{
				name.replace(name.find("%" + (string)UnicodeToAnsi(replacements[n].key.c_str()) + "%"), replacements[n].key.length() + 2, replacements[n].value);
			}
		}
	}
	// Replace named stat output strings with their STAT# counterpart
	map<string, int>::iterator it;
	for (it = stat_id_map.begin(); it != stat_id_map.end(); it++)
	{
		while (name.find("%" + it->first + "%") != string::npos)
		{
			name.replace(name.find("%" + it->first + "%"), it->first.length() + 2, "%STAT" + std::to_string(it->second) + "%");
		}
	}

	// stat & skill replacements
	if (name.find("%STAT") != string::npos)
	{
		std::regex  stat_reg("%STAT([0-9]{1,4})%", std::regex_constants::ECMAScript);
		std::smatch stat_match;

		while (std::regex_search(name, stat_match, stat_reg))
		{
			int stat = stoi(stat_match[1].str(), nullptr, 10);
			statVal[0] = '\0';
			if (stat <= (int)STAT_MAX)
			{
				auto value = D2COMMON_GetUnitStat(item, stat, 0);
				// Hp and mana need adjusting
				if (stat == STAT_MAXHP || stat == STAT_MAXMANA)
				{
					value /= 256;
				}
				// These stat values need to be grabbed differently otherwise they just:
				else if (
					stat == STAT_ENHANCEDDEFENSE ||				// return 0
					stat == STAT_ENHANCEDMAXIMUMDAMAGE ||		// return 0
					stat == STAT_ENHANCEDMINIMUMDAMAGE ||		// return 0
					stat == STAT_MINIMUMDAMAGE ||				// return base min 1h weapon damage
					stat == STAT_MAXIMUMDAMAGE ||				// return base max 1h weapon damage
					stat == STAT_SECONDARYMINIMUMDAMAGE ||		// return base min 2h weapon damage
					stat == STAT_SECONDARYMAXIMUMDAMAGE			// return base max 2h weapon damage
					)
				{
					value = GetStatFromList(uInfo, stat);
				}
				sprintf_s(statVal, "%d", value);
			}
			name.replace(
				stat_match.prefix().length(),
				stat_match[0].length(),
				statVal);
		}
	}
	else if (name.find("%SK") != string::npos)
	{
		std::regex  stat_reg("%SK([0-9]{1,4})%", std::regex_constants::ECMAScript);
		std::smatch stat_match;

		while (std::regex_search(name, stat_match, stat_reg))
		{
			int stat2 = stoi(stat_match[1].str(), nullptr, 10);
			statVal[0] = '\0';
			if (stat2 <= (int)SKILL_MAX)
			{
				auto value = D2COMMON_GetUnitStat(item, STAT_SINGLESKILL, stat2);
				sprintf_s(statVal, "%d", value);
			}
			name.replace(
				stat_match.prefix().length(),
				stat_match[0].length(),
				statVal);
		}
	}
	else if (name.find("%OS") != string::npos)
	{
		std::regex  stat_reg("%OS([0-9]{1,4})%", std::regex_constants::ECMAScript);
		std::smatch stat_match;

		while (std::regex_search(name, stat_match, stat_reg))
		{
			int stat2 = stoi(stat_match[1].str(), nullptr, 10);
			statVal[0] = '\0';
			if (stat2 <= (int)SKILL_MAX)
			{
				auto value = D2COMMON_GetUnitStat(item, STAT_NONCLASSSKILL, stat2);
				sprintf_s(statVal, "%d", value);
			}
			name.replace(
				stat_match.prefix().length(),
				stat_match[0].length(),
				statVal);
		}
	}
	else if (name.find("%CLSK") != string::npos)
	{
		std::regex  stat_reg("%CLSK([0-9]{1,4})%", std::regex_constants::ECMAScript);
		std::smatch stat_match;

		while (std::regex_search(name, stat_match, stat_reg))
		{
			int stat2 = stoi(stat_match[1].str(), nullptr, 10);
			statVal[0] = '\0';
			if (stat2 <= (int)SKILL_MAX)
			{
				auto value = D2COMMON_GetUnitStat(item, STAT_CLASSSKILLS, stat2);
				sprintf_s(statVal, "%d", value);
			}
			name.replace(
				stat_match.prefix().length(),
				stat_match[0].length(),
				statVal);
		}
	}
	else if (name.find("%TABSK") != string::npos)
	{
		std::regex  stat_reg("%TABSK([0-9]{1,4})%", std::regex_constants::ECMAScript);
		std::smatch stat_match;

		while (std::regex_search(name, stat_match, stat_reg))
		{
			int stat2 = stoi(stat_match[1].str(), nullptr, 10);
			statVal[0] = '\0';
			if (stat2 <= (int)SKILL_MAX)
			{
				auto value = D2COMMON_GetUnitStat(item, STAT_SKILLTAB, stat2);
				sprintf_s(statVal, "%d", value);
			}
			name.replace(
				stat_match.prefix().length(),
				stat_match[0].length(),
				statVal);
		}
	}
	else if (name.find("%MULTI") != string::npos)
	{
		std::regex  stat_reg("%MULTI([0-9]{1,4}),([0-9]{1,4})%", std::regex_constants::ECMAScript);
		std::smatch stat_match;

		while (std::regex_search(name, stat_match, stat_reg))
		{
			int stat = stoi(stat_match[1].str(), nullptr, 10);
			int stat2 = stoi(stat_match[2].str(), nullptr, 10);
			statVal[0] = '\0';
			if (stat <= (int)STAT_MAX)
			{
				auto value = D2COMMON_GetUnitStat(item, stat, stat2);
				sprintf_s(statVal, "%d", value);
			}
			name.replace(
				stat_match.prefix().length(),
				stat_match[0].length(),
				statVal);
		}
	}
	else if (name.find("%CHARSTAT") != string::npos)
	{
		std::regex  stat_reg("%CHARSTAT([0-9]{1,4})%", std::regex_constants::ECMAScript);
		std::smatch stat_match;

		while (std::regex_search(name, stat_match, stat_reg))
		{
			int stat = stoi(stat_match[1].str(), nullptr, 10);
			statVal[0] = '\0';
			if (stat <= (int)STAT_MAX)
			{
				auto value = D2COMMON_GetUnitStat(D2CLIENT_GetPlayerUnit(), stat, 0);
				sprintf_s(statVal, "%d", value);
			}
			name.replace(
				stat_match.prefix().length(),
				stat_match[0].length(),
				statVal);
		}
	}

	int lengthLimit = 0;
	if (bLimit)
	{
		// Calc the extra size from colors
		std::regex color_reg(join(colorreps, "|"), std::regex_constants::ECMAScript);
		auto       color_matches = std::sregex_iterator(name.begin(), name.end(), color_reg);
		auto       color_end = std::sregex_iterator();
		auto       match_count = std::distance(color_matches, color_end);
		nColorCodesSize += 3 * match_count;

		// Increase limit for shop items
		lengthLimit = inShop ? MAX_ITEM_TEXT_SIZE : MAX_ITEM_NAME_SIZE;

		int nColorsToKeep = 0;
		for (std::sregex_iterator k = color_matches; k != color_end; ++k)
		{
			std::smatch match = *k;
			auto        pos = match.position();
			if (pos - (nColorsToKeep) > lengthLimit) { break; }
			nColorsToKeep += 3;
		}

		// Truncate if too long
		if (name.size() - nColorCodesSize > lengthLimit)
		{
			int max_size = lengthLimit + nColorsToKeep;
			name.resize(max_size);
		}
	}

	// Limit all names/descriptions to a hard cap, regarless of color codes
	lengthLimit = (uInfo->itemCode[0] == 't' || uInfo->itemCode[0] == 'i') &&
		uInfo->itemCode[1] == 'b' &&
		uInfo->itemCode[2] == 'k' ? BOOK_NAME_SIZE_LIMIT : MAX_ITEM_TEXT_SIZE;
	if (name.size() > lengthLimit - 1) { name.resize(lengthLimit - 1); }
//	PrintText(3, "\xc3\xbf\x63\x30 testing ÿc5 ąśćźżńó生命值"); // for testing purposes
}

BYTE GetAffixLevel(BYTE ilvl,
	BYTE qlvl,
	BYTE mlvl)
{
	if (ilvl > 99) { ilvl = 99; }
	if (qlvl > ilvl) { ilvl = qlvl; }
	if (mlvl > 0) { return ilvl + mlvl > 99 ? 99 : ilvl + mlvl; }
	return ((ilvl) < (99 - ((qlvl) / 2)) ? (ilvl)-((qlvl) / 2) : (ilvl) * 2 - 99);
}

// Returns the (lowest) level requirement (for any class) of an item
BYTE GetRequiredLevel(UnitAny* item)
{
	// Some crafted items can supposedly go above 100, but it's practically the same as 100
	BYTE rlvl = 100;

	// The unit for which the required level is calculated
	UnitAny* character = D2CLIENT_GetPlayerUnit();

	// Extra checks for these as they can have charges
	if (item->pItemData->dwQuality == ITEM_QUALITY_RARE || item->pItemData->dwQuality == ITEM_QUALITY_MAGIC)
	{
		// Save the original class of the character (0-6)
		DWORD temp = character->dwTxtFileNo;

		// Pretend to be every class once, use the lowest req lvl (for charged items)
		for (DWORD i = 0; i < 7; i++)
		{
			character->dwTxtFileNo = i;
			BYTE temprlvl = (BYTE)D2COMMON_GetItemLevelRequirement(item, character);

			if (temprlvl < rlvl)
			{
				rlvl = temprlvl;
				//Only one class will have a lower req than the others, so if a lower one is found we can stop
				if (i > 0) { break; }
			}
		}
		// Go back to being original class
		character->dwTxtFileNo = temp;
	}
	else { rlvl = (BYTE)D2COMMON_GetItemLevelRequirement(item, character); }

	return rlvl;
}

BYTE GetOperation(wstring* op)
{
	if (op->length() < 1) { return NONE; }
	else if ((*op)[0] == L'=') { return EQUAL; }
	else if ((*op)[0] == L'<') { return LESS_THAN; }
	else if ((*op)[0] == L'>') { return GREATER_THAN; }
	else if ((*op)[0] == L'~') { return BETWEEN; }
	return NONE;
}

unsigned int GetItemCodeIndex(char codeChar)
{
	// Characters '0'-'9' map to 0-9, and a-z map to 10-35
	return codeChar - (codeChar < 90 ? 48 : 87);
}

bool IntegerCompare(int Lvalue,
	BYTE         operation,
	int Rvalue,
	int Bvalue = 0)
{
	switch (operation)
	{
	case EQUAL:
		return Lvalue == Rvalue;
	case GREATER_THAN:
		return Lvalue > Rvalue;
	case LESS_THAN:
		return Lvalue < Rvalue;
	case BETWEEN:
		return (Rvalue <= Lvalue && Lvalue <= Bvalue);
	default:
		return false;
	}
}

namespace ItemDisplay
{
	bool item_display_initialized = false;

	void InitializeItemRules()
	{
		if (item_display_initialized) return;
		if (!IsInitialized()) { return; }


		item_display_initialized = true;
		rules.clear();
		ResetCaches();
		BH::lootFilter->ReadMapList(L"ItemDisplay", rules);
		for (unsigned int i = 0; i < rules.size(); i++)
		{
			wstring         buf;
			wstringstream   ss(rules[i].first);
			vector<wstring> tokens;
			while (ss >> buf) { tokens.push_back(buf); }

			LastConditionType = CT_None;
			vector<Condition*> RawConditions;
			for (vector<wstring>::iterator tok = tokens.begin(); tok < tokens.end(); tok++) { Condition::BuildConditions(RawConditions, (*tok)); }
			Rule* r = new Rule(RawConditions, &(rules[i].second));

			RuleList.push_back(r);
			if (r->action.colorOnMap != UNDEFINED_COLOR ||
				r->action.borderColor != UNDEFINED_COLOR ||
				r->action.dotColor != UNDEFINED_COLOR ||
				r->action.pxColor != UNDEFINED_COLOR ||
				r->action.lineColor != UNDEFINED_COLOR) {
				MapRuleList.push_back(r);
			}
			else if (r->action.name.length() == 0) { IgnoreRuleList.push_back(r); }
		}

		// Setup filter level names based on config file
		Item* item = static_cast<Item*>(BH::moduleManager->Get("item"));

		// Clear and add 0 to the list
		item->ItemFilterNames.clear();
		item->ItemFilterNames.push_back("0 - Show All Items");

		vector<pair<wstring, wstring>> filterDefinitions;
		BH::lootFilter->ReadMapList(L"ItemDisplayFilterName", filterDefinitions);
		for (unsigned int i = 0; i < filterDefinitions.size(); i++) {
			item->ItemFilterNames.push_back(to_string(i + 1) + " - " + UnicodeToAnsi(filterDefinitions[i].second.c_str()));

			// Max 9 entries
			if (i >= 8) {
				break;
			}
		}

		// If there is only 1 entry, it means no definitons were made, add standard
		if (item->ItemFilterNames.size() == 1) {
			item->ItemFilterNames.push_back("1 - Standard");
		}

		item->ReplaceItemFilters(item->ItemFilterNames);
	}

	void UninitializeItemRules()
	{
		// RuleList contains every created rule. MapRuleList and IgnoreRuleList have a subset of rules.
		// Deleting objects in RuleList is sufficient.
		if (item_display_initialized)
		{
			for (Rule* r : RuleList)
			{
				for (Condition* condition : r->conditions) { delete condition; }
				delete r;
			}
		}
		item_display_initialized = false;
		ResetCaches();
		RuleList.clear();
		MapRuleList.clear();
		IgnoreRuleList.clear();
	}
}

Rule::Rule(vector<Condition*>& inputConditions,
	wstring* str)
{
	Condition::ProcessConditions(inputConditions, conditions);
	BuildAction(str, &action);
	conditionStack.reserve(conditions.size()); // TODO: too large?
}

void BuildAction(wstring* str,
	Action* act)
{
	act->name = wstring(str->c_str());

	//// upcase all text in a %replacement_string%
	//// for some reason \w wasn't catching _, so I added it to the groups
	try
	{
		std::wregex replace_reg(
			L"(^(?:(?:%[^%]*%)|[^%])*%((?:\w|_|-)*?[a-z]+?(?:\w|_|-)*?)%)",
			std::regex_constants::ECMAScript);
		std::wsmatch replace_match;
		while (std::regex_search(act->name, replace_match, replace_reg))
		{
			auto offset = replace_match[1].first - act->name.begin();
			std::transform(
				replace_match[1].first,
				replace_match[1].second,
				act->name.begin() + offset,
				toupper
			);
		}
	}
	catch (std::exception e)
	{
		act->name = L"\377c1FILTER REGEX ERROR";
	}

	// new stuff:
	act->borderColor = ParseMapColor(act, L"BORDER");
	act->colorOnMap = ParseMapColor(act, L"MAP");
	act->dotColor = ParseMapColor(act, L"DOT");
	act->pxColor = ParseMapColor(act, L"PX");
	act->lineColor = ParseMapColor(act, L"LINE");
	act->notifyColor = ParseMapColor(act, L"NOTIFY");
	act->pingLevel = ParsePingLevel(act, L"TIER");
	act->description = ParseDescription(act);

	// legacy support:
	size_t map = act->name.find(L"%MAP%");
	if (map != wstring::npos)
	{
		int          mapColor = MAP_COLOR_WHITE;
		size_t       lastColorPos = 0;
		ColorReplace colors[] = {
			MAP_COLOR_REPLACEMENTS
		};
		for (int n = 0; n < sizeof(colors) / sizeof(colors[0]); n++)
		{
			size_t pos = act->name.find(L"%" + colors[n].key + L"%");
			if (pos != wstring::npos && pos < map && pos >= lastColorPos)
			{
				mapColor = colors[n].value;
				lastColorPos = pos;
			}
		}

		act->name.replace(map, 5, L"");
		act->colorOnMap = mapColor;
		if (act->borderColor == UNDEFINED_COLOR)
			act->borderColor = act->colorOnMap;
	}

	size_t done = act->name.find(L"%CONTINUE%");
	if (done != string::npos)
	{
		act->name.replace(done, 10, L"");
		act->stopProcessing = false;
	}
}

int ParsePingLevel(Action* act, const wstring& key_string) {
	std::wregex pattern(L"%" + key_string + L"-([0-9])%",
		std::regex_constants::ECMAScript | std::regex_constants::icase);
	int ping_level = -1;
	std::wsmatch the_match;

	if (std::regex_search(act->name, the_match, pattern)) {
		ping_level = stoi(the_match[1].str());
		act->name.replace(
			the_match.prefix().length(),
			the_match[0].length(), L"");
	}
	return ping_level;
}

wstring ParseDescription(Action* act)
{
	size_t l_idx = act->name.find(L"{");
	size_t r_idx = act->name.find(L"}");
	if (l_idx == wstring::npos || r_idx == wstring::npos || l_idx > r_idx) return L"";
	size_t start_idx = l_idx + 1;
	size_t len = r_idx - start_idx;
	wstring desc_string = act->name.substr(start_idx, len);
	act->name.replace(l_idx, len + 2, L"");
	return desc_string;
}

int ParseMapColor(Action* act,
	const wstring& key_string)
{
	std::wregex pattern(L"%" + key_string + L"-([a-f0-9]{1,4})%",
		std::regex_constants::ECMAScript | std::regex_constants::icase);
	int         color = UNDEFINED_COLOR;
	std::wsmatch the_match;

	if (std::regex_search(act->name, the_match, pattern))
	{
		color = stoi(the_match[1].str(), nullptr, 16);
		act->name.replace(
			the_match.prefix().length(),
			the_match[0].length(),
			L"");
	}
	return color;
}

const wstring Condition::tokenDelims = L"<=>~";

// Implements the shunting-yard algorithm to evaluate condition expressions
// Returns a vector of conditions in Reverse Polish Notation
void Condition::ProcessConditions(vector<Condition*>& inputConditions,
	vector<Condition*>& processedConditions)
{
	vector<Condition*> conditionStack;
	unsigned int       size = inputConditions.size();
	for (unsigned int c = 0; c < size; c++)
	{
		Condition* input = inputConditions[c];
		if (input->conditionType == CT_Operand) { processedConditions.push_back(input); }
		else if (input->conditionType == CT_BinaryOperator || input->conditionType == CT_NegationOperator)
		{
			bool go = true;
			while (go)
			{
				if (conditionStack.size() > 0)
				{
					Condition* stack = conditionStack.back();
					if ((stack->conditionType == CT_NegationOperator || stack->conditionType == CT_BinaryOperator) &&
						input->conditionType == CT_BinaryOperator)
					{
						conditionStack.pop_back();
						processedConditions.push_back(stack);
					}
					else { go = false; }
				}
				else { go = false; }
			}
			conditionStack.push_back(input);
		}
		else if (input->conditionType == CT_LeftParen) { conditionStack.push_back(input); }
		else if (input->conditionType == CT_RightParen)
		{
			bool foundLeftParen = false;
			while (conditionStack.size() > 0 && !foundLeftParen)
			{
				Condition* stack = conditionStack.back();
				conditionStack.pop_back();
				if (stack->conditionType == CT_LeftParen)
				{
					foundLeftParen = true;
					break;
				}
				else { processedConditions.push_back(stack); }
			}
			if (!foundLeftParen)
			{
				// TODO: find a way to report error
				return;
			}
		}
	}
	while (conditionStack.size() > 0)
	{
		Condition* next = conditionStack.back();
		conditionStack.pop_back();
		if (next->conditionType == CT_LeftParen || next->conditionType == CT_RightParen)
		{
			// TODO: find a way to report error
			break;
		}
		else { processedConditions.push_back(next); }
	}
}

void Condition::BuildConditions(vector<Condition*>& conditions,
	wstring              token)
{
	vector<Condition*> endConditions;
	int                i;

	// Since we don't have a real parser, things will break if [!()] appear in
	// the middle of a token (e.g. "(X AND Y)(A AND B)")

	// Look for syntax characters at the beginning of the token
	for (i = 0; i < (int)token.length(); i++)
	{
		if (token[i] == L'!') { Condition::AddNonOperand(conditions, new NegationOperator()); }
		else if (token[i] == L'(') { Condition::AddNonOperand(conditions, new LeftParen()); }
		else if (token[i] == L')') { Condition::AddNonOperand(conditions, new RightParen()); }
		else { break; }
	}
	token.erase(0, i);

	// Look for syntax characters at the end of the token
	for (i = token.length() - 1; i >= 0; i--)
	{
		if (token[i] == L'!') { endConditions.insert(endConditions.begin(), new NegationOperator()); }
		else if (token[i] == L'(') { endConditions.insert(endConditions.begin(), new LeftParen()); }
		else if (token[i] == L')') { endConditions.insert(endConditions.begin(), new RightParen()); }
		else { break; }
	}
	if (i < (int)(token.length() - 1)) { token.erase(i + 1, wstring::npos); }

	size_t delPos = token.find_first_of(tokenDelims);
	wstring key;
	wstring delim = L"";
	int    value = 0;
	int    value2 = 0;
	if (delPos != wstring::npos)
	{
		key = Trim(token.substr(0, delPos));
		delim = token.substr(delPos, 1);
		wstring valueStr = Trim(token.substr(delPos + 1));
		if (valueStr.length() > 0)
		{
			// Get min/max values if a range is given
			if (delim == L"~" && valueStr.find(L"-") != wstring::npos)
			{
				auto rangeDelim = valueStr.find(L"-");
				wstringstream ss1(valueStr.substr(0, rangeDelim));
				valueStr.erase(0, rangeDelim + 1);
				wstringstream ss2(valueStr);
				if ((ss1 >> value).fail() || (ss2 >> value2).fail())
				{
					return; // TODO: returning errors
				}
			}
			else {
				wstringstream ss(valueStr);
				if ((ss >> value).fail())
				{
					return; // TODO: returning errors
				}
			}
		}
	}
	else { key = token; }

	BYTE operation = GetOperation(&delim);
	unsigned int keylen = key.length();
	wstringstream number_ss(L"");
	int cond_num = -1;
	std::wregex multi_reg(L"([0-9]{1,10}),([0-9]{1,10})", std::regex_constants::ECMAScript | std::regex_constants::icase);
	std::wsmatch multi_match;

	FilterCondition condition = COND_NULL;
	if (condition_map.find(key) != condition_map.end())
	{
		condition = condition_map[key];
	}
	else if (keylen >= 3 && !(isupper(key[0]) || isupper(key[1]) || isupper(key[2])))
	{
		condition = COND_ITEMCODE;
	}
	else if (key.find(L'+') != std::wstring::npos)
	{
		condition = COND_ADD;
	}
	else if (key.compare(0, 2, L"SK") == 0)
	{
		condition = COND_SK;
		number_ss = wstringstream(key.substr(2));
	}
	else if (key.compare(0, 2, L"OS") == 0)
	{
		condition = COND_OS;
		number_ss = wstringstream(key.substr(2));
	}
	else if (key.compare(0, 4, L"CHSK") == 0)
	{
		condition = COND_CHSK;
		number_ss = wstringstream(key.substr(4));
	}
	else if (key.compare(0, 4, L"CLSK") == 0)
	{
		condition = COND_CLSK;
		number_ss = wstringstream(key.substr(4));
	}
	else if (key.compare(0, 5, L"TABSK") == 0)
	{
		condition = COND_TABSK;
		number_ss = wstringstream(key.substr(5));
	}
	else if (key.compare(0, 4, L"STAT") == 0)
	{
		condition = COND_STAT;
		number_ss = wstringstream(key.substr(4));
	}
	else if (key.compare(0, 8, L"CHARSTAT") == 0)
	{
		condition = COND_CHARSTAT;
		number_ss = wstringstream(key.substr(8));
	}
	else if (key.compare(0, 5, L"MULTI") == 0)
	{
		condition = COND_MULTI;
	}

	switch (condition)
	{
	case COND_AND:
		Condition::AddNonOperand(conditions, new AndOperator());
		break;
	case COND_OR:
		Condition::AddNonOperand(conditions, new OrOperator());
		break;
	case COND_ETH:
		Condition::AddOperand(conditions, new FlagsCondition(ITEM_ETHEREAL));
		break;
	case COND_SOCK:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_SOCKETS, 0, operation, value, value2));
		break;
	case COND_SET:
		Condition::AddOperand(conditions, new QualityCondition(ITEM_QUALITY_SET));
		break;
	case COND_MAG:
		Condition::AddOperand(conditions, new QualityCondition(ITEM_QUALITY_MAGIC));
		break;
	case COND_RARE:
		Condition::AddOperand(conditions, new QualityCondition(ITEM_QUALITY_RARE));
		break;
	case COND_UNI:
		Condition::AddOperand(conditions, new QualityCondition(ITEM_QUALITY_UNIQUE));
		break;
	case COND_AMAZON:
		Condition::AddOperand(conditions, new CharacterClassCondition(EQUAL, 0));
		break;
	case COND_SORCERESS:
		Condition::AddOperand(conditions, new CharacterClassCondition(EQUAL, 1));
		break;
	case COND_NECROMANCER:
		Condition::AddOperand(conditions, new CharacterClassCondition(EQUAL, 2));
		break;
	case COND_PALADIN:
		Condition::AddOperand(conditions, new CharacterClassCondition(EQUAL, 3));
		break;
	case COND_BARBARIAN:
		Condition::AddOperand(conditions, new CharacterClassCondition(EQUAL, 4));
		break;
	case COND_DRUID:
		Condition::AddOperand(conditions, new CharacterClassCondition(EQUAL, 5));
		break;
	case COND_ASSASSIN:
		Condition::AddOperand(conditions, new CharacterClassCondition(EQUAL, 6));
		break;
	case COND_CRAFTALVL:
		Condition::AddOperand(conditions, new CraftLevelCondition(operation, value, value2));
		break;
	case COND_PREFIX:
		Condition::AddOperand(conditions, new MagicPrefixCondition(operation, value, value2));
		break;
	case COND_SUFFIX:
		Condition::AddOperand(conditions, new MagicSuffixCondition(operation, value, value2));
		break;
	case COND_AUTOMOD:
		Condition::AddOperand(conditions, new AutomodCondition(operation, value, value2));
		break;
	case COND_MAPID:
		Condition::AddOperand(conditions, new MapIdCondition(operation, value, value2));
		break;
	case COND_MAPTIER:
		Condition::AddOperand(conditions, new MapTierCondition(operation, value, value2));
		break;
	case COND_CRAFT:
		Condition::AddOperand(conditions, new QualityCondition(ITEM_QUALITY_CRAFT));
		break;
	case COND_RW:
		Condition::AddOperand(conditions, new FlagsCondition(ITEM_RUNEWORD));
		break;
	case COND_NMAG:
		Condition::AddOperand(conditions, new NonMagicalCondition());
		break;
	case COND_SUP:
		Condition::AddOperand(conditions, new QualityCondition(ITEM_QUALITY_SUPERIOR));
		break;
	case COND_INF:
		Condition::AddOperand(conditions, new QualityCondition(ITEM_QUALITY_INFERIOR));
		break;
	case COND_NORM:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_NORMAL, ITEMFLAG_BASE));
		break;
	case COND_EXC:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_EXCEPTIONAL, ITEMFLAG_BASE));
		break;
	case COND_ELT:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_ELITE, ITEMFLAG_BASE));
		break;
	case COND_CLASS:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_CLASS, ITEMFLAG_BASE));
		break;
	case COND_ID:
		Condition::AddOperand(conditions, new FlagsCondition(ITEM_IDENTIFIED));
		break;
	case COND_ILVL:
		Condition::AddOperand(conditions, new ItemLevelCondition(operation, value, value2));
		break;
	case COND_QLVL:
		Condition::AddOperand(conditions, new QualityLevelCondition(operation, value, value2));
		break;
	case COND_ALVL:
		Condition::AddOperand(conditions, new AffixLevelCondition(operation, value, value2));
		break;
	case COND_CLVL:
		Condition::AddOperand(conditions, new CharStatCondition(STAT_LEVEL, 0, operation, value, value2));
		break;
	case COND_FILTLVL:
		Condition::AddOperand(conditions, new FilterLevelCondition(operation, value, value2));
		break;
	case COND_DIFF:
		Condition::AddOperand(conditions, new DifficultyCondition(operation, value, value2));
		break;
	case COND_RUNE:
		Condition::AddOperand(conditions, new RuneCondition(operation, value, value2));
		break;
	case COND_GOLD:
		Condition::AddOperand(conditions, new GoldCondition(operation, value, value2));
		break;
	case COND_GEMMED:
		Condition::AddOperand(conditions, new GemmedCondition());
		break;
	case COND_GEMTYPE:
		Condition::AddOperand(conditions, new GemTypeCondition(operation, value, value2));
		break;
	case COND_GEM:
		Condition::AddOperand(conditions, new GemLevelCondition(operation, value, value2));
		break;
	case COND_ED:
		Condition::AddOperand(conditions, new EDCondition(operation, value, value2));
		break;
	case COND_EDEF:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_ENHANCEDDEFENSE, 0, operation, value, value2));
		break;
	case COND_EDAM:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_ENHANCEDMAXIMUMDAMAGE, 0, operation, value, value2));
		break;
	case COND_DEF:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_DEFENSE, 0, operation, value, value2));
		break;
	case COND_MAXDUR:
		Condition::AddOperand(conditions, new DurabilityCondition(operation, value, value2));
		break;
	case COND_RES:
		Condition::AddOperand(conditions, new ResistAllCondition(operation, value, value2));
		break;
	case COND_FRES:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_FIRERESIST, 0, operation, value, value2));
		break;
	case COND_CRES:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_COLDRESIST, 0, operation, value, value2));
		break;
	case COND_LRES:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_LIGHTNINGRESIST, 0, operation, value, value2));
		break;
	case COND_PRES:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_POISONRESIST, 0, operation, value, value2));
		break;
	case COND_IAS:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_IAS, 0, operation, value, value2));
		break;
	case COND_FCR:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_FASTERCAST, 0, operation, value, value2));
		break;
	case COND_FHR:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_FASTERHITRECOVERY, 0, operation, value, value2));
		break;
	case COND_FBR:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_FASTERBLOCK, 0, operation, value, value2));
		break;
	case COND_LIFE:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_MAXHP, 0, operation, value, value2));
		break;
	case COND_MANA:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_MAXMANA, 0, operation, value, value2));
		break;
	case COND_QTY:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_AMMOQUANTITY, 0, operation, value, value2));
		break;
	case COND_GOODSK:
		Condition::AddOperand(conditions, new SkillListCondition(operation, CLASS_SKILLS, value));
		break;
	case COND_GOODTBSK:
		Condition::AddOperand(conditions, new SkillListCondition(operation, CLASS_TAB_SKILLS, value));
		break;
	case COND_FOOLS:
		Condition::AddOperand(conditions, new FoolsCondition());
		break;
	case COND_LVLREQ:
		Condition::AddOperand(conditions, new RequiredLevelCondition(operation, value, value2));
		break;
	case COND_ARPER:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_TOHITPERCENT, 0, operation, value, value2));
		break;
	case COND_MFIND:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_MAGICFIND, 0, operation, value, value2));
		break;
	case COND_GFIND:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_GOLDFIND, 0, operation, value, value2));
		break;
	case COND_STR:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_STRENGTH, 0, operation, value, value2));
		break;
	case COND_DEX:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_DEXTERITY, 0, operation, value, value2));
		break;
	case COND_FRW:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_FASTERRUNWALK, 0, operation, value, value2));
		break;
	case COND_MINDMG:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_MINIMUMDAMAGE, 0, operation, value, value2));
		break;
	case COND_MAXDMG:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_MAXIMUMDAMAGE, 0, operation, value, value2));
		break;
	case COND_AR:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_ATTACKRATING, 0, operation, value, value2));
		break;
	case COND_DTM:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_DAMAGETOMANA, 0, operation, value, value2));
		break;
	case COND_MAEK:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_MANAAFTEREACHKILL, 0, operation, value, value2));
		break;
	case COND_REPLIFE:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_REPLENISHLIFE, 0, operation, value, value2));
		break;
	case COND_REPQUANT:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_REPLENISHESQUANTITY, 0, operation, value, value2));
		break;
	case COND_REPAIR:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_REPAIRSDURABILITY, 0, operation, value, value2));
		break;
	case COND_ARMOR:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_ALLARMOR, ITEMFLAG_ARMOR));
		break;
	case COND_BELT:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_BELT, ITEMFLAG_ARMOR));
		break;
	case COND_CHEST:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_BODY_ARMOR, ITEMFLAG_ARMOR));
		break;
	case COND_HELM:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_HELM, ITEMFLAG_ARMOR));
		break;
	case COND_SHIELD:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_SHIELD, ITEMFLAG_ARMOR));
		break;
	case COND_GLOVES:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_GLOVES, ITEMFLAG_ARMOR));
		break;
	case COND_BOOTS:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_BOOTS, ITEMFLAG_ARMOR));
		break;
	case COND_CIRC:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_CIRCLET, ITEMFLAG_ARMOR));
		break;
	case COND_DRU:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_DRUID_PELT, ITEMFLAG_ARMOR));
		break;
	case COND_BAR:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_BARBARIAN_HELM, ITEMFLAG_ARMOR));
		break;
	case COND_DIN:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_PALADIN_SHIELD, ITEMFLAG_ARMOR));
		break;
	case COND_NEC:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_NECROMANCER_SHIELD, ITEMFLAG_ARMOR));
		break;
	case COND_SIN:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_ASSASSIN_KATAR, ITEMFLAG_WEAPON));
		break;
	case COND_SOR:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_SORCERESS_ORB, ITEMFLAG_WEAPON));
		break;
	case COND_ZON:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_AMAZON_WEAPON, ITEMFLAG_WEAPON));
		break;
	case COND_SHOP:
		Condition::AddOperand(conditions, new ShopCondition());
		break;
	case COND_EQUIPPED:
		Condition::AddOperand(conditions, new EquippedCondition());
		break;
	case COND_1H:
		Condition::AddOperand(conditions, new OneHandedCondition());
		break;
	case COND_2H:
		Condition::AddOperand(conditions, new TwoHandedCondition());
		break;
	case COND_AXE:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_AXE, ITEMFLAG_WEAPON));
		break;
	case COND_MACE:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_ALLMACE, ITEMFLAG_WEAPON));
		break;
	case COND_CLUB:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_CLUB, ITEMFLAG_WEAPON));
		break;
	case COND_TMACE:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_TIPPED_MACE, ITEMFLAG_WEAPON));
		break;
	case COND_HAMMER:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_HAMMER, ITEMFLAG_WEAPON));
		break;
	case COND_SWORD:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_SWORD, ITEMFLAG_WEAPON));
		break;
	case COND_DAGGER:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_DAGGER, ITEMFLAG_WEAPON));
		break;
	case COND_THROWING:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_THROWING, ITEMFLAG_WEAPON));
		break;
	case COND_JAV:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_JAVELIN, ITEMFLAG_WEAPON));
		break;
	case COND_SPEAR:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_SPEAR, ITEMFLAG_WEAPON));
		break;
	case COND_POLEARM:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_POLEARM, ITEMFLAG_WEAPON));
		break;
	case COND_BOW:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_BOW, ITEMFLAG_WEAPON));
		break;
	case COND_XBOW:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_CROSSBOW, ITEMFLAG_WEAPON));
		break;
	case COND_STAFF:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_STAFF, ITEMFLAG_WEAPON));
		break;
	case COND_WAND:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_WAND, ITEMFLAG_WEAPON));
		break;
	case COND_SCEPTER:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_SCEPTER, ITEMFLAG_WEAPON));
		break;
	case COND_WEAPON:
		Condition::AddOperand(conditions, new ItemGroupCondition(ITEM_GROUP_ALLWEAPON, ITEMFLAG_WEAPON));
		break;
	case COND_SK:
		if ((number_ss >> cond_num).fail() || cond_num < 0 || cond_num >(int)SKILL_MAX) { break; }
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_SINGLESKILL, cond_num, operation, value, value2));
		break;
	case COND_OS:
		if ((number_ss >> cond_num).fail() || cond_num < 0 || cond_num >(int)SKILL_MAX) { break; }
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_NONCLASSSKILL, cond_num, operation, value, value2));
		break;
	case COND_CHSK:
		// skills granted by charges
		if ((number_ss >> cond_num).fail() || cond_num < 0 || cond_num >(int)SKILL_MAX) { break; }
		Condition::AddOperand(conditions, new ChargedCondition(operation, cond_num, value, value2));
		break;
	case COND_CLSK:
		if ((number_ss >> cond_num).fail() || cond_num < 0 || cond_num >= CLASS_NA) { break; }
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_CLASSSKILLS, cond_num, operation, value, value2));
		break;
	case COND_ALLSK:
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_ALLSKILLS, 0, operation, value, value2));
		break;
	case COND_TABSK:
		if ((number_ss >> cond_num).fail() || cond_num < 0 || cond_num > SKILLTAB_MAX) { break; }
		Condition::AddOperand(conditions, new ItemStatCondition(STAT_SKILLTAB, cond_num, operation, value, value2));
		break;
	case COND_STAT:
		if ((number_ss >> cond_num).fail() || cond_num < 0 || cond_num >(int)STAT_MAX) { break; }
		Condition::AddOperand(conditions, new ItemStatCondition(cond_num, 0, operation, value, value2));
		break;
	case COND_CHARSTAT:
		if ((number_ss >> cond_num).fail() || cond_num < 0 || cond_num >(int)STAT_MAX) { break; }
		Condition::AddOperand(conditions, new CharStatCondition(cond_num, 0, operation, value, value2));
		break;
	case COND_MULTI:
		if (std::regex_search(key, multi_match, multi_reg))
		{
			int stat1, stat2;
			stat1 = stoi(multi_match[1].str(), nullptr, 10);
			stat2 = stoi(multi_match[2].str(), nullptr, 10);

			Condition::AddOperand(conditions, new ItemStatCondition(stat1, stat2, operation, value, value2));
		}
		break;
	case COND_PRICE:
		Condition::AddOperand(conditions, new ItemPriceCondition(operation, value, value2));
		break;
	case COND_ITEMCODE:
		Condition::AddOperand(conditions, new ItemCodeCondition(key.substr(0, 4).c_str()));
		break;
	case COND_ADD:
		Condition::AddOperand(conditions, new AddCondition(key, operation, value));
		break;

	case COND_NULL:
		break;
	default:
		break;
	}

	for (vector<Condition*>::iterator it = endConditions.begin(); it != endConditions.end(); it++) { Condition::AddNonOperand(conditions, (*it)); }
}

// Insert extra AND operators to stay backwards compatible with old config
// that implicitly ANDed all conditions
void Condition::AddOperand(vector<Condition*>& conditions,
	Condition* cond)
{
	if (LastConditionType == CT_Operand || LastConditionType == CT_RightParen) { conditions.push_back(new AndOperator()); }
	conditions.push_back(cond);
	LastConditionType = CT_Operand;
}

void Condition::AddNonOperand(vector<Condition*>& conditions,
	Condition* cond)
{
	if ((cond->conditionType == CT_NegationOperator || cond->conditionType == CT_LeftParen) &&
		(LastConditionType == CT_Operand || LastConditionType == CT_RightParen)) {
		conditions.push_back(new AndOperator());
	}
	conditions.push_back(cond);
	LastConditionType = cond->conditionType;
}

bool Condition::Evaluate(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	return EvaluateInternal(uInfo, arg1, arg2);
}

bool FilterLevelCondition::EvaluateInternal(UnitItemInfo* uInfo, Condition* arg1, Condition* arg2) {
	return IntegerCompare(Item::GetFilterLevel(), operation, filterLevel, filterLevel2);
}

bool TrueCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2) {
	return true;
}

bool FalseCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2) {
	return false;
}

bool NegationOperator::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2) {
	return !arg1->Evaluate(uInfo, arg1, arg2);
}

bool LeftParen::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2) {
	return false;
}

bool RightParen::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2) {
	return false;
}

bool AndOperator::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2) {
	return arg1->Evaluate(uInfo, NULL, NULL) && arg2->Evaluate(uInfo, NULL, NULL);
}

bool OrOperator::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2) {
	return arg1->Evaluate(uInfo, NULL, NULL) || arg2->Evaluate(uInfo, NULL, NULL);
}

bool ItemCodeCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	return (targetCode[0] == uInfo->itemCode[0] && targetCode[1] == uInfo->itemCode[1] && targetCode[2] == uInfo->itemCode[2] && targetCode[3] == uInfo->itemCode[3]);
}

bool FlagsCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2) {
	return ((uInfo->item->pItemData->dwFlags & flag) > 0);
}

bool QualityCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2) {
	return (uInfo->item->pItemData->dwQuality == quality);
}

bool NonMagicalCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	return (uInfo->item->pItemData->dwQuality == ITEM_QUALITY_INFERIOR ||
		uInfo->item->pItemData->dwQuality == ITEM_QUALITY_NORMAL ||
		uInfo->item->pItemData->dwQuality == ITEM_QUALITY_SUPERIOR);
}

bool GemLevelCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	if (IsGem(uInfo->attrs)) { return IntegerCompare(GetGemLevel(uInfo->attrs), operation, gemLevel, gemLevel2); }
	return false;
}

bool GemTypeCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	if (IsGem(uInfo->attrs)) { return IntegerCompare(GetGemType(uInfo->attrs), operation, gemType, gemType2); }
	return false;
}

bool RuneCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	if (IsRune(uInfo->attrs)) { return IntegerCompare(RuneNumberFromItemCode(uInfo->itemCode), operation, runeNumber, runeNumber2); }
	return false;
}

bool GoldCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	if (uInfo->itemCode[0] == 'g' && uInfo->itemCode[1] == 'l' && uInfo->itemCode[2] == 'd')
	{
		return IntegerCompare(D2COMMON_GetUnitStat(uInfo->item, STAT_GOLD, 0), operation, goldAmount, goldAmount2);
	}
	return false;
}

bool ItemLevelCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2) {
	return IntegerCompare(uInfo->item->pItemData->dwItemLevel, operation, itemLevel, itemLevel2);
}

bool QualityLevelCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	BYTE qlvl = uInfo->attrs->qualityLevel;
	return IntegerCompare(qlvl, operation, qualityLevel, qualityLevel2);
}

bool AffixLevelCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	BYTE qlvl = uInfo->attrs->qualityLevel;
	BYTE alvl = GetAffixLevel((BYTE)uInfo->item->pItemData->dwItemLevel, (BYTE)uInfo->attrs->qualityLevel, uInfo->attrs->magicLevel);
	return IntegerCompare(alvl, operation, affixLevel, affixLevel2);
}

bool MapIdCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	auto map_id = **Var_D2CLIENT_MapId();

	return IntegerCompare(map_id, operation, mapId, mapId2);
}

bool MapTierCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	int value = -1;
	if (maptiers.find(uInfo->attrs->category) != maptiers.end())
	{
		value = maptiers.at(uInfo->attrs->category);
	}
	return IntegerCompare(value, operation, mapTier, mapTier2);
}

bool CraftLevelCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	auto ilvl_int = uInfo->item->pItemData->dwItemLevel;
	auto clvl_int = D2COMMON_GetUnitStat(D2CLIENT_GetPlayerUnit(), STAT_LEVEL, 0);
	auto qlvl_int = uInfo->attrs->qualityLevel;
	auto mlvl_int = uInfo->attrs->magicLevel;

	auto craft_alvl = GetAffixLevel(
		(int)(0.5 * clvl_int) + (int)(0.5 * ilvl_int),
		qlvl_int,
		mlvl_int
	);

	return IntegerCompare(craft_alvl, operation, craftLevel, craftLevel2);
}

bool MagicPrefixCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	auto itemData = uInfo->item->pItemData;

	if (itemData->dwQuality == ITEM_QUALITY_RARE && !(itemData->dwFlags & ITEM_IDENTIFIED))
	{
		return false;
	}
	if (operation == GREATER_THAN || operation == LESS_THAN)
	{
		return false;
	}

	if ((itemData->wPrefix[0] - PREFIX_OFFSET > 0) ? IntegerCompare(itemData->wPrefix[0] - PREFIX_OFFSET, operation, prefixID1, prefixID2) : false)
	{
		return true;
	}
	if ((itemData->wPrefix[1] - PREFIX_OFFSET > 0) ? IntegerCompare(itemData->wPrefix[1] - PREFIX_OFFSET, operation, prefixID1, prefixID2) : false)
	{
		return true;
	}
	if ((itemData->wPrefix[2] - PREFIX_OFFSET > 0) ? IntegerCompare(itemData->wPrefix[2] - PREFIX_OFFSET, operation, prefixID1, prefixID2) : false)
	{
		return true;
	}

	return false;
}

bool MagicSuffixCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	auto itemData = uInfo->item->pItemData;

	if (itemData->dwQuality == ITEM_QUALITY_RARE && !(itemData->dwFlags & ITEM_IDENTIFIED))
	{
		return false;
	}
	if (operation == GREATER_THAN || operation == LESS_THAN)
	{
		return false;
	}

	if ((itemData->wSuffix[0] > 0) ? IntegerCompare(itemData->wSuffix[0], operation, suffixID1, suffixID2) : false)
	{
		return true;
	}
	if ((itemData->wSuffix[1] > 0) ? IntegerCompare(itemData->wSuffix[1], operation, suffixID1, suffixID2) : false)
	{
		return true;
	}
	if ((itemData->wSuffix[2] > 0) ? IntegerCompare(itemData->wSuffix[2], operation, suffixID1, suffixID2) : false)
	{
		return true;
	}

	return false;
}

bool AutomodCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	auto itemData = uInfo->item->pItemData;

	if ((itemData->dwQuality == ITEM_QUALITY_MAGIC || itemData->dwQuality == ITEM_QUALITY_RARE) && !(itemData->dwFlags & ITEM_IDENTIFIED))
	{
		return false;
	}

	return IntegerCompare(itemData->wAutoPrefix - AUTOMOD_OFFSET, operation, automodID, automodID2);
}

bool CharacterClassCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	return IntegerCompare(D2CLIENT_GetPlayerUnit()->dwTxtFileNo, operation, characterClass);
}

bool RequiredLevelCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	unsigned int rlvl = GetRequiredLevel(uInfo->item);

	return IntegerCompare(rlvl, operation, requiredLevel, requiredLevel2);
}

bool ItemGroupCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	switch (flagType)
	{
	case ITEMFLAG_BASE:
		return ((uInfo->attrs->baseFlags & itemGroup) > 0);
	case ITEMFLAG_WEAPON:
		return ((uInfo->attrs->weaponFlags & itemGroup) > 0);
	case ITEMFLAG_ARMOR:
		return ((uInfo->attrs->armorFlags & itemGroup) > 0);
	case ITEMFLAG_MISC:
		return ((uInfo->attrs->miscFlags & itemGroup) > 0);
	default:
		return false;
	}
}

bool EDCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	// Either enhanced defense or enhanced damage depending on item type
	WORD stat;
	if (uInfo->attrs->armorFlags & ITEM_GROUP_ALLARMOR) { stat = STAT_ENHANCEDDEFENSE; }
	else
	{
		// Normal %ED will have the same value for STAT_ENHANCEDMAXIMUMDAMAGE and STAT_ENHANCEDMINIMUMDAMAGE
		stat = STAT_ENHANCEDMAXIMUMDAMAGE;
	}
	DWORD     value = 0;
	StatList* pStatList = D2COMMON_GetStatList(uInfo->item, NULL, 0x40);
	if (pStatList)
	{
		value += D2COMMON_GetStatValueFromStatList(pStatList, stat, 0);
	}

	return IntegerCompare(value, operation, targetED, targetED2);
}

bool DurabilityCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	// Pulled from JSUnit.cpp in d2bs
	DWORD     value = 0;
	Stat      aStatList[256] = { NULL };
	StatList* pStatList = D2COMMON_GetStatList(uInfo->item, NULL, 0x40);
	if (pStatList)
	{
		DWORD dwStats = D2COMMON_CopyStatList(pStatList, (Stat*)aStatList, 256);
		for (UINT i = 0; i < dwStats; i++) { if (aStatList[i].wStatIndex == STAT_ENHANCEDMAXDURABILITY && aStatList[i].wSubIndex == 0) { value += aStatList[i].dwStatValue; } }
	}
	return IntegerCompare(value, operation, targetDurability, targetDurability2);
}

bool ChargedCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	DWORD     value = 0;
	Stat      aStatList[256] = { NULL };
	StatList* pStatList = D2COMMON_GetStatList(uInfo->item, NULL, 0x40);
	if (pStatList)
	{
		DWORD dwStats = D2COMMON_CopyStatList(pStatList, (Stat*)aStatList, 256);
		for (UINT i = 0; i < dwStats; i++)
		{
			//if (aStatList[i].wStatIndex == STAT_CHARGED)
			//	PrintText(1, "ChargedCondition::EvaluateInternal: Index=%hx, SubIndex=%hx, Value=%x", aStatList[i].wStatIndex, aStatList[i].wSubIndex, aStatList[i].dwStatValue);
			if (aStatList[i].wStatIndex == STAT_CHARGED && (aStatList[i].wSubIndex >> 6) == skill)
			{
				// 10 MSBs of subindex is the skill ID
				unsigned int level = aStatList[i].wSubIndex & 0x3F;     // 6 LSBs are the skill level
				value = (level > value) ? level : value; // use highest level
			}
		}
	}
	return IntegerCompare(value, operation, targetLevel, targetLevel2);
}

bool FoolsCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	// 1 = MAX DMG / level
	// 2 = AR / level
	// 3 = Fools

	// Pulled from JSUnit.cpp in d2bs
	unsigned int value = 0;
	Stat         aStatList[256] = { NULL };
	StatList* pStatList = D2COMMON_GetStatList(uInfo->item, NULL, 0x40);
	if (pStatList)
	{
		DWORD dwStats = D2COMMON_CopyStatList(pStatList, (Stat*)aStatList, 256);
		for (UINT i = 0; i < dwStats; i++)
		{
			if (aStatList[i].wStatIndex == STAT_MAXDAMAGEPERLEVEL && aStatList[i].wSubIndex == 0) { value += 1; }
			if (aStatList[i].wStatIndex == STAT_ATTACKRATINGPERLEVEL && aStatList[i].wSubIndex == 0) { value += 2; }
		}
	}
	// We are returning a comparison on 3 here instead of any the actual number because the way it is setup is
	// to just write FOOLS in the mh file instead of FOOLS=3 this could be changed to accept 1-3 for the different
	// types it can produce
	return IntegerCompare(value, (BYTE)EQUAL, 3);
}

bool EquippedCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	bool is_equipped = false;
	if (uInfo->item->pItemData->pOwnerInventory)
	{
		if (uInfo->item->pItemData->pOwnerInventory->dwOwnerId == D2CLIENT_GetPlayerUnit()->dwUnitId)
		{
			if (uInfo->item->pItemData->BodyLocation > 0 && uInfo->item->pItemData->ItemLocation == STORAGE_NULL)
			{
				is_equipped = true;
			}
		}
	}

	return IntegerCompare(is_equipped, (BYTE)EQUAL, 1);
}

bool ShopCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	bool is_shop = false;
	if (uInfo->item->pItemData &&
		uInfo->item->pItemData->pOwnerInventory &&
		uInfo->item->pItemData->pOwnerInventory->pOwner)
	{
		auto wNpcId = uInfo->item->pItemData->pOwnerInventory->pOwner->dwTxtFileNo;
		if (find(begin(ShopNPCs), end(ShopNPCs), wNpcId) != end(ShopNPCs))
		{
			is_shop = true;
		}
	}

	return IntegerCompare(is_shop, (BYTE)EQUAL, 1);
}

bool OneHandedCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	if (code_to_dwtxtfileno.find(uInfo->itemCode) != code_to_dwtxtfileno.end())
	{
		int weapon_number = code_to_dwtxtfileno[uInfo->itemCode];
		WeaponType weapon_type = Drawing::StatsDisplay::GetCurrentWeaponType(weapon_number);
		bool is_onehanded = false;

		if (weapon_type == WeaponType::kAxe ||
			weapon_type == WeaponType::kWand ||
			weapon_type == WeaponType::kClub ||
			weapon_type == WeaponType::kScepter ||
			weapon_type == WeaponType::kMace ||
			weapon_type == WeaponType::kHammer ||
			weapon_type == WeaponType::kSword ||
			weapon_type == WeaponType::kKnife ||
			weapon_type == WeaponType::kThrowing ||
			weapon_type == WeaponType::kJavelin ||
			weapon_type == WeaponType::kThrowingPot ||
			weapon_type == WeaponType::kClaw1 ||
			weapon_type == WeaponType::kClaw2 ||
			weapon_type == WeaponType::kOrb ||
			weapon_type == WeaponType::kAmaJav
			)
		{
			is_onehanded = true;
		}

		return IntegerCompare(is_onehanded, (BYTE)EQUAL, 1);
	}
	else
	{
		return false;
	}
}

bool TwoHandedCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	if (code_to_dwtxtfileno.find(uInfo->itemCode) != code_to_dwtxtfileno.end())
	{
		int weapon_number = code_to_dwtxtfileno[uInfo->itemCode];
		WeaponType weapon_type = Drawing::StatsDisplay::GetCurrentWeaponType(weapon_number);
		bool is_twohanded = false;

		if (weapon_type == WeaponType::kAxe2H ||
			weapon_type == WeaponType::kHammer2H ||
			weapon_type == WeaponType::kSword2H ||
			weapon_type == WeaponType::kSpear ||
			weapon_type == WeaponType::kPole ||
			weapon_type == WeaponType::kStaff ||
			weapon_type == WeaponType::kBow ||
			weapon_type == WeaponType::kCrossbow ||
			weapon_type == WeaponType::kAmaBow ||
			weapon_type == WeaponType::kAmaSpear
			)
		{
			is_twohanded = true;
		}

		return IntegerCompare(is_twohanded, (BYTE)EQUAL, true);
	}
	else
	{
		return false;
	}
}

bool GemmedCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	bool is_gemmed = false;
	if (uInfo->item->pInventory)
	{
		is_gemmed = uInfo->item->pInventory->dwItemCount > 0;
	}

	return IntegerCompare(is_gemmed, (BYTE)EQUAL, true);
}

void SkillListCondition::Init()
{
	// Clear lists
	classSkillList.clear();
	skillList.clear();
	goodClassSkills.clear();
	goodTabSkills.clear();

	// Build character skills list
	BH::config->ReadAssoc(L"ClassSkillsList", skillList);
	for (auto it = skillList.cbegin(); it != skillList.cend(); it++) { if (WStringToBool((*it).second)) { goodClassSkills.push_back(stoi((*it).first)); } }

	// Build tab skills list
	BH::config->ReadAssoc(L"TabSkillsList", classSkillList);
	for (auto it = classSkillList.cbegin(); it != classSkillList.cend(); it++) { if (WStringToBool((*it).second)) { goodTabSkills.push_back(stoi((*it).first)); } }
}

bool SkillListCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	int value = 0;
	if (type == CLASS_SKILLS)
	{
		for (unsigned int i = 0; i < goodClassSkills.size(); i++) { value += D2COMMON_GetUnitStat(uInfo->item, STAT_CLASSSKILLS, goodClassSkills.at(i)); }
	}
	else if (type == CLASS_TAB_SKILLS)
	{
		for (unsigned int i = 0; i < goodTabSkills.size(); i++) { value += D2COMMON_GetUnitStat(uInfo->item, STAT_SKILLTAB, goodTabSkills.at(i)); }
	}

	return IntegerCompare(value, operation, targetStat);
}

bool CharStatCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2) {
	return IntegerCompare(D2COMMON_GetUnitStat(D2CLIENT_GetPlayerUnit(), stat1, stat2), operation, targetStat, targetStat2);
}

bool DifficultyCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2) {
	return IntegerCompare(D2CLIENT_GetDifficulty(), operation, targetDiff, targetDiff2);
}

bool ItemStatCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2) {
	int newTarget = targetStat;
	int newTarget2 = targetStat2;
	if (itemStat == STAT_MAXHP || itemStat == STAT_MAXMANA)
	{
		newTarget *= 256;
		newTarget2 *= 256;
	}
	// These stat values need to be grabbed differently otherwise they just:
	else if (
		itemStat == STAT_ENHANCEDDEFENSE ||				// return 0
		itemStat == STAT_ENHANCEDMAXIMUMDAMAGE ||		// return 0
		itemStat == STAT_ENHANCEDMINIMUMDAMAGE ||		// return 0
		itemStat == STAT_MINIMUMDAMAGE ||				// return base min 1h weapon damage
		itemStat == STAT_MAXIMUMDAMAGE ||				// return base max 1h weapon damage
		itemStat == STAT_SECONDARYMINIMUMDAMAGE ||		// return base min 2h weapon damage
		itemStat == STAT_SECONDARYMAXIMUMDAMAGE			// return base max 2h weapon damage
		)
	{
		return IntegerCompare(GetStatFromList(uInfo, itemStat), operation, targetStat, targetStat2);
	}
	return IntegerCompare(D2COMMON_GetUnitStat(uInfo->item, itemStat, itemStat2), operation, newTarget, newTarget2);

}

bool ItemPriceCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	return IntegerCompare(D2COMMON_GetItemPrice(D2CLIENT_GetPlayerUnit(), uInfo->item, D2CLIENT_GetDifficulty(), (DWORD)D2CLIENT_GetQuestInfo(), 0x201, 1), operation, targetStat, targetStat2);
}

bool ResistAllCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	int fRes = D2COMMON_GetUnitStat(uInfo->item, STAT_FIRERESIST, 0);
	int lRes = D2COMMON_GetUnitStat(uInfo->item, STAT_LIGHTNINGRESIST, 0);
	int cRes = D2COMMON_GetUnitStat(uInfo->item, STAT_COLDRESIST, 0);
	int pRes = D2COMMON_GetUnitStat(uInfo->item, STAT_POISONRESIST, 0);
	return (IntegerCompare(fRes, operation, targetStat, targetStat2) &&
		IntegerCompare(lRes, operation, targetStat, targetStat2) &&
		IntegerCompare(cRes, operation, targetStat, targetStat2) &&
		IntegerCompare(pRes, operation, targetStat, targetStat2));
}

void AddCondition::Init()
{
	codes.clear();
	codes = split(key, L'+');
	for (auto code : codes)
	{
		for (int j = 0; j < sizeof(skills) / sizeof(skills[0]); j++)
		{
			if (code == skills[j].key)
				stats.push_back(skills[j].value);
		}
	}
}

bool AddCondition::EvaluateInternal(UnitItemInfo* uInfo,
	Condition* arg1,
	Condition* arg2)
{
	int value = 0;
	for (unsigned int i = 0; i < stats.size(); i++)
	{
		int tmpVal = D2COMMON_GetUnitStat(uInfo->item, stats[i], 0);
		if (stats[i] == STAT_MAXHP || stats[i] == STAT_MAXMANA)
		{
			tmpVal /= 256;
		}
		else if (
			stats[i] == STAT_ENHANCEDDEFENSE ||				// return 0
			stats[i] == STAT_ENHANCEDMAXIMUMDAMAGE ||		// return 0
			stats[i] == STAT_ENHANCEDMINIMUMDAMAGE ||		// return 0
			stats[i] == STAT_MINIMUMDAMAGE ||				// return base min 1h weapon damage
			stats[i] == STAT_MAXIMUMDAMAGE ||				// return base max 1h weapon damage
			stats[i] == STAT_SECONDARYMINIMUMDAMAGE ||		// return base min 2h weapon damage
			stats[i] == STAT_SECONDARYMAXIMUMDAMAGE			// return base max 2h weapon damage
			)
		{
			tmpVal = GetStatFromList(uInfo, stats[i]);
		}
		value += tmpVal;
	}

	return IntegerCompare(value, operation, targetStat);
}

int GetStatFromList(UnitItemInfo* uInfo, int itemStat)
{
	int value = 0;
	StatList* pStatList = D2COMMON_GetStatList(uInfo->item, NULL, 0x40);
	int sockets = D2COMMON_GetUnitStat(uInfo->item, STAT_SOCKETS, 0);

	if (pStatList)
	{
		value += D2COMMON_GetStatValueFromStatList(pStatList, itemStat, 0);
	}

	if (uInfo->item->pItemData->dwFlags & ITEM_RUNEWORD)
	{
		StatList* pStateStatList = D2COMMON_GetStateStatList(uInfo->item, 171);  // 171=runeword
		if (pStateStatList)
		{
			value += D2COMMON_GetStatValueFromStatList(pStateStatList, itemStat, 0);
		}
	}

	if (sockets)
	{
		for (UnitAny* sItem = uInfo->item->pInventory->pFirstItem; sItem; sItem = sItem->pItemData->pNextInvItem)
		{
			value += D2COMMON_GetUnitStat(sItem, itemStat, 0);
		}
	}
	return value;
}

void HandleUnknownItemCode(wchar_t* code,
	wchar_t* tag)
{
	// If the DATATBLS arent loaded yet then this is expected
	if (!IsInitialized()) { return; }

	// Avoid spamming endlessly
	if (UnknownItemCodes.size() > 10 || (*BH::MiscToggles2)["Allow Unknown Items"].state) { return; }
	if (UnknownItemCodes.find(code) == UnknownItemCodes.end())
	{
		//PrintText(1, "Unknown item code %s: %c%c%c\n", tag, code[0], code[1], code[2]);
		UnknownItemCodes[code] = 1;
	}
}

