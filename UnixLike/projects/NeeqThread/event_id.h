///NEEQ全局事件定义
/***********************************************************************
系统名称: NEEQ1.0
模块名称:
文 件 名: event_id.h
功能说明:
作    者: 何李夫
开发日期: 2013-9-5   18:19:25
修改记录:
***********************************************************************/
#ifndef _EVENT_ID_H_
#define _EVENT_ID_H_


//////////////////////////////////////////////////////////////////////////
/*                                                                      */
/* 事件宏定义格式： 模块名_错误级别_简述                                */
/*                                                                      */
//////////////////////////////////////////////////////////////////////////

///各模块业务状态时序号段：800000-805000
enum BusinessSequenceEventId
{
    /* 交易主机 */
    TS_NOTICE_STATRTINIT             = 800000,   /**<TS初始化开始                                */
    TS_NOTICE_FINISHINIT             = 800001,   /**<TS初始化完成                                */
    TS_CRIT_INITFAILED               = 800002,   /**<TS初始化失败                                */
    TS_NOTICE_STARTMARKET            = 800003,   /**<TS开市                                      */
    TS_NOTICE_LUNCHBREAK             = 800006,   /**<TS午间休市                                  */
    TS_NOTICE_STATRTMARKETAFTERNOON  = 800009,   /**<TS下午开市                                  */
    TS_NOTICE_AFTERHOURS             = 800010,   /**<TS下午闭市+晚上开市                         */
    TS_NOTICE_CLOSEMARKET            = 800012,   /**<TS全天闭市                                  */
    TS_NOTICE_TREATY_ISSUE           = 800015,   /**<协议转让开始接收申报  500                   */
    TS_NOTICE_TREATY_MATCH           = 800016,   /**<协议转让开始连续撮合成交 501                */
    TS_NOTICE_TREATY_REST            = 800017,   /**<协议转让午间休市  100                       */
    TS_NOTICE_TREATY_MATCH_AFTERNOON = 800018,   /**<协议转让午间休市下午开市501                 */
    TS_NOTICE_TREATY_FIX_MATCH_CLOSE = 800019,   /**<协议转让收盘定价匹配成交，收市 502          */
    TS_NOTICE_TOWNET_NOTISSUE        = 800020,   /**<两网及退市开始接收申报  200                 */
    TS_NOTICE_TWO_NET_REST           = 800021,   /**<两网及退市午间休市    202                   */
    TS_NOTICE_TOWNET_NOTISSUE_AFTERNOON = 800022,   /**<两网及退市下午开市   200                 */
    TS_NOTICE_TOWNET_CLOSE           = 800023,   /**<两网及退市收市        203                   */
    TS_NOTICE_MARKET_REST           = 800024,   /**<做市中午休市        100                   */

    TS_NOTICE_TRADEORDERCOUNT        = 802001,   /**<TS开闭市指令数量                            */
    TS_NOTICE_E_ACCOUNT              = 802002,   /**<TS接收证券帐户紧急维护指令                  */
    TS_NOTICE_E_ACCOUNT_RESTRICT     = 802003,   /**<TS接收证券账户交易限制紧急维护指令          */
    TS_NOTICE_E_CONFIG               = 802004,   /**<TS接收证券交易参数紧急维护指令              */
    TS_NOTICE_E_BUSITYPE             = 802005,   /**<TS接收证券业务类别紧急维护指令              */
    TS_NOTICE_E_UNITNO               = 802006,   /**<TS接收交易单元交易限制紧急维护指令          */
    TS_NOTICE_E_SUSPEND              = 802007,   /**<TS接收证券临时停牌指令                      */
    TS_NOTICE_E_RESUME               = 802008,   /**<TS接收证券复牌指令                          */

    TS_NOTICE_LOADSTOCKTYPE          = 802009,   /**<加载初始化数据（证券类别）成功                                       */
    TS_NOTICE_LOADSTOCKCODE          = 802010,   /**<加载初始化数据（证券代码）成功                                       */
    TS_NOTICE_LOADSTOCKHOLDER        = 802011,   /**<加载初始化数据（证券帐户）成功                                       */
    TS_NOTICE_LOADUNITNO             = 802012,   /**<加载初始化数据（交易单元）成功                                       */
    TS_NOTICE_ALLOWBUSITYPE          = 802013,   /**<加载初始化数据（证券允许业务类别）成功                               */
    TS_NOTICE_LOADTNFLAG             = 802014,   /**<加载初始化数据（证券交易T+n标识）成功                                */
    TS_NOTICE_LOADSTOCK              = 802015,   /**<加载初始化数据（证券持仓信息）成功                                   */
    TS_NOTICE_LOADUNITNORESTRICT     = 802016,   /**<加载初始化数据（交易单元限制表）成功                                 */
    TS_NOTICE_LOADACCPROPRESTRICT    = 802017,   /**<加载初始化数据（账户性质限制）成功                                   */
    TS_NOTICE_LOADACCOUNTRESTRICT    = 802018,   /**<加载初始化数据（证券账户限制）成功                                   */
    TS_NOTICE_LOADMAKERRESTRICT      = 802019,   /**<加载初始化数据（做市限制）成功                                       */
    TS_NOTICE_LOADFORBIDTIME         = 802020,   /**<加载初始化数据（申报禁止业务时间）成功                               */
    TS_NOTICE_LOADMATCHTIME          = 802021,   /**<加载初始化数据（撮合交易阶段时间设置）成功                           */
    TS_NOTICE_LOADDEFAULTSYSDATA     = 802022,   /**<加载初始化数据（证券账户性质，交易单元类型默认禁止列表配置）成功     */
    TS_NOTICE_LOADDATE               = 802023,   /**<加载初始化数据（初始化日期）成功                                     */


    TS_ERROR_LOADSTOCKTYPE        = 802024,      /**<加载初始化数据（证券类别）失败                                       */
    TS_ERROR_LOADSTOCKCODE        = 802025,      /**<加载初始化数据（证券代码）失败                                       */
    TS_ERROR_LOADSTOCKHOLDER      = 802026,      /**<加载初始化数据（证券帐户）失败                                       */
    TS_ERROR_LOADUNITNO           = 802027,      /**<加载初始化数据（交易单元）失败                                       */
    TS_ERROR_LOADALLOWBUSITYPE    = 802028,      /**<加载初始化数据（证券允许业务类别）失败                               */
    TS_ERROR_LOADTNFLAG           = 802029,      /**<加载初始化数据（证券交易T+n标识）失败                                */
    TS_ERROR_LOADSTOCK            = 802030,      /**<加载初始化数据（证券持仓信息）失败                                   */
    TS_ERROR_LOADUNITNORESTRICT   = 802031,      /**<加载初始化数据（交易单元限制表）失败                                 */
    TS_ERROR_LOADACCPROPRESTRICT  = 802032,      /**<加载初始化数据（账户性质限制）失败                                   */
    TS_ERROR_LOADACCRESTRICT      = 802033,      /**<加载初始化数据（证券账户限制）失败                                   */
    TS_ERROR_LOADMAKERRESTRICT    = 802034,      /**<加载初始化数据（做市限制）失败                                       */
    TS_ERROR_LOADFORBIDTIME       = 802035,      /**<加载初始化数据（申报禁止业务时间）失败                               */
    TS_ERROR_LOADMATCHTIME        = 802036,      /**<加载初始化数据（撮合交易阶段时间设置）失败                           */
    TS_ERROR_LOADDEFAULTSYSDATA   = 802037,      /**<加载初始化数据（证券账户性质，交易单元类型默认禁止列表配置）失败     */
    TS_ERROR_LOADDATE             = 802038,      /**<加载初始化数据（初始化日期）失败                                     */

    TS_WARNING_LOADSTOCKTYPEPARTLYFAILED        = 802039,   /**<加载初始化数据（证券类别）部分失败                                   */
    TS_WARNING_LOADSTOCKCODEPARTLYFAILED        = 802040,   /**<加载初始化数据（证券代码）部分失败                                   */
    TS_WARNING_LOADSTOCKACCPARTLYFAILED         = 802041,   /**<加载初始化数据（证券帐户）部分失败                                   */
    TS_WARNING_LOADUNITNOPARTLYFAILED           = 802042,   /**<加载初始化数据（交易单元）部分失败                                   */
    TS_WARNING_LOADBUSITYPEPARTLYFAILED         = 802043,   /**<加载初始化数据（证券允许业务类别）部分失败                           */
    TS_WARNING_LOADTNFLAGEPARTLYFAILED          = 802044,   /**<加载初始化数据（证券交易T+n标识）部分失败                            */
    TS_WARNING_LOADSTOCKPARTLYFAILED            = 802045,   /**<加载初始化数据（证券持仓信息）部分失败                               */
    TS_WARNING_LOADUNITNORESTRICTPARTLYFAILED   = 802046,   /**<加载初始化数据（交易单元限制表）部分失败                             */
    TS_WARNING_LOADACCPROPRESTRICTARTLYFAILED   = 802047,   /**<加载初始化数据（账户性质限制）部分失败                               */
    TS_WARNING_LOADACCRESTRICTPARTLYFAILED      = 802048,   /**<加载初始化数据（证券账户限制）部分失败                               */
    TS_WARNING_LOADMAKERRESTRICTPARTLYFAILED    = 802049,   /**<加载初始化数据（做市限制）部分失败                                   */
    TS_WARNING_LOADFORBIDTIMEPARTLYFAILED       = 802050,   /**<加载初始化数据（申报禁止业务时间）部分失败                           */
    TS_WARNING_LOADMATCHTIMEPARTLYFAILED        = 802051,   /**<加载初始化数据（撮合交易阶段时间设置）部分失败                       */
    TS_WARNING_LOADDEFAULTSYSDATAPARTLYFAILED   = 802052,   /**<加载初始化数据（证券账户性质，交易单元类型默认禁止列表配置）部分失败 */

    TS_NOTICE_TEMP_CLOSE            = 802053,   /**<TS临时休市指令                         */
    TS_NOTICE_MANUAL_CLOSING        = 802054,   /**<TS手工收市                         */
    TS_NOTICE_TOWNET_ISSUE           = 802055,   /**<两网虚拟成交定时发布指令        201                   */
    TS_NOTICE_MARKET_ISSUE          = 802056,   /**<做市转让行情发布       400                   */
    TS_NOTICE_MARKET_MATCH          = 802057,   /**<做市转让撮合开始       401                   */
    TS_NOTICE_MARKET_CLOSE          = 802058,   /**<做市转让收市       403                   */

    /* 行情主机 */

    /* 成交前置机 */
    REPC_NOTICE_INIT_BEGIN              = 800401,	/**< 成交前置机初始化开始 */
    REPC_NOTICE_INIT_END                = 800402,	/**< 成交前置机初始化结束 */
    REPC_CRIT_INIT_FAIL                 = 800403,	/**< 成交前置机初始化失败 */
    REPC_NOTICE_WORK_NORMAL             = 800404,	/**< 成交前置机正常工作中 */
    REPC_CRIT_WORK_INNORMAL             = 800405,	/**< 成交前置机非正常工作 */

    /* 行情前置机 */

    /* 委托前置机 */

    /* 委托排队机 */

    /* 委托仲裁机 */

    /* 中登前置机 */
    CCOMM_NOTICE_INIT_BEGIN                = 800651,   //开始初始化,
    CCOMM_NOTICE_INIT_OK                   = 800652,   // 初始化成功
    CCOMM_CRIT_INIT_FAIL                   = 800653,   // 初始化失败
    CCOMM_NOTICE_WORK_NORMAL               = 800654,   // 正常工作中
    CCOMM_CRIT_WORK_ERROR                  = 800655,   // 非正常工作
    CCOMM_CRIT_INITFILE_ERROR              = 802701,   //初始化文件失败
    CCOMM_NOTICE_INITFILE_OK               = 802702,   //初始化文件成功
    CCOMM_NOTICE_IV_OPEN                   = 802704,   //打开IV文件
    CCOMM_NOTICE_IB_OPEN                   = 802705,   //打开IB文件
    CCOMM_NOTICE_SG_OPEN                   = 802706,   //打开SG文件
    CCOMM_NOTICE_GF_OPEN                   = 802707,   //打开GF文件
    CCOMM_NOTICE_GC_OPEN                   = 802708,   //打开GC文件
    CCOMM_NOTICE_MX_OPEN                   = 802709,   //打开MX文件
    CCOMM_NOTICE_MC_OPEN                   = 802710,   //打开MC文件
    CCOMM_NOTICE_CC_OPEN                   = 802711,   //打开CC文件
    CCOMM_NOTICE_TD_OPEN                   = 802712,   //打开TD文件
    CCOMM_NOTICE_XW_OPEN                   = 802713,   //打开XW文件
    CCOMM_NOTICE_ZH_OPEN                   = 802714,   //打开ZH文件
    CCOMM_NOTICE_IV_OK                     = 802715,   //IV文件接收成功
    CCOMM_NOTICE_IB_OK                     = 802716,   //IB文件接收成功
    CCOMM_NOTICE_SG_OK                     = 802717,   //SG文件接收成功
    CCOMM_NOTICE_GF_OK                     = 802718,   //GF文件接收成功
    CCOMM_NOTICE_GC_OK                     = 802719,   //GC文件接收成功
    CCOMM_NOTICE_MX_OK                     = 802720,   //MX文件接收成功
    CCOMM_NOTICE_MC_OK                     = 802721,   //MC文件接收成功
    CCOMM_NOTICE_CC_OK                     = 802722,   //CC文件接收成功
    CCOMM_NOTICE_TD_OK                     = 802723,   //TD文件接收成功
    CCOMM_NOTICE_XW_OK                     = 802724,   //XW文件接收成功
    CCOMM_NOTICE_ZH_OK                     = 802725,   //ZH文件接收成功
    
    
    /* 数据网关 */
    DATAGATEWAY_NOTICE_INIT_BEGIN       = 800701,   /* 数据网关初始化开始 */
    DATAGATEWAY_NOTICE_INIT_END         = 800702,   /* 数据网关初始化完成 */
    DATAGATEWAY_CRIT_INIT_FAILED        = 800703,   /* 数据网关初始化失败 */
    DATAGATEWAY_NOTICE_WORK_NORMAL      = 800704,   /* 数据网关正常工作中 */
    DATAGATEWAY_CRIT_WORK_ABNORMAL      = 800705,   /* 数据网关非正常工作 */

