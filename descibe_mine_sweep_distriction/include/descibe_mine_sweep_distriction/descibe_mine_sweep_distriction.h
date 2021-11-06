#ifndef descibe_mine_sweep_distriction_h
#define descibe_mine_sweep_distriction_h

/// this is the class to describe area of mine sweep

/// rect of windows,get by Win API
/// measure: size of square,height of menubar
/// so we can get the position of three icon
/// so we can get the the position of mine_square

/// this is a data struct to descibe the distiption of mines
///



/// 在计算过程中，有一部分数据已经无用，需要标注
/// ... 即该数值周围没有未知的方块

/// 扫雷的规则
/// - 某一数值的周围8格中，必然包含指定数值的雷
/// - 无数值的方格周围必然无雷
/// - 雷的总数确定
/// - 一个方格有为雷和非雷两种状态


/// 总体解决思路
/// 假设法
/// 假设为雷则满足所有条件，而假设非雷不满足某个条件，则标记某方块为雷
/// 反之，假设非雷则满足所有条件，而假设为雷不满足某个条件，则标记某方块非雷
/// 可以简化所有条件为相关条件

/// 判断是否满足条件的方法
/// 所有与该方格相关的数值在周围的8格中，包含直接相关的数值
/// 建立一个副本计算，是否能推导出必然为雷或者非雷的情况


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

/// 提供整体的既定描述
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

class GameStatus
{
public:
  ///处于游戏状态
  bool __start;
  SquareArray* __array;
  int __total_mine;
  int __remain_mine;
  int __time_cost;
};

///针对所有特殊情况进行计算
/// 遍历所有3*3方块
///

/// 将所有具有数字的作为计算单元（有一些周围没有未识别的方块，设置为无效）
/// 数字根据 周围未识别区域进行从小到大进行排序（标注为雷认为已识别）
/// 取最小的数据进行假设，（某一个为雷/非雷，若得到矛盾的结论，则）
/// 假设一个区域中有 mine square_mine  open_num square_doubt
/// 由简到难逐渐化简，
/// - 查找所有为空的位置，其周围的任何方块都不为雷 (open_num==0,square_doubt>0)
///
/// - 查找所有(open_num-mine-square_mine== 0)的情况
/// - 查找所有（square_doubt == 1）的情况
/// - 在解决(open_num-mine-square_mine== 1)的情况,使用

/// - 每一次计算结束后，进行挖掘，更新状态，检查是否有更简单的情况的存在，优先解决简单的情况






/// then update the datastruct ,when status change

/// according to square_status,mine_list/mine_number,calculte
/// calculate one square is not mine ,and then click
/// or record the sqare must be mine
/// until all obviously are not

/// 简化方法，先解决较易解决的问题
/// 逐个假设某个方格为
///


#endif
