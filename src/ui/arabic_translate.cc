#include "arabic_translate.h"

#include <iostream>
#include <algorithm>

#include <QtCore/QFile>

#include <QtGui/QResizeEvent>

#include <QtWidgets/QFileDialog>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QMessageBox>
#include <QtCore\QTextStream>
#include <QtCore\QElapsedTimer>

#include <ActiveQt/QAxWidget>
#include <ActiveQt/QAxObject>

#include "../xpdf_parse.h"
#include "../industrial_data.h"
#include "../residential_data.h"
#include "../parse_data.h"

#include "excel_write.h"

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
  db_mgr_->CloseDb();
}

void ArabicTranslate::FileOpen()
{
  std::cout << "File Open Triggered." << std::endl;
  QString current_dir = QDir::currentPath();
  QString pdf_file_name = QFileDialog::getOpenFileName(this,
    tr("Open PDF File"),
    current_dir,
    tr("PDF File (*.pdf)"));
  std::cout << "File Name = " << pdf_file_name.toStdString()
    << std::endl;

  if (pdf_file_name.size() > 0)
  {
    QElapsedTimer exec_timer;
    exec_timer.start();
    XPdfParse xpdf_parse(pdf_file_name);
    xpdf_parse.Parse();    
    Blocks data = xpdf_parse.GetBlocks();
    quint64 time_spent = exec_timer.elapsed();
    std::cout << "Time Spent for convertion and Parsing = " << time_spent <<
      " milli seconds, seconds = " << (time_spent * 0.001) << std::endl;

    ParseData parse_data;
    parse_data.FormData(data);
    std::vector<unsigned int> types = ParseData::GetTypes();
    std::cout << "No. of Types in the input file = " << types.size()
      << std::endl;
    
    if (types.size() > 0)
    {
      /* Get the current types if any. If there are then remove first. */
      ui_.combo_box_types->clear();        
      ui_.combo_box_types->update();

      QStringList types_string;
      types_current_index_ = 0;
      for (unsigned int counter = 0; counter < types.size(); counter++)
      {
        types_string << QString::number(types.at(counter));
      }

      if (types.size() > 0)
      {
        types_string << "All";        
        types_current_index_ = types.size();
      }
      ui_.combo_box_types->addItems(types_string);
      ui_.combo_box_types->setCurrentIndex(types_current_index_);
      ui_.combo_box_types->update();
     
      is_file_save_ = true;
    }
  }  
  this->update();
}

void ArabicTranslate::FileSave()
{
  std::cout << "File Save Triggered." << std::endl;
  QString current_dir = QDir::currentPath();
  QString file_name = QFileDialog::getSaveFileName(this,
      tr("Save Excel File"),
      current_dir,
      tr("Excel Files (*.xlsx)"));
  std::cout << "File Name = " << file_name.toStdString() << std::endl;

  if (file_name.size() > 0)
  {
    QElapsedTimer exec_timer;
    exec_timer.start();
    ExcelWrite excel_write(file_name);
    excel_write.Write(types_current_index_);
    quint64 time_spent = exec_timer.elapsed();
    std::cout << "Time Spent for Writing data in Excel = " << time_spent <<
      " milli seconds, seconds = " << (time_spent * 0.001) << std::endl;
  }
  this->update();
}

void ArabicTranslate::FileExit()
{
  this->close();
  this->update();
}

void ArabicTranslate::TypesIndexChanged(int index)
{
  std::cout << "Types current Index = " << index << std::endl;  
  std::vector<unsigned int> types = ParseData::GetTypes();
  if (index < types.size())
  { 
    std::cout << "Selected Type = " << types.at(index) << std::endl;
    data_table_view_->SetType(types.at(index));
  } else
  {
    if (index > 0)
    {
      data_table_view_->SetType(types.at(index - 1), true);
      std::cout << "Selected Type = All" << std::endl;
    }
  }  

  types_current_index_ = index;

  data_table_view_->setVisible(true);
  data_table_view_->update();
  ui_.data_view->update();

  /*ui_.data_base_operations->setVisible(true);
  ui_.data_base_operations->update();
  ui_.db_add->setVisible(true);
  ui_.db_add->update();

  ui_.db_retrieve->setVisible(true);
  ui_.db_retrieve->update();

  ui_.search_num->setVisible(true);
  ui_.search_num->update();*/

  this->update();
}

