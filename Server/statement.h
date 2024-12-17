#ifndef STATEMENT_H
#define STATEMENT_H

//200 成功；302 重定向；403 拒绝；404 找不到；500 运行错误；
#define LOGIN 20010101  //登录请求，登录成功
#define LOGINFAIL 40410101 //登录失败：账号或密码错误
#define SIGNIN 20010201 //注册请求，注册成功
#define SIGNINFAIL 40410201  //注册失败：账号已存在
#define SIGNINERROR 30410201  //NULL
#define CHATMSG 20010301  //发送聊天信息
#define CHATHISTORY 20010302  //请求聊天历史
#define PERSONCHANGE 20010401 //修改个人账号，修改成功
#define PERSONCHANGEFAIL 40410401  //修改个人账号失败
#define PERSONCHANGEERROR 40310401 //修改个人密码错误
#define SEARCHPRODUCT 20010501 //搜索商品
#define REQUESTHOME 20010601 //首页请求
#define ADDSHOPPING 20010701  //加入购物车
#define REQUESTSHOPPING 20010702  //购物车请求
#define DELSHOPPING 20010703  //删除购物车
#define CREATEORDER 20010801  //创建订单
#define UPDATEORDER 20010802  //更新订单
#define CHECKORDER 20010803 //检查库存是否充足
#define CREATEORDERLIST 20010901  //创建订单List
#define REQUESTORDER 20011001   //请求订单历史
//#define RESETPWD 20010103
//#define RESETPWDF 40410103
//#define RESETPWDE 30410103

//#define updateOrder 1000002
//#define deleteShopping 1000003
//#define searchProduct 1000004
//#define addOrderList 1000005
//#define chatRoom 1000006
//#define searchProductType 1000007
//#define clientUpdate 1000008

#include <QColor>
const QColor redPress(232, 50, 11);
const QColor redDefault(252, 90, 31);
const QColor redHover(255, 107, 48);

#endif // STATEMENT_H
