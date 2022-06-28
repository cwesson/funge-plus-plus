# N-Dimensional Funge

## Fingerprint 0x4e46554e ('NFUN')
The NFUN fingerprint enables higher-dimension funges.

### 4th Dimension
`A` delta <- (0,0,0,-1)

`I` delta <- if(b) (0,0,0,-1) else (0,0,0,0,1)

`V` delta <- (0,0,0,1)

### 5th Dimension
`H` delta <- (0,0,0,0,1)

`L` delta <- (0,0,0,0,-1)

`M` delta <- if(b) (0,0,0,0,-1) else (0,0,0,0,0,1)

The **-finvert-hl** flag affects `H` and `L`.

### 6th Dimension
`C` delta <- (0,0,0,0,0,-1)

`D` delta <- (0,0,0,0,0,1)

`R` delta <- if(b) (0,0,0,0,0,-1) else (0,0,0,0,0,0,1)

### Nth Dimension
`X` delta <- if(b) N- else N+

`Y` delta <- N- (BeQunge compatible)

`Z` delta <- N+ (BeQunge compatible)
