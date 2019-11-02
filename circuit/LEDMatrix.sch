EESchema Schematic File Version 4
LIBS:LEDMatrix-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "LED Matrix BLE Controller"
Date "2019-10-18"
Rev "MK1-V0.1-B1"
Comp ""
Comment1 "Author: Li Wei"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_ST_STM32F1:STM32F103C8Tx U2
U 1 1 5DA943F2
P 5850 4900
F 0 "U2" H 5300 6400 50  0000 C CNN
F 1 "STM32F103C8Tx" H 5900 5750 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 5250 3500 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00161566.pdf" H 5850 4900 50  0001 C CNN
	1    5850 4900
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:AMS1117-3.3 U1
U 1 1 5DA94EC5
P 7350 1300
F 0 "U1" H 7200 1050 50  0000 C CNN
F 1 "AMS1117-3.3" H 7350 1451 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 7350 1500 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 7450 1050 50  0001 C CNN
F 4 "C6186" H 7350 1300 50  0001 C CNN "JLC_MODEL"
	1    7350 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C1
U 1 1 5DA97B77
P 6850 1550
F 0 "C1" H 6900 1650 50  0000 L CNN
F 1 "104" H 6900 1450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6888 1400 50  0001 C CNN
F 3 "~" H 6850 1550 50  0001 C CNN
	1    6850 1550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR0102
U 1 1 5DA9B3AE
P 8500 1300
F 0 "#PWR0102" H 8500 1150 50  0001 C CNN
F 1 "+3.3V" V 8515 1428 50  0000 L CNN
F 2 "" H 8500 1300 50  0001 C CNN
F 3 "" H 8500 1300 50  0001 C CNN
	1    8500 1300
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 5DAA011B
P 8050 4300
F 0 "R1" H 7800 4350 50  0000 L CNN
F 1 "10k" H 7800 4250 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" V 7980 4300 50  0001 C CNN
F 3 "~" H 8050 4300 50  0001 C CNN
	1    8050 4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 4450 8050 4550
Wire Wire Line
	8050 4550 8400 4550
$Comp
L power:+3.3V #PWR01
U 1 1 5DAA0E11
P 8050 3650
F 0 "#PWR01" H 8050 3500 50  0001 C CNN
F 1 "+3.3V" H 8065 3823 50  0000 C CNN
F 2 "" H 8050 3650 50  0001 C CNN
F 3 "" H 8050 3650 50  0001 C CNN
	1    8050 3650
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C5
U 1 1 5DAA189E
P 9100 4100
F 0 "C5" V 8871 4100 50  0000 C CNN
F 1 "104" V 8962 4100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 9100 4100 50  0001 C CNN
F 3 "~" H 9100 4100 50  0001 C CNN
	1    9100 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	9000 4100 8900 4100
Wire Wire Line
	8900 4100 8900 4250
$Comp
L power:GND #PWR05
U 1 1 5DAA3424
P 9300 4100
F 0 "#PWR05" H 9300 3850 50  0001 C CNN
F 1 "GND" V 9305 3972 50  0000 R CNN
F 2 "" H 9300 4100 50  0001 C CNN
F 3 "" H 9300 4100 50  0001 C CNN
	1    9300 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8700 4100 8700 4250
$Comp
L Device:C_Small C4
U 1 1 5DAA3B6F
P 8500 4100
F 0 "C4" V 8729 4100 50  0000 C CNN
F 1 "104" V 8638 4100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8500 4100 50  0001 C CNN
F 3 "~" H 8500 4100 50  0001 C CNN
	1    8500 4100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8050 3650 8050 3800
Wire Wire Line
	8600 4100 8700 4100
$Comp
L power:GND #PWR02
U 1 1 5DAAB7DD
P 8300 4100
F 0 "#PWR02" H 8300 3850 50  0001 C CNN
F 1 "GND" V 8150 4100 50  0000 R CNN
F 2 "" H 8300 4100 50  0001 C CNN
F 3 "" H 8300 4100 50  0001 C CNN
	1    8300 4100
	0    1    1    0   
$EndComp
Wire Wire Line
	8300 4100 8400 4100
Wire Wire Line
	8050 3800 8700 3800
Wire Wire Line
	8700 3800 8700 4100
Connection ~ 8050 3800
Wire Wire Line
	8050 3800 8050 4150
Connection ~ 8700 4100
Wire Wire Line
	9200 4100 9300 4100
$Comp
L power:+5V #PWR04
U 1 1 5DAAF0B8
P 8900 3650
F 0 "#PWR04" H 8900 3500 50  0001 C CNN
F 1 "+5V" H 8915 3823 50  0000 C CNN
F 2 "" H 8900 3650 50  0001 C CNN
F 3 "" H 8900 3650 50  0001 C CNN
	1    8900 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8900 3650 8900 4100
Connection ~ 8900 4100
$Comp
L power:GND #PWR03
U 1 1 5DAB43AA
P 8800 5750
F 0 "#PWR03" H 8800 5500 50  0001 C CNN
F 1 "GND" H 8700 5700 50  0000 R CNN
F 2 "" H 8800 5750 50  0001 C CNN
F 3 "" H 8800 5750 50  0001 C CNN
	1    8800 5750
	1    0    0    -1  
