#include "descibe_mine_sweep_distriction/descibe_mine_sweep_distriction.h"
#include <vector>
#include <set>
#include <algorithm>
#include "macro_glog/macro_glog.h"

/// 一次更新操作
bool TotalStatus::update()
{
  /// 遍历所有ENUM_STATUS_COVER_SAFE方格,且周围包含ENUM_STATUS_UNCOVER_DOUBT的数据
  /// 根据计算已知条件计算，查找出一下情景
  /// 1.center_number -ENUM_STATUS_COVER_MINE -ENUM_STATUS_UNCOVER_MINE==0,
  /// >此时可知所有ENUM_STATUS_UNCOVER_DOUBT为ENUM_STATUS_COVER_SAFE
  /// 2.center_number -ENUM_STATUS_COVER_MINE -ENUM_STATUS_UNCOVER_MINE= \\
  /// ENUM_STATUS_UNCOVER_DOUBT
  /// >此时可知所有ENUM_STATUS_UNCOVER_DOUBT为ENUM_STATUS_UNCOVER_MINE

  for (size_t h=0;h<__array.__height;h++) {
    for (size_t w=0;w<__array.__width;w++) {
      if (__array.__array[h*__array.__width+w].__status
          == Square::ENUM_STATUS_UNCOVER_SAFE)
      {
        int  v_uncover_mine;
        int  v_uncover_safe;
        int  v_cover_mine;
        int  v_cover_safe;
        int  v_cover_doubt;
        calculateAllEleInMat(h,w,
                             v_uncover_mine,
                             v_uncover_safe,
                             v_cover_mine,
                             v_cover_safe,
                             v_cover_doubt
                             );

        if (v_cover_doubt == 0) {
          continue;
        }

        if (__array.__array[h*__array.__width+w].__num-v_cover_mine-v_uncover_mine == 0) {
          /// setAll ENUM_STATUS_UNCOVER_DOUBT as ENUM_STATUS_COVER_SAFE

          setAllEleStatusInMat(h,w,Square::ENUM_STATUS_COVER_DOUBT,Square::ENUM_STATUS_COVER_SAFE);

          return true;
        }
        else if(__array.__array[h*__array.__width+w].__num-v_cover_mine-v_uncover_mine
                == v_cover_doubt){
          /// setAll ENUM_STATUS_UNCOVER_DOUBT as ENUM_STATUS_COVER_MINE
          setAllEleStatusInMat(h,w,Square::ENUM_STATUS_COVER_DOUBT,Square::ENUM_STATUS_COVER_MINE);

          return true;
        }
        else{
          return false;
        }

      }
      ;
    }

  }

  return false;
}

int TotalStatus::setObject(const std::string &v_obj)
{
  /// getRect
  /// getStatus // ifstart time remainMine
  /// verifySquare

}

int TotalStatus::tryOpenFirst()
{
  /// 随机点一个方格
}



/// 统计一个格子周围1格，各种类型的格子数量
int TotalStatus::calculateAllEleInMat(int v_h,int v_w,
                                      int & v_uncover_mine,
                                      int & v_uncover_safe,
                                      int & v_cover_mine,
                                      int & v_cover_safe,
                                      int & v_cover_doubt)
{
  /// v_h-1 v_h v_h+1
  /// v_w-1 v_w v_w+1
  v_uncover_mine=0;
  v_uncover_safe=0;
  v_cover_mine=0;
  v_cover_safe=0;
  v_cover_doubt=0;
  for (int h=v_h-1;h<=v_h+1;h++) {
    for (int w=v_w-1;w<=v_w+1;w++) {
      if (h>=0&&h<__array.__height
          && w>=0&&w<__array.__width) {
        switch (__array.__array[h*__array.__width+w].__status) {
          case Square::ENUM_STATUS_COVER_DOUBT:{
            v_cover_doubt++;
            break;
          }
          case Square::ENUM_STATUS_COVER_MINE:{
            v_cover_mine++;
            break;
          }
          case Square::ENUM_STATUS_COVER_SAFE:{
            v_cover_safe++;
            break;
          }

          case Square::ENUM_STATUS_UNCOVER_MINE:{
            v_cover_mine++;
            break;
          }
          case Square::ENUM_STATUS_UNCOVER_SAFE:{
            v_cover_safe++;
            break;
          }
        }
      }
    }
  }

  return 0;
}

void TotalStatus::setAllEleStatusInMat(int v_h,
                                       int v_w,
                                       Square::ENUM_STATUS v_src,
                                       Square::ENUM_STATUS v_target)
{

  for (int h=v_h-1;h<=v_h+1;h++) {
    for (int w=v_w-1;w<=v_w+1;w++) {
      if (h>=0&&h<__array.__height
          && w>=0&&w<__array.__width) {
        if (__array.__array[h*__array.__width+w].__status == v_src) {
          __array.__array[h*__array.__width+w].__status = v_target;
        }
      }
    }
  }

}

bool TotalStatus::checkPointInArea(int v_h,int v_w,Area v_area)
{
  if (v_h>=v_area.__h&&v_h<(v_area.__h+v_area.__height)&&
      v_w>=v_area.__w && v_w<(v_area.__w+v_area.__width)) {
    return true;
  }
  else{
    return false;
  }
}

