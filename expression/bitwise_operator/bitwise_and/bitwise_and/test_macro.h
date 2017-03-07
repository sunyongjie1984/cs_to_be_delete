/////////////////////////////////////////////////////////////////////////////
#define WM_USER_NOTIFY           (WM_APP+1)
#define WM_USER_PUSH             (WM_APP+2)
#define WM_USER_COMMAND          (WM_APP+3)
#define WM_USER_GETMODALDATA     (WM_APP+4)
#define WM_USER_BROADCAST        (WM_APP+5)
#define WM_USER_MODULE           (WM_APP+16)    //模块间应用
/////////////////////////////////////////////////////////////////////////////
//WM_USER_MODULE
#define MODULE_WP_GETGLOBALS     1              //取公用变量
#define MODULE_WP_SETLOGINNOTIFY 2              //多帐号登录提示
#define MODULE_WP_ENABLEACCEL    3              //快捷键状态
#define MODULE_WP_SETACCEL       4              //设置快捷键
#define MODULE_WP_ALLOCATESESS   5              //AllocateSess
#define MODULE_WP_RELEASESESS    6              //ReleaseSess
/////////////////////////////////////////////////////////////////////////////
//MODULE_WP_GETGLOBALS
#define G_PCOMM                  0              //g_pComm
#define G_NWTFS                  1              //g_nWtfs
#define G_LREVISETIME_HI         2              //g_lReviseTime high
#define G_LREVISETIME_LO         3              //g_lReviseTime low
#define G_NSYSFUNSOPTION         4              //g_nSysFunsOption
#define G_STRSVRNAME             5              //g_strSvrName
#define G_NACTIVERECNO           6              //g_nActiveRecno
#define G_NMASTERRECNO           7              //g_nMasterRecno
#define G_STRNODE                8              //g_strNode
#define G_STRNODEEX              9              //g_strNodeEx

#define G_RECJYS                 10             //g_recJys
#define G_RECZQLB                11             //g_recZqlb
#define G_RECMONEY               12             //g_recMoney
#define G_RECXTDM                13             //g_recXtdm
#define G_RECHYHQ                14             //g_recHyhq
#define G_RECJGDM                15             //g_recJgdm
#define G_RECYHCS                16             //g_recYhcs
#define G_RECJYSTLDM             17             //g_recJysTldm
#define G_RECJYSTLHY             18             //g_recJysTlhy
#define G_RECSUBSCIBEHYDM        19             //g_recSubscibeHydm

#define G_RECKHH                 30             //g_recKhh
#define G_RECJYBM                31             //g_recJybm
#define G_RECZJZH                32             //g_recZjzh
#define G_RECHYCC                33             //g_recHycc
#define G_RECHYMX                34             //g_recHymx
#define G_RECYHZH                35             //g_recYhzh
#define G_RECNOTIFY              36             //g_recNotify
#define G_RECPUSHMSG             37             //g_recPushMsg
#define G_RECXZKH                38             //g_recXzkh
#define G_RECFZXX                39             //g_recFzxx
#define G_RECFZKH                40             //g_recFzkh
#define G_RECYYWT                41             //g_recYywt
#define G_NSYSTEMFLAGS           50             //g_nSystemFlags
/////////////////////////////////////////////////////////////////////////////
//帐号标志
#define ACCFLAG_CHKJYMM          0x00000001     //已验证
#define ACCFLAG_JYMMJY           0x00000002     //验证交易密码通过
#define ACCFLAG_XGJYMM           0x00000004     //外部修改交易密码
#define ACCFLAG_XGJYMM_FIRST     0x00000008     //首次登录要求先修改交易密码

#define ACCFLAG_CHKZJMM          0x00000010     //已验证
#define ACCFLAG_ZJMMJY           0x00000020     //资金密码验证标志
#define ACCFLAG_XGZJMM           0x00000040     //外部修改资金密码
#define ACCFLAG_XGZJMM_FIRST     0x00000080     //首次登录要求先修改资金密码

#define ACCFLAG_JSDQR            0x00000100     //需要确认结算单
#define ACCFLAG_PUSHMSG          0x00000400     //登录推送
#define ACCFLAG_XGKHZL           0x00000800     //修改客户资料

