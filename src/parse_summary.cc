#include "parse_summary.h"

#include <algorithm>    // std::find

#include "parser_3_summary.h"
#include "parser_4_summary.h"

#include "utilities.h"


ParseSummary::ParseSummary()
{

}

ParseSummary::~ParseSummary()
{
  
}

void ParseSummary::ParseData(Block data)
{  
  std::cout << "Parse Summary Data." << std::endl;

  Utilities::ParserTypes parser_type = Utilities::GetParserType();

  switch (parser_type)
  {
    case Utilities::ParserTypes::PARSER_TYPE_3:
    {
      Parser3Summary summary;
      summary.ParseData(data);      
    }
    break;
    case Utilities::ParserTypes::PARSER_TYPE_4:
    {
      Parser4Summary summary;
      summary.ParseData(data);      
    }
    break;
    default:
      std::cout << "Not a Summary Data parser." << std::endl;
     break;
  }
}