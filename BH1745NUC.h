
enum BH1745NUC_DEVICE_ADDRESS
{
    BH1745NUC_DEVICE_ADDRESS_38 = 0x38, // 7bit Addrss(ADDR = 'L')
    BH1745NUC_DEVICE_ADDRESS_39 = 0x39, // 7bit Addrss(ADDR = 'H')
};

enum BH1745NUC_REGISTER
{
    BH1745NUC_SYSTEM_CONTROL = 0x40,    /* RW 0Bh System control */
    BH1745NUC_MODE_CONTROL1 = 0x41,     /* RW 00h Function setting */
    BH1745NUC_MODE_CONTROL2 = 0x42,     /* RW 00h Function setting */
    BH1745NUC_MODE_CONTROL3 = 0x44,     /* RW 00h Function setting */
    BH1745NUC_RED_DATA_LSBs = 0x50,     /* R  00h Low byte of RED */
    BH1745NUC_RED_DATA_MSBs = 0x51,     /* R  00h High byte of RED */
    BH1745NUC_GREEN_DATA_LSBs = 0x52,   /* R  00h Low byte of GREEN */
    BH1745NUC_GREEN_DATA_MSBs = 0x53,   /* R  00h High byte of GREEN */
    BH1745NUC_BLUE_DATA_LSBs = 0x54,    /* R  00h Low byte of BLUE */
    BH1745NUC_BLUE_DATA_MSBs = 0x55,    /* R  00h High byte of BLUE */
    BH1745NUC_CLEAR_DATA_LSBs = 0x56,   /* R  00h Low byte of CLEAR */
    BH1745NUC_CLEAR_DATA_MSBs = 0x57,   /* R  00h High byte of CLEAR */
    BH1745NUC_DINT_DATA_LSBs = 0x58,    /* R  00h Low byte of Internal Data */
    BH1745NUC_DINT_DATA_MSBs = 0x59,    /* R  00h High byte of Internal Data */
    BH1745NUC_INTERRUPT = 0x60,         /* RW 00h Interrupt setting */
    BH1745NUC_PERSISTENCE = 0x61,       /* RW 01h Persistence setting */
    BH1745NUC_TH_LSBs = 0x62,           /* RW FFh Higher threshold low byte */
    BH1745NUC_TH_MSBs = 0x63,           /* RW FFh Higher threshold high byte */
    BH1745NUC_TL_LSBs = 0x64,           /* RW 00h Lower threshold low byte */
    BH1745NUC_TL_MSBs = 0x65,           /* RW 00h Lower threshold high byte */
    BH1745NUC_MANUFACTURER = 0x92,      /* R  E0h ID Manufacturer ID */
};

#define BH1745NUC_PartName          "BH1745NUC"
#define BH1745NUC_Part_ID_Default   0x0B   /* 0b001011 */


int bh1745nuc_get(int argc, char *argv[]);
