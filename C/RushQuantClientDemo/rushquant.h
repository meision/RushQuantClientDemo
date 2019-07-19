#ifndef RUSHQUANT_H
#define RUSHQUANT_H

#ifdef RUSHQUANT_EXPORTS
#define RUSHQUANT_API __declspec(dllexport)
#else
#define RUSHQUANT_API __declspec(dllimport)
#endif

typedef int BOOL;

/********** constant BEGIN **********/
/* 交易所编号 */
#define ExchangeId_SSE "SSE"         /* 上海证券交易所 */
#define ExchangeId_SZE "SZE"         /* 深圳证券交易所 */

/* 货币代码 */
#define Currency_RMB 1                            /* 人民币 */
#define Currency_HKD 2                            /* 港币 */
#define Currency_USD 3                            /* 美元 */

/* 报价方式 */
#define QuoteType_SSE_LimitPrice 1                 /*上海: 限价委托*/
#define QuoteType_SSE_FivePriceThenCancel 5        /*上海: 五档即成剩撤*/
#define QuoteType_SSE_FivePriceThenLimitPrice 7    /*上海: 五档即成转限价*/
#define QuoteType_SZE_LimitPrice 1                /* 深圳: 限价委托 */
#define QuoteType_SZE_CounterpartyBestPrice 2     /* 深圳: 对方最优价格 */
#define QuoteType_SZE_BestPrice 3                 /* 深圳: 本方最优价格 */
#define QuoteType_SZE_AnyPriceThenCancel 4        /* 深圳: 即时成交剩余撤销 */
#define QuoteType_SZE_FivePriceThenCancel 5       /* 深圳: 五档即成剩撤 */
#define QuoteType_SZE_AllPriceOrCancel 6          /* 深圳: 全额成交或撤销 */

/* 交易标志 */
#define TradeFlag_Buy 1                 /* 买入 */
#define TradeFlag_Sell 2                /* 卖出 */
#define TradeFlag_Purchase 3            /* 申购 */
#define TradeFlag_Redeem 4              /* 赎回 */
#define TradeFlag_MarginBuy 6           /* 融资买入 */
#define TradeFlag_MarginSell 7          /* 融券卖出 */
#define TradeFlag_MarginBuyCover 8      /* 融资售回 */
#define TradeFlag_MarginSellCover 9     /* 融券购回 */
#define TradeFlag_ETFPurchase 11        /* ETF申购 */
#define TradeFlag_ETFRedeem 12          /* ETF赎回 */
#define TradeFlag_FundPurchase 13       /* 基金申购 */
#define TradeFlag_FundRedeem 14         /* 基金赎回 */
#define TradeFlag_GradedFundMerge 17    /* 分级基金合并 */
#define TradeFlag_GradedFundSplit 18    /* 分级基金合拆 */
#define TradeFlag_FundSubscribe 19      /* 基金认购 */
#define TradeFlag_Placement 21          /* 配售 */
#define TradeFlag_Distribution 22       /* 配号 */
#define TradeFlag_CancelBuy -1          /* 撤买 */
#define TradeFlag_CancelSell -2         /* 撤卖 */

/* 委托状态 */
#define OrderStatus_Unorder 1                           /* 未申报 */
#define OrderStatus_UndealtOrder 3                      /* 已申报未成交 */
#define OrderStatus_InvalidOrder 4                      /* 非法委托 */
#define OrderStatus_PartialDealt 6                      /* 部分成交 */
#define OrderStatus_AllDealt 7                          /* 全部成交 */
#define OrderStatus_PartialDealtPartialCancelled  8     /* 部成部撤 */
#define OrderStatus_AllCancelled 9                      /* 全部撤单 */
/********** constant END **********/

#pragma pack(push)

/********** manage BEGIN **********/
#pragma region 初始化 initialize
// 系统初始化。
RUSHQUANT_API BOOL rushquant_initialize(const char* pUsername, const char* pKey);
#pragma endregion

#pragma region 释放内存 free
// 释放由系统生成的内存。
RUSHQUANT_API void rushquant_free(void* pointer);
#pragma endregion

