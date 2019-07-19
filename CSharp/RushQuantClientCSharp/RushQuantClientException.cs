using System;
using System.Collections.Generic;
using System.Runtime.Serialization;
using System.Text;

namespace RushQuant.Clients
{
    public class RushQuantClientException : Exception
    {
        private int _errorCode;
        public int ErrorCode
        {
            get
            {
                return this._errorCode;
            }
        }

        public RushQuantClientException(string message)
            : base(message)
        {
        }

        public RushQuantClientException(int errorCode, string message)
            : base(message)
        {
            this._errorCode = errorCode;
        }

        public RushQuantClientException(string message, Exception innerException)
            : base(message, innerException)
        {
        }

        protected RushQuantClientException(SerializationInfo info, StreamingContext context)
            : base(info, context)
        {
        }

    }
}
