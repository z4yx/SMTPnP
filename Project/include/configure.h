/*
 * =====================================================================================
 *
 *       Filename:  configure.h
 *
 *    Description:  所有可配置的参数汇总
 *
 *        Version:  
 *        Created:  
 *       Revision:  
 *       Compiler:  
 *
 *         Author:  zhangyuxiang
 *   Organization:  
 *
 * =====================================================================================
 */

//三轴最大行程(um)
#define X_MAX_LIMIT 160000
#define Y_MAX_LIMIT 180000
#define Z_MAX_LIMIT 100000

//X轴步进电机旋转一周对应的直线位移(um)
#define X_DISTANCE_PER_CYCLE 4000
//X轴步进电机旋转一周需要的脉冲数量(考虑细分)
#define X_PULSES_PER_CYCLE   (16*200)
//X轴运行方向调整(取值+/-1)
#define X_DIRECTION_ADJ      1 

//Y轴步进电机旋转一周对应的直线位移(um)
#define Y_DISTANCE_PER_CYCLE 4000
//Y轴步进电机旋转一周需要的脉冲数量(考虑细分)
#define Y_PULSES_PER_CYCLE (16*200)
//Y轴运行方向调整(取值+/-1)
#define Y_DIRECTION_ADJ      -1 

//A轴(贴片头旋转)步进电机旋转一周需要的脉冲数量(考虑细分)
#define A_PULSES_PER_CYCLE (16*200)
//A轴(贴片头旋转)脉冲频率
#define A_PULSE_FREQ       2000

//Z轴(贴片头升降)脉冲频率
#define Z_PULSE_FREQ       2000

//限位开关最小触发间隔时间(ms)
#define LIMIT_SWITCH_MIN_TOGGLE_PERIOD 50
//限位开关接通有效的阈值(ms)
#define LIMIT_SWITCH_VALID_TIME 10

//功率输出板极性反转,影响PWM,风扇等
#define DRIVER_BOARD_POLARITY

//默认给进速度(um/min)
#define DEFAULT_FEEDRATE (500*1000)

//SD卡初始化重试次数限制
#define SD_INIT_RETRY_TIMES 3
//SD卡存放打印文件的目录
#define SD_GFILES_DIR "/"
//支持的最长文件名(包含\0)
#define SD_MAX_FILENAME_LEN (31+1)
//最多列举的G文件数量
#define SD_MAX_ITEMS 32

//每次向上位机报告的间隔(ms)
#define REPORT_PERIOD 1000