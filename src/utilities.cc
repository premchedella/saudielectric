#include "utilities.h"

#include <QtCore\QStringList>
#include <QtCore\QString>
#include <QtCore\QDate>

#include "common_types.h"

Utilities::VatTypes Utilities::vat_type_ = Utilities::VatTypes::WITH;
Utilities::InputFileTypes Utilities::file_type_ = 
    Utilities::InputFileTypes::KAU1_MAIN;

bool Utilities::is_other_fees_= false;
Utilities::ParserTypes Utilities::parser_type_ = 
    Utilities::ParserTypes::PARSER_TYPE_0;

QStringList Utilities::months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                                 "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

bool Utilities::is_extra_word_ = false;

QString Utilities::ConvertEnglish(QString arabic)
{
  QChar *data = arabic.data();
  QString val = "";
  bool is_negative = false;

  while (!data->isNull())
  {
    if (*data == 1632)
      val = val + "0";
    else if (*data == 1633)
      val = val + "1";
    else if (*data == 1634)
      val = val + "2";
    else if (*data == 1635)
      val = val + "3";
    else if (*data == 1636)
      val = val + "4";
    else if (*data == 1637)
      val = val + "5";
    else if (*data == 1638)
      val = val + "6";
    else if (*data == 1639)
      val = val + "7";
    else if (*data == 1640)
      val = val + "8";
    else if (*data == 1641)
      val = val + "9";
    else if (*data == 47)
      val = val + "/"; 
    else if (*data == 46)
      val = val + ".";
    else if (*data == 45)
      is_negative = true;

    ++data;
  }

  if (is_negative)
  {
    val = "-" + val;
  }

  return val;
}

QString Utilities::ToFloat(QString arabic)
{
  QString val = arabic;
  val.insert((arabic.size() - 2), ".");
  return val;
}

QString Utilities::ToDate(QString mmddyyy)
{
  QString ddmmyyyy = "";
  QChar sep = '/';
  int index = mmddyyy.indexOf(sep);

  QStringList words = mmddyyy.split('/');
  if (words.size() == 3)
  {
    int day = 0;
    int month = 0;
    int year = 0;

    //Year
    if (words.at(0).size() == 4)
    {
      year = words.at(0).toInt();
      month = words.at(1).toInt();
      day = words.at(2).toInt();
    }

    if (year == 0)
    {
      year = words.at(2).toInt();
      day = words.at(0).toInt();
      month = words.at(1).toInt();
    }
    
    if (month > 0 && month < 13)
    {
      day = day;
      month = month;
    } else
    {
      int temp = day;
      day = month;
      month = temp;
    }

    ddmmyyyy = QString::number(day).trimmed() + "/" + 
        QString::number(month).trimmed() + "/" +
        QString::number(year).trimmed();
  }

  return ddmmyyyy;
}

QString Utilities::ToDate(QString mmddyyy, QChar sep)
{
  QString ddmmyyyy = "";
  QStringList words = mmddyyy.split(sep);
  if (words.size() == 3)
  {
    int day = words.at(0).toInt();
    int month = words.at(1).toInt();
    int year = words.at(2).toInt();

    ddmmyyyy = QString::number(day).trimmed() + "/" +
      QString::number(month).trimmed() + "/" +
      QString::number(year).trimmed();
  }

  return ddmmyyyy;
}

QString Utilities::ToDot(QString value)
{
  QString val = value;
  val.insert((value.size() - 4), ".");
  return val;
}

QString Utilities::ToGregorian(QString arabic)
{
#if 0
//https://www.quora.com/How-can-we-convert-Hijri-dates-to-Gregorian-and-vice-versa-What-is-the-algorithm

  QString date = "";
  QStringList words = arabic.split('/');

  if (words.size() == 3)
  {
    float day = words.at(0).toFloat();
    float month = words.at(1).toFloat();
    float year = words.at(2).toFloat();

    float hijiri_years = (year - 1) + ((month - 1) / 12) + ((day - 1) / 354.3);
    float greogrian_elapsed_years = hijiri_years * 354.3 / 365.24;
    float start_greogrian = 622.54 + greogrian_elapsed_years;
 
    QString s_year = QString::number(floor(start_greogrian));
    month = start_greogrian - floor(start_greogrian);
    month *= 11.9908;
    QString s_month = QString::number(floor(month));    
    day = (month - floor(month)) * 30.4398;
    QString s_day = QString::number(floor(day));
    date = s_day + "/" + s_month + "/" + s_year;
  }
  return date;
#endif

https://gist.github.com/seyyah/ebe7c309d9a9a2baf4739b6c1faf4e21

  QString date = "";
  QStringList words = arabic.split('/');

  if (words.size() == 3)
  {
    int day = words.at(0).toInt();
    int month = words.at(1).toInt();
    int year = words.at(2).toInt();

    int julian_day = (((11 * year + 3) / 30) + 354 * year) +
      (+30 * month - ((month - 1) / 2)) + (day + 1948440 - 385);
    int d = 0;
    int m = 0;
    int y = 0;
    if (julian_day > 2299160) {
      int l = julian_day + 68569;
      int n = (4 * l) / 146097;
      l = l - ((146097 * n + 3) / 4);
      int i = (4000 * (l + 1)) / 1461001;
      l = l - ((1461 * i) / 4) + 31;
      int j = ((80 * l) / 2447);
      d = l - ((2447 * j) / 80);
      l = (j / 11);
      m = j + 2 - 12 * l;
      y = 100 * (n - 49) + i + l;
    } else {
      int j = julian_day + 1402;
      int k = ((j - 1) / 1461);
      int l = j - 1461 * k;
      int n = ((l - 1) / 365) - (l / 1461);
      int i = l - 365 * n + 30;
      j = ((80 * i) / 2447);
      d = i - ((2447 * j) / 80);
      i = (j / 11);
      m = j + 2 - 12 * i;
      y = 4 * k + n + i - 4716;
    }
    
    date = QString::number(d) + "/" + QString::number(m) + "/" 
        + QString::number(y);
  }

  return date;
}

