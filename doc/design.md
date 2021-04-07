# saolei
## aim
- find all lei

## process
- randly find safe area
loop until all lei is find
- caculate safe area  
- apply to show safe area


## model
- room (lei/safe)
- block consist of room (width*height)
- room status(sure/unsure)
- the number of surround lei
- sum of all lei

## algorithm
- accord to number of sure&safe room,we can judge some area is lei or not
  - some room contains vertain quentity of lei ,

## some tech
- acknowledge the room of number
- judge the game area
- find same icon and judge what it means
- some process
- some operation to the game ,right click or left click

## accomplish process
- think out some algorithm to calcute the rate of whether certain room is lei
- think out a method that all application can observe the game in realtime
- cut some icon from game,and iput the mean of this icon
- using some tech before,we can get the the location of game ,and by visit some position we can get the infomation we expext
- using the  infomation we get,we can set up a model varying with real-time game status
  - at first we should make some rules
    - when this app is runing,no one can use this pc at same time
    - we may just run for play just one concrete game,

- then this app should be able to control our mouse,just right click ,so as to start/reset the game ,or click the room to submit our opertation to game
- when game is over, app should get its grade,win or not ,the time it cost .then app save its grade to a local file.


/// some algothrm using in saolei
/// random postion
/// rate calcule :
/// 假设穷举法
/// 假设我们知道某一区域的总数，然后有若干数值可以对同时描述了这一区域，
/// 我们选择某一值假设该值，然后利用已知数据向确定周围的数据，直至计算了所有已知值
///  若发现冲突，反向确定了该值
///  若未发现冲突，则假设该值的反值，再看是否有冲突产生
/// 由于某些情况下更容易计算出合理的值，因此在算法优化过程中可以首先寻找是否存在较容易计算出冲突的值，若有则优先计算
/// 对于没有冲突产生的情况，我门常常是一次性确定一些块的状态
