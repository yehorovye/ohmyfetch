# ohmyfetch
fastest system fetch.

## install
```sh
git clone https://github.com/yehorovye/ohmyfetch.git
cd ohmyfetch
```
> optionally enter nix shell

build
```sh
tcc -O2 -o ohmyfetch src/ohmyfetch.c
```

## benchmark
I use hyperfine for benchmarking
```sh
hyperfine "tinyfetch" "./ohmyfetch" -i -N --warmup 5
```

however, don't trust benchmarks unless they are ran in a silent machine.
