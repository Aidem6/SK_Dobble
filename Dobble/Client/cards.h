#ifndef CARDS_H
#define CARDS_H

//SYMBOLS: OrderedDict([(1, 'OneWay'), (2, 'Target'), (3, 'Lightning'), (4, 'Clown'), (5, 'Shades'), (6, 'Spider'), (7, 'Anchor'), (8, 'Tree'), (9, 'Web'), (10, 'Cat'), (11, 'Bomb'), (12, 'Lock'), (13, 'Dobble'), (14, 'Apple'), (15, 'Ghost'), (16, 'Man'), (17, 'Car'), (18, 'Moon'), (19, 'Eye'), (20, 'Clock'), (21, 'Scissors'), (22, 'Dinosaur'), (23, 'Spot'), (24, 'Key'), (25, 'Dog'), (26, 'Crayon'), (27, 'Exclamation'), (28, 'Horse'), (29, 'Cactus'), (30, 'Dolphin'), (31, 'Candle'), (32, 'Zebra'), (33, 'Drop'), (34, 'MapleLeaf'), (35, 'Fire'), (36, 'Turtle(ART)'), (37, 'Skull'), (38, 'Lips'), (39, 'Heart'), (40, 'Question'), (41, 'Cheeze'), (42, 'Sun'), (43, 'Ladybug'), (44, 'Snowflake'), (45, 'Treble'), (46, 'Icecube'), (47, 'Igloo'), (48, 'Carrot'), (49, 'Lightbulb'), (50, 'Bird(OK)'), (51, 'Clover'), (52, 'Flower'), (53, 'Bottle'), (54, 'YinYang'), (55, 'Hammer(STOP)'), (56, 'Dragon'), (57, 'Snowman')])

#include <QObject>
#include <QVector>
#include <iostream>
#include <stdlib.h>
#include <time.h>
class Cards : public QObject
{
    Q_OBJECT
public:
    char symbols[57][50]{
        {"( ͡° ͜ʖ ͡°)"},
        {"¯\\_(ツ)_/¯"},
        {"ヽ༼ຈل͜ຈ༽ﾉ"},
        {"ಠ_ಠ"},
        {"¯\(°_o)/¯"},
        {"( ﾟдﾟ)"},
        {"இдஇ"},
        {"(≧▽≦)"},
        {"(´_ゝ`)"},
        {" ´• ل •`"},
        {"ʕ•ᴥ•ʔ"},
        {" (▀̿̿Ĺ̯̿▀̿ ̿)"},
        {"ᶘᵒᴥᵒᶅ"},
        {"[̲̅$̲̅(̲̅ιοο̲̅)̲̅$̲̅]"},
        {"凸-_-凸"},
        {"(ㆁωㆁ*)"},
        {" (•ө•)♡"},
        {"(/◕ヮ◕)/"},
        {"(^_^.)"},
        {" (◉ω◉)"},
        {"^오^"},
        {"(*´∀｀)"},
        {"•̀.̫•́✧"},
        {"(*´∀｀)"},
        {"(๑´ڡ`๑)"},
        {"(・∀・)"},
        {"༼ ºلº ༽"},
        {"ლ(´ڡ`ლ)"},
        {" (･ิω･ิ)"},
        {"ヽ(^o^)丿"},
        {"(*^_^*)"},
        {"٩(♡ε♡ )۶"},
        {"(๑•̀ㅂ•́)ﻭ✧"},
        {"(๑˃̵ᴗ˂̵)ﻭ"},
        {"(^o^)"},
        {"(✿◠‿◠)"},
        {"(＾ｕ＾)"},
        {"(-_-;)"},
        {"^_^;"},
        {"(^o^;"},
        {"(ーー;)"},
        {"('・ω・')"},
        {"(；･`д･´)"},
        {"(´-﹏-`；)"},
        {"m(_ _;)m"},
        {"( ﾟдﾟ) "},
        {"(๑´•.̫ • `๑)"},
        {"'ㅂ'"},
        {"'ㅅ'"},
        {"-ㅅ-"},
        {"(︶^︶)"},
        {"(・へ・)"},
        {"(~_~メ)"},
        {"(ノಠ益ಠ)"},
        {"Ƹ̵̡Ӝ̵̨̄Ʒ"},
        {"◕‿◕"},
        {"ó_ò"},
    };