QString Utilities::ToType(QString arabic)
{
  QString type = "";
  
  QString industrial = QStringLiteral(TYPE_AR_INDUSTRIAL_1);
  QString residential = QStringLiteral(TYPE_AR_RESIDENTIAL_1);
  QString commercial = QStringLiteral(TYPE_AR_COMMERCIAL_1);
  QString medical = QStringLiteral(TYPE_AR_MEDICAL_1);
  QString charity = QStringLiteral(TYPE_AR_CHARITY_1);
  QString educational = QStringLiteral(TYPE_AR_EDUCATIONAL_1);
  QString govenmental = QStringLiteral(TYPE_AR_GOVERNMENTAL_1);

  if (arabic == industrial)
  {
    type = QStringLiteral(TYPE_ENG_INDUSTRIAL);
  } else if (arabic == residential)
  {
    type = QStringLiteral(TYPE_ENG_RESIDENTIAL);
  } else if (arabic == commercial)
  {
    type = QStringLiteral(TYPE_ENG_COMMERCIAL);
  } else if (arabic == medical)
  {
    type = QStringLiteral(TYPE_ENG_MEDICAL);
  } else if (arabic == charity)
  {
    type = QStringLiteral(TYPE_ENG_CHARITY);
  } else if (arabic == educational)
  {
    type = QStringLiteral(TYPE_ENG_EDUCATIONAL);
  } else if (arabic == govenmental)
  {
    type = QStringLiteral(TYPE_ENG_GOVERNMENTAL);
  } else
  {
    std::cout << "Not a suitable Sub Type."   << std::endl;
  }
     
  return type;
}

void Utilities::SetVatType(Utilities::VatTypes type)
{
  vat_type_ = type;
}

Utilities::VatTypes Utilities::GetVatType()
{
  return vat_type_;
}

void Utilities::SetFileType(Utilities::InputFileTypes type)
{
  file_type_ = type;
}

Utilities::InputFileTypes Utilities::GetFileType()
{
  return file_type_;
}


Line Utilities::Convert(QStringList data)
{
  Line line_data;

  for (unsigned int index = 0; index < data.size(); index++)
  {
    line_data.push_back(data.at(index));
  }

  return line_data;
}

bool Utilities::IsOtherFees(QStringList data)
{
  bool is_other_fees = false;
  QString other_fees = data.at(0) + " " + data.at(1);
  QString other_fees_constant = QStringLiteral(OTHER_FEES);

  if (other_fees == other_fees_constant)
  {
    is_other_fees = true;
    is_other_fees_ = true;
  }

  return is_other_fees;
}

bool Utilities::IsOtherFees()
{
  return is_other_fees_;
}

void Utilities::SetParserType(ParserTypes parser_type)
{
  parser_type_ = parser_type;
}

Utilities::ParserTypes Utilities::GetParserType()
{
  return parser_type_;
}

QString Utilities::ToDateMonth(QString mmddyyyy)
{
  QString date = ToDate(mmddyyyy);
  QStringList date_parts = date.split("/");
  QString date_new = "";
  if (date_parts.size() == 3)
    date_new = date_parts[0] + "/" + months.at(date_parts[1].toInt() - 1) +
      "/" + date_parts[2];

  return date_new;  
}

bool Utilities::Is5and15Vat(Block data)
{
  bool is_flag = false;

  QString extra_1 = QStringLiteral(u")(%");
  QString extra_2 = QStringLiteral(u"١٥");
  QString extra_3 = QStringLiteral(u"٥");

  QStringList line_data_5_vat;
  QStringList line_data_15_vat;

  Utilities::InputFileTypes file_type = Utilities::GetFileType();

  if (file_type == Utilities::InputFileTypes::KAU2_MAIN)
  {
    //Line 9 contains 5%
    //Line 10 contains 15%
    unsigned int line_no = 9;
    line_data_5_vat = data.at(line_no);
    line_no = 10;
    line_data_15_vat = data.at(line_no);
  } else
  {
    //Line 10 contains 5%
    //Line 11 contains 15%
    unsigned int line_no = 10;
    line_data_5_vat = data.at(line_no);
    line_no = 11;
    line_data_15_vat = data.at(line_no);
  }  

  if ((line_data_5_vat.size() >= 11) && (line_data_15_vat.size() >= 11))
  {
    if (((line_data_15_vat[10] == extra_1) && (line_data_15_vat[11] == extra_2))
        &&
        ((line_data_5_vat[10] == extra_1) && (line_data_5_vat[11] == extra_3)))
    {
      is_flag = true;
    }
  }

  return is_flag;
}

bool Utilities::IsExtraWord()
{
  return is_extra_word_;
}

void Utilities::SetExtraWord(bool flag)
{
  is_extra_word_ = flag;
}
