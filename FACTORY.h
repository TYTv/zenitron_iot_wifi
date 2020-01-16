//#pragma pack (1)
typedef struct
{
    uint8_t dct_next_boot_mode;

//    uint8_t  uint8_var ;
//    uint32_t uint32_var;
//    char     string_var[50];

} dct_app_boot;
//#pragma pack ()

enum bootselect
{
    boot_normal,
    boot_ota,
    boot_num,
};

void factory_start(void);
uint8_t boot_mode_read_dct(void);
void boot_mode_write_dct(uint8_t mode);
void reboot_now(void);
