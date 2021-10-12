
#include <iostream>
#include "cjsonobject/CJsonObject.hpp"

using namespace  std;

int main(int argc, char *argv[])
{
  neb::CJsonObject v_root;
  v_root.Add("key","key_val");
  cout<<v_root.ToFormattedString()<<endl;
  return 0;
}