bool TotalStatus::composeUpdate()
{
  for (int ih=0;ih<__array.__height;ih++) {
    for (int iw=0;iw<__array.__width;iw++) {
      if(__array.__array[ih*__array.__width+iw].__status == Square::ENUM_STATUS_COVER_DOUBT)
      {
        if (statisticalCalculateInMat(ih,iw)) {
          return true;
        }

      }

    }
  }
  return false;

}




/// 找到所有ENUM_STATUS_COVER_DOUBT落在该井字区域A的井字区域b，记录进列表L
/// 组合L中不重合的井字格，若组合中mine-mine_(cover or uncover)=0
/// >或者mine-mine_(cover or uncover)=组合L中余下的ENUM_STATUS_COVER_DOUBT数量，
/// >此时能确定余下的ENUM_STATUS_COVER_DOUBT全为ENUM_STATUS_COVER_MINE或者ENUM_STATUS_COVER_SAFE
bool   TotalStatus::statisticalCalculateInMat(int v_h,int v_w)
{

  std::vector<Position> list;

  /// 获取一个列表
  /// 目标点的所有ENUM_STATUS_COVER_DOUBT落在 （v_h，v_w）井字区域
  for (int ih=v_h-2;ih<=v_h+2;ih++) {
    for (int iw=v_w-2;iw<=v_w+2;iw++)
    {

      if (ih>=0&&ih<__array.__height
          && iw>=0&&iw<__array.__width) {
        //（ih，iw）点的区域落在
        if (isAllCoverDoubtFallIn(ih,iw,v_h,v_w)) {
          list.push_back(Position(ih,iw));
        }

      }

      /// 对list中的元素进行组合，元素数量任意
      /// 若组合中任意两元素没有重叠区域，则组合的总雷数为数值之和
      /// 获取目标区域的总雷数S，目标区域中组合之外的ENUM_STATUS_COVER_DOUBT O,组合的总雷数Sx
      /// 当以下情形，可以确认ENUM_STATUS_COVER_DOUBT的状态，
      /// S=Sx时,ENUM_STATUS_COVER_DOUBT全为ENUM_STATUS_COVER_SAFE
      /// S-Sx=O时，ENUM_STATUS_COVER_DOUBT全为mine
      /// 成功时别后全部翻出ENUM_STATUS_COVER_SAFE的继续

      std::vector<std::vector<int>> combinations=getCombination(0,list.size()-1);

      for(auto it:combinations){
        /// it中每一个数代表list中的一个组合
        /// 选择组合 每个组合中两两之间没有重叠区域或者重叠区域中不存在ENUM_STATUS_COVER_DOUBT，不满足则跳过
        /// 可以记录所有的ENUM_STATUS_COVER_DOUBT，新增的ENUM_STATUS_COVER_DOUBT点不与原有点重复
        std::set<Position> list_cover_doubt;
        std::set<Position> list_cover_mine;
        std::set<Position> list_uncover_mine;
        int sum_mine_in_cover_doubt=0;
        bool suitable=true;


        for(auto item_ele:it)
        {

          int  v_uncover_mine;
          int  v_uncover_safe;
          int  v_cover_mine;
          int  v_cover_safe;
          int  v_cover_doubt;

          calculateAllEleInMat(list[item_ele].__h,
                               list[item_ele].__w,
                               v_uncover_mine,
                               v_uncover_safe,
                               v_cover_mine,
                               v_cover_safe,
                               v_cover_doubt
                               );

          /// 每个组合中包含多个点，每个点的状态进行统计
          for (int sh=list[item_ele].__h-1;sh<=list[item_ele].__h+1;sh++) {
            for (int sw=list[item_ele].__w-1;sw<=list[item_ele].__w+1;sw++){
              if (checkPoint(sh,sw) && checkPointInArea(sh,sw,Area(v_h-1,v_w-1,3,3))) {
                switch (__array.__array[v_h*__array.__width+v_w].__status) {
                  case Square::ENUM_STATUS_COVER_DOUBT:{
                    if (list_cover_doubt.find(list[item_ele]) == list_cover_doubt.end()) {
                      /// 未找到
                      list_cover_doubt.insert(list[item_ele]);
                    }
                    else{
                      suitable =false;
                      goto flag_continue;

                    }

                    break;
                  }
                  case Square::ENUM_STATUS_COVER_MINE:{
                    list_cover_mine.insert(list[item_ele]);
                    break;
                  }
                  case Square::ENUM_STATUS_UNCOVER_MINE:{
                    list_uncover_mine.insert(list[item_ele]);
                    break;
                  }
                  default:
                    break;

                }

              }

            }
          }

          sum_mine_in_cover_doubt+=(
                __array.__array[list[item_ele].__h*__array.__width+list[item_ele].__w].__num
              - v_uncover_mine-v_cover_mine);

        }

flag_continue:
        ///
        if (suitable) {
          /// 获取所有在(v_h,v_w)区域中且不在list_cover_doubt的ENUM_STATUS_COVER_DOUBT方格
          std::vector<Position> l_position_remain;
          for (int sh=v_h-1;sh<=v_h+1;sh++) {
            for (int sw=v_w-1;sw<=v_w+1;sw++){

              if (checkPoint(sh,sw) && (__array.__array[sh*__array.__width+sw].__status==Square::ENUM_STATUS_COVER_DOUBT)) {
                if (list_cover_doubt.find(Position(sh,sw))==list_cover_doubt.end()) {
                  l_position_remain.push_back(Position(sh,sw));
                }
              }

            }
          }
          if (l_position_remain.size() == 0) {
            continue;
          }



          if (sum_mine_in_cover_doubt + list_cover_mine.size()+list_uncover_mine.size()
              == __array.__array[v_h*__array.__width+v_w].__num) {
            /// 此时(v_h,v_w)区域中所有不在list_cover_doubt中的方块均为ENUM_STATUS_UNCOVER_SAFE

            for (auto it_set:l_position_remain) {
              __array.__array[it_set.__h*__array.__width+it_set.__w].__status=Square::ENUM_STATUS_UNCOVER_SAFE;
            }
            return true;

          }
          else if (sum_mine_in_cover_doubt + list_cover_mine.size()+list_uncover_mine.size()
                   +l_position_remain.size()
                   == __array.__array[v_h*__array.__width+v_w].__num) {
            /// 此时l_position_remain中的

            for (auto it_set:l_position_remain) {
              __array.__array[it_set.__h*__array.__width+it_set.__w].__status=Square::ENUM_STATUS_UNCOVER_MINE;
            }
            return true;

          }


        }
        else{
          continue;
        }

      }



    }
  }
  return false;
}