#define ACCFLAG_CHECKSTAMP       0x00001000     //验证机器特征码
#define ACCFLAG_BINDSTAMP        0x00002000     //可以绑定机器特征码
#define ACCFLAG_AUTHMSG          0x00004000     //有预留的验证信息

#define ACCFLAG_CXJYBM           0x00010000     //查询交易编码
#define ACCFLAG_CXZJZH           0x00020000     //查询资金帐号
#define ACCFLAG_CXJSZD           0x00040000     //查询结算单
#define ACCFLAG_CXYHZH           0x00080000     //查询银行帐号
#define ACCFLAG_CXXZKH           0x00100000     //取关联小组
#define ACCFLAG_CXFZKH           0x00200000     //取关联分组
#define ACCFLAG_NOTIFYMSG        0x00400000     //读取提示信息
#define ACCFLAG_UNREADMSG        0x00800000     //未阅读信息
#define ACCFLAG_HYCCDM           0x01000000     //持仓合约代码有变动
//客户类别
#define KHLB_MASTER              1              //独立客户
#define KHLB_XZKH                2              //关联小组客户,通过FID_XZBH关联
#define KHLB_GLKH                3              //相关子客户,通过FID_KHJL关联
//内部标记
#define MODIFY_HYDM              0x00000001     //合约代码修改
#define MODIFY_JYLB              0x00000002     //开平标志修改
#define MODIFY_MMLB              0x00000004     //买卖标志修改
#define MODIFY_WTJG              0x00000008     //委托价格修改
#define MODIFY_WTSL              0x00000010     //委托数量修改
#define MODIFY_JYBM              0x00000020     //交易帐号修改
#define MODIFY_HYDM2             0x00000040     //合约代码修改
#define MODIFY_JYLB2             0x00000080     //开平标志修改
#define MODIFY_MMLB2             0x00000100     //买卖标志修改
#define MODIFY_WTJG2             0x00000200     //委托价格修改
#define MODIFY_WTSL2             0x00000400     //委托数量修改
#define MODIFY_JYBM2             0x00000800     //交易帐号修改
#define USER_UPDATED_THREAD      0x10000000     //线程运行状态
#define USER_UPDATED_CANCEL      0x20000000     //中止标记
#define USER_UPDATED_RESET       0x40000000     //重置标记

#define USER_FLAG_EXIT           USER_UPDATED_CANCEL
#define USER_FLAG_CANCEL         USER_UPDATED_CANCEL
#define USER_FLAG_THREAD         USER_UPDATED_THREAD
#define USER_FLAG_SHOWWINDOW     0x80000000
//内部通知
#define USER_NOTIFY_UPDATED      0x00000001     //数据更新标志
#define USER_NOTIFY_DATAREADY    0x00000002     //更新数据Ready标志
#define USER_NOTIFY_GLXZKHDL     0x00000004     //关联小组客户登录
#define USER_NOTIFY_ACTIVEKHH    0x00000008     //客户号切换
#define USER_NOTIFY_ZJXX         0x00000010     //资金变动
#define USER_NOTIFY_FEXX         0x00000020     //份额
#define USER_NOTIFY_HYDMGX       0x00000040     //代码更新
#define USER_NOTIFY_TLDMGX       0x00000080     //更新交易所套利代码
#define USER_NOTIFY_PARAM        0x00000100     //参数修改
#define USER_NOTIFY_XGKHZL       0x00000200     //客户资料修改
#define USER_NOTIFY_GLXZGX       0x00000400     //关联帐号查询
//具体业务
#define USER_NOTIFY_WTCX         0x00001000     //委托记录
#define USER_NOTIFY_CJHB         0x00002000     //成交推送
#define USER_NOTIFY_QYZZ         0x00004000     //期银业务
#define USER_NOTIFY_YYWT         0x00008000     //预约委托
#define USER_NOTIFY_HQCF         0x00010000     //自动单委托
#define USER_NOTIFY_HYHQ         0x00020000     //行情变动
#define USER_NOTIFY_GLWT         0x00040000     //关联委托
#define USER_NOTIFY_PLWT         0x00080000     //批量委托
#define USER_NOTIFY_ZSZY         0x00100000     //止损止盈委托
#define USER_NOTIFY_CJCF         0x00200000     //成交触发单
#define USER_NOTIFY_TLWT         0x00400000     //套利触发单
#define USER_NOTIFY_SWAP         0x00800000     //互换交易触发单

