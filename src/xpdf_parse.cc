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
  GenerateBlockLength(entire_data);
  Blocks blocks = GetBlocks(entire_data);
}

void XPdfParse::Generate(const QString file_name)
{
  PreDirCheck();

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

  GenerateBlockLength(entire_data);

  /* In the case of Residential, there are some hardles, which needs to be
     removed. */
  if (block_length_ == RESIDENTIAL_BLOCK_LENGTH)
    entire_data = RemoveHardles(entire_data);

  /* In the case of Industry, there are some hardles, which needs to be
      removed.*/
  /*if (block_length_ == INDUSTRIAL_BLOCK_LENGTH)
    entire_data = RemoveIndustryHardles(entire_data);
  */
  /*if (file_name.size() > 0)
  {
    WriteExcel(file_name, entire_data);
  }*/
  Blocks blocks = GetBlocks(entire_data);
}

void XPdfParse::GeneratePdftoExcel(const QString file_name)
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

  QString temp_dir = base_dir + QDir::separator() + "temp";
  temp_dir = QDir::toNativeSeparators(temp_dir);

  QString tools_dir = base_dir + QDir::separator() +  "tools";
  QString pdf_txt_exe = QDir::toNativeSeparators(tools_dir) + QDir::separator()
      + "pdftotext.exe";
 
  //pdf_txt_exe = QDir(QDir::toNativeSeparators(pdf_txt_exe)).absolutePath(); 

  QString pdf_to_file = temp_dir + QDir::separator() + "data.txt";
  pdf_to_file = QDir::toNativeSeparators(pdf_to_file);
  
  GenerateTextFile(pdf_txt_exe, in_file_name_, pdf_to_file);

  std::vector<QStringList> data_rows;

  QFile inpu_file(pdf_to_file);
  if (inpu_file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    std::cout << "Able to open the file for reading." << std::endl;
    QTextStream in(&inpu_file);
    in.setCodec("UTF-8"); // change the file codec to UTF-8.
    int counter = 0;
    QString start = QStringLiteral(START_BLOCK_WORD);
    QString end = QStringLiteral(END_BLOCK_WORD);    
    bool flag = false;
    while (!in.atEnd())
    {
      QString line = in.readLine();
      if (line.size() > 0)
      {
        counter++;
        QStringList words;

        LineSplit(line, words);
        int words_len = words.size();

        if (words_len > START_BLOCK_INDEX)
        {
          QString word = words.at(0);
          //Remove Extra Quote at the end
          word = word.mid(1, (word.size() - 2));
          if (word == start)
          {            
            flag = true;
            //std::cout << "Start Word Line Index = " << counter << std::endl;
          }
        }

        if ((words_len > END_BLOCK_INDEX) &&
          (words.at(END_BLOCK_INDEX) == end))
        {
          data_rows.push_back(words);
          flag = false;
          //std::cout << "End Word Line Index = " << counter << std::endl;
        }

        if (flag)
        {
          data_rows.push_back(words);
        }
      }
    }
  }

  WriteExcel(file_name, data_rows);
  // Delete the temporary directory and its contents
  //DeleteDir(temp_dir);    
}

unsigned int XPdfParse::GetBlockLength()
{
  return block_length_;
}

Blocks XPdfParse::GetBlocks()
{
  return data_blocks_;
}

