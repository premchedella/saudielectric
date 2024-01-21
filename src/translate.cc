#include <iostream>

#include <QtCore\QString>
#include <QtCore\QCoreApplication>
#include <QtCore\QElapsedTimer>
#include <QtCore\QFileInfo>
#include <QtCore\QDir>

#include "xpdf_parse.h"
#include "common_types.h"
#include "account_details.h"

#include "utilities.h"
#include "csv_write.h"
#include "parse_data.h"
#include "parse_summary.h"

void perform6parameters(int argc, char *argv[]);
void perform4parameters(int argc, char *argv[], QString output_path);
void Perform5Parameters(int argc, char* argv[]);

int main(int argc, char *argv[])
{
  QCoreApplication core_app(argc, argv);

  std::cout << "Application Version = " << VERSION << std::endl;

  if (argc > 1)
  {
    if (argc == 6)
    {
      perform6parameters(argc, argv);
    } else if (argc == 4)
    {
      perform4parameters(argc, argv, "");
    } else if (argc == 5)
    {
      Perform5Parameters(argc, argv);
    }
  } else
  {	  
    std::cout << "Not a valid parameters." << std::endl;    
  }
  core_app.exit();
}

void perform6parameters(int argc, char *argv[])
{
  bool is_process = true;
  int file_type = 0;
  int month = 0;
  int year = 0;
  QString in_file = "";
  QString out_file = "";

  if (QString(argv[1]).size() > 0)
  {
    file_type = QString(argv[1]).toInt();
    if ((file_type >= 0) && (file_type <= 2))
    {
    } else
    {
      std::cout << "File Type value between 0 to 2." << std::endl;
      is_process = false;
    }
  } else
  {
    is_process = false;
  }

  if (QString(argv[2]).size() > 0)
  {
    month = QString(argv[2]).toInt();
    if ((month >= 0) && (month <= 11))
    {
    } else
    {
      std::cout << "Month value between 0 to 11." << std::endl;
      is_process = false;
    }
  } else
  {
    is_process = false;
  }

  if (QString(argv[3]).size() > 0)
  {
    year = QString(argv[3]).toInt();
  } else
  {
    is_process = false;
  }

  if (QString(argv[4]).size() > 0)
  {
    in_file = QString(argv[4]);
  } else
  {
    is_process = false;
  }

  if (QString(argv[5]).size() > 0)
  {
    out_file = QString(argv[5]);
  } else
  {
    is_process = false;
  }

  QString ext = in_file.right(3);
  ext = ext.toLower();

  if (ext != "pdf")
  {
    std::cout << "Input file name extension is not PDF" <<
      in_file.toStdString() << std::endl;
    is_process = false;
  }

  ext = out_file.right(3);
  ext = ext.toLower();

  if (ext != "csv")
  {
    std::cout << "Output file name extension is not csv" <<
      out_file.toStdString() << std::endl;
    is_process = false;
  }

  //Check whether input file exists or not
  bool is_in_file_exists = QFileInfo::exists(in_file);
  if (!is_in_file_exists)
  {
    std::cout << "The Input file does not exists. " <<
      in_file.toStdString() << std::endl;
    is_process = false;
  }
  
  if (is_process)
  {
    if (year < 2018)
    {
      Utilities::SetVatType(Utilities::VatTypes::WITH_OUT);
    } else if ((year == 2018) && ((month + 1) == 1))
    {
      Utilities::SetVatType(Utilities::VatTypes::PARTIAL);
    } else {
      Utilities::SetVatType(Utilities::VatTypes::WITH);
    }

    if (file_type == 0)
    {
      Utilities::SetFileType(Utilities::InputFileTypes::KAU1_MAIN);
    } else if (file_type == 1)
    {
      Utilities::SetFileType(Utilities::InputFileTypes::KAU1_BRANCH);
    } else if (file_type == 2)
    {
      Utilities::SetFileType(Utilities::InputFileTypes::KAU2_MAIN);
    }

    // If the year is 2020 and month is July and August then set the Parser type 1
    // since the invoices format changes.  

    if ((year == 2020) && (month >= 7) && (month <= 8))
    {
      Utilities::SetParserType(Utilities::ParserTypes::PARSER_TYPE_1);
    }

    /*If year is 2020 or greater and month greater than 8 then set the
    Parser Type to 1.5 (Mix of Parser 1 and Parser 2)
    */

    if ((year == 2020) && (month >= 9) && (month <= 10))
    {
      Utilities::SetParserType(Utilities::ParserTypes::PARSER_TYPE_1_5);
    }

    /*If year is 2020 or greater and month greater than 8 then set the
    Parser Type to 1.5 (Mix of Parser 1 and Parser 2)
    */
    if (((year == 2020) && (month >= 11)) || (year >= 2021))
    {
      Utilities::SetParserType(Utilities::ParserTypes::PARSER_TYPE_2);
    }
    
    QElapsedTimer exec_timer;
    exec_timer.start();
    XPdfParse xpdf_parse(in_file);
    xpdf_parse.Parse();
    Blocks data = xpdf_parse.GetBlocks();

    ParseData parse_data;
    parse_data.FormData(data);
    quint64 time_spent = exec_timer.elapsed();
    std::cout << "Time Spent for PDF conversion and Parsing: " <<
      time_spent << " milli seconds, " << (time_spent * 0.001) <<
      " seconds. \n" << std::endl;

    std::vector<unsigned int> types = ParseData::GetTypes();
#if DEBUG     
    std::cout << "No. of Types in the input file = " << types.size()
      << std::endl;
#endif      
    exec_timer.start();
    CsvWrite csv_write(out_file);
    Utilities::ParserTypes parser_type = Utilities::GetParserType();
    if (parser_type >= Utilities::ParserTypes::PARSER_TYPE_1)
    {
      csv_write.Write();
    } else
    {
      csv_write.Write(types.size());
    }
    time_spent = exec_timer.elapsed();
    std::cout << "Time Spent for Writing data in CSV file: " << time_spent <<
      " milli seconds, " << (time_spent * 0.001) << " seconds. \n" <<
      std::endl;
  } else
  {
    std::cout << "Not a valid parameters." << std::endl;
  }
}