#pragma region 销毁 dispose
// 系统销毁，释放资源。
RUSHQUANT_API BOOL rushquant_dispose();
#pragma endregion
/********** manage End **********/

/********** trade BEGIN **********/
#pragma region 账户列表 GetAccountList
// 获取支持账户编号列表, 返回账户个数。
RUSHQUANT_API int rushquant_trade_GetAccountList(int* accountIds);
#pragma endregion

#pragma region 账户重置 Reset
// 重置账户环境，如果指定账户已经登录并处于正常工作状态，则退出并重置状态。
RUSHQUANT_API BOOL rushquant_trade_Reset(int accountId);
#pragma endregion

#pragma region 下一编号 NextId
// 获取系统的下一个编号，用于请求的输入编号。
RUSHQUANT_API int rushquant_trade_NextId();
#pragma endregion

#pragma region 登录 Login
#pragma pack(1)
typedef struct
{
    int Id;                              /* 编号 */

    char TradePassword[12];              /* 交易密码 */
    char CommunicationPassword[12];      /* 通讯密码 */
} LoginInput;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* 结构大小 */
    int Id;                              /* 编号 */
    char ErrorMessage[100];              /* 错误消息 */
} LoginOutput;
// 登录指定的帐户。
RUSHQUANT_API BOOL rushquant_trade_Login(int accountId, const LoginInput* pInput, LoginOutput* pOutput);
#pragma endregion

#pragma region 查询Tick行情 QueryTickData
#pragma pack(1)
typedef struct
{
    int Id;                              /* 编号 */

    char ExchangeId[10];                 /* 交易所代码 */
    char InstrumentCode[16];             /* 合约代码 */
} QueryTickDataInput;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* 结构大小 */
    int Id;                              /* 编号 */
    char ErrorMessage[100];              /* 错误消息 */

    char ExchangeId[10];                 /* 交易所代码 */
    char InstrumentCode[16];             /* 合约代码 */
    char InstrumentName[32];             /* 合约名称 */
    double PreClosePrice;                /* 昨收价 */
    double OpenPrice;                    /* 今开价 */
    double LatestPrice;                  /* 当前价 */
    double BidPrice1;                    /* 买一价 */
    double BidPrice2;                    /* 买二价 */
    double BidPrice3;                    /* 买三价 */
    double BidPrice4;                    /* 买四价 */
    double BidPrice5;                    /* 买五价 */
    int BidVolume1;                      /* 买一量 */
    int BidVolume2;                      /* 买二量 */
    int BidVolume3;                      /* 买三量 */
    int BidVolume4;                      /* 买四量 */
    int BidVolume5;                      /* 买五量 */
    double AskPrice1;                    /* 卖一价 */
    double AskPrice2;                    /* 卖二价 */
    double AskPrice3;                    /* 卖三价 */
    double AskPrice4;                    /* 卖四价 */
    double AskPrice5;                    /* 卖五价 */
    int AskVolume1;                      /* 卖一量 */
    int AskVolume2;                      /* 卖二量 */
    int AskVolume3;                      /* 卖三量 */
    int AskVolume4;                      /* 卖四量 */
    int AskVolume5;                      /* 卖五量 */
} QueryTickDataOutput;
// 查询合约的五档Tick行情数据。
RUSHQUANT_API BOOL rushquant_trade_QueryTickData(int accountId, const QueryTickDataInput* pInput, QueryTickDataOutput** pOutput);
#pragma endregion

#pragma region 查询股东信息 QueryStockholderInfo
#pragma pack(1)
typedef struct
{
    int Id;                              /* 编号 */
} QueryStockholderInfoInput;
#pragma pack(1)
typedef struct
{
    char StockholderCode[12];            /* 股东代码 */
    char ExchangeId[10];                 /* 交易所代码 */
} QueryStockholderInfoOutputItem;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* 结构大小 */
    int Id;                              /* 编号 */
    char ErrorMessage[100];              /* 错误消息 */

    int Count;                           /* 项目条数 */
    QueryStockholderInfoOutputItem Items[];
} QueryStockholderInfoOutput;
// 查询股东信息，获取沪深A股东号码列表。
RUSHQUANT_API BOOL rushquant_trade_QueryStockholderInfo(int accountId, const QueryStockholderInfoInput* pInput, QueryStockholderInfoOutput** pOutput);
#pragma endregion