#define USER_NOTIFY_WTJY         (USER_NOTIFY_WTCX|USER_NOTIFY_ZJXX|USER_NOTIFY_FEXX)
#define USER_NOTIFY_EXWTCX       (USER_NOTIFY_GLWT|USER_NOTIFY_PLWT|USER_NOTIFY_ZSZY|USER_NOTIFY_CJCF|USER_NOTIFY_TLWT|USER_NOTIFY_SWAP)
#define USER_NOTIFY_ZZDWT        USER_NOTIFY_HQCF

//推送信息 LOWORD(WPARAM)
#define USER_PUSH_MESSAGE        1              //消息推送
#define USER_PUSH_WTQR           2              //委托确认
#define USER_PUSH_CJHB           3              //成交回报
#define USER_PUSH_NOTIFY         4              //通告信息
#define USER_PUSH_HYHQ           5              //期货行情推送
//委托确认类别 !!对应声音提醒序号,不可单独修改
#define WTQR_WTQR                1              //申报成功
#define WTQR_SBSB                2              //申报失败
#define WTQR_CDQR                3              //撤单确认
#define WTQR_CDSB                4              //撤单失败
//操作或通知
#define COMMAND_NOTIFY           1              //更新通知
#define COMMAND_UPGRADE          2              //启动升级程序
#define COMMAND_QUOTESUBSCIBE    3              //代码订阅
#define COMMAND_SETACCELERATOR   4              //更新快捷键
#define COMMAND_BZJJGZX          5              //登录保证金监管中心网页
#define COMMAND_SETLAYERED       6              //设置窗口透明度
#define COMMAND_XGMM             7              //密码修改
#define COMMAND_CXHYDM           8              //查询合约代码
#define COMMAND_CXJYSTLDM        9              //查询交易所套利代码
#define COMMAND_CXKHZL           10             //查询客户资料 服务项目等
#define COMMAND_TZHDLTS          11             //同帐号登录提示
#define COMMAND_PUSH_DLTS        12             //同帐号登录提示
#define COMMAND_SYSLOCK          13             //系统锁定

#define COMMAND_NOTIFY_USER      30             //之后为通知类,尽量不转发

#define COMMAND_NOTIFY_ZJMMDL    30             //资金密码登录
#define COMMAND_NOTIFY_CXHYDM    31             //查询合约代码
#define COMMAND_NOTIFY_CXJYSTLDM 32             //查询交易所套利代码
#define COMMAND_NOTIFY_CXKHZL    33             //查询客户资料 服务项目等
#define COMMAND_NOTIFY_CXGLXZ    34             //查询关联小组
#define COMMAND_NOTIFY_CXJYBM    35             //查询交易编码
#define COMMAND_NOTIFY_CXYHZH    36             //查询银行帐号

#define COMMAND_USER             60             //之后为自定义各模块使用

//推送类型
#define WEBCUSTOMMESSAGE_PT      11             //普通提示
#define WEBCUSTOMMESSAGE_ZJBZJ   12             //追保风险率
#define WEBCUSTOMMESSAGE_QZPC    13             //强平风险率提示
#define WEBCUSTOMMESSAGE_KHDL    14             //多用户登录提示
#define WEBCUSTOMMESSAGE_XGMM    15             //重新效验密码要求
#define WEBCUSTOMMESSAGE_FWXM    21             //修改服务项目
//通知信息标志
#define MSGFLAG_READ             1              //已阅读
#define MSGFLAG_SAVE             2              //已保存
#define MSGFLAG_RESPONSES        4              //回应
//登录验证类别(密码类别)
#define CLIENT_TYPE_JYMM         1L             //交易密码
#define CLIENT_TYPE_ZJMM         2L             //资金密码
//订单类型
#define DDLX_XJWT                1
#define DDLX_SJWT                2
#define DDLX_TLWT                4              //交易所套利指令
#define DDLX_SWAP                8              //交易所互换指令
#define DDLX_ZSZL                16             //交易所止损指令
#define DDLX_ZYZL                32             //交易所止盈指令
//市价委托标志
#define SJWTBZ_XJWT              0              //限价委托
#define SJWTBZ_ZDTSJ             1              //涨跌停市价
#define SJWTBZ_SJZL              2              //市价指令
//委托查询过滤条件
#define WTCX_FLAG_QBCJ           1              //过滤已全部成交
#define WTCX_FLAG_CXBZ           2              //过滤已撤消
#define WTCX_FLAG_WTFD           4              //过滤废单
#define WTCX_FLAG_KZWT           8              //过滤扩展委托单
//合约代码标志定义
#define QF_QUERY                 0x00000001     //已查询过行情
#define QF_ALTER                 0x00000002     //变动数据未处理(昨持仓和成交量数据)
#define QF_ZXJ                   0x00000004     //最新价或昨结算变动
#define QF_JYSTLDM               0x00000010     //交易所套利代码
#define QF_ZXHYDM                0x00000020     //自选合约代码