void XPdfParse::GenerateBlocks(const QString file_name)
{
  QFile inpu_file(in_file_name_);
  if (inpu_file.open(QIODevice::ReadOnly | QIODevice::Text))
  {    
    std::cout << "Able to open the file for reading." << std::endl;
    QTextStream in(&inpu_file);
    in.setCodec("UTF-8"); // change the file codec to UTF-8.
    int counter = 0;
    QString start = QStringLiteral(START_BLOCK_WORD);
    QString end = QStringLiteral(END_BLOCK_WORD);
    PBlocks blocks;    
    Block* block;
    bool flag = false;
    while (!in.atEnd())
    {
      QString line = in.readLine();
      if (line.size() > 0)
      {
        counter++;
        QStringList words;

        LineSplit(line, words);
        int words_len = words.size();
        
        if (words_len > START_BLOCK_INDEX)
        {
          QString word = words.at(0);
          //Remove Extra Quote at the end
          word = word.mid(1, (word.size() - 2));
          if (word == start)
          {
            block = new Block();
            flag = true;
            //std::cout << "Start Word Line Index = " << counter << std::endl;
          }
        }

        if ((words_len > END_BLOCK_INDEX) &&
            (words.at(END_BLOCK_INDEX) == end))
        {         
          block->push_back(words);
          blocks.push_back(block);
          flag = false;
          //std::cout << "End Word Line Index = " << counter << std::endl;
        }

        if (flag)
        {
          block->push_back(words);
        }
      }
    }
    
    std::cout << "Number of Blocks = " << blocks.size() << std::endl;      

    std::vector<QStringList> rows;

    std::vector<QStringList> header = GetHeader();
    rows.push_back(header.at(0));
    rows.push_back(header.at(1));
    for (unsigned int counter = 0; counter < blocks.size(); counter++)
    {
      Block* block = blocks.at(counter);
      QStringList row_words;      
      for (unsigned int row = 0; row < block->size(); row++)
      {
        QStringList words = block->at(row);

        //Row 2, fields 2 and 3 and string position 8 and 7.

        if (row == 2)
        {
          Positions src_pos = {2, 3};
          Positions dest_pos = {8, 7};
          CopyWords(words, row_words, src_pos, dest_pos);
        }

        if (row == 3)
        {
          Positions src_pos = {5, 6, 7};
          Positions dest_pos = {1, 2, 0};
          CopyWords(words, row_words, src_pos, dest_pos);
        }

        if (row == 4)
        {
          Positions src_pos = {6, 7};
          Positions dest_pos = {3, 4};
          CopyWords(words, row_words, src_pos, dest_pos);
        }

        if (row == 7)
        {
          Positions src_pos = {1};
          Positions dest_pos = {5};
          CopyWords(words, row_words, src_pos, dest_pos);
        }

        if (row == 10)
        {
          Positions src_pos = {12};
          Positions dest_pos = {6};
          CopyWords(words, row_words, src_pos, dest_pos);
        }
      }
      QStringList order_words;
      
      order_words.push_back(row_words.at(4));
      order_words.push_back(row_words.at(2));
      order_words.push_back(row_words.at(3));
      order_words.push_back(row_words.at(5));
      order_words.push_back(row_words.at(6));
      order_words.push_back(row_words.at(7));
      order_words.push_back(row_words.at(8));
      order_words.push_back(row_words.at(0));
      order_words.push_back(row_words.at(1));

      rows.push_back(order_words);
    }

    std::cout << "Number of final rows = " << rows.size() << std::endl;   
    WriteExcel(file_name, rows);
  } else
  {
    std::cout << "Input file, " << file_name.toStdString() <<
      " cannot be opened." << std::endl;
  }
}

void XPdfParse::GenerateExcel(const QString file_name)
{
  QFile inpu_file(in_file_name_);  
  if (inpu_file.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    QStringList text_data;
    std::cout << "Able to open the file for reading." << std::endl;
    QTextStream in(&inpu_file);
    in.setCodec("UTF-8"); // change the file codec to UTF-8.
    int counter = 0;
    while (!in.atEnd())
    {
      QString line = in.readLine();
      if (line.size() > 0)
      {
        counter++;
        text_data.push_back(line);
      }
    }
    //Remove the last element since it contains the junk.
    text_data.removeLast();
    std::cout << "Number of the non empty lines: " << counter << std::endl;
    WriteExcel(file_name, text_data);    
  } else
  {
    std::cout << "Input file, " << file_name.toStdString() <<
        " cannot be opened." << std::endl;
  }
}

void XPdfParse::WriteExcel(const QString file_name, QStringList data)
{
  QAxObject* excel = new QAxObject("Excel.Application", this);

  //workbooks pointer
  QAxObject* workbooks = excel->querySubObject("WorkBooks");
  workbooks->dynamicCall("Add"); // Add new workbook
  QAxObject* workbook = excel->querySubObject("ActiveWorkBook");
  QAxObject* sheets = workbook->querySubObject("WorkSheets");

  QAxObject * cell;
  //int count = sheets->dynamicCall("Count()").toInt();  

  //Write only one sheet
  //The work sheet row and column starts from 1.
  for (int k = 1; k <= 1; k++)
  {
    //sheet pointer
    QAxObject* sheet = sheets->querySubObject("Item(int)", k);
    for (int row = 1; row <= data.size(); row++)
    {
      for (int col = 1; col < 2; col++)
      {
        QString text = data.at(row - 1); // value you want to export        

        //get cell                
        QAxObject* cell = sheet->querySubObject("Cells(int, int)", row, col);
        //set your value to the cell of row and column 
        cell->dynamicCall("SetValue(QString)", text);
      }
    }
  }

  workbook->dynamicCall("SaveAs(QString&)", file_name);
  workbook->dynamicCall("Close (Boolean)", false);
  excel->dynamicCall("Quit()");
  std::cout << "Saved the data in the " << file_name.toStdString() << "."
    << std::endl;
}