#pragma region 查询证券资产信息 QuerySecurityCapitalInfo
#pragma pack(1)
typedef struct
{
    int Id;                              /* 编号 */
} QuerySecurityCapitalInfoInput;
#pragma pack(1)
typedef struct
{
    int Currency;                        /* 币种 */
    double RemainingCapitalAmount;       /* 资金余额 */
    double AvailableCapitalAmount;       /* 可用资金 */
    double WithdrawableCapitalAmount;    /* 可取资金 */
    double TotalAssetAmount;             /* 总资产 */
} QuerySecurityCapitalInfoOutputItem;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* 结构大小 */
    int Id;                              /* 编号 */
    char ErrorMessage[100];              /* 错误消息 */

    int Count;                           /* 项目条数 */
    QuerySecurityCapitalInfoOutputItem Items[];
} QuerySecurityCapitalInfoOutput;
// 查询证券资产信息，获取账户的资产列表。
RUSHQUANT_API BOOL rushquant_trade_QuerySecurityCapitalInfo(int accountId, const QuerySecurityCapitalInfoInput* pInput, QuerySecurityCapitalInfoOutput** pOutput);
#pragma endregion

#pragma region 查询证券持仓信息 QuerySecurityPositionInfo
#pragma pack(1)
typedef struct
{
    int Id;                              /* 编号 */
} QuerySecurityPositionInfoInput;
#pragma pack(1)
typedef struct
{
    char ExchangeId[10];                 /* 交易所代码 */
    char InstrumentCode[16];             /* 合约代码 */
    char InstrumentName[32];             /* 合约代码 */
    int Volume;                          /* 证券数量 */
    int AvailableVolume;                 /* 可卖数量 */
    char StockholderCode[12];            /* 股东代码 */
} QuerySecurityPositionInfoOutputItem;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* 结构大小 */
    int Id;                              /* 编号 */
    char ErrorMessage[100];              /* 错误消息 */

    int Count;                           /* 项目条数 */
    QuerySecurityPositionInfoOutputItem Items[];
} QuerySecurityPositionInfoOutput;
// 查询证券持仓信息，获取账户的持仓列表。
RUSHQUANT_API BOOL rushquant_trade_QuerySecurityPositionInfo(int accountId, const QuerySecurityPositionInfoInput* pInput, QuerySecurityPositionInfoOutput** pOutput);
#pragma endregion

#pragma region 查询证券委托评估 QuerySecurityOrderEvaluation
#pragma pack(1)
typedef struct
{
    int Id;                              /* 编号 */

    char ExchangeId[10];                 /* 交易所代码 */
    char InstrumentCode[16];             /* 合约代码 */
    double OrderPrice;                   /* 委托价格 */
    double LatestPrice;                  /* 最新价格 */
    double CapitalAmount;                /* 资金总额 */
} QuerySecurityOrderEvaluationInput;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* 结构大小 */
    int Id;                              /* 编号 */
    char ErrorMessage[100];              /* 错误消息 */

    double BidableVolume;                /* 可买数量 */
} QuerySecurityOrderEvaluationOutput;
// 查询证券委托评估，获取当前可用资金条件下指定证券可委托数量。
RUSHQUANT_API BOOL rushquant_trade_QuerySecurityOrderEvaluation(int accountId, const QuerySecurityOrderEvaluationInput* pInput, QuerySecurityOrderEvaluationOutput** pOutput);
#pragma endregion

