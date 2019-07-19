using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using RushQuant.Clients;

namespace RushQuantClientDemo
{
    class Program
    {
        public static string __username;
        public static string __key;
        public static string __accountId;
        public static string __password;
        //public static string __accountId1; //另外一个账户
        //public static string __password1;

        public static string GetQuoteType(string exchangeId, int quoteType)
        {
            if (exchangeId == ExchangeId.SSE)
            {
                switch (quoteType)
                {
                    case (int)QuoteType.SSE_LimitPrice:
                        return "1-限价委托";
                    case (int)QuoteType.SSE_FivePriceThenCancel:
                        return "5-五档即成剩撤";
                    case (int)QuoteType.SSE_FivePriceThenLimitPrice:
                        return "7-五档即成转限价";
                    default:
                        return "0-未知";
                }
            }
            else if (exchangeId == ExchangeId.SZE)
            {
                switch (quoteType)
                {
                    case (int)QuoteType.SZE_LimitPrice:
                        return "1-限价委托";
                    case (int)QuoteType.SZE_CounterpartyBestPrice:
                        return "2-对方最优价格";
                    case (int)QuoteType.SZE_BestPrice:
                        return "3-本方最优价格";
                    case (int)QuoteType.SZE_AnyPriceThenCancel:
                        return "4-即时成交剩余撤销";
                    case (int)QuoteType.SZE_FivePriceThenCancel:
                        return "5-五档即成剩撤";
                    case (int)QuoteType.SZE_AllPriceOrCancel:
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

        private static Dictionary<int, string> __currencyDescriptions = ((Func<Dictionary<int, string>>)(() =>
        {
            Dictionary<int, string> items = DescriptionAttribute.GetDescriptions<Currency>();
            return items;
        }))();
        public static string GetCurrencyText(int value)
        {
            if (!__currencyDescriptions.ContainsKey(value))
            {
                return "0-未知";
            }

            return __currencyDescriptions[value];
        }


        private static Dictionary<int, string> __tradeDescriptions = ((Func<Dictionary<int, string>>)(() =>
        {
            Dictionary<int, string> items = DescriptionAttribute.GetDescriptions<TradeFlag>();
            return items;
        }))();
        public static string GetTradeFlagText(int value)
        {
            if (!__tradeDescriptions.ContainsKey(value))
            {
                return "0-未知";
            }

            return __tradeDescriptions[value];
        }

        private static Dictionary<int, string> __statusDescriptions = ((Func<Dictionary<int, string>>)(() =>
        {
            Dictionary<int, string> items = DescriptionAttribute.GetDescriptions<OrderStatus>();
            return items;
        }))();
        public static string GetStatusText(int value)
        {
            if (!__statusDescriptions.ContainsKey(value))
            {
                return "0-未知";
            }

            return __statusDescriptions[value];

            //switch (status)
            //{
            //    case 1:
            //        return "1-";
            //    case 2:
            //        return "2-已申报未成交";
            //    case 3:
            //        return "3-";
            //    case 4:
            //        return "4-";
            //    case 5:
            //        return "5-";
            //    case 6:
            //        return "6-全部成交";
            //    case 7:
            //        return "7-部成部撤";
            //    case 8:
            //        return "8-全部撤单";
            //    case 9:
            //        return "9-";
            //    case 10:
            //        return "10-";
            //    case 11:
            //        return "11-";
            //    case 12:
            //        return "12-";
            //    case 13:
            //        return "13-";
            //    default:
            //        return "0-未知";
            //}
        }

        private static void Test_QueryTickData(RushQuantTradeClient client)
        {
            Console.WriteLine("******* QueryTickData BEGIN *********\n");

            QueryTickDataInput input = new QueryTickDataInput
            {
                ExchangeId = ExchangeId.SSE,
                InstrumentCode = "601288"
            };
            QueryTickDataOutput output = client.QueryTickData(input);
            QueryTickDataOutput item = output;
            Console.WriteLine(
$@"交易所名称:{item.ExchangeId}, 合约代码:{item.InstrumentCode}, 合约名称:{item.InstrumentName}
卖五: {item.AskPrice5.ToString("f2")}   {item.AskVolume5}
卖四: {item.AskPrice4.ToString("f2")}   {item.AskVolume4}
卖三: {item.AskPrice3.ToString("f2")}   {item.AskVolume3}
卖二: {item.AskPrice2.ToString("f2")}   {item.AskVolume2}
卖一: {item.AskPrice1.ToString("f2")}   {item.AskVolume1}
买一: {item.BidPrice1.ToString("f2")}   {item.BidVolume1}
买二: {item.BidPrice2.ToString("f2")}   {item.BidVolume2}
买三: {item.BidPrice3.ToString("f2")}   {item.BidVolume3}
买四: {item.BidPrice4.ToString("f2")}   {item.BidVolume4}
买五: {item.BidPrice5.ToString("f2")}   {item.BidVolume5}
");

            Console.WriteLine("******* QueryTickData END *********");
            Console.WriteLine();
        }

        private static void Test_QueryStockholderInfo(RushQuantTradeClient client)
        {
            Console.WriteLine("******* QueryStockholderInfo BEGIN *********\n");

            QueryStockholderInfoInput input = new QueryStockholderInfoInput()
            {
            };
            QueryStockholderInfoOutput output = client.QueryStockholderInfo(input);
            Console.WriteLine($"{"交易所名称",-20}\t{"股东代码",-20}");
            for (int i = 0; i < output.Count; i++)
            {
                QueryStockholderInfoOutputItem item = output.Items[i];
                Console.WriteLine($"{item.ExchangeId,-26}\t{item.StockholderCode,-26}");
            }
            Console.WriteLine("******* QueryStockholderInfo END *********\n");
            Console.WriteLine();
        }

        private static void Test_QuerySecurityCapitalInfo(RushQuantTradeClient client)
        {
            Console.WriteLine("******* QuerySecurityCapitalInfo BEGIN *********\n");

            QuerySecurityCapitalInfoInput input = new QuerySecurityCapitalInfoInput()
            {
            };
            QuerySecurityCapitalInfoOutput output = client.QuerySecurityCapitalInfo(input);
            Console.WriteLine($"{"币种",-20}\t{"资金余额",-20}\t{"可用资金",-20}\t{"可取资金",-20}\t{"总资产",-20}");

            for (int i = 0; i < output.Count; i++)
            {
                QuerySecurityCapitalInfoOutputItem item = output.Items[i];
                Console.WriteLine($"{GetCurrencyText(item.Currency),-22}\t{item.RemainingCapitalAmount,-26}\t{item.AvailableCapitalAmount,-26}\t{item.WithdrawableCapitalAmount,-26}\t{item.TotalAssetAmount,-26}");
            }
            Console.WriteLine("******* QuerySecurityCapitalInfo END *********\n");
            Console.WriteLine();
        }

        private static void Test_QuerySecurityPositionInfo(RushQuantTradeClient client)
        {
            Console.WriteLine("******* QuerySecurityPositionInfo BEGIN *********\n");

            QuerySecurityPositionInfoInput input = new QuerySecurityPositionInfoInput()
            {
            };
            QuerySecurityPositionInfoOutput output = client.QuerySecurityPositionInfo(input);
            Console.WriteLine($"{"交易所名称",-20}\t{"合约代码",-20}\t{"合约名称",-20}\t{"数量",-20}\t{"可卖数量",-20}\t{"股东代码",-20}");

            for (int i = 0; i < output.Count; i++)
            {
                QuerySecurityPositionInfoOutputItem item = output.Items[i];
                Console.WriteLine($"{item.ExchangeId,-22}\t{item.InstrumentCode,-26}\t{item.InstrumentName,-26}\t{item.Volume,-26}\t{item.AvailableVolume,-26}\t{item.StockholderCode,-26}");
            }
            Console.WriteLine("******* QuerySecurityPositionInfo END *********\n");
            Console.WriteLine();
        }


        private static void Test_QuerySecurityIntradayOrder(RushQuantTradeClient client)
        {
            Console.WriteLine("******* QuerySecurityIntradayOrder BEGIN *********\n");

            QuerySecurityIntradayOrderInput input = new QuerySecurityIntradayOrderInput()
            {
            };
            QuerySecurityIntradayOrderOutput output = client.QuerySecurityIntradayOrder(input);
            Console.WriteLine($"{"委托日期",-10}{"委托时间",-10}{"委托编号",-10}{"股东代码",-10}{"交易所代码",-10}{"合约代码",-10}{"合约名称",-10}{"交易标志",-10}{"委托价格",-10}{"委托数量",-10}{"成交价格",-10}{"成交数量",-10}{"撤单数量",-10}{"报价类型",-10}{"状态",-10}");

            for (int i = 0; i < output.Count; i++)
            {
                QuerySecurityIntradayOrderOutputItem item = output.Items[i];
                Console.WriteLine($"{item.OrderDate,-14}{item.OrderTime,-14}{item.OrderID,-14}{item.StockholderCode,-14}{item.ExchangeId,-15}{item.InstrumentCode,-14}{item.InstrumentName,-10}{GetTradeFlagText(item.TradeFlag),-12}{item.OrderPrice,-14}{item.OrderVolume,-14}{item.DealPrice,-14}{item.DealVolume,-14}{item.CancelVolume,-14}{GetQuoteType(item.ExchangeId, item.QuoteType),-10}{GetStatusText(item.OrderStatus)}");
            }
            Console.WriteLine("******* QuerySecurityIntradayOrder END *********\n");
            Console.WriteLine();
        }

        private static void Test_QuerySecurityHistoricalOrder(RushQuantTradeClient client)
        {
            Console.WriteLine("******* QuerySecurityHistoricalOrder BEGIN *********\n");

            QuerySecurityHistoricalOrderInput input = new QuerySecurityHistoricalOrderInput()
            {
                BeginDate = 20181224,
                EndDate = 20181231
            };
            QuerySecurityHistoricalOrderOutput output = client.QuerySecurityHistoricalOrder(input);
            Console.WriteLine($"{"委托日期",-10}{"委托时间",-10}{"委托编号",-10}{"股东代码",-10}{"交易所代码",-10}{"合约代码",-10}{"合约名称",-10}{"交易标志",-10}{"委托价格",-10}{"委托数量",-10}{"成交数量",-10}{"撤单数量",-10}{"报价类型",-10}{"状态",-10}");

            for (int i = 0; i < output.Count; i++)
            {
                QuerySecurityHistoricalOrderOutputItem item = output.Items[i];
                Console.WriteLine($"{item.OrderDate,-14}{item.OrderTime,-14}{item.OrderID,-14}{item.StockholderCode,-14}{item.ExchangeId,-15}{item.InstrumentCode,-14}{item.InstrumentName,-10}{GetTradeFlagText(item.TradeFlag),-12}{item.OrderPrice,-14}{item.OrderVolume,-14}{item.DealVolume,-14}{item.CancelVolume,-14}{GetQuoteType(item.ExchangeId, item.QuoteType),-10}{GetStatusText(item.OrderStatus)}");
            }
            Console.WriteLine("******* QuerySecurityHistoricalOrder END *********\n");
            Console.WriteLine();
        }

        private static void Test_QuerySecurityIntradayDeal(RushQuantTradeClient client)
        {
            Console.WriteLine("******* QuerySecurityIntradayDeal BEGIN *********\n");

            QuerySecurityIntradayDealInput input = new QuerySecurityIntradayDealInput()
            {
            };
            QuerySecurityIntradayDealOutput output = client.QuerySecurityIntradayDeal(input);
            Console.WriteLine($"{"成交日期",-10}{"成交时间",-10}{"成交编号",-10}{"委托编号",-10}{"申报编号",-10}{"股东代码",-10}{"交易所代码",-10}{"合约代码",-10}{"合约名称",-10}{"交易标志",-10}{"成交价格",-10}{"成交数量",-10}");

            for (int i = 0; i < output.Count; i++)
            {
                QuerySecurityIntradayDealOutputItem item = output.Items[i];
                Console.WriteLine($"{item.DealDate,-14}{item.DealTime,-14}{item.DealID,-14}{item.OrderID,-14}{item.QuoteNumber,-14}{item.StockholderCode,-14}{item.ExchangeId,-15}{item.InstrumentCode,-14}{item.InstrumentName,-14}{GetTradeFlagText(item.TradeFlag),-12}{item.DealPrice,-14}{item.DealVolume,-14}");
            }
            Console.WriteLine("******* QuerySecurityIntradayDeal END *********\n");
            Console.WriteLine();
        }

        private static void Test_QuerySecurityHistoricalDeal(RushQuantTradeClient client)
        {
            Console.WriteLine("******* QuerySecurityHistoricalDeal BEGIN *********\n");

            QuerySecurityHistoricalDealInput input = new QuerySecurityHistoricalDealInput()
            {
                BeginDate = 20181212,
                EndDate = 20181213,
            };
            QuerySecurityHistoricalDealOutput output = client.QuerySecurityHistoricalDeal(input);
            Console.WriteLine($"{"成交日期",-10}{"成交时间",-10}{"成交编号",-20}{"股东代码",-10}{"交易所代码",-10}{"合约代码",-10}{"合约名称",-10}{"交易标志",-10}{"成交价格",-10}{"成交数量",-10}");

            for (int i = 0; i < output.Count; i++)
            {
                QuerySecurityHistoricalDealOutputItem item = output.Items[i];
                Console.WriteLine($"{item.DealDate,-14}{item.DealTime,-14}{item.DealID,-24}{item.StockholderCode,-14}{item.ExchangeId,-15}{item.InstrumentCode,-14}{item.InstrumentName,-14}{GetTradeFlagText(item.TradeFlag),-12}{item.DealPrice,-14}{item.DealVolume,-14}");
            }
            Console.WriteLine("******* QuerySecurityHistoricalDeal END *********\n");
            Console.WriteLine();
        }

        private static void Test_PostSecuritySubmitOrder(RushQuantTradeClient client)
        {
            Console.WriteLine("******* PostSecuritySubmitOrder BEGIN *********\n");

            PostSecuritySubmitOrderInput input = new PostSecuritySubmitOrderInput
            {
                ExchangeId = ExchangeId.SSE,
                InstrumentCode = "601288",
                TradeFlag = (int)TradeFlag.Buy,
                QuoteType = (int)QuoteType.SSE_LimitPrice,
                OrderPrice = 3.42,
                OrderVolume = 100,
            };
            PostSecuritySubmitOrderOutput output = client.PostSecuritySubmitOrder(input);
            PostSecuritySubmitOrderOutput item = output;
            Console.WriteLine($"委托编号: {item.OrderID}");

            Console.WriteLine("******* QueryTickData END *********");
            Console.WriteLine();
        }

        private static void Test_PostSecurityCancelOrder(RushQuantTradeClient client)
        {
            Console.WriteLine("******* PostSecurityCancelOrder BEGIN *********\n");

            PostSecurityCancelOrderInput input = new PostSecurityCancelOrderInput
            {
                ExchangeId = ExchangeId.SSE,
                OrderID = "558",
            };
            PostSecurityCancelOrderOutput output = client.PostSecurityCancelOrder(input);
            PostSecurityCancelOrderOutput item = output;
            Console.WriteLine($"已撤单。");

            Console.WriteLine("******* QueryTickData END *********");
            Console.WriteLine();
        }

        static int Main(string[] args)
        {
            Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);

            // TODO: Read config from args
            if (args.Length == 4)
            {
                __username = args[0]; // 比如'jimcai'。
                __key = args[1]; // 从Rushquant网站获取。
                __accountId = args[2]; // 要操作的账户id，为末尾5位。
                __password = args[3]; // 要操作的账户交易密码。
            }

            if (!RushQuantClient.Initialize(__username, __key))
            {
                return -1;
            }

            var c = RushQuantTradeClient.GetAccountList();

            RushQuantTradeClient client = RushQuantTradeClient.Create(Convert.ToInt32(__accountId));
            client.Reset();
            try
            {
                client.Login(new LoginInput() { TradePassword = __password });

                Test_QueryTickData(client);
                Test_QueryStockholderInfo(client);
                Test_QuerySecurityCapitalInfo(client);
                Test_QuerySecurityPositionInfo(client);
                Test_QuerySecurityIntradayOrder(client);
                Test_QuerySecurityHistoricalOrder(client);
                Test_QuerySecurityIntradayDeal(client);
                Test_QuerySecurityHistoricalDeal(client);

                Test_PostSecuritySubmitOrder(client);
                //Test_PostSecuritySubmitOrder_Purchase(client);
                //Test_PostSecurityCancelOrder(client);

                //for (int i = 0; i < 20; i++)
                //{
                //    test_PostSecuritySubmitOrder_NotReturn();
                //    Sleep(1);
                //}
            }
            catch (RushQuantClientException exception)
            {
                Console.WriteLine($"Login Error: {exception.ErrorCode}, Message: {exception.Message}");
                Console.Read();
                return -1;
            }

            RushQuantClient.Dispose();
            Console.Read();

            return 0;
        }
    }
}