void perform4parameters(int argc, char *argv[], QString output_path)
{
  bool is_process = true;
  int file_type = 0;
  int month = 0;
  int year = 0;
  QString in_file = "";  

  if (QString(argv[1]).size() > 0)
  {
    month = QString(argv[1]).toInt();
    if ((month < 1) || (month > 12))
    {
      std::cout << "Month value between 1 to 12." << std::endl;
      is_process = false;
    }
  } else
  {
    is_process = false;
  }

  if (QString(argv[2]).size() > 0)
  {
    year = QString(argv[2]).toInt();
  } else
  {
    is_process = false;
  }

  if (QString(argv[3]).size() > 0)
  {
    in_file = QString(argv[3]);
  } else
  {
    is_process = false;
  }

  // Cretae file information for the input file
  QFileInfo file_info(in_file);

  // Create extension and base name of the input file
  QString ext = "";
  QString base_name = "";

  if (file_info.exists())
  {
    // Get the extension from the file info
    ext = file_info.suffix();

    // Get the base name from the file info
    base_name = QDir(file_info.absolutePath()).filePath(file_info.baseName());
  } else
  {
    std::cout << " Input file does not exist." << in_file.toStdString() << std::endl;
    is_process = false;
  }
  
  if (output_path.size() > 0)
  {
    base_name = QDir(output_path).filePath(file_info.baseName());
  }

  if (ext != "pdf")
  {
    std::cout << "Input file name extension is not Pdf" <<
      in_file.toStdString() << std::endl;
    is_process = false;
  }

  if (is_process)
  {
   
    if (((year == 2021) && (month >= 7)) || (year >= 2022))
    {
      Utilities::SetParserType(Utilities::ParserTypes::PARSER_TYPE_3);
    }

    if ((year == 2023) && (month >= 7) || (year >= 2024))
    {
      Utilities::SetParserType(Utilities::ParserTypes::PARSER_TYPE_4);
    }

    QElapsedTimer exec_timer;
    exec_timer.start();

    XPdfParse xpdf_parse(in_file);    

    xpdf_parse.Parse();
    Blocks data = xpdf_parse.GetBlocks();

    ParseData parse_data;
    parse_data.FormData(data);

    quint64 time_spent = exec_timer.elapsed();
    std::cout << "Time Spent for PDF conversion and Parsing: " <<
      time_spent << " milli seconds, " << (time_spent * 0.001) <<
      " seconds. \n" << std::endl;

    xpdf_parse.ParseSummary();
    Block summary_block = xpdf_parse.GetSummary();

    ParseSummary parse_summary;
    parse_summary.ParseData(summary_block);

    exec_timer.start();
    CsvWrite csv_write;
    csv_write.SetBaseFileName(base_name);    
    csv_write.Write();
    
    time_spent = exec_timer.elapsed();
    std::cout << "Time Spent for Writing data in CSV file: " << time_spent <<
      " milli seconds, " << (time_spent * 0.001) << " seconds. \n" <<
      std::endl;    
  }
}

void Perform5Parameters(int argc, char* argv[])
{
  QString output_path = QString(argv[4]);
  QDir dir(output_path);

  //Check whether the directory exists or not
  //If available use that directory to write otherwise 
  //Write the data in the input file directory.
  if (dir.exists())
  {
    perform4parameters(argc, argv, output_path);
  } else
  {
    perform4parameters(argc, argv, "");
  }  
}



#if 0
Debug
  2 0 2018 E:\KAUST1\projects\misc\excel_arabic\test\par_vat\2018_vat_2.pdf E : \KAUST1\projects\misc\excel_arabic\test\par_vat\kau2_main_jan_2018_4june2018.csv

  2 7 2018 E:\KAUST1\projects\misc\excel_arabic\test\vat\aug_2018\KAU3_Aug_2018.pdf E : \KAUST1\projects\misc\excel_arabic\test\vat\aug_2018\branch_aug_2018_31_Oct_2018.csv
#endif
  
