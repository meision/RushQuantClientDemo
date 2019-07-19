#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "const.h"
#include "rushquant.h"


#pragma comment(lib,"RushQuantClient64.lib")

typedef unsigned char Byte;

#define DYNAMIC_DATA

static char* __username;
static char* __key;
static int __accountId;
static char* __password;

char* CopyString(char *pDestination, const char *pSource)
{
    char *s = pDestination;
    while ((*s++ = *pSource++) != 0)
        ;
    return (pDestination);
}


char* GetQuoteType(char* exchangeId, int quoteType)
{
    if (strcmp(exchangeId, "SSE") == 0)
    {
        switch (quoteType)
        {
            case QuoteType_SSE_LimitPrice:
                return "1-限价委托";
            case QuoteType_SSE_FivePriceThenCancel:
                return "5-五档即成剩撤";
            case QuoteType_SSE_FivePriceThenLimitPrice:
                return "7-五档即成转限价";
            default:
                return "0-未知";
        }
    }
    else if (strcmp(exchangeId, "SZE") == 0)
    {
        switch (quoteType)
        {
            case QuoteType_SZE_LimitPrice:
                return "1-限价委托";
            case QuoteType_SZE_CounterpartyBestPrice:
                return "2-对方最优价格";
            case QuoteType_SZE_BestPrice:
                return "3-本方最优价格";
            case QuoteType_SZE_AnyPriceThenCancel:
                return "4-即时成交剩余撤销";
            case QuoteType_SZE_FivePriceThenCancel:
                return "5-五档即成剩撤";
            case QuoteType_SZE_AllPriceOrCancel:
                return "6-全额成交或撤销";
            default:
                return "0-未知";
        }
    }
    else
    {
        return "0-未知";
    }
}

char* GetTradeFlagText(int tradeFlag)
{
    switch (tradeFlag)
    {
        case TradeFlag_Buy:
            return "1-买入";
        case TradeFlag_Sell:
            return "2-卖出";
        case TradeFlag_Purchase:
            return "3-申购";
        case TradeFlag_Redeem:
            return "4-赎回";
        case TradeFlag_MarginBuy:
            return "6-融资买入";
        case TradeFlag_MarginSell:
            return "7-融券卖出";
        case TradeFlag_MarginBuyCover:
            return "8-融资售回";
        case TradeFlag_MarginSellCover:
            return "9-融券购回";
        case TradeFlag_ETFPurchase:
            return "11-ETF申购";
        case TradeFlag_ETFRedeem:
            return "12-ETF赎回";
        case TradeFlag_FundPurchase:
            return "13-基金申购";
        case TradeFlag_FundRedeem:
            return "14-基金赎回";
        case TradeFlag_GradedFundMerge:
            return "17-分级基金合并";
        case TradeFlag_GradedFundSplit:
            return "18-分级基金合拆";
        case TradeFlag_FundSubscribe:
            return "19-基金认购";
        case TradeFlag_Placement:
            return "21-配售";
        case TradeFlag_Distribution:
            return "22-配号";
        case TradeFlag_CancelBuy:
            return "-1-撤买";
        case TradeFlag_CancelSell:
            return "-2-撤卖";
        default:
            return "0-未知";
    }
}

char* GetStatusText(int status)
{
    switch (status)
    {
        case OrderStatus_Unorder:
            return "1-未申报";
        case OrderStatus_UndealtOrder:
            return "3-已申报未成交";
        case OrderStatus_InvalidOrder:
            return "4-非法委托";
        case OrderStatus_PartialDealt:
            return "6-部分成交";
        case OrderStatus_AllDealt:
            return "7-全部成交";
        case OrderStatus_PartialDealtPartialCancelled:
            return "8-部成部撤";
        case OrderStatus_AllCancelled:
            return "9-全部撤单";
        default:
            return "0-未知";
    }
}