    int cards[57][8]{
        {1, 8, 15, 16, 17, 18, 19, 20},
        {1, 9, 21, 22, 23, 24, 25, 26},
        {1, 10, 27, 28, 29, 30, 31, 32},
        {1, 11, 33, 34, 35, 36, 37, 38},
        {1, 12, 39, 40, 41, 42, 43, 44},
        {1, 13, 45, 46, 47, 48, 49, 50},
        {1, 14, 51, 52, 53, 54, 55, 56},
        {2, 8, 26, 27, 36, 41, 46, 51},
        {2, 9, 15, 32, 37, 42, 47, 52},
        {2, 10, 16, 21, 38, 43, 48, 53},
        {2, 11, 17, 22, 28, 44, 49, 54},
        {2, 12, 18, 23, 29, 33, 50, 55},
        {2, 13, 19, 24, 30, 34, 39, 56},
        {2, 14, 20, 25, 31, 35, 40, 45},
        {3, 8, 23, 32, 34, 43, 45, 54},
        {3, 9, 18, 30, 38, 40, 49, 51},
        {3, 10, 15, 24, 35, 44, 46, 55},
        {3, 11, 19, 21, 31, 41, 50, 52},
        {3, 12, 16, 25, 28, 36, 47, 56},
        {3, 13, 20, 22, 27, 33, 42, 53},
        {3, 14, 17, 26, 29, 37, 39, 48},
        {4, 8, 22, 31, 38, 39, 47, 55},
        {4, 9, 19, 29, 36, 44, 45, 53},
        {4, 10, 17, 25, 34, 42, 50, 51},
        {4, 11, 15, 23, 27, 40, 48, 56},
        {4, 12, 20, 21, 30, 37, 46, 54},
        {4, 13, 18, 26, 28, 35, 43, 52},
        {4, 14, 16, 24, 32, 33, 41, 49},
        {5, 8, 25, 30, 33, 44, 48, 52},
        {5, 9, 16, 27, 35, 39, 50, 54},
        {5, 10, 18, 22, 37, 41, 45, 56},
        {5, 11, 20, 24, 29, 43, 47, 51},
        {5, 12, 15, 26, 31, 34, 49, 53},
        {5, 13, 17, 21, 32, 36, 40, 55},
        {5, 14, 19, 23, 28, 38, 42, 46},
        {6, 8, 24, 28, 37, 40, 50, 53},
        {6, 9, 17, 31, 33, 43, 46, 56},
        {6, 10, 20, 23, 36, 39, 49, 52},
        {6, 11, 16, 26, 30, 42, 45, 55},
        {6, 12, 19, 22, 32, 35, 48, 51},
        {6, 13, 15, 25, 29, 38, 41, 54},
        {6, 14, 18, 21, 27, 34, 44, 47},
        {7, 8, 21, 29, 35, 42, 49, 56},
        {7, 9, 20, 28, 34, 41, 48, 55},
        {7, 10, 19, 26, 33, 40, 47, 54},
        {7, 11, 18, 25, 32, 39, 46, 53},
        {7, 12, 17, 24, 27, 38, 45, 52},
        {7, 13, 16, 23, 31, 37, 44, 51},
        {7, 14, 15, 22, 30, 36, 43, 50},
        {1, 2, 3, 4, 5, 6, 7, 57},
        {20, 26, 32, 38, 44, 50, 56, 57},
        {8, 9, 10, 11, 12, 13, 14, 57},
        {18, 24, 31, 36, 42, 48, 54, 57},
        {15, 21, 28, 33, 39, 45, 51, 57},
        {17, 23, 30, 35, 41, 47, 53, 57},
        {16, 22, 29, 34, 40, 46, 52, 57},
        {19, 25, 27, 37, 43, 49, 55, 57}
    };
};

#endif // CARDS_H
