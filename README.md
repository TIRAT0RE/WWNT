# WHITE WOLF NETWORK TOOLKIT


WWNT is a simple CLI-program for Linux to interact with network.
You probably need libc6-dev packcage to compile this project (on fresh Ubuntu installation compilation was broken until libc6-dev package installed).
Install it by:
~~~
sudo apt-get install libc6-dev
~~~

## Planned features
* Getting info about network devices (NICs, Wi-Fi adapters)
* Interface reloading

## Building & Running

```
git clone https://github.com/TIRAT0RE/WWNT

gcc wwnt_v2.c -o wwnt

./wwnt
```
