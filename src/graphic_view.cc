#include "graphic_view.h"

#include <iomanip>
#include <list>
#include <functional>

#include <QtGui\QPainter>
#include <QtGui\QPen>
#include <QtGui\QBrush>


GraphicArea::GraphicArea(QWidget *parent)
{
  this->setParent(parent);
}

GraphicArea::~GraphicArea()
{

}


void GraphicArea::scrollContentsBy(int dx, int dy)
{
  std::cout << "Graphic View Scroll Event  = " << std::endl;
  this->update();
}


GraphicView::GraphicView(QWidget *parent)
{
  this->setParent(parent);  
  is_draw_ = false;
  data_.clear();
  min_ = 0;
  max_ = 0;
  avg_ = 0; 
    
}

GraphicView::~GraphicView()
{

}

void GraphicView::SetData(std::vector<float> data)
{
  std::cout << "Size of the View values = " << data.size()
    << std::endl;
  data_ = data;
  if (data.size() > 0)
  {
    std::vector<float>::iterator iter;

    iter = std::min_element(data.begin(), data.end());
    min_ = *iter;
    int min_loc = std::distance(std::begin(data), iter);

    iter = std::max_element(data.begin(), data.end());
    max_ = *iter;
    int max_loc = std::distance(std::begin(data), iter);

    double total_cost = 0;
    for (unsigned int counter = 0; counter < data.size(); counter++)
    {
      total_cost = total_cost + data.at(counter);
    }
    avg_ = total_cost / data.size();

    //std::cout.precision(std::numeric_limits<float>::digits10 + 1);
    std::cout << "Maximum Value = " <<  max_ <<
        " at location = " << max_loc << ", Minimum Value = " << min_ <<
        " at location = " << min_loc << ", Average Value = " << avg_ <<
        std::endl;  

    this->update();
    is_draw_ = true;
  }
}

void GraphicView::SetDimensions(QRect rect)
{
 
}

void GraphicView::mouseReleaseEvent(QMouseEvent* event)
{
  is_draw_ = true;
  this->update();
}

void GraphicView::paintEvent(QPaintEvent *event)
{  
  if (is_draw_)
  {
    std::cout << "Paint Called." << std::endl;
    std::cout << "X = " << this->x() << ", Y = " << this->y() << ", Width ="
      << this->width() << ", Height = " << this->height() << std::endl;
    is_draw_ = false;
    
    QPainter p;
    p.begin(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.translate(0, 0);
    p.scale(1, 1);  

    p.setBrush(QColor(0x00, 0x00, 0x00));
    //Set the background with balck.
    p.drawRect(this->rect());
    
    //Draw the Horizontal and Vertical axes.
    p.setPen(QPen(QColor(0x86, 0x86, 0x86), 3)); 

    // Setup Font
    p.setFont(QFont(p.font().family(), 10));
           
    //Each data value has 5 pixels.  
    int view_width = this->width() - this->x();
    int view_height = this->height() - this->y();
    
    //Horizontal Axis    
    p.drawLine(this->x() + 5, view_height - 30, view_width, view_height - 30);
    //Vertical Axis
    p.drawLine(this->x() + 25, view_height - 10, this->x() + 25, this->y() + 5);

    //Horizontal Labels

    view_width = view_width - (this->x() + 25);
    view_height = view_height - 30 - (this->y() + 5);

    int start_x = this->x() + 25 + 20;
    int y = view_height + 10;
        
    for (unsigned int counter = 0; counter < data_.size(); counter++)
    {
      int x = start_x + (counter * 20);
      p.drawLine(x, y, x, y + 10);      
    }
      

    std::vector<float> data_sort = data_;
    std::sort(data_sort.begin(), data_sort.end(), std::greater<float>());

    float unit = float(view_height) / data_sort.at(3);
    float total = 0;
    for (unsigned int counter = 3; counter < data_sort.size(); counter++)
    {
      total = total + data_sort.at(counter);
    }

    float avg = total / (data_sort.size() - 3);
    
    p.setBrush(QColor(0xff, 0x00, 0x00));
    int start_y = (this->height() - this->y()) - 30;
    start_x = this->x() + 30;

    for (unsigned int counter = 0; counter < data_.size(); counter++)
    {
      QRect rect;
      int height = unit * data_.at(counter);
      int end_y = start_y - height;
      int x = start_x + (20 * counter);
      rect.setX(x);
      rect.setY(end_y);
      rect.setWidth(20);
      rect.setHeight(height);
      p.drawRect(rect);     
    }
    
    //Draw the Average line.    
    p.setPen(QPen(QColor(0x00, 0xff, 0x00), 3));

    int end_y = start_y - (unit * avg);
    p.drawLine(this->x() + 5, end_y, view_width, end_y);
    

    p.end();
  }
}