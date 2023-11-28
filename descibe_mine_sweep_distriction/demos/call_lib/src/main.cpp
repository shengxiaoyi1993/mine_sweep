#include "descibe_mine_sweep_distriction/descibe_mine_sweep_distriction.h"
#include "macro_glog/macro_glog.h"

int main(int argc, char *argv[])
{
  TotalStatus root;
  std::string object_game="mine.exe";
  root.setObject(object_game);
  root.tryOpenFirst();


  while (root.syncDataFromObject() != 0) {
    if (root.update()) {
      goto update;
    }

    if (root.composeUpdate()) {
      goto update;
    }

    MACRO_GLOG_INFO("All update finish ,but cannot find all mine ");

    update:
    root.syncDataToObject();

  }


//  root.syncDataFromObject();

  return 0;

}