$EndComp
$Comp
L Logic_LevelTranslator:TXS0108EPW U3
U 1 1 5DAA3014
P 8800 4950
F 0 "U3" H 8550 5600 50  0000 C CNN
F 1 "TXS0108EPW" H 9100 4300 50  0000 C CNN
F 2 "Package_SO:TSSOP-20_4.4x6.5mm_P0.65mm" H 8800 4200 50  0001 C CNN
F 3 "www.ti.com/lit/ds/symlink/txs0108e.pdf" H 8800 4850 50  0001 C CNN
	1    8800 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8800 5650 8800 5750
Text GLabel 5150 6200 0    50   Input ~ 0
LED_GROUP2
Text GLabel 8400 4750 0    50   Input ~ 0
LED_GROUP1
Text GLabel 6450 5400 2    50   Input ~ 0
LED_GROUP1
Text GLabel 8400 4850 0    50   Input ~ 0
LED_GROUP2
NoConn ~ 8400 4950
NoConn ~ 8400 5050
NoConn ~ 8400 5150
NoConn ~ 8400 5250
NoConn ~ 8400 5350
NoConn ~ 9200 5350
NoConn ~ 9200 5250
NoConn ~ 9200 5150
NoConn ~ 9200 5050
NoConn ~ 9200 4950
$Comp
L power:GND #PWR09
U 1 1 5DAC55CA
P 9800 4850
F 0 "#PWR09" H 9800 4600 50  0001 C CNN
F 1 "GND" V 9750 4900 50  0000 C CNN
F 2 "" H 9800 4850 50  0001 C CNN
F 3 "" H 9800 4850 50  0001 C CNN
	1    9800 4850
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C8
U 1 1 5DAC81BC
P 4650 3600
F 0 "C8" V 4421 3600 50  0000 C CNN
F 1 "104" V 4512 3600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4650 3600 50  0001 C CNN
F 3 "~" H 4650 3600 50  0001 C CNN
	1    4650 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	4750 3600 4950 3600
$Comp
L power:GND #PWR011
U 1 1 5DAC922C
P 4450 3600
F 0 "#PWR011" H 4450 3350 50  0001 C CNN
F 1 "GND" V 4455 3472 50  0000 R CNN
F 2 "" H 4450 3600 50  0001 C CNN
F 3 "" H 4450 3600 50  0001 C CNN
	1    4450 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	4450 3600 4550 3600
$Comp
L Device:R_Small R3
U 1 1 5DACA288
P 4950 3250
F 0 "R3" H 5009 3296 50  0000 L CNN
F 1 "10k" H 5009 3205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4950 3250 50  0001 C CNN
F 3 "~" H 4950 3250 50  0001 C CNN
	1    4950 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 3350 4950 3600
Wire Wire Line
	4950 3000 4950 3150
$Comp
L power:+3.3V #PWR012
U 1 1 5DACC3B4
P 4950 3000
F 0 "#PWR012" H 4950 2850 50  0001 C CNN
F 1 "+3.3V" H 4965 3173 50  0000 C CNN
F 2 "" H 4950 3000 50  0001 C CNN
F 3 "" H 4950 3000 50  0001 C CNN
	1    4950 3000
	1    0    0    -1  
$EndComp
Connection ~ 4950 3600
Wire Wire Line
	4950 3600 5150 3600
NoConn ~ 5150 3800
Wire Wire Line
	5650 3400 5650 3250
Wire Wire Line
	5650 3250 5750 3250
Wire Wire Line
	6050 3250 6050 3400
Wire Wire Line
	5750 3400 5750 3250
Connection ~ 5750 3250
Wire Wire Line
	5750 3250 5850 3250
Wire Wire Line
	5850 3400 5850 3250
Connection ~ 5850 3250
Wire Wire Line
	5850 3250 5950 3250
Wire Wire Line
	5950 3250 5950 3400
Connection ~ 5950 3250
Wire Wire Line
	5950 3250 6050 3250
$Comp
L power:+3.3V #PWR014
U 1 1 5DAD3556
P 5850 3100
F 0 "#PWR014" H 5850 2950 50  0001 C CNN
F 1 "+3.3V" H 5865 3273 50  0000 C CNN
F 2 "" H 5850 3100 50  0001 C CNN
F 3 "" H 5850 3100 50  0001 C CNN
	1    5850 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 3100 5850 3250
Wire Wire Line
	5650 6400 5650 6550
Wire Wire Line
	5650 6550 5750 6550
Wire Wire Line
	5950 6550 5950 6400
Wire Wire Line
	5850 6400 5850 6550
Connection ~ 5850 6550
Wire Wire Line
	5850 6550 5950 6550
Wire Wire Line
	5750 6400 5750 6550
Connection ~ 5750 6550
Wire Wire Line
	5750 6550 5800 6550
$Comp
L power:GND #PWR013
U 1 1 5DAD76B2
P 5800 6700
F 0 "#PWR013" H 5800 6450 50  0001 C CNN
F 1 "GND" H 5805 6527 50  0000 C CNN
F 2 "" H 5800 6700 50  0001 C CNN
F 3 "" H 5800 6700 50  0001 C CNN
	1    5800 6700
	1    0    0    -1  