void ArabicTranslate::DbAdd()
{
  std::cout << "DB Add is pressed." << std::endl;
  QElapsedTimer exec_timer;
  exec_timer.start();
  bool is_db_open = db_mgr_->IsDbOpen();
  if (is_db_open)
  {
    std::cout << "Data Base is opened." << std::endl;
    //Check whether Master table exists, if not create the same.
    QString table_name = MAIN_TABLE_NAME;
    bool retval = db_mgr_->IsTableExists(table_name);
    if (!retval)
    {
      db_mgr_->CreateMainTable(table_name);
    }

    std::vector<AccountDetails> data;
    std::vector<unsigned int> types = ParseData::GetTypes();
    if (types_current_index_ < types.size())
    {
      data = ParseData::GetDataInfo(types.at(types_current_index_));
    } else
    {
      data = ParseData::GetDataInfo();
    }

    for (unsigned int index = 0; index < data.size(); index++)
    {
      AccountDetails acc_details = data.at(index);
      retval = db_mgr_->IsInMainTable(table_name,
          acc_details.subscription_num_);
      if (!retval)
      {
        db_mgr_->InsertMainData(table_name, acc_details);
      }

      QString sub_table_name = SUB_TABLE_START +
          QString::number(acc_details.subscription_num_);
      //Check whether Sub Table exists, if Not Create it
      retval = db_mgr_->IsTableExists(sub_table_name);
      if (!retval)
      {
        db_mgr_->CreateSubTable(sub_table_name);
      }

      retval = db_mgr_->IsInSubTable(sub_table_name, acc_details.invoice_num_);
      if (!retval)
      {
        db_mgr_->InsertSubData(sub_table_name, acc_details);
      }
    }    
  }
  quint64 time_spent = exec_timer.elapsed();
  std::cout << "Time Spent for storing data in DB = " << time_spent <<
    " milli seconds, seconds = " << (time_spent * 0.001) << std::endl;
  std::cout << "Add DB function completed." << std::endl;
}

void ArabicTranslate::DbRetrieve()
{
  std::cout << "Retrieve Data is pressed." << std::endl;
  QString line_data = ui_.search_num->text();
  qulonglong sub_num = line_data.toULongLong();
  std::cout << "Subscription Number = " << sub_num << std::endl;
  bool is_db_open = db_mgr_->IsDbOpen();
  if (is_db_open)
  {
    /* Check whether main table exist or not.*/
    QString main_table_name = MAIN_TABLE_NAME;
    bool retval = db_mgr_->IsTableExists(main_table_name);
    if (retval)
    {
      std::cout << "Main table exists." << std::endl;
      //Check whether the subscription number exists or not.
      retval = db_mgr_->IsInMainTable(main_table_name, sub_num);
      
      if (retval)
      {
        AccountDetails main = db_mgr_->RetrieveMainData(main_table_name,
            sub_num);

        std::cout << "Subscription Number found in the main table."
            << std::endl;
        QString sub_table_name = SUB_TABLE_START + line_data;
        /* check whether sub_table exists or not*/
        retval = db_mgr_->IsTableExists(sub_table_name);

        if (retval)
        {
          std::cout << "Subscription Table found." << std::endl;
          std::vector<AccountDetails> whole_data = db_mgr_->RetrieveSubData(
              sub_table_name, sub_num, main);
          data_table_view_->UpdateSubGroup(whole_data);
          data_table_view_->setVisible(true);
          data_table_view_->update();
          ui_.data_view->update();
        } else
        {
          std::cout << "Subscription table does not exist." << std::endl;
        }
      } else
      {
        std::cout << "Subscription does not exist in the main table."
            << std::endl;
        message_box_->setText("Not a valid Sub Scription Number");
        message_box_->setStandardButtons(QMessageBox::Ok);
        message_box_->update();
        message_box_->show();
      }
    } else
    {
      std::cout << "Main table does not exist." << std::endl;
    }    
  }
  std::cout << "End of DB Retrieval Function." << std::endl;
  this->update();
}

void ArabicTranslate::Pdf()
{
  std::cout << "Pdf is pressed." << std::endl; 
  
  QString current_dir = QDir::currentPath();
  QString pdf_file_name = QFileDialog::getOpenFileName(this,
      tr("Open PDF File"),
      current_dir,
      tr("PDF File (*.pdf)"));
  std::cout << "File Name = " << pdf_file_name.toStdString()
    << std::endl;  

  if (pdf_file_name.size() > 0)
  {
    QElapsedTimer exec_timer;
    exec_timer.start();
    XPdfParse xpdf_parse(pdf_file_name);
    xpdf_parse.Parse();
    unsigned int block_length = xpdf_parse.GetBlockLength();
    Blocks data = xpdf_parse.GetBlocks();
    quint64 time_spent = exec_timer.elapsed();
    std::cout << "Time Spent for convertion and Parsing = " << time_spent <<
        " milli seconds, seconds = " << (time_spent * 0.001) << std::endl;

    ParseData parse_data;
    parse_data.FormData(data);
    std::vector<unsigned int> types = ParseData::GetTypes();
    std::cout << "No. of Types in the input file = " << types.size()
        << std::endl;
    

    /*if (data.size() > 0)
    { 
      if (block_length > RESIDENTIAL_BLOCK_LENGTH)
      {
        UpdateInduDataTable(data);
      } else
      {
        UpdateResiDataTable(data);
      }      
      graphics_area_->setVisible(false);
      graphics_area_->update();
      
      ui_.view->setVisible(true);
      this->update();
      time_spent = exec_timer.elapsed();
      std::cout << "Time Spent for convertion and Parsing, and Table = "  
          <<time_spent << " milli seconds, seconds = " << (time_spent * 0.001)
          <<std::endl;      
    }  */  
  }
}

