using System;

namespace RushQuant.Clients
{
    /// <summary>错误代码</summary>
    public static class ErrorCode
    {
        /// <summary>成功</summary>
        public const int Success = 0;

        /// <summary>无效的用户名或者密钥</summary>
        public const int System_InvalidUsernameOrKey = 1001;
        /// <summary>初始化Socket错误</summary>
        public const int System_FailToInitializeSocket = 1002;
        /// <summary>没有有效的交易服务器</summary>
        public const int System_NotAvailableTradeServer = 1003;
        /// <summary>获取远程数据出错</summary>
        public const int System_FailToFetchData = 1004;
        /// <summary>加载出错</summary>
        public const int System_FailToLoad = 1005;
        /// <summary>版本不支持</summary>
        public const int System_VersionNotSupport = 1006;

        /// <summary>帐户不存在</summary>
        public const int Account_NotFound = 2001;
        /// <summary>帐户初始化出错</summary>
        public const int Account_FailToInitialize = 2001;

        /// <summary>网络初始化出错</summary>
        public const int Network_FailToInitialize = 3001;
        /// <summary>网络连接出错</summary>
        public const int Network_FailToConnect = 3002;
        /// <summary>网络发送错误</summary>
        public const int Network_FailToSend = 3003;
        /// <summary>网络接收错误</summary>
        public const int Network_FailToReceive = 3004;

        /// <summary>无效的回应数据</summary>
        public const int Trade_InvalidResponse = 6001;
        /// <summary>无法解析回应数据</summary>
        public const int Trade_FailToAnalyseResponse = 6002;
        /// <summary>不支持的请求</summary>
        public const int Trade_UnsupportRequest = 6003;
        /// <summary>远程返回错误消息</summary>
        public const int Trade_RemoteResponseError = 6004;
        /// <summary>远程返回数据太大</summary>
        public const int Trade_ResponseTooLarge = 6005;
        /// <summary>返回的数据未与预期一致</summary>
        public const int Trade_ResponseUnexceptedData = 6006;
        /// <summary>请求数据无效</summary>
        public const int Trade_InvalidRequest = 6007;
        /// <summary>输出结构体内存大小不足</summary>
        public const int Trade_OutputSizeNotEnough = 6008;
        /// <summary>通讯协议出错</summary>
        public const int Trade_ProtocolError = 6009;
        /// <summary>登录失败</summary>
        public const int Trade_FailToLogin = 6010;
    }
}