void XPdfParse::WriteExcel(const QString file_name,
    std::vector<QStringList> data)
{  
  QAxObject* excel = new QAxObject("Excel.Application", this);

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
    QAxObject* sheet = sheets->querySubObject("Item( int )", k);    
    for (int row = 1; row <= data.size(); row++)
    {
      QStringList data_rows = data.at(row - 1);
      for (int col = 1; col <= data_rows.size(); col++)      {

        QString text = data_rows.at(col - 1); 
        QAxObject* cell = sheet->querySubObject("Cells( int, int )", row, col);
        cell->dynamicCall("SetValue(QString)", text);
        QVariant value = cell->dynamicCall("Value()");
      }
    }
  }

  workbook->dynamicCall("SaveAs(QString&)", file_name);
  workbook->dynamicCall("Close (Boolean)", false);
  excel->dynamicCall("Quit()");
  
  std::cout << "Saved the data in the " << file_name.toStdString() << "."
    << std::endl; 
}

void XPdfParse::LineSplit(QString data, QStringList& words)
{
  //Remove all white spaces at the begin and at the end.
  data = data.trimmed();

  //The string contains quote at the begining and at the end. Remove it.
  //data = data.mid(1, (data.size() - 2));

  //split data with sapces.
  QStringList data_words = data.split(" ");

  //Lots of white spaces in the data words and remove them.
  for (unsigned int counter = 0; counter < data_words.size(); counter++)
  {
    if (data_words.at(counter).size() > 0)
      words.push_back(data_words.at(counter).trimmed());
  }
}

void XPdfParse::CopyWords(QStringList src, QStringList& dest, Positions src_pos,
  Positions dest_pos)
{
  for (unsigned int counter = 0; counter < src_pos.size(); counter++)
  {
    //dest.insert(dest_pos.at(counter), src.at(src_pos.at(counter)));
    dest.push_back(src.at(src_pos.at(counter)));
  }  
}

std::vector<QStringList> XPdfParse::GetHeader()
{
  std::vector<QStringList> header;
  QStringList row_1;
  row_1 << "Subscribtion Number"
        << "Active Power Consumption"
        << "Active power Consumption Cost (SAR)"
        << "Reactive Power Consumption"
        << "Reactive Power Consumption Cost (SAR)"
        << "Settlement"
        << "Power Factor"
        << "Reading From"
        << "Reading To";
  header.push_back(row_1);

  QStringList row_2;
  row_2 << QStringLiteral("الاشتراك")
        << QStringLiteral("استهلاك الطاقه الفاعله")
        << QStringLiteral("قيمة استهلاك الطاقه الفاعله")
        << QStringLiteral("استهلاك الطاقه الغير فاعله")
        << QStringLiteral("قيمة استهلاك الطاقة الغير فاعلة")
        << QStringLiteral("التسويات")
        << QStringLiteral("معامل القدرة")
        << QStringLiteral("القراءة السابقة")
        << QStringLiteral("القراءه الحالية");
  header.push_back(row_2);
  return header;
}

bool XPdfParse::DeleteDir(QString dir_name)
{
  bool retval = true;
  QDir dir(dir_name);
  
  if (dir.exists(dir_name))
  {
    Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot
      | QDir::System | QDir::Hidden | QDir::AllDirs | QDir::Files,
      QDir::DirsFirst))
    {
      if (info.isDir())
      {
        retval = DeleteDir(info.absoluteFilePath());
      } else
      {
        retval = QFile::remove(info.absoluteFilePath());
      }

      if (!retval)
      {
        return retval;
      }
    }
    retval = dir.rmdir(dir_name);
  }

  return retval;
}

void XPdfParse::GenerateTextFile(QString exe_name, QString input_file,
    QString output_file)
{
  QStringList arguments;
  QString argument = "-layout";
  arguments.push_back(argument);

  argument = "-table";
  arguments.push_back(argument);

  argument = "-enc";
  arguments.push_back(argument);
  //the following is done because enc exepcts a string parameter
  //which can be achieved by defining the QStringLiteral
  argument = QStringLiteral("UTF-8");
  arguments.push_back(argument);

  arguments.push_back(input_file);
  arguments.push_back(output_file);

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
      /*int value = Utilities::ConvertEnglish(words.at(0)).toInt();
      if (value == 0)*/
      continue;
    }
    data_out.push_back(words);
  }
  return data_out;
}

void XPdfParse::GenerateBlockLength(Block data_in)
{
  QString start = QStringLiteral(START_BLOCK_WORD);

  block_length_ = 0;

  for (int counter = 0; counter < data_in.size(); counter++)
  {
    QStringList words = data_in.at(counter);
    if (words.at(0) == start)
    {
      if (counter > 0)
      {
        block_length_ = counter;
        break;
      }
    }
  }
  std::cout << "Block Length = " << block_length_ << std::endl;
}

