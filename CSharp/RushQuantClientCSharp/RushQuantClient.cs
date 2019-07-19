using System;

namespace RushQuant.Clients
{
    public abstract class RushQuantClient
    {
        private static bool __initialized;
        protected static bool Initialized
        {
            get
            {
                return __initialized;
            }
        }

        public static bool Initialize(string pUsername, string pKey)
        {
            int result = UnsafeNativeMethods.rushquant_initialize(pUsername, pKey);
            RushQuantClient.__initialized = (result == ErrorCode.Success);

            return RushQuantClient.__initialized;
        }

        public static void Dispose()
        {
            int result = UnsafeNativeMethods.rushquant_dispose();

            RushQuantClient.__initialized = false;
        }
    }    
}