    /* 紧急维护转换机 */
    URC_NOTICE_INIT_START  	    = 800751, ////	紧急维护转换机初始化开始
    URC_NOTICE_INIT_FINISH 	    = 800752, ////	紧急维护转换机初始化完成
    URC_CRIT_INIT_FAILED 	    = 800753, ////	紧急维护转换机初始化失败
    URC_NOT_WORKING_OK 		    = 800754, ////	紧急维护转换机正常工作中
    URC_CRIT_WORK_ERR 		    = 800755,  ////	紧急维护转换机非正常工作
    /* 监控服务 */

    /* 初始化服务 */
    DB2DBF_NOTICE_INIT_BEGIN            = 800901,   /* 初始化服务：初始化开始 */
    DB2DBF_NOTICE_INIT_END              = 800902,   /* 初始化服务：初始化完成 */
    DB2DBF_CRIT_INIT_FAILED             = 800903,   /* 初始化服务：初始化失败 */
    DB2DBF_NOTICE_DUMP_BEGIN            = 800904,   /* 初始化服务：数据导出开始 */
    DB2DBF_NOTICE_DUMP_END              = 800905,   /* 初始化服务：数据导出完成 */
    DB2DBF_CRIT_DUMP_FAILED             = 800906    /* 初始化服务：数据导出失败 */
};



///公共模块：919000-919999
enum CommonEventId
{
    ERR_NONE                        = 0,        /* 成功 */

    COMMON_EVENT_ID_START           = 919000,   /* 公共错误码开始 */

    /* main库事件定义 */
    COMMON_ERROR_MAIN_CORE_DUMP     = 919100,   /* main库coredump事件 */

    /* 公共错误码 */
    COMMON_ERROR_READ_CONFIG_FAILED = 919900,   /* 读取配置项失败 */
    COMMON_ERROR_NEW_MEMORY_FAILED  = 919901,   /* 申请内存失败 */
    COMMON_ERROR_OPEN_QUEUE         = 919902,   /* 打开对垒失败 */
    COMMON_ERROR_CREATE_SHM         = 919903,   /* 建立共享内存失败 */
    COMMON_ERROR_SHM_MMAP           = 919904,   /* MMAP共享内存失败 */
    COMMON_ERROR_OPEN_SHM           = 919905,   /* 打开共享内存失败 */
    COMMON_ERROR_SHM_FSTAT          = 919906,   /* FSTAT共享内存失败  */
    COMMON_ERROR_OPEN_SEM           = 919907,   /* 打开信号量失败 */
    COMMON_ERROR_POST_SEM           = 919908,   /* POST 信号量失败 */
    COMMON_ERROR_WAIT_SEM           = 919909,   /* WAIT 信号量失败 */
    COMMON_ERROR_TIME_WAIT_SEM      = 919910,   /* TIME WAIT信号量失败 */
    COMMON_ERROR_TRY_WAIT_SEM       = 919911,   /* TRY WAIT信号量失败 */
    COMMON_ERROR_GET_SEM_VALUE      = 919912,   /* 获取信号量值失败  */
    COMMON_ERROR_CLOSE_SEM          = 919913,   /* 关闭信号量失败 */
    COMMON_ERROR_REMOVE_SEM         = 919914,   /* 删除信号量失败 */





    COMMON_EVENT_ID_END             = 919999    /* 公共错误码结束 */
};

///初始化服务：925000-929999
enum InitialServiceEventId
{
    DB2DBF_EVENT_ID_START               = 925000,   /* 初始化服务错误码开始 */

    DB2DBF_ERROR_INIT_DB_FAILED         = 925001,   /* 初始化数据库失败 */
    DB2DBF_ERROR_CREATE_DB_OBJ_FAILED   = 925002,   /* 创建数据库对象失败 */
    DB2DBF_INFO_TRANSFER_BEGIN          = 925003,   /* 转换数据开始 */
    DB2DBF_ERROR_CONNECT_DB_FAILED      = 925004,   /* 连接数据库失败 */
    DB2DBF_ERROR_EXECUTE_SQL_FAILED     = 925005,   /* 执行SQL语句失败 */
    DB2DBF_ERROR_SQL_SYNTAX_ERROR       = 925006,   /* SQL语句语法错误 */
    DB2DBF_ERROR_CREATE_DBF_FAILED      = 925007,   /* 创建DBF文件失败 */
    DB2DBF_ERROR_MAP_FIELD_FAILED       = 925008,   /* 数据库字段转换到DBF字段失败 */
    DB2DBF_ERROR_ADD_FIELD_FAILED       = 925009,   /* 新增DBF字段失败 */
    DB2DBF_ERROR_OPEN_DBF_FAILED        = 925010,   /* 打开DBF文件失败 */
    DB2DBF_ERROR_APPEND_FAILED          = 925011,   /* 设置增加模式失败 */
    DB2DBF_ERROR_SET_VALUE_FAILED       = 925012,   /* 设置字段值失败 */
    DB2DBF_ERROR_POST_FAILED            = 925013,   /* DBF提交失败 */
    DB2DBF_ERROR_APPEND_NEXT_FAILED     = 925014,   /* 增加下一条失败 */
    DB2DBF_INFO_TRANSFER_FINISH         = 925015,   /* 转换数据结束 */

    DB2DBF_EVENT_ID_END                 = 929999    /* 初始化服务错误码结束 */
};

///监控服务：930000-934999
enum MonProxyEventId
{
    MONPROXY_ERR_NOSHAREDMEMERRNO       =  931000,  /* 无法加载共享内存 */
    MONPROXY_CRIT_PROCESSSTOPERRNO      =  931001,  /* 进程停止 */
    MONPROXY_ERR_SRVTYPEDIF             =  931002,  /* 共享内存与配置文件中的主机类型不同 */
    MONPROXY_ERR_SRVIDDIF               =  931003,  /* 共享内存与配置文件中的主机标识不同 */
    MONPROXY_ERR_FILESIZEDIF            =  931004,  /* 共享文件大小与结构大小不一致*/
    MONPROXY_ERR_NOTEXISTPROC           =  931005   /* 在共享文件中没有获得进程PID*/
};

///监察管理服务：935000-939999


///紧急维护转换机事件：940000-944999
enum UrcommEventId
{
	URCOMM_ERR_NEW_NET				= 940001, /// 网络模块创建失败
	URCOMM_ERR_INIT_NET				= 940002, /// 网络模块初始化失败
	URCOMM_ERR_NEW_RM				= 940005, /// 组播模块创建失败
	URCOMM_ERR_INIT_RM				= 940006, /// 组播模块初始化失败
	URCOMM_INFO_WORK_CLOSE          = 940007, /// 紧急维护程序关闭
	URCOMM_ERR_DATA_GET             = 940010, /// 整理数据失败
	URCOMM_ERR_DATA_SEND            = 940011, /// 发送数据失败
	URCOMM_ERR_DATA_UPDATE          = 940012, /// 更新申报状态失败
	URCOMM_ERR_GET_ORDER            = 940014, /// 获取指令失败
	URCOMM_ERR_RM_NEW               = 940015, /// 创建组播接收实例失败

	URCOMM_ERR_RM_CREATE            = 940017, /// 初始化组播接收实例失败
	URCOMM_ERR_RM_START             = 940018, /// 启动组播接收器失败
	URCOMM_ERR_RM_STOCKINFO         = 940020, /// 组播模块更新证券信息表失败
	URCOMM_ERR_RM_UPDATE            = 940021, /// 组播模块更新指令执行结果失败
	URCOMM_ERR_INIT_SM		        = 940022, /// 共享内存初始化失败
	URCOMM_ERR_DBSTR		        = 940023, /// 数据库连接串为空


	URCOMM_ERR_INVALID_IP           = 940026, /// 无效ip地址，该ip不在配置文件中
	URCOMM_ERR_RM_INIT_PARAM        = 940027, /// 组播设置有空的
	URCOMM_ERR_RM_STOP              = 940028, /// 组播模块停止失败


	URCOMM_ERR_RM_CREAT_FILE		= 940031, /// 创建组播索引文件失败

    URCOMM_ERR_CONFIG_RM_FILE       = 940033, /// 组播索引文件名字配置为NULL
    URCOMM_ERR_DB_CTX               = 940034, /// 获取数据库上下文失败
    URCOMM_WAR_NET_TIMEOUT          = 940035, /// 网络连接超时，自动断开
    URCOMM_NET_INVALID_ARG          = 940036, /// 用于网络层OnError使用
    URCOMM_ERR_DIS_LINK             = 940037, /// 网络连接断开失败
    URCOMM_ERR_NET_ONERROR          = 940038, /// 网络底层出现错误
    URCOMM_ERR_DATA_COUNT           = 940039, /// 获取指令总数失败
    URCOMM_ERR_DATA_COUNT_LESS      = 940040, /// 指令总数小于排队机接收总数
    URCOMM_ERR_IP_NULL              = 940041, /// 监控ip或端口为null

    URCOMM_ERR_ACCEPTOR_NULL        = 940043, /// 适配类为NULL
    URCOMM_ERR_NET_NULL_IP          = 940044, /// 连接ip为空，请查看配置文件
    URCOMM_ERR_SHAREDATA_NULL       = 940045, /// m_lpMonData is null
    URCOMM_ERR_WRONG_STATUS         = 940046, /// 网络通信状态不一致


    URCOMM_ERR_SOCK_INDEX_MISMATCH  = 940049, /// socket索引不匹配
    URCOMM_ERR_DISCONNECT           = 940050, /// 断开连接错误
    URCOMM_INFO_ON_DISCONNECT       = 940051, /// 回调断开连接
    URCOMM_ERR_NO_ACK               = 940052, /// 没有ack,网络连接自动断开
    URCOMM_ERR_START_NET            = 940053, /// 网络启动失败
    URCOMM_ERR_DB_CLOSE             = 940054, /// 断开数据库链接失败
    URCOMM_ERR_RM_FILE_CLOSE        = 940055, /// 释放映射文件内存失败
    URCOMM_ERR_SEND_ARRAYINDEX      = 940056, /// 发送连接数据的索引非法
    URCOMM_ERR_COMM_STATUS          = 940057, /// 网络通信状态非法
    URC_ERR_RM_ONERROR              = 940058, /// 组播错误
    URC_WAR_SVR_STATUS              = 940059, /// 服务器状态没有准备好
    URCOMM_ERR_OBJ_NULL             = 940060, /// 创建对象为NULL
    URCOMM_ERR_CONNECT              = 940061, /// 发送NEEQ_CONNECT失败
    URCOMM_ERR_SEQNO                = 940062, /// 发送NEEQ_SEQNO失败
    URCOMM_ERR_WAIT_TIME            = 940063, /// wait_time配置错误
    URCOMM_NOTICE_SUSPEND_SUCC      = 802801, ///发送停牌指令成功总数
    URCOMM_NOTICE_SUSPEND_FAIL      = 802802, ///发送停牌指令失败总数
    URCOMM_NOTICE_RESUM_SUCC        = 802803, ///发送复牌指令成功总数
    URCOMM_NOTICE_RESUM_FAIL        = 802804, ///发送复牌指令失败总数
    URCOMM_NOTICE_HOLDER_SUCC       = 802805, ///发送证券账户紧急维护指令成功总数
    URCOMM_NOTICE_HOLDER_FAIL       = 802806, ///发送证券账户紧急维护指令失败总数
    URCOMM_NOTICE_HOLDERLIMIT_SUCC  = 802807, ///发送证券账户交易限制紧急维护指令成功总数
    URCOMM_NOTICE_HOLDERLIMIT_FAIL  = 802808, ///发送证券账户交易限制紧急维护指令失败总数
    URCOMM_NOTICE_STOCKEMERG_SUCC   = 802809, ///发送证券交易参数紧急维护指令成功总数
    URCOMM_NOTICE_STOCKEMERG_FAIL   = 802810, ///发送证券交易参数紧急维护指令失败总数
    URCOMM_NOTICE_STOCKLIMIT_SUCC   = 802811, ///发送证券业务类别紧急维护指令成功总数
    URCOMM_NOTICE_STOCKLIMIT_FAIL   = 802812, ///发送证券业务类别紧急维护指令失败总数
    URCOMM_NOTICE_BOND_SUCC      = 802813, ///发送质押式回购债券紧急维护指令成功总数
    URCOMM_NOTICE_BOND_FAIL      = 802814, ///发送质押式回购债券紧急维护指令失败总数
    URCOMM_NOTICE_BROKERNOLIMIT_SUCC = 802815, ///发送交易单元交易限制紧急维护指令成功总数
    URCOMM_NOTICE_BROKERNOLIMIT_FAIL = 802816, ///发送交易单元交易限制紧急维护指令失败总数
    URCOMM_NOTICE_MANUAL_CLOSING_FAIL= 802817, /// 发送手工收市指令失败
    URCOMM_NOTICE_TEMP_CLOSE_FAIL    = 802818, /// 发送临时停市指令失败
    URCOMM_NOTICE_MANUAL_CLOSING_SUCC= 802819, /// 发送手工收市指令成功
    URCOMM_NOTICE_TEMP_CLOSE_SUCC    = 802820, /// 发送临时停市指令成功
};

