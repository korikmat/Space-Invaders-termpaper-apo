  li t0, 0xffffc000   // base address into memory mapped I/O area
  addi t1, zero, 48
  addi t6, zero, 1234
  addi t2, zero, 10
loop:
  lw   t3, 0x08(t0)
  andi t3, t3, 1
  beq  t3, zero, loop  
  sw   t1, 0x0c(t0)
  addi t1, t1, 1
  addi t2, t2, -1
  bne  t2, zero, loop
  ebreak
  