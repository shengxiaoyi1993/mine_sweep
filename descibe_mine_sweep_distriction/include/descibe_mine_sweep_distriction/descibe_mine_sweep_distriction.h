#ifndef descibe_mine_sweep_distriction_h
#define descibe_mine_sweep_distriction_h

/// this is the class to describe area of mine sweep

/// rect of windows,get by Win API
/// measure: size of square,height of menubar
/// so we can get the position of three icon
/// so we can get the the position of mine_square

/// this is a data struct to descibe the distiption of mines



/// when
class Square
{
  enum ENUM_STATUS{
    ENUM_STATUS_safe,
    ENUM_STATUS_mine,
    ENUM_STATUS_doubt
  };

  ENUM_STATUS __status;
  /// when __num>=0 ,this number is valid
  int __num;

}

#endif
