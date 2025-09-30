#!/bin/bash
echo "Starting the script..."


export PATH=$PATH:/home/marios/intelFPGA/23.1std/qprogrammer/bin
export PATH=/opt/riscv/bin/:$PATH

SPRITES="/home/marios/Documents/IS1200/labs/miniproject"

jtagd --user-start
jtagconfig


cd /home/marios/Documents/IS1200/dtekv-tools || exit

./dtekv-upload $SPRITES/sprites/flapp32.raw   0x02025800
./dtekv-upload $SPRITES/sprites/background5.raw 0x02000000
./dtekv-upload $SPRITES/sprites/background5.raw 0x0201c200
./dtekv-upload $SPRITES/sprites/background5.raw 0x02009600
./dtekv-upload $SPRITES/sprites/background5.raw 0x02012c00
./dtekv-upload $SPRITES/sprites/gameover.raw  0x02025e40
./dtekv-upload $SPRITES/sprites/startscreen.raw  0x0203AFC0


