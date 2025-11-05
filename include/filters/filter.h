#ifndef FILTER_H
#define FILTER_H

#include <opencv2/opencv.hpp>

namespace filters
{

class filter
{
public:
  virtual const char *id () const = 0;
  virtual bool is_enabled () const = 0;
  virtual void set_enabled (bool on) = 0;
  virtual void apply (const cv::Mat &src_bgr, cv::Mat &dst_bgr) = 0;

  virtual ~filter () = default;
};

}

#endif