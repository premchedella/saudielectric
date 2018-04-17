#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <set>

//#include <QtWidgets/QApplication>
#include <QtCore\QDir>
#include <QtCore\QString>
#include <QtCore\QTextStream>
#include <QtCore\QByteArray>
#include <QtCore\QTextCodec>

#include <ActiveQt/QAxWidget>
#include <ActiveQt/QAxObject>

#include <PDFWriter\InputFile.h>
#include <PDFWriter\PDFParser.h>

#include <PDFWriter\PDFDictionary.h>
#include <PDFWriter\PDFObjectCast.h>
#include <PDFWriter\ObjectsBasicTypes.h>
#include <PDFWriter\PDFIndirectObjectReference.h>
#include <PDFWriter\PDFArray.h>
#include <PDFWriter\ParsedPrimitiveHelper.h>
#include <PDFWriter\PDFStreamInput.h>
#include <PDFWriter\RefCountPtr.h>


#include "ui\arabic_translate.h"

using namespace std;
typedef set<ObjectIDType> ObjectIDTypeSet;
/*
void TestPdfHummus();
PDFHummus::EStatusCode IterateObjectTypes(PDFObject* pdf_object,
PDFParser& pdf_parser);
void PdfHummusParse(InputFile& pdf_file, PDFParser& parser);
int tab_level;
ObjectIDTypeSet it_obj_ids;
*/
//PDF Mine

void ParsePdfMineText();
void ParseXPdfText();
void WriteExcel(QString file_name, QStringList data);


int main(int argc, char *argv[])
{
#if 1
  QApplication a(argc, argv);
  ArabicTranslate w;
  w.show();
  return a.exec();
# endif
  std::cout << "Arabic PDF Test." << std::endl;
  //TestPdfHummus();
  //ParsePdfMineText();
  ParseXPdfText();

  return 0;
}


#if 0
void TestPdfHummus()
{
  /*QString file_name = "E:\\KAUST1\\projects\\misc\\excel_arabic\\test\\testCase.pdf";*/

  QString file_name = "E:\\KAUST1\\projects\\misc\\excel_arabic\\test\\Workbook3.pdf";

  
  if (file_name.size() > 0)
  {
    std::cout << "Got the file Name." << std::endl;
    file_name = QDir::toNativeSeparators(file_name);
    //std::cout << "File Name = " << file_name.toStdString() << std::endl;
    PDFHummus::EStatusCode status = PDFHummus::eSuccess;
    InputFile pdf_file;

    status = pdf_file.OpenFile(file_name.toStdString());
    if (status != PDFHummus::eSuccess)
    {
      std::cout << "Not Able to open the PDF file for reading." << std::endl;
      return;
    } 
    
    std::cout << "Able to open the PDF file for reading." << std::endl;
    
    PDFParser parser;
    status = parser.StartPDFParsing(pdf_file.GetInputStream());
    if (status != PDFHummus::eSuccess)
    {
      std::cout << "Unable to parse input file" << std::endl; 
      return;     
    }

    std::cout << "Able to parse input file" << std::endl;
    PdfHummusParse(pdf_file, parser);

#if 0
    
    std::cout << "Number of Pages = " << parser.GetPagesCount() << std::endl;    

    PDFObjectCastPtr<PDFDictionary> catalog(
        parser.QueryDictionaryObject(parser.GetTrailer(), "Root"));
    if (!catalog)
    {
      cout << "Can't find catalog. fail" << std::endl;
      status = PDFHummus::eFailure;
      return;
    }
    std::cout << "Able to find the Catalog" << std::endl;

    //PdfParse(parser);

    tab_level = 0;
    status = IterateObjectTypes(catalog.GetPtr(), parser);

    if (status != PDFHummus::eSuccess)
    {
      cout << "Failed iterating object types.";
      return;
    }
#endif
  }
}


