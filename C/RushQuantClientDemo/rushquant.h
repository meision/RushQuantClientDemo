#ifndef RUSHQUANT_H
#define RUSHQUANT_H

#ifdef RUSHQUANT_EXPORTS
#define RUSHQUANT_API __declspec(dllexport)
#else
#define RUSHQUANT_API __declspec(dllimport)
#endif

typedef int BOOL;

/********** constant BEGIN **********/
/* ��������� */
#define ExchangeId_SSE "SSE"         /* �Ϻ�֤ȯ������ */
#define ExchangeId_SZE "SZE"         /* ����֤ȯ������ */

/* ���Ҵ��� */
#define Currency_RMB 1                            /* ����� */
#define Currency_HKD 2                            /* �۱� */
#define Currency_USD 3                            /* ��Ԫ */

/* ���۷�ʽ */
#define QuoteType_SSE_LimitPrice 1                 /*�Ϻ�: �޼�ί��*/
#define QuoteType_SSE_FivePriceThenCancel 5        /*�Ϻ�: �嵵����ʣ��*/
#define QuoteType_SSE_FivePriceThenLimitPrice 7    /*�Ϻ�: �嵵����ת�޼�*/
#define QuoteType_SZE_LimitPrice 1                /* ����: �޼�ί�� */
#define QuoteType_SZE_CounterpartyBestPrice 2     /* ����: �Է����ż۸� */
#define QuoteType_SZE_BestPrice 3                 /* ����: �������ż۸� */
#define QuoteType_SZE_AnyPriceThenCancel 4        /* ����: ��ʱ�ɽ�ʣ�೷�� */
#define QuoteType_SZE_FivePriceThenCancel 5       /* ����: �嵵����ʣ�� */
#define QuoteType_SZE_AllPriceOrCancel 6          /* ����: ȫ��ɽ����� */

/* ���ױ�־ */
#define TradeFlag_Buy 1                 /* ���� */
#define TradeFlag_Sell 2                /* ���� */
#define TradeFlag_Purchase 3            /* �깺 */
#define TradeFlag_Redeem 4              /* ��� */
#define TradeFlag_MarginBuy 6           /* �������� */
#define TradeFlag_MarginSell 7          /* ��ȯ���� */
#define TradeFlag_MarginBuyCover 8      /* �����ۻ� */
#define TradeFlag_MarginSellCover 9     /* ��ȯ���� */
#define TradeFlag_ETFPurchase 11        /* ETF�깺 */
#define TradeFlag_ETFRedeem 12          /* ETF��� */
#define TradeFlag_FundPurchase 13       /* �����깺 */
#define TradeFlag_FundRedeem 14         /* ������� */
#define TradeFlag_GradedFundMerge 17    /* �ּ�����ϲ� */
#define TradeFlag_GradedFundSplit 18    /* �ּ�����ϲ� */
#define TradeFlag_FundSubscribe 19      /* �����Ϲ� */
#define TradeFlag_Placement 21          /* ���� */
#define TradeFlag_Distribution 22       /* ��� */
#define TradeFlag_CancelBuy -1          /* ���� */
#define TradeFlag_CancelSell -2         /* ���� */

/* ί��״̬ */
#define OrderStatus_Unorder 1                           /* δ�걨 */
#define OrderStatus_UndealtOrder 3                      /* ���걨δ�ɽ� */
#define OrderStatus_InvalidOrder 4                      /* �Ƿ�ί�� */
#define OrderStatus_PartialDealt 6                      /* ���ֳɽ� */
#define OrderStatus_AllDealt 7                          /* ȫ���ɽ� */
#define OrderStatus_PartialDealtPartialCancelled  8     /* ���ɲ��� */
#define OrderStatus_AllCancelled 9                      /* ȫ������ */
/********** constant END **********/

#pragma pack(push)

/********** manage BEGIN **********/
#pragma region ��ʼ�� initialize
// ϵͳ��ʼ����
RUSHQUANT_API BOOL rushquant_initialize(const char* pUsername, const char* pKey);
#pragma endregion

#pragma region �ͷ��ڴ� free
// �ͷ���ϵͳ���ɵ��ڴ档
RUSHQUANT_API void rushquant_free(void* pointer);
#pragma endregion

