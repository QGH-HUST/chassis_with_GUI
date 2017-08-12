#! /bin/bash
echo xiaopohaier174 | sudo -S /etc/init.d/ethercat restart

cd /opt/etherlab/bin

#estun_servo_pdo_config slave 0 

./ethercat download -t int8  -p 0 0x1c12 0 0
./ethercat download -t int8  -p 0 0x1c13 0 0

./ethercat download -t int8  -p 0 0x1600 0 0
./ethercat download -t int8  -p 0 0x1a00 0 0

./ethercat download -t int32 -p 0 0x1600 3 0x60600008
./ethercat download -t int32 -p 0 0x1600 4 0x607a0020
./ethercat download -t int32 -p 0 0x1600 5 0x60810020
./ethercat download -t int32 -p 0 0x1600 6 0x60820020
./ethercat download -t int32 -p 0 0x1600 7 0x60830020
./ethercat download -t int32 -p 0 0x1600 8 0x60840020

./ethercat download -t int32 -p 0 0x1a00 3 0x60610008
./ethercat download -t int32 -p 0 0x1a00 4 0x60640020

./ethercat download -t int8  -p 0 0x1600 0 8
./ethercat download -t int8  -p 0 0x1a00 0 4

./ethercat download -t int8  -p 0 0x1c12 0 1
./ethercat download -t int8  -p 0 0x1c13 0 1

#estun_servo_pdo_config slave 1 

./ethercat download -t int8  -p 1 0x1c12 0 0
./ethercat download -t int8  -p 1 0x1c13 0 0

./ethercat download -t int8  -p 1 0x1600 0 0
./ethercat download -t int8  -p 1 0x1a00 0 0

./ethercat download -t int32 -p 1 0x1600 3 0x60600008
./ethercat download -t int32 -p 1 0x1600 4 0x607a0020
./ethercat download -t int32 -p 1 0x1600 5 0x60810020
./ethercat download -t int32 -p 1 0x1600 6 0x60820020
./ethercat download -t int32 -p 1 0x1600 7 0x60830020
./ethercat download -t int32 -p 1 0x1600 8 0x60840020

./ethercat download -t int32 -p 1 0x1a00 3 0x60610008
./ethercat download -t int32 -p 1 0x1a00 4 0x60640020

./ethercat download -t int8  -p 1 0x1600 0 8
./ethercat download -t int8  -p 1 0x1a00 0 4

./ethercat download -t int8  -p 1 0x1c12 0 1
./ethercat download -t int8  -p 1 0x1c13 0 1

sudo /etc/init.d/ethercat restart