#pragma region 查询证券当日委托 QuerySecurityIntradayOrder
#pragma pack(1)
typedef struct
{
    int Id;                              /* 编号 */
} QuerySecurityIntradayOrderInput;
#pragma pack(1)
typedef struct
{
    int OrderDate;                       /* 委托日期 */
    int OrderTime;                       /* 委托时间 */
    char OrderID[20];                    /* 委托编号 */
    char StockholderCode[12];            /* 股东代码 */
    char ExchangeId[10];                 /* 交易所代码 */
    char InstrumentCode[16];             /* 合约代码 */
    char InstrumentName[32];             /* 合约名称 */
    int TradeFlag;                       /* 交易标志 */
    double OrderPrice;                   /* 委托价格 */
    int OrderVolume;                     /* 委托数量 */
    double DealPrice;                    /* 成交均价 */
    int DealVolume;                      /* 成交数量 */
    int CancelVolume;                    /* 撤单数量 */
    int QuoteType;                       /* 报价类型 */
    int OrderStatus;                     /* 状态 */
} QuerySecurityIntradayOrderOutputItem;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* 结构大小 */
    int Id;                              /* 编号 */
    char ErrorMessage[100];              /* 错误消息 */

    int Count;                           /* 项目条数 */
    QuerySecurityIntradayOrderOutputItem Items[];
} QuerySecurityIntradayOrderOutput;
// 查询证券当日委托，获取证券委托列表。
RUSHQUANT_API BOOL rushquant_trade_QuerySecurityIntradayOrder(int accountId, const QuerySecurityIntradayOrderInput* pInput, QuerySecurityIntradayOrderOutput** pOutput);
#pragma endregion

#pragma region 查询证券历史委托 QuerySecurityHistoricalOrder
#pragma pack(1)
typedef struct
{
    int Id;                              /* 编号 */

    int BeginDate;                       /* 开始日期 */
    int EndDate;                         /* 终止日期 */
} QuerySecurityHistoricalOrderInput;
#pragma pack(1)
typedef struct
{
    int OrderDate;                       /* 委托日期 */
    int OrderTime;                       /* 委托时间 */
    char OrderID[20];                    /* 委托编号 */
    char StockholderCode[12];            /* 股东代码 */
    char ExchangeId[10];                 /* 交易所代码 */
    char InstrumentCode[16];             /* 合约代码 */
    char InstrumentName[32];             /* 合约名称 */
    int TradeFlag;                       /* 交易标志 */
    double OrderPrice;                   /* 委托价格 */
    int OrderVolume;                     /* 委托数量 */
    int DealVolume;                      /* 成交数量 */
    double DealAmount;                   /* 成交金额 */
    int CancelVolume;                    /* 撤单数量 */
    int QuoteType;                       /* 报价类型 */
    int OrderStatus;                     /* 状态 */
} QuerySecurityHistoricalOrderOutputItem;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* 结构大小 */
    int Id;                              /* 编号 */
    char ErrorMessage[100];              /* 错误消息 */

    int Count;                           /* 项目条数 */
    QuerySecurityHistoricalOrderOutputItem Items[];
} QuerySecurityHistoricalOrderOutput;
// 查询证券历史委托，获取证券委托列表。
RUSHQUANT_API BOOL rushquant_trade_QuerySecurityHistoricalOrder(int accountId, const QuerySecurityHistoricalOrderInput* pInput, QuerySecurityHistoricalOrderOutput** pOutput);
#pragma endregion

#pragma region 查询证券当日成交 QuerySecurityIntradayDeal
#pragma pack(1)
typedef struct
{
    int Id;                              /* 编号 */
} QuerySecurityIntradayDealInput;
#pragma pack(1)
typedef struct
{
    int DealDate;                        /* 成交日期 */
    int DealTime;                        /* 成交时间 */
    char DealID[20];                     /* 成交编号 */
    char OrderID[20];                    /* 委托编号 */
    char QuoteNumber[20];                /* 申报编号 */
    char StockholderCode[12];            /* 股东代码 */
    char ExchangeId[10];                 /* 交易所代码 */
    char InstrumentCode[16];             /* 合约代码 */
    char InstrumentName[32];             /* 合约名称 */
    int TradeFlag;                       /* 交易标志 */
    double DealPrice;                    /* 成交价格 */
    int DealVolume;                      /* 成交数量 */
} QuerySecurityIntradayDealOutputItem;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* 结构大小 */
    int Id;                              /* 编号 */
    char ErrorMessage[100];              /* 错误消息 */

    int Count;                           /* 项目条数 */
    QuerySecurityIntradayDealOutputItem Items[];
} QuerySecurityIntradayDealOutput;
// 查询证券当日成交，获取证券成交列表。
RUSHQUANT_API BOOL rushquant_trade_QuerySecurityIntradayDeal(int accountId, const QuerySecurityIntradayDealInput* pInput, QuerySecurityIntradayDealOutput** pOutput);
#pragma endregion