///数据网关事件：945000-949999
enum DataGatewayEventId
{
    DATAGATEWAY_EVENT_ID_START          = 945000,   /* 数据网关错误码开始 */

    DATAGATEWAY_ERROR_WRITEMSG_FAILED   = 945001,   /* 写落地文件失败 */
    DATAGATEWAY_ERROR_RM_ERROR          = 945002,   /* 组播层错误信息 */
    DATAGATEWAY_ERROR_INVALID_LENGTH    = 945003,   /* 接收的消息长度非法 */

    DATAGATEWAY_EVENT_ID_END            = 949999    /* 数据网关错误码结束 */
};

///中登前置机事件：950000-954999
enum CcommEventId
{
    CCOMM_INFO_NORMAL_MSG                = 950000,   // 正常的信息
    CCOMM_WARN_INIT_WARN                 = 950103,   // 初始化时出现警告
    CCOMM_WARN_RM_WARN                   = 950100,   // 组播相关警告
    CCOMM_INFO_RM_MSG                    = 950101,   // 组播模块相关信息
    CCOMM_ERROR_RM_ERROR                 = 950102,   // 组播模块错误
    CCOMM_INFO_TCP_MSG                   = 950201,   // tcp库相关信息
    CCOMM_ERROR_TCP_ERROR                = 950202,   // tcp库底层错误
    CCOMM_WARN_CC_WARN                   = 950300,   // 中登通讯警告
    CCOMM_INFO_CC_MSG                    = 950301,   // 中登通信相关信息
    CCOMM_ERROR_CC_ERROR                 = 950302,   // 中登通信相关错误(应用层错误)
    CCOMM_ERROR_CC_FILE_SYNC             = 950304,   // 发送断点同步包
    CCOMM_ERROR_CC_DATA_ERROR            = 950306,   // 数据出错
    CCOMM_ERROR_CC_VERIFY_ERROR          = 950308,   // 数据包较验出错
    CCOMM_ERROR_DBFFILE_ERROR            = 950402,   // DBF文件操作出错
    CCOMM_ERROR_OKFILE_ERROR             = 950404,   // OK文件操作出错
    CCOMM_ERROR_DAYEND_ERROR             = 950408,	// 日终检查出错
};

///委托仲裁机事件：955000-959999
enum ARBEventId
{
    ARB_NOTICE_START_INIT              = 800601,    //仲裁机开始初始化
    ARB_NOTICE_INIT_OK                 = 800602,    //初始化成功
    ARB_CRIT_INIT_FAIL                 = 800603,    //初始化失败
    ARB_NOTICE_IN_WORKING              = 800604,    //工作中
    ARB_NOTICE_OUT_OF_WORKING          = 800605,    //非正常工作中

    ARB_NOTICE_LOAD_CONFIG             = 803301,    //装载配置参数
    ARB_ERROR_LOAD_CONFIG_FAILED       = 803302,    //装载配置参数失败
    ARB_NOTICE_START_TCP_SERVER        = 803303,    //启动TCP SERVER
    ARB_ERROR_START_TCP_SERVER_FAILED  = 803304,    //启动TCP SERVER失败
    ARB_NOTICE_INIT_MON_DATA           = 803305,    //初始化监视数据
    ARB_NOTICE_START_TCP_SERVER_OK     = 803306,    //启动ABNET TCP SERVER成功

    ARB_RUN_LOG                        = 955001,    //仲裁机DEBUG或INFO下的log
    ARB_ERROR_ALLOCATE_OBJECT          = 955002,    //仲裁机ALLOCATE对象失败
    ARB_ERROR_CONFIG_PARAMTER          = 955003,    //仲裁机配置文件参数错
    ARB_ERROR_START_TCP_SERVER         = 955004,    //仲裁机启动TCP SERVER失败
    ARB_WARNING_TCP_DISCONNECTED       = 955005,    //与仲裁代理TCP连接断开
    ARB_WARNING_LOST_ACD_CONNECTION    = 955006,    //失去与仲裁代理的TCP连接
    ARB_WARNING_UNKNOWN_MSG            = 955007,    //接收到非法类型的消息
    ARB_WARNING_TCP_ERROR              = 955008,    //与代理的TCP连接出错
    ARB_ERROR_ILLEGAL_SOCKET_INDEX     = 955009,    //非法的SOCKET_INDEX.
    ARB_ERROR_ACD_NO_RESPONSE          = 955010,    //排队机在单位时间内无响应
    ARB_WARNING_ACTION_TYPE            = 955011,    //ACTION类型出错
    ARB_WARNING_SEND_DATA              = 955012,    //发送TCP 数据失败
    ARB_WARNING_EVENT_ID               = 955013,    //接收到非法的事件
    ARB_WARNING_ACD_ID                 = 955014,    //排队机ID非法
    ARB_WARNING_STATUS_CHANGE          = 955015,    //排队机状态改变
    ARB_CRIT_ACD_STATUS                = 955016,    //排队机所处状态不正确
    ARB_ERROR_OPEN_FILE                = 955017,    //打开排队机状态镜像文件失
    ARB_WARNNING_GET_EVENT             = 955018,    //排队机收到事件消息
    ARB_WARNING_NO_ACD_USABLE          = 955019,    //所有排队机都不可用
    ARB_ERROR_CREATE_TIMER             = 955020,    //建立定时器失败

};

///委托排队机事件：960000-964999
enum AcdEventId
{
    ACD_NOTICE_INIT_START               = 800551,  // 排队机初始化开始
    ACD_NOTICE_INIT_COMPLETE            = 800552,  // 排队机初始化完成
    ACD_CRIT_INIT_FAIL                  = 800553,  // 排队机初始化失败
    ACD_NOTICE_IN_WORKING               = 800554,  // 排队机正常工作中
    ACD_ERROR_OUT_OF_WORKING            = 800555,  // 排队机非正常工作

    ACD_NOTICE_INIT_INDEX_SHM           = 803001,  // 初始化排队机内存指针共享内存
    ACD_NOTICE_INIT_STAT_SHM            = 803002,  // 初始化统计信息共享内存
    ACD_NOTICE_INIT_TRADE_INFO_SHM      = 803003,  // 初始化交易信息共享内存
    ACD_NOTICE_INIT_LINK_STATUS_SHM     = 803004,  // 初始化LINK状态共享内存
    ACD_NOTICE_INIT_ORDER_SHM           = 803005,  // 初始化委托单共享内存
    ACD_NOTICE_INIT_MODULE_INFO_SHM     = 803006,  // 初始化模块信息共享内存
    ACD_NOTICE_INIT_SHM_OK              = 803007,  // 共享内存初始化成功
    ACD_NOTICE_INIT_MON_DATA            = 803008,  // 初始化监控信息
    ACD_NOTICE_INIT_MON_DATA_OK         = 803009,  // 初始化监控信息成功
    ACD_ERROR_LOAD_ORDER                = 803010,  // 从委托单镜像文件里
                                                   // 装载委托单失败
    ACD_NOTICE_START_PROXY              = 803011,  // 准备启动仲裁代理
    ACD_NOTICE_LOAD_CONFIG              = 803012,  // 装载配置参数
    ACD_NOTCIE_LOAD_CONFIG_FAILED       = 803013,  // 装载配置参数失败
    ACD_NOTCIE_LOAD_CONFIG_OK           = 803014,  // 装载配置参数成功
    ACD_NOTICE_CONNECT_ARB              = 803015,  // 连接仲裁服务器
    ACD_NOTICE_CONNECT_ARB_OK           = 803016,  // 连接仲裁服务器成功
    ACD_NOTICE_CONNECT_ARB_FAILED       = 803017,  // 连接仲裁服务器失败
    ACD_NOTICE_GET_STATUS               = 803018,  // 获取排队机主备机状态
    ACD_NOTICE_GET_STATUS_OK            = 803019,  // 获取排队机准备机状态成功
    ACD_NOTICE_START_PROCESS            = 803020,  // 启动业务进程
    ACD_NOTICE_START_PROCESS_OK         = 803021,  // 业务进程启动成功
    ACD_NOTICE_START_PROCESS_FAILED     = 803022,  // 业务进程启动失败
    ACD_NOTICE_GOES_INTO_SERVICE        = 803023,  // 排队机进入业务工作状态

    DISPATCH_DEBUG_QUEUE_PACKAGE        = 960001,       // 收到QUEUE中的数据包
    DISPATCH_DEBUG_TCP_PACKAGE          = 960002,       // 收到TCP数据包
    DISPATCH_DEBUG_RECEIVE_IDLE         = 960003,       // 接收到心跳数据包
    DISPATCH_DEBUG_ON_HEART             = 960004,       // TCP心跳事件
    DISPATCH_NOTICE_LINK                = 960005,       // LINK表更新
    DISPATCH_NOTICE_EXIT                = 960006,       // 模块退出运行
    DISPATCH_NOTICE_CONNECT             = 960007,       // TCP客户端连接服务器成功
    DISPATCH_WARNING_PACKAGE_LENGTH     = 960008,       // 数据包长度错误
    DISPATCH_WARNING_SET_TCP_PARAM      = 960009,       // 设置TCP参数失败
    DISPATCH_WARNING_CLOSE              = 960010,       // 关闭TCP连接
    DISPATCH_WARNING_RECEIVE_UNKNOWN    = 960011,       // 接收到不可识别类型的数据包
    DISPATCH_WARNING_TIME_OUT           = 960012,       // TCP TIMEOUT事件
    DISPATCH_WARNING_LINK_STATUS        = 960013,       // LINK状态错误，当前正在处理委托
    DISPATCH_WARNING_CONNECTION_INVALID = 960014,       // 无效的链路的TCP连接
    DISPATCH_ERROR_LINK_LENGTH          = 960015,       // LINK ID通知中，长度错误
    DISPATCH_ERROR_PROCESS_ID           = 960016,       // PROCESS ID错误
    DISPATCH_ERROR_INIT_THREAD          = 960017,       // 线程初始化失败
    DISPATCH_ERROR_INIT_TCP             = 960018,       // TCP初始化失败
    DISPATCH_ERROR_CONFIG               = 960019,       // 配置加载失败
    DISPATCH_ERROR_CONNECT              = 960020,       // 连接前置机或者紧急指令发生器失败
    DISPATCH_ERROR_QUEUE_WRITE          = 960021,       // 写入QUEUE失败
    DISPATCH_ERROR_QUEUE_READ           = 960022,       // 读取QUEUE失败
    DISPATCH_ERROR_TCP_SEND             = 960023,       // TCP发送数据失败
    DISPATCH_ERROR_TCP_RECONNECT        = 960024,       // TCP重连接失败
    DISPATCH_ERROR_TCP_MES              = 960025,       // TCP ERROR事件
    DISPATCH_ERROR_START_TIMER          = 960026,       // 设置计时器失败
    DISPATCH_ERROR_TCP_ALL_DISCONNECT   = 960027,       // 所有TCP连接断开
    DISPATCH_ERROR_CREATE_TIMER         = 960028,       // 建立重连定时器失败
    DISPATCH_WARNING_DISCARD_ORDERS     = 960029,       // 丢弃委托单警告

    HANDLER_DEBUG_QUEUE_PACKAGE         = 960501,       // 收到队列中的数据包
    HANDLER_DEBUG_SHM_INDEX             = 960502,       // 更新共享内存中的委托指针
    HANDLER_DEBUG_RM_SEMAPHORE          = 960503,       // 通知组播模块开始组播
    HANDLER_DEBUG_SYNC_SEMAPHORE        = 960504,       // 通知同步模块开始同步
    HANDLER_DEBUG_ORDER_ACK             = 960505,       // 回复ORDER ACK
    HANDLER_INFO_IGNORE_PACKAGE         = 960506,       // 时间初始化前，忽略队列中的数据包
    HANDLER_NOTICE_EXIT                 = 960507,       // 模块退出运行
    HANDLER_ERROR_PROCESS_ID            = 960508,       // PROCESS ID错误
    HANDLER_ERROR_INIT_THREAD           = 960509,       // 线程初始化失败
    HANDLER_ERROR_QUEUE_WRITE           = 960510,       // 写入QUEUE失败
    HANDLER_ERROR_QUEUE_READ            = 960511,       // 读取QUEUE失败
    HANDLER_ERROR_ORDER_IGNORE          = 960512,       // 闭市后丢弃后续的委托
    HANDLER_ERROR_MACHINE_STATUS        = 960513,       // MACHINE STATUS错误
    HANDLER_ERROR_MIRROR                = 960514,       // 写入落地文件失败
    HANDLER_ERROR_ORDER_LENGTH          = 960515,       // 委托或者伪委托长度错误
    HANDLER_ERROR_CONFIG                = 960516,       // 配置加载失败
    HANDLER_ERROR_GET_SYSTEM_DATE       = 960517,       // 读取当前时间失败
    HANDLER_CRIT_MEMORY_OVERFLOW        = 960518,       // 委托单共享内存用尽
    HANDLER_WARNING_MEMORY_THRESHOLD    = 960519,       // 委托单共享内存达到告警阀值
    HANDLER_WARNING_MARKET_CLOSE        = 960520,       // 接收市场闭市或者收市指令