void PdfHummusParse(InputFile& pdf_file, PDFParser& parser)
{
  unsigned long page_count = parser.GetPagesCount();

  std::cout << "Number of Pages = " << page_count << std::endl;

  RefCountPtr<PDFDictionary> page = parser.ParsePage(0);

  if (!page)
  {
    std::cout << "Not able to get the Page." << std::endl;
    return;
  }

  std::cout << "Able to get the page." << std::endl;

  RefCountPtr<PDFObject> contents(
    parser.QueryDictionaryObject(
    page.GetPtr(), "Contents"));

  if (!contents)
    return;

  std::cout << "Type = " << contents->GetType() << std::endl;

  if (contents->GetType() == PDFObject::ePDFObjectArray)
  {
    std::cout << "Array Data." << std::endl;

  } else
  {
    std::cout << "Non Array Data." << std::endl;
    IByteReader* stream_reader =
      parser.CreateInputStreamReader((PDFStreamInput*)contents.GetPtr());
    Byte buffer[1000];
    if (stream_reader)
    {
      pdf_file.GetInputStream()->SetPosition(((PDFStreamInput*)contents.GetPtr())->GetStreamContentStart());

      while (stream_reader->NotEnded())
      {
        LongBufferSizeType read_amount =
          stream_reader->Read(buffer, 1000);
        cout.write((const char*)buffer, read_amount);
        std::cout << "Read Data Count = " << read_amount << std::endl;
      }

      /*QTextCodec *codec = QTextCodec::codecForName("UTF-16");
      QString data = codec->toUnicode((const char*)buffer);
      std::cout << "Data = " << data.toStdString() << std::endl;*/
    } else
      cout << "Unable to read content stream. " << std::endl;
  }
}



#endif


void ParsePdfMineText()
{
  QString in_file_name =
      "E:\\KAUST1\\projects\\misc\\excel_arabic\\test\\output\\pdf_miner\\pdf_miner_test_case.txt";  
  QFile inputFile(in_file_name);
  std::vector<QStringList> blocks;
  if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QTextStream in(&inputFile);
    in.setCodec("UTF-8"); // change the file codec to UTF-8.
    int counter = 0;
    QString start = QStringLiteral("ﺭﻗﻢ");
    QString end = QStringLiteral("ﻣﻌﺎﻣﻞﺍﻟﻘﺪﺭﺓ:");
    bool flag = false;
    int start_counter = 0;
    int no_blocks = 0;
    QStringList text_data;
    while (!in.atEnd())
    {
      QString line = in.readLine();     
      if (line.size() > 0)
      {
        counter++;
        text_data.push_back(line);   
           
        /*if (line == start)
        {
          flag = true;
          start_counter = counter;          
        }

        if (line == end)
        {
          flag = false;
          std::cout << "Block start = " << start_counter << ", end = " << 
              counter << " , length = " << (counter - start_counter) <<
              std::endl;   
          no_blocks++;
        }*/        
      }
    }
    std::cout << "Number of blocks = " << no_blocks << std::endl;
    std::cout << "Number of Text Lines = " << text_data.size()<< std::endl;  
    
    if (text_data.size() > 0)
    {
      QString out_file_name =
          "E:\\KAUST1\\projects\\misc\\excel_arabic\\test\\output\\pdf_miner\\pdf_miner_test_case.xls";
      WriteExcel(out_file_name, text_data);
    }
  } else
  {
    std::cout << "Not able to open the file = " << in_file_name.toStdString() << std::endl;
  }
}