#pragma region ���� dispose
// ϵͳ���٣��ͷ���Դ��
RUSHQUANT_API BOOL rushquant_dispose();
#pragma endregion
/********** manage End **********/

/********** trade BEGIN **********/
#pragma region �˻��б� GetAccountList
// ��ȡ֧���˻�����б�, �����˻�������
RUSHQUANT_API int rushquant_trade_GetAccountList(int* accountIds);
#pragma endregion

#pragma region �˻����� Reset
// �����˻����������ָ���˻��Ѿ���¼��������������״̬�����˳�������״̬��
RUSHQUANT_API BOOL rushquant_trade_Reset(int accountId);
#pragma endregion

#pragma region ��һ��� NextId
// ��ȡϵͳ����һ����ţ���������������š�
RUSHQUANT_API int rushquant_trade_NextId();
#pragma endregion

#pragma region ��¼ Login
#pragma pack(1)
typedef struct
{
    int Id;                              /* ��� */

    char TradePassword[12];              /* �������� */
    char CommunicationPassword[12];      /* ͨѶ���� */
} LoginInput;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* �ṹ��С */
    int Id;                              /* ��� */
    char ErrorMessage[100];              /* ������Ϣ */
} LoginOutput;
// ��¼ָ�����ʻ���
RUSHQUANT_API BOOL rushquant_trade_Login(int accountId, const LoginInput* pInput, LoginOutput* pOutput);
#pragma endregion

#pragma region ��ѯTick���� QueryTickData
#pragma pack(1)
typedef struct
{
    int Id;                              /* ��� */

    char ExchangeId[10];                 /* ���������� */
    char InstrumentCode[16];             /* ��Լ���� */
} QueryTickDataInput;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* �ṹ��С */
    int Id;                              /* ��� */
    char ErrorMessage[100];              /* ������Ϣ */

    char ExchangeId[10];                 /* ���������� */
    char InstrumentCode[16];             /* ��Լ���� */
    char InstrumentName[32];             /* ��Լ���� */
    double PreClosePrice;                /* ���ռ� */
    double OpenPrice;                    /* �񿪼� */
    double LatestPrice;                  /* ��ǰ�� */
    double BidPrice1;                    /* ��һ�� */
    double BidPrice2;                    /* ����� */
    double BidPrice3;                    /* ������ */
    double BidPrice4;                    /* ���ļ� */
    double BidPrice5;                    /* ����� */
    int BidVolume1;                      /* ��һ�� */
    int BidVolume2;                      /* ����� */
    int BidVolume3;                      /* ������ */
    int BidVolume4;                      /* ������ */
    int BidVolume5;                      /* ������ */
    double AskPrice1;                    /* ��һ�� */
    double AskPrice2;                    /* ������ */
    double AskPrice3;                    /* ������ */
    double AskPrice4;                    /* ���ļ� */
    double AskPrice5;                    /* ����� */
    int AskVolume1;                      /* ��һ�� */
    int AskVolume2;                      /* ������ */
    int AskVolume3;                      /* ������ */
    int AskVolume4;                      /* ������ */
    int AskVolume5;                      /* ������ */
} QueryTickDataOutput;
// ��ѯ��Լ���嵵Tick�������ݡ�
RUSHQUANT_API BOOL rushquant_trade_QueryTickData(int accountId, const QueryTickDataInput* pInput, QueryTickDataOutput** pOutput);
#pragma endregion

#pragma region ��ѯ�ɶ���Ϣ QueryStockholderInfo
#pragma pack(1)
typedef struct
{
    int Id;                              /* ��� */
} QueryStockholderInfoInput;
#pragma pack(1)
typedef struct
{
    char StockholderCode[12];            /* �ɶ����� */
    char ExchangeId[10];                 /* ���������� */
} QueryStockholderInfoOutputItem;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* �ṹ��С */
    int Id;                              /* ��� */
    char ErrorMessage[100];              /* ������Ϣ */

    int Count;                           /* ��Ŀ���� */
    QueryStockholderInfoOutputItem Items[];
} QueryStockholderInfoOutput;
// ��ѯ�ɶ���Ϣ����ȡ����A�ɶ������б�
RUSHQUANT_API BOOL rushquant_trade_QueryStockholderInfo(int accountId, const QueryStockholderInfoInput* pInput, QueryStockholderInfoOutput** pOutput);
#pragma endregion