    INSTR_DEBUG_TIME_STAMP              = 961001,       // 发送时间片伪委托
    INSTR_NOTICE_MARCKET                = 961002,       // 发送市场信息伪委托
    INSTR_NOTICE_EXIT                   = 961003,       // 模块退出运行
    INSTR_ERROR_CONFIG                  = 961004,       // 配置加载失败
    INSTR_ERROR_PROCESS_ID              = 961005,       // PROCESS ID错误
    INSTR_ERROR_INIT_THREAD             = 961006,       // 线程初始化失败
    INSTR_ERROR_DBF_FILE                = 961007,       // DBF文件加载失败
    INSTR_ERROR_QUEUE_WRITE             = 961008,       // 写入QUEUE失败

    RMAPP_DEBUG_PACKAGE                 = 961501,       // 组播委托
    RMAPP_NOTICE_INIT_BEGIN             = 961502,       // 初始化开始
    RMAPP_CRIT_INIT_FAIlED              = 961503,       // 初始化失败
    RMAPP_NOTICE_INIT_END               = 961504,       // 初始化成功
    RMAPP_ERROR_OPEN_SEM_FAILED         = 961505,       // 打开信号灯失败
    RMAPP_ERROR_OPEN_SHM_FAILED         = 961506,       // 打开共享内存失败
    RMAPP_ERROR_RMSENDER_NEW_FAILED     = 961507,       // 实例化发送端失败
    RMAPP_ERROR_RMSENDER_CREATE_FAILED  = 961508,       // 初始化发送端对象失败
    RMAPP_ERROR_RMSENDER_INIT_FAILED    = 961509,       // 初始化发送端失败
    RMAPP_ERROR_RMSENDER_START_FAILED   = 961510,       // 启动失败
    RMAPP_ERROR_RMSENDER_STOP_FAILED    = 961511,       // 停止失败
    RMAPP_ERROR_RMSENDER_PUSH_FAILED    = 961512,       // 丢数据给组播模块失败

    MSYNC_ERROR_PROCESS_INDEX           = 962001,       // 命令行-r参数进程序号错误
    MSYNC_ERROR_CONFIG_PARAMETER        = 962002,       // 配置文件里配置参数错
    MSYNC_ERROR_START_TCP_SERVER        = 962003,       // 主机同步启动TCP SERVER失败
    MSYNC_WARNING_TCP_DISCONNECTED      = 962004,       // 失去与备机同步TCP连接
    MSYNC_WARNING_UNKNOW_MSG            = 962005,       // 主机同步程序接收到非法类型消息
    MSYNC_WARNING_TCP_ERROR             = 962006,       // 主机同步程序TCP连接报错
    MSYNC_WARNING_NO_HISTRORY_DATA      = 962007,       // 主机同步程序获取不到历史委托单`
    MSYNC_WARNING_CURINDEX_ILLEGAL      = 962008,       // CurIndex值非法
    MSYNC_WARNING_CONFIRMINDEX_ILLEGAL  = 962009,       // ConfirmIndex值非法
    MSYNC_WARNING_SYNCINDEX_ILLEGAL     = 962010,       // SyncIndex 值非法
    MSYNC_CRIT_CONFIRM_SYNCINDEX_ILLEGAL = 962011,      // 同步确认消息中的同步指针非法
    MSYNC_CRIT_SYNCINDEX_G_CONFIRMINDEX  = 962012,      // 同步过程中，SYNCINDEX超越CONFIRMINDEX
    MSYNC_CRIT_SYNCINDEX_G_CURINDEX     = 962013,       // 同步过程中，SYNCINDEX超越CURINDEX
    MSYNC_WARNING_LINKID                = 962014,       // LINKID超越最大值
    MSYNC_WARNING_WRITE_QUEUE           = 962015,       // 写队列失败
    MSYNC_WARNING_SEND_DATA             = 962016,       // 发送TCP数据失败
    MSYNC_ERROR_GET_MSG_SIZE            = 962017,       // 获取消息队列大小失败
    MSYNC_ERROR_ALLOCATE_BUF            = 962018,       // 分配缓冲区失败
    MSYNC_WARNING_READ_QUEUE_FAILED     = 962019,       // 读取队列数据失败
    MSYNC_WARNING_SYNC_RESP             = 962020,       // 在同步协议规定的时间内,
                                                        // 备机无响应
    MSYNC_WARNING_RECONNECT_TIMEOUT     = 962021,       // 备机重连超时
    MSYNC_ERROR_WRITE_QUEUE             = 962022,       // 主机同步模块写队列失败
    MSYNC_ERROR_CREATE_TIMER            = 962023,       // 建立定时器失败

    SSYNC_ERROR_PROCESS_INDEX           = 963001,       //备机同步程序PROCESS INDEX非法
    SSYNC_ERROR_CONFIG_PARAMETER        = 963002,       //备机同步程序配置文件参数错误
    SSYNC_ERROR_CONNECT_MMSYC           = 963003,       //备机连接主机同步失败
    SSYNC_WARNING_TCP_DISCONNECTED      = 963004,       //与主机同步TCP连接断开
    SSYNC_WARNING_UNKNOWN_MSG           = 963005,       //备机同步程序接受到非法类型消息
    SSYNC_WARNING_TCP_ERROR             = 963006,       //同步TCP连接出错
    SSYNC_WARNING_SEND_DATA             = 963007,       //发送TCP数据失败
    SSYNC_WARNIN_GET_SYSTEM_DATE        = 963008,       //取系统日期失败
    SSYNC_ERROR_OPEN_MIRROR_FILE        = 963009,       //打开委托单镜像文件失败
    SSYNC_WARNING_SYNCINDEX             = 963010,       //同步指针非法
    SSYNC_WARNING_WRITE_MIRROR          = 963011,       //写委托单镜像失败
    SSYNC_WARNING_RECONNECT_N           = 963012,       //同步TCP重连第N次失败
    SSYNC_WARNING_FINAL_RECONNECT       = 963013,       //同步重连N次后最后失败             
    SSYNC_ERROR_WRITE_QUEUE             = 963014,       //北京同步模块写EVENT QUEUE失败
    SSYNC_CRIT_SYNC_POINT               = 963015,       //备机拥有的委托单大于主机，主备机
                                                        //同步点不匹配
    SSYNC_WARNING_SERVICE_STOP          = 963016,       //备机同步停止
    SSYNC_WARNING_ROLLBACK              = 963017,       //备机同步回退记录
    SSYNC_ERROR_CONNECT_MSYNC           = 963018,       //启动后连接主机同步服务器失败

    PROXY_ERROR_CONFIG_PARAMETER        = 965001,       // PROXY配置文件里参数错误
    PROXY_ERROR_CONNECT_ARB             = 965002,       // PROXY连接仲裁失败
    PROXY_WARNING_TCP_ERROR             = 965003,       // 与仲裁服务器的TCP连接出错
    PROXY_WARNING_UNKNOWN_MSG           = 965004,       // 仲裁代理接收到非法类型消息
    PROXY_WARNING_TCP_DISCONNECTED      = 965005,       // 与仲裁服务器的TCP连接断开
    PROXY_WARNING_SEND_DATA             = 965006,       // 发送数据失败
    PROXY_ERROR_NEW_MACHINE_STATUS      = 965007,       // 仲裁代理处理新的机器状态失败
    PROXY_WARNING_WRITE_QUEUE           = 965008,       // 仲裁代理写队列失败
    PROXY_ERROR_WAIT_CHILD_PROCESS      = 965009,       // 仲裁代理获取子进程状态失败
    PROXY_WARNING_READ_QUEUE            = 965010,       // 仲裁代理读取队列失败
    PROXY_WARNING_UNKNOWN_EVENT         = 965011,       // 仲裁代理接收到非法类型的事件
    PROXY_ERROR_GET_QUEUE_SIZE          = 965012,       // 仲裁代理获取队列大小失败
    PROXY_ERROR_ALLOCATE_BUF            = 965013,       // 获取接收QUEUE消息的BUF失败
    PROXY_ERROR_OPEN_PROCESS_CONFIG     = 965014,       // 打开进程配置文件失败
    PROXY_ERROR_PROCESS_INDEX           = 965015,       // 进程INDEX非法
    PROXY_ERROR_PROCESS_NAME            = 965016,       // 进程名非法
    PROXY_WARNING_PROCESS_NAME_LEN      = 965017,       // 进程名长度超标
    PROXY_ERROR_PROCESS_POINTER         = 965018,       // 进程信息内存指针为空
    PROXY_ERROR_FORK                    = 965019,       // FORK子进程失败
    PROXY_WARNING_APP_STOP              = 965020,       // 子进程CRASH
    PROXY_ERROR_CREATE_TIMER            = 965021,       // 建立定时器失败

    ACD_RUN_LOG                         = 966001,       // DEBUG或INFO等级下的LOG
    ACD_ERROR_ALLOCATE_OBJECT           = 966002,       // 分配对象失败
    ACD_ERROR_PROCESS_INDEX_ILLEGAL     = 966003,       // 非法的PROCESS INDEX
    ACD_ERROR_STAT_TYPE                 = 966004,       // 统计类型错误
    ACD_ERROR_MACHINE_TYPE              = 966005,       // 机器类型错误

};

///委托前置机事件：965000-969999
enum ACDFrontEventId
{
    FRONT_NOTICE_INIT_START                 = 800501,       // 委托前置机初始化开始
    FRONT_NOTICE_INIT_COMPLETE              = 800502,       // 初始化完成
    FRONT_CRIT_INIT_FAIL                    = 800503,       // 委托前置机初始化失败
    FRONT_NOTICE_IN_WORKING                 = 800504,       // 委托前置机正常工作中
    FRONT_ERROR_OUT_OF_WORKING              = 800505,       // 委托前置机非正常工作

    FRONT_NOTICE_INIT_ACD_SERVER            = 802901,       // 初始化排队机侧TCP SERVER
    FRONT_NOTICE_INIT_SSC_SERVER            = 802902,       // 初始化深证通侧TCP SERVER
    FRONT_NOTICE_INIT_MON_SHM               = 802903,       // 委托前置机初始化监视共享内存

    FRONT_DEBUG_RECEIVE_BIZ                 = 965001,       // 接收到数据包
    FRONT_DEBUG_RECEIVE_IDLE                = 965002,       // 接收到心跳数据包
    FRONT_DEBUG_ON_HEART                    = 965003,       // TCP心跳事件
    FRONT_RUN_LOG                           = 965004,       // INFO或DEBUG等级LOG

    FRONT_NOTICE_EXIT                       = 965101,       // 进程退出运行
    FRONT_NOTICE_SERVER_ACCEPT              = 965102,       // ACCEPT新的TCP客户端
    FRONT_NOTICE_UPDATE_ROLE                = 965103,       // 更新ACD的LINK ROLE

    FRONT_WARNING_LINK_ID_UNKNOWN           = 965201,       // 深证通的LINK ID未找到
    FRONT_WARNING_CLOSE                     = 965202,       // 关闭TCP连接
    FRONT_WARNING_SET_TCP_PARAM             = 965203,       // 设置TCP参数失败
    FRONT_WARNING_RECEIVE_QUIT              = 965204,       // 接收到退出数据包
    FRONT_WARNING_RECEIVE_UNKNOWN           = 965205,       // 接收到不可识别类型的数据包
    FRONT_WARNING_TIME_OUT                  = 965206,       // TCP TIMEOUT事件
    FRONT_WARNING_PACKAGE_LENGTH            = 965207,       // 数据包长度非法
    FRONT_WARNING_ROLE_DOWN                 = 965208,       // 接收到排队机降低身份数据包
    FRONT_WARNING_ROLE_FAIL                 = 965209,       // ACD ROLE检查失败
    FRONT_WARNING_ACD_INVALID               = 965210,       // 无效的ACD连接
    FRONT_WARNING_SSC_INVALID               = 965211,       // 无效的SSC连接

    FRONT_ERROR_ALLOCATE_SERVER             = 965301,       // 申请SERVER对象内存失败
    FRONT_ERROR_CONFIG                      = 965302,       // 配置加载失败
    FRONT_ERROR_SERVER_CREATE               = 965303,       // TCP SERVER创建失败
    FRONT_ERROR_TCP_MES                     = 965304,       // TCP ERROR事件
    FRONT_ERROR_SEND_DATA                   = 965305,       // TCP SEND出错
    FRONT_ERROR_START_TIMER                 = 965306,       // 设置计时器失败
};

