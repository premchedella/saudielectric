#ifndef UTILITIES_H_
#define UTILITIES_H_


#include <iostream>

#include <QtCore\QString>

class Utilities
{
 public:
  static QString ConvertEnglish(QString arabic);
  static QString ToFloat(QString arabic);

};

#endif //UTILITIES_H_