#include "arabic_translate.h"

#include <iostream>
#include <algorithm>

#include <QtCore/QFile>

#include <QtGui/QResizeEvent>

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QMessageBox>
#include <QtWidgets\QHeaderView>
#include <QtCore\QTextStream>
#include <QtCore\QElapsedTimer>

#include <ActiveQt/QAxWidget>
#include <ActiveQt/QAxObject>

#include "../xpdf_parse.h"
#include "../parse_data.h"

#include "csv_write.h"
#include "../utilities.h"

ArabicTranslate::ArabicTranslate(QWidget *parent)
  : QMainWindow(parent)
{
  ui_.setupUi(this);
  InitUi();
  Init();  
  ConnectSignals();
}

ArabicTranslate::~ArabicTranslate()
{
  
}

void ArabicTranslate::FileOpen()
{
  std::cout << "File Open:File Open Triggered." << std::endl;
  QString current_dir = QDir::currentPath();
  QString pdf_file_name = QFileDialog::getOpenFileName(this,
      tr("Open PDF File"),
      current_dir,
      tr("PDF File (*.pdf)"));
  std::cout << "Opened File Name = " << pdf_file_name.toStdString()
      << std::endl;

  unsigned int year = ui_.year_box->currentText().toInt();
  unsigned int month = ui_.month_box->currentIndex();

  if (year < 2018)
  {
    Utilities::SetVatType(Utilities::VatTypes::WITH_OUT);
  } else if ((year == 2018) && ((month + 1) == 1))
  {
    Utilities::SetVatType(Utilities::VatTypes::PARTIAL);
  } else
  {
    Utilities::SetVatType(Utilities::VatTypes::WITH);
  } 

  unsigned int file_type = ui_.file_type->currentIndex();
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

  if (pdf_file_name.size() > 0)
  {
    QElapsedTimer exec_timer;
    exec_timer.start();
    XPdfParse xpdf_parse(pdf_file_name);
    xpdf_parse.Parse();    
    Blocks data = xpdf_parse.GetBlocks();    
    
    ParseData parse_data;
    parse_data.FormData(data);
    std::vector<unsigned int> types = ParseData::GetTypes();
    std::cout << "No. of Types in the input file = " << types.size()
      << std::endl;

    quint64 time_spent = exec_timer.elapsed();
    std::cout << "Time Spent for convertion and Parsing = " << time_spent <<
        " milli seconds, seconds = " << (time_spent * 0.001) << std::endl;

    if (types.size() > 0)
    {      
      is_file_save_ = true;
      data_table_->setVisible(true);
      UpdateDataTable();
    }
  }  
  this->update();
}

void ArabicTranslate::FileSaveCsv()
{
  std::cout << "File Save as CSV Triggered." << std::endl;
  QString current_dir = QDir::currentPath();
  QString file_name = QFileDialog::getSaveFileName(this,
      tr("Save CSV File"),
      current_dir,
      tr("CSV Files (*.csv)"));
  std::cout << "Saved File Name = " << file_name.toStdString() << std::endl;

  if (file_name.size() > 0)
  {
    QElapsedTimer exec_timer;
    exec_timer.start();
    CsvWrite csv_write(file_name);
    std::vector<unsigned int> types = ParseData::GetTypes();
    csv_write.Write(types.size());
    quint64 time_spent = exec_timer.elapsed();
    std::cout << "Time Spent for Writing data in CSV file = " << time_spent <<
        " milli seconds, seconds = " << (time_spent * 0.001) << std::endl;
  }
  this->update();
}

void ArabicTranslate::FileExit()
{
  this->close();
  this->update();
}

void ArabicTranslate::paintEvent(QPaintEvent *event)
{ 
  ui_.file_save_excel->setEnabled(false);
  ui_.file_save_csv->setEnabled(is_file_save_);   
}

void ArabicTranslate::resizeEvent(QResizeEvent* event)
{
  QSize size = event->size();
  this->resize(size);
  Resize();
}

void ArabicTranslate::Init()
{
  //Get the current directory
  QString cur_dir = QDir::toNativeSeparators(QDir::currentPath());
  std::cout << "Current Directory is " << cur_dir.toStdString() << std::endl;

  QFile style_sheet_file(QStringLiteral(":/ArabicTranslate/style_sheet_file"));  
  if (style_sheet_file.open(QFile::ReadOnly))
  {
    //std::cout << "Applied Style Sheet." << std::endl;
    QString data = QString::fromLatin1(style_sheet_file.readAll());
    qApp->setStyleSheet(data);
    style_sheet_file.close();
  }  
     
  QDesktopWidget *desktop_widget = QApplication::desktop();
  QRect widget_geometry = desktop_widget->availableGeometry(
      desktop_widget->primaryScreen());
  this->resize((widget_geometry.width() - 500),
      (widget_geometry.height() - 200));
}

void ArabicTranslate::InitUi()
{     
  message_box_ = new QMessageBox(this);
  message_box_->setVisible(false);
  message_box_->setStandardButtons(0);

  QString window_title = "Arabic Translate  ";
  window_title = window_title + QString(VERSION);
  this->setWindowTitle(window_title);

  InitDataTable();
  
  is_file_save_ = false;
}

void ArabicTranslate::ConnectSignals()
{
  connect(ui_.file_open, SIGNAL(triggered()), this, SLOT(FileOpen()));  
  connect(ui_.file_save_csv, SIGNAL(triggered()), this, SLOT(FileSaveCsv()));
  connect(ui_.file_exit, SIGNAL(triggered()), this, SLOT(FileExit()));  
}

void ArabicTranslate::Resize()
{
  QRect widget_geometry = ui_.menu_bar->geometry();
  QSize toolbar_size = ui_.tool_bar->minimumSize();
  QSize statusbar_size = ui_.status_bar->minimumSize();

  int view_width = this->width();
  int view_height = this->height() - (widget_geometry.height()
    + toolbar_size.height() + statusbar_size.height());

  widget_geometry = ui_.control_group->geometry();
  widget_geometry.setHeight(view_height - 10);
  ui_.control_group->setGeometry(widget_geometry);
  ui_.control_group->update();

  widget_geometry = ui_.data_view->geometry();
  widget_geometry.setWidth(view_width - widget_geometry.x() - 5);
  widget_geometry.setHeight(view_height - 10);
  ui_.data_view->setGeometry(widget_geometry);
  ui_.data_view->update();  

  data_table_->setGeometry(0, 0, 400, ui_.data_view->height() - 50);
  data_table_->update();

  this->update();
}

void ArabicTranslate::InitDataTable()
{
  data_table_ = new QTableWidget(ui_.data_view);
  data_table_->setColumnCount(2);
  QStringList header;
  header << "Type";
  header << "Subscription \n Number";

  data_table_->setHorizontalHeaderLabels(header);
  QHeaderView* header_view = data_table_->horizontalHeader();

  header_view->setSectionResizeMode(QHeaderView::Stretch);

  data_table_->setVisible(false);
  data_table_->setGeometry(0, 0, 400, ui_.data_view->height() - 50);
  data_table_->update();  
}

void ArabicTranslate::UpdateDataTable()
{
  std::vector<AccountDetails> data;
  data = ParseData::GetDataInfo();

  data_table_->setRowCount(data.size());
    
  for (unsigned int counter = 0; counter < data.size(); counter++)
  {
    AccountDetails acc_details = data.at(counter);
        
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText(acc_details.type_);
    data_table_->setItem(counter, 0, item);

    item = new QTableWidgetItem();
    item->setText(acc_details.subscription_num_);
    data_table_->setItem(counter, 1, item);    
  }
  
  data_table_->update();
}
