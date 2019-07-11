#ifndef COMMON_TYPES_H_
#define COMMON_TYPES_H_

#include <iostream>
#include <vector>
#include <QtCore\QStringList>

typedef std::vector<QStringList> Block;
typedef std::vector<Block> Blocks;
typedef std::vector<QString> Line;

#define VERSION "1.2.1"

#define START_BLOCK_INDEX 0
#define END_BLOCK_INDEX 14
#define START_BLOCK_WORD u"ﺭﻗﻢ"
#define END_BLOCK_WORD u"ﺍﻟﻘﺪﺭﺓ‪:‬‬"
#define LAST_BLOCK_WORD u"ﻣﺠﻤﻮﻉ"

#define START_BLOCK_WORD_TWO u"ﺍﻟﻔﺌﺔ\\"

#define INDUSTRIAL_BLOCK_LENGTH 36
#define RESIDENTIAL_BLOCK_LENGTH 9

#define RESIDENTIAL_BLOCK_LENGTH_VAT 9
#define RESIDENTIAL_BLOCK_LENGTH_NON_VAT 8
#define RESIDENTIAL_BLOCK_LENGTH_PARTIAL_VAT 15

#define TYPE_1_NON_VAT_SMALL_SIZE 8
const std::vector<int> type_1_non_vat_small_1 = {10, 11, 9, 9, 12, 12, 2, 3};
const std::vector<int> type_1_non_vat_small_2 = {10, 11, 9, 9, 11, 10, 2, 3 };

#define TYPE_5_BLOCK_LENGTH_VAT 15
#define TYPE_5_BLOCK_LENGTH_NON_VAT 14
#define TYPE_5_BLOCK_LENGTH_NON_VAT_ANOTHER 19
#define TYPE_5_BLOCK_LENGTH_PARTIAL_VAT 16

#define TYPE_1_BLOCK_LENGTH_VAT 22
#define TYPE_1_BLOCK_LENGTH_NON_VAT 21
#define TYPE_1_BLOCK_LENGTH_PARTIAL_VAT 28

#define TYPE_1_LINE_5_RESIDENTIAL 12

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


//Types
#define TYPE_AR_INDUSTRIAL u"صناعي"
#define TYPE_AR_INDUSTRIAL_1 u"\uFEBB\uFEE8\uFE8E\uFECB\uFEF2"
#define TYPE_AR_RESIDENTIAL u"سكني"
#define TYPE_AR_RESIDENTIAL_1 u"\uFEB3\uFEDC\uFEE8\uFEF2"
#define TYPE_AR_COMMERCIAL u"تجاري"
#define TYPE_AR_COMMERCIAL_1 u"\uFE97\uFEA0\uFE8E\uFEAD\uFEF1"
#define TYPE_AR_MEDICAL u"خيري"
#define TYPE_AR_MEDICAL_1 u"\uFEBB\uFEA4\uFEF2"
#define TYPE_AR_CHARITY u"تعليمي"
#define TYPE_AR_CHARITY_1 u"\uFEA7\uFEF4\uFEAE\uFEF1"
#define TYPE_AR_EDUCATIONAL u"تعليمي"
#define TYPE_AR_EDUCATIONAL_1 u"\uFE97\uFECC\uFEE0\uFEF4\uFEE4\uFEF2"
#define TYPE_AR_GOVERNMENTAL u"حكومي"
#define TYPE_AR_GOVERNMENTAL_1 u"\uFEA3\uFEDC\uFEEE\uFEE3\uFEF2"



#define TYPE_ENG_INDUSTRIAL "Industrial"
#define TYPE_ENG_RESIDENTIAL "Residential"
#define TYPE_ENG_COMMERCIAL "Commercial"
#define TYPE_ENG_MEDICAL "Medical"
#define TYPE_ENG_CHARITY "Charity"
#define TYPE_ENG_EDUCATIONAL "Educational"
#define TYPE_ENG_GOVERNMENTAL "Governmental"


#define TOTAL_INNOVICES_1 u"عدد الفواتير"
#define TOTAL_INNOVICES u"\uFE8D\uFEDF\uFED4\uFEEE\uFE8D\uFE97\uFEF4\uFEAE"

#endif //COMMON_TYPES_H_