$EndComp
Wire Wire Line
	5800 6550 5800 6700
Connection ~ 5800 6550
Wire Wire Line
	5800 6550 5850 6550
$Comp
L Device:Crystal Y1
U 1 1 5DAD9304
P 4350 4250
F 0 "Y1" V 4304 4381 50  0000 L CNN
F 1 "8M" V 4395 4381 50  0000 L CNN
F 2 "Crystal:Crystal_SMD_5032-2Pin_5.0x3.2mm" H 4350 4250 50  0001 C CNN
F 3 "~" H 4350 4250 50  0001 C CNN
F 4 "YSX530GA 8MHZ 20PF 10PPM" V 4350 4250 50  0001 C CNN "MODEL"
F 5 "C115962" V 4350 4250 50  0001 C CNN "JLC_MODEL"
	1    4350 4250
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5DADA80A
P 3950 4250
F 0 "R2" H 4009 4296 50  0000 L CNN
F 1 "10M" H 4009 4205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3950 4250 50  0001 C CNN
F 3 "~" H 3950 4250 50  0001 C CNN
	1    3950 4250
	-1   0    0    1   
$EndComp
$Comp
L Device:C_Small C7
U 1 1 5DADADA1
P 3750 4500
F 0 "C7" V 3521 4500 50  0000 C CNN
F 1 "22pF" V 3612 4500 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3750 4500 50  0001 C CNN
F 3 "~" H 3750 4500 50  0001 C CNN
	1    3750 4500
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4350 4400 4350 4500
Wire Wire Line
	4350 4500 3950 4500
Wire Wire Line
	3950 4500 3950 4350
Wire Wire Line
	3950 4150 3950 4000
Wire Wire Line
	3950 4000 4350 4000
Wire Wire Line
	4350 4000 4350 4100
Wire Wire Line
	3950 4500 3850 4500
Connection ~ 3950 4500
$Comp
L Device:C_Small C6
U 1 1 5DAE12F1
P 3750 4000
F 0 "C6" V 3850 4000 50  0000 C CNN
F 1 "22pF" V 3950 4000 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3750 4000 50  0001 C CNN
F 3 "~" H 3750 4000 50  0001 C CNN
	1    3750 4000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3950 4000 3850 4000
Connection ~ 3950 4000
Wire Wire Line
	3650 4500 3550 4500
Wire Wire Line
	3550 4500 3550 4250
Wire Wire Line
	3550 4000 3650 4000
$Comp
L power:GND #PWR010
U 1 1 5DAE4DA2
P 3450 4250
F 0 "#PWR010" H 3450 4000 50  0001 C CNN
F 1 "GND" V 3455 4122 50  0000 R CNN
F 2 "" H 3450 4250 50  0001 C CNN
F 3 "" H 3450 4250 50  0001 C CNN
	1    3450 4250
	0    1    1    0   
$EndComp
Wire Wire Line
	3550 4250 3450 4250
Connection ~ 3550 4250
Wire Wire Line
	3550 4250 3550 4000
Wire Wire Line
	4350 4000 5150 4000
Connection ~ 4350 4000
Wire Wire Line
	4350 4500 4550 4500
Wire Wire Line
	4550 4500 4550 4100
Wire Wire Line
	4550 4100 5150 4100
Connection ~ 4350 4500
Text GLabel 6450 6000 2    50   Input ~ 0
SWDIO
Text GLabel 6450 6100 2    50   Input ~ 0
SWCLK
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 5DAF420C
P 10100 2350
F 0 "J3" H 10180 2342 50  0000 L CNN
F 1 "CONN_SWD" H 10180 2251 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 10100 2350 50  0001 C CNN
F 3 "~" H 10100 2350 50  0001 C CNN
	1    10100 2350
	1    0    0    -1  
$EndComp
Text GLabel 9900 2450 0    50   Input ~ 0
SWDIO
Text GLabel 9900 2350 0    50   Input ~ 0
SWCLK
$Comp
L power:GND #PWR015
U 1 1 5DAF589C
P 9600 2250
F 0 "#PWR015" H 9600 2000 50  0001 C CNN
F 1 "GND" V 9605 2122 50  0000 R CNN
F 2 "" H 9600 2250 50  0001 C CNN
F 3 "" H 9600 2250 50  0001 C CNN
	1    9600 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	9600 2250 9900 2250
$Comp
L power:+3.3V #PWR016
U 1 1 5DAF7FE8
P 9600 2550
F 0 "#PWR016" H 9600 2400 50  0001 C CNN
F 1 "+3.3V" V 9615 2678 50  0000 L CNN
F 2 "" H 9600 2550 50  0001 C CNN
F 3 "" H 9600 2550 50  0001 C CNN
	1    9600 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9600 2550 9900 2550