#pragma region ��ѯ֤ȯ�ʲ���Ϣ QuerySecurityCapitalInfo
#pragma pack(1)
typedef struct
{
    int Id;                              /* ��� */
} QuerySecurityCapitalInfoInput;
#pragma pack(1)
typedef struct
{
    int Currency;                        /* ���� */
    double RemainingCapitalAmount;       /* �ʽ���� */
    double AvailableCapitalAmount;       /* �����ʽ� */
    double WithdrawableCapitalAmount;    /* ��ȡ�ʽ� */
    double TotalAssetAmount;             /* ���ʲ� */
} QuerySecurityCapitalInfoOutputItem;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* �ṹ��С */
    int Id;                              /* ��� */
    char ErrorMessage[100];              /* ������Ϣ */

    int Count;                           /* ��Ŀ���� */
    QuerySecurityCapitalInfoOutputItem Items[];
} QuerySecurityCapitalInfoOutput;
// ��ѯ֤ȯ�ʲ���Ϣ����ȡ�˻����ʲ��б�
RUSHQUANT_API BOOL rushquant_trade_QuerySecurityCapitalInfo(int accountId, const QuerySecurityCapitalInfoInput* pInput, QuerySecurityCapitalInfoOutput** pOutput);
#pragma endregion

#pragma region ��ѯ֤ȯ�ֲ���Ϣ QuerySecurityPositionInfo
#pragma pack(1)
typedef struct
{
    int Id;                              /* ��� */
} QuerySecurityPositionInfoInput;
#pragma pack(1)
typedef struct
{
    char ExchangeId[10];                 /* ���������� */
    char InstrumentCode[16];             /* ��Լ���� */
    char InstrumentName[32];             /* ��Լ���� */
    int Volume;                          /* ֤ȯ���� */
    int AvailableVolume;                 /* �������� */
    char StockholderCode[12];            /* �ɶ����� */
} QuerySecurityPositionInfoOutputItem;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* �ṹ��С */
    int Id;                              /* ��� */
    char ErrorMessage[100];              /* ������Ϣ */

    int Count;                           /* ��Ŀ���� */
    QuerySecurityPositionInfoOutputItem Items[];
} QuerySecurityPositionInfoOutput;
// ��ѯ֤ȯ�ֲ���Ϣ����ȡ�˻��ĳֲ��б�
RUSHQUANT_API BOOL rushquant_trade_QuerySecurityPositionInfo(int accountId, const QuerySecurityPositionInfoInput* pInput, QuerySecurityPositionInfoOutput** pOutput);
#pragma endregion

#pragma region ��ѯ֤ȯί������ QuerySecurityOrderEvaluation
#pragma pack(1)
typedef struct
{
    int Id;                              /* ��� */

    char ExchangeId[10];                 /* ���������� */
    char InstrumentCode[16];             /* ��Լ���� */
    double OrderPrice;                   /* ί�м۸� */
    double LatestPrice;                  /* ���¼۸� */
    double CapitalAmount;                /* �ʽ��ܶ� */
} QuerySecurityOrderEvaluationInput;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* �ṹ��С */
    int Id;                              /* ��� */
    char ErrorMessage[100];              /* ������Ϣ */

    double BidableVolume;                /* �������� */
} QuerySecurityOrderEvaluationOutput;
// ��ѯ֤ȯί����������ȡ��ǰ�����ʽ�������ָ��֤ȯ��ί��������
RUSHQUANT_API BOOL rushquant_trade_QuerySecurityOrderEvaluation(int accountId, const QuerySecurityOrderEvaluationInput* pInput, QuerySecurityOrderEvaluationOutput** pOutput);
#pragma endregion

