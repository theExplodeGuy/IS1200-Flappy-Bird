# Flappy Bird on DTEK-V

This project runs a **Flappy Bird** game on the DTEK-V board using the VGA framebuffer and hardware sprite uploading.

---

## 🛠 Requirements
- DTEK-V board connected via JTAG  
- Intel FPGA tools (Quartus Programmer / `jtagd`, `jtagconfig`) installed  
- RISC-V toolchain (`/opt/riscv/bin/`) 
- `dtekv-tools` compiled and accessible (provides `dtekv-upload` and `dtekv-run`)  

---

## 🚀 Running the Game

1. **Edit the script paths**  
   Open `start.sh` (the provided bash script) and change all absolute paths to match your PC’s directory layout. For example:

   ```bash
   SPRITES="/home/<your-username>/Documents/IS1200/labs/miniproject"
   RUNMAIN="/home/<your-username>/Documents/IS1200/labs/miniproject/main.bin"