$Comp
L Device:R_Small R5
U 1 1 5DB6EC8F
P 4750 5900
F 0 "R5" V 4554 5900 50  0000 C CNN
F 1 "1k" V 4645 5900 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4750 5900 50  0001 C CNN
F 3 "~" H 4750 5900 50  0001 C CNN
	1    4750 5900
	0    1    1    0   
$EndComp
Wire Wire Line
	4850 5900 5150 5900
Wire Wire Line
	4450 5900 4650 5900
NoConn ~ 5150 4300
NoConn ~ 5150 4400
NoConn ~ 5150 4500
$Comp
L Device:C C9
U 1 1 5DB84255
P 1200 3150
F 0 "C9" H 1315 3196 50  0000 L CNN
F 1 "104" H 1315 3105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1238 3000 50  0001 C CNN
F 3 "~" H 1200 3150 50  0001 C CNN
	1    1200 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 5DB844DC
P 1650 3150
F 0 "C10" H 1765 3196 50  0000 L CNN
F 1 "104" H 1765 3105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 1688 3000 50  0001 C CNN
F 3 "~" H 1650 3150 50  0001 C CNN
	1    1650 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C11
U 1 1 5DB84D73
P 2100 3150
F 0 "C11" H 2215 3196 50  0000 L CNN
F 1 "104" H 2215 3105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2138 3000 50  0001 C CNN
F 3 "~" H 2100 3150 50  0001 C CNN
	1    2100 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 5DB85313
P 2550 3150
F 0 "C12" H 2665 3196 50  0000 L CNN
F 1 "104" H 2665 3105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 2588 3000 50  0001 C CNN
F 3 "~" H 2550 3150 50  0001 C CNN
	1    2550 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 3000 2550 2850
Wire Wire Line
	2550 2850 2100 2850
Wire Wire Line
	1200 3000 1200 2850
Wire Wire Line
	1650 3000 1650 2850
Connection ~ 1650 2850
Wire Wire Line
	1650 2850 1200 2850
Wire Wire Line
	2550 3300 2550 3450
Wire Wire Line
	2550 3450 2100 3450
Wire Wire Line
	1200 3450 1200 3300
Wire Wire Line
	1650 3300 1650 3450
Connection ~ 1650 3450
Wire Wire Line
	1650 3450 1200 3450
Wire Wire Line
	2100 3300 2100 3450
Connection ~ 2100 3450
Wire Wire Line
	2100 3450 1650 3450
Wire Wire Line
	2100 3000 2100 2850
Connection ~ 2100 2850
Wire Wire Line
	2100 2850 1650 2850
$Comp
L power:GND #PWR019
U 1 1 5DBB917D
P 1200 3550
F 0 "#PWR019" H 1200 3300 50  0001 C CNN
F 1 "GND" H 1205 3377 50  0000 C CNN
F 2 "" H 1200 3550 50  0001 C CNN
F 3 "" H 1200 3550 50  0001 C CNN
	1    1200 3550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 3550 1200 3450
Connection ~ 1200 3450
$Comp
L power:+3.3V #PWR018
U 1 1 5DBBD3FB
P 1200 2750
F 0 "#PWR018" H 1200 2600 50  0001 C CNN
F 1 "+3.3V" H 1215 2923 50  0000 C CNN
F 2 "" H 1200 2750 50  0001 C CNN
F 3 "" H 1200 2750 50  0001 C CNN
	1    1200 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 2750 1200 2850
Connection ~ 1200 2850
$Comp
L power:+3.3V #PWR017
U 1 1 5DBCE9ED
P 3950 5900
F 0 "#PWR017" H 3950 5750 50  0001 C CNN
F 1 "+3.3V" V 4050 6000 50  0000 C CNN
F 2 "" H 3950 5900 50  0001 C CNN
F 3 "" H 3950 5900 50  0001 C CNN
	1    3950 5900
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 5DBFB77B
P 10100 3000
F 0 "J2" H 10180 2992 50  0000 L CNN
F 1 "CONN_USART1" H 10180 2901 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 10100 3000 50  0001 C CNN
F 3 "~" H 10100 3000 50  0001 C CNN
	1    10100 3000
	1    0    0    -1  
$EndComp
Text GLabel 9900 3000 0    50   Input ~ 0
USART1_TX
Text GLabel 9900 3100 0    50   Input ~ 0
USART1_RX
$Comp
L power:GND #PWR0104
U 1 1 5DBFB787
P 9450 2900
F 0 "#PWR0104" H 9450 2650 50  0001 C CNN
F 1 "GND" V 9455 2772 50  0000 R CNN
F 2 "" H 9450 2900 50  0001 C CNN
F 3 "" H 9450 2900 50  0001 C CNN
	1    9450 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	9450 2900 9900 2900
$Comp
L power:+3.3V #PWR0106
U 1 1 5DBFB792
P 9450 3200
F 0 "#PWR0106" H 9450 3050 50  0001 C CNN
F 1 "+3.3V" V 9465 3328 50  0000 L CNN
F 2 "" H 9450 3200 50  0001 C CNN
F 3 "" H 9450 3200 50  0001 C CNN
	1    9450 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9450 3200 9900 3200
