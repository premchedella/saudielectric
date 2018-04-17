#ifndef COMMON_TYPES_H_
#define COMMON_TYPES_H_

#include <iostream>
#include <QtCore\QStringList>

typedef std::vector<QStringList> Block;
typedef std::vector<Block> Blocks;

#define START_BLOCK_INDEX 0
#define END_BLOCK_INDEX 14
#define START_BLOCK_WORD "ﺭﻗﻢ"
#define END_BLOCK_WORD "ﺍﻟﻘﺪﺭﺓ‪:‬‬"

#define INDUSTRIAL_BLOCK_LENGTH 36
#define RESIDENTIAL_BLOCK_LENGTH 8

#define HARDLES_WORDS_SIZE 16
#define HARDLES_WORD_1_POSITION 12
#define HARDLES_WORD_2_POSITION 14
#define HARDLES_NO_LINES 6

#define INDUSTRY_HARDLES_WORDS_SIZE 1
#define INDUSTRY_HARDLES_WORD_POSITION 0
#define INDUSTRY_HARDLES_VALUE 0


//Data Base types
#define DATABASE_DIR_NAME "database"
#define DATABASE_NAME "data.db"
#define MAIN_TABLE_NAME "master"
#define SUB_TABLE_START "sub_"



#endif //COMMON_TYPES_H_