#define QF_MASK_SUBSCIBE         0x0000FF00
#define QF_FOCUS                 0x00000100     //关注代码
#define QF_CCDM                  0x00000200     //持仓代码
#define QF_ZHDM                  0x00000400     //组合代码
#define QF_JYK                   0x00000800     //交易卡
#define QF_YMWT                  0x00001000     //预埋委托
#define QF_SUBSCIBE              0x00002000     //订阅标志(临时)

#define ZHHQ_JCXX_FLAG           0x00000001     //价差小于下限标志
#define ZHHQ_JCSX_FLAG           0x00000002
#define ZHHQ_FLAG_MASK           0x0000000F
#define ZHHQ_JCXX_ALERT          0x00010000     //价差小于下限已提醒标志
#define ZHHQ_JCSX_ALERT          0x00020000
#define ZHHQ_ALERT_MASK          0x000F0000

#define QF_ZSZY                  0x00100000     //默认启用止损止盈
#define QF_ZSZY_SJWT             0x00200000     //止损止盈平仓按涨跌停委托

//服务项目
#define FWXM_HQCF                0x00000001     //行情触发服务
#define FWXM_ZSZY                0x00000002     //止损止盈服务
#define FWXM_CJCF                0x00000004     //成交触发服务
#define FWXM_GLWT                0x00000008     //关联委托服务
#define FWXM_PLWT                0x00000010     //批量委托服务
#define FWXM_HQGL                0x00000020     //行情关联委托
#define FWXM_YQZZ                0x00000040     //前端银期转帐
#define FWXM_TLWT                0x00000080     //套利委托服务
#define FWXM_JYSTLWT             0x00000200     //交易所套利委托
#define FWXM_SWAP                0x00000400     //互换交易
#define FWXM_JYSSWAP             0x00000800     //交易所互换指令
#define FWXM_CCZSZY              0x00001000     //持仓止损止盈
#define FWXM_ZLSX                0x00002000     //指令属性
#define FWXM_JYSZSZY             0x00004000     //交易所止损止盈
#define FWXM_ZDDCS               0x00100000     //自动单
#define FWXM_YJFJY               0x00200000     //一键飞交易
#define FWXM_LSCX                0x00400000     //历史查询
//银期业务类别
#define YQYWLB_YHTOQH            2
#define YQYWLB_QHTOYH            4
#define YQYWLB_YECX              128
//委托单类别
#define WTDLB_PTWT               0              //普通委托单
#define WTDLB_ZDQP               1              //自动强平单
#define WTDLB_HQCF               2              //行情触发单
#define WTDLB_ZSZY               3              //止损止盈单
#define WTDLB_CJCF               4              //成交触发单
#define WTDLB_GLWT               5              //关联委托单
#define WTDLB_PLWT               6              //批量委托单
#define WTDLB_TLWT               7              //套利委托单
#define WTDLB_QZPC               8              //强制平仓
#define WTDLB_SWAP               11             //互换交易触发单
#define WTDLB_CCZSZY             13             //持仓止损止盈
//关联交易小组下单方式
#define XDFS_JSXD                1              //按基数下单
#define XDFS_ZLXD                2              //按总量下单
//扩展委托
#define KZWT_ITEM_HQCF        1     //行情触发单
#define KZWT_ITEM_ZSZY        2     //止损止盈单
#define KZWT_ITEM_CJCF        3     //成交触发单
#define KZWT_ITEM_TLWT        4     //套利委托单
#define KZWT_ITEM_PLWT        5     //批量委托
#define KZWT_ITEM_GLWT        6     //关联委托
#define KZWT_ITEM_SWAP        7     //互换交易
#define KZWT_ITEM_ZHTL        8     //套利委托单
//交易所扩展业务
#define JYSYW_ITEM_TLWT       1     //交易所套利委托
#define JYSYW_ITEM_SWAP       2     //互换交易
#define JYSYW_ITEM_ZSZY       3     //止损止盈
//扩展服务
#define KZFW_ITEM_YYQK        1     //预约取款