Text GLabel 6450 5700 2    50   Input ~ 0
USART1_RX
Text GLabel 6450 5600 2    50   Input ~ 0
USART1_TX
Text GLabel 6450 4900 2    50   Input ~ 0
USART2_TX
Text GLabel 6450 5000 2    50   Input ~ 0
USART2_RX
NoConn ~ 6450 5200
NoConn ~ 6450 5500
NoConn ~ 6450 5800
NoConn ~ 6450 5900
NoConn ~ 6450 6200
NoConn ~ 5150 6000
NoConn ~ 5150 6100
NoConn ~ 5150 5800
NoConn ~ 5150 5700
NoConn ~ 5150 5600
NoConn ~ 5150 5400
NoConn ~ 5150 5500
NoConn ~ 5150 5300
NoConn ~ 5150 5200
NoConn ~ 5150 5100
Text GLabel 6450 5100 2    50   Input ~ 0
BLE_STAT
NoConn ~ 6450 4800
NoConn ~ 6450 4700
NoConn ~ 5150 4800
NoConn ~ 5150 4900
NoConn ~ 5150 5000
Text GLabel 2550 5850 2    50   Input ~ 0
USART2_RX
Text GLabel 2550 5950 2    50   Input ~ 0
USART2_TX
$Comp
L power:+3.3V #PWR0107
U 1 1 5DC6E589
P 1050 4700
F 0 "#PWR0107" H 1050 4550 50  0001 C CNN
F 1 "+3.3V" H 950 4900 50  0000 L CNN
F 2 "" H 1050 4700 50  0001 C CNN
F 3 "" H 1050 4700 50  0001 C CNN
	1    1050 4700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 5DC735FC
P 1050 6450
F 0 "#PWR0108" H 1050 6200 50  0001 C CNN
F 1 "GND" H 1055 6277 50  0000 C CNN
F 2 "" H 1050 6450 50  0001 C CNN
F 3 "" H 1050 6450 50  0001 C CNN
	1    1050 6450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J1
U 1 1 5DCDA574
P 10100 4750
F 0 "J1" H 10180 4792 50  0000 L CNN
F 1 "LED_PORT1" H 10180 4701 50  0000 L CNN
F 2 "LEDMatrix:TerminalBlock_JL301-5.00-3P" H 10100 4750 50  0001 C CNN
F 3 "~" H 10100 4750 50  0001 C CNN
	1    10100 4750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Screw_Terminal_01x03 J5
U 1 1 5DCDBF9E
P 10100 5150
F 0 "J5" H 10180 5192 50  0000 L CNN
F 1 "LED_PORT2" H 10180 5101 50  0000 L CNN
F 2 "LEDMatrix:TerminalBlock_JL301-5.00-3P" H 10100 5150 50  0001 C CNN
F 3 "~" H 10100 5150 50  0001 C CNN
	1    10100 5150
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 4850 9900 4850
Wire Wire Line
	9800 4650 9900 4650
Wire Wire Line
	9800 5050 9900 5050
$Comp
L power:GND #PWR08
U 1 1 5DCF5DE3
P 9800 5250
F 0 "#PWR08" H 9800 5000 50  0001 C CNN
F 1 "GND" V 9750 5300 50  0000 C CNN
F 2 "" H 9800 5250 50  0001 C CNN
F 3 "" H 9800 5250 50  0001 C CNN
	1    9800 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	9800 5250 9900 5250
Wire Wire Line
	9900 5150 9600 5150
$Comp
L LedMatrix-Symbols:XL1509-5.0E1 U5
U 1 1 5DAC1589
P 4300 1400
F 0 "U5" H 4000 1650 50  0000 L CNN
F 1 "XL1509-5.0E1" H 4350 1650 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 4300 650 50  0001 C CNN
F 3 "" H 4300 1400 50  0001 C CNN
F 4 "C61063" H 4300 1400 50  0001 C CNN "JLC_MODEL"
	1    4300 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C14
U 1 1 5DAEF101
P 3600 1550
F 0 "C14" H 3715 1596 50  0000 L CNN
F 1 "104" H 3715 1505 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3638 1400 50  0001 C CNN
F 3 "~" H 3600 1550 50  0001 C CNN
	1    3600 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 1400 3600 1300
Wire Wire Line
	3600 1300 3900 1300
Wire Wire Line
	3600 1300 3300 1300
Wire Wire Line
	3300 1300 3300 1400
Connection ~ 3600 1300
Wire Wire Line
	3300 1700 3300 1800
Wire Wire Line
	3300 1800 3600 1800
Wire Wire Line
	4100 1800 4100 1700
Wire Wire Line
	3600 1700 3600 1800
Connection ~ 3600 1800
Wire Wire Line
	3600 1800 4100 1800
$Comp
L power:+12V #PWR020
U 1 1 5DAFFD6D
P 3300 1100
F 0 "#PWR020" H 3300 950 50  0001 C CNN
F 1 "+12V" H 3200 1300 50  0000 L CNN
F 2 "" H 3300 1100 50  0001 C CNN
F 3 "" H 3300 1100 50  0001 C CNN
	1    3300 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 1100 3300 1300
