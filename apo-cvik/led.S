  lui t0, 0xffffc
  ori t0, t0, 0x100

  addi t1, zero, 5
  mv t3, t2

  addi t2, zero, 1
  slli t2, t2, 31

loop:
  sw t1, 4(t0)
  slli t1, t1, 1
  bleu t1, t2, loop
  sw t1, 4(t0)

loop2:
  sw t1, 4(t0)
  srli t1, t1, 1
  bne t1, t3, loop2
 
  ebreak