///行情前置机事件：970000-974999
enum QfepEventId
{
	///800451-800500
	///时序
	QFEP_NOTICE_INIT_BEGIN = 800451,//970601,///初始化开始
	QFEP_NOTICE_INIT_END = 800452,//970602,///初始化结束
	QFEP_CRIT_INIT_FAILED = 800453,///初始化失败
	QFEP_NOTICE_QUOT_PUBLICING = 800454,///行情发布中
	QFEP_NOTICE_CLOSE_1_BEGIN = 800456,///闭市1开始
	QFEP_NOTICE_CLOSE_1_END = 800457,///闭市1结束
	QFEP_CRIT_CLOSE_1 = 800458,///闭市1失败
	QFEP_NOTICE_CLOSE_2_BEGIN = 800459,///闭市2开始
	QFEP_NOTICE_CLOSE_2_END = 800460,///闭市2结束
	QFEP_CRIT_CLOSE_2 = 800461,///闭市2失败
	QFEP_NOTICE_LOAD_MATCHTIME_END = 802501,///加载qfep_matchtime.dbf成功
	QFEP_CRIT_LOAD_MATCHTIME_FAILED = 802502,///加载qfep_matchtime.dbf失败
	QFEP_NOTICE_MKTALLOWORDER = 802503,////**< 开市:0915 */
	QFEP_NOTICE_MKTAMCLOSE = 802504,////**< 上午竞价休市:1130 */
	QFEP_NOTICE_MKTPMOPEN = 802505,////**< 下午竞价开始:1300 */
	QFEP_NOTICE_MKTPMCLOSE = 802506,///**下午闭市：1500 <= time 
	QFEP_NOTICE_MKTEVOPEN = 802507,///**盘后交易开市：1500≤time＜1530 */
	QFEP_NOTICE_MKTEVCLOSE = 802508,///**< 盘后交易闭市：1530≤time */
	///***crit(970000~970100)***/
	///公共
	QFEP_CRIT_MEM_OUT = 970000,///内存不足
	QFEP_CRIT_READ_CONF = 970001,///读取配置文件错误
	QFEP_CRIT_SHAREDMEM_INIT = 970002,///共享内存初始化
	QFEP_CRIT_LOAD_INIT = 970003,///初始化读取dbf错误
	QFEP_CRIT_READ_BACKUP_FILE = 970004,///读取灾备文件错误
	///组播(11~20)
	QFEP_CRIT_RM_INIT = 970011,///组播初始化失败
	QFEP_CRIT_RM_LOCAL_FIlE_INIT = 970012,///组播落地文件初始化失败
	///write dbf(21~30)
	QFEP_CRIT_WRITE_DBF_INIT = 970021,///写dbf初始化失败
	///tcp(31~40)
	QFEP_CRIT_TCP_INIT = 970031,///tcp初始化失败
	///udp(41~50)
	QFEP_CRIT_UDP_INIT = 970041,///udp初始化失败	
	///公告(51~60)
	QFEP_CRIT_NOTICE_INIT = 970051,///公告扫描初始化失败
	///***err(970101~970400)***/
	///公共(101~150)
	QFEP_ERROR_GET_MEMDATA = 970101,///获得内存数据错误
	///组播(151~170)
	QFEP_ERROR_RM_THREAD_START = 970151,///组播线程启动失败
	QFEP_ERROR_RM_THREAD_STOP = 970152,///组播线程停止失败
	QFEP_ERROR_RM = 970153,///组播错误
	QFEP_ERROR_RM_DATA = 970154,///可靠组播接收到错误数据
	QFEP_ERROR_RM_WRITE_LOCAL_FILE = 970155,///组播数据落地失败
	///write dbf(171~190)
	QFEP_ERROR_WRITE_DBF_THREAD_START = 970171,///dbf线程启动失败
	QFEP_ERROR_WRITE_DBF_THREAD_STOP = 970172,///dbf线程停止失败
	QFEP_ERROR_WRITE_DBF = 970173,///Dbf写入失败
	QFEP_ERROR_BACKUP_DBF = 970174,///留痕失败
	///tcp(191~210)
	QFEP_ERROR_TCP_THREAD_START = 970191,///tcp线程启动失败
	QFEP_ERROR_TCP_THREAD_STOP = 970192,///tcp线程停止失败
	QFEP_ERROR_TCP_SEND = 970193,///TCP发送失败
	QFEP_ERROR_TCP_SOCKET_MANAGE = 970194,///管理sockindex失败
	///udp(211~230)
	QFEP_ERROR_UDP_THREAD_START = 970211,///udp线程启动失败
	QFEP_ERROR_UDP_THREAD_STOP = 970212,///udp线程停止失败
	QFEP_ERROR_UDP_SEND = 970213,///UDP发送失败
	///公告(231~250)
	QFEP_ERROR_NOTICE_THREAD_START = 970231,///notice线程启动失败
	QFEP_ERROR_NOTICE_THREAD_STOP = 970232,///notice线程停止失败
	QFEP_ERROR_SCAN_NOTICE = 970233,///扫描公告错误
	///***warning(970401~970600)***/
	///公共(401~450)
	///组播(451~470)
	///write dbf(471~490)
	///tcp(491~510)
	QFEP_WARNING_TCP_SOCKET_FULL = 970500,///tcp连接超限
	///udp(511~530)
	///公告(531~550)
	///***notice(970601~970700)***/
	///公共(601~630)
	QFEP_NOTICE_WORK_NORMAL = 970603,///正常工作
	QFEP_NOTICE_RM_RECOVERY = 970604,///组播灾备
	QFEP_NOTICE_NOTICE_RECOVERY = 970605,///公告灾备
	///市场状态指令(631~640)
	QFEP_NOTICE_TMP_CLOSE = 970634,///临时停市
	///tcp(641~650)
	QFEP_NOTICE_TCP_DISCONNECT = 970641,///tcp断开连接
	///***info(970701~970900)***/
	///公共(701~730)
	///数据处理(731~740)
	QFEP_INFO_DATA_PROCESSOR_INIT_BEGIN = 970731,///数据处理模块初始化开始
	QFEP_INFO_DATA_PROCESSOR_INIT_END = 970732,///数据处理模块初始化结束
	///共享内存(741~750)
	QFEP_INFO_SHAREDMEM_INIT_BEGIN = 970741,///共享内存初始化开始
	QFEP_INFO_SHAREDMEM_INIT_END = 970742,///共享内存初始化结束
	///加载dbf(751~760)
	QFEP_INFO_LOAD_DBF_INIT_BEGIN = 970751,///加载DBF初始化开始
	QFEP_INFO_LOAD_DBF_INIT_END = 970752,///加载DBF初始化结束
	///组播(761~770)
	QFEP_INFO_RM_INIT_BEGIN = 970761,///组播初始化开始
	QFEP_INFO_RM_INIT_END = 970762,///组播初始化结束
	QFEP_INFO_RM_THREAD_START = 970763,///组播线程启动
	QFEP_INFO_RM_THREAD_STOP = 970764,///组播线程停止
	//QFEP_INFO_RM_CREATE_DATA_FILE_BEGIN = 970765,///创建组播落地文件开始
	//QFEP_INFO_RM_CREATE_DATA_FILE_END = 970766,///创建组播落地文件结束
	///write dbf(771~780)
	QFEP_INFO_DBF_WRITER_INIT_BEGIN = 970771,///组播初始化开始
	QFEP_INFO_DBF_WRITER_INIT_END = 970772,///组播初始化结束
	QFEP_INFO_WRITE_DBF_THREAD_START = 970773,///dbf线程启动
	QFEP_INFO_WRITE_DBF_THREAD_STOP = 970774,///dbf线程停止
	///tcp(781~790)
	QFEP_INFO_TCP_SENDER_INIT_BEGIN = 970781,///tcp初始化开始
	QFEP_INFO_TCP_SENDER_INIT_END = 970782,///tcp初始化结束
	QFEP_INFO_TCP_THREAD_START = 970783,///tcp线程启动
	QFEP_INFO_TCP_THREAD_STOP = 970784,///tcp线程停止
	///udp(791~800)
	QFEP_INFO_UDP_SENDER_INIT_BEGIN = 970791,///udp初始化开始
	QFEP_INFO_UDP_SENDER_INIT_END = 970792,///udp初始化结束
	QFEP_INFO_UDP_THREAD_START = 970793,///udp线程启动
	QFEP_INFO_UDP_THREAD_STOP = 970794,///udp线程停止
	///公告(801~810)
	QFEP_INFO_NOTICE_INIT_BEGIN = 970801,///公告初始化开始
	QFEP_INFO_NOTICE_INIT_END = 970802,///公告初始化结束
	QFEP_INFO_NOTICE_THREAD_START = 970803,///notice线程启动
	QFEP_INFO_NOTICE_THREAD_STOP = 970804,///notice线程停止
	///***debug(970901~971000)***/
	QFEP_DEBUG = 970901///debug
};

///成交前置机事件：975000-979999
enum RepcommEventId
{
    REPC_NOTICE_S_BROKENO               = 802601, /**< 发送交易单元次数和时间  */
    REPC_NOTICE_S_STOCKTYPE             = 802602, /**< 发送证券类别次数和时间  */
    REPC_NOTICE_S_TRADING_START         = 802603, /**< 发送开市指令和时间  */
    REPC_NOTICE_S_AM_OPEN               = 802604, /**< 发送上午竞价指令  */
    REPC_NOTICE_S_AM_CLOSE              = 802605, /**< 发送上午休市指令  */
    REPC_NOTICE_S_PM_OPEN               = 802606, /**< 发送下午竞价指令  */
    REPC_NOTICE_S_PM_CLOSE              = 802607, /**< 发送下午休市指令  */
    REPC_NOTICE_R_TRADING_START         = 802608, /**< 接收开市指令  */
    REPC_NOTICE_R_AM_OPEN               = 802609, /**< 接收上午竞价指令  */
    REPC_NOTICE_R_AM_CLOSE              = 802610, /**< 接收上午休市指令  */
    REPC_NOTICE_R_PM_OPEN               = 802611, /**< 接收下午竞价指令  */
    REPC_NOTICE_R_PM_CLOSE              = 802612, /**< 接收下午休市指令  */
    REPC_NOTICE_DBF_MAKET_MAKER         = 802613, /**< 已加载做市商dbf  */
    REPC_NOTICE_DBF_MATCHTIME           = 802614, /**< 已加载交易时段dbf  */
    REPC_NOTICE_DBF_PBU                 = 802615, /**< 已加载交易单元dbf  */
    REPC_NOTICE_DBF_STOCK_INFO          = 802616, /**< 已加载证券信息dbf  */
    REPC_NOTICE_S_TIME_NOW              = 802617, /**< 发送交易系统时间次数和时间*/
    REPC_NOTICE_S_MARKET_MAKER          = 802618, /**< 发送做市商次数和时间 */
    REPC_NOTICE_S_BUSINESS_PERIOD       = 802619, /**< 发送时间段次数和时间 */
    REPC_NOTICE_S_STOCK_INFO            = 802620, /**< 发送证券信息次数和时间*/ 
    REPC_NOTICE_S_MARKET_STATUS         = 802621, /**< 发送市场状态次数和时间*/

    REPC_CRI_NO_MEM				      = 975000,	/**< 申请内存失败 */
    REPC_ERR_RM_ONERROR			      = 975001,	/**< 组播错误 */
    REPC_WAR_STOCK_CODE	              = 975002,	/**< 更新证券信息时不存在的证券代码 */
    REPC_INF_INIT                     = 975003, /**< 初始化时打印信息 */
    REPC_ERR_CFG			          = 975004,	/**< 初始化时配置错误 */
    REPC_ERR_SHM                      = 975005, /**< 初始化时监控共享内存错误 */
    REPC_WAR_SVR_STATUS               = 975006, /**< 系统状态错误 */
    REPC_WAR_SSC_INDEX                = 975007, /**< 深圳通回调时连接号不匹配 */
    REPC_WAR_SSC_ARG                  = 975008, /**< 深圳通回调时参数无效 */
    REPC_INF_SSC_CONNECT    	      = 975009, /**< 深圳通建立连接 */
    REPC_INF_SSC_DISCONNECT    	      = 975010, /**< 深圳通断开连接 */
    REPC_ERR_SSC_PROTOCOL             = 975011, /**< 深圳通协议错误 */
    REPC_ERR_SSC_IP                   = 975012, /**< 深圳通请求连接的IP地址不在配置文件中 */
    REPC_WAR_SSC_SEND                 = 975013, /**< 深圳通连接发送失败 */
    REPC_WAR_SSC_TIME_OUT             = 975014, /**< 深圳通接收超时30s没收到数据 */
    REPC_ERR_ACCEPTOR_CREATE          = 975015, /**< 创建tcp侦听失败 */
    REPC_ERR_ACCEPTOR_DESTROY         = 975016, /**< 销毁tcp侦听失败 */
    REPC_WAR_ACCEPTOR_ONERROR         = 975017, /**< tcp通信库错误 */
    REPC_ERR_ACCEPTOR_DISCONNECT      = 975018, /**< tcp断开连接失败 */
    REPC_INF_THREAD_START             = 975019, /**< 线程启动 */
    REPC_INF_THREAD_STOP              = 975020, /**< 线程停止 */
    REPC_ERR_THREAD_START             = 975021, /**< 线程启动失败 */
    REPC_ERR_THREAD_STOP              = 975022, /**< 线程停止失败 */
    REPC_ERR_FILE_OPEN                = 975023, /**< 打开文件失败 */
    REPC_ERR_FILE_READ                = 975024, /**< 读文件失败 */
    REPC_WAR_FILE_WRITE               = 975025, /**< 写文件失败 */
    REPC_WAR_FILE_SEEK                = 975026, /**< 移动文件偏移失败 */
    REPC_WAR_FILE_EINTR               = 975027, /**< 由于线程停止,写文件中断 */
    REPC_WAR_FILE_SYNC                = 975028, /**< 文件刷磁盘失败 */
    REPC_ERR_FILE_DATA                = 975029  /**< 文件头和内容不匹配 */
};

