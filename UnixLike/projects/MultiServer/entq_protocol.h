//定义委托排队机和交易撮合主机之间的业务协议接口
/**
 *源程序名称:entq_protocol.h
 *系统名称:NEEQ1.0 委托排队机、交易撮合主机
 *模块名称:概要设计中定义
 *功能说明:定义委托排队机和交易撮合主机之间的业务协议接口
 *作    者: 徐志坚
 *开发日期: 20130702
 *修改记录：
 *20140201  *****
 */
 
#ifndef _ENTQ_PROTOCOL_H_
#define _ENTQ_PROTOCOL_H_

#include "config_env.h"

#include "order_deal.h"

#pragma pack(1)

///委托结构
typedef struct {
    ///委托类型 此处为0
    uint32_t   OrderType;
    ///由排队机打的时间戳 /* TIME-8, HHMMSSCC */
    uint32_t   TimeStamp;

	///对应深圳通委托结构
	ORDER_T entcommEntrust;
} ENTQ_OUT_ENTRUST;

///交易阶段时间控制指令
typedef struct {
    ///委托类型
    /**  非0：表示为指令：
	 *   1: 开市
	 *   3：上午竞价休市
     *   4：下午竞价开始
     *   8：盘后指令开始
	 *   9：全天闭市
     *   40：时间片指令
     */
    uint32_t   OrderType;
    ///由排队机打的时间戳 /* TIME-8, HHMMSSCC*/
    uint32_t   TimeStamp;
    ///撮合模式 填'0'
    char	   MatchType;
} TIMER_ORDER;

///证券停复牌指令
typedef struct {
    ///委托类型
    /**  非0：表示为指令
     *   600060：证券临时停牌
     *   600061：证券复牌
     */
    uint32_t   OrderType;
    ///由排队机打的时间戳 /* TIME-8, HHMMSSCC
    uint32_t   TimeStamp;
    ///指令流水号
    uint32_t   OrderNo; 
    ///证券代码
    uint32_t   StockCode; 
	///停牌状态 F:“正常转让”T:“停牌，不接受转让申报”H:“停牌，接受转让申报”
	char     StopType;
	///停牌类型 1:“停牌一小时”2:“停牌半天”3:“停牌一天”4:“长期停牌”
	char     StopTimeType;
} STOP_ORDER;

///证券账户紧急维护指令
typedef struct {
    ///委托类型
    /**  非0：表示为指令
     *  600050：证券账户紧急维护
     */
    uint32_t   OrderType;
    ///由排队机打的时间戳 /* TIME-8, HHMMSSCC
    uint32_t   TimeStamp;
    ///指令流水号
    uint32_t   OrderNo; 
    ///证券帐号
    char       StockAccount[11];
	/// 账户类别 1-“A股”、2-“B股”
	char    HolderType;
    /// 账户属性
    char    HolderAttr;
	///账户性质 
	char    AccountProp[3];
	///证券账户状态 1-“正常”、2-“不合格”、9-“停用”
	char    HolderStatus;
} HOLDER_EMERGENCY_ORDER;

///证券账户交易限制紧急维护指令
typedef struct {
    ///委托类型
    /**  非0：表示为指令
     *   600051：证券账户交易限制紧急维护
     */
    uint32_t   OrderType;
    ///由排队机打的时间戳 /* TIME-8, HHMMSSCC
    uint32_t   TimeStamp;
    ///指令流水号
    uint32_t   OrderNo; 
	///交易单元
	uint32_t   UnitNo;
	///证券代码
	uint32_t   StockCode;
	///允许业务类别
	char       EnTradeType[128];
	///证券账户
	char       StockAccount[11];
	///操作类型 0增加；1修改；2删除
	char       ActionIn;
	///证券类别
	char       StockType[3];
	///交易单元类型 1-“经纪业务”、2-“做市业务”、3-“自营业务”、4-“其他”
	char       UnitType;
	///额度类型 0普通 1大额
	char       SystemType;
	///允许标志 0禁止；1允许
	char	   AllowFlag;
	///限制来源
	char       LimitSource;
} HOLDER_LIMIT_ORDER;