#pragma region ��ѯ֤ȯ����ί�� QuerySecurityIntradayOrder
#pragma pack(1)
typedef struct
{
    int Id;                              /* ��� */
} QuerySecurityIntradayOrderInput;
#pragma pack(1)
typedef struct
{
    int OrderDate;                       /* ί������ */
    int OrderTime;                       /* ί��ʱ�� */
    char OrderID[20];                    /* ί�б�� */
    char StockholderCode[12];            /* �ɶ����� */
    char ExchangeId[10];                 /* ���������� */
    char InstrumentCode[16];             /* ��Լ���� */
    char InstrumentName[32];             /* ��Լ���� */
    int TradeFlag;                       /* ���ױ�־ */
    double OrderPrice;                   /* ί�м۸� */
    int OrderVolume;                     /* ί������ */
    double DealPrice;                    /* �ɽ����� */
    int DealVolume;                      /* �ɽ����� */
    int CancelVolume;                    /* �������� */
    int QuoteType;                       /* �������� */
    int OrderStatus;                     /* ״̬ */
} QuerySecurityIntradayOrderOutputItem;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* �ṹ��С */
    int Id;                              /* ��� */
    char ErrorMessage[100];              /* ������Ϣ */

    int Count;                           /* ��Ŀ���� */
    QuerySecurityIntradayOrderOutputItem Items[];
} QuerySecurityIntradayOrderOutput;
// ��ѯ֤ȯ����ί�У���ȡ֤ȯί���б�
RUSHQUANT_API BOOL rushquant_trade_QuerySecurityIntradayOrder(int accountId, const QuerySecurityIntradayOrderInput* pInput, QuerySecurityIntradayOrderOutput** pOutput);
#pragma endregion

#pragma region ��ѯ֤ȯ��ʷί�� QuerySecurityHistoricalOrder
#pragma pack(1)
typedef struct
{
    int Id;                              /* ��� */

    int BeginDate;                       /* ��ʼ���� */
    int EndDate;                         /* ��ֹ���� */
} QuerySecurityHistoricalOrderInput;
#pragma pack(1)
typedef struct
{
    int OrderDate;                       /* ί������ */
    int OrderTime;                       /* ί��ʱ�� */
    char OrderID[20];                    /* ί�б�� */
    char StockholderCode[12];            /* �ɶ����� */
    char ExchangeId[10];                 /* ���������� */
    char InstrumentCode[16];             /* ��Լ���� */
    char InstrumentName[32];             /* ��Լ���� */
    int TradeFlag;                       /* ���ױ�־ */
    double OrderPrice;                   /* ί�м۸� */
    int OrderVolume;                     /* ί������ */
    int DealVolume;                      /* �ɽ����� */
    double DealAmount;                   /* �ɽ���� */
    int CancelVolume;                    /* �������� */
    int QuoteType;                       /* �������� */
    int OrderStatus;                     /* ״̬ */
} QuerySecurityHistoricalOrderOutputItem;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* �ṹ��С */
    int Id;                              /* ��� */
    char ErrorMessage[100];              /* ������Ϣ */

    int Count;                           /* ��Ŀ���� */
    QuerySecurityHistoricalOrderOutputItem Items[];
} QuerySecurityHistoricalOrderOutput;
// ��ѯ֤ȯ��ʷί�У���ȡ֤ȯί���б�
RUSHQUANT_API BOOL rushquant_trade_QuerySecurityHistoricalOrder(int accountId, const QuerySecurityHistoricalOrderInput* pInput, QuerySecurityHistoricalOrderOutput** pOutput);
#pragma endregion

#pragma region ��ѯ֤ȯ���ճɽ� QuerySecurityIntradayDeal
#pragma pack(1)
typedef struct
{
    int Id;                              /* ��� */
} QuerySecurityIntradayDealInput;
#pragma pack(1)
typedef struct
{
    int DealDate;                        /* �ɽ����� */
    int DealTime;                        /* �ɽ�ʱ�� */
    char DealID[20];                     /* �ɽ���� */
    char OrderID[20];                    /* ί�б�� */
    char QuoteNumber[20];                /* �걨��� */
    char StockholderCode[12];            /* �ɶ����� */
    char ExchangeId[10];                 /* ���������� */
    char InstrumentCode[16];             /* ��Լ���� */
    char InstrumentName[32];             /* ��Լ���� */
    int TradeFlag;                       /* ���ױ�־ */
    double DealPrice;                    /* �ɽ��۸� */
    int DealVolume;                      /* �ɽ����� */
} QuerySecurityIntradayDealOutputItem;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* �ṹ��С */
    int Id;                              /* ��� */
    char ErrorMessage[100];              /* ������Ϣ */

    int Count;                           /* ��Ŀ���� */
    QuerySecurityIntradayDealOutputItem Items[];
} QuerySecurityIntradayDealOutput;
// ��ѯ֤ȯ���ճɽ�����ȡ֤ȯ�ɽ��б�
RUSHQUANT_API BOOL rushquant_trade_QuerySecurityIntradayDeal(int accountId, const QuerySecurityIntradayDealInput* pInput, QuerySecurityIntradayDealOutput** pOutput);
#pragma endregion

