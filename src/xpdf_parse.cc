#include "xpdf_parse.h"

#include <QtCore\QDir>
#include <QtCore\QString>
#include <QtCore\QTextStream>
#include <QtCore\QByteArray>
#include <QtCore\QTextCodec>
#include <QtCore\QProcess>

#include <ActiveQt/QAxWidget>
#include <ActiveQt/QAxObject>

#include "utilities.h"

XPdfParse::XPdfParse(const QString file_name)
{
  in_file_name_ = file_name;
}

XPdfParse::~XPdfParse()
{

}

void XPdfParse::Parse()
{
  PreDirCheck();
  total_invoices_ = 0;
  QString cur_dir = QDir::currentPath();
  QString base_dir = cur_dir + QDir::separator() + "..";
  QString temp_dir = base_dir + QDir::separator() + "temp";
  QString pdf_to_file = temp_dir + QDir::separator() + "data.txt";
  pdf_to_file = QDir::toNativeSeparators(pdf_to_file);

  PdftoText(pdf_to_file);
  QStringList txt_data = ReadTextFile(pdf_to_file);
  std::cout << "Size of text data, initial  = " << txt_data.size()
      << std::endl;

  txt_data = RemoveWhiteSpaces(txt_data);
  std::cout << "Size of text data, after white space removal = "
      << txt_data.size() << std::endl;

  txt_data = RemoveHeaderFooter(txt_data);
  std::cout << "Size of text data, after header and footer removal = "
      << txt_data.size() << std::endl;
  
  Block entire_data = ConvertData(txt_data);

  entire_data = RemoveSingleValueZero(entire_data);
  std::cout << "Size of text data, after Single 0 value removal = "
        << entire_data.size() << std::endl;
  
  Blocks blocks = GetBlocks(entire_data);
}

Blocks XPdfParse::GetBlocks()
{
  return data_blocks_;
}

unsigned int XPdfParse::GetTotalInvoices()
{
  return total_invoices_;
}

void XPdfParse::PrintCommands(QString exe_name, QStringList arguments)
{
  std::cout << exe_name.toStdString() << " ";
  foreach(const QString &argument, arguments)
  {
    std::cout << argument.toStdString() << " ";
  }
  std::cout << std::endl;
}

void XPdfParse::PreDirCheck()
{
  QString cur_dir = QDir::currentPath();
  QString base_dir = cur_dir + QDir::separator() + "..";
  base_dir = QDir(QDir::toNativeSeparators(base_dir)).absolutePath();

  //Create a temp directory 
  bool ret = QDir(base_dir).mkdir("temp");

  if (ret)
  {
    std::cout << "Able to create a temp directory." << std::endl;
  }
}

void XPdfParse::PdftoText(QString out_file)
{
  QString cur_dir = QDir::currentPath();
  QString base_dir = cur_dir + QDir::separator() + "..";
 
  QString tools_dir = base_dir + QDir::separator() + "tools";
  QString exe_name = tools_dir + QDir::separator() + "pdftotext.exe";
  exe_name = QDir::toNativeSeparators(exe_name);

  QStringList arguments;
  QString argument = "-layout";
  arguments.push_back(argument);

  argument = "-table";
  arguments.push_back(argument);

  /* The first page conains meta data, which is not required.*/
  argument = "-f";
  arguments.push_back(argument);
  argument = QString::number(2);
  arguments.push_back(argument);

  /*argument = "-nopgbrk";
  arguments.push_back(argument);*/
  
  argument = "-enc";
  arguments.push_back(argument);
  
  //the following is done because enc exepcts a string parameter
  //which can be achieved by defining the QStringLiteral
  argument = QStringLiteral("UTF-8");
  arguments.push_back(argument);

  arguments.push_back(in_file_name_);
  arguments.push_back(out_file);

  PrintCommands(exe_name, arguments);
  QProcess  process;
  int retval = process.execute(exe_name, arguments);
  if (retval != 0)
  {
    std::cout << "Not able to generated text file is an error =" <<
      retval <<  std::endl;
  }  else
  {
    std::cout << "Generated the PDF to Text file." << std::endl;
  }  
}

QStringList XPdfParse::ReadTextFile(QString file_name)
{
  QStringList data_out;

  QFile inpu_file(file_name);
  if (inpu_file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    std::cout << "Able to open the file for reading." << std::endl;
    QTextStream in(&inpu_file);
    in.setCodec("UTF-8"); // change the file codec to UTF-8.
   
    while (!in.atEnd())
    {
      QString line = in.readLine();     
      data_out.push_back(line);      
    }
    inpu_file.close();
  }

  return data_out;
}

