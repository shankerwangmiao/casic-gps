#ifdef __APPLE__
# include <libkern/OSByteOrder.h>
# define bswap_16(x) OSSwapInt16(x)
# define bswap_32(x) OSSwapInt32(x)
# define bswap_64(x) OSSwapInt64(x)
# include <machine/endian.h>
# ifndef __BYTE_ORDER
#  define __BYTE_ORDER BYTE_ORDER
# endif
# ifndef __LITTLE_ENDIAN 
#  define __LITTLE_ENDIAN LITTLE_ENDIAN 
# endif
# ifndef __BIG_ENDIAN
#  define __BIG_ENDIAN BIG_ENDIAN
# endif
#else
# include <byteswap.h>
# include <endian.h>
#endif
#if __BYTE_ORDER == __LITTLE_ENDIAN
# define TO_LE32(x) (x)
# define TO_LE16(x) (x)
#elif __BYTE_ORDER == __BIG_ENDIAN
# define TO_LE32(x) (bswap_32(x))
# define TO_LE16(x) (bswap_16(x))
#else
# error cannot detect endianess
#endif
#define FROM_LE32(x) TO_LE32(x)
#define FROM_LE16(x) TO_LE16(x)

#define CASIC_HEADER TO_LE16(0xceba)
enum __CASIC_CLASS{
  CASIC_CLASS_NAV = 0x1,
  CASIC_CLASS_TIM = 0x2,
  CASIC_CLASS_RXM = 0x3,
  CASIC_CLASS_ACK = 0x5,
  CASIC_CLASS_CFG = 0x6,
  CASIC_CLASS_MEAS = 0x7,
  CASIC_CLASS_MSG = 0x8,
  CASIC_CLASS_MON = 0xa,
  CASIC_CLASS_AID = 0xb,
  CASIC_NUM_CLASSES
} ;

static char *casic_classes[CASIC_NUM_CLASSES] = {
  [CASIC_CLASS_NAV] = "NAV",
  [CASIC_CLASS_TIM] = "TIM",
  [CASIC_CLASS_RXM] = "RXM",
  [CASIC_CLASS_ACK] = "ACK",
  [CASIC_CLASS_CFG] = "CFG",
  [CASIC_CLASS_MEAS] = "MEAS",
  [CASIC_CLASS_MSG] = "MSG",
  [CASIC_CLASS_MON] = "MON",
  [CASIC_CLASS_AID] = "AID"
};

enum  __CASIC_COMMANDS_NAV{
  CASIC_NAV_STATUS = 0x00,
  CASIC_NAV_DOP = 0x01,
  CASIC_NAV_SOL = 0x02,
  CASIC_NAV_PV = 0x03,
  CASIC_NAV_TIMEUTC = 0x10,
  CASIC_NAV_CLOCK = 0x11,
  CASIC_NAV_GPSINFO = 0x20,
  CASIC_NAV_BDSINFO = 0x21,
  CASIC_NAV_GLNINFO = 0x22,
  CASIC_NUM_NAV,
  CASIC_TIM_TP = 0x00,
  CASIC_NUM_TIM,
  CASIC_RXM_MEASX = 0x00,
  CASIC_RXM_SVPOS = 0x01,
  CASIC_NUM_RXM,
  CASIC_ACK_NACK = 0x00,
  CASIC_ACK_ACK = 0x01,
  CASIC_NUM_ACK,
  CASIC_CFG_PRT = 0x00,
  CASIC_CFG_MSG = 0x01,
  CASIC_CFG_RST = 0x02,
  CASIC_CFG_TP = 0x03,
  CASIC_CFG_RATE = 0x04,
  CASIC_CFG_CFG = 0x05,
  CASIC_CFG_TMODE = 0x06,
  CASIC_CFG_NAVX = 0x07,
  CASIC_CFG_GROUP = 0x08,
  CASIC_CFG_POLLMSG = 0x10,
  CASIC_NUM_CFG,
  CASIC_MEAS_ = 0x00,
  CASIC_NUM_MEAS,
  CASIC_MSG_BDSUTC = 0x00,
  CASIC_MSG_BDSION = 0x01,
  CASIC_MSG_BDSEPH = 0x02,
  CASIC_MSG_GPSUTC = 0x05,
  CASIC_MSG_GPSION = 0x06,
  CASIC_MSG_GPSEPH = 0x07,
  CASIC_MSG_GLNEPH = 0x08,
  CASIC_NUM_MSG,
  CASIC_MON_VER = 0x04,
  CASIC_MON_HW = 0x09,
  CASIC_NUM_MON,
  CASIC_AID_INI = 0x01,
  CASIC_AID_HUI = 0x03,
  CASIC_NUM_AID
};

