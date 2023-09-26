#include "parser_4_write_data.h"

#include <QtCore\QDir>
#include <QtCore\QTextStream>

#include "parse_data.h"
#include "parser_4_summary.h"

Parser4WriteData::Parser4WriteData()
{
  
}

Parser4WriteData::~Parser4WriteData()
{

}

void Parser4WriteData::WriteInvoiceData()
{

}

void Parser4WriteData::WriteBiggerData()
{
  std::cout << "Not required." << std:: endl;  
}

void Parser4WriteData::WriteSmallerData()
{
  std::cout << "Not required." << std::endl;
}

void Parser4WriteData::WriteSummaryData()
{
  std::vector<Summary4Data> summray_data = Parser4Summary::GetSummaryData();
  
  if (summray_data.size() > 0)
  {

    QString file_name = GetFileName() + "_summary.csv";
    file_name = QDir::toNativeSeparators(file_name);  

    QFile csv_file(file_name);

    if (csv_file.open(QFile::WriteOnly | QFile::Truncate))
    {           
      csv_file.close();
    }
    std::cout << "Saved the summary data in the " << file_name.toStdString() << "."
      << std::endl;
  }
}