void test_QueryTickData()
{
    printf("******* QueryTickData BEGIN *********\n");

    QueryTickDataInput input = { 0 };
    CopyString(input.ExchangeId, "SSE");
    CopyString(input.InstrumentCode, "601288");

#ifdef DYNAMIC_DATA
    QueryTickDataOutput* pOutput = NULL;
#else
    Byte buffer[50000];
    QueryTickDataOutput* pOutput = (QueryTickDataOutput*)buffer;
    pOutput->Size = sizeof(buffer);
#endif

    int result = rushquant_trade_QueryTickData(__accountId, &input, &pOutput);
    if (result != Error_Success)
    {
        printf("%d: %s\n", result, pOutput->ErrorMessage);
        printf("******* QueryTickData END *********\n");
        printf("\n");
        return;
    }

    QueryTickDataOutput* pItem = pOutput;
    printf("交易所名称:%s, 合约代码:%s, 合约名称:%s\n卖五: %-10.4f %d\n卖四: %-10.4f %d\n卖三: %-10.4f %d\n卖二: %-10.4f %d\n卖一: %-10.4f %d\n买一: %-10.4f %d\n买二: %-10.4f %d\n买三: %-10.4f %d\n买四: %-10.4f %d\n买五: %-10.4f %d\n",
        pItem->ExchangeId, pItem->InstrumentCode, pItem->InstrumentName,
        pItem->AskPrice5, pItem->AskVolume5,
        pItem->AskPrice4, pItem->AskVolume4,
        pItem->AskPrice3, pItem->AskVolume3,
        pItem->AskPrice2, pItem->AskVolume2,
        pItem->AskPrice1, pItem->AskVolume1,

        pItem->BidPrice1, pItem->BidVolume1,
        pItem->BidPrice2, pItem->BidVolume2,
        pItem->BidPrice3, pItem->BidVolume3,
        pItem->BidPrice4, pItem->BidVolume4,
        pItem->BidPrice5, pItem->BidVolume5);
    printf("******* QueryTickData END *********\n");
    printf("\n");

#ifdef DYNAMIC_DATA
    rushquant_free(pOutput);
#endif
}

void test_QueryStockholderInfo()
{
    printf("******* QueryStockholderInfo BEGIN *********\n");

    QueryStockholderInfoInput input = { 0 };

#ifdef DYNAMIC_DATA
    QueryStockholderInfoOutput* pOutput = NULL;
#else
    Byte buffer[50000];
    QueryStockholderInfoOutput* pOutput = (QueryStockholderInfoOutput*)buffer;
    pOutput->Size = sizeof(buffer);
#endif

    int result = rushquant_trade_QueryStockholderInfo(__accountId, &input, &pOutput);
    if (result != Error_Success)
    {
        printf("%d: %s\n", result, pOutput->ErrorMessage);
        printf("******* QueryStockholderInfo END *********\n");
        printf("\n");
        return;
    }

    printf("%-20s\t%-20s\n", "交易所名称", "股东代码");
    for (int i = 0; i < pOutput->Count; i++)
    {
        QueryStockholderInfoOutputItem* pItem = pOutput->Items + i;
        printf("%-20s\t%-20s\n", pItem->ExchangeId, pItem->StockholderCode);
    }
    printf("******* QueryStockholderInfo END *********\n");
    printf("\n");

#ifdef DYNAMIC_DATA
    rushquant_free(pOutput);
#endif
}

