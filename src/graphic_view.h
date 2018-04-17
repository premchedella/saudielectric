#ifndef GRAPHIC_VIEW_H_
#define GRAPHIC_VIEW_H_

#include <iostream>

#include <QtWidgets/QScrollArea>


class GraphicArea : public QScrollArea
{
  Q_OBJECT

 public:
  GraphicArea(QWidget *parent = 0);
  ~GraphicArea();

protected:  
  void scrollContentsBy(int dx, int dy);

};

class GraphicView : public QWidget
{
  Q_OBJECT

 public:
   GraphicView(QWidget *parent = 0);
   ~GraphicView();
  void SetData(std::vector<float> data);
  void SetDimensions(QRect rect);

 protected:
  void paintEvent(QPaintEvent *event);
  void mouseReleaseEvent(QMouseEvent* event);  

 private:
  std::vector<float> data_;
  float min_;
  float max_;
  float avg_;
  bool is_draw_;  
};

#endif //GRAPHIC_VIEW_H_
