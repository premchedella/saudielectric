#include <iostream>

#include <QtCore\QString>
#include <QtCore\QCoreApplication>
#include <QtCore\QElapsedTimer>
#include <QtCore\QFileInfo>

#include "xpdf_parse.h"
#include "common_types.h"
#include "account_details.h"

#include "utilities.h"
#include "csv_write.h"
#include "parse_data.h"

int main(int argc, char *argv[])
{
  QCoreApplication core_app(argc, argv);

  if (argc > 1)
  {
    bool is_process = true;
    int file_type = 0;
    int month = 0;
    int year = 0;
    QString in_file = "";
    QString out_file = "";

    if (argc == 6)
    {
      if (QString(argv[1]).size() > 0)
      {
        file_type = QString(argv[1]).toInt();
        if ((file_type >=0) && (file_type <=2)) 
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

    } else
    {
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

      // If the year is >= 2020 and month is >= 07 then set the Parser type 1
      // since the invoices format changes.  

      if (((year == 2020) && (month >= 07)) || (year >= 2021)) 
      {
        Utilities::SetParserType(Utilities::ParserTypes::PARSER_TYPE_1);
      }
          
      std::cout << "Application Version = " << VERSION << std::endl;
      QElapsedTimer exec_timer;
      exec_timer.start();
      XPdfParse xpdf_parse(in_file);
      xpdf_parse.Parse();
      Blocks data = xpdf_parse.GetBlocks();      

      ParseData parse_data;
      parse_data.FormData(data);
      quint64 time_spent = exec_timer.elapsed();
      std::cout << "Time Spent for PDF convertion and Parsing: " <<
          time_spent <<  " milli seconds, " << (time_spent * 0.001) <<
          "seconds. \n" << std::endl;

      std::vector<unsigned int> types = ParseData::GetTypes();
#if DEBUG     
      std::cout << "No. of Types in the input file = " << types.size()
        << std::endl;
#endif      
      exec_timer.start();
      CsvWrite csv_write(out_file);
      csv_write.Write(types.size());
      time_spent = exec_timer.elapsed();
      std::cout << "Time Spent for Writing data in CSV file: " << time_spent <<
          " milli seconds, " << (time_spent * 0.001) << "seconds. \n" <<
          std::endl;
    } else
    {
      std::cout << "Not a valid parameters."  << std::endl;      
    }
    core_app.exit();
  } else
  {
	  std::cout << "Not a valid parameters." << std::endl;
    core_app.exit();
  }
}


#if 0
Debug
  2 0 2018 E:\KAUST1\projects\misc\excel_arabic\test\par_vat\2018_vat_2.pdf E : \KAUST1\projects\misc\excel_arabic\test\par_vat\kau2_main_jan_2018_4june2018.csv

  2 7 2018 E:\KAUST1\projects\misc\excel_arabic\test\vat\aug_2018\KAU3_Aug_2018.pdf E : \KAUST1\projects\misc\excel_arabic\test\vat\aug_2018\branch_aug_2018_31_Oct_2018.csv
#endif
  
