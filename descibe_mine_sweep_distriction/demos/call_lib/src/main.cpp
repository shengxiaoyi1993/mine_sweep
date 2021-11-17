#include "descibe_mine_sweep_distriction/descibe_mine_sweep_distriction.h"


int main(int argc, char *argv[])
{
// Area tmp= TotalStatus::getOverlap(Position(0,0),Position(1,1),9,9);
// tmp.print();

// Area tmp_r= TotalStatus::getOverlap(Position(1,1),Position(0,0),9,9);
// tmp_r.print();
  auto array=getCombination(0,9);
  for (auto it_l:array) {
    for (auto it_e:it_l) {
      std::cout<<""<<it_e<<" ";

    }
    std::cout<<std::endl;
  }


  return 0;
}
