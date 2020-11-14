# SESO
## Description
This project is a full kernel simulator. It simulates how will behave the implemented kernel in diferent systems by changing the clock rate, the number of cores of the cpu ...

It's divided in 5 parts,
  1. System architecture
  2. Scheduler
  3. Memory management
  4. Flash disk controler
  5. Security
  
## Compilation
### LMake
If you have lmake installed in your system (https://github.com/IkerGalardi/LMake.git) execute
```
lmake build
```
If you want to print execution debuging edit the lmake.lua  and add -DDEBUG flag.
 ```
 lmake_set_compiler_flags("-pthread -Wall -Iinclude -DDEBUG")
 ```
### comp script
If you dont have lmake execute comp script 
```
sh comp
```
## Usage
You can execute it with lmake or with any other method.
to use LMake do: 
```
lmake run
```
once you executed it will ask you for the simulation parameters.
```

 $$$$$$$\  $$$$$$\   $$$$$$$\  $$$$$$\
$$  _____|$$  __$$\ $$  _____|$$  __$$\
 \$$$$$$\ $$$$$$$$ |\$$$$$$\  $$ /  $$ |
  \____$$\$$   ____| \____$$\ $$ |  $$ |
$$$$$$$  |\$$$$$$$\ $$$$$$$  |\$$$$$$  |
\_______/  \_______|\_______/  \______/

=================================================

Select clock rate (MHz): 8
Select scheduler action rate (clock ticks): 3
Select process generation rate (clock ticks): 5
Select number of cores: 8
```
