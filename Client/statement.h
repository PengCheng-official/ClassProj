#ifndef STATEMENT_H
#define STATEMENT_H

//200 成功；302 重定向；403 拒绝；404 找不到；500 运行错误；
#define LOGIN 200101  //登录请求，登录成功
#define LOGINFAIL 404101 //登录失败：账号或密码错误
#define SIGNIN 200102 //注册请求，注册成功
#define SIGNINFAIL 404102  //注册失败：账号已存在
#define SIGNINERROR 304102  //NULL
#define CHATMSG 200103  //发送聊天信息
#define CHATHISTORY 200104  //请求聊天历史
#define PERSONMODIFY 200105 //修改个人信息
#define PERSONCHANGE 200205 //修改个人账号，修改成功
#define PERSONFAIL 404205  //修改个人账号失败
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

#endif // STATEMENT_H