void test_QuerySecurityCapitalInfo()
{
    printf("******* QuerySecurityCapitalInfo BEGIN *********\n");

    QuerySecurityCapitalInfoInput input = { 0 };

#ifdef DYNAMIC_DATA
    QuerySecurityCapitalInfoOutput* pOutput = NULL;
#else
    Byte buffer[50000];
    QuerySecurityCapitalInfoOutput* pOutput = (QuerySecurityCapitalInfoOutput*)buffer;
    pOutput->Size = sizeof(buffer);
#endif

    int result = rushquant_trade_QuerySecurityCapitalInfo(__accountId, &input, &pOutput);
    if (result != Error_Success)
    {
        printf("%d: %s\n", result, pOutput->ErrorMessage);
        printf("******* QuerySecurityCapitalInfo END *********\n");
        printf("\n");
        return;
    }

    printf("%-20s\t%-20s\t%-20s\t%-20s\t%-20s\n", "币种", "资金余额", "可用资金", "可取资金", "总资产");
    for (int i = 0; i < pOutput->Count; i++)
    {
        QuerySecurityCapitalInfoOutputItem* pItem = pOutput->Items + i;
        printf("%-20d\t%-20.4f\t%-20.4f\t%-20.4f\t%-20.4f\n", pItem->Currency, pItem->RemainingCapitalAmount, pItem->AvailableCapitalAmount, pItem->WithdrawableCapitalAmount, pItem->TotalAssetAmount);
    }
    printf("******* QuerySecurityCapitalInfo END *********\n");
    printf("\n");

#ifdef DYNAMIC_DATA
    rushquant_free(pOutput);
#endif
}

void test_QuerySecurityPositionInfo()
{
    printf("******* QuerySecurityPositionInfo BEGIN *********\n");

    QuerySecurityPositionInfoInput input = { 0 };

#ifdef DYNAMIC_DATA
    QuerySecurityPositionInfoOutput* pOutput = NULL;
#else
    Byte buffer[50000];
    QuerySecurityPositionInfoOutput* pOutput = (QuerySecurityPositionInfoOutput*)buffer;
    pOutput->Size = sizeof(buffer);
#endif

    int result = rushquant_trade_QuerySecurityPositionInfo(__accountId, &input, &pOutput);
    if (result != Error_Success)
    {
        printf("%d: %s\n", result, pOutput->ErrorMessage);
        printf("******* QuerySecurityPositionInfo END *********\n");
        printf("\n");
        return;
    }

    printf("%-10s\t%-20s\t%-20s\t%-20s\t%-20s\t%-20s\n", "交易所名称", "合约代码", "合约名称", "数量", "可卖数量", "股东代码");
    for (int i = 0; i < pOutput->Count; i++)
    {
        QuerySecurityPositionInfoOutputItem* pItem = pOutput->Items + i;
        printf("%-10s\t%-20s\t%-20s\t%-20d\t%-20d\t%-20s\n", pItem->ExchangeId, pItem->InstrumentCode, pItem->InstrumentName, pItem->Volume, pItem->AvailableVolume, pItem->StockholderCode);
    }
    printf("******* QuerySecurityPositionInfo END *********\n");
    printf("\n");

#ifdef DYNAMIC_DATA
    rushquant_free(pOutput);
#endif
}

