#pragma once
#include "targa/targa.h"

struct Texture {
  unsigned int texture_id;
  Targa::TgaImage* texture;
};
