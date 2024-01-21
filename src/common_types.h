#ifndef COMMON_TYPES_H_
#define COMMON_TYPES_H_

#include <iostream>
#include <vector>
#include <QtCore\QStringList>

typedef std::vector<QStringList> Block;
typedef std::vector<Block> Blocks;
typedef std::vector<QString> Line;

#define VERSION "4.01"

#define START_BLOCK_INDEX 0

#define START_BLOCK_WORD u"ﺭﻗﻢ"
#define END_BLOCK_WORD u"ﺍﻟﻘﺪﺭﺓ‪:‬‬"
#define LAST_BLOCK_WORD u"ﻣﺠﻤﻮﻉ"
#define START_BLOCK_WORD_TWO u"ﺍﻟﻔﺌﺔ\\"

#define START_PAGE_STRING u":ﻭﺻﻒ ﺍﻟﺤﺴﺎﺏ"

//Parser 1
#define PARSER_1_START_BLOCK_WORD u"ﺭﻗﻢ ﺍﻟﺤﺴﺎﺏ"
#define PARSER_1_START_BLOCK_WORD_1 u"ﺍﻟﺤﺴﺎﺏ"
#define PARSER_1_START_BLOCK_WORD_2 u"ﺭﻗﻢ"
#define PARSER_1_15_VAT_EXTRA u"(%١٥)"

#define PARSER_1_SMALLER_LENGTH 23


#define TYPE_12_SMALL_BLOCK_LENGTH 9

#define OTHER_FEES u"ﺭﺳﻮﻡ ﺃﺧﺮﻯ"

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

//Total Invoices
#define TOTAL_INNOVICES_1 u"عدد الفواتير"
#define TOTAL_INNOVICES u"\uFE8D\uFEDF\uFED4\uFEEE\uFE8D\uFE97\uFEF4\uFEAE"


// Differentiate between bigger and smaller invoices

//#define BIG_INVOICE_CONTAINS u"(نوع الاستهلاك: طاقة غير فاعلة)"

//#define BIG_INVOICE_CONTAINS u"ﻴﺎﻧﺎﺕ ﺍﺳﺘﻬﻼﻛﺎﺕ"

//#define BIG_INVOICE_CONTAINS u"ﻴﺎﻧﺎﺕ ﺍﺳﺘﻬﻼﻛﺎﺕ"

#define BIG_INVOICE_CONTAINS u":ﻃﺎﻗﺔ ﻏﻴﺮ ﻓﺎﻋﻠﺔ("
#define BIG_INVOICE_CONTAINS_1 u"ﺍﻻﺳﺘﻬﻼﻙ("


//Debug Purpose
#define DEBUG 0

#define PRINT_FIELD_VALUE 0

#endif //COMMON_TYPES_H_


