#ifndef CONST_H
#define CONST_H

#define Error_Success 0                            /* 成功 */
// System
#define Error_System_InvalidUsernameOrKey 1001     /* 无效的用户名或者密钥 */
#define Error_System_FailToInitializeSocket 1002   /* 初始化Socket错误 */
#define Error_System_NotAvailableTradeServer 1003  /* 没有有效的交易服务器 */
#define Error_System_FailToFetchData 1004          /* 获取远程数据出错 */
#define Error_System_FailToLoad 1005               /* 加载出错 */
#define Error_System_VersionNotSupport 1006        /* 版本不支持 */
// Account
#define Error_Account_NotFound 2001                /* 帐户不存在 */
#define Error_Account_FailToInitialize 2001        /* 帐户初始化出错 */
// Network
#define Error_Network_FailToInitialize 3001        /* 网络初始化出错 */
#define Error_Network_FailToConnect 3002           /* 网络连接出错 */
#define Error_Network_FailToSend 3003              /* 网络发送错误 */
#define Error_Network_FailToReceive 3004           /* 网络接收错误 */
// Trade
#define Error_Trade_InvalidResponse 6001           /* 无效的回应数据 */
#define Error_Trade_FailToAnalyseResponse 6002     /* 无法解析回应数据 */
#define Error_Trade_UnsupportRequest 6003          /* 不支持的请求 */
#define Error_Trade_RemoteResponseError 6004       /* 远程返回错误消息  */
#define Error_Trade_ResponseTooLarge 6005          /* 远程返回数据太大  */
#define Error_Trade_ResponseUnexceptedData 6006    /* 返回的数据未与预期一致 */
#define Error_Trade_InvalidRequest 6007            /* 请求数据无效 */
#define Error_Trade_OutputSizeNotEnough 6008       /* 输出结构体内存大小不足 */
#define Error_Trade_ProtocolError 6009             /* 通讯协议出错 */
#define Error_Trade_FailToLogin 6010               /* 登录失败 */

#endif /* CONST_H */