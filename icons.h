// 'clear', 13x13px
const unsigned char sunny[] PROGMEM = {0x02, 0x00, 0x07, 0x00, 0x30, 0x60, 0x27, 0x20, 0x0f, 0x80, 0x5f, 0xd0, 0xdf, 0xd8, 0x5f, 0xd0, 0x0f, 0x80, 0x27, 0x20, 0x30, 0x60, 0x07, 0x00, 0x02, 0x00};
// 'clouds', 13x5px
const unsigned char clouds[] PROGMEM = {0x00, 0xc0, 0x31, 0xe0, 0x7b, 0xf0, 0xff, 0xf8, 0x7f, 0xf0};
// 'few clouds', 13x8px
const unsigned char fewClouds[] PROGMEM = { 0x15, 0x00, 0x0e, 0x00, 0x1f, 0x00, 0x0e, 0xc0, 0x35, 0xe0, 0x7b, 0xf0, 0xff, 0xf8, 0x7f, 0xf0};
// 'fog', 14x12px
const unsigned char fog[] PROGMEM = { 0xf0, 0xe0, 0xf0, 0xe0, 0x0f, 0x1c, 0x0f, 0x1c, 0xf0, 0xe0, 0xf0, 0xe0, 0x0f, 0x1c, 0x0f, 0x1c, 0xf0, 0xe0, 0xf0, 0xe0, 0x0f, 0x1c, 0x0f, 0x1c};
// 'rain', 13x10px
const unsigned char rain[] PROGMEM = { 0x00, 0xc0, 0x31, 0xe0, 0x7b, 0xf0, 0xff, 0xf8, 0x7f, 0xf0, 0x24, 0x50, 0x09, 0x00, 0x40, 0xa8, 0x02, 0x20, 0x12, 0x40};
// 'snow', 9x9px
const unsigned char snow[] PROGMEM = { 0x5d, 0x00, 0xc9, 0x80, 0x2a, 0x00, 0x94, 0x80, 0xe3, 0x80, 0x94, 0x80, 0x2a, 0x00, 0xc9, 0x80, 0x5d, 0x00};
// 'tstorm', 13x10px
const unsigned char tstorm[] PROGMEM = { 0x00, 0xc0, 0x31, 0xe0, 0x7b, 0xf0, 0xff, 0xf8, 0x7f, 0xf0, 0x20, 0x80, 0x30, 0x40, 0x18, 0x80, 0x14, 0x40, 0x12, 0x40};
