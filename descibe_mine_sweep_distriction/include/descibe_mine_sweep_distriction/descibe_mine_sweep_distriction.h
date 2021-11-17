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
#include <vector>

/// 点击实际方格操作后，根据已有情况进行更新时，只有ENUM_STATUS_UNCOVER_DOUBT状态的转换成其他状态
/// 经过计算后ENUM_STATUS_UNCOVER_DOUBT确认后，状态装换成其他状态
/// 当状态为ENUM_STATUS_COVER_SAFE时，__num有效，标记周围的雷数

class Square
{

public:
  enum ENUM_STATUS{
    ENUM_STATUS_UNCOVER_MINE,
    ENUM_STATUS_UNCOVER_SAFE,
    ENUM_STATUS_COVER_MINE,
    ENUM_STATUS_COVER_DOUBT,
    ENUM_STATUS_COVER_SAFE
  };

  ENUM_STATUS __status;
  /// when __num>=0 ,this number is valid
  int __num;

  Square(){
    __num = -1;
    __status = ENUM_STATUS_UNCOVER_MINE;
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
  size_t __width;
  size_t __height;

};

class Position
{
public:
  int __h;
  int __w;
  Position(int v_h,int v_w):
    __h(v_h),__w(v_w)
  {

  }
};

class Area
{
public:
  int __h;
  int __w;
  int __height;
  int __width;

  Area(int v_h,int v_w,int v_height,int v_width):
    __h(v_h),__w(v_w),__height(v_height),__width(v_width)
  {

  }

 void print()
  {
    std::cout<<"__h:"<<__h<<std::endl;
    std::cout<<"__w:"<<__w<<std::endl;
    std::cout<<"__height:"<<__height<<std::endl;
    std::cout<<"__width:"<<__width<<std::endl;

  }

 bool has(Position v_point)
 {
   if (v_point.__h>=__h&&v_point.__h<=__h+__height
       &&v_point.__w>=__w&&v_point.__w<=__w+__width
       ) {
     return true;
   }
   else{
     return  false;
   }

 }


};


/// 用以标记所有的
class TotalStatus
{
public:
  ///处于游戏状态
  bool __start;
  SquareArray __array;
  int __total_mine;
  int __remain_mine;
  int __time_cost;


  public:
  /// 对数据进行检验，直至没有简易直接确定的情景发生
  bool update();

  /// 根据当前数据揭露所有被认定为ENUM_STATUS_UNCOVER_SAFE的单元
  bool coverAllUncoverSafe();

  /// 根据实际的棋盘更新数据
  bool updateData();

  int calculateAllEleInMat(int v_h,int v_w,
      int & v_uncover_mine,
                           int & v_uncover_safe,
                           int & v_cover_mine,
                           int & v_cover_safe,
                           int & v_cover_doubt);

  /// 将所有v_src的方格更改为v_target状态
  void setAllEleStatusInMat(int v_h,
                            int v_w,
                            Square::ENUM_STATUS v_src,
                            Square::ENUM_STATUS v_target);

  /// 两个区域重合时，方格的确定
  /// 假设存在这种情况，某井字区域A总数确定。且存在相邻井字区域B（或者）包含的未知方格只存在于A区域中，且不重合
  /// 且满足余下的未包含未知方格数与未知雷数相同，则可以确定出若干雷或者空格，则可可知统计出

  bool  StatisticalCalculateInMat(int v_h,int v_w);

  /// target点的CoverDoubt数量不为0，且全部落在area中
  bool isAllCoverDoubtFallIn(int target_h,int target_w,int area_h,int area_w);

  /// 检查点是否落在有效区域
  bool checkPoint(int v_h,int v_w);

  /// 假设输入的两点已验证为有效
  /// 假设必然有交集
  static Area getOverlap(Position v_a,Position v_b, int v_height,int v_width);


};


/// 获取连续数字的任意组合
std::vector<std::vector<int>> getCombination(int v_start,int v_num);

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
