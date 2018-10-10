# COREWAR

Recode of the miythical programmig game Core War in a VM with SDL2 interface: https://en.wikipedia.org/wiki/Core_War

You will need to have installed sdl2 dependencies as well as sdl2_image and sdl2_ttf.

## Usage

### Assembler
```
make && ./asm [-a] [foo.s]
```
### Virtual Machine

```
make && ./corewar [-dump N -n N][-i -k -v -f] [foo_1.cor ... foo_n.cor]
```

### Tester script

```
sh tester.sh [-a -r -f -d]
```
-a => Test assembler.
-r => Test VM with random inputs.
-f => Test especific input of the VM.
-d => Test all combinations of inputs of the VM in a specific directory (a lot of time).

## Screenshot
![alt text](https://github.com/latiagertrutis/corewar/blob/master/images/ezgif.com-video-to-gif.gif)