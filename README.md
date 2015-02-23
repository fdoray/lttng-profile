# lttng-profile

A libary to help you understand in which call stacks your application spends its time, both on-cpu and off-cpu.

## Requirements (third party):

* [lttng-ust](https://github.com/lttng/lttng-ust)
* [libunwind](http://www.nongnu.org/libunwind) Configure with --enable-block-signals=false to get better performance.

## Building

```
cd lttng-profile
./bootstrap
./configure
make
sudo make install
```

## Using

```
LD_PRELOAD=liblttng-profile.so ./myapplication
```

