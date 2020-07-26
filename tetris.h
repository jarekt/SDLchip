const char import_string[] = {0xa2,0xb4,0x23,0xe6,0x22,0xb6,0x70,0x1,0xd0,0x11,0x30,0x25,0x12,0x6,0x71,0xff,0xd0,0x11,0x60,0x1a,0xd0,0x11,0x60,0x25,0x31,0x0,0x12,0xe,0xc4,0x70,0x44,0x70,0x12,0x1c,0xc3,0x3,0x60,0x1e,0x61,0x3,0x22,0x5c,0xf5,0x15,0xd0,0x14,0x3f,0x1,0x12,0x3c,0xd0,0x14,0x71,0xff,0xd0,0x14,0x23,0x40,0x12,0x1c,0xe7,0xa1,0x22,0x72,0xe8,0xa1,0x22,0x84,0xe9,0xa1,0x22,0x96,0xe2,0x9e,0x12,0x50,0x66,0x0,0xf6,0x15,0xf6,0x7,0x36,0x0,0x12,0x3c,0xd0,0x14,0x71,0x1,0x12,0x2a,0xa2,0xc4,0xf4,0x1e,0x66,0x0,0x43,0x1,0x66,0x4,0x43,0x2,0x66,0x8,0x43,0x3,0x66,0xc,0xf6,0x1e,0x0,0xee,0xd0,0x14,0x70,0xff,0x23,0x34,0x3f,0x1,0x0,0xee,0xd0,0x14,0x70,0x1,0x23,0x34,0x0,0xee,0xd0,0x14,0x70,0x1,0x23,0x34,0x3f,0x1,0x0,0xee,0xd0,0x14,0x70,0xff,0x23,0x34,0x0,0xee,0xd0,0x14,0x73,0x1,0x43,0x4,0x63,0x0,0x22,0x5c,0x23,0x34,0x3f,0x1,0x0,0xee,0xd0,0x14,0x73,0xff,0x43,0xff,0x63,0x3,0x22,0x5c,0x23,0x34,0x0,0xee,0x80,0x0,0x67,0x5,0x68,0x6,0x69,0x4,0x61,0x1f,0x65,0x10,0x62,0x7,0x0,0xee,0x40,0xe0,0x0,0x0,0x40,0xc0,0x40,0x0,0x0,0xe0,0x40,0x0,0x40,0x60,0x40,0x0,0x40,0x40,0x60,0x0,0x20,0xe0,0x0,0x0,0xc0,0x40,0x40,0x0,0x0,0xe0,0x80,0x0,0x40,0x40,0xc0,0x0,0x0,0xe0,0x20,0x0,0x60,0x40,0x40,0x0,0x80,0xe0,0x0,0x0,0x40,0xc0,0x80,0x0,0xc0,0x60,0x0,0x0,0x40,0xc0,0x80,0x0,0xc0,0x60,0x0,0x0,0x80,0xc0,0x40,0x0,0x0,0x60,0xc0,0x0,0x80,0xc0,0x40,0x0,0x0,0x60,0xc0,0x0,0xc0,0xc0,0x0,0x0,0xc0,0xc0,0x0,0x0,0xc0,0xc0,0x0,0x0,0xc0,0xc0,0x0,0x0,0x40,0x40,0x40,0x40,0x0,0xf0,0x0,0x0,0x40,0x40,0x40,0x40,0x0,0xf0,0x0,0x0,0xd0,0x14,0x66,0x35,0x76,0xff,0x36,0x0,0x13,0x38,0x0,0xee,0xa2,0xb4,0x8c,0x10,0x3c,0x1e,0x7c,0x1,0x3c,0x1e,0x7c,0x1,0x3c,0x1e,0x7c,0x1,0x23,0x5e,0x4b,0xa,0x23,0x72,0x91,0xc0,0x0,0xee,0x71,0x1,0x13,0x50,0x60,0x1b,0x6b,0x0,0xd0,0x11,0x3f,0x0,0x7b,0x1,0xd0,0x11,0x70,0x1,0x30,0x25,0x13,0x62,0x0,0xee,0x60,0x1b,0xd0,0x11,0x70,0x1,0x30,0x25,0x13,0x74,0x8e,0x10,0x8d,0xe0,0x7e,0xff,0x60,0x1b,0x6b,0x0,0xd0,0xe1,0x3f,0x0,0x13,0x90,0xd0,0xe1,0x13,0x94,0xd0,0xd1,0x7b,0x1,0x70,0x1,0x30,0x25,0x13,0x86,0x4b,0x0,0x13,0xa6,0x7d,0xff,0x7e,0xff,0x3d,0x1,0x13,0x82,0x23,0xc0,0x3f,0x1,0x23,0xc0,0x7a,0x1,0x23,0xc0,0x80,0xa0,0x6d,0x7,0x80,0xd2,0x40,0x4,0x75,0xfe,0x45,0x2,0x65,0x4,0x0,0xee,0xa7,0x0,0xf2,0x55,0xa8,0x4,0xfa,0x33,0xf2,0x65,0xf0,0x29,0x6d,0x32,0x6e,0x0,0xdd,0xe5,0x7d,0x5,0xf1,0x29,0xdd,0xe5,0x7d,0x5,0xf2,0x29,0xdd,0xe5,0xa7,0x0,0xf2,0x65,0xa2,0xb4,0x0,0xee,0x6a,0x0,0x60,0x19,0x0,0xee,0x37,0x23};
const size_t import_string_size = sizeof(import_string) / sizeof(import_string[1]);
//this is tetris.ch8 converted using my python script into a string