#pragma region ��ѯ֤ȯ��ʷ�ɽ� QuerySecurityHistoricalDeal
#pragma pack(1)
typedef struct
{
    int Id;                              /* ��� */

    int BeginDate;                       /* ��ʼ���� */
    int EndDate;                         /* ��ֹ���� */
} QuerySecurityHistoricalDealInput;
#pragma pack(1)
typedef struct
{
    int DealDate;                        /* �ɽ����� */
    int DealTime;                        /* �ɽ�ʱ�� */
    char DealID[20];                     /* �ɽ���� */
    char StockholderCode[12];            /* �ɶ����� */
    char ExchangeId[10];                 /* ���������� */
    char InstrumentCode[16];             /* ��Լ���� */
    char InstrumentName[32];             /* ��Լ���� */
    int TradeFlag;                       /* ���ױ�־ */
    double DealPrice;                    /* �ɽ��۸� */
    int DealVolume;                      /* �ɽ����� */
} QuerySecurityHistoricalDealOutputItem;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* �ṹ��С */
    int Id;                              /* ��� */
    char ErrorMessage[100];              /* ������Ϣ */

    int Count;                           /* ��Ŀ���� */
    QuerySecurityHistoricalDealOutputItem Items[];
} QuerySecurityHistoricalDealOutput;
// ��ѯ֤ȯ��ʷ�ɽ�����ȡ֤ȯ�ɽ��б�
RUSHQUANT_API BOOL rushquant_trade_QuerySecurityHistoricalDeal(int accountId, const QuerySecurityHistoricalDealInput* pInput, QuerySecurityHistoricalDealOutput** pOutput);
#pragma endregion

#pragma region ����֤ȯ�µ�ί�� PostSecuritySubmitOrder
#pragma pack(1)
typedef struct
{
    int Id;                              /* ��� */

    char ExchangeId[10];                 /* ���������� */
    char InstrumentCode[16];             /* ��Լ���� */
    int TradeFlag;                       /* ���ױ�־ */
    double OrderPrice;                   /* ί�м۸� */
    int OrderVolume;                     /* ί������ */
    int QuoteType;                       /* �������� */

} PostSecuritySubmitOrderInput;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* �ṹ��С */
    int Id;                              /* ��� */
    char ErrorMessage[100];              /* ������Ϣ */

    char OrderID[20];                    /* ί�б�� */
} PostSecuritySubmitOrderOutput;
// ����֤ȯ�µ�ί�У�����µ���š�
RUSHQUANT_API BOOL rushquant_trade_PostSecuritySubmitOrder(int accountId, const PostSecuritySubmitOrderInput* pInput, PostSecuritySubmitOrderOutput** pOutput);
#pragma endregion

#pragma region ����֤ȯ����ί�� PostSecurityCancelOrder
#pragma pack(1)
typedef struct
{
    int Id;                              /* ��� */

    char ExchangeId[10];                 /* ���������� */
    char OrderID[20];                    /* ί�б�� */
} PostSecurityCancelOrderInput;
#pragma pack(1)
typedef struct
{
    unsigned int Size;                   /* �ṹ��С */
    int Id;                              /* ��� */
    char ErrorMessage[100];              /* ������Ϣ */

    char OrderID[20];                    /* ί�б�� */
} PostSecurityCancelOrderOutput;
// ����֤ȯ����ί�С�
RUSHQUANT_API BOOL rushquant_trade_PostSecurityCancelOrder(int accountId, const PostSecurityCancelOrderInput* pInput, PostSecurityCancelOrderOutput** pOutput);
#pragma endregion
/********** trade End **********/


#pragma pack(pop)


#endif /* RUSHQUANT_H */