Connection ~ 3300 1300
$Comp
L power:GND #PWR021
U 1 1 5DB04991
P 3300 1900
F 0 "#PWR021" H 3300 1650 50  0001 C CNN
F 1 "GND" H 3305 1727 50  0000 C CNN
F 2 "" H 3300 1900 50  0001 C CNN
F 3 "" H 3300 1900 50  0001 C CNN
	1    3300 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 1900 3300 1800
Connection ~ 3300 1800
Wire Wire Line
	4100 1800 4200 1800
Wire Wire Line
	4550 1800 4550 1700
Connection ~ 4100 1800
Wire Wire Line
	4400 1700 4400 1800
Connection ~ 4400 1800
Wire Wire Line
	4400 1800 4550 1800
Wire Wire Line
	4300 1700 4300 1800
Connection ~ 4300 1800
Wire Wire Line
	4300 1800 4400 1800
Wire Wire Line
	4200 1700 4200 1800
Connection ~ 4200 1800
Wire Wire Line
	4200 1800 4300 1800
$Comp
L Device:D_Schottky D2
U 1 1 5DB1D587
P 4900 1550
F 0 "D2" V 4854 1629 50  0000 L CNN
F 1 "SS14" V 4945 1629 50  0000 L CNN
F 2 "Diode_SMD:D_SMA" H 4900 1550 50  0001 C CNN
F 3 "~" H 4900 1550 50  0001 C CNN
	1    4900 1550
	0    1    1    0   
$EndComp
Wire Wire Line
	4750 1300 4900 1300
Wire Wire Line
	4900 1300 4900 1400
Wire Wire Line
	4900 1700 4900 1800
Wire Wire Line
	4900 1800 4550 1800
Connection ~ 4550 1800
$Comp
L pspice:INDUCTOR L1
U 1 1 5DB28BAF
P 5300 1300
F 0 "L1" H 5300 1400 50  0000 C CNN
F 1 "68uH 500mA" H 5300 1250 50  0000 C CNN
F 2 "Inductor_SMD:L_Taiyo-Yuden_NR-40xx_HandSoldering" H 5300 1300 50  0001 C CNN
F 3 "~" H 5300 1300 50  0001 C CNN
	1    5300 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1300 5050 1300
Connection ~ 4900 1300
Wire Wire Line
	5550 1300 5700 1300
Wire Wire Line
	5700 1300 5700 1400
Wire Wire Line
	5700 1700 5700 1800
Wire Wire Line
	5700 1800 4900 1800
Connection ~ 4900 1800
Connection ~ 5700 1300
Text GLabel 2550 4750 2    50   Input ~ 0
BLE_STAT
Wire Wire Line
	5700 1300 5700 1000
Wire Wire Line
	5700 1000 4300 1000
Wire Wire Line
	4300 1000 4300 1100
$Comp
L Connector:Screw_Terminal_01x02 J6
U 1 1 5DB5D4B1
P 2550 1600
F 0 "J6" H 2468 1275 50  0000 C CNN
F 1 "PWR_IN" H 2468 1366 50  0000 C CNN
F 2 "LEDMatrix:TerminalBlock_JL301-5.00-2P" H 2550 1600 50  0001 C CNN
F 3 "~" H 2550 1600 50  0001 C CNN
	1    2550 1600
	-1   0    0    1   
$EndComp
Wire Wire Line
	2750 1500 2850 1500
Wire Wire Line
	2850 1500 2850 1300
Wire Wire Line
	2850 1300 3300 1300
Wire Wire Line
	2750 1600 2850 1600
Wire Wire Line
	2850 1600 2850 1800
Wire Wire Line
	2850 1800 3300 1800
Wire Wire Line
	6050 1300 6050 1400
Wire Wire Line
	5700 1300 6050 1300
Wire Wire Line
	6050 1700 6050 1800
Wire Wire Line
	6050 1800 5700 1800
Connection ~ 5700 1800
Connection ~ 6050 1300
$Comp
L Device:CP C13
U 1 1 5DBD1739
P 3300 1550
F 0 "C13" H 2950 1600 50  0000 L CNN
F 1 "100uF" H 2950 1500 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_8x10" H 3338 1400 50  0001 C CNN
F 3 "~" H 3300 1550 50  0001 C CNN
F 4 "VUA101M1ETR-0810K" H 3300 1550 50  0001 C CNN "MODEL"
F 5 "C134507" H 3300 1550 50  0001 C CNN "JLC_MODEL"
	1    3300 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C15
U 1 1 5DBD79FD
P 5700 1550
F 0 "C15" H 5350 1600 50  0000 L CNN
F 1 "100uF" H 5350 1500 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_8x10" H 5738 1400 50  0001 C CNN
F 3 "~" H 5700 1550 50  0001 C CNN
F 4 "VUA101M1ETR-0810K" H 5700 1550 50  0001 C CNN "MODEL"
F 5 "C134507" H 5700 1550 50  0001 C CNN "JLC_MODEL"
	1    5700 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C16