/// 实现
/// 先计算出重叠区域，然后检查target非重叠区域无CoverDoubt，统计重叠区域有CoverDoubt
bool TotalStatus::isAllCoverDoubtFallIn(int target_h,int target_w,int area_h,int area_w)
{
  Area overlap=getOverlap(Position(target_h,target_w),
                          Position(area_h,area_w),
                          __array.__height,
                          __array.__width
                          );
  if (overlap.__height<0||overlap.__width<0) {
    MACRO_GLOG_ERROR("overlap.__height<0||overlap.__w<0");
    throw "error";
  }

  bool hascoverdoubt=false;
  for (int ih=target_h-1;ih<target_h+1;ih++) {
    for (int iw=target_w-1;iw<target_w+1;iw++) {
      if (overlap.has(Position(ih,iw))) {
        hascoverdoubt=true;
      }
      else{
        if (__array.__array[ih*__array.__width+iw].__status==Square::ENUM_STATUS_COVER_DOUBT) {
          return false;
        }
      }

    }
  }
  return hascoverdoubt;

}



bool TotalStatus::checkPoint(int v_h,int v_w)
{
  if (v_h>=0&&v_h<__array.__height
      && v_w>=0&&v_w<__array.__width) {
    //（ih，iw）点的区域落在
    return true;
  }
  else{
    return false;

  }
}

///先计算重叠区域，再取合法区域
Area TotalStatus::getOverlap(Position v_a,Position v_b, int v_height,int v_width)
{

  int overlap_h_min=v_a.__h>v_b.__h?v_a.__h-1:v_b.__h-1;
  int overlap_h_max=v_a.__h>v_b.__h?v_b.__h+1:v_a.__h+1 ;

  int overlap_w_min=v_a.__w>v_b.__w?v_a.__w-1:v_b.__w-1;
  int overlap_w_max=v_a.__w>v_b.__w?v_b.__w+1:v_a.__w+1 ;

  /// 需要去除小于0的部分，及大于规定大小的部分
  overlap_h_min=overlap_h_min>0?overlap_h_min:0;
  overlap_w_min=overlap_w_min>0?overlap_w_min:0;
  overlap_h_max=overlap_h_max<v_height-1?overlap_h_max:v_height-1;
  overlap_w_max=overlap_w_max<v_width-1?overlap_w_max:v_width-1;

  if (overlap_w_max-overlap_w_min<0||overlap_h_max-overlap_h_min<0) {
    return Area(0,0,0,0);
  }
  else{
    return Area(overlap_h_min>0?overlap_h_min:0,
                overlap_w_min>0?overlap_w_min:0,
                overlap_h_max-overlap_h_min+1,
                overlap_w_max-overlap_w_min+1);
  }

}

/// 迭代法
/// 每次增加一个数，获得的组合为之前的结果加上（之前的结果各加上新增的数）
/// 直至所有数被用完
std::vector<std::vector<int>> getCombination(int v_start,int v_num)
{
  if (v_start==v_num) {
    return {{v_start}};
  }
  else if(v_start>v_num){
    return {};
  }
  else{
    std::vector<std::vector<int>> array= getCombination(v_start+1,v_num);

    unsigned long size=array.size();
    for (unsigned long i=0;i<size;i++) {
      std::vector<int> copy=std::vector<int>(array[i].begin(),array[i].end());
      copy.push_back(v_start);
      array.push_back(copy);
    }
    array.push_back({v_start});

    return array;

  }

}




