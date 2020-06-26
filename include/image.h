#include "core.h"

class Image
{
public:
  typedef std::shared_ptr<Image> Ptr;
  typedef std::shared_ptr<const Image> ConstPtr;

  int w;
  int h;
  int c;
  unsigned char* data;

  static Ptr create(int width, int height, int channels);
  static Ptr load(const std::string& filename);
  static void save(const std::string& filename, ConstPtr img);

  Image();

  Image(const int width, const int height, const int channels, unsigned char* data);

  ~Image();
};