void test_QuerySecurityIntradayOrder()
{
    printf("******* QuerySecurityIntradayOrder BEGIN *********\n");

    QuerySecurityIntradayOrderInput input = { 0 };

#ifdef DYNAMIC_DATA
    QuerySecurityIntradayOrderOutput* pOutput = NULL;
#else
    Byte buffer[50000];
    QuerySecurityIntradayOrderOutput* pOutput = (QuerySecurityIntradayOrderOutput*)buffer;
    pOutput->Size = sizeof(buffer);
#endif

    int result = rushquant_trade_QuerySecurityIntradayOrder(__accountId, &input, &pOutput);
    if (result != Error_Success)
    {
        printf("%d: %s\n", result, pOutput->ErrorMessage);
        printf("******* QuerySecurityIntradayOrder END *********\n");
        printf("\n");
        return;
    }

    printf("%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n", "委托日期", "委托时间", "委托编号", "股东代码", "交易所代码", "合约代码", "合约名称", "交易标志", "委托价格", "委托数量", "成交价格", "成交数量", "撤单数量", "报价类型", "状态");
    for (int i = 0; i < pOutput->Count; i++)
    {
        QuerySecurityIntradayOrderOutputItem* pItem = pOutput->Items + i;
        printf("%-15d\t%-15d\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15.4f\t%-15d\t%-15.4f\t%-15d\t%-15d\t%-15s\t%-15s\n",
            pItem->OrderDate,
            pItem->OrderTime,
            pItem->OrderID,
            pItem->StockholderCode,
            pItem->ExchangeId,

            pItem->InstrumentCode,
            pItem->InstrumentName,
            GetTradeFlagText(pItem->TradeFlag),
            pItem->OrderPrice,
            pItem->OrderVolume,
            pItem->DealPrice,
            pItem->DealVolume,
            pItem->CancelVolume,
            GetQuoteType(pItem->ExchangeId, pItem->QuoteType),
            GetStatusText(pItem->OrderStatus));

    }
    printf("******* QuerySecurityIntradayOrder END *********\n");
    printf("\n");

#ifdef DYNAMIC_DATA
    rushquant_free(pOutput);
#endif
}

void test_QuerySecurityHistoricalOrder()
{
    printf("******* QuerySecurityHistoricalOrder BEGIN *********\n");

    QuerySecurityHistoricalOrderInput input = { 0 };
    input.BeginDate = 20181226;
    input.EndDate = 20181231;

#ifdef DYNAMIC_DATA
    QuerySecurityHistoricalOrderOutput* pOutput = NULL;
#else
    Byte buffer[50000];
    QuerySecurityHistoricalOrderOutput* pOutput = (QuerySecurityHistoricalOrderOutput*)buffer;
    pOutput->Size = sizeof(buffer);
#endif

    int result = rushquant_trade_QuerySecurityHistoricalOrder(__accountId, &input, &pOutput);
    if (result != Error_Success)
    {
        printf("%d: %s\n", result, pOutput->ErrorMessage);
        printf("******* QuerySecurityHistoricalOrder END *********\n");
        printf("\n");
        return;
    }

    printf("%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n", "委托日期", "委托时间", "委托编号", "股东代码", "交易所代码", "合约代码", "合约名称", "交易标志", "委托价格", "委托数量", "成交数量", "撤单数量", "报价类型", "状态");
    for (int i = 0; i < pOutput->Count; i++)
    {
        QuerySecurityHistoricalOrderOutputItem* pItem = pOutput->Items + i;
        printf("%-15d\t%-15d\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15.4f\t%-15d\t%-15d\t%-15d\t%-15s\t%-15s\n",
            pItem->OrderDate,
            pItem->OrderTime,
            pItem->OrderID,
            pItem->StockholderCode,
            pItem->ExchangeId,

            pItem->InstrumentCode,
            pItem->InstrumentName,
            GetTradeFlagText(pItem->TradeFlag),
            pItem->OrderPrice,
            pItem->OrderVolume,

            pItem->DealVolume,
            pItem->CancelVolume,
            GetQuoteType(pItem->ExchangeId, pItem->QuoteType),
            GetStatusText(pItem->OrderStatus));

    }
    printf("******* QuerySecurityHistoricalOrder END *********\n");
    printf("\n");

#ifdef DYNAMIC_DATA
    rushquant_free(pOutput);
#endif
}

