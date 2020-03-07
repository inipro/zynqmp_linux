#BT_HCI_RTS on FPGA /  emio_uart0_ctsn connect to 
set_property PACKAGE_PIN B7 [get_ports BT_ctsn]
#BT_HCI_CTS on FPGA / emio_uart0_rtsn
set_property PACKAGE_PIN B5 [get_ports BT_rtsn]

#HD_GPIO_0
set_property PACKAGE_PIN G7 [get_ports rtsn] 
#HD_GPIO_1
set_property PACKAGE_PIN F7 [get_ports rxd] 
#HD_GPIO_2
set_property PACKAGE_PIN F8 [get_ports txd]
#HD_GPIO_3
set_property PACKAGE_PIN D7 [get_ports ctsn]


# Set the bank voltage for IO Bank 26 to 1.8V
set_property IOSTANDARD LVCMOS18 [get_ports -of_objects [get_iobanks 26]];