///交易管理事件：980000-984999
///监察主机事件：985000-989999

///行情主机事件：990000-994999
enum QsEventId
{
    /** 以下是时序通知 */
    QS_NOTICE_START_SUCCESS            =	800101,	/**< QS初始化开始 */
    QS_NOTICE_INIT_SUCCESS             =	800102,	/**< QS初始化完成 */
    QS_NOTICE_INIT_FAIL                =	800103,	/**< QS初始化失败 */
    QS_NOTICE_AM_INIT_START            =	800104, /**< QS上午开市开始 */
    QS_NOTICE_AM_INIT_END              =	800105, /**< QS上午开市结束 */
    QS_NOTICE_AM_INIT_FAIL             =	800106, /**< QS上午开市失败 */
    QS_NOTICE_NM_INIT_START            =	800107, /**< QS上午休市开始 */
    QS_NOTICE_NM_INIT_END              =	800108, /**< QS上午休市结束 */
    QS_NOTICE_NM_INIT_FAIL             =	800109, /**< QS上午休市失败 */
    QS_NOTICE_PV_INIT_START            =	800110, /**< QS下午开市开始 */
    QS_NOTICE_PV_INIT_END              =    800111, /**< QS下午开市结束 */
    QS_NOTICE_PV_INIT_FAIL             =    800112, /**< QS下午开市失败 */
    QS_NOTICE_CLOSE_START              =	800113,	/**< QS闭市开始 */
    QS_NOTICE_CLOSE_END                =	800114,	/**< QS闭市结束 */
    QS_NOTICE_CLOSE_FAIL               =	800115,	/**< QS闭市失败 */
    QS_NOTICE_EV_INIT_START            =	800116, /**< QS晚上开市开始 */
    QS_NOTICE_EV_INIT_END              =    800117, /**< QS晚上开市结束 */
    QS_NOTICE_EV_INIT_FAIL             =    800118, /**< QS晚上开市失败 */   
    QS_ORDER_TREATY_ISSUE              =    800119, /**< 协议转让行情发布指令开始 9:15 */
    QS_ORDER_TREATY_ISSUE_OK           =    800120, /**< 协议转让行情发布指令开始 9:15 */
    QS_ORDER_TREATY_MATCH              =    800121, /**< 协议转让撮合指令开始 9:30 */
    QS_ORDER_TREATY_MATCH_OK           =    800122, /**< 协议转让撮合指令开始 9:30 */
    QS_NOTICE_PA_CLOSE                 =    800123, /**< 协议转让收市指令开始 15:00 */
    QS_NOTICE_PA_CLOSE_OK              =    800124, /**< 协议转让收市指令开始 15:00 */
    QS_INFO_SEND_CLOSE_INSTRUCT1_OK    =	800125, /**< 闭市指令（是否已发和发送时间）*/
    QS_INFO_SEND_CLOSE_INSTRUCT2_OK    =	800126, /**< 闭市指令2（是否已发和发送时间） */
        
    QS_ORDER_MARKET_ISSUE              =    800127, /**< 做市转让行情发布指令开始 9:15 */
    QS_ORDER_MARKET_ISSUE_OK           =    800128, /**< 做市转让行情发布指令开始 9:15 */
    QS_ORDER_MARKET_MATCH              =    800129, /**< 做市转让撮合指令开始 9:30 */
    QS_ORDER_MARKET_MATCH_OK           =    800130, /**< 做市转让撮合指令开始 9:30 */
    QS_NOTICE_MM_CLOSE                 =    800131, /**< 做市转让收市指令开始 15:00 */
    QS_NOTICE_MM_CLOSE_OK              =    800132, /**< 做市转让收市指令开始 15:00 */

    QS_ORDER_TOWNET_NOTISSUE           =    800133, /**< 两网虚拟成交不发布指令开始 9:30 */   
    QS_ORDER_TOWNET_NOTISSUE_OK        =    800134, /**< 两网虚拟成交不发布指令开始 9:30 */   
    QS_NOTICE_O3B_CLOSE                =    800135, /**< 两网及退市收市指令开始 15:00*/
    QS_NOTICE_O3B_CLOSE_OK             =    800136, /**< 两网及退市收市指令开始 15:00*/    
    
    QS_NOTICE_LOAD_STOCKINFO_OK          =    802501, /**< qs_stock_info.dbf（是否已加载到位和加载时间）  */
    QS_NOTICE_LOAD_STOCK_PRECLOSE_OK     =    802502, /**< qs_stock_close.dbf（是否已加载到位和加载时间） */
    QS_NOTICE_LOAD_STOCK_PUBLIC_PARAM_OK =    802503, /**< qs_stock_param.dbf（是否已加载到位和加载时间） */   
    QS_NOTICE_LOAD_CLOSE_PARAM_OK        =    802504, /**< qs_close_param.dbf（是否已加载到位和加载时间） */
    QS_NOTICE_LOAD_MAKER_INFO_OK         =    802505, /**< qs_maker_info.dbf（是否已加载到位和加载时间）  */
    QS_NOTICE_LOAD_MAKER_NAME_OK         =    802506, /**< qs_maker_name.dbf（是否已加载到位和加载时间）  */
    QS_NOTICE_LOAD_TRADER_UNIT_OK        =    802507, /**< qs_trade_unit.dbf（是否已加载到位和加载时间）  */
    QS_NOTICE_LOAD_BRANCH_OK             =    802508, /**< qs_branch.dbf（是否已加载到位和加载时间）  */      
    
    QS_INFO_SEND_CLOSE_INSTRUCT3_OK      =	802337, /**< 闭市指令3 （是否已发和发送时间）*/
    QS_NOTICE_SUSPENSION                 =	802338, /**< 接收停牌指令和最新的接收时间 */
    QS_NOTICE_RESUMPTION                 =	802339, /**< 接收复牌指令和最新的接收时间 */
    QS_NOTICE_TEMP_CLOSE                 =  802345, /**< 临时休市 */
    QS_NOTICE_CLOSE_SUSPENSION           =  802346, /**< QS停牌指令 */
    QS_NOTICE_CLOSE_RESUMPTION           =  802347, /**< QS复牌指令 */

    /** 以下是错误号 990000 */
    QS_ERROR_LOAD_INITIAL_FILE_FAIL      =	990000,	/**< 加载初始化文件失败 */
    QS_ERROR_NO_MEMORY                   =	990001,	/**< 内存不足 */
    QS_ERROR_STOCK_CODE_INVALID          =	990002,	/**< 初始化文件存在非法股票代码 */
    QS_ERROR_STOCK_COUNT                 =	990003,	/**< 证券收盘表与证券信息不匹配 */
    QS_ERROR_CLOSE_PARAM                 =	990004,	/**< 收盘参数索引(必须>=1)无效 */
    QS_ERROR_NO_PUBLIC_PARAM             =	990005,	/**< 未设置行情揭示参数 */
    QS_ERROR_INIT_RMSEND                 =	990006,	/**< 初始化组播发送模块失败 */
    QS_ERROR_RMSEND_CREATE               =	990007,	/**< 组播发送模块创建失败 */
    QS_ERROR_RMSEND_START                =	990008,	/**< 组播发送模块启动失败 */
    QS_ERROR_ORDTYPE_INVALID             =	990009,	/**< 收到业务数据非法 */
    QS_WARNING_NO_BUILDER                =	990010,	/**< 此交易阶段没有处理方法 */
    QS_ERROR_STRUCT_NOMATCH              =	990011,	/**< 股票信息结构长度不匹配 */
    QS_ERROR_NOSUPPORT_BUSINESS          =	990012,	/**< 不支持此种业务 */
    QS_ERROR_CREATE_DATAMANAGER          =	990013,	/**< 创建数据管理器失败 */
    QS_ERROR_LOAD_DATA                   =	990014,	/**< 数据管理器加载数据失败 */
    QS_ERROR_CANNOT_TREAT                =	990015,	/**< 不处理其它指令 */
    QS_ERROR_CREATE_INVESTOR_BUY_BOOK    =	990016,	/**< 创建投资者买订单簿失败 */
    QS_ERROR_CREATE_INVESTOR_SALE_BOOK   =	990017,	/**< 创建投资者卖订单簿失败 */
    QS_ERROR_CREATE_LIMIT_BUY_BOOK       =	990018,	/**< 创建限价/做市商买订单簿失败 */
    QS_ERROR_CREATE_LIMIT_SALE_BOOK      =	990019,	/**< 创建限价/做市商卖订单簿失败 */
    QS_ERROR_CREATE_SEND_COMPONENT       =	990020,	/**< 初始化组播发送模块失败 */
    QS_ERROR_CREATE_SHAREMEM             =	990021,	/**< 创建共享内存失败请关闭共享内存，重新启动 */
    QS_ERROR_CREATE_ORDERBOOK_ARRAY      =	990022,	/**< 创建股票订单簿队列失败 */
    QS_ERROR_CREATE_ORDERBOOK            =	990023,	/**< 创建股票订单簿失败 */
    QS_ERROR_CREATE_MEMSNAP              =	990024,	/**< 初始化内存快照失败 */
    QS_ERROR_CREATE_AGREEMENT_DIRECTOR   =	990025,	/**< 创建协议业务指挥失败 */
    QS_ERROR_CREATE_MARKET_DIRECTOR      =	990026,	/**< 创建做市业务指挥失败 */
    QS_ERROR_CREATE_TWONET_DIRECTOR      =	990027,	/**< 创建两网及退市业务指挥失败 */
    QS_ERROR_CREATE_INSTRUCTOR           =	990028,	/**< 创建指令处理器失败 */
    QS_ERROR_CANNOT_CLONE                =	990029,	/**< 本身未初化不能被克隆 */
    QS_ERROR_CREATE_STOCKINFO_BUFFER     =	990030,	/**< 创建证券信息缓存失败 */
    QS_ERROR_CREATE_STOCKOTHER_BUFFER    =	990031,	/**< 创建证券附加信息缓存失败 */
    QS_ERROR_CREATE_STOCKQUOT_BUFFER     =	990032,	/**< 创建证券行情信息缓存失败 */
    QS_ERROR_CREATE_STOCKORDER_BUFFER    =	990033,	/**< 创建委托申报缓存失败 */
    QS_ERROR_CREATE_MAKERINFO_BUFFER     =	990034,	/**< 创建做市商信息缓存失败 */
    QS_ERROR_GET_FILEDBYNAME             =	990035,	/**< 获取表字段失败 */
    QS_ERROR_ORDER_INDEX_INVALID         =	990036,	/**< 委托申报索引错误 */
    QS_ERROR_CREATE_BUILDER              =	990037,	/**< 创建业务建造者失败 */
    QS_ERROR_NO_CONFIG_LOG               =	990038,	/**< 配置文件或日志必须存在 */
    QS_ERROR_NO_POSITION_TYPE            =	990039,	/**< 揭示行情参数错误不存在此买卖盘性质 */
    QS_ERROR_NO_CONFIG_SECTION_ITEM      =	990040,	/**< 配置段或结点不存在 */
    QS_ERROR_NO_REGISTER_ORDERBOOK       =	990041,	/**< 此股票订单簿未注册或注册不完整 */
    QS_ERROR_CLOSE_STATE                 =	990042,	/**< 收盘状态错误 */
    QS_ERROR_RMSEND_INSTRUCT             =	990043,	/**< 发送行情指令失败 */
    QS_ERROR_RMSEND_OUT_STOP_ORDER       =	990045,	/**< 发送停复牌行情信息失败 */
    QS_ERROR_RMSEND_STOCK_QUOT           =	990046,	/**< 发送股票行情失败 */
    QS_ERROR_RMSEND_STOCK_ORDER          =	990047,	/**< 发送股票委托数据失败 */
    QS_ERROR_NOALLOW_MAKE_CLOSE_QUOT     =	990048,	/**< 未闭市前不允许产生收盘行情 */
    QS_ERROR_DIR_NOEXSIST                =	990049,	/**< 配置目录不存在 */
    QS_ERROR_CREATE_QUOTMAKER            =  990050, /**< 创建行情生成实例失败 */
    QS_ERROR_PUBLIC_QUOT_PARAM           =  990051, /**< 配置揭示行情频率参数非法 */
    QS_ERROR_PUBLIC_INFO_PARAM           =  990052, /**< 配置揭示行情信息频率参数非法 */
    QS_ERROR_NOEXSIST_STOCK              =  990053, /**< 股票代码不存在 */
    QS_ERROR_PUBLIC_INITIAZATION_PARAM   =  990054, /**< 配置初始化发布时间点非法 */
    QS_ERROR_CONFIG_ITEM_VALID           =  990055, /**< 配置项非法 */
    QS_ERROR_AGREEMENT_ORDER_ENQUEUE     =  990056, /**< 协议委托入队错误 */
    QS_ERROR_AGREEMENT_ORDER_COPY        =  990057, /**< 协议委托申报信息拷贝错误 */

