#include "parser_data_write.h"

#include <QtCore\QDir>
#include <QtCore\QTextStream>


ParserDataWrite::ParserDataWrite()
{
  
}

ParserDataWrite::~ParserDataWrite()
{

}

void ParserDataWrite::SetBaseFileName(QString file_name)
{
  file_name_ = QDir::toNativeSeparators(file_name);
}

void ParserDataWrite::Write(ParserDataWriteTypes type)
{
 
  if (type == ParserDataWriteTypes::PARSER_DATA_WRITE_BIGGER)
  {    
    WriteBiggerData();
  } else if (type == ParserDataWriteTypes::PARSER_DATA_WRITE_SMALLER)
  {
    WriteSmallerData();
  } else
  {
    WriteSummaryData();
  }
}

QString ParserDataWrite::GetFileName()
{
  return file_name_;
}

void ParserDataWrite::WriteBiggerData()
{

}

void ParserDataWrite::WriteSmallerData()
{

}

void ParserDataWrite::WriteSummaryData()
{

}


