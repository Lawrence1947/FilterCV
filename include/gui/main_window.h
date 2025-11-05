#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QImage>
#include <QLabel>
#include <QWidget>

#include <opencv2/opencv.hpp>

namespace gui
{

class main_window : public QWidget
{
  Q_OBJECT
public:
  explicit main_window (QWidget *parent = nullptr);

  void set_image (const cv::Mat &mat);

  ~main_window ();

protected:
  void resizeEvent (QResizeEvent *event) override;

private:
  QLabel *image_label = nullptr;
  QImage original;
  
  void update_scaled_pixmap ();
};

}

#endif