void ArabicTranslate::View()
{
  std::cout << "View is pressed." << std::endl;  
  
  int width = data_values_.size() * 20 + 50;
  int height = graphics_area_->height() - graphics_area_->y() - 10;

  data_table_->setVisible(false);
  data_table_->update();

  graphic_view_->setMinimumSize(width, height);
  graphic_view_->SetData(data_values_);  
  graphic_view_->setVisible(true);
  graphic_view_->update();     
  
  graphics_area_->setVisible(true);
  graphics_area_->update();
  ui_.data_view->update();  
  this->update();
}

void ArabicTranslate::paintEvent(QPaintEvent *event)
{
  ui_.file_save->setEnabled(is_file_save_);  
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
  

  //database
  // Check whether database directory exists, if not create.

  QString db_path = cur_dir + QDir::separator() + ".." + QDir::separator()
    + DATABASE_DIR_NAME;
  db_path = QDir(QDir::toNativeSeparators(db_path)).absolutePath();
  QFile file(db_path);
  if (!file.exists())
  { 
    QString base_path = cur_dir + QDir::separator() + "..";
    base_path = QDir(QDir::toNativeSeparators(base_path)).absolutePath();
    bool ret = QDir(base_path).mkdir(DATABASE_DIR_NAME);

    if (ret)
    {
      std::cout << "Able to create a temp directory." << std::endl;
    }
  }

  QString db_name = db_path + QDir::separator() + DATABASE_NAME;

  db_name = QDir(QDir::toNativeSeparators(db_name)).absolutePath();
  std::cout << "Data Base File = " << db_name.toStdString() << std::endl;
  db_mgr_ = new DbManager();
  db_mgr_->CreateDb(db_name);
  db_mgr_->OpenDb(db_name);

  /*db_mgr_ = new DbManager(db_name);*/

  QDesktopWidget *desktop_widget = QApplication::desktop();
  QRect widget_geometry = desktop_widget->availableGeometry(
      desktop_widget->primaryScreen());
  this->resize((widget_geometry.width() - 500),
      (widget_geometry.height() - 200));
}

void ArabicTranslate::InitUi()
{  
  InitDataTable();
  ui_.view->setVisible(false); 
  ui_.pdf->setVisible(false);

  graphics_area_ = new QScrollArea(ui_.data_view);  
  graphics_area_->setVisible(false);   

  graphic_view_ = new GraphicView(graphics_area_);
  graphics_area_->setWidget(graphic_view_);
  graphic_view_->setVisible(false);
  
  data_table_view_ = new TableView(ui_.data_view);
  data_table_view_->setVisible(false);

  message_box_ = new QMessageBox(this);
  message_box_->setVisible(false);
  message_box_->setStandardButtons(0);

  /*ui_.data_base_operations->setVisible(false);
  ui_.db_add->setVisible(false);
  ui_.search_num->setVisible(false);
  ui_.db_retrieve->setVisible(false);*/

  is_file_save_ = false;
}

void ArabicTranslate::ConnectSignals()
{
  connect(ui_.file_open, SIGNAL(triggered()), this, SLOT(FileOpen()));
  connect(ui_.file_save, SIGNAL(triggered()), this, SLOT(FileSave()));
  connect(ui_.file_exit, SIGNAL(triggered()), this, SLOT(FileExit()));
  connect(ui_.combo_box_types, SIGNAL(currentIndexChanged(int)), this,
      SLOT(TypesIndexChanged(int)));
  connect(ui_.db_add, SIGNAL(released()), this, SLOT(DbAdd()));
  connect(ui_.db_retrieve, SIGNAL(released()), this, SLOT(DbRetrieve()));
  

  connect(ui_.pdf, SIGNAL(released()), this, SLOT(Pdf()));  
  connect(ui_.view, SIGNAL(released()), this, SLOT(View()));
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

  data_table_->setGeometry(5, 15, ui_.data_view->width() - 10,
    ui_.data_view->height() - 20);
  data_table_->update();

  data_table_view_->setGeometry(5, 15, ui_.data_view->width() - 10,
      ui_.data_view->height() - 20);
  data_table_view_->update();

  graphics_area_->setGeometry(5, 15, ui_.data_view->width() - 10,
    ui_.data_view->height() - 20);
  graphics_area_->update(); 
  
  this->update();
}