Block XPdfParse::RemoveHardles(Block data_in)
{
  Block data_out;
  QString start = QStringLiteral(START_BLOCK_WORD);
  for (unsigned int counter = 0; counter < data_in.size(); )
  {
    QStringList words = data_in.at(counter);

    if (words.size() == HARDLES_WORDS_SIZE)
    {
      if ((words.at(HARDLES_WORD_1_POSITION) == start) &&
          (words.at(HARDLES_WORD_1_POSITION) == start))
      {
        data_out.pop_back();
        std::cout << "Abnormal, Remove the data." << std::endl;
        counter = counter + HARDLES_NO_LINES;
        continue;
      }
    }
    data_out.push_back(words);
    counter++;
  }
  return data_out;
}

Block XPdfParse::RemoveIndustryHardles(Block data_in)
{
  Block data_out;
  
  for (unsigned int counter = 0; counter < data_in.size(); counter++)
  {
    QStringList words = data_in.at(counter);
    if (words.size() == INDUSTRY_HARDLES_WORDS_SIZE)
    {
      int value = 
          Utilities::ConvertEnglish(words.at      (INDUSTRY_HARDLES_WORD_POSITION)).toInt();
      if (value == INDUSTRY_HARDLES_VALUE) 
      {        
        std::cout << "Don't add that line." << std::endl;        
        continue;
      }
    }
    data_out.push_back(words);
  }
  return data_out;

}

Blocks XPdfParse::GetBlocks(Block data_in)
{ 
  /*data_blocks_.clear();
    
  for (int counter = 0; counter < data_in.size();)
  {
    Block block;
    for (int index = 0; index < block_length_; index++)
    {
      block.push_back(data_in.at(counter + index));
    }
    data_blocks_.push_back(block);
    counter = counter + block_length_;
    if ((counter + block_length_) > data_in.size())
      break;
  }
  return data_blocks_;*/

  QString start = QStringLiteral(START_BLOCK_WORD);  

  PBlocks pblocks;
  Block* pblock = new Block();

  for (int counter = 0; counter < data_in.size(); counter++)
  {
    QStringList words = data_in.at(counter);  
    int words_len = words.size();

    if (words_len > START_BLOCK_INDEX)
    {
      QString word = words.at(0);    
      if (word == start)
      {
        if (pblock->size() > 0)
        {
          pblocks.push_back(pblock);        
        }
        pblock = new Block();
      }
      pblock->push_back(words);
    }    
  }

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


#if 0
if (file_name.size() > 0)
{
  QAxObject* excel = new QAxObject("Excel.Application", 0);

  QAxObject* workbooks = excel->querySubObject("Workbooks");
  /*(QAxObject* workbook = workbooks->querySubObject("Open(const QString&)",
  file_name);*/
  workbooks->dynamicCall("Add"); // Add new workbook
  QAxObject* workbook = excel->querySubObject("ActiveWorkBook");
  QAxObject* sheets = workbook->querySubObject("Worksheets");
  int count = sheets->dynamicCall("Count()").toInt();

  // Need only first sheet.
  int start_row = 1;

  for (int k = 1; k <= 1; k++)
  {
    //sheet pointer
    QAxObject* sheet = sheets->querySubObject("Item(int)", k);

    for (int row = 1; row < header.size(); row++, start_row++)
    {
      QStringList row_data = header.at(row - 1); // value you want to export 
      for (int col = 1; col <= row_data.size(); col++)
      {
        QString text = row_data.at(col - 1);
        //get cell                
        QAxObject* cell = sheet->querySubObject("Cells(int, int)", row, col);
        cell->setProperty("SetValue(QString)", text);
      }
    }

    for (int row = 0; row < data.size(); row++)
    {
      QStringList row_data = data.at(row); // value you want to export 
      for (int col = 1; col <= row_data.size(); col++)
      {
        QString text = row_data.at(col - 1);
        //get cell                
        QAxObject* cell = sheet->querySubObject("Cells(int, int)",
          (start_row + row), col);
        //set your value to the cell of row and column 
        //cell->dynamicCall("SetValue(QString)", text);
        cell->setProperty("SetValue(QString)", text);

        QVariant value = cell->dynamicCall("Value()");
      }
    }
  }

  workbook->dynamicCall("SaveAs(QString&)", file_name);
  workbook->dynamicCall("Close (Boolean)", false);
  //excel->setProperty("Visible", true);
  //excel->dynamicCall("Save()");
  excel->dynamicCall("Quit()");
  delete excel;

  std::cout << "Saved the excel sheet." << std::endl;
}
#endif

/*

*/