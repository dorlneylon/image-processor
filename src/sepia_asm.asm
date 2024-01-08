section .rodata
cf:
align 16
  dd  0.131, 0.168, 0.189, 0
  dd  0.534, 0.686, 0.769, 0
  dd  0.272, 0.349, 0.393, 0

section .text
global sepia_asm
sepia_asm:
  ; rdi - struct entry image
  ; rsi - struct output image
  ; rdx - sz
.loop:
  ; load image
  
  ; the things below could've been done in one instruction
  ; w/ vpbroadcastd but unfortunately my processor doesn't support avx5
  
  ; Set first byte of [rdi] to all parts of xmm0
  movzx eax, byte [rdi]
  cvtsi2ss xmm0, eax
  shufps xmm0, xmm0, 0x00
  
  ; Set second byte of [rdi] to all parts of xmm1
  movzx eax, byte [rdi + 1]
  cvtsi2ss xmm1, eax
  shufps xmm1, xmm1, 0x00

  ; Set third byte of [rdi] to all parts of xmm2
  movzx eax, byte [rdi + 2]
  cvtsi2ss xmm2, eax
  shufps xmm2, xmm2, 0x00

  ; load coefficients
  vmovaps xmm3, [cf]
  vmovaps xmm4, [cf + 16]
  vmovaps xmm5, [cf + 32]

  ; result
  vxorps xmm6, xmm6, xmm6

  ; multiply
  vfmadd231ps xmm6, xmm3, xmm0
  vfmadd231ps xmm6, xmm4, xmm1
  vfmadd231ps xmm6, xmm5, xmm2
  
  ; store
  cvtps2dq xmm6, xmm6         ; Convert floats to 32-bit integers
  packusdw xmm6, xmm6         ; Pack 32-bit integers into 16-bit unsigned integers
  packuswb xmm6, xmm6         ; Pack 16-bit integers into 8-bit unsigned integers

  vmovdqu [rsi], xmm6

  add rdi, 3
  add rsi, 3
  sub rdx, 3

  jnz .loop

  ret