void ArabicTranslate::InitDataTable()
{
  data_table_ = new QTableWidget(ui_.data_view);  
  data_table_->setVisible(false);
}

void ArabicTranslate::UpdateInduDataTable(Blocks data_in)
{  
  data_table_->setColumnCount(10);
  QStringList header;
  header << "Subscription \n Number";
  header << "Type";
  header << "Active Power \n Consumption";
  header << "Active Power \n Consumption \n (SAR)";
  header << "Reactive Power \n Consumption";
  header << "Reactive Power \n Consumption (SAR)";
  header << "Settlement";
  header << "Power Factor";
  header << "Reading From";
  header << "Reading To";
  data_table_->setHorizontalHeaderLabels(header);
  QHeaderView* header_view = data_table_->horizontalHeader();

  header_view->setSectionResizeMode(QHeaderView::Stretch);

  data_values_.clear();
  IndustrialData industrial_data;
  industrial_data.FormData(data_in);
  std::vector<AccountDetails> acc_data = industrial_data.GetDataInfo();

  data_table_->setRowCount(acc_data.size());
  for (unsigned int counter = 0; counter < acc_data.size(); counter++)
  {
    AccountDetails acc_details = acc_data.at(counter);
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.subscription_num_));
    data_table_->setItem(counter, 0, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.type_));
    data_table_->setItem(counter, 1, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.active_pow_cons_));
    data_table_->setItem(counter, 2, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.active_pow_cons_cost_, 'f', 2));
    data_table_->setItem(counter, 3, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.reactive_pow_cons_));
    data_table_->setItem(counter, 4, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.reactive_pow_cons_cost_, 'f', 2));
    data_table_->setItem(counter, 5, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.settlement_, 'f', 2));
    data_table_->setItem(counter, 6, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.power_factor_, 'f', 2));
    data_table_->setItem(counter, 7, item);

    item = new QTableWidgetItem();
    item->setText(acc_details.reading_from_);
    data_table_->setItem(counter, 8, item);

    item = new QTableWidgetItem();
    item->setText(acc_details.reading_to_);
    data_table_->setItem(counter, 9, item);      
  }
  
  data_table_->setVisible(true);
  data_table_->update();
  this->update();
}

void ArabicTranslate::UpdateResiDataTable(Blocks data_in)
{
  ResidentialData resi_data;
  resi_data.FormData(data_in);
  std::vector<AccountDetails> acc_data = resi_data.GetDataInfo();

  data_table_->setRowCount(acc_data.size());

  data_table_->setColumnCount(10);
  QStringList header;
  header << "Subscription \n Number";
  header << "Type";
  header << "Active Power \n Consumption";
  header << "Active Power \n Consumption\n (SAR)";
  header << "Electrometer Fee";
  header << "Total Consumption Cost\n (SAR)";
  header << "Settlement";
  header << "Total Cost \n (SAR)";
  header << "Reading From";
  header << "Reading To";
  data_table_->setHorizontalHeaderLabels(header);
  QHeaderView* header_view = data_table_->horizontalHeader();

  header_view->setSectionResizeMode(QHeaderView::Stretch);

  data_values_.clear();

  for (unsigned int counter = 0; counter < acc_data.size(); counter++)
  {
    AccountDetails acc_details = acc_data.at(counter);

    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.subscription_num_));
    data_table_->setItem(counter, 0, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.type_));
    data_table_->setItem(counter, 1, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.active_pow_cons_));
    data_table_->setItem(counter, 2, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.active_pow_cons_cost_, 'f', 2));
    data_table_->setItem(counter, 3, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.electrometer_fee_, 'f', 2));
    data_table_->setItem(counter, 4, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.total_cons_cost_, 'f', 2));
    data_table_->setItem(counter, 5, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.settlement_, 'f', 2));
    data_table_->setItem(counter, 6, item);

    item = new QTableWidgetItem();
    item->setText(QString::number(acc_details.total_cost_, 'f', 2));
    data_table_->setItem(counter, 7, item);

    item = new QTableWidgetItem();
    item->setText(acc_details.reading_from_);
    data_table_->setItem(counter, 8, item);

    item = new QTableWidgetItem();
    item->setText(acc_details.reading_to_);
    data_table_->setItem(counter, 9, item);

    if (acc_details.type_ == 1)
    {
      data_values_.push_back(acc_details.total_cost_);
    }
  }

  data_table_->setVisible(true);
  data_table_->update();
  this->update();
}


