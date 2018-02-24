#include <stdint.h>
#include "GLCD_PIC.h"

#define PX_CHAR_WIDTH 5
#define PX_CHAR_HEIGHT 12

// <editor-fold defaultstate="collapsed" desc="PX Defines">
#define PX_32 new_px_char(0b00000000000000000000000000000000,0b00000000000000000000000000000000)
#define PX_33 new_px_char(0b00000000000000001000000000100001,0b00001000010000100001000000000000)
#define PX_34 new_px_char(0b00000000000000000000000000000000,0b00000000101001010010100000000000)
#define PX_35 new_px_char(0b00000000000000010100101011111010,0b10111110101001010000000000000000)
#define PX_36 new_px_char(0b00000000000100011111010010100011,0b10001010010111110001000000000000)
#define PX_37 new_px_char(0b00000000001001101010101000010001,0b00010000101010101100100000000000)
#define PX_38 new_px_char(0b00000000010110010011100100101000,0b10001010010100010000000000000000)
#define PX_39 new_px_char(0b00000000000000000000000000000000,0b00000000010000100001000000000000)
#define PX_40 new_px_char(0b00000100000100001000001000010000,0b10000100001000100001000100000000)
#define PX_41 new_px_char(0b00000001000100001000100001000010,0b00010000100000100001000001000000)
#define PX_42 new_px_char(0b00000000000000000000000000000001,0b00101010111010101001000000000000)
#define PX_43 new_px_char(0b00000000000000000000010000100111,0b11001000010000000000000000000000)
#define PX_44 new_px_char(0b00000001000100011000000000000000,0b00000000000000000000000000000000)
#define PX_45 new_px_char(0b00000000000000000000000000000111,0b11000000000000000000000000000000)
#define PX_46 new_px_char(0b00000010001110001000000000000000,0b00000000000000000000000000000000)
#define PX_47 new_px_char(0b00000000000001000010001000010001,0b00010000100010000100000000000000)
#define PX_48 new_px_char(0b00000000000000001000101010001100,0b01100011000110001010100010000000)
#define PX_49 new_px_char(0b00000000000000111110010000100001,0b00001000010000101001100010000000)
#define PX_50 new_px_char(0b00000000000000111110000100010001,0b00010001000010001100010111000000)
#define PX_51 new_px_char(0b00000000000000011101000110000100,0b00011100010001000100001111100000)
#define PX_52 new_px_char(0b00000000000000010000100011111010,0b01010100101001100010000100000000)
#define PX_53 new_px_char(0b00000000000000011101000110000100,0b00100110110100001000011111100000)
#define PX_54 new_px_char(0b00000000000000011101000110001100,0b01011110000100001100010111000000)
#define PX_55 new_px_char(0b00000000000000000100001000010001,0b00001000100001000100001111100000)
#define PX_56 new_px_char(0b00000000000000011101000110001100,0b01011101000110001100010111000000)
#define PX_57 new_px_char(0b00000000000000011101000110000100,0b00111101000110001100010111000000)
#define PX_58 new_px_char(0b00000000000000001000111000100000,0b00000000010001110001000000000000)
#define PX_59 new_px_char(0b00000001000100011000000000000001,0b00011100010000000000000000000000)
#define PX_60 new_px_char(0b00000000010000010000010000010000,0b01000100010001000100000000000000)
#define PX_61 new_px_char(0b00000000000000000001111100000000,0b00111110000000000000000000000000)
#define PX_62 new_px_char(0b00000000000001000100010001000100,0b00010000010000010000010000000000)
#define PX_63 new_px_char(0b00000000000100000000010000100010,0b00100001000110001011100000000000)
#define PX_64 new_px_char(0b00000000011110000010110110101101,0b01110011000110001011100000000000)
#define PX_65 new_px_char(0b00000000000000100011000110001111,0b11100011000110001010100010000000)
#define PX_66 new_px_char(0b00000000000000011111001010010100,0b10011101001010010100100111100000)
#define PX_67 new_px_char(0b00000000000000011101000100001000,0b01000010000100001100010111000000)
#define PX_68 new_px_char(0b00000000000000011111001010010100,0b10100101001010010100100111100000)
#define PX_69 new_px_char(0b00000000000000111110000100001000,0b01011110000100001000011111100000)
#define PX_70 new_px_char(0b00000000000000000010000100001000,0b01011110000100001000011111100000)
#define PX_71 new_px_char(0b00000000000000011101000110001110,0b01000010000100001100010111000000)
#define PX_72 new_px_char(0b00000000000000100011000110001100,0b01111111000110001100011000100000)
#define PX_73 new_px_char(0b00000000000000011100010000100001,0b00001000010000100001000111000000)
#define PX_74 new_px_char(0b00000000000000001100100101000010,0b00010000100001000010001110000000)
#define PX_75 new_px_char(0b00000000000000100011000101001001,0b01000110010101001100011000100000)
#define PX_76 new_px_char(0b00000000000000111110000100001000,0b01000010000100001000010000100000)
#define PX_77 new_px_char(0b00000000000000100011000110001100,0b01101011010111011100011000100000)
#define PX_78 new_px_char(0b00000000000000100011000111001110,0b01101011010110011100111000100000)
#define PX_79 new_px_char(0b00000000000000011101000110001100,0b01100011000110001100010111000000)
#define PX_80 new_px_char(0b00000000000000000010000100001000,0b01011111000110001100010111100000)
#define PX_81 new_px_char(0b00000000010000011101010110001100,0b01100011000110001100010111000000)
#define PX_82 new_px_char(0b00000000000000100011000101001001,0b01011111000110001100010111100000)
#define PX_83 new_px_char(0b00000000000000011101000110000100,0b00011100000100001100010111000000)
#define PX_84 new_px_char(0b00000000000000001000010000100001,0b00001000010000100001001111100000)
#define PX_85 new_px_char(0b00000000000000011101000110001100,0b01100011000110001100011000100000)
#define PX_86 new_px_char(0b00000000000000001000010001010010,0b10100011000110001100011000100000)
#define PX_87 new_px_char(0b00000000000000010101010110101101,0b01101011000110001100011000100000)
#define PX_88 new_px_char(0b00000000000000100011000101010010,0b10001000101001010100011000100000)
#define PX_89 new_px_char(0b00000000000000001000010000100001,0b00001000101001010100011000100000)
#define PX_90 new_px_char(0b00000000000000111110000100010000,0b10001000100001000100001111100000)
#define PX_91 new_px_char(0b00000111000010000100001000010000,0b10000100001000010000100111000000)
#define PX_92 new_px_char(0b00000000010000100000100001000001,0b00000100001000001000010000000000)
#define PX_93 new_px_char(0b00000111001000010000100001000010,0b00010000100001000010000111000000)
#define PX_94 new_px_char(0b00000000000000000000000000000000,0b00000001000101010001000000000000)
#define PX_95 new_px_char(0b00001111100000000000000000000000,0b00000000000000000000000000000000)
#define PX_96 new_px_char(0b00000000000000000000000000000000,0b00000000000001000001000011000000)
#define PX_97 new_px_char(0b00000000000000101101100110001111,0b10100000111000000000000000000000)
#define PX_98 new_px_char(0b00000000000000011111000110001100,0b01100010111100001000010000100000)
#define PX_99 new_px_char(0b00000000000000011101000100001000,0b01100010111000000000000000000000)
#define PX_100 new_px_char(0b00000000000000111101000110001100,0b01100011111010000100001000000000)
#define PX_101 new_px_char(0b00000000000000011101000100001111,0b11100010111000000000000000000000)
#define PX_102 new_px_char(0b00000000000000000100001000010000,0b10011110001000010100100110000000)
#define PX_103 new_px_char(0b00000111010001100001111010001100,0b01100010111000000000000000000000)
#define PX_104 new_px_char(0b00000000000000100011000110001100,0b01100110110100001000010000100000)
#define PX_105 new_px_char(0b00000000000000011100010000100001,0b00001000011000000001000000000000)
#define PX_106 new_px_char(0b00000011001001010010100001000010,0b00010000100001100000000100000000)
#define PX_107 new_px_char(0b00000000000000100010100100101000,0b11001010100100001000010000100000)
#define PX_108 new_px_char(0b00000000000000011100010000100001,0b00001000010000100001000011000000)
#define PX_109 new_px_char(0b00000000000000100011010110101101,0b01101010101100000000000000000000)
#define PX_110 new_px_char(0b00000000000000100011000110001100,0b01100110110100000000000000000000)
#define PX_111 new_px_char(0b00000000000000011101000110001100,0b01100010111000000000000000000000)
#define PX_112 new_px_char(0b00000000100001000010111110001100,0b01100010111100000000000000000000)
#define PX_113 new_px_char(0b00001000010000100001111010001100,0b01100011111000000000000000000000)
#define PX_114 new_px_char(0b00000000000000000010000100001000,0b01100110110100000000000000000000)
#define PX_115 new_px_char(0b00000000000000011101000101000001,0b10100010111000000000000000000000)
#define PX_116 new_px_char(0b00000000000000011001001000010000,0b10000100111100010000100000000000)
#define PX_117 new_px_char(0b00000000000000101101100110001100,0b01100011000100000000000000000000)
#define PX_118 new_px_char(0b00000000000000001000101001010100,0b01100011000100000000000000000000)
#define PX_119 new_px_char(0b00000000000000010101010110101101,0b01100011000100000000000000000000)
#define PX_120 new_px_char(0b00000000000000100010101000100001,0b00010101000100000000000000000000)
#define PX_121 new_px_char(0b00000111010001100001011011001100,0b01100011000100000000000000000000)
#define PX_122 new_px_char(0b00000000000000111110000100010001,0b00010001111100000000000000000000)
#define PX_123 new_px_char(0b00001100000100001000010000100000,0b11001000010000100001001100000000)
#define PX_124 new_px_char(0b00000000000100001000010000100001,0b00001000010000100001000000000000)
#define PX_125 new_px_char(0b00000001100100001000010000100110,0b00001000010000100001000001100000)
#define PX_126 new_px_char(0b00000000000000000000000000000000,0b00000000100110101100100000000000)
// </editor-fold>

typedef struct {
    uint32_t part[2];
} px_char;

px_char new_px_char(uint32_t a, uint32_t b);
inline px_char px_map(char c);

void draw_px_char(int x, int y, px_char p);
void print_px_char(int x, int y, char c);
void print_px_string(int x, int y, char *s);