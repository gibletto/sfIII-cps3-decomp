/*
 * EFFH6.C  staff-roll character code table
 *
 * code_tab maps each ASCII character of a staff-roll line to its character cell number (-1 for
 * none, which leaves a gap). Read by EFFH6_CODE.C, the staff-roll lines.
 */

#include "types.h"
#include "structs.h"

#pragma section TBL

extern const s8 code_tab[];

const s8 code_tab[128] = {
     -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  /* control codes 0x00-0x07 */
     -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  /* control codes 0x08-0x0F */
     -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  /* control codes 0x10-0x17 */
     -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  /* control codes 0x18-0x1F */
     -1,  69,  62,  80,  71,  -1,  -1,  -1,  /* sp ! " # $ % & ' */
     63,  64,  -1,  -1,  -1,  65,  66,  -1,  /* ( ) * + , - . / */
     52,  53,  54,  55,  56,  57,  58,  59,  /* 0 1 2 3 4 5 6 7 */
     60,  61,  67,  -1,  -1,  -1,  -1,  70,  /* 8 9 : ; < = > ? */
     -1,   0,   1,   2,   3,   4,   5,   6,  /* @ A B C D E F G */
      7,   8,   9,  10,  11,  12,  13,  14,  /* H I J K L M N O */
     15,  16,  17,  18,  19,  20,  21,  22,  /* P Q R S T U V W */
     23,  24,  25,  -1,  -1,  -1,  -1,  68,  /* X Y Z [ \ ] ^ _ */
     -1,  26,  27,  28,  29,  30,  31,  32,  /* ` a b c d e f g */
     33,  34,  35,  36,  37,  38,  39,  40,  /* h i j k l m n o */
     41,  42,  43,  44,  45,  46,  47,  48,  /* p q r s t u v w */
     49,  50,  51,  -1,  -1,  -1,  -1,  -1,  /* x y z { | } ~ DEL */
};