void ParseXPdfText()
{
  QString in_file_name =
      "E:\\KAUST1\\projects\\misc\\excel_arabic\\test\\output\\x_pdf\\xpdf_test_case.txt";
  QString out_file_name =
      "E:\\KAUST1\\projects\\misc\\excel_arabic\\test\\output\\x_pdf\\xpdf_test_case_new.xls";

  QFile inputFile(in_file_name);
  QStringList text_data;
  if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    std::cout << "Able to open the file for reading." << std::endl;
    QTextStream in(&inputFile);
    in.setCodec("UTF-8"); // change the file codec to UTF-8.
    int counter = 0;
    QString line_data;
    while (!in.atEnd())
    {
      QString line = in.readLine();
      if (line.size() > 0)
      {
        text_data.push_back(line);
        counter++;
        if (counter  == 7)
        {
          line_data = line;
        }        
      }  
    } 
      
    WriteExcel(out_file_name, text_data);
  } else
  {
    std::cout << "Not able to open the file =" << in_file_name.toStdString()
      << std::endl;
  }

}

void WriteExcel(QString file_name, QStringList data)
{
  std::cout << "Number of Text Lines = " << data.size() << std::endl;
  
  QAxObject* excel = new QAxObject("Excel.Application", NULL);

  //workbooks pointer
  QAxObject* workbooks = excel->querySubObject("WorkBooks");
  workbooks->dynamicCall("Add"); // Add new workbook
  QAxObject* workbook = excel->querySubObject("ActiveWorkBook");
  QAxObject* sheets = workbook->querySubObject("WorkSheets");

  QAxObject * cell;
  int count = sheets->dynamicCall("Count()").toInt();
  bool isEmpty = true;

  for (int k = 1; k <= 1; k++)
  {
    //sheet pointer
    QAxObject* sheet = sheets->querySubObject("Item( int )", k);    
    for (int i = 1; i <= data.size(); i++)
    {
      for (int j = 1; j<2; j++)      {

        QString text = data.at(i-1); // value you want to export        

        //get cell                
        QAxObject* cell = sheet->querySubObject("Cells( int, int )", i, j);
        //set your value to the cell of ith row n jth column 
        cell->dynamicCall("SetValue(QString)", text);
        // if you wish check your value set correctly or not by retrieving and printing it
        QVariant value = cell->dynamicCall("Value()");

      }
    }
  }
  
  workbook->dynamicCall("SaveAs(QString&)", file_name);
  workbook->dynamicCall("Close (Boolean)", false);  
  excel->dynamicCall("Quit()");
  std::cout << "Written to Excel Sheet." << std::endl;  
}

#if 0

QString file_name =
"E:\\KAUST1\\projects\\misc\\excel_arabic\\test\\xpdf_test_case_1.txt";
QFile inputFile(file_name);
QStringList text_data;
if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
{
  QTextStream in(&inputFile);
  in.setCodec("UTF-8"); // change the file codec to UTF-8.
  text_data.push_back("  ");
  int counter = 0;
  QString start;
  QString end;
  while (!in.atEnd())
  {
    QString line = in.readLine();
    if (line.size() > 0)
    {
      text_data.push_back(line);
      counter++;
      if (counter == 5)
      {
        start = line;
      }

      if (counter == 15)
      {
        end = line;
      }
    }

  }

  QStringList words = start.split(" ");
  std::cout << "Size of the words = " << words.size() << std::endl;
  QStringList clean_words;

  for (unsigned int i = 0; i < words.size(); i++)
  {
    if (words.at(i).size() > 0)
      clean_words.push_back(words.at(i));
  }
  std::cout << "Size of the clean words = " << clean_words.size() << std::endl;
  /*QMessageBox msg_box;
  msg_box.setText(msg);
  msg_box.exec();*/
#endif



//PATH = $(QTDIR)\bin % 3b"$(QTDIR)\bin%3b$(PATH)

// E:\KAUST1\projects\misc\excel_arabic\test\testCase.pdf
/*
PATH = $(QTDIR)\bin % 3b"$(QTDIR)\bin%3b$(PATH)%3bE:\dev\libssh-0.7.5\build\bin%3bE:\dev\zlib-1.2.11\binary%3bE:\dev\curl-7.56.1\third-party\bin\release_x64%3bE:\dev\openssl-0.9.8k_X64\bin
*/