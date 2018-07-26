#include <iostream>

#include <QtCore\QString>
#include <QtWidgets\QApplication>
#include <QtCore\QElapsedTimer>


#include "xpdf_parse.h"
#include "db_manager.h"

#include "ui\arabic_translate.h"
#include "common_types.h"
#include "account_details.h"
#include "industrial_data.h"

#include "utilities.h"
#include "ui\csv_write.h"

int main(int argc, char *argv[])
{
#if 1  
  QApplication a(argc, argv);

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

      QElapsedTimer exec_timer;
      exec_timer.start();
      XPdfParse xpdf_parse(in_file);
      xpdf_parse.Parse();
      Blocks data = xpdf_parse.GetBlocks();      

      ParseData parse_data;
      parse_data.FormData(data);
      quint64 time_spent = exec_timer.elapsed();
      std::cout << "Time Spent for convertion and Parsing = " << time_spent <<
        " milli seconds, seconds = " << (time_spent * 0.001) << std::endl;
      std::vector<unsigned int> types = ParseData::GetTypes();
      std::cout << "No. of Types in the input file = " << types.size()
        << std::endl;
      
      exec_timer.start();
      CsvWrite csv_write(out_file);
      csv_write.Write(types.size());
      time_spent = exec_timer.elapsed();
      std::cout << "Time Spent for Writing data in CSV file = " << time_spent <<
        " milli seconds, seconds = " << (time_spent * 0.001) << std::endl;
    } else
    {
      std::cout << "Not a valid parameters."  << std::endl;      
    }
    return 0;    
  } else
  {
    ArabicTranslate w;
    w.show();
    return a.exec();
  }
  
#else  
  QString arabic = "25/10/1438"; //"4/11/1436";
  QString date = Utilities::ToGregorian(arabic);
#if 0
  QApplication a(argc, argv);

  std::cout << "Tranlate." << std::endl;
  
  int option = 0;

  if (QString(argv[1]).size() > 0)
  {
    option = QString(argv[1]).toInt();
  }

  
  std::cout << "Option value = " << option << std::endl;
    

  if (option > 0)
  {
    QString in_file = "";
    if ((argc > 2) && (QString(argv[2]).size() > 0))
    {
      in_file = QString(argv[2]);
    }

    QString out_file = "";
    if ((argc > 3) && (QString(argv[3]).size() > 0))
    {
      out_file = QString(argv[3]);
    }

    std::cout << "The Input File = " << in_file.toStdString() << std::endl;
    std::cout << "The Output File = " << out_file.toStdString() << std::endl;

    XPdfParse xpdf_parse(in_file);

    if (option == 1)
    {
      xpdf_parse.GenerateExcel(out_file);
    } else if (option == 2)
    {
      xpdf_parse.GenerateBlocks(out_file);
    } else if (option == 3)
    {
      //Convert pdf to excel sheet.
      /*
      1. First check whether the file is pdf or not.   If not not exit.
      2. If the file is pdf then convert the pdf to text.
      3. Read the text file.
      */
      //Get the extension from the Input file
      QString ext = in_file.right(3);

      if ((ext == "pdf") || (ext == "PDF"))
      {
        xpdf_parse.GeneratePdftoExcel(out_file);
      } else
      {
        std::cout << "Input file extension is not pdf." << std::endl;
      }
    } else if (option == 4)
    {
      QString ext = in_file.right(3);
      if ((ext == "pdf") || (ext == "PDF"))
      {
        xpdf_parse.Generate(out_file);
        unsigned int block_length = xpdf_parse.GetBlockLength();
        Blocks data = xpdf_parse.GetBlocks(); 
        if (block_length == INDUSTRIAL_BLOCK_LENGTH)
        {
          IndustrialData industrial_data;
          industrial_data.FormData(data);
          std::vector<AccountDetails> acc_data = industrial_data.GetDataInfo();
        }

      } else
      {
        std::cout << "Input file extension is not pdf." << std::endl;
      }

    } else if (option == 5)
    {
      std::cout << "Data Base Managment" << std::endl;
      DbManager dbm(in_file);
      bool retval = dbm.OpenDb();
      if (retval)
      {
        std::cout << "Data Base opened." << std::endl;
        QString test = "";
        retval = dbm.ShowTables();
        retval = dbm.CreateTable(test);
        retval = dbm.ShowTables();
        //retval = dbm.DeleteTable(test);
        retval = dbm.ShowTables();
        retval = dbm.InsertData(test, 1, "Prem", "Chedella");
        retval = dbm.InsertData(test, 2, "Mohamed", "Shalaby");
        retval = dbm.InsertData(test, 3, "Biswarup", "Chowdary");
        retval = dbm.InsertData(test, 4, "Aritra", "Dutta");
        retval = dbm.InsertData(test, 5, "Rahman", "Hassan");
        retval = dbm.GetData(1);
      }
    }
  } else
  {
    QString arabic = QStringLiteral("٢٢٠٤٤٠٠٠٠٠٠٥٠٨");
    //QString arabic = QStringLiteral("‫‪١٤٣٨/١١/١٤");
        
    /*int len = arabic.size();
    QChar* data = new QChar(len);
    for (unsigned int counter = 0; counter < len; counter++)
    {
      data[counter] = arabic.at(counter);
    }
    QString val = "";
    for(unsigned int counter = 0; counter < len; counter++)
    {
      if (data[counter] == 1632)      
        val = val + "0";
      else if (data[counter] == 1633)
        val = val + "1";
      else if (data[counter] == 1634)
        val = val + "2";
      else if (data[counter] == 1635)
        val = val + "3";
      else if (data[counter] == 1636)
        val = val + "4";
      else if (data[counter] == 1637)
        val = val + "5";
      else if (data[counter] == 1638)
        val = val + "6";
      else if (data[counter] == 1639)
        val = val + "7";
      else if (data[counter] == 1640)
        val = val + "8";
      else if (data[counter] == 1641)
        val = val + "9";
      else if (data[counter] == 47)
        val = val + "/";              
    }*/
        
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
      
    //delete data;
    std::cout << "English Value = " << val.toStdString() << std::endl;
  }
#endif
  return 0;
#endif
}


#if 0

2 E:\KAUST1\projects\misc\excel_arabic\test\output\x_pdf\xpdf_test_2.txt E:\KAUST1\projects\misc\excel_arabic\test\output\x_pdf\output_3.xls 

3 E:\KAUST1\projects\misc\excel_arabic\test\x_pdf\input\testCase.pdf E:\KAUST1\projects\misc\excel_arabic\test\x_pdf\output\output.xls 


2 E:\KAUST1\projects\misc\excel_arabic\arabic_translate\temp\data.txt E:\KAUST1\projects\misc\excel_arabic\test\x_pdf\output\test_2.xls

5 E:\KAUST1\projects\misc\excel_arabic\arabic_translate\database\simple.db 

2 E:\KAUST1\projects\misc\excel_arabic\arabic_translate\temp\data.txt E : \KAUST1\projects\misc\excel_arabic\test\x_pdf\output\test_2.xls

4 E:\KAUST1\projects\misc\excel_arabic\test\x_pdf\input\residential.pdf

E:\KAUST1\projects\misc\excel_arabic\test\x_pdf\output\residential.xls
  4 E:\KAUST1\projects\misc\excel_arabic\test\x_pdf\input\industry_1.pdf

Debug

  2 0 2018 E:\KAUST1\projects\misc\excel_arabic\test\par_vat\2018_vat_2.pdf E : \KAUST1\projects\misc\excel_arabic\test\par_vat\kau2_main_jan_2018_4june2018.csv
#endif
  
