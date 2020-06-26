#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

Image::Ptr Image::create(const int width, const int height, const int channels)
{
  auto img = std::make_shared<Image>(width, height, channels, nullptr);
  img->data = (unsigned char*)STBI_MALLOC(height * width * channels * sizeof(unsigned char));
  return img;
}

Image::Ptr Image::load(const std::string& filename)
{
  auto img = std::make_shared<Image>();
  img->data = stbi_load(filename.c_str(), &img->w, &img->h, &img->c, 0);
  return img;
}

void Image::save(const std::string& filename, Image::ConstPtr img)
{
  if(stbi_write_png(filename.c_str(), img->w, img->h, img->c, img->data, img->w * img->c) > 0)
  {
    std::cout << "Created image at "<< filename << std::endl;
  }
  else
  {
    throw std::runtime_error("Failed to save image at " + filename);
  }
}

Image::Image()
{}

Image::Image(const int width, const int height, const int channels, unsigned char* data) :
  w{width}, h{height}, c{channels}, data{data}
{}

Image::~Image()
{
  STBI_FREE(data);
}