///证券交易参数紧急维护指令
typedef struct {
    ///委托类型
    /**  非0：表示为指令
     *  600052：证券交易参数紧急维护
     */
    uint32_t   	OrderType;
    ///由排队机打的时间戳 /* TIME-8, HHMMSSCC
    uint32_t   	TimeStamp;
    ///指令流水号
    uint32_t    OrderNo; 
    ///证券代码
    uint32_t   	StockCode; 
    ///前收盘价（厘）
    uint32_t   	ClosePrice;
	///涨停价格（厘）
	uint32_t   	UpPrice;
	///跌停价格（厘）
	uint32_t	DownPrice;
	///大额涨停价格（厘）
	uint32_t    BigUpPrice;
	///大额跌停价格（厘）
	uint32_t	BigDownPrice;
} STOCK_EMERGENCY_ORDER;

///证券业务类别紧急维护指令
typedef struct {
    ///委托类型  非0：表示为指令
    /**
     *  600053：证券业务类别紧急维护
     */
    uint32_t   OrderType;
    ///由排队机打的时间戳 /* TIME-8, HHMMSSCC
    uint32_t   TimeStamp;
    ///指令流水号
    uint32_t   OrderNo; 
	///证券代码
	uint32_t   StockCode;
	///操作类型 0增加；1修改；2删除
	char       ActionIn;
	///额度类型 0普通 1大额
	char       SystemType;
	///允许业务类别
	char       EnTradeType[128];
} STOCK_LIMIT_ORDER;

///质押式回购债券紧急维护指令
typedef struct {
    ///委托类型  非0：表示为指令
    /**
     *   600054：质押式回购债券紧急维护
     */
    uint32_t   OrderType;
    ///由排队机打的时间戳 /* TIME-8, HHMMSSCC
    uint32_t   TimeStamp;
    ///指令流水号
    uint32_t   OrderNo; 
    ///证券代码
    uint32_t   StockCode;
    ///标准券代码 
    uint32_t   Standard;
    ///折算率
    uint32_t   BondRate;
} BONDRATE_ORDER;

///交易单元交易限制紧急维护指令
typedef struct {
    ///委托类型  非0：表示为指令
    /**
     *   600055：交易单元交易限制紧急维护
     */
    uint32_t    OrderType;
    ///由排队机打的时间戳 /* TIME-8, HHMMSSCC
    uint32_t    TimeStamp;
    ///指令流水号
    uint32_t   OrderNo; 
	///交易单元
	uint32_t    UnitNo;
	///证券代码
	uint32_t    StockCode;
	///允许业务类别
	char       EnTradeType[128];
	///证券类别
	char       StockType[3];
	///操作类型 0增加；1修改；2删除
	char       ActionIn;
	///额度类型 0普通 1大额
	char       SystemType;
	///允许标志 0禁止；1允许
	char	   AllowFlag;
	///限制来源
	char        LimitSource;
} BROKERNO_LIMIT_ORDER;

///手工收市,临时停市指令
typedef struct {
    ///委托类型  非0：表示为指令
    /**
     *   600098: 手工收市指令
     *   600099：临时停市指令
     */
    uint32_t    OrderType;
    ///由排队机打的时间戳 /* TIME-8, HHMMSSCC
    uint32_t    TimeStamp;
    ///指令流水号
    uint32_t   OrderNo; 
} TEMP_CLOSE_ORDER;


struct ACD_ORDER  // 委托单共享内存中的委托单
{
	///委托指令联合结构，用于解析组播获取数据
	union
	{
		///委托
		ENTQ_OUT_ENTRUST		Entrust;
		///交易阶段时间控制指令
		TIMER_ORDER			TimerOrder;
		///证券停复牌指令
		STOP_ORDER			StopOrder;
		///证券账户紧急维护指令
		HOLDER_EMERGENCY_ORDER	HolderEmergencyOrder;
		///证券账户交易限制紧急维护指令
		HOLDER_LIMIT_ORDER		HolderLimitOrder;
		///证券交易参数紧急维护指令
		STOCK_EMERGENCY_ORDER	StockEmergencyOrder;
		///证券业务类别紧急维护指令
		STOCK_LIMIT_ORDER		StockLimitOrder;
		///质押式回购债券紧急维护指令
		BONDRATE_ORDER			BondRateOrder;
		///交易单元交易限制紧急维护指令
		BROKERNO_LIMIT_ORDER	BrokerNoLimitOrder;
		///手工收市,临时停市指令
		TEMP_CLOSE_ORDER       TempCloseOrder;
	};
	unsigned char   LinkId;         // 链接ID
	bool            LastOrder;      // 委托包中的最终委托单：FALSE:否；TRUE:是
	bool            ConfirmStatus;  // 备机确认标志：FALSE:未确认；TRUE:确认
};

#pragma pack()
#endif /* _ENTQ_PROTOCOL_H_ */
