/*                                                                            
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                            */


/*                                                                            
                                                                              
                                                                             */

#include <generated/autoconf.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/init.h>
#include <linux/fb.h>
#include <linux/delay.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/earlysuspend.h>
#include <linux/kthread.h>
#include <linux/rtpm_prio.h>

#include "I2C.h"
#include "tmNxCompId.h"
#include "tmdlHdmiTx_IW.h"
#include <linux/string.h>
#ifdef BUILD_UBOOT
#include <asm/arch/mt_gpio.h>
#else
#include <mach/mt_gpio.h>
#include "mach/eint.h"
#include "mach/irqs.h"
#endif
#include "hdmi_drv.h"

static size_t hdmi_i2c_log_on;
#define HDMI_I2C_LOG(fmt, arg...) \
    do { \
	if (hdmi_i2c_log_on) \
	{ \
	    pr_debug("[hdmi_i2c log], %s, #%d", __func__, __LINE__); \
	    pr_debug(fmt, ##arg); \
	} \
    } while (0)

#define HDMI_I2C_FUNC()	\
	do { \
		if (hdmi_i2c_log_on) pr_debug("[hdmi_i2c func] %s\n", __func__); \
	} while (0)

void hdmi_i2c_log_enable(int enable)
{
	pr_debug("hdmi_i2c log %s\n", enable ? "enabled" : "disabled");
	hdmi_i2c_log_on = enable;
}

extern void I2C_ISR(void);

unsigned char nb_byte[3];
unsigned char slave[3];
unsigned char *pt_mtd[3], *pt_mrd[3];
volatile unsigned char transmission;
unsigned char rep_start_cntr;
unsigned char ptr[255];

/*                          */
tmdlHdmiTxIWSemHandle_t gI2CSemaphore;

/*                                                                            
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                             */
/*             */
#if 0

/*         */
/*                                   */
/*                                   */

#if defined GPIO_HDMI_I2C_SDA
#define GPIO_SDA	GPIO_HDMI_I2C_SDA
#else
#error "GPIO_HDMI_I2C_SDA is not defined"
#endif

#if defined GPIO_HDMI_I2C_SCL
#define GPIO_SCL	GPIO_HDMI_I2C_SCL
#else
#error "GPIO_HDMI_I2C_SCL is not defined"
#endif

#define SET_SCCB_CLK_OUTPUT						mt_set_gpio_dir(GPIO_SCL, GPIO_DIR_OUT)
#define SET_SCCB_CLK_INPUT						mt_set_gpio_dir(GPIO_SCL, GPIO_DIR_IN)
#define SET_SCCB_DATA_OUTPUT					mt_set_gpio_dir(GPIO_SDA, GPIO_DIR_OUT)
#define SET_SCCB_DATA_INPUT						mt_set_gpio_dir(GPIO_SDA, GPIO_DIR_IN)

#define SET_SCCB_CLK_HIGH						mt_set_gpio_out(GPIO_SCL, GPIO_OUT_ONE)
#define SET_SCCB_CLK_LOW						mt_set_gpio_out(GPIO_SCL, GPIO_OUT_ZERO)
#define SET_SCCB_DATA_HIGH						mt_set_gpio_out(GPIO_SDA, GPIO_OUT_ONE)
#define SET_SCCB_DATA_LOW						mt_set_gpio_out(GPIO_SDA, GPIO_OUT_ZERO)

#define GET_SCCB_DATA_BIT						mt_get_gpio_in(GPIO_SDA)

#define I2C_DELAY								2

static int i2c_delay(unsigned int n)
{
#if 1
	udelay(n);
#else
	unsigned int count = 1024 * n;
	asm volatile ("1:                                \n\t"
		      "subs   %[count], %[count], #1     \n\t"
		      "bge    1b                         \n\t":[count] "+r"(count)
 :  : "memory");
#endif
	return 0;
}


#define I2C_START_TRANSMISSION \
{ \
	/*                         */ \
	SET_SCCB_CLK_OUTPUT; \
	SET_SCCB_DATA_OUTPUT; \
	SET_SCCB_CLK_HIGH; \
	SET_SCCB_DATA_HIGH; \
	/*                         */\
	i2c_delay(I2C_DELAY);	\
	SET_SCCB_DATA_LOW; \
	/*                         */\
	i2c_delay(I2C_DELAY);	\
	SET_SCCB_CLK_LOW; \
}

#define I2C_STOP_TRANSMISSION \
{ \
	/*                         */ \
	SET_SCCB_CLK_OUTPUT; \
	SET_SCCB_DATA_OUTPUT; \
	SET_SCCB_CLK_LOW; \
	SET_SCCB_DATA_LOW; \
	/*                         */\
	i2c_delay(I2C_DELAY);	\
	SET_SCCB_CLK_HIGH; \
	/*                         */\
	i2c_delay(I2C_DELAY);	\
	SET_SCCB_DATA_HIGH; \
}

static void SCCB_send_byte(unsigned char send_byte)
{
	volatile signed char i;
	/*                          */

	for (i = 7; i >= 0; i--) {	/*              */
		if (send_byte & (1 << i)) {
			SET_SCCB_DATA_HIGH;
		} else {
			SET_SCCB_DATA_LOW;
		}
		i2c_delay(I2C_DELAY);
		SET_SCCB_CLK_HIGH;
		i2c_delay(I2C_DELAY);
		SET_SCCB_CLK_LOW;
		i2c_delay(I2C_DELAY);
	}
	/*                         */
	SET_SCCB_DATA_LOW;
	SET_SCCB_DATA_INPUT;
	SET_SCCB_CLK_HIGH;
	i2c_delay(I2C_DELAY);
	SET_SCCB_CLK_LOW;
	SET_SCCB_DATA_OUTPUT;
}				/*                  */

static unsigned char SCCB_get_byte(void)
{
	volatile signed char i;
	/*                           */
	unsigned char get_byte = 0;

	SET_SCCB_DATA_INPUT;

	for (i = 7; i >= 0; i--) {	/*              */
		SET_SCCB_CLK_HIGH;
		/*                           */
		i2c_delay(I2C_DELAY);
		if (GET_SCCB_DATA_BIT)
			get_byte |= (1 << i);
		/*                           */
		i2c_delay(I2C_DELAY);
		SET_SCCB_CLK_LOW;
		/*                           */
		i2c_delay(I2C_DELAY);
	}
	/*                         */
	SET_SCCB_DATA_OUTPUT;
	SET_SCCB_DATA_HIGH;
	/*                           */
	i2c_delay(I2C_DELAY);
	SET_SCCB_CLK_HIGH;
	/*                           */
	i2c_delay(I2C_DELAY);
	SET_SCCB_CLK_LOW;

	return get_byte;
}				/*                  */

static void sccb_write(unsigned char slave_addr, unsigned char addr, unsigned char para)
{
	/*                            */

	I2C_START_TRANSMISSION;
	/*                           */
	i2c_delay(I2C_DELAY);
	SCCB_send_byte(slave_addr);

	/*                           */
	i2c_delay(I2C_DELAY);
	SCCB_send_byte(addr);

	/*                           */
	i2c_delay(I2C_DELAY);
	SCCB_send_byte(para);

	/*                           */
	i2c_delay(I2C_DELAY);
	i2c_delay(I2C_DELAY);
	i2c_delay(I2C_DELAY);
	I2C_STOP_TRANSMISSION;
}

static void sccb_write_multi(unsigned char slave_addr, unsigned char *addr, unsigned int nb_char)
{
	volatile unsigned int i;

	I2C_START_TRANSMISSION;

	i2c_delay(I2C_DELAY);
	SCCB_send_byte(slave_addr);

	for (i = 0; i < nb_char; i++) {
		i2c_delay(I2C_DELAY);
		SCCB_send_byte(addr[i]);
	}

	I2C_STOP_TRANSMISSION;
}


static unsigned int sccb_read(unsigned char slave_addr, unsigned char addr)
{
	unsigned int get_byte;
	/*                             */

	I2C_START_TRANSMISSION;
	/*                           */
	i2c_delay(I2C_DELAY);
	SCCB_send_byte(slave_addr);
	/*                           */
	i2c_delay(I2C_DELAY);
	SCCB_send_byte(addr);
	/*                           */
	i2c_delay(I2C_DELAY);
	I2C_STOP_TRANSMISSION;
	/*                           */
	i2c_delay(I2C_DELAY);
	I2C_START_TRANSMISSION;
	/*                           */
	i2c_delay(I2C_DELAY);
	SCCB_send_byte(slave_addr | 0x1);
	/*                           */
	i2c_delay(I2C_DELAY);
	get_byte = SCCB_get_byte();
	/*                           */
	i2c_delay(I2C_DELAY);
	I2C_STOP_TRANSMISSION;

	return get_byte;
}

tmErrorCode_t suspend_i2c(void)
{
	mt_set_gpio_pull_enable(GPIO_SDA, true);
	mt_set_gpio_pull_select(GPIO_SDA, GPIO_PULL_UP);
	/*                              */
	/*                                         */
	/*                                                 */


	mt_set_gpio_pull_enable(GPIO_SCL, true);
	mt_set_gpio_pull_select(GPIO_SCL, GPIO_PULL_UP);
	return TM_OK;
}

tmErrorCode_t resume_i2c(void)
{
	mt_set_gpio_pull_enable(GPIO_SDA, false);

	mt_set_gpio_pull_enable(GPIO_SCL, false);
	return TM_OK;
}

#include <linux/semaphore.h>
DEFINE_SEMAPHORE(i2c_mutex);

tmErrorCode_t Init_i2c(void)
{
	tmErrorCode_t errCode;
#if 1
	HDMI_I2C_LOG("hdmi, %s\n", __func__);
	mt_set_gpio_mode(GPIO_SDA, GPIO_MODE_00);
	mt_set_gpio_mode(GPIO_SCL, GPIO_MODE_00);

	mt_set_gpio_dir(GPIO_SDA, GPIO_DIR_OUT);
	mt_set_gpio_dir(GPIO_SCL, GPIO_DIR_OUT);
#endif

#if 0
	/*                */
	I2CONCLR = 0x6C;	/*                            */
	I2CONSET = 0x40;	/*            */

	/*                                      */
	/*                                                                  */
	/*                                                      */
	/*                           */
	I2SCLH = 0x7D;
	I2SCLL = 0x7D;

	/*                            */
	VICIntEnable |= 0x200;	/*                         */
	VICVectCntl0 = 0x29;	/*                              */
	VICVectAddr0 = (unsigned long)I2C_ISR;

#endif
	/*                                            */
	/*                                                        */

	gI2CSemaphore = (unsigned long)(&i2c_mutex);
	errCode = TM_OK;

	return errCode;
}

/*                                                                            
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                             
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                             */

unsigned char Write_i2c(unsigned char address, unsigned char *ptr, unsigned char nb_char)
{
	/*                  */
	int hConnection;

	HDMI_I2C_LOG("hdmi, %s, addr = 0x%08x, count = %d, data= 0x%08x, 0x%08x\n", __func__,
		     address, nb_char, ptr[0], ptr[1]);

	switch (address) {
	case reg_TDA997X:
		hConnection = (2 * slaveAddressTDA9975A);
		break;
	case reg_TDA998X:
		hConnection = (2 * slaveAddressTDA9984);
		break;
	case reg_TDA8778:
		hConnection = (2 * slaveAddressTDA8778);
		break;
	case reg_UDA1355H:
		hConnection = (2 * slaveAddressUDA1355H);
		break;
	case reg_MAX4562:
		hConnection = (2 * slaveAddressMAX4562);
		break;
	case reg_TDA9989_CEC:
	case reg_TDA9950:
		hConnection = (2 * slaveAddressDriverHdmiCEC);
		break;
	case reg_PCA9536:
		hConnection = (2 * slaveAddressPCA9536);
		break;

	default:
		return (unsigned char)~TM_OK;	/*                             */
	}

	if (nb_char > 2) {
		HDMI_I2C_LOG("hdmi, !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%s, nb_char=%d\n", __func__,
			     nb_char);
		sccb_write_multi((hConnection), ptr, nb_char);
	} else {
		sccb_write((hConnection), ptr[0], ptr[1]);
	}
#if 0

	pt_mtd[0] = ptr;
	nb_byte[0] = nb_char;
	slave[0] = hConnection & 0xFE;	/*         */
	rep_start_cntr = 0;	/*                                                          */

	transmission = INIT;	/*                    */
	I2CONSET = 0x20;

	while (transmission == INIT)
		i++;		/*               */
	while (transmission == START)
		i++;		/*                          */
#endif
	return 0;
}





/*                                                                            
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                              
                                                                             */


unsigned char Read_at_i2c(unsigned char address, unsigned char pos, unsigned char nb_char,
			  unsigned char *ptr)
{
	/*                  */
	int hConnection;
	switch (address) {
	case reg_TDA997X:
		hConnection = (2 * slaveAddressTDA9975A);
		break;
	case reg_TDA998X:
		hConnection = (2 * slaveAddressTDA9984);
		break;
	case reg_TDA8778:
		hConnection = (2 * slaveAddressTDA8778);
		break;
	case reg_UDA1355H:
		hConnection = (2 * slaveAddressUDA1355H);
		break;
	case reg_MAX4562:
		hConnection = (2 * slaveAddressMAX4562);
		break;
	case reg_TDA9989_CEC:
	case reg_TDA9950:
		hConnection = (2 * slaveAddressDriverHdmiCEC);
		break;
	case reg_PCA9536:
		hConnection = (2 * slaveAddressPCA9536);
		break;
	default:
		return (unsigned char)~TM_OK;	/*                             */
	}
	*ptr = sccb_read((hConnection), pos);
	HDMI_I2C_LOG("hdmi, %s, address=0x%08x, pos=0x%08x, nb_char=0x%08x, value=0x%08x\n",
		     __func__, address, pos, nb_char, *ptr);

	return 0;
#if 0



	pt_mtd[1] = &pos;
	pt_mrd[0] = ptr;
	nb_byte[1] = 1;
	nb_byte[0] = nb_char;
	slave[1] = hConnection & 0xFE;	/*         */
	slave[0] = hConnection | 0x01;	/*         */
	rep_start_cntr = 1;	/*                                                                           */

	transmission = INIT;
	I2CONSET = 0x20;	/*                    */
	while (transmission == INIT)
		i++;		/*               */
	while (transmission == START)
		i++;		/*                          */
	return (transmission);
#endif
}


/*                                                                            
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                                
                                                                    
                                                                                
                                                                                
                                                                             */
/*                                          */
/*                                          */
/*                                          */
/*                                          */
/*                                          */
/*                                          */
/*                                          */
unsigned char Read_edid(unsigned char seg_addr, unsigned char seg_ptr, unsigned char data_addr,
			unsigned char word_offset, unsigned char nb_char, unsigned char *ptr)
{
	/*                  */
	HDMI_I2C_LOG("hdmi, %s\n", __func__);
#if 0

	pt_mtd[2] = &seg_ptr;
	pt_mtd[1] = &word_offset;
	pt_mrd[0] = ptr;
	nb_byte[2] = 1;		/*                                 */
	nb_byte[1] = 1;		/*                             */
	nb_byte[0] = nb_char;	/*                              */
	slave[2] = seg_addr & 0xFE;	/*                          */
	slave[1] = data_addr & 0xFE;	/*                       */
	slave[0] = data_addr | 0x01;	/*                       */
	if (seg_addr == 0) {	/*                                                                                     */
		rep_start_cntr = 1;	/*                                                      */
	} else {
		rep_start_cntr = 2;	/*                                                                       */
	}


	transmission = INIT;
	I2CONSET = 0x20;	/*                    */
	while (transmission == INIT)
		i++;		/*               */
	while (transmission == START)
		i++;		/*                          */
#endif
	return (transmission);
}



tmErrorCode_t i2cWrite(i2cRegisterType_t type_register, tmbslHdmiSysArgs_t *pSysArgs)
{

	tmErrorCode_t errCode;
	int i;

	/*                            */
	errCode = tmdlHdmiTxIWSemaphoreP(gI2CSemaphore);
	if (errCode) {
		return errCode;
	}

	ptr[0] = pSysArgs->firstRegister;

	for (i = 1; i <= pSysArgs->lenData; i++) {
		ptr[i] = (*pSysArgs->pData);
		(pSysArgs->pData)++;
	}
	pSysArgs->lenData++;

	errCode = Write_i2c(type_register, ptr, pSysArgs->lenData);
	if (errCode) {
		/*                                               */
		tmdlHdmiTxIWSemaphoreV(gI2CSemaphore);
		return errCode;
	}

	/*                               */
	errCode = tmdlHdmiTxIWSemaphoreV(gI2CSemaphore);
	if (errCode) {
		return errCode;
	}

	return errCode;
}


tmErrorCode_t i2cRead(i2cRegisterType_t type_register, tmbslHdmiSysArgs_t *pSysArgs)
{
	tmErrorCode_t errCode;

	/*                            */
	errCode = tmdlHdmiTxIWSemaphoreP(gI2CSemaphore);
	if (errCode) {
		return errCode;
	}

	errCode =
	    Read_at_i2c(type_register, pSysArgs->firstRegister, pSysArgs->lenData, pSysArgs->pData);
	if (errCode) {
		/*                                               */
		tmdlHdmiTxIWSemaphoreV(gI2CSemaphore);
		return errCode;
	}

	/*                               */
	errCode = tmdlHdmiTxIWSemaphoreV(gI2CSemaphore);
	if (errCode) {
		return errCode;
	}

	return errCode;
}



/*                                          */
/*                                          */
/*                                          */
/*                                          */
/*                                          */
/*                                          */
/*                                          */
/*                                          */
/*                                          */
unsigned char i2cReadEdid(unsigned char seg_addr, unsigned char seg_ptr, unsigned char data_addr,
			  unsigned char word_offset, unsigned char nb_char, unsigned char *ptr)
{
	/*                  */
	/*                        */

	HDMI_I2C_LOG("hdmi, %s\n", __func__);
#if 0
	/*                            */
	errCode = tmdlHdmiTxIWSemaphoreP(gI2CSemaphore);
	if (errCode) {
		return errCode;
	}

	pt_mtd[2] = &seg_ptr;
	pt_mtd[1] = &word_offset;
	pt_mrd[0] = ptr;
	nb_byte[2] = 1;		/*                                 */
	nb_byte[1] = 1;		/*                             */
	nb_byte[0] = nb_char;	/*                              */
	slave[2] = seg_addr & 0xFE;	/*                          */
	slave[1] = data_addr & 0xFE;	/*                       */
	slave[0] = data_addr | 0x01;	/*                       */
	if (seg_addr == 0) {	/*                                                                                     */
		rep_start_cntr = 1;	/*                                                      */
	} else {
		rep_start_cntr = 2;	/*                                                                       */
	}


	transmission = INIT;
	I2CONSET = 0x20;	/*                    */
	while (transmission == INIT)
		i++;		/*               */
	while (transmission == START)
		i++;		/*                          */

	/*                               */
	errCode = tmdlHdmiTxIWSemaphoreV(gI2CSemaphore);
	if (errCode) {
		return errCode;
	}
#endif

	return (transmission);
}

#else				/*        */

#include <linux/semaphore.h>
DEFINE_SEMAPHORE(i2c_mutex);

/*                                                                            */
/*                         */
/*                                                                            */
#define MAX_TRANSACTION_LENGTH 8
#define HDMI_DEVICE_NAME            "mtk-hdmi"
#define NXP19989_I2C_SLAVE_ADDR  slaveAddressTDA9989
/*                                                                            */
static int hdmi_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id);
/*                                                                                               */
static int hdmi_i2c_remove(struct i2c_client *client);
/*                                                                            */
static struct i2c_client *nxp19989_i2c_client;
static const struct i2c_device_id hdmi_i2c_id[] = { {HDMI_DEVICE_NAME, 0}, {} };

