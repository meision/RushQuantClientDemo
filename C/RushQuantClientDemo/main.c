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
                return "1-�޼�ί��";
            case QuoteType_SSE_FivePriceThenCancel:
                return "5-�嵵����ʣ��";
            case QuoteType_SSE_FivePriceThenLimitPrice:
                return "7-�嵵����ת�޼�";
            default:
                return "0-δ֪";
        }
    }
    else if (strcmp(exchangeId, "SZE") == 0)
    {
        switch (quoteType)
        {
            case QuoteType_SZE_LimitPrice:
                return "1-�޼�ί��";
            case QuoteType_SZE_CounterpartyBestPrice:
                return "2-�Է����ż۸�";
            case QuoteType_SZE_BestPrice:
                return "3-�������ż۸�";
            case QuoteType_SZE_AnyPriceThenCancel:
                return "4-��ʱ�ɽ�ʣ�೷��";
            case QuoteType_SZE_FivePriceThenCancel:
                return "5-�嵵����ʣ��";
            case QuoteType_SZE_AllPriceOrCancel:
                return "6-ȫ��ɽ�����";
            default:
                return "0-δ֪";
        }
    }
    else
    {
        return "0-δ֪";
    }
}

char* GetTradeFlagText(int tradeFlag)
{
    switch (tradeFlag)
    {
        case TradeFlag_Buy:
            return "1-����";
        case TradeFlag_Sell:
            return "2-����";
        case TradeFlag_Purchase:
            return "3-�깺";
        case TradeFlag_Redeem:
            return "4-���";
        case TradeFlag_MarginBuy:
            return "6-��������";
        case TradeFlag_MarginSell:
            return "7-��ȯ����";
        case TradeFlag_MarginBuyCover:
            return "8-�����ۻ�";
        case TradeFlag_MarginSellCover:
            return "9-��ȯ����";
        case TradeFlag_ETFPurchase:
            return "11-ETF�깺";
        case TradeFlag_ETFRedeem:
            return "12-ETF���";
        case TradeFlag_FundPurchase:
            return "13-�����깺";
        case TradeFlag_FundRedeem:
            return "14-�������";
        case TradeFlag_GradedFundMerge:
            return "17-�ּ�����ϲ�";
        case TradeFlag_GradedFundSplit:
            return "18-�ּ�����ϲ�";
        case TradeFlag_FundSubscribe:
            return "19-�����Ϲ�";
        case TradeFlag_Placement:
            return "21-����";
        case TradeFlag_Distribution:
            return "22-���";
        case TradeFlag_CancelBuy:
            return "-1-����";
        case TradeFlag_CancelSell:
            return "-2-����";
        default:
            return "0-δ֪";
    }
}

char* GetStatusText(int status)
{
    switch (status)
    {
        case OrderStatus_Unorder:
            return "1-δ�걨";
        case OrderStatus_UndealtOrder:
            return "3-���걨δ�ɽ�";
        case OrderStatus_InvalidOrder:
            return "4-�Ƿ�ί��";
        case OrderStatus_PartialDealt:
            return "6-���ֳɽ�";
        case OrderStatus_AllDealt:
            return "7-ȫ���ɽ�";
        case OrderStatus_PartialDealtPartialCancelled:
            return "8-���ɲ���";
        case OrderStatus_AllCancelled:
            return "9-ȫ������";
        default:
            return "0-δ֪";
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
    printf("����������:%s, ��Լ����:%s, ��Լ����:%s\n����: %-10.4f %d\n����: %-10.4f %d\n����: %-10.4f %d\n����: %-10.4f %d\n��һ: %-10.4f %d\n��һ: %-10.4f %d\n���: %-10.4f %d\n����: %-10.4f %d\n����: %-10.4f %d\n����: %-10.4f %d\n",
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

    printf("%-20s\t%-20s\n", "����������", "�ɶ�����");
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

    printf("%-20s\t%-20s\t%-20s\t%-20s\t%-20s\n", "����", "�ʽ����", "�����ʽ�", "��ȡ�ʽ�", "���ʲ�");
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

    printf("%-10s\t%-20s\t%-20s\t%-20s\t%-20s\t%-20s\n", "����������", "��Լ����", "��Լ����", "����", "��������", "�ɶ�����");
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

    printf("%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n", "ί������", "ί��ʱ��", "ί�б��", "�ɶ�����", "����������", "��Լ����", "��Լ����", "���ױ�־", "ί�м۸�", "ί������", "�ɽ��۸�", "�ɽ�����", "��������", "��������", "״̬");
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

    printf("%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n", "ί������", "ί��ʱ��", "ί�б��", "�ɶ�����", "����������", "��Լ����", "��Լ����", "���ױ�־", "ί�м۸�", "ί������", "�ɽ�����", "��������", "��������", "״̬");
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

    printf("%-15s\t%-15s\t%-25s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n", "�ɽ�ʱ��", "�ɽ����", "ί�б��", "�걨���", "�ɶ�����", "����������", "��Լ����", "��Լ����", "���ױ�־", "�ɽ��۸�", "�ɽ�����");
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

    printf("%-15s\t%-15s\t%-25s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\t%-15s\n", "�ɽ�����", "�ɽ�ʱ��", "�ɽ����", "�ɶ�����", "����������", "��Լ����", "��Լ����", "���ױ�־", "�ɽ��۸�", "�ɽ�����");
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
    printf("��������:%.0f\n",
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
    printf("ί�б��: %s\n",
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
    printf("ί�б��: %s\n",
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
    //printf("ί�б��: %s\n",
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
        __username = argv[1]; // ����'jimcai'��
        __key = argv[2]; // ��Rushquant��վ��ȡ��
        __accountId = atoi(argv[3]); // Ҫ�������˻�id��Ϊĩβ5λ��
        __password = argv[4]; // Ҫ�������˻��������롣
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
    // ���ý�������
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