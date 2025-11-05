#ifndef CV_ENGINE_H
#define CV_ENGINE_H

#include <QImage>

#include <opencv2/opencv.hpp>

#include "filters/filter.h"

namespace core
{

class cv_engine
{
public:
  cv_engine () = default;
  ~cv_engine () = default;

  cv_engine (const cv_engine &) = delete;
  cv_engine &operator= (const cv_engine &) = delete;
  cv_engine (cv_engine &&) = delete;
  cv_engine &operator= (cv_engine &&) = delete;

  void set_source_image (const cv::Mat &bgr);
  void clear_filters ();
  void add_filter (std::shared_ptr<filters::filter> filter);
  std::shared_ptr<filters::filter> find_filter (const char *id);

  QImage process ();

private:
  cv::Mat source_bgr;
  std::vector<std::shared_ptr<filters::filter>> pipeline;
};

}


#endif