void test_QuerySecurityIntradayDeal()
{
    printf("******* QuerySecurityIntradayDeal BEGIN *********\n");

    QuerySecurityIntradayDealInput input = { 0 };

#ifdef DYNAMIC_DATA
    QuerySecurityIntradayDealOutput* pOutput = NULL;
#else
    Byte buffer[50000];
    QuerySecurityIntradayDealOutput* pOutput = (QuerySecurityIntradayDealOutput*)buffer;
    pOutput->Size = sizeof(buffer);
#endif

    int result = rushquant_trade_QuerySecurityIntradayDeal(__accountId, &input, &pOutput);
    if (result != Error_Success)
    {
        printf("%d: %s\n", result, pOutput->ErrorMessage);
        printf("******* QuerySecurityIntradayDeal END *********\n");
        printf("\n");
        return;
    }

    printf("%-15s\t%-15s\t%-25s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n", "成交时间", "成交编号", "委托编号", "申报编号", "股东代码", "交易所代码", "合约代码", "合约名称", "交易标志", "成交价格", "成交数量");
    for (int i = 0; i < pOutput->Count; i++)
    {
        QuerySecurityIntradayDealOutputItem* pItem = pOutput->Items + i;
        printf("%-15d\t%-15s\t%-25s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15.4f\t%-15d\n",
            pItem->DealTime,
            pItem->DealID,
            pItem->OrderID,
            pItem->QuoteNumber,

            pItem->StockholderCode,
            pItem->ExchangeId,
            pItem->InstrumentCode,
            pItem->InstrumentName,

            GetTradeFlagText(pItem->TradeFlag),
            pItem->DealPrice,
            pItem->DealVolume);
    }
    printf("******* QuerySecurityIntradayDeal END *********\n");
    printf("\n");

#ifdef DYNAMIC_DATA
    rushquant_free(pOutput);
#endif
}

void test_QuerySecurityHistoricalDeal()
{
    printf("******* QuerySecurityHistoricalDeal BEGIN *********\n");

    QuerySecurityHistoricalDealInput input = { 0 };
    input.BeginDate = 20181212;
    input.EndDate = 20181213;

#ifdef DYNAMIC_DATA
    QuerySecurityHistoricalDealOutput* pOutput = NULL;
#else
    Byte buffer[50000];
    QuerySecurityHistoricalDealOutput* pOutput = (QuerySecurityHistoricalDealOutput*)buffer;
    pOutput->Size = sizeof(buffer);
#endif

    int result = rushquant_trade_QuerySecurityHistoricalDeal(__accountId, &input, &pOutput);
    if (result != Error_Success)
    {
        printf("%d: %s\n", result, pOutput->ErrorMessage);
        printf("******* QuerySecurityHistoricalDeal END *********\n");
        printf("\n");
        return;
    }

    printf("%-15s\t%-15s\t%-25s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n", "成交日期", "成交时间", "成交编号", "股东代码", "交易所代码", "合约代码", "合约名称", "交易标志", "成交价格", "成交数量");
    for (int i = 0; i < pOutput->Count; i++)
    {
        QuerySecurityHistoricalDealOutputItem* pItem = pOutput->Items + i;
        printf("%-15d\t%-15d\t%-25s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15.4f\t%-15d\n",
            pItem->DealDate,
            pItem->DealTime,
            pItem->DealID,

            pItem->StockholderCode,
            pItem->ExchangeId,
            pItem->InstrumentCode,
            pItem->InstrumentName,

            GetTradeFlagText(pItem->TradeFlag),
            pItem->DealPrice,
            pItem->DealVolume);

    }
    printf("******* QuerySecurityHistoricalDeal END *********\n");
    printf("\n");

#ifdef DYNAMIC_DATA
    rushquant_free(pOutput);
#endif
}

