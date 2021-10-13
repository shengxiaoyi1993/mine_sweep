#ifndef descibe_mine_sweep_distriction_h
#define descibe_mine_sweep_distriction_h

/// this is the class to describe area of mine sweep

/// rect of windows,get by Win API
/// measure: size of square,height of menubar
/// so we can get the position of three icon
/// so we can get the the position of mine_square

/// this is a data struct to descibe the distiption of mines


#include <iostream>

/// when
class Square
{

public:
  enum ENUM_STATUS{
    ENUM_STATUS_SAFE,
    ENUM_STATUS_MINE,
    ENUM_STATUS_DOUBT
  };

  ENUM_STATUS __status;
  /// when __num>=0 ,this number is valid
  int __num;

  Square(){
    __num = -1;
    __status = ENUM_STATUS_DOUBT;
  }

};


class SquareArray{
SquareArray(int v_w,int v_h):
  __width(v_w),__height(v_h),
  __array(new Square[v_w*v_h])
{

}

public:
  Square *__array;
  ushort __width;
  ushort __height;

};



/// then update the datastruct ,when status change

/// according to square_status,mine_list/mine_number,calculte
/// calculate one square is not mine ,and then click
/// or record the sqare must be mine
/// until all obviously are not

/// 暴力方法
/// 简化方法，当
/// 逐个假设某个方格为
#endif
