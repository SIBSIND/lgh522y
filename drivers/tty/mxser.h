#ifndef _MXSER_H
#define _MXSER_H

/*
                                 
 */

/*
              
 */

#define MOXA			0x400
#define MOXA_GETDATACOUNT	(MOXA + 23)
#define MOXA_DIAGNOSE		(MOXA + 50)
#define MOXA_CHKPORTENABLE	(MOXA + 60)
#define MOXA_HighSpeedOn	(MOXA + 61)
#define MOXA_GET_MAJOR		(MOXA + 63)
#define MOXA_GETMSTATUS		(MOXA + 65)
#define MOXA_SET_OP_MODE	(MOXA + 66)
#define MOXA_GET_OP_MODE	(MOXA + 67)

#define RS232_MODE		0
#define RS485_2WIRE_MODE	1
#define RS422_MODE		2
#define RS485_4WIRE_MODE	3
#define OP_MODE_MASK		3

#define MOXA_SDS_RSTICOUNTER	(MOXA + 69)
#define MOXA_ASPP_OQUEUE  	(MOXA + 70)
#define MOXA_ASPP_MON     	(MOXA + 73)
#define MOXA_ASPP_LSTATUS 	(MOXA + 74)
#define MOXA_ASPP_MON_EXT 	(MOXA + 75)
#define MOXA_SET_BAUD_METHOD	(MOXA + 76)

/*                                                     */

#define NPPI_NOTIFY_PARITY	0x01
#define NPPI_NOTIFY_FRAMING	0x02
#define NPPI_NOTIFY_HW_OVERRUN	0x04
#define NPPI_NOTIFY_SW_OVERRUN	0x08
#define NPPI_NOTIFY_BREAK	0x10

#define NPPI_NOTIFY_CTSHOLD         0x01	/*                    */
#define NPPI_NOTIFY_DSRHOLD         0x02	/*                    */
#define NPPI_NOTIFY_XOFFHOLD        0x08	/*                          */
#define NPPI_NOTIFY_XOFFXENT        0x10	/*           */

/*                                        */
/* */
/*                                                        */
/*                                                         */
/*                                              */
#define MOXA_MUST_ENTER_ENCHANCE	0xBF

/*                                                           */
#define MOXA_MUST_GDL_REGISTER		0x07
#define MOXA_MUST_GDL_MASK		0x7F
#define MOXA_MUST_GDL_HAS_BAD_DATA	0x80

#define MOXA_MUST_LSR_RERR		0x80	/*                       */
/*                                                                  */
/*                                 */
#define MOXA_MUST_EFR_REGISTER		0x02
/*                      */
#define MOXA_MUST_EFR_EFRB_ENABLE	0x10
/*                                   */
#define MOXA_MUST_EFR_BANK0		0x00
#define MOXA_MUST_EFR_BANK1		0x40
#define MOXA_MUST_EFR_BANK2		0x80
#define MOXA_MUST_EFR_BANK3		0xC0
#define MOXA_MUST_EFR_BANK_MASK		0xC0

/*                                                            */
#define MOXA_MUST_XON1_REGISTER		0x04

/*                                                            */
#define MOXA_MUST_XON2_REGISTER		0x05

/*                                                             */
#define MOXA_MUST_XOFF1_REGISTER	0x06

/*                                                             */
#define MOXA_MUST_XOFF2_REGISTER	0x07

#define MOXA_MUST_RBRTL_REGISTER	0x04
#define MOXA_MUST_RBRTH_REGISTER	0x05
#define MOXA_MUST_RBRTI_REGISTER	0x06
#define MOXA_MUST_THRTL_REGISTER	0x07
#define MOXA_MUST_ENUM_REGISTER		0x04
#define MOXA_MUST_HWID_REGISTER		0x05
#define MOXA_MUST_ECR_REGISTER		0x06
#define MOXA_MUST_CSR_REGISTER		0x07

/*                       */
#define MOXA_MUST_FCR_GDA_MODE_ENABLE	0x20
/*                                */
#define MOXA_MUST_FCR_GDA_ONLY_ENABLE	0x10

/*                      */
#define MOXA_MUST_IER_ECTSI		0x80
/*                      */
#define MOXA_MUST_IER_ERTSI		0x40
/*                           */
#define MOXA_MUST_IER_XINT		0x20
/*                      */
#define MOXA_MUST_IER_EGDAI		0x10

#define MOXA_MUST_RECV_ISR		(UART_IER_RDI | MOXA_MUST_IER_EGDAI)

/*                       */
#define MOXA_MUST_IIR_GDA		0x1C
#define MOXA_MUST_IIR_RDA		0x04
#define MOXA_MUST_IIR_RTO		0x0C
#define MOXA_MUST_IIR_LSR		0x06

/*                                                 */
#define MOXA_MUST_IIR_XSC		0x10

/*                                        */
#define MOXA_MUST_IIR_RTSCTS		0x20
#define MOXA_MUST_IIR_MASK		0x3E

#define MOXA_MUST_MCR_XON_FLAG		0x40
#define MOXA_MUST_MCR_XON_ANY		0x80
#define MOXA_MUST_MCR_TX_XON		0x08

/*                                          */
#define MOXA_MUST_EFR_SF_MASK		0x0F
/*                 */
#define MOXA_MUST_EFR_SF_TX1		0x08
/*                 */
#define MOXA_MUST_EFR_SF_TX2		0x04
/*                            */
#define MOXA_MUST_EFR_SF_TX12		0x0C
/*                     */
#define MOXA_MUST_EFR_SF_TX_NO		0x00
/*                               */
#define MOXA_MUST_EFR_SF_TX_MASK	0x0C
/*                        */
#define MOXA_MUST_EFR_SF_RX_NO		0x00
/*                    */
#define MOXA_MUST_EFR_SF_RX1		0x02
/*                    */
#define MOXA_MUST_EFR_SF_RX2		0x01
/*                               */
#define MOXA_MUST_EFR_SF_RX12		0x03
/*                               */
#define MOXA_MUST_EFR_SF_RX_MASK	0x03

#endif