static struct i2c_board_info i2c_hdmi __initdata = {
	I2C_BOARD_INFO(HDMI_DEVICE_NAME, (NXP19989_I2C_SLAVE_ADDR >> 1)),
	/*                                                                 */
};

/*                                                                            */
struct i2c_driver hdmi_i2c_driver = {
	.probe = hdmi_i2c_probe,
	.remove = hdmi_i2c_remove,
	/*                            */
	.driver = {.name = HDMI_DEVICE_NAME,},
	.id_table = hdmi_i2c_id,
	/*                                                 */
};

struct nxp19989_i2c_data {
	struct i2c_client *client;
	uint16_t addr;
	int use_reset;		/*                */
	int use_irq;		/*               */
	int retry;
};

static struct nxp19989_i2c_data *obj_i2c_data;

tmErrorCode_t Init_i2c(void)
{
	tmErrorCode_t errCode;
	HDMI_I2C_LOG("hdmi, %s\n", __func__);


	i2c_register_board_info(0, &i2c_hdmi, 1);

	if (i2c_add_driver(&hdmi_i2c_driver)) {
		HDMI_I2C_LOG("unable to add HDMI i2c driver.\n");
		return -1;

	}
	gI2CSemaphore = (unsigned long)(&i2c_mutex);
	errCode = TM_OK;

	return errCode;
}


