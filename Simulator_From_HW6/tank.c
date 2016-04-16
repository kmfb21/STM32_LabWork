#include"tank.h"
#include<stdint.h>
uint16_t tankimg[32][32] = {
{0x80,0x40,0x0,0x0,0x0,0x0,0x20,0x20,0x0,0x0,0x0,0x20,0x40,0x860,0x800,0x800,0x800,0x0,0x20,0x40,0x0,0x0,0x0,0x800,0x20,0x40,0x21,0x1,0x1,0x0,0x20,0x40},
{0x80,0x20,0x0,0x0,0x0,0x0,0x20,0x20,0x0,0x0,0x0,0x40,0x60,0x40,0x0,0x0,0x0,0x0,0x40,0x40,0x0,0x0,0x0,0x0,0x20,0x40,0x20,0x0,0x0,0x0,0x0,0x40},
{0x40,0x20,0x0,0x0,0x0,0x0,0x40,0x20,0x0,0x0,0x0,0x60,0xa0,0x60,0x0,0x0,0x0,0x20,0x80,0x80,0x20,0x800,0x800,0x0,0x40,0x60,0x20,0x0,0x0,0x0,0x0,0x20},
{0x20,0x0,0x0,0x0,0x0,0x0,0x40,0x40,0x1,0x0,0x20,0x40,0xa0,0x80,0x20,0x0,0x0,0x20,0x60,0x60,0x0,0x0,0x0,0x0,0x40,0x60,0x20,0x0,0x0,0x0,0x0,0x0},
{0x20,0x0,0x0,0x0,0x0,0x20,0x40,0x41,0x21,0x0,0x0,0x61,0xc1,0xc1,0x40,0x0,0x21,0x20,0x60,0x80,0x0,0x0,0x0,0x0,0x40,0x60,0x40,0x0,0x0,0x0,0x0,0x0},
{0x20,0x0,0x0,0x0,0x0,0x20,0x61,0x41,0x0,0x1,0x1,0x62,0x40,0xa2,0x0,0x0,0x1,0x0,0x21,0x41,0x802,0x1,0x0,0x0,0x20,0x60,0x40,0x0,0x0,0x0,0x0,0x0},
{0x20,0x0,0x0,0x0,0x0,0x20,0x41,0x21,0x3107,0x418a,0x28c6,0x20c5,0x1,0x2,0x1,0x2,0x1,0x2,0x1,0x2,0x1004,0x3088,0x3087,0x2024,0x0,0x40,0x40,0x0,0x0,0x0,0x0,0x0},
{0x20,0x0,0x0,0x0,0x0,0x20,0x41,0x1,0xb4d7,0xcd3a,0x8b53,0x6a6f,0x804,0x20a7,0x1805,0x3048,0x2007,0x2828,0x1807,0x1807,0x48cc,0x8ab4,0x9314,0x7290,0x1,0x20,0x40,0x0,0x0,0x0,0x0,0x0},
{0x40,0x20,0x0,0x0,0x0,0x20,0x21,0x1,0xcd5b,0xdd3c,0xccbb,0xabd7,0x2,0x59ae,0x7a32,0x6970,0x6130,0x8255,0x6992,0x2009,0x380c,0x9ab8,0xbbfb,0x9335,0x2,0x1,0x40,0x20,0x0,0x0,0x0,0x20},
{0x40,0x20,0x0,0x0,0x20,0x20,0x1,0x1,0x592c,0x79d1,0x9ab5,0xc41b,0x50cd,0xb3b9,0xcc1c,0xaaf9,0xa299,0x9a79,0x9258,0x7175,0x5831,0x6072,0x6912,0x6150,0x2,0x1,0x40,0x40,0x0,0x0,0x0,0x20},
{0x60,0x20,0x0,0x0,0x20,0x20,0x1,0x2,0xd4fb,0xcbfa,0xb2f8,0xecdf,0xc3db,0xe4df,0xcbfe,0x8155,0x6812,0x8917,0xaabd,0x9a1b,0x7096,0x9179,0xaa9b,0x8235,0x3,0x2,0x20,0x40,0x0,0x0,0x20,0x21},
{0x40,0x20,0x0,0x0,0x20,0x20,0x1,0x2,0x9af5,0xaab7,0xaa57,0xf4df,0xe47f,0xc3bd,0xc37d,0x8977,0x7054,0x7076,0xa23d,0xaa5e,0x7057,0x7877,0x9199,0x79b4,0x3,0x2,0x20,0x40,0x0,0x0,0x0,0x21},
{0x20,0x20,0x0,0x0,0x20,0x20,0x1,0x2,0x8211,0x9a35,0xa237,0xec9f,0xe49f,0xab1b,0xcbbf,0xbafd,0x8938,0x7876,0x99dc,0xa21e,0x7017,0x7016,0x8938,0x6933,0x3,0x1,0x20,0x40,0x0,0x0,0x0,0x0},
{0x20,0x0,0x0,0x0,0x20,0x20,0x1,0x2,0xab97,0xbb19,0xb299,0xec9f,0xe4bf,0xab3b,0xc3df,0xc39f,0x99ba,0x80f8,0x99fc,0xa1dd,0x7058,0x80d9,0x99da,0x7174,0x3,0x1,0x20,0x40,0x0,0x0,0x0,0x0},
{0x0,0x0,0x0,0x0,0x20,0x20,0x1,0x2,0x488b,0x70f0,0x91f6,0xe49f,0xdcbf,0xab9c,0xcc5f,0xd45f,0xdbff,0xa21c,0xa23d,0xaa5e,0x7038,0x5813,0x6013,0x58b0,0x3,0x1,0x20,0x40,0x0,0x0,0x0,0x0},
{0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x2,0xc49a,0xb399,0xb359,0xed5f,0xe57f,0xc49e,0xc45e,0xab7b,0xaafb,0xa2bb,0xaadc,0x8999,0x6834,0x8958,0xaa7b,0x8214,0x2,0x1,0x20,0x20,0x0,0x0,0x0,0x0},
{0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x7a50,0x8292,0xabb7,0xbc3a,0x3049,0xcd1d,0xbc7a,0xccfd,0xb43a,0x8253,0x8234,0x380b,0x582f,0x7933,0x7131,0x69b1,0x3,0x2,0x0,0x20,0x0,0x0,0x0,0x0},
{0x20,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0xa3f5,0xb457,0xbcb8,0xa3f6,0x1,0x3088,0x38ea,0xbcfa,0xc51a,0x1004,0x2006,0x803,0x3809,0x9295,0xb3b8,0x7a72,0x3,0x2,0x1,0x20,0x20,0x0,0x0,0x0},
{0x40,0x20,0x0,0x0,0x0,0x0,0x1,0x1,0xddfc,0xddfc,0xc539,0xa435,0x2,0x2,0x1,0xb4d8,0xacb7,0x1,0x2,0x1,0x616e,0xa356,0x9b55,0x9b95,0x2,0x2,0x21,0x40,0x20,0x20,0x0,0x0},
{0x60,0x40,0x20,0x0,0x0,0x0,0x0,0x1,0x9c54,0x93f3,0x51eb,0x3107,0x1,0x1,0x1,0xc599,0xc5da,0x803,0x1,0x1,0x8af2,0x9333,0x410a,0x49ac,0x2,0x1,0x41,0x60,0x60,0x40,0x20,0x0},
{0x60,0x40,0x40,0x20,0x0,0x0,0x0,0x0,0x0,0x802,0x0,0x1,0x1,0x0,0x0,0xbdb8,0xbdd8,0x0,0x802,0x1,0x2,0x1,0x1,0x1,0x1,0x21,0x61,0x80,0x80,0x60,0x40,0x20},
{0x60,0x60,0x40,0x20,0x20,0x0,0x0,0x0,0x801,0x0,0x0,0x0,0x1,0x0,0x1082,0xbe18,0xce99,0x20,0x21,0x1,0x0,0x2,0x1024,0x1,0x1,0x41,0x80,0x80,0x80,0x60,0x40,0x20},
{0x60,0x60,0x40,0x20,0x20,0x0,0x0,0x0,0x821,0x0,0x0,0x0,0x1082,0x0,0x20,0x4268,0x4ac9,0x80,0x60,0x0,0x0,0x0,0x0,0x1,0x21,0x40,0x60,0x80,0x60,0x60,0x20,0x20},
{0x40,0x40,0x20,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x861,0x0,0x0,0x40,0x20,0x40,0x80,0x60,0x40,0x20,0x821,0x821,0x0,0x0,0x20,0x20,0x40,0x60,0x60,0x40,0x20,0x0},
{0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x20,0x60,0x60,0x40,0x20,0x0,0x0,0x0,0x0,0x0,0x20,0x20,0x20,0x20,0x0,0x0,0x0},
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x20,0x40,0x40,0x20,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x20,0x20,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x20},
{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x20,0x20,0x20,0x20,0x0,0x0,0x0,0x0,0x0,0x20,0x20,0x20},
{0x0,0x0,0x0,0x0,0x20,0x20,0x20,0x20,0x20,0x20,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x20,0x20,0x20,0x20,0x0,0x0,0x0,0x0,0x0,0x20,0x20,0x40}
};