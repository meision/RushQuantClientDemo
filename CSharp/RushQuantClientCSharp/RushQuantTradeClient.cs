using System;

namespace RushQuant.Clients
{
    public class RushQuantTradeClient : RushQuantClient
    {
        public static int MAX_ACCOUNT = 100;

        public static RushQuantTradeClient Create(int accountId)
        {
            if (!RushQuantClient.Initialized)
            {
                return null;
            }

            return new RushQuantTradeClient(accountId);
        }

        public static unsafe int[] GetAccountList()
        {
            if (!RushQuantClient.Initialized)
            {
                return null;
            }

            int* pointer = stackalloc int[MAX_ACCOUNT];
            int count = UnsafeNativeMethods.rushquant_trade_GetAccountList(pointer);
            int[] accountIds = new int[count];
            for (int i = 0; i < count; i++)
            {
                accountIds[i] = *(pointer + i);
            }
            return accountIds;
        }

        public static unsafe void Free(byte* pointer)
        {
            UnsafeNativeMethods.rushquant_free(pointer);
        }

        private int _accountId;
        public int AccountId
        {
            get
            {
                return this._accountId;
            }
        }

        internal RushQuantTradeClient(int accountId)
        {
            this._accountId = accountId;
        }

        public int Reset()
        {
            return UnsafeNativeMethods.rushquant_trade_Reset(this._accountId);
        }

        public int NextId()
        {
            return UnsafeNativeMethods.rushquant_trade_NextId(this._accountId);
        }

        public unsafe LoginOutput Login(LoginInput input)
        {
            if (input == null)
            {
                throw new ArgumentNullException(nameof(input));
            }

            byte* pInput = stackalloc byte[LoginInput.GetSize()];
            byte* pOutput = stackalloc byte[LoginOutput.GetSize()];

            input.WriteTo(pInput);
            int result = UnsafeNativeMethods.rushquant_trade_Login(this._accountId, pInput, pOutput);
            LoginOutput output = new LoginOutput();
            output.ReadFrom(pOutput);
            if (result != ErrorCode.Success)
            {
                throw new RushQuantClientException(result, output.ErrorMessage);
            }

            return output;
        }


        public unsafe QueryTickDataOutput QueryTickData(QueryTickDataInput input)
        {
            if (input == null)
            {
                throw new ArgumentNullException(nameof(input));
            }

            byte* pInput = stackalloc byte[QueryTickDataInput.GetSize()];
            byte* pOutput = null;
            input.WriteTo(pInput);
            int result = UnsafeNativeMethods.rushquant_trade_QueryTickData(this._accountId, pInput, ref pOutput);
            QueryTickDataOutput output = new QueryTickDataOutput();
            output.ReadFrom(pOutput);
            UnsafeNativeMethods.rushquant_free(pOutput);
            if (result != ErrorCode.Success)
            {
                throw new RushQuantClientException(result, output.ErrorMessage);
            }

            return output;
        }

        public unsafe QueryStockholderInfoOutput QueryStockholderInfo(QueryStockholderInfoInput input)
        {
            if (input == null)
            {
                throw new ArgumentNullException(nameof(input));
            }

            byte* pInput = stackalloc byte[QueryStockholderInfoInput.GetSize()];
            byte* pOutput = null;
            input.WriteTo(pInput);
            int result = UnsafeNativeMethods.rushquant_trade_QueryStockholderInfo(this._accountId, pInput, ref pOutput);
            QueryStockholderInfoOutput output = new QueryStockholderInfoOutput();
            output.ReadFrom(pOutput);
            UnsafeNativeMethods.rushquant_free(pOutput);
            if (result != ErrorCode.Success)
            {
                throw new RushQuantClientException(result, output.ErrorMessage);
            }

            return output;
        }