#include "tda998x.h"
extern tda_instance our_instance;
/*                                                                            */

static int hdmi_i2c_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	int ret = -1;
	struct nxp19989_i2c_data *obj;
	tda_instance *this;

	HDMI_I2C_LOG("MediaTek HDMI i2c probe\n");

	obj = kzalloc(sizeof(*obj), GFP_KERNEL);
	if (obj == NULL) {
		ret = -ENOMEM;
		HDMI_I2C_LOG(HDMI_DEVICE_NAME ": Allocate ts memory fail\n");
		return ret;
	}
	obj_i2c_data = obj;
	obj->client = client;


	this = &our_instance;
	this->driver.i2c_client = client;


	nxp19989_i2c_client = obj->client;
	i2c_set_clientdata(client, obj);

	HDMI_I2C_LOG("MediaTek HDMI i2c probe success\n");

	return 0;
}

/*                                                                            */

static int hdmi_i2c_remove(struct i2c_client *client)
{
	nxp19989_i2c_client = NULL;
	i2c_unregister_device(client);
	kfree(i2c_get_clientdata(client));
	i2c_del_driver(&hdmi_i2c_driver);
	return 0;
}

tmErrorCode_t suspend_i2c(void)
{
	return TM_OK;
}

tmErrorCode_t resume_i2c(void)
{
	return TM_OK;
}



