#ifndef STATEMENT_H
#define STATEMENT_H

//200 成功；302 重定向；403 拒绝；404 找不到；500 运行错误；
#define LOGIN 20010101  //登录请求，登录成功
#define LOGINF 40410101 //登录失败：账号或密码错误
#define SIGNIN 20010102 //注册请求，注册成功
#define SIGNINF 40410102    //注册失败：账号已存在
#define SIGNINE 30410102    //NULL
#define SENDMSG 20010103    //发送聊天信息
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