U 1 1 5DBD850E
P 6050 1550
F 0 "C16" H 6150 1600 50  0000 L CNN
F 1 "100uF" H 6150 1500 50  0000 L CNN
F 2 "Capacitor_SMD:CP_Elec_8x10" H 6088 1400 50  0001 C CNN
F 3 "~" H 6050 1550 50  0001 C CNN
F 4 "VUA101M1ETR-0810K" H 6050 1550 50  0001 C CNN "MODEL"
F 5 "C134507" H 6050 1550 50  0001 C CNN "JLC_MODEL"
	1    6050 1550
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0109
U 1 1 5DB3CD3D
P 6050 1100
F 0 "#PWR0109" H 6050 950 50  0001 C CNN
F 1 "+5V" H 6000 1300 50  0000 L CNN
F 2 "" H 6050 1100 50  0001 C CNN
F 3 "" H 6050 1100 50  0001 C CNN
	1    6050 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 1100 6050 1300
Wire Wire Line
	6050 1300 6500 1300
Connection ~ 6050 1800
Wire Wire Line
	6850 1700 6850 1800
Connection ~ 6850 1800
Wire Wire Line
	6850 1800 6500 1800
Wire Wire Line
	6850 1300 6850 1400
Connection ~ 6850 1300
Wire Wire Line
	6850 1300 7050 1300
Wire Wire Line
	7350 1600 7350 1800
Connection ~ 7350 1800
Wire Wire Line
	7350 1800 6850 1800
Connection ~ 8300 1300
Wire Wire Line
	8300 1300 8300 1450
$Comp
L power:GND #PWR0105
U 1 1 5DB6674D
P 8300 2150
F 0 "#PWR0105" H 8300 1900 50  0001 C CNN
F 1 "GND" H 8305 1977 50  0000 C CNN
F 2 "" H 8300 2150 50  0001 C CNN
F 3 "" H 8300 2150 50  0001 C CNN
	1    8300 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R4
U 1 1 5DB17C2B
P 8300 1950
F 0 "R4" H 8359 1996 50  0000 L CNN
F 1 "1k" H 8359 1905 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 8300 1950 50  0001 C CNN
F 3 "~" H 8300 1950 50  0001 C CNN
	1    8300 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5DB1176E
P 8300 1600
F 0 "D1" V 8339 1483 50  0000 R CNN
F 1 "LED" V 8248 1483 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric" H 8300 1600 50  0001 C CNN
F 3 "~" H 8300 1600 50  0001 C CNN
F 4 "19-217/GHC-YR1S2/3T " V 8300 1600 50  0001 C CNN "Model"
	1    8300 1600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8300 2050 8300 2150
Wire Wire Line
	8300 1750 8300 1850
Wire Wire Line
	7850 1800 7350 1800
Wire Wire Line
	7850 1300 8300 1300
Connection ~ 7850 1300
Wire Wire Line
	7650 1300 7850 1300
Wire Wire Line
	7850 1700 7850 1800
Wire Wire Line
	7850 1300 7850 1400
$Comp
L Device:CP C3
U 1 1 5DBD939B
P 7850 1550
F 0 "C3" H 7500 1500 50  0000 L CNN
F 1 "100uF" H 7500 1400 50  0000 L CNN
F 2 "Capacitor_Tantalum_SMD:CP_EIA-3528-21_Kemet-B" H 7888 1400 50  0001 C CNN
F 3 "~" H 7850 1550 50  0001 C CNN
F 4 "VUA101M1ETR-0810K" H 7850 1550 50  0001 C CNN "MODEL"
F 5 "TAJB107K006RNJ" H 7850 1550 50  0001 C CNN "JLC_MODEL"
	1    7850 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D3
U 1 1 5DCCFE52
P 4300 5900
F 0 "D3" H 4400 5800 50  0000 R CNN
F 1 "RED" H 4400 6050 50  0000 R CNN
F 2 "Diode_SMD:D_0603_1608Metric" H 4300 5900 50  0001 C CNN
F 3 "~" H 4300 5900 50  0001 C CNN
F 4 "" V 4300 5900 50  0001 C CNN "Model"
	1    4300 5900
	-1   0    0    1   
$EndComp
Wire Wire Line
	3950 5900 4150 5900
$Comp
L Device:C C2
U 1 1 5DD10559
P 6500 1550
F 0 "C2" H 6550 1650 50  0000 L CNN
F 1 "106" H 6550 1450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6538 1400 50  0001 C CNN
F 3 "~" H 6500 1550 50  0001 C CNN
F 4 "C19702" H 6500 1550 50  0001 C CNN "JLC_MODEL"
	1    6500 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 1400 6500 1300
Wire Wire Line
	6500 1300 6850 1300
Wire Wire Line
	6500 1700 6500 1800
Wire Wire Line
	6500 1800 6050 1800
Wire Wire Line
	8300 1300 8500 1300
Connection ~ 6500 1800
Connection ~ 6500 1300
$Comp
L power:+12V #PWR0101
U 1 1 5DD679FA
P 9800 4650
F 0 "#PWR0101" H 9800 4500 50  0001 C CNN
F 1 "+12V" V 9900 4650 50  0000 L CNN
F 2 "" H 9800 4650 50  0001 C CNN
F 3 "" H 9800 4650 50  0001 C CNN
	1    9800 4650
	0    -1   -1   0   
