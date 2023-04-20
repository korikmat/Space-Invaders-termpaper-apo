  lui t0, 0xffffc
  ori t0, t0, 0x100

  addi t1, zero, 5

  sw t1, 4(t0)
  slli t1, t1, 1
  sw t1, 4(t0)
  slli t1, t1, 1
  sw t1, 4(t0)
  slli t1, t1, 1

  ebreak