static void sccb_write(unsigned char slave_addr, unsigned char addr, unsigned char data)
{

	/*                                                                                               */

	struct i2c_client *client = nxp19989_i2c_client;
	u8 buf[2];
	int ret = 0;
	u32 client_main_addr = client->addr;

	/*                                            */
	client->addr = slave_addr;

	buf[0] = addr;
	buf[1] = data;

	ret = i2c_master_send(client, (const char *)buf, 2);
	if (ret < 0) {
		HDMI_I2C_LOG("send command error!!\n");
		return /*       */;
	}

	/*                                */
	client->addr = client_main_addr;

	return /*  */;
}

static void sccb_write_multi(unsigned char slave_addr, unsigned char *data, unsigned int len)
{
	/*                                                                                               */

	/*                                                                                */
	int err, idx /*      */;
	char buf[MAX_TRANSACTION_LENGTH];
	struct i2c_client *client = nxp19989_i2c_client;

	u32 client_main_addr = client->addr;

	/*                                            */
	client->addr = slave_addr;


	if (!client) {
		return /*       */;
	}
#if 0
	if (len >= MAX_TRANSACTION_LENGTH) {
		HDMI_I2C_LOG(" length %d exceeds %d\n", len, MAX_TRANSACTION_LENGTH);
		return -EINVAL;
	}

	num = 0;
	for (idx = 0; idx < len; idx++) {
		buf[num++] = data[idx];
	}

	err = i2c_master_send(client, buf, num);
	if (err < 0) {
		HDMI_I2C_LOG("send command error!!\n");
		return -EFAULT;
	} else {
		err = 0;	/*         */
	}
#else
	buf[0] = *data;
	data++;
	for (idx = len - 1; idx != 0; idx--) {
		buf[1] = *data;
		err = i2c_master_send(client, buf, 2);
		if (err < 0) {
			HDMI_I2C_LOG("send command error!!\n");
			return /*       */;
		}
		data++;
		buf[0] = buf[0] + 1;	/*                                                */
	}
#endif

	/*                                */
	client->addr = client_main_addr;


	return /*    */;
}


