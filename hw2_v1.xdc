#BT_HCI_RTS on FPGA /  emio_uart0_ctsn connect to 
set_property PACKAGE_PIN B7 [get_ports BT_ctsn]
#BT_HCI_CTS on FPGA / emio_uart0_rtsn
set_property PACKAGE_PIN B5 [get_ports BT_rtsn]

#HD_GPIO_0
set_property PACKAGE_PIN D7 [get_ports GPIO_0_tri_o[0]]
#HD_GPIO_1
set_property PACKAGE_PIN F8 [get_ports GPIO_0_tri_o[1]]
#HD_GPIO_2
set_property PACKAGE_PIN F7 [get_ports GPIO_0_tri_o[2]]
#HD_GPIO_3
set_property PACKAGE_PIN G7 [get_ports GPIO_0_tri_o[3]]
#HD_GPIO_4
set_property PACKAGE_PIN F6 [get_ports GPIO_0_tri_o[4]]
#HD_GPIO_5
set_property PACKAGE_PIN G5 [get_ports GPIO_0_tri_o[5]]
#HD_GPIO_6
set_property PACKAGE_PIN A6 [get_ports GPIO_0_tri_o[6]]
#HD_GPIO_7
set_property PACKAGE_PIN A7 [get_ports GPIO_0_tri_o[7]]

#HD_GPIO_8, ~CS
set_property PACKAGE_PIN G6 [get_ports SPI_0_0_ss_io]
#HD_GPIO_9, NC
set_property PACKAGE_PIN E6 [get_ports SPI_0_0_io0_io]
#HD_GPIO_10, SDO
set_property PACKAGE_PIN E5 [get_ports SPI_0_0_io1_io]
#HD_GPIO_11, SCK
set_property PACKAGE_PIN D6 [get_ports SPI_0_0_sck_io]

#DSI_D1_P
set_property PACKAGE_PIN E4 [get_ports IIC_0_scl_io]
#DSI_D1_N
set_property PACKAGE_PIN E3 [get_ports IIC_0_sda_io]

set_property DRIVE 8 [get_ports IIC_0_scl_io]
set_property DRIVE 8 [get_ports IIC_0_sda_io]

# Set the bank voltage for IO Bank 26 to 1.8V
set_property IOSTANDARD LVCMOS18 [get_ports -of_objects [get_iobanks 26]];

# Set the bank voltage for IO Bank 65 to 1.2V
set_property IOSTANDARD LVCMOS12 [get_ports -of_objects [get_iobanks 65]];