        public unsafe QuerySecurityCapitalInfoOutput QuerySecurityCapitalInfo(QuerySecurityCapitalInfoInput input)
        {
            if (input == null)
            {
                throw new ArgumentNullException(nameof(input));
            }

            byte* pInput = stackalloc byte[QuerySecurityCapitalInfoInput.GetSize()];
            byte* pOutput = null;
            input.WriteTo(pInput);
            int result = UnsafeNativeMethods.rushquant_trade_QuerySecurityCapitalInfo(this._accountId, pInput, ref pOutput);
            QuerySecurityCapitalInfoOutput output = new QuerySecurityCapitalInfoOutput();
            output.ReadFrom(pOutput);
            UnsafeNativeMethods.rushquant_free(pOutput);
            if (result != ErrorCode.Success)
            {
                throw new RushQuantClientException(result, output.ErrorMessage);
            }

            return output;
        }

        public unsafe QuerySecurityPositionInfoOutput QuerySecurityPositionInfo(QuerySecurityPositionInfoInput input)
        {
            if (input == null)
            {
                throw new ArgumentNullException(nameof(input));
            }

            byte* pInput = stackalloc byte[QuerySecurityPositionInfoInput.GetSize()];
            byte* pOutput = null;
            input.WriteTo(pInput);
            int result = UnsafeNativeMethods.rushquant_trade_QuerySecurityPositionInfo(this._accountId, pInput, ref pOutput);
            QuerySecurityPositionInfoOutput output = new QuerySecurityPositionInfoOutput();
            output.ReadFrom(pOutput);
            UnsafeNativeMethods.rushquant_free(pOutput);
            if (result != ErrorCode.Success)
            {
                throw new RushQuantClientException(result, output.ErrorMessage);
            }

            return output;
        }

        public unsafe QuerySecurityOrderEvaluationOutput QuerySecurityOrderEvaluation(QuerySecurityOrderEvaluationInput input)
        {
            if (input == null)
            {
                throw new ArgumentNullException(nameof(input));
            }

            byte* pInput = stackalloc byte[QuerySecurityOrderEvaluationInput.GetSize()];
            byte* pOutput = null;
            input.WriteTo(pInput);
            int result = UnsafeNativeMethods.rushquant_trade_QuerySecurityOrderEvaluation(this._accountId, pInput, ref pOutput);
            QuerySecurityOrderEvaluationOutput output = new QuerySecurityOrderEvaluationOutput();
            output.ReadFrom(pOutput);
            UnsafeNativeMethods.rushquant_free(pOutput);
            if (result != ErrorCode.Success)
            {
                throw new RushQuantClientException(result, output.ErrorMessage);
            }

            return output;
        }

        public unsafe QuerySecurityIntradayOrderOutput QuerySecurityIntradayOrder(QuerySecurityIntradayOrderInput input)
        {
            if (input == null)
            {
                throw new ArgumentNullException(nameof(input));
            }

            byte* pInput = stackalloc byte[QuerySecurityIntradayOrderInput.GetSize()];
            byte* pOutput = null;
            input.WriteTo(pInput);
            int result = UnsafeNativeMethods.rushquant_trade_QuerySecurityIntradayOrder(this._accountId, pInput, ref pOutput);
            QuerySecurityIntradayOrderOutput output = new QuerySecurityIntradayOrderOutput();
            output.ReadFrom(pOutput);
            UnsafeNativeMethods.rushquant_free(pOutput);
            if (result != ErrorCode.Success)
            {
                throw new RushQuantClientException(result, output.ErrorMessage);
            }

            return output;
        }

        public unsafe QuerySecurityHistoricalOrderOutput QuerySecurityHistoricalOrder(QuerySecurityHistoricalOrderInput input)
        {
            if (input == null)
            {
                throw new ArgumentNullException(nameof(input));
            }

            byte* pInput = stackalloc byte[QuerySecurityHistoricalOrderInput.GetSize()];
            byte* pOutput = null;
            input.WriteTo(pInput);
            int result = UnsafeNativeMethods.rushquant_trade_QuerySecurityHistoricalOrder(this._accountId, pInput, ref pOutput);
            QuerySecurityHistoricalOrderOutput output = new QuerySecurityHistoricalOrderOutput();
            output.ReadFrom(pOutput);
            UnsafeNativeMethods.rushquant_free(pOutput);
            if (result != ErrorCode.Success)
            {
                throw new RushQuantClientException(result, output.ErrorMessage);
            }

            return output;
        }

