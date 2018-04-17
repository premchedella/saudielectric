#include "utilities.h"

QString Utilities::ConvertEnglish(QString arabic)
{
  QChar *data = arabic.data();
  QString val = "";
  while (!data->isNull())
  {
    QChar ind = *data;

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
    ++data;
  }

  return val;
}

QString Utilities::ToFloat(QString arabic)
{
  QString val = arabic;
  val.insert((arabic.size() - 2), ".");
  return val;
}