$EndComp
$Comp
L power:+12V #PWR0103
U 1 1 5DD68592
P 9800 5050
F 0 "#PWR0103" H 9800 4900 50  0001 C CNN
F 1 "+12V" V 9850 4900 50  0000 L CNN
F 2 "" H 9800 5050 50  0001 C CNN
F 3 "" H 9800 5050 50  0001 C CNN
	1    9800 5050
	0    -1   -1   0   
$EndComp
$Comp
L Device:C C17
U 1 1 5DD7115A
P 3000 3150
F 0 "C17" H 3115 3196 50  0000 L CNN
F 1 "104" H 3115 3105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3038 3000 50  0001 C CNN
F 3 "~" H 3000 3150 50  0001 C CNN
	1    3000 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 3300 3000 3450
Wire Wire Line
	3000 3450 2550 3450
Connection ~ 2550 3450
Wire Wire Line
	2550 2850 3000 2850
Wire Wire Line
	3000 2850 3000 3000
Connection ~ 2550 2850
$Comp
L LedMatrix-Symbols:JDY-08 U4
U 1 1 5DAC26C9
P 1850 5550
F 0 "U4" H 1850 6637 60  0000 C CNN
F 1 "JDY-08" H 1850 6531 60  0000 C CNN
F 2 "LEDMatrix:JDY-08_HandSoldering" H 3700 5450 60  0001 C CNN
F 3 "https://github.com/kichMan/JDY-08" H 3700 5450 60  0001 C CNN
	1    1850 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1050 4700 1050 4800
Wire Wire Line
	1050 4800 1150 4800
Wire Wire Line
	1050 6450 1050 6350
Wire Wire Line
	1050 6350 1150 6350
Text GLabel 1150 5300 0    50   Input ~ 0
BLE_PWRC
Text GLabel 1150 5650 0    50   Input ~ 0
BLE_ATCMD
NoConn ~ 2550 4850
NoConn ~ 2550 4950
NoConn ~ 2550 5050
NoConn ~ 2550 5150
NoConn ~ 2550 5250
NoConn ~ 2550 5350
NoConn ~ 2550 5450
NoConn ~ 2550 5550
NoConn ~ 2550 5650
NoConn ~ 2550 5750
NoConn ~ 2550 6050
NoConn ~ 2550 6150
NoConn ~ 2550 6250
NoConn ~ 2550 6350
NoConn ~ 1150 5150
Text GLabel 6450 5300 2    50   Input ~ 0
BLE_ATCMD
Text GLabel 5150 4700 0    50   Input ~ 0
BLE_PWRC
Text Label 9200 4750 0    50   ~ 0
LED_DATA1
Text Label 9200 4850 0    50   ~ 0
LED_DATA2
Wire Wire Line
	9200 4750 9900 4750
Wire Wire Line
	9600 4850 9200 4850
Wire Wire Line
	9600 4850 9600 5150
NoConn ~ 8400 4650
NoConn ~ 9200 4650
$Comp
L Mechanical:MountingHole_Pad H1
U 1 1 5DACD529
P 9900 950
F 0 "H1" V 9854 1100 50  0000 L CNN
F 1 "MountingHole_Pad" V 9945 1100 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 9900 950 50  0001 C CNN
F 3 "~" H 9900 950 50  0001 C CNN
	1    9900 950 
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H2
U 1 1 5DACE0AC
P 9900 1550
F 0 "H2" V 9854 1700 50  0000 L CNN
F 1 "MountingHole_Pad" V 9945 1700 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 9900 1550 50  0001 C CNN
F 3 "~" H 9900 1550 50  0001 C CNN
	1    9900 1550
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H3
U 1 1 5DACE2ED
P 9900 1150
F 0 "H3" V 9854 1300 50  0000 L CNN
F 1 "MountingHole_Pad" V 9945 1300 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 9900 1150 50  0001 C CNN
F 3 "~" H 9900 1150 50  0001 C CNN
	1    9900 1150
	0    1    1    0   
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 5DACE55B
P 9900 1350
F 0 "H4" V 9854 1500 50  0000 L CNN
F 1 "MountingHole_Pad" V 9945 1500 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 9900 1350 50  0001 C CNN
F 3 "~" H 9900 1350 50  0001 C CNN
	1    9900 1350
	0    1    1    0   
$EndComp
Wire Wire Line
	9800 950  9700 950 
Wire Wire Line
	9700 950  9700 1150
Wire Wire Line
	9800 1350 9700 1350
Connection ~ 9700 1350
Wire Wire Line
	9800 1150 9700 1150
Connection ~ 9700 1150
Wire Wire Line
	9700 1150 9700 1350
$Comp
L power:GND #PWR06
U 1 1 5DAE4B96
P 9700 1650
F 0 "#PWR06" H 9700 1400 50  0001 C CNN
F 1 "GND" H 9705 1477 50  0000 C CNN
F 2 "" H 9700 1650 50  0001 C CNN
F 3 "" H 9700 1650 50  0001 C CNN
	1    9700 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	9700 1350 9700 1650
NoConn ~ 9800 1550
$EndSCHEMATC