        public unsafe QuerySecurityIntradayDealOutput QuerySecurityIntradayDeal(QuerySecurityIntradayDealInput input)
        {
            if (input == null)
            {
                throw new ArgumentNullException(nameof(input));
            }

            byte* pInput = stackalloc byte[QuerySecurityIntradayDealInput.GetSize()];
            byte* pOutput = null;
            input.WriteTo(pInput);
            int result = UnsafeNativeMethods.rushquant_trade_QuerySecurityIntradayDeal(this._accountId, pInput, ref pOutput);
            QuerySecurityIntradayDealOutput output = new QuerySecurityIntradayDealOutput();
            output.ReadFrom(pOutput);
            UnsafeNativeMethods.rushquant_free(pOutput);
            if (result != ErrorCode.Success)
            {
                throw new RushQuantClientException(result, output.ErrorMessage);
            }

            return output;
        }

        public unsafe QuerySecurityHistoricalDealOutput QuerySecurityHistoricalDeal(QuerySecurityHistoricalDealInput input)
        {
            if (input == null)
            {
                throw new ArgumentNullException(nameof(input));
            }

            byte* pInput = stackalloc byte[QuerySecurityHistoricalDealInput.GetSize()];
            byte* pOutput = null;
            input.WriteTo(pInput);
            int result = UnsafeNativeMethods.rushquant_trade_QuerySecurityHistoricalDeal(this._accountId, pInput, ref pOutput);
            QuerySecurityHistoricalDealOutput output = new QuerySecurityHistoricalDealOutput();
            output.ReadFrom(pOutput);
            UnsafeNativeMethods.rushquant_free(pOutput);
            if (result != ErrorCode.Success)
            {
                throw new RushQuantClientException(result, output.ErrorMessage);
            }

            return output;
        }

        public unsafe PostSecuritySubmitOrderOutput PostSecuritySubmitOrder(PostSecuritySubmitOrderInput input)
        {
            if (input == null)
            {
                throw new ArgumentNullException(nameof(input));
            }

            byte* pInput = stackalloc byte[PostSecuritySubmitOrderInput.GetSize()];
            byte* pOutput = null;
            input.WriteTo(pInput);
            int result = UnsafeNativeMethods.rushquant_trade_PostSecuritySubmitOrder(this._accountId, pInput, ref pOutput);
            PostSecuritySubmitOrderOutput output = new PostSecuritySubmitOrderOutput();
            output.ReadFrom(pOutput);
            UnsafeNativeMethods.rushquant_free(pOutput);
            if (result != ErrorCode.Success)
            {
                throw new RushQuantClientException(result, output.ErrorMessage);
            }

            return output;
        }

        public unsafe PostSecurityCancelOrderOutput PostSecurityCancelOrder(PostSecurityCancelOrderInput input)
        {
            if (input == null)
            {
                throw new ArgumentNullException(nameof(input));
            }

            byte* pInput = stackalloc byte[PostSecurityCancelOrderInput.GetSize()];
            byte* pOutput = null;
            input.WriteTo(pInput);
            int result = UnsafeNativeMethods.rushquant_trade_PostSecurityCancelOrder(this._accountId, pInput, ref pOutput);
            PostSecurityCancelOrderOutput output = new PostSecurityCancelOrderOutput();
            output.ReadFrom(pOutput);
            UnsafeNativeMethods.rushquant_free(pOutput);
            if (result != ErrorCode.Success)
            {
                throw new RushQuantClientException(result, output.ErrorMessage);
            }

            return output;
        }
    }
}