void test_QuerySecurityOrderEvaluation()
{
    printf("******* QueryTickData BEGIN *********\n");

    QuerySecurityOrderEvaluationInput input = { 0 };
    CopyString(input.ExchangeId, "SSE");
    CopyString(input.InstrumentCode, "601288");
    input.LatestPrice = 3.52;
    input.CapitalAmount = 53612.15;

#ifdef DYNAMIC_DATA
    QuerySecurityOrderEvaluationOutput* pOutput = NULL;
#else
    Byte buffer[50000];
    QuerySecurityOrderEvaluationOutput* pOutput = (QuerySecurityOrderEvaluationOutput*)buffer;
    pOutput->Size = sizeof(buffer);
#endif

    int result = rushquant_trade_QuerySecurityOrderEvaluation(__accountId, &input, &pOutput);
    if (result != Error_Success)
    {
        printf("%d: %s\n", result, pOutput->ErrorMessage);
        printf("******* QuerySecurityOrderEvaluation END *********\n");
        printf("\n");
        return;
    }

    QuerySecurityOrderEvaluationOutput* pItem = pOutput;
    printf("可买数量:%.0f\n",
        pItem->BidableVolume);
    printf("******* QuerySecurityOrderEvaluation END *********\n");
    printf("\n");

#ifdef DYNAMIC_DATA
    rushquant_free(pOutput);
#endif
}

void test_PostSecuritySubmitOrder()
{
    printf("******* PostSecuritySubmitOrder BEGIN *********\n");

    PostSecuritySubmitOrderInput input = { 0 };
    CopyString(input.ExchangeId, "SSE");
    CopyString(input.InstrumentCode, "601288");
    input.TradeFlag = TradeFlag_Buy;
    input.QuoteType = QuoteType_SSE_LimitPrice;
    input.OrderPrice = 3.42;
    input.OrderVolume = 100;

#ifdef DYNAMIC_DATA
    PostSecuritySubmitOrderOutput* pOutput = NULL;
#else
    Byte buffer[50000];
    PostSecuritySubmitOrderOutput* pOutput = (PostSecuritySubmitOrderOutput*)buffer;
    pOutput->Size = sizeof(buffer);
#endif

    int result = rushquant_trade_PostSecuritySubmitOrder(__accountId, &input, &pOutput);
    if (result != Error_Success)
    {
        printf("%d: %s\n", result, pOutput->ErrorMessage);
        printf("******* PostSecuritySubmitOrder END *********\n");
        printf("\n");
        return;
    }

    PostSecuritySubmitOrderOutput* pItem = pOutput;
    printf("委托编号: %s\n",
        pItem->OrderID);
    printf("******* PostSecuritySubmitOrder END *********\n");
    printf("\n");

#ifdef DYNAMIC_DATA
    rushquant_free(pOutput);
#endif
}

void test_PostSecuritySubmitOrder_NotReturn()
{
    //printf("******* PostSecuritySubmitOrder BEGIN *********\n");

    PostSecuritySubmitOrderInput input = { 0 };
    CopyString(input.ExchangeId, "SSE");
    CopyString(input.InstrumentCode, "601288");
    input.TradeFlag = TradeFlag_Buy;
    input.QuoteType = QuoteType_SSE_LimitPrice;
    input.OrderPrice = 3.25;
    input.OrderVolume = 100;

    int result = rushquant_trade_PostSecuritySubmitOrder(__accountId, &input, NULL);
    if (result != Error_Success)
    {
        printf("%d\n", result);
        printf("******* PostSecuritySubmitOrder END *********\n");
        printf("\n");
        return;
    }

    //printf("******* PostSecuritySubmitOrder END *********\n");
    //printf("\n");
}

void test_PostSecuritySubmitOrder_Purchase()
{
    printf("******* PostSecuritySubmitOrder BEGIN *********\n");

    PostSecuritySubmitOrderInput input = { 0 };
    CopyString(input.ExchangeId, "SSE");
    CopyString(input.InstrumentCode, "511851");
    input.TradeFlag = TradeFlag_Purchase;
    input.QuoteType = QuoteType_SSE_LimitPrice;
    input.OrderPrice = 1.0;
    input.OrderVolume = 100;

#ifdef DYNAMIC_DATA
    PostSecuritySubmitOrderOutput* pOutput = NULL;
#else
    Byte buffer[50000];
    PostSecuritySubmitOrderOutput* pOutput = (PostSecuritySubmitOrderOutput*)buffer;
    pOutput->Size = sizeof(buffer);
#endif

    int result = rushquant_trade_PostSecuritySubmitOrder(__accountId, &input, &pOutput);
    if (result != Error_Success)
    {
        printf("%d: %s\n", result, pOutput->ErrorMessage);
        printf("******* PostSecuritySubmitOrder END *********\n");
        printf("\n");
        return;
    }

    PostSecuritySubmitOrderOutput* pItem = pOutput;
    printf("委托编号: %s\n",
        pItem->OrderID);
    printf("******* PostSecuritySubmitOrder END *********\n");
    printf("\n");

#ifdef DYNAMIC_DATA
    rushquant_free(pOutput);
#endif
}

