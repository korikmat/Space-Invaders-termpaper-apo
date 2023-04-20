  lui t0, 0xffffc
  ori t0, t0, 0x100

  addi t1, zero, 0
  addi t2, zero, 0

  la s0, n
  lw s0,0(s0)

cykl1:  
  slli t1, t1, 1
  ori  t1, t1, 1
  addi t2,t2,1
  sw t1, 4(t0)
  bne s0,t2, cykl1

  ebreak
.data
n:
  .word 5