//控件排列
#define SORT_ITEM_VERT     1
#define SORT_ITEM_HORZ     2
#define SORT_TAB_ORDER     4
//对齐
#define ALIGN_TOP          1
#define ALIGN_BOTTOM       2
#define ALIGN_LEFT         3
#define ALIGN_RIGHT        4
//股东属性
#define GDSX_TJ            16          //投机
#define GDSX_TB            32          //套保
#define GDSX_TL            64          //套利
//投资类别
#define TZLB_TJ            0           //投机
#define TZLB_TB            1           //套保
#define TZLB_TL            2           //套利
//wav定义
#define WAV_WTSB_SUCCESS   0           //委托成功
#define WAV_WTSB_FAIL      1           //委托失败
#define WAV_WTCD_SUCCESS   2           //撤单成功
#define WAV_WTCD_FAIL      3           //撤单失败
#define WAV_CJHB           4           //成交回报
#define WAV_FAIL           5           //操作失败
#define WAV_TLHQ_JCXX      6           //价差减少
#define WAV_TLHQ_JCSX      7           //价差增大
//输入FOCUS
#define ICDS_HYDM             1
#define ICDS_WTJG             2
#define ICDS_WTSL             3
#define ICDS_CFJG             4
//全局系统标志
#define GSF_SYSTEMSTATUS_MASK       0x0000000F  //系统状态掩码
#define GSF_SYSTEMSTATUS_NORMAL     0           //正常
#define GSF_SYSTEMSTATUS_LIQUIDATE  1           //清算
#define GSF_SYSTEMSTATUS_TEST       2           //测试
#define GSF_RESTARTPROGRAM          0x00000020  //重启程序标志
#define GSF_DISABLEACCEL            0x00000040  //停用全局快捷键
#define GSF_SYSTEMLOCK              0x00000080  //程序锁定
#define GSF_CHECKSTAMP              0x00000100  //验证机器特征码
#define GSF_SIGNINJGZX              0x00000400  //登录监管中心
#define GSF_CHECKZJMMFIRST          0x00000800  //银行业务先验证资金密码

//统一分隔符定义
#define SEPARATOR_HYDM              ','         //代码分隔
#define SEPARATOR_SUBSCIBE          ';'         //订阅串中的分隔符
//一些常量
#define DEFAULT_ROWCOUNT            20          //默认每次查询记录数
#define DEFAULT_JMLX                2L          //加密类型
/////////////////////////////////////////////////////////////////////////////


#define USER_FLAG_DLTS           0x00000001     //同帐号登录提示
#define USER_FLAG_UDPQUOTE       0x00000002     //UDP行情
#define USER_FLAG_INITSUBSCIBE   0x00000004     //订阅初始化处理
#define USER_FLAG_EXTERNSUBSCIBE 0x00000008     //重新订阅
#define USER_FLAG_QHHQCX         0x00000010     //订阅代码变动,重新查询特定的合约代码
#define USER_FLAG_CHECKUPDATE    0x00000020     //检查更新
#define USER_FLAG_QUERYALLHYDM   0x00000040     //推送中包含不存在合约而查询全体合约标志
#define USER_FLAG_CCDMZXJGX      0x00000080     //持仓代码最新价更新
#define USER_FLAG_WTQR           0x00000100     //委托确认
#define USER_FLAG_BROADCAST      0x00000200     //本地广播行情
#define USER_FLAG_LOCALTLDM      0x00000400     //本地套利代码缓存
#define USER_FLAG_DLTS_DONE      0x00010000     //同帐号登录提示已处理