#pragma region 查询证券历史成交 QuerySecurityHistoricalDeal
#pragma pack(1)
typedef struct
{
    int Id;                              /* 编号 */

    int BeginDate;                       /* 开始日期 */
    int EndDate;                         /* 终止日期 */
} QuerySecurityHistoricalDealInput;
#pragma pack(1)
typedef struct
{
    int DealDate;                        /* 成交日期 */
    int DealTime;                        /* 成交时间 */
    char DealID[20];                     /* 成交编号 */
    char StockholderCode[12];            /* 股东代码 */
    char ExchangeId[10];                 /* 交易所代码 */
    char InstrumentCode[16];             /* 合约代码 */
    char InstrumentName[32];             /* 合约名称 */
    int TradeFlag;                       /* 交易标志 */
    double DealPrice;                    /* 成交价格 */
    int DealVolume;                      /* 成交数量 */
} QuerySecurityHistoricalDealOutputItem;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* 结构大小 */
    int Id;                              /* 编号 */
    char ErrorMessage[100];              /* 错误消息 */

    int Count;                           /* 项目条数 */
    QuerySecurityHistoricalDealOutputItem Items[];
} QuerySecurityHistoricalDealOutput;
// 查询证券历史成交，获取证券成交列表。
RUSHQUANT_API BOOL rushquant_trade_QuerySecurityHistoricalDeal(int accountId, const QuerySecurityHistoricalDealInput* pInput, QuerySecurityHistoricalDealOutput** pOutput);
#pragma endregion

#pragma region 发送证券下单委托 PostSecuritySubmitOrder
#pragma pack(1)
typedef struct
{
    int Id;                              /* 编号 */

    char ExchangeId[10];                 /* 交易所代码 */
    char InstrumentCode[16];             /* 合约代码 */
    int TradeFlag;                       /* 交易标志 */
    double OrderPrice;                   /* 委托价格 */
    int OrderVolume;                     /* 委托数量 */
    int QuoteType;                       /* 报价类型 */

} PostSecuritySubmitOrderInput;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* 结构大小 */
    int Id;                              /* 编号 */
    char ErrorMessage[100];              /* 错误消息 */

    char OrderID[20];                    /* 委托编号 */
} PostSecuritySubmitOrderOutput;
// 发送证券下单委托，获得下单编号。
RUSHQUANT_API BOOL rushquant_trade_PostSecuritySubmitOrder(int accountId, const PostSecuritySubmitOrderInput* pInput, PostSecuritySubmitOrderOutput** pOutput);
#pragma endregion

#pragma region 发送证券撤单委托 PostSecurityCancelOrder
#pragma pack(1)
typedef struct
{
    int Id;                              /* 编号 */

    char ExchangeId[10];                 /* 交易所代码 */
    char OrderID[20];                    /* 委托编号 */
} PostSecurityCancelOrderInput;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* 结构大小 */
    int Id;                              /* 编号 */
    char ErrorMessage[100];              /* 错误消息 */

    char OrderID[20];                    /* 委托编号 */
} PostSecurityCancelOrderOutput;
// 发送证券撤单委托。
RUSHQUANT_API BOOL rushquant_trade_PostSecurityCancelOrder(int accountId, const PostSecurityCancelOrderInput* pInput, PostSecurityCancelOrderOutput** pOutput);
#pragma endregion
/********** trade End **********/


#pragma pack(pop)


#endif /* RUSHQUANT_H */