using System;

namespace RushQuant.Clients
{
    /// <summary>交易所编号</summary>
    public static class ExchangeId
    {
        /// <summary>上海证券交易所</summary>
        public const string SSE = "SSE";
        /// <summary>深圳证券交易所</summary>
        public const string SZE = "SZE";
    }

    /// <summary>货币代码</summary>
    public enum Currency
    {
        /// <summary>人民币</summary>
        [Description("人民币")]
        RMB = 1,
        /// <summary>港币</summary>
        [Description("港币")]
        HKD = 2,
        /// <summary>美元</summary>
        [Description("美元")]
        USD = 3,
    }

    /// <summary>报价方式</summary>
    public enum QuoteType
    {
        /// <summary>上海: 限价委托</summary>
        [Description("上海: 限价委托")]
        SSE_LimitPrice = 1,
        /// <summary>上海: 五档即成剩撤</summary>
        [Description("上海: 五档即成剩撤")]
        SSE_FivePriceThenCancel = 5,
        /// <summary>上海: 五档即成转限价</summary>
        [Description("上海: 五档即成转限价")]
        SSE_FivePriceThenLimitPrice = 7,
        /// <summary>深圳: 限价委托</summary>
        [Description("深圳: 限价委托")]
        SZE_LimitPrice = 1,
        /// <summary>深圳: 对方最优价格</summary>
        [Description("深圳: 对方最优价格")]
        SZE_CounterpartyBestPrice = 2,
        /// <summary>深圳: 本方最优价格</summary>
        [Description("深圳: 本方最优价格")]
        SZE_BestPrice = 3,
        /// <summary>深圳: 即时成交剩余撤销</summary>
        [Description("深圳: 即时成交剩余撤销")]
        SZE_AnyPriceThenCancel = 4,
        /// <summary>深圳: 五档即成剩撤</summary>
        [Description("深圳: 五档即成剩撤")]
        SZE_FivePriceThenCancel = 5,
        /// <summary>深圳: 全额成交或撤销</summary>
        [Description("深圳: 全额成交或撤销")]
        SZE_AllPriceOrCancel = 6,
    }

    /// <summary>交易标志</summary>
    public enum TradeFlag
    {
        /// <summary>买入</summary>
        [Description("买入")]
        Buy = 1,
        /// <summary>卖出</summary>
        [Description("卖出")]
        Sell = 2,
        /// <summary>申购</summary>
        [Description("申购")]
        Purchase = 3,
        /// <summary>赎回</summary>
        [Description("赎回")]
        Redeem = 4,
        /// <summary>融资买入</summary>
        [Description("融资买入")]
        MarginBuy = 6,
        /// <summary>融券卖出</summary>
        [Description("融券卖出")]
        MarginSell = 7,
        /// <summary>融资售回</summary>
        [Description("融资售回")]
        MarginBuyCover = 8,
        /// <summary>融券购回</summary>
        [Description("融券购回")]
        MarginSellCover = 9,
        /// <summary>ETF申购</summary>
        [Description("ETF申购")]
        ETFPurchase = 11,
        /// <summary>ETF赎回</summary>
        [Description("ETF赎回")]
        ETFRedeem = 12,
        /// <summary>基金申购</summary>
        [Description("基金申购")]
        FundPurchase = 13,
        /// <summary>基金赎回</summary>
        [Description("基金赎回")]
        FundRedeem = 14,
        /// <summary>分级基金合并</summary>
        [Description("分级基金合并")]
        GradedFundMerge = 17,
        /// <summary>分级基金合拆</summary>
        [Description("分级基金合拆")]
        GradedFundSplit = 18,
        /// <summary>基金认购</summary>
        [Description("基金认购")]
        FundSubscribe = 19,
        /// <summary>配售</summary>
        [Description("配售")]
        Placement = 21,
        /// <summary>配号</summary>
        [Description("配号")]
        Distribution = 22,
        /// <summary>撤买</summary>
        [Description("撤买")]
        CancelBuy = -1,
        /// <summary>撤卖</summary>
        [Description("撤卖")]
        CancelSell = -2,
    }

    /// <summary>委托状态</summary>
    public enum OrderStatus
    {
        /// <summary>未申报</summary>
        [Description("未申报")]
        Unorder = 1,
        /// <summary>已申报未成交</summary>
        [Description("已申报未成交")]
        UndealtOrder = 3,
        /// <summary>非法委托</summary>
        [Description("非法委托")]
        InvalidOrder = 4,
        /// <summary>部分成交</summary>
        [Description("部分成交")]
        PartialDealt = 6,
        /// <summary>全部成交</summary>
        [Description("全部成交")]
        AllDealt = 7,
        /// <summary>部成部撤</summary>
        [Description("部成部撤")]
        PartialDealtPartialCancelled = 8,
        /// <summary>全部撤单</summary>
        [Description("全部撤单")]
        AllCancelled = 9,
    }

}