static unsigned int sccb_read(unsigned char slave_addr, unsigned char addr)
{
	/*                                                                                        */

	u8 buf;
	int ret = 0;
	struct i2c_client *client = nxp19989_i2c_client;


	u32 client_main_addr = client->addr;

	/*                                            */
	client->addr = slave_addr;



	buf = addr;
	ret = i2c_master_send(client, (const char *)&buf, 1);
	if (ret < 0) {
		HDMI_I2C_LOG("send command error!!\n");
		return -EFAULT;
	}
	ret = i2c_master_recv(client, (char *)&buf, 1);
	if (ret < 0) {
		HDMI_I2C_LOG("reads data error!!\n");
		return -EFAULT;
	}


	/*                                */
	client->addr = client_main_addr;


	/*                                                   */
	return buf;
}


unsigned char Write_i2c(unsigned char address, unsigned char *ptr, unsigned char nb_char)
{
	/*                  */
	int hConnection;
	/*                                                                                                           */
	switch (address) {
	case reg_TDA997X:
		hConnection = (2 * slaveAddressTDA9975A);
		break;
	case reg_TDA998X:
		hConnection = (2 * slaveAddressTDA9984);
		break;
	case reg_TDA8778:
		hConnection = (2 * slaveAddressTDA8778);
		break;
	case reg_UDA1355H:
		hConnection = (2 * slaveAddressUDA1355H);
		break;
	case reg_MAX4562:
		hConnection = (2 * slaveAddressMAX4562);
		break;
	case reg_TDA9989_CEC:
	case reg_TDA9950:
		hConnection = (2 * slaveAddressDriverHdmiCEC);
		break;
	case reg_PCA9536:
		hConnection = (2 * slaveAddressPCA9536);
		break;

	default:
		return (unsigned char)~TM_OK;	/*                             */
	}


	hConnection = hConnection >> 1;

	if (nb_char > 2) {
		/*                                                                                          */
		sccb_write_multi((hConnection), ptr, nb_char);
	} else {
		sccb_write((hConnection), ptr[0], ptr[1]);
	}
	return 0;
}