void test_PostSecurityCancelOrder()
{
    printf("******* PostSecurityCancelOrder BEGIN *********\n");

    PostSecurityCancelOrderInput input = { 0 };
    CopyString(input.ExchangeId, "SZE");
    CopyString(input.OrderID, "6080");

#ifdef DYNAMIC_DATA
    PostSecurityCancelOrderOutput* pOutput = NULL;
#else
    Byte buffer[50000];
    PostSecurityCancelOrderOutput* pOutput = (PostSecurityCancelOrderOutput*)buffer;
    pOutput->Size = sizeof(buffer);
#endif

    int result = rushquant_trade_PostSecurityCancelOrder(__accountId, &input, &pOutput);
    if (result != Error_Success)
    {
        printf("%d: %s\n", result, pOutput->ErrorMessage);
        printf("******* PostSecurityCancelOrder END *********\n");
        printf("\n");
        return;
    }

    PostSecurityCancelOrderOutput* pItem = pOutput;
    //printf("委托编号: %s\n",
    //    pItem->OrderID);
    printf("******* PostSecurityCancelOrder END *********\n");
    printf("\n");

#ifdef DYNAMIC_DATA
    rushquant_free(pOutput);
#endif
}

int main(int argc, char* argv[])
{
    // TODO: Read config from args
    if (argc == 5)
    {
        __username = argv[1]; // 比如'jimcai'。
        __key = argv[2]; // 从Rushquant网站获取。
        __accountId = atoi(argv[3]); // 要操作的账户id，为末尾5位。
        __password = argv[4]; // 要操作的账户交易密码。
    }
    else
    {
        return -1;
    }

    int result;
    // initialize
    result = rushquant_initialize(__username, __key);
    if (result != Error_Success)
    {
        printf("Initialize Error: %d", result);
        return result;
    }

    int accountId[1000];
    int count = rushquant_trade_GetAccountList(accountId);


    // reset account
    result = rushquant_trade_Reset(__accountId);
    if (result != Error_Success)
    {
        printf("Reset Error: %d", result);
        return result;
    }
    // Login
    LoginInput input = { 0 };
    // 设置交易密码
    CopyString(input.TradePassword, __password);
    LoginOutput output = { 0 };
    result = rushquant_trade_Login(__accountId, &input, &output);
    if (result != Error_Success)
    {
        printf("Login Error: %d, Message: %s", result, output.ErrorMessage);
        return result;
    }

    test_QueryTickData();
    test_QueryStockholderInfo();
    test_QuerySecurityCapitalInfo();
    test_QuerySecurityPositionInfo();
    test_QuerySecurityIntradayOrder();
    test_QuerySecurityHistoricalOrder();
    test_QuerySecurityIntradayDeal();
    test_QuerySecurityHistoricalDeal();
    test_QuerySecurityOrderEvaluation();
    //test_PostSecuritySubmitOrder();
    //test_PostSecuritySubmitOrder();
    //test_PostSecuritySubmitOrder_Purchase();
    //test_PostSecurityCancelOrder();

   //for (int i = 0; i < 5; i++)
   // {
   //     test_PostSecuritySubmitOrder_NotReturn();
   //     //sleep(10);
   // }

    rushquant_dispose();

    system("pause");
    return 0;
}