//See LICENSE for license details.

#include "simif.h"

class GCDwithTB_t: virtual simif_t
{
public:
  GCDwithTB_t(int argc, char** argv) {}
  void run() {
    target_reset();
    const int max_iter = 1000;
    int iter = 0;
    while( peek( io_done) == 0 & iter < max_iter ) {
      step(1);
      ++iter;
    }
  }
};