    /** 以下是程序运行消息 990500 */
    QS_INFO_PROGRAM_QUIT                = 802391,/**< 程序关闭成功 */
    QS_INFO_LOAD_INIT_FILE_OK           = 802392,/**< 加载初始化文件列表完成 */
    QS_INFO_DM_INIT_OK                  = 802393,/**< 数据加载模块初始化成功 */
    QS_INFO_RM_INIT_OK                  = 802394,/**< 组播组件创建及初始化成功 */
    QS_INFO_SHAREMEM_INIT_OK            = 802395,/**< 创建创建及初始化成功 */
    QS_INFO_ORDERBOOK_CREATE_OK         = 802396,/**< 创建股票订单簿存储容器成功 */
    QS_INFO_QM_MEM_CREATE_OK            = 802397,/**< 创建行情数据内存成功 */
    QS_INFO_QM_BIZ_OBJECT_CREATE_OK     = 802398,/**< 创建行情数据生成业务处理对象成功 */
    QS_INFO_QM_BIZ_STATE_CHANGED        = 802399,/**< 行情业务品种揭示状态变化 */    
};


///交易主机事件：995000-999998
enum TsEventId
{
	TS_ERROR_CONFIGNOTEXIST       = 995000,      /**<配置文件不存在或不符合要求                                           */
	TS_ERROR_LOADSTOCKCODE_COMMONSTOCKTYPE_NOTFOUND = 995016,   /**<加载初始化数据（证券代码）时发现对应普通额度证券类别不存在           */
	TS_ERROR_LOADSTOCKCODE_BIGSTOCKTYPE_NOTFOUND    = 995017,   /**<加载初始化数据（证券代码）时发现对应大额额度证券类别不存在           */
	TS_ERROR_LACKOFMEMORY         = 995500,      /**<系统资源不足                                                         */
	TS_ERROR_MULTICASTRECV        = 995501,      /**<组播接收错误                                                         */
	TS_ERROR_LOADMULTICASTSENDER  = 995502,      /**<加载启动组播发送失败                                                 */
	TS_ERROR_LOADMULTICASTRECVER  = 995503,      /**<加载启动组播接收失败                                                 */
    TS_ERROR_LOADMATCHMODULE      = 995504,      /**<加载交易撮合模块失败                                                 */
    TS_ERROR_LOADMAXAGREEMENTDEALNUM = 995505,   /**<加载协议转让互报成交确认最大约定号失败                               */
    TS_ERROR_PRICESTEPZERO        = 995506,      /**<加载证券类别最小价差为0                                              */
    TS_ERROR_LOADMAXLIMITDEALNUM  = 995507,      /**<加载限价允许委托分配的最大约定号失败                                 */
    TS_ERROR_LOADBUYUNITZERO      = 995508,      /**<加载证券类别买入单位为0                                              */
    TS_ERROR_LOADSELLUNITZERO     = 995509,      /**<加载证券类别卖出单位为0                                              */
    TS_ERROR_MAXAGREEDEALNO_LESSTHANLIMITDEALNO = 995510,   /**<加载加载限价允许委托分配的最大约定号失败，小于互报成交确认最大约定号 */
    TS_ERROR_WRITE_LOCAL_FILE     = 995511,      /**<写本地组播接收文件失败 */
    TS_ERROR_READ_DFB             = 995512,      /**<读dbf文件错误 */
    TS_ERROR_INSERT_ORDER         = 995513,      /**<插入指令或委托错误 */
    TS_ERROR_READ_LOCAL_FILE      = 995514,      /**<读本地组播接收文件失败 */
    TS_ERROR_RECV_TOO_LARGE_DATA  = 995515,      /**<组播接收到数据大于指定最长数据 */

	TS_WARNING_STOCKTYPEPARANOTFOUND            = 996501,   /**<在增加证券T+n标识或证券类别限制时发现对应的证券类别参数设置不存在    */
	TS_WARNING_STOCKCODENOTFOUND                = 996502,   /**<在增加证券允许业务类别中发现对应证券代码不存在                       */
	TS_WARNING_ACCOUNTNONOTFOUND                = 996503,   /**<在增加证券帐户限制、做市商限制、证券持仓过程中发现对应证券帐号不存在 */
	TS_WARNING_UNITNONOTFOUND                   = 996504,   /**<在增加加以单元信息中发现对应证券交易单元不存在                       */

	TS_WARNING_STOCKTYPEKEYDUP                  = 996601,   /**<加载初始化数据（证券类别）对应记录主键重复                           */
	TS_WARNING_STOCKCODEKEYDUP                  = 996602,   /**<加载初始化数据（证券代码）对应记录主键重复                           */
	TS_WARNING_ACCOUNTNOKEYDUP                  = 996603,   /**<加载初始化数据（证券帐户）对应记录主键重复                           */
	TS_WARNING_UNITNOKEYDUP                     = 996604,   /**<加载初始化数据（交易单元）对应记录主键重复                           */
	TS_WARNING_ALLOWBUSITYPEKEYDUP              = 996605,   /**<加载初始化数据（证券允许业务类别）对应记录主键重复                   */
	TS_WARNING_TNFLAGKEYDUP                     = 996606,   /**<加载初始化数据（证券交易T+n标识）对应记录主键重复                    */
	TS_WARNING_STOCKKEYDUP                      = 996607,   /**<加载初始化数据（证券持仓信息）对应记录主键重复                       */
	TS_WARNING_UNITNORESTRICTKEYDUP             = 996608,   /**<加载初始化数据（交易单元限制表）对应记录主键重复                     */
	TS_WARNING_ACCPROPRESTRICTKEYDUP            = 996609,   /**<加载初始化数据（账户性质限制）对应记录主键重复                       */
	TS_WARNING_ACCOUNTRESTRICTKEYDUP            = 996610,   /**<加载初始化数据（证券账户限制）对应记录主键重复                       */
	TS_WARNING_MAKERRESTRICTKEYDUP              = 996611,   /**<加载初始化数据（做市限制）对应记录主键重复                           */
	TS_WARNING_FORBIDTIMERESTRICTKEYDUP         = 996612,   /**<加载初始化数据（申报禁止业务时间）对应记录主键重复                   */
	TS_WARNING_MATCHTIMEKEYDUP                  = 996613,   /**<加载初始化数据（撮合交易阶段时间设置）对应记录主键重复               */

	TS_WARNING_EMER_STOCKHOLDERNOTEXIST               = 996801,   /**<处理证券账户紧急维护指令时发现对应证券账户不存在                     */
	TS_WARNING_EMER_ACCRESTRICT_STOCKHOLDERNOTEXIST   = 996802,   /**<处理证券账户交易限制紧急维护指令时发现对应证券账户不存在             */
	TS_WARNING_EMER_ACCRESTRICT_RESTRICTIONNOTEXIST   = 996803,   /**<处理证券账户交易限制紧急维护指令时发现要求删除的交易限制不存在       */
	TS_WARNING_EMER_ACCRESTRICT_ORDERERROR            = 996804,   /**<处理证券账户交易限制紧急维护指令时发现对应指令信息不正确             */
	TS_WARNING_EMER_PARA_STOCKCODENOTEXIST            = 996805,   /**<处理证券交易参数紧急维护指令时发现对应证券代码不存在                 */
	TS_WARNING_EMER_BUSITYPE_STOCKCODENOTEXIST        = 996806,   /**<处理证券业务类别紧急维护发现对应证券代码不存在                       */
	TS_WARNING_EMER_UNITNORESTRICT_UNITNONOTEXIST     = 996807,   /**<处理交易单元交易限制紧急维护指令时发现对应交易单元不存在             */
	TS_WARNING_EMER_UNITNORESTRICT_RESTRICTIONNOTEXIST= 996808,   /**<处理交易单元交易限制紧急维护指令时发现要求删除的交易限制不存在       */
    TS_WARNING_EMER_UNITNORESTRICT_ORDERERROR         = 996809,   /**<处理交易单元交易限制紧急维护指令时发现对应指令信息不正确             */
    TS_WARNING_EMER_BUSITYPE_BUSITYPENOTEXIST         = 996810,   /**<处理证券业务类别紧急维护发现对应证券代码允许业务类别不存在           */
    TS_WARNING_EMER_NOTINTEMPCLOSING               = 996811,   /**<处理手工收市时发现系统并未处于临时休市状态                     */

	TS_INFO_START                                   = 998001,   /**<撮合主机启动开始                                                     */
	TS_INFO_START_MULTICASTRECVERLOGOBJECT          = 998002,   /**<开始创建记录组播接收日志对象                                         */
	TS_INFO_FINISH_MULTICASTRECVERLOGOBJECT         = 998003,   /**<创建记录组播接收日志对象完成                                         */
	TS_INFO_START_MONMEMORYOBJECT                   = 998004,   /**<开始监控内存访问对象                                                 */
	TS_INFO_FINISH_MONMEMORYOBJECT                  = 998005,   /**<创建监控内存访问对象完成                                             */
	TS_INFO_START_PREINITDATA                       = 998006,   /**<开始加载预初始化数据                                                 */
	TS_INFO_FINISH_PREINITDATA                      = 998007,   /**<加载预初始化数据完成                                                 */
	TS_INFO_START_QUOTATION                             = 998008,   /**<开始启动行情模块                                                     */
	TS_INFO_FINISH_QUOTA                            = 998009,   /**<启动行情模块完成                                                     */
	TS_INFO_START_INITDATA                          = 998010,   /**<开始加载初始化数据                                                   */
	TS_INFO_FINISH_INITDATA                         = 998011,   /**<加载初始化数据完成                                                   */
	TS_INFO_START_MATCH                             = 998012,   /**<开始启动交易撮合模块                                                 */
	TS_INFO_FINISH_MATCH                            = 998013,   /**<启动交易撮合模块完成                                                 */
	TS_INFO_START_LOCALDATA                         = 998014,   /**<开始加载本地已接收数据                                               */
	TS_INFO_END_LOCALDATA                           = 998015,   /**<加载本地已接收数据完成                                               */
	TS_INFO_START_MULTICASTRECVER                   = 998016,   /**<开始启动组播接收模块                                                 */
	TS_INFO_FINISH_MULTICASTRECVER                  = 998017,   /**<启动组播接收模块完成                                                 */
	TS_INFO_FINISH                                  = 998018,   /**<撮合主机启动完毕                                                     */

	TS_INFO_CREATE_MATCHTIMEORDER                   = 998020,   /**<撮合主机生成交易阶段时间切换指令                                     */

	TS_INFO_BEGIN_STOP                              = 998051,   /**<撮合主机开始停止过程                                                 */
	TS_INFO_BEGIN_STOPMULTICASTRECV                 = 998052,   /**<撮合主机开始停止组播接收                                             */
	TS_INFO_FINISH_STOPMULTICASTRECV                = 998053,   /**<撮合主机停止组播接收完成                                             */
	TS_INFO_BEGIN_STOPQUOTA                         = 998054,   /**<撮合主机开始停止行情模块                                             */
	TS_INFO_FINISH_STOPQUOTA                        = 998055,   /**<撮合主机停止行情模块完成                                             */
	TS_INFO_BEGIN_STOPMATCH                         = 998056,   /**<撮合主机开始停止交易撮合模块                                         */
	TS_INFO_FINISH_STOPMATCH                        = 998057,   /**<撮合主机停止交易撮合模块完成                                         */
	TS_INFO_BEGIN_STOPMULTICASTSENDER               = 998058,   /**<撮合主机开始停止组播发送                                             */
	TS_INFO_FINISH_STOPMULTICASTSENDER              = 998059,   /**<撮合主机停止组播发送完成                                             */
	TS_INFO_BEGIN_STOP_MULTICASTRECVERLOGOBJECT     = 998060,   /**<撮合主机开始关闭组播接收数据日志模块                                 */
	TS_INFO_FINISH_STOP_MULTICASTRECVERLOGOBJECT    = 998061,   /**<撮合主机关闭组播接收数据日志模块完成                                 */
	TS_INFO_BEGIN_STOP_MONMEMERY                    = 998062,   /**<撮合主机开始关闭并释放监控共享内存                                   */
	TS_INFO_FINISH_STOP_MONMEMERY                   = 998063,   /**<撮合主机关闭并释放监控共享内存完成                                   */
	TS_INFO_FINISH_STOP                             = 998064,   /**<撮合主机停止过程结束                                                 */
    TS_INFO_STOP_FAILED                             = 998065,   /**<撮合主机停止失败                                                     */
    TS_INFO_FINISH_STOPFAILED                       = 998066,   /**<撮合主机结束失败                                                     */
    TS_INFO_ALLCLOSEORDER_NOTRECV                   = 998067,   /**<撮合主机已发完所有指令，但没有收到全市场闭市指令                     */

    TS_DEBUG_CHECKFAILED                            = 998100,   /**<撮合主机校验失败                                                    */
    TS_NOTICE_READINGDBF                             = 998155,   /**<撮合主机读取DBF中                                                   */
	TS_DEBUG_GETMEMORYINFO                          = 998900,   /**<撮合主机获取内存结构信息                                             */
    /*****************************add by shoujj 2013-09-28 交易撮合模块事件定义区*******************************/

