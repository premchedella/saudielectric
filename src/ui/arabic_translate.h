#ifndef MVESFM_H
#define MVESFM_H

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableWidget>
#include <QtWidgets\QScrollArea>
#include <QtWidgets\QMessageBox>

#include "ui_arabictranslate.h"

#include "../common_types.h"
#include "../graphic_view.h"

#include "table_view.h"
#include "../db_manager.h"


class ArabicTranslate : public QMainWindow
{
  Q_OBJECT

 public:
   ArabicTranslate(QWidget *parent = 0);
   ~ArabicTranslate();

 public slots:
  void FileOpen();
  void FileSave();
  void FileExit();

  void TypesIndexChanged(int index);
  void DbAdd();
  void DbRetrieve();
  
  void Pdf();
  void View();

 protected:
  void paintEvent(QPaintEvent *event);
  void resizeEvent(QResizeEvent* event);  

 private:
  void Init();
  void InitUi();
  void ConnectSignals();
  void Resize();
  
  void InitDataTable();  
  void UpdateInduDataTable(Blocks data_in);
  void UpdateResiDataTable(Blocks data_in);
  Ui::ArabicTranslateClass ui_; 
  QTableWidget* data_table_; 
  TableView* data_table_view_;
  QScrollArea* graphics_area_;
  //GraphicArea* graphics_area_;

  std::vector<float> data_values_;  
  GraphicView*  graphic_view_;
  QMessageBox*  message_box_;
  
  //Menu elements
  bool is_file_save_; 
  int types_current_index_;
  DbManager* db_mgr_;  
};

#endif // MVESFM_H
