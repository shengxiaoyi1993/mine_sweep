
#include <iostream>
#include "cjsonobject/CJsonObject.hpp"
#include "screenshot/screenshot.h"


using namespace  std;

int main(int argc, char *argv[])
{
  neb::CJsonObject v_root;
  v_root.Add("key","key_val");
  cout<<v_root.ToFormattedString()<<endl;
  getScreenShotSave("screen.png","png");
  return 0;
}