unsigned char Read_at_i2c(unsigned char address, unsigned char pos, unsigned char nb_char,
			  unsigned char *ptr)
{
	/*                  */
	int hConnection;
	switch (address) {
	case reg_TDA997X:
		hConnection = (2 * slaveAddressTDA9975A);
		break;
	case reg_TDA998X:
		hConnection = (2 * slaveAddressTDA9984);
		break;
	case reg_TDA8778:
		hConnection = (2 * slaveAddressTDA8778);
		break;
	case reg_UDA1355H:
		hConnection = (2 * slaveAddressUDA1355H);
		break;
	case reg_MAX4562:
		hConnection = (2 * slaveAddressMAX4562);
		break;
	case reg_TDA9989_CEC:
	case reg_TDA9950:
		hConnection = (2 * slaveAddressDriverHdmiCEC);
		break;
	case reg_PCA9536:
		hConnection = (2 * slaveAddressPCA9536);
		break;
	default:
		return (unsigned char)~TM_OK;	/*                             */
	}

	hConnection = hConnection >> 1;


	*ptr = sccb_read((hConnection), pos);
	/*                                                                                                                      */

	return 0;
}

unsigned char Read_edid(unsigned char seg_addr, unsigned char seg_ptr, unsigned char data_addr,
			unsigned char word_offset, unsigned char nb_char, unsigned char *ptr)
{
	HDMI_I2C_LOG("hdmi, %s\n", __func__);
	return (transmission);
}