	/*******************************************错误级别定义区*******************************************/
	TS_ERROR_ENTRUSTNULL							  = 999401,  /**< 取到一条校验通过的空委托单 */
	TS_ERROR_MATCHDOTPATHNULL						  = 999402,  /**< 撮合点存放路径为空*/
	TS_ERROR_CONVENTION_LESS						  = 999403,  /**<约定号范围不正确*/
	TS_ERROR_COMMON_PUTNEW							  = 999404,  /**<限价买卖单挂入失败*/
	TS_ERROR_COMMON_REMOVE							  = 999405,  /**<买卖单移除失败*/
	TS_ERROR_NOTRMSENDER							  = 999406,  /**<数据组播失败*/
	TS_ERROR_NOTMAKEQUOTATION                         = 999407,  /**数据传送给行情模块失败*/
	TS_ERROR_NOTEVENTNOTIFY							  = 999408,  /**撮合线程事件通知失败，不能处理委托单*/
	TS_ERROR_NOTUNLOAD								  = 999409,  /**指定撮合点卸载失败*/
	TS_ERROR_NOTLOAD                                  = 999410,  /**指定撮合点加载初始化失败*/
	TS_ERROR_LOADSO_FAIL							  = 999411,  /**指定撮合点名加载失败*/
	TS_ERROR_MATCHDOT_NUM_LARGE						  = 999412,  /**获取的撮合点号超过了最大号，不能正常使用*/
	TS_ERROR_MATCHDOTFUN_NOTEXITST					  = 999413,  /**撮合点名指定的接口函数不存在，不能正常使用*/
	TS_ERROR_MATCHDOT_NOTEXITST						  = 999414,  /**指定目录下没有找到合法的撮合点，撮合模块不能正常工作*/
	TS_ERROR_MATCHORDER_NOTEXITST					  = 999415,  /**无效的撮合指令，不能正常进行切换*/
	TS_ERROR_MATCHORDER_NOTINSERT                     = 999416,  /**此指令撮合对象不能正常插入Map标准库对象*/
	TS_ERROR_MATCHOBJET_NOTCREATE					  = 999417,  /**指令撮合对象名创建不成功，这将导致不能进行该指令撮合*/
	TS_ERROR_SENDDATAWRITE_FAIL						  = 999418,  /**数据落地失败，可能磁盘空间已满*/
	TS_ERROR_SUSPENDORDERE_FAIL						  = 999419,  /**代码不存在，停复盘指令执行失败*/
	TS_ERROR_INITRETURNFILE_FAIL					  = 999420,  /**初始化回报成交数据落地文件失败*/
	TS_ERROR_CODETRAY_CLEAR_FAIL					  = 999421,  /**买卖盘清空失败*/
	TS_ERROR_MATCHDEAL_FAIL							  = 999422,  /**撮合处理失败*/
	TS_ERROR_NOTEXPECT_ORDER						  = 999423,  /**没有获取到期望的指令*/

	/*******************************************警告级别定义区*******************************************/
	TS_WARNING_STOCK_NOTENOUGH						  = 999501,  /**余额不足，即将主动撤单返回*/
	TS_WARNING_STOCK_NOTMULTIPLE					  = 999502,  /**买卖数量不是整数倍，即将主动撤单返回*/
	TS_WARNING_STOCK_LESSMINAMOUNT					  = 999503,  /**小于最小下单数量, 即将主动撤单返回*/
	TS_WARNING_NOENTRUST							  = 999504,  /**可能原始单不存在或者已全部成交*/
	TS_WARNING_INVALID_SORT							  = 999505,  /**此交易阶段为非法，现进行撤单返回*/
	TS_WARNING_NOT_WITHDRAWALS						  = 999506,  /**不能进行撤单处理，即将主动撤单废单返回*/
	TS_WARNING_REPEATENTRUST						  = 999507,  /**之前已经报过此合同号委托单, 现不处理*/
	TS_WARNING_ENTRUSTNOTDEAL						  = 999508,  /**此代码已经闭市，对任何委托都概不处理*/
	TS_WARNING_MARKET_ONLYBOTH						  = 999509,  /**做市商双向报价单发现此账户之前已报过单，现即将之前的未成交单先撤除掉*/
	TS_WARNING_MARKET_BOTHEXIST						  = 999510,  /**收到一笔新的单向报价单, 发现已存在一笔双向报价单, 将此单向报价单主动撤单返回*/
	TS_WARNING_MARKET_SINGLEEXIST					  = 999511,  /**收到一笔新的单向报价单, 发现已存在一笔反向单向报价单, 将此单向报价单主动撤单返回*/
	TS_WARNING_MARKET_ONLYSINGLE					  = 999512,  /**收到一笔新的单向报价单, 发现已存在一笔单向报价单, 将之前的未成交单先撤除掉*/
	TS_WARNING_TREATY_RICEERROR						  = 999513,  /**不在有效价格区间, 即将主动撤单返回*/
	TS_WARNING_TREATY_LIMITCONFIRM_WITHDRAWALS		  = 999514,  /**限价确认单没有全部成交完毕，即将主动撤单返回*/
	TS_WARNING_TREATY_CONFIRM_WITHDRAWALS			  = 999515,  /**确认单找到对手方, 但条件未匹配, 即将对两笔主动撤单返回*/
	TS_WARNING_TREATY_FIXEDCONFIRM_WITHDRAWALS		  = 999516,  /**定价确认单找到对手方, 但条件未匹配, 即将定价确认单撤单返回*/
	TS_WARNING_UNABLEENTRUSTINCLOSE					  = 999517,  /**在闭市之间不能下委托单*/
	TS_WARNING_GREATERTHAN_HIGHPRICE				  = 999518,  /**委托价格大于当日最高价*/
	TS_WARNING_LESSTHAN_LOWPRICE					  = 999519,  /**委托价格小于当日最低价*/
	TS_WARNING_GREATERTHAN_PREPRICE                   = 999520,  /**委托价格大于昨收价比*/
	TS_WARNING_LESSTHAN_PREPRICE					  = 999521,  /**委托价格小于昨收价比*/
	TS_WARNING_NOPREPRICE					          = 999522,  /**没有前收盘价*/
	TS_WARNING_NOLASTMATCHORDER						  = 999523,	 /**对代码进行复盘时，没有找到上一个撮合指令阶段*/


	/*******************************************通知级别定义区*******************************************/
	TS_NOTICE_ENGINESTART							  = 999601,  /**撮合模块引擎已启动*/
	TS_NOTICE_ENGINESTOP							  = 999602,  /**撮合模块引擎已停止*/
	TS_NOTICE_ENGINESTARTFAIL						  = 999603,  /**撮合模块引擎启动失败*/
	TS_NOTICE_MATCHDOTLOAD							  = 999604,  /**加载撮合点成功, 可进行相关指定撮合*/
	TS_NOTICE_MATCHSWITCH							  = 999605,  /**撮合指令切换*/

	/*******************************************信息级别定义区*******************************************/
	TS_INFO_MATCHTHREAD_START						  = 999701,  /**撮合线程已正常启动*/
	TS_INFO_MATCHTHREAD_OVER						  = 999702,  /**撮合线程已正常退出*/

	/*******************************************调试级别定义区*******************************************/
	TS_DEBUG_WITHDRAWAL								  = 999801,  /**普通单成功生成撤单回报*/
	TS_DEBUG_MARKET_WITHDRAWAL						  = 999802,  /**做市单成功生成撤单回报*/
	TS_DEBUG_COMMON_PUTNEW							  = 999803,  /**成功挂入限价买卖单*/
	TS_DEBUG_TREATY_PUTNEW							  = 999804,  /**成功挂入限价买卖单，并自动生成约定号*/
	TS_DEBUG_TREATY_CONFIRMPUTNEW					  = 999805,  /**成功挂入确认买卖单*/
	TS_DEBUG_MARKET_PUTNEW							  = 999806,  /**成功挂入做市报价单*/
	TS_DEBUG_CAllAUCTION_ISSUE						  = 999807,  /**集合竞价阶段发布了最新匹配价*/
	TS_DEBUG_DEALQUEUE								  = 999808,  /**目前先暂时不撮合, 放入待处理队列*/
	TS_DEBUG_RETURNINFO								  = 999809,  /**普通交易撮合成交成功*/
	TS_DEBUG_MARKET_RETURNINFOOFMAKER				  = 999810,  /**做市商与投资人撮合成交成功*/
	TS_DEBUG_MARKET_RETURNINFOOFINVESTOR			  = 999811,  /**投资人与做市商撮合成交成功*/
	TS_DEBUG_TREATY_RETURNINFO						  = 999812,  /**协议交易撮合成交成功*/
	TS_DEBUG_REMOVE									  = 999813,  /**投资人成交完毕从盘中移除*/
	TS_DEBUG_MARKET_REMOVE							  = 999814,  /**做市商成交完毕从盘中移除*/
	TS_DEBUG_TIMEORDERDEAL							  = 999815,  /**收到指令号对代码进行处理*/
	TS_DEBUG_EVENTNOTIFY							  = 999816,	 /**交易撮合模块收到一个通知，现进行工作*/
	TS_DEBUG_CAllAUCTION_COMPUTE					  = 999817,  /**此委托触发集合竞价计算*/
	TS_DEBUG_STOCK_FROZEN							  = 999818,  /**股份冻结数量*/
	TS_DEBUG_STOCK_CURRENT_ADD						  = 999819,  /**股份增加数量*/
	TS_DEBUG_STOCK_CURRENT_DECR						  = 999820,	 /**股份真正减少数量*/
	TS_DEBUG_STOCK_FROZEN_DECR						  = 999821,	 /**股份冻结回减数量*/
	TS_DEBUG_BUSINESSCOUNT							  = 999822,  /**触发成交笔数，推送给组播模块*/
	TS_DEBUG_CODEDUMPSTART							  = 999823,  /**买卖盘dump开始*/
	TS_DEBUG_PRICENODEDUMP							  = 999824,  /**价格档位相关信息*/
	TS_DEBUG_ENTRUSTDUMP							  = 999825,	 /**委托节点相关信息*/
	TS_DEBUG_CODEDUMPSTOP							  = 999826,   /**买卖盘dump结束*/
	TS_DEBUG_DEALCOUNTOFPERSECOND					  = 999827,	 /**记录撮合模块每秒处理的笔数*/
	TS_DEBUG_TREATY_LIMITCONFIRM_WITHDRAWALS		  = 999828,  /**限价确认单没有全部成交完毕，即将主动撤单返回*/
	TS_DEBUG_MARKET_ONLYBOTH                          = 999829   /**做市商双向报价单发现此账户之前已报过单，现即将之前的未成交单先撤除掉*/
	/************************************************************************************************************/
};

/*
enum ArbEventId
{
	  I_RUN_LOG                   = 955000,   // 运行日志
	  E_PARAMETER_CONFIG_ERROR   ,   // 从配置文件中参数有误
	  E_CREATE_SERVER_FAILED     ,   // TCP SERVER建立失败
	  E_CREATE_SHM_FAILED        ,   // 建立共享内存失败
          E_OPEN_SHM_FAILED          ,
          E_FSTAT_SHM_FAILED         ,
          E_MMAP_FAILED              ,
	  E_OPEN_FILE_FAILED         ,   // 打开文件失败
	  E_ACD_ID_ERROR             ,   // 排队机标示ID错
	  E_ACD_STATUS_ERROR         ,   // 排队机状态错
	  E_ARB_MESSAGE_ERROR        ,   // 非法仲裁包文类型
	  E_TCP_CONNECT_ERROR        ,   // TCP连接出错
          E_UNKNOW_SOCKET_INDEX      ,
          E_ACD_NO_RESPONE           ,   // ACD在TIME OUT时间没任何消息
	  E_ACTION_TYPE_ERROR        ,   // 仲裁要求排队机执行的动作类型非法
          E_ACD_EVENT_ERROR          ,   // 排队机发送的事件非法
          E_NEW_OBJECT_FAILED        ,   // 分配对象失败
          E_SEND_DATA_FAILED         ,   //  TCP发送数据失败
          E_TCP_DISCONNECTED         ,   // TCP连接断开
          E_LOST_ACD_CONNECTION      ,   // 排队机在规定的时间里没有重连仲裁机
          E_PROCESS_STOP             ,   // 业务处理进程CRASH
          E_CONNECT_SERVER_FAILED    ,   // 连接TCP SERVER失败
          E_VALUE_ILLEGAL            ,   // 变量值不在取值范围内或不合法数据类型
          E_STRING_LENGTH_EXCEED     ,   // 字符串长度超标
          E_FORK_PROCESS_FAILED      ,   //  Fork子进程失败
          E_MALLOC_FAILED            ,   // malloc 分配内存失败
          E_GET_QUEUE_SIZE_FAILED    ,   // 获取POSIX消息队列大小失败
          E_READ_QUEUE_FAILED        ,   // 从POSIX消息队列读取消息失败
          E_WRITE_QUEUE_FAILED       ,
          E_OPEN_QUEUE_FAILED        ,   // 打开POSIX消息队列失败
          E_SYNC_MESSAGE_ERROR       ,   // 非法同步包文类型
          E_SYNC_FAILED              ,   //  同步失败
          E_OPEN_SEM_FAILED          ,
          E_CLOSE_SEM_FAILED         ,
          E_REMOVE_SEM_FAILED        ,
          E_WAIT_SEM_FAILED          ,
          E_POST_SEM_FAILED          ,
          E_TRY_WAIT_SEM_FAILED      ,
          E_WRITE_FILE_FAILED        ,
          E_GET_DATE_FAILED          ,
          E_HANDLER_ERROR            ,
          I_STATUS_CHANGE            ,
          E_OPTION_ERROR             ,
          E_GET_SEM_VALUE_FAILED     ,
          E_MACHINE_TYPE             ,
          E_STAT_TYPE                ,
          E_GET_SYSTEM_TIME          ,


}; */
#endif