static char *__CASIC_CLASS_NAV_COMMANDS[CASIC_NUM_NAV] = {
  [CASIC_NAV_STATUS] = "STATUS",
  [CASIC_NAV_DOP] = "DOP",
  [CASIC_NAV_SOL] = "SOL",
  [CASIC_NAV_PV] = "PV",
  [CASIC_NAV_TIMEUTC] = "TIMEUTC",
  [CASIC_NAV_CLOCK] = "CLOCK",
  [CASIC_NAV_GPSINFO] = "GPSINFO",
  [CASIC_NAV_BDSINFO] = "BDSINFO",
  [CASIC_NAV_GLNINFO] = "GLNINFO",
};
static char *__CASIC_CLASS_TIM_COMMANDS[CASIC_NUM_TIM] = {
  [CASIC_TIM_TP] = "TP",
};
static char *__CASIC_CLASS_RXM_COMMANDS[CASIC_NUM_RXM] = {
  [CASIC_RXM_MEASX] = "MEASX",
  [CASIC_RXM_SVPOS] = "SVPOS",
};
static char *__CASIC_CLASS_ACK_COMMANDS[CASIC_NUM_ACK] = {
  [CASIC_ACK_NACK] = "NACK",
  [CASIC_ACK_ACK] = "ACK",
};
static char *__CASIC_CLASS_CFG_COMMANDS[CASIC_NUM_CFG] = {
  [CASIC_CFG_PRT] = "PRT",
  [CASIC_CFG_MSG] = "MSG",
  [CASIC_CFG_RST] = "RST",
  [CASIC_CFG_TP] = "TP",
  [CASIC_CFG_RATE] = "RATE",
  [CASIC_CFG_CFG] = "CFG",
  [CASIC_CFG_TMODE] = "TMODE",
  [CASIC_CFG_NAVX] = "NAVX",
  [CASIC_CFG_GROUP] = "GROUP",
  [CASIC_CFG_POLLMSG] = "POLLMSG",
};
static char *__CASIC_CLASS_MEAS_COMMANDS[CASIC_NUM_MEAS] = {
  [CASIC_MEAS_] = "",
};
static char *__CASIC_CLASS_MSG_COMMANDS[CASIC_NUM_MSG] = {
  [CASIC_MSG_BDSUTC] = "BDSUTC",
  [CASIC_MSG_BDSION] = "BDSION",
  [CASIC_MSG_BDSEPH] = "BDSEPH",
  [CASIC_MSG_GPSUTC] = "GPSUTC",
  [CASIC_MSG_GPSION] = "GPSION",
  [CASIC_MSG_GPSEPH] = "GPSEPH",
  [CASIC_MSG_GLNEPH] = "GLNEPH",
};
static char *__CASIC_CLASS_MON_COMMANDS[CASIC_NUM_MON] = {
  [CASIC_MON_VER] = "VER",
  [CASIC_MON_HW] = "HW",
};
static char *__CASIC_CLASS_AID_COMMANDS[CASIC_NUM_AID] = {
  [CASIC_AID_INI] = "INI",
  [CASIC_AID_HUI] = "HUI",
};

static char **casic_commands[CASIC_NUM_CLASSES] = {
  [CASIC_CLASS_NAV] = __CASIC_CLASS_NAV_COMMANDS,
  [CASIC_CLASS_TIM] = __CASIC_CLASS_TIM_COMMANDS,
  [CASIC_CLASS_RXM] = __CASIC_CLASS_RXM_COMMANDS,
  [CASIC_CLASS_ACK] = __CASIC_CLASS_ACK_COMMANDS,
  [CASIC_CLASS_CFG] = __CASIC_CLASS_CFG_COMMANDS,
  [CASIC_CLASS_MEAS] = __CASIC_CLASS_MEAS_COMMANDS,
  [CASIC_CLASS_MSG] = __CASIC_CLASS_MSG_COMMANDS,
  [CASIC_CLASS_MON] = __CASIC_CLASS_MON_COMMANDS,
  [CASIC_CLASS_AID] = __CASIC_CLASS_AID_COMMANDS
};

static int casic_commands_nums[CASIC_NUM_CLASSES] = {
  [CASIC_CLASS_NAV] = CASIC_NUM_NAV,
  [CASIC_CLASS_TIM] = CASIC_NUM_TIM,
  [CASIC_CLASS_RXM] = CASIC_NUM_RXM,
  [CASIC_CLASS_ACK] = CASIC_NUM_ACK,
  [CASIC_CLASS_CFG] = CASIC_NUM_CFG,
  [CASIC_CLASS_MEAS] = CASIC_NUM_MEAS,
  [CASIC_CLASS_MSG] = CASIC_NUM_MSG,
  [CASIC_CLASS_MON] = CASIC_NUM_MON,
  [CASIC_CLASS_AID] = CASIC_NUM_AID
};