tmErrorCode_t i2cWrite(i2cRegisterType_t type_register, tmbslHdmiSysArgs_t *pSysArgs)
{

	/*                                       */
	tmErrorCode_t errCode;
	int i;

	/*                            */
	errCode = tmdlHdmiTxIWSemaphoreP(gI2CSemaphore);
	if (errCode) {
		return errCode;
	}

	ptr[0] = pSysArgs->firstRegister;

	for (i = 1; i <= pSysArgs->lenData; i++) {
		ptr[i] = (*pSysArgs->pData);
		(pSysArgs->pData)++;
	}
	pSysArgs->lenData++;

	errCode = Write_i2c(type_register, ptr, pSysArgs->lenData);
	if (errCode) {
		/*                                               */
		tmdlHdmiTxIWSemaphoreV(gI2CSemaphore);
		return errCode;
	}

	/*                               */
	errCode = tmdlHdmiTxIWSemaphoreV(gI2CSemaphore);
	if (errCode) {
		return errCode;
	}

	return errCode;
}



tmErrorCode_t i2cRead(i2cRegisterType_t type_register, tmbslHdmiSysArgs_t *pSysArgs)
{
	tmErrorCode_t errCode;

	/*                            */
	errCode = tmdlHdmiTxIWSemaphoreP(gI2CSemaphore);
	if (errCode) {
		return errCode;
	}

	errCode =
	    Read_at_i2c(type_register, pSysArgs->firstRegister, pSysArgs->lenData, pSysArgs->pData);
	if (errCode) {
		/*                                               */
		tmdlHdmiTxIWSemaphoreV(gI2CSemaphore);
		return errCode;
	}

	/*                               */
	errCode = tmdlHdmiTxIWSemaphoreV(gI2CSemaphore);
	if (errCode) {
		return errCode;
	}

	return errCode;
}



unsigned char i2cReadEdid(unsigned char seg_addr, unsigned char seg_ptr, unsigned char data_addr,
			  unsigned char word_offset, unsigned char nb_char, unsigned char *ptr)
{

	HDMI_I2C_LOG("hdmi, %s\n", __func__);

	return (transmission);
}


#endif				/*            */
