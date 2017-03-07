///委托单, 成交单公共数据结构定义
/**
  *源程序名称:  order_deal.h
  *系统名称:  NEEQ1.0 交易撮合主机、行情主机、监察主机
  *模块名称:  委托单,成交单公共结构
  *功能说明:  定义委托单, 成交单公共数据结构
  *作    者:  yuxw 
  *开发日期: 20130815
  *修改记录：
*/

#ifndef _ORDER_DEAL_H_
#define _ORDER_DEAL_H_
#include <stdint.h>

#pragma pack(1)

typedef struct{   
    uint32_t   BrokerNo;            // 交易单元 
    uint32_t   OrderDate;           // 委托日期 
    char       OrderNo[8];          // 委托流水号 
    uint32_t   CompanyNo;           // 证券代码 
    char       AccountNo[10];       // 证券帐号 
    uint32_t   OrderHands;          // 委托数量 
    uint32_t   Price;               // 委托价格 
    char       FunctionCode;        // 功能码 
    char       OrderKind;           // 业务类别 
    uint32_t   OrderTime;           // 委托时间 
    uint16_t   UserNo;              // used for breakpoint resume 
    uint32_t   MatchBrokerNo;       // 对方交易单元 
    char       MatchAccountNo[10];  // 对方证券帐号 
    uint32_t   OrderHands2;         // 委托数量2
    uint32_t   Price2;              // 委托价格2 
    char       CreditFlag;          // 融资融券标识
    char       PositioinFlag;       // 平仓标识 
    uint32_t   DealAgreedNo;        // 成交约定号 
    //uint32_t   IntentDeclareNo;     // 意向申报号 20131115 xuzj 根据最新接口文档删除
    char       Contact[12];         // 联系人 20131015 根据梁工邮件更新 由C20改为C12
    char       ContactInfo[30];     // 联系方式  20131015 根据梁工邮件更新 由C50改为C30
    char       GatewayNo[11];       // 报盘小站号 
}ORDER_T;

typedef struct 
{
    uint32_t  DealNo;               // 成交编号
    uint32_t  BuyBrokerNo;          // 买方交易单元
    uint32_t  BuyOrderYmd;          // 买方委托日期
    char      BuyOrderNo[8];        // 买方委托流水号
    uint32_t  SellBrokerNo;         // 卖方交易单元
    uint32_t  SellOrderYmd;         // 卖方委托日期
    char      SellOrderNo[8];       // 卖方委托流水号
    uint32_t  CompanyNo;            // 证券代码
    int32_t   MatchHands;           // 成交数量
    int32_t   MatchHands2;          // 成交数量2
    uint32_t  Price;                // 成交价格 
    uint32_t  Time;                 // 成交时间 
    uint32_t  Ymd;                  // 成交日期
    char      FunctionCode;         // 功能码
    char      OrderKind;            // 业务类别
    char      BuyAccountNo[10];     // 买方证券帐号
    char      SellAccountNo[10];    // 卖方证券帐号
    char      BuyCreditFlag;        // 买方融资融券标识
    char      BuyPositioinFlag;     // 买方平仓标识
    char      SellCreditFlag;       // 卖方融资融券标识
	char      SellPositioinFlag;	// 卖方平仓标识
}ORDER_DEAL_T;

#pragma pack()

#endif
