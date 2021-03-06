#ifndef FONT5X7_H_
#define FONT5X7_H_

// 5x7 font for ascii characters 0x20-0xFF (32-255)
static unsigned char Font5x7[] = { /******/
0x00, 0x00, 0x00, 0x00, 0x00, // (space)
		0x00, 0x00, 0xfa, 0x00, 0x00, // !
		0x00, 0xe0, 0x00, 0xe0, 0x00, // "
		0x28, 0xfe, 0x28, 0xfe, 0x28, // #
		0x24, 0x54, 0xfe, 0x54, 0x48, // $
		0xc4, 0xc8, 0x10, 0x26, 0x46, // %
		0x6c, 0x92, 0xaa, 0x44, 0x0a, // &
		0x00, 0x00, 0xc0, 0x00, 0x00, // '
		0x00, 0x38, 0x44, 0x82, 0x00, // (
		0x00, 0x82, 0x44, 0x38, 0x00, // )
		0x10, 0x54, 0x38, 0x54, 0x10, // *
		0x10, 0x10, 0x7c, 0x10, 0x10, // +
		0x00, 0x0a, 0x0c, 0x00, 0x00, // ,
		0x10, 0x10, 0x10, 0x10, 0x10, // -
		0x00, 0x06, 0x06, 0x00, 0x00, // .
		0x04, 0x08, 0x10, 0x20, 0x40, // /
		0x7c, 0x8a, 0x92, 0xa2, 0x7c, // 0
		0x00, 0x42, 0xfe, 0x02, 0x00, // 1
		0x42, 0x86, 0x8a, 0x92, 0x62, // 2
		0x84, 0x82, 0xa2, 0xd2, 0x8c, // 3
		0x18, 0x28, 0x48, 0xfe, 0x08, // 4
		0xe4, 0xa2, 0xa2, 0xa2, 0x9c, // 5
		0x3c, 0x52, 0x92, 0x92, 0x0c, // 6
		0x80, 0x8e, 0x90, 0xa0, 0xc0, // 7
		0x6c, 0x92, 0x92, 0x92, 0x6c, // 8
		0x60, 0x92, 0x92, 0x94, 0x78, // 9
		0x00, 0x6c, 0x6c, 0x00, 0x00, // :
		0x00, 0x6a, 0x6c, 0x00, 0x00, // ;
		0x00, 0x10, 0x28, 0x44, 0x82, // <
		0x28, 0x28, 0x28, 0x28, 0x28, // =
		0x82, 0x44, 0x28, 0x10, 0x00, // >
		0x40, 0x80, 0x8a, 0x90, 0x60, // ?
		0x4c, 0x92, 0x9e, 0x82, 0x7c, // @
		0x7e, 0x88, 0x88, 0x88, 0x7e, // A
		0xfe, 0x92, 0x92, 0x92, 0x6c, // B
		0x7c, 0x82, 0x82, 0x82, 0x44, // C
		0xfe, 0x82, 0x82, 0x44, 0x38, // D
		0xfe, 0x92, 0x92, 0x92, 0x82, // E
		0xfe, 0x90, 0x90, 0x80, 0x80, // F
		0x7c, 0x82, 0x82, 0x8a, 0x4c, // G
		0xfe, 0x10, 0x10, 0x10, 0xfe, // H
		0x00, 0x82, 0xfe, 0x82, 0x00, // I
		0x04, 0x02, 0x82, 0xfc, 0x80, // J
		0xfe, 0x10, 0x28, 0x44, 0x82, // K
		0xfe, 0x02, 0x02, 0x02, 0x02, // L
		0xfe, 0x40, 0x20, 0x40, 0xfe, // M
		0xfe, 0x20, 0x10, 0x08, 0xfe, // N
		0x7c, 0x82, 0x82, 0x82, 0x7c, // O
		0xfe, 0x90, 0x90, 0x90, 0x60, // P
		0x7c, 0x82, 0x8a, 0x84, 0x7a, // Q
		0xfe, 0x90, 0x98, 0x94, 0x62, // R
		0x62, 0x92, 0x92, 0x92, 0x8c, // S
		0x80, 0x80, 0xfe, 0x80, 0x80, // T
		0xfc, 0x02, 0x02, 0x02, 0xfc, // U
		0xf8, 0x04, 0x02, 0x04, 0xf8, // V
		0xfe, 0x04, 0x18, 0x04, 0xfe, // W
		0xc6, 0x28, 0x10, 0x28, 0xc6, // X
		0xc0, 0x20, 0x1e, 0x20, 0xc0, // Y
		0x86, 0x8a, 0x92, 0xa2, 0xc2, // Z
		0x00, 0x00, 0xfe, 0x82, 0x82, // [
		0x40, 0x20, 0x10, 0x08, 0x04, // '\'
		0x82, 0x82, 0xfe, 0x00, 0x00, // ]
		0x20, 0x40, 0x80, 0x40, 0x20, // ^
		0x02, 0x02, 0x02, 0x02, 0x02, // _
		0x00, 0x80, 0x40, 0x20, 0x00, // `
		0x04, 0x2a, 0x2a, 0x2a, 0x1e, // a
		0xfe, 0x12, 0x22, 0x22, 0x1c, // b
		0x1c, 0x22, 0x22, 0x22, 0x00, // c
		0x1c, 0x22, 0x22, 0x12, 0xfe, // d
		0x1c, 0x2a, 0x2a, 0x2a, 0x18, // e
		0x10, 0x7e, 0x90, 0x40, 0x00, // f
		0x10, 0x2a, 0x2a, 0x2a, 0x3c, // g
		0xfe, 0x10, 0x20, 0x20, 0x1e, // h
		0x00, 0x00, 0xbe, 0x00, 0x00, // i
		0x00, 0x04, 0x22, 0xbc, 0x00, // j
		0x00, 0xfe, 0x08, 0x14, 0x22, // k
		0x00, 0x00, 0xfe, 0x02, 0x00, // l
		0x3e, 0x20, 0x18, 0x20, 0x1e, // m
		0x3e, 0x10, 0x20, 0x20, 0x1e, // n
		0x1c, 0x22, 0x22, 0x22, 0x1c, // o
		0x3e, 0x28, 0x28, 0x28, 0x10, // p
		0x10, 0x28, 0x28, 0x18, 0x3e, // q
		0x3e, 0x10, 0x20, 0x20, 0x10, // r
		0x12, 0x2a, 0x2a, 0x2a, 0x04, // s
		0x20, 0xfc, 0x22, 0x04, 0x00, // t
		0x3c, 0x02, 0x02, 0x04, 0x3e, // u
		0x38, 0x04, 0x02, 0x04, 0x38, // v
		0x3c, 0x02, 0x0c, 0x02, 0x3c, // w
		0x22, 0x14, 0x08, 0x14, 0x22, // x
		0x30, 0x0a, 0x0a, 0x0a, 0x3c, // y
		0x22, 0x26, 0x2a, 0x32, 0x22, // z
		0x00, 0x10, 0x6c, 0x82, 0x00, // {
		0x00, 0x00, 0xfe, 0x00, 0x00, // |  0x7c
		0x00, 0x82, 0x6c, 0x10, 0x00, // }  0x7d
		0x08, 0x10, 0x18, 0x08, 0x10, // ~  0x7e
		0x1E, 0x22, 0x42, 0x22, 0x1E, // 0x7F
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x80
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x80
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x81
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x82
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x83
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x84
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x85
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x86
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x87
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x88
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x89
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x8A
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x8B
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x8C
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x8D
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x8E
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x8F
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x90
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x91
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x92
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x93
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x94
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x95
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x96
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x97
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x98
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x99
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x9A
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x9B
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x9C
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x9D
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x9E
		0x00, 0x00, 0x00, 0x00, 0x00, // 0x9F
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xA0
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xA1
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xA2
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xA3
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xA4
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xA5
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xA6
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xA7
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xA8
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xA9
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xAA
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xAB
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xAC
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xAD
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xAE
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xAF
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xB0
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xB1
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xB2
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xB3
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xB4
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xB5
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xB6
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xB7
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xB8
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xB9
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xBA
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xBB
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xBC
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xBD
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xBE
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xBF
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xC0
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xC1
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xC2
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xC3
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xC4
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xC5
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xC6
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xC7
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xC8
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xC9
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xCA
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xCB
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xCC
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xCD
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xCE
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xCF
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xD0
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xD1
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xD2
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xD3
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xD4
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xD5
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xD6
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xD7
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xD8
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xD9
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xDA
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xDB
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xDC
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xDD
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xDE
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xDF
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xE0
		0x00, 0x00, 0xc0, 0x00, 0x00, // 0xE1
		0x00, 0x00, 0xc0, 0x00, 0x00, // ' 0xE2
		0x00, 0x00, 0xc0, 0x00, 0x00, // 0xE3
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xE4
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xE5
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xE6
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xE7
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xE8
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xE9
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xEA
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xEB
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xEC
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xED
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xEE
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xEF
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xF0
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xF1
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xF2
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xF3
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xF4
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xF5
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xF6
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xF7
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xF8
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xF9
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xFA
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xFB
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xFC
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xFD
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xFE
		0x00, 0x00, 0x00, 0x00, 0x00, // 0xFF
		};
#endif