QStringList XPdfParse::RemoveWhiteSpaces(QStringList data_in)
{
  QStringList data_out;

  for (unsigned int counter = 0; counter < data_in.size(); counter++)
  {
    QString line = data_in.at(counter);
    if (line.size() > 0)
    {
      data_out.push_back(line);
    }
  }
  return data_out;
}

QStringList XPdfParse::RemoveHeaderFooter(QStringList data_in)
{
  QStringList data_out;
  /* Each page starts with page break '\f' (=0x12) except the first page. */
  /* Footer of the previous needs to be removed. (only one line) */
  /* First 4 lines in each page has to be removed.*/
  
  for (unsigned int counter = 4; counter < data_in.size(); counter++)
  {
    QString line = data_in.at(counter);
    if (line.at(0) == '\f')
    {
      data_out.removeLast();
      counter = counter + 3;
    } else {
      data_out.push_back(line);
    }
  }

  return data_out;
}

Block XPdfParse::ConvertData(QStringList data_in)
{
  Block data_out;
    
  for (unsigned int counter = 0; counter < data_in.size(); counter++)
  {
    QString line = data_in.at(counter);
    line = line.trimmed();
    QChar remove_char = 8235; //Start Double Quote    
    line.remove(remove_char, Qt::CaseInsensitive);
    remove_char = 8236; // End Double Quote
    line.remove(remove_char, Qt::CaseInsensitive);
    remove_char = 8234; // Another Double Quote
    line.remove(remove_char, Qt::CaseInsensitive);   

    QStringList words = line.split(" ", QString::SkipEmptyParts);

    data_out.push_back(words);
  }
  return data_out;  
}

Block XPdfParse::RemoveSingleValueZero(Block data_in)
{
  //Skip the line with zero value as there is no value for it.
  Block data_out;
  for (unsigned int counter = 0; counter < data_in.size(); counter++)
  {
    QStringList words = data_in.at(counter);
  
    if (words.size() == 1)
    {     
      continue;
    }
    data_out.push_back(words);
  }
  return data_out;
}

Blocks XPdfParse::GetBlocks(Block data_in)
{ 
  QString start = QStringLiteral(START_BLOCK_WORD);
  QString start_two = QStringLiteral(START_BLOCK_WORD_TWO);
  
  std::vector<Block*> pblocks;
  Block* pblock = new Block();

  for (int counter = 0; counter < data_in.size(); counter++)
  {
    QStringList words = data_in.at(counter);  
    int words_len = words.size();

    if (words_len > START_BLOCK_INDEX)
    {
      QString word_one = words.at(0);
      QString word_two = words.at(1);
      if ((word_one == start) && (word_two == start_two))
      {
        if (pblock->size() > 0)
        {
          pblocks.push_back(pblock);        
        }
        pblock = new Block();
      } else if (word_one == start) 
      {
        /* Some of the files contains extra line which is not intended.
        Remove that line.  */
        continue;
      }
      pblock->push_back(words);
    }    
  }

  QString total = QStringLiteral(TOTAL_INNOVICES);

  // For the last block, extra data, remove the same.
  if (pblock->size() > 0)
  {
    start = QStringLiteral(LAST_BLOCK_WORD);
    
    for (unsigned int counter = 0; counter < pblock->size(); counter++)
    {
      QStringList words = pblock->at(counter);
      if (words.at(0) == start)
      {
        for (unsigned int index = pblock->size(); index > counter; index--)
        {
          QStringList total_count = pblock->at(index - 1);
          if (total_count.contains(total))
          {
            //Total count
            total_invoices_ = 
                Utilities::ConvertEnglish(total_count.at(0)).toInt();
            std::cout << "Total Count from PDF = " << total_invoices_ <<
                std::endl;
          }
          pblock->pop_back();
        }
        pblocks.push_back(pblock);
        break;
      }
    }         
  }

  data_blocks_.clear();

  for (unsigned int counter = 0; counter < pblocks.size(); counter++)
  {
    Block* pblock = pblocks.at(counter);
    Block block;
    for (unsigned int index = 0; index < pblock->size(); index++)
    {
      block.push_back(pblock->at(index));
    }
    data_blocks_.push_back(block);
  }

  return data_blocks_;
}
