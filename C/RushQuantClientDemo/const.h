#ifndef CONST_H
#define CONST_H

#define Error_Success 0                            /* �ɹ� */
// System
#define Error_System_InvalidUsernameOrKey 1001     /* ��Ч���û���������Կ */
#define Error_System_FailToInitializeSocket 1002   /* ��ʼ��Socket���� */
#define Error_System_NotAvailableTradeServer 1003  /* û����Ч�Ľ��׷����� */
#define Error_System_FailToFetchData 1004          /* ��ȡԶ�����ݳ��� */
#define Error_System_FailToLoad 1005               /* ���س��� */
#define Error_System_VersionNotSupport 1006        /* �汾��֧�� */
// Account
#define Error_Account_NotFound 2001                /* �ʻ������� */
#define Error_Account_FailToInitialize 2001        /* �ʻ���ʼ������ */
// Network
#define Error_Network_FailToInitialize 3001        /* �����ʼ������ */
#define Error_Network_FailToConnect 3002           /* �������ӳ��� */
#define Error_Network_FailToSend 3003              /* ���緢�ʹ��� */
#define Error_Network_FailToReceive 3004           /* ������մ��� */
// Trade
#define Error_Trade_InvalidResponse 6001           /* ��Ч�Ļ�Ӧ���� */
#define Error_Trade_FailToAnalyseResponse 6002     /* �޷�������Ӧ���� */
#define Error_Trade_UnsupportRequest 6003          /* ��֧�ֵ����� */
#define Error_Trade_RemoteResponseError 6004       /* Զ�̷��ش�����Ϣ  */
#define Error_Trade_ResponseTooLarge 6005          /* Զ�̷�������̫��  */
#define Error_Trade_ResponseUnexceptedData 6006    /* ���ص�����δ��Ԥ��һ�� */
#define Error_Trade_InvalidRequest 6007            /* ����������Ч */
#define Error_Trade_OutputSizeNotEnough 6008       /* ����ṹ���ڴ��С���� */
#define Error_Trade_ProtocolError 6009             /* ͨѶЭ����� */
#define Error_Trade_FailToLogin 6010               /* ��¼ʧ�� */

#endif /* CONST_H */