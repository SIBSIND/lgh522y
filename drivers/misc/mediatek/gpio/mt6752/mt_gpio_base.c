/******************************************************************************
 * mt_gpio_base.c - MTKLinux GPIO Device Driver
 * 
 * Copyright 2008-2009 MediaTek Co.,Ltd.
 * 
 * DESCRIPTION:
 *     This file provid the other drivers GPIO relative functions
 *
 ******************************************************************************/

#include <mach/sync_write.h>
//                             
#include <mach/mt_typedefs.h>
#include <mach/mt_gpio.h>
#include <mach/mt_gpio_core.h>
#include <mach/mt_gpio_base.h>
//       
#include <mach/gpio_cfg.h>
#ifdef CONFIG_OF
#include <linux/of_address.h>
#endif
#ifdef CONFIG_MD32_SUPPORT
#include <linux/workqueue.h>
#include <mach/md32_ipi.h>
#endif

spinlock_t		 mtk_gpio_lock;

#ifdef CONFIG_MD32_SUPPORT
struct GPIO_IPI_Packet
{
    u32 touch_pin;
};
static struct work_struct work_md32_cust_pin;
static struct workqueue_struct *wq_md32_cust_pin;
#endif

//                           
//                        

struct mt_gpio_vbase gpio_vbase;
static GPIO_REGS *gpio_reg;
/*                                                                           */
int mt_set_gpio_dir_base(unsigned long pin, unsigned long dir)
{
    unsigned long pos;
    unsigned long bit;
    GPIO_REGS *reg = gpio_reg;

    pos = pin / MAX_GPIO_REG_BITS;
    bit = pin % MAX_GPIO_REG_BITS;
    
    if (dir == GPIO_DIR_IN)
        GPIO_SET_BITS((1L << bit), &reg->dir[pos].rst);
    else
        GPIO_SET_BITS((1L << bit), &reg->dir[pos].set);
    return RSUCCESS;
}
/*                                                                           */
int mt_get_gpio_dir_base(unsigned long pin)
{    
    unsigned long pos;
    unsigned long bit;
    unsigned long data;
    GPIO_REGS *reg = gpio_reg;

    pos = pin / MAX_GPIO_REG_BITS;
    bit = pin % MAX_GPIO_REG_BITS;
    
    data = GPIO_RD32(&reg->dir[pos].val);
    return (((data & (1L << bit)) != 0)? 1: 0);        
}
/*                                                                           */
int mt_set_gpio_pull_enable_base(unsigned long pin, unsigned long enable)
{

    if(PULLEN_offset[pin].offset == -1){
	  return GPIO_PULL_EN_UNSUPPORTED;
    }
    else{
    	  if (enable == GPIO_PULL_DISABLE)
		GPIO_SET_BITS((1L << (PULLEN_offset[pin].offset)), PULLEN_addr[pin].addr + 8);
	  else
		GPIO_SET_BITS((1L << (PULLEN_offset[pin].offset)), PULLEN_addr[pin].addr + 4);
    }

    return RSUCCESS;
}
/*                                                                           */
int mt_get_gpio_pull_enable_base(unsigned long pin)
{
    unsigned long data;

    if(PULLEN_offset[pin].offset == -1){
	  return GPIO_PULL_EN_UNSUPPORTED;
    }
    else{   
	  data = GPIO_RD32(PULLEN_addr[pin].addr);

          return (((data & (1L << (PULLEN_offset[pin].offset))) != 0)? 1: 0);
    }        
}
/*                                                                           */
int mt_set_gpio_smt_base(unsigned long pin, unsigned long enable)
{
    unsigned long flags;

    if(SMT_offset[pin].offset == -1){
	  return GPIO_SMT_UNSUPPORTED;
    }
    else if((pin >= 149) && (pin < 179)){
	spin_lock_irqsave(&mtk_gpio_lock, flags);
	  if (enable == GPIO_SMT_DISABLE)
		GPIO_CLR_BITS((1L << (SMT_offset[pin].offset)), SMT_addr[pin].addr);
	  else
		GPIO_SW_SET_BITS((1L << (SMT_offset[pin].offset)), SMT_addr[pin].addr);
	spin_unlock_irqrestore(&mtk_gpio_lock, flags);
    }
    else{
    	  if (enable == GPIO_SMT_DISABLE)
		GPIO_SET_BITS((1L << (SMT_offset[pin].offset)), SMT_addr[pin].addr + 8);
	  else
		GPIO_SET_BITS((1L << (SMT_offset[pin].offset)), SMT_addr[pin].addr + 4);
    }

    return RSUCCESS;
}
/*                                                                           */
int mt_get_gpio_smt_base(unsigned long pin)
{
    unsigned long data;

    if(SMT_offset[pin].offset == -1){
	  return GPIO_SMT_UNSUPPORTED;
    }
    else{
	  data = GPIO_RD32(SMT_addr[pin].addr);

          return (((data & (1L << (SMT_offset[pin].offset))) != 0)? 1: 0);
    }
}
/*                                                                           */
int mt_set_gpio_ies_base(unsigned long pin, unsigned long enable)
{
    unsigned long flags;

    if(IES_offset[pin].offset == -1){
	  return GPIO_IES_UNSUPPORTED;
    }
    else if((pin >= 149) && (pin < 179)){
	spin_lock_irqsave(&mtk_gpio_lock, flags);
	  if (enable == GPIO_IES_DISABLE)
		GPIO_CLR_BITS((1L << (IES_offset[pin].offset)), IES_addr[pin].addr);
	  else
		GPIO_SW_SET_BITS((1L << (IES_offset[pin].offset)), IES_addr[pin].addr);
	spin_unlock_irqrestore(&mtk_gpio_lock, flags);
    }
    else{
    	  if (enable == GPIO_IES_DISABLE)
		GPIO_SET_BITS((1L << (IES_offset[pin].offset)), IES_addr[pin].addr + 8);
	  else
		GPIO_SET_BITS((1L << (IES_offset[pin].offset)), IES_addr[pin].addr + 4);
    }

    return RSUCCESS;
}
/*                                                                           */
int mt_get_gpio_ies_base(unsigned long pin)
{
    unsigned long data;

    if(IES_offset[pin].offset == -1){
	  return GPIO_IES_UNSUPPORTED;
    }
    else{
	  data = GPIO_RD32(IES_addr[pin].addr);

          return (((data & (1L << (IES_offset[pin].offset))) != 0)? 1: 0);
    }
}
/*                                                                           */
int mt_set_gpio_pull_select_base(unsigned long pin, unsigned long select)
{
    unsigned long flags;

    if((PULL_offset[pin].offset == -1) && (PU_offset[pin].offset == -1)){
	  return GPIO_PULL_UNSUPPORTED;
    }
    else if(PULL_offset[pin].offset == -1){
	spin_lock_irqsave(&mtk_gpio_lock, flags);
	  if (select == GPIO_PULL_DOWN){
		GPIO_CLR_BITS((1L << (PU_offset[pin].offset)), PU_addr[pin].addr);
		GPIO_SW_SET_BITS((1L << (PD_offset[pin].offset)), PD_addr[pin].addr);
	  }
	  else {
		GPIO_CLR_BITS((1L << (PD_offset[pin].offset)), PD_addr[pin].addr);
		GPIO_SW_SET_BITS((1L << (PU_offset[pin].offset)), PU_addr[pin].addr);
	  }
	spin_unlock_irqrestore(&mtk_gpio_lock, flags);
    }
    else{
	  if (select == GPIO_PULL_DOWN)
		GPIO_SET_BITS((1L << (PULL_offset[pin].offset)), PULL_addr[pin].addr + 8);
	  else
		GPIO_SET_BITS((1L << (PULL_offset[pin].offset)), PULL_addr[pin].addr + 4);
    }

    return RSUCCESS;
}
/*                                                                           */
int mt_get_gpio_pull_select_base(unsigned long pin)
{
    unsigned long data;

    if((PULL_offset[pin].offset == -1) && (PU_offset[pin].offset == -1)){
	  return GPIO_PULL_UNSUPPORTED;
    }
    else if(PULL_offset[pin].offset == -1){
	  data = GPIO_RD32(PU_addr[pin].addr);

    	  return (((data & (1L << (PU_offset[pin].offset))) != 0)? 1: 0);
    }
    else{
	  data = GPIO_RD32(PULL_addr[pin].addr);

    	  return (((data & (1L << (PULL_offset[pin].offset))) != 0)? 1: 0);
    }
}
/*                                                                           */
int mt_set_gpio_inversion_base(unsigned long pin, unsigned long enable)
{/*      
   */
    return RSUCCESS;
}
/*                                                                           */
int mt_get_gpio_inversion_base(unsigned long pin)
{/*      */
   	return 0;//      
}
/*                                                                           */
int mt_set_gpio_out_base(unsigned long pin, unsigned long output)
{
    unsigned long pos;
    unsigned long bit;
    GPIO_REGS *reg = gpio_reg;

    pos = pin / MAX_GPIO_REG_BITS;
    bit = pin % MAX_GPIO_REG_BITS;
    
    if (output == GPIO_OUT_ZERO)
        GPIO_SET_BITS((1L << bit), &reg->dout[pos].rst);
    else
        GPIO_SET_BITS((1L << bit), &reg->dout[pos].set);
    return RSUCCESS;
}
/*                                                                           */
int mt_get_gpio_out_base(unsigned long pin)
{
    unsigned long pos;
    unsigned long bit;
    unsigned long data;
    GPIO_REGS *reg = gpio_reg;

    pos = pin / MAX_GPIO_REG_BITS;
    bit = pin % MAX_GPIO_REG_BITS;

    data = GPIO_RD32(&reg->dout[pos].val);
    return (((data & (1L << bit)) != 0)? 1: 0);        
}
/*                                                                           */
int mt_get_gpio_in_base(unsigned long pin)
{
    unsigned long pos;
    unsigned long bit;
    unsigned long data;
    GPIO_REGS *reg = gpio_reg;

    pos = pin / MAX_GPIO_REG_BITS;
    bit = pin % MAX_GPIO_REG_BITS;

    data = GPIO_RD32(&reg->din[pos].val);
    return (((data & (1L << bit)) != 0)? 1: 0);        
}
/*                                                                           */
int mt_set_gpio_mode_base(unsigned long pin, unsigned long mode)
{
    unsigned long pos;
    unsigned long bit;
    unsigned long data;
    //                                                    
    GPIO_REGS *reg = gpio_reg;

	
    pos = pin / MAX_GPIO_MODE_PER_REG;
    bit = pin % MAX_GPIO_MODE_PER_REG;

#if 0    
    data = GPIO_RD32(&reg->mode[pos].val);
    
    data &= ~(mask << (GPIO_MODE_BITS*bit));
    data |= (mode << (GPIO_MODE_BITS*bit));
    
    GPIO_WR32(&reg->mode[pos].val, data);
#endif

    data = ((1L << (GPIO_MODE_BITS*bit)) << 3) | (mode << (GPIO_MODE_BITS*bit));

    GPIO_WR32(&reg->mode[pos]._align1, data);
	
    return RSUCCESS;
}
/*                                                                           */
int mt_get_gpio_mode_base(unsigned long pin)
{
    unsigned long pos;
    unsigned long bit;
    unsigned long data;
    unsigned long mask = (1L << GPIO_MODE_BITS) - 1;    
    GPIO_REGS *reg = gpio_reg;

	
    pos = pin / MAX_GPIO_MODE_PER_REG;
    bit = pin % MAX_GPIO_MODE_PER_REG;
    
    data = GPIO_RD32(&reg->mode[pos].val);
    
    return ((data >> (GPIO_MODE_BITS*bit)) & mask);
	
}
/*                                                                           */
void fill_addr_reg_array(PIN_addr *addr, PIN_addr_t *addr_t)
{
    unsigned long i;

    for (i = 0; i < MT_GPIO_BASE_MAX; i++) {
	if (strcmp(addr_t->s1,"GPIO_BASE")==0)
		addr->addr = GPIO_BASE_1 + addr_t->offset;
	else if (strcmp(addr_t->s1,"IOCFG_L_BASE")==0)
		addr->addr = IOCFG_L_BASE_1 + addr_t->offset;
	else if (strcmp(addr_t->s1,"IOCFG_B_BASE")==0)
		addr->addr = IOCFG_B_BASE_1 + addr_t->offset;
	else if (strcmp(addr_t->s1,"IOCFG_R_BASE")==0)
		addr->addr = IOCFG_R_BASE_1 + addr_t->offset;
	else if (strcmp(addr_t->s1,"IOCFG_T_BASE")==0)
		addr->addr = IOCFG_T_BASE_1 + addr_t->offset;
	else if (strcmp(addr_t->s1,"MIPI_TX0_BASE")==0)
		addr->addr = MIPI_TX0_BASE_1 + addr_t->offset;
	else if (strcmp(addr_t->s1,"MIPI_RX_ANA_CSI0_BASE")==0)
		addr->addr = MIPI_RX_ANA_CSI0_BASE_1 + addr_t->offset;
	else if (strcmp(addr_t->s1,"MIPI_RX_ANA_CSI1_BASE")==0)
		addr->addr = MIPI_RX_ANA_CSI1_BASE_1 + addr_t->offset;
	else
		addr->addr = 0;

	//                                                                              

	addr += 1;
	addr_t += 1;
    }
    //             
}
/*                                                                           */
void get_gpio_vbase(struct device_node *node)
{
    /*                    */
    gpio_vbase.gpio_regs = of_iomap(node, 0);
    GPIOLOG("gpio_vbase.gpio_regs=0x%p\n", gpio_vbase.gpio_regs);

    gpio_reg = (GPIO_REGS*)(GPIO_BASE_1);
    
    //                                                        
    spin_lock_init(&mtk_gpio_lock);
}
/*                                                                           */
void get_io_cfg_vbase(void)
{
    struct device_node *node = NULL;
    //                
    
    node = of_find_compatible_node(NULL, NULL, "mediatek,IOCFG_L");
    if(node){
	/*                    */
	gpio_vbase.IOCFG_L_regs = of_iomap(node, 0);
	//                                                                    
    }
    
    node = of_find_compatible_node(NULL, NULL, "mediatek,IOCFG_B");
    if(node){
	/*                    */
	gpio_vbase.IOCFG_B_regs = of_iomap(node, 0);
	//                                                                    
    }  
 
    node = of_find_compatible_node(NULL, NULL, "mediatek,IOCFG_R");
    if(node){
	/*                    */
	gpio_vbase.IOCFG_R_regs = of_iomap(node, 0);
	//                                                                    
    }    

    node = of_find_compatible_node(NULL, NULL, "mediatek,IOCFG_T");
    if(node){
	/*                    */
	gpio_vbase.IOCFG_T_regs = of_iomap(node, 0);
	//                                                                    
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,MIPI_TX0");
    if(node){
	/*                    */
	gpio_vbase.MIPI_TX0_regs = of_iomap(node, 0);
	//                                                                      
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,MIPI_RX_ANA_CSI0");
    if(node){
	/*                    */
	gpio_vbase.MIPI_RX_CSI0_regs = of_iomap(node, 0);
	//                                                                              
    }

    node = of_find_compatible_node(NULL, NULL, "mediatek,MIPI_RX_ANA_CSI1");
    if(node){
	/*                    */
	gpio_vbase.MIPI_RX_CSI1_regs = of_iomap(node, 0);
	//                                                                              
    }


    fill_addr_reg_array(IES_addr, IES_addr_t);
    fill_addr_reg_array(SMT_addr, SMT_addr_t);
    fill_addr_reg_array(PULLEN_addr, PULLEN_addr_t);
    fill_addr_reg_array(PULL_addr, PULL_addr_t);
    fill_addr_reg_array(PU_addr, PU_addr_t);
    fill_addr_reg_array(PD_addr, PD_addr_t);
#if 0
    for (i = 0; i < MT_GPIO_BASE_MAX; i++) {
	if (strcmp(IES_addr_t[i].s1,"GPIO_BASE")==0)
		IES_addr[i].addr = GPIO_BASE_1 + IES_addr_t[i].offset;
	else if (strcmp(IES_addr_t[i].s1,"IOCFG_L_BASE")==0)
		IES_addr[i].addr = IOCFG_L_BASE_1 + IES_addr_t[i].offset;
	else if (strcmp(IES_addr_t[i].s1,"IOCFG_B_BASE")==0)
		IES_addr[i].addr = IOCFG_B_BASE_1 + IES_addr_t[i].offset;
	else if (strcmp(IES_addr_t[i].s1,"IOCFG_R_BASE")==0)
		IES_addr[i].addr = IOCFG_R_BASE_1 + IES_addr_t[i].offset;
	else if (strcmp(IES_addr_t[i].s1,"IOCFG_T_BASE")==0)
		IES_addr[i].addr = IOCFG_T_BASE_1 + IES_addr_t[i].offset;
	else if (strcmp(IES_addr_t[i].s1,"MIPI_TX0_BASE")==0)
		IES_addr[i].addr = MIPI_TX0_BASE_1 + IES_addr_t[i].offset;
	else if (strcmp(IES_addr_t[i].s1,"MIPI_RX_ANA_CSI0_BASE")==0)
		IES_addr[i].addr = MIPI_RX_ANA_CSI0_BASE_1 + IES_addr_t[i].offset;
	else if (strcmp(IES_addr_t[i].s1,"MIPI_RX_ANA_CSI1_BASE")==0)
		IES_addr[i].addr = MIPI_RX_ANA_CSI1_BASE_1 + IES_addr_t[i].offset;
	else
		IES_addr[i].addr = 0;
    }
#endif
}
/*                                                                           */
#ifdef CONFIG_MD32_SUPPORT
/*                                                                           */
void md32_send_cust_pin_from_irq(void)
{
    ipi_status ret = BUSY;
    struct GPIO_IPI_Packet ipi_pkt;

    GPIOLOG("Enter ipi wq function to send cust pin... \n");
    ipi_pkt.touch_pin = (GPIO_CTP_EINT_PIN & ~(0x80000000));

    ret = md32_ipi_send(IPI_GPIO, &ipi_pkt, sizeof(ipi_pkt), true);
    if (ret != DONE)
        GPIOLOG("MD32 side IPI busy... %d\n", ret);

    //                                                                       
}
/*                                                                           */
void gpio_ipi_handler(int id, void *data, uint len)
{
    GPIOLOG("Enter gpio_ipi_handler... \n");
    queue_work(wq_md32_cust_pin, &work_md32_cust_pin);
}
/*                                                                           */
void md32_gpio_handle_init(void)
{
    //                                
    md32_ipi_registration(IPI_GPIO, gpio_ipi_handler, "GPIO IPI");
    wq_md32_cust_pin = create_workqueue("MD32_CUST_PIN_WQ");
    INIT_WORK(&work_md32_cust_pin,(void(*)(void))md32_send_cust_pin_from_irq);

    //                                                                
    //         
    //                         
    //                                                 
    // 
}
/*                                                                           */
#endif /*                   */
/*                                                                           */
#ifdef CONFIG_PM 
/*                                                                           */
void mt_gpio_suspend(void)
{
	/*                     */
}
/*                                                                           */
void mt_gpio_resume(void)
{
	/*                     */
}
/*                                                                           */
#endif /*         */
/*                                                                           */
