#include "gui/main_window.h"

#include <QString>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

#include <opencv2/opencv.hpp>

#include <string>

#include "globals.h"
#include "system/screen.h"
#include "gui/utils.h"

namespace gui
{

main_window::main_window (QWidget *parent) : QWidget (parent)
{
  setWindowTitle (WINDOW_NAME);

  system_utils::screen screen;
  int main_window_width = screen.get_width () / 1.5;
  int main_window_height = screen.get_height () / 1.5;

  resize (main_window_width, main_window_height);

  auto *layout = new QVBoxLayout (this);
  layout->setContentsMargins(0, 0, 0, 0);

  image_label = new QLabel (this);
  image_label->setAlignment (Qt::AlignCenter);
  image_label->setSizePolicy (QSizePolicy::Expanding, QSizePolicy::Expanding);
  image_label->setMinimumSize (1, 1);

  layout->addWidget (image_label);

  cv::Mat cvimg (main_window_height, main_window_width, CV_8UC3, cv::Scalar (0, 0, 0));
  set_image (cvimg);
}

void main_window::set_image (const cv::Mat &mat)
{
  original = cvmat_to_qimage (mat);
  update_scaled_pixmap ();
}

void main_window::resizeEvent (QResizeEvent *event)
{
  QWidget::resizeEvent (event);
  update_scaled_pixmap ();
}

void main_window::update_scaled_pixmap ()
{
  if (original.isNull ())
    {
      image_label->clear ();
      return;
    }

  const auto scaled = QPixmap::fromImage (original).scaled (size (), Qt::KeepAspectRatio, Qt::SmoothTransformation);
  image_label->setPixmap (scaled);
}

main_window::~main_window () {}

}
