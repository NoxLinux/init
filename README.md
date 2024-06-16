# Building

```bash
make -j $(nproc --all)
```
You can also use `STRIP=1` (in the environment, not the make command) to strip the output binary  
There's also CC, CFLAGS, and LDFLAGS (again, environment, not make)

