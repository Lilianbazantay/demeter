<img src="assets/epitech.svg" height="72px"/>

# My RPG

![Repo Size](https://img.shields.io/endpoint?url=https://gist.githubusercontent.com/Sigmanificient/91380f2b5680fe49cad0c6351863d989/raw/my_rpg_repo_size_data)

*Epitech B2 - C Graphical Programming (B-MUL-200), REN-2-1, promotion 2028*

## :wrench: <samp>INSTALLATION</samp>

> **Note**
> To ensure a consistent development environment and to simplify dependency
> management, we strongly recommend using Nix. The project is configured to
> work seamlessly with Nix, providing reproducible builds and a standardized
> development environment.

*If you haven't already, consider installing Nix by following the instructions
on* [nix installation page](https://nixos.org/download).

### :cherry_blossom: <samp>Nix</samp>

You can use the standard nix flakes commands to `clone`, `build` & `run` this
project.

```
nix run github:Sigmapitech/myrpg
```

<details>
<summary>See other possible actions</summary>

> Clone the flake
```bash
nix flake close github:Sigmapitech/myrpg
```

> Building the project
```bash
nix build github:Sigmapitech/myrpg
nix build github:Sigmapitech/myrpg#debug
nix build .#myrpg
nix build .#debug
```

> Build the CSFML in debug mode
```bash
nix build .#csfml-debug
```

> Running directly
```bash
nix run github:Sigmapitech/myrpg
nix run github:Sigmapitech/myrpg#debug
nix run .
nix run .#debug
```

> Lookup flake informations
```bash
nix flake show .
nix flake show  github:Sigmapitech/myrpg
nix flake metadata .
nix flake metadata github:Sigmapitech/myrpg
```

> Format the flake
```bash
nix fmt
```

</details>

### :paperclip: <samp>Non-nix</samp>

<kbd>0.</kbd> Install the required dependencies

Make sure to have the following dependencies available within your environment:

- The [`Coreutils`](https://www.gnu.org/software/coreutils/coreutils.html) command set, which
 *are expected to exist on every operating system*.
- [`CSFML`](https://www.sfml-dev.org/download/csfml), version >= 2.5.2, with the library headers.
- a recent version of [`Gnu make`](https://www.gnu.org/software/make/manual/make.html) ~4.x.x
- [`GCC`](https://gcc.gnu.org), preferably, version `13.x.x` along the [`GNU C Library`](https://www.gnu.org/software/libc).
- The [`GNU ar`](https://linux.die.net/man/1/ar) archive program, provided by
  [`binutils`](https://www.gnu.org/software/binutils).
- Optionally, [`tput`](https://www.gnu.org/software/termutils/manual/termutils-2.0/html_chapter/tput_1.html)
  command to support colors within the Makefile.

#### <samp>Epitest Docker</samp>

If you want to use the [epitest](https://github.com/Epitech/epitest-docker)
container provided by Epitech, you can use the following command:

```bash
docker run -it --rm -v $(pwd):/home/project -w /home/project epitechcontent/epitest-docker:latest /bin/bash
```

<kbd>I.</kbd> Clone the repository

```bash
git clone https://github.com/Sigmapitech/MyRPG.git my_rpg
cd my_rpg
```

<kbd>II.</kbd> Compile the desired program

> **Note**: you can `touch .fast` to use parralel building.

```
make
make debug
```

To see available targets, you can use a program such as [fzf-make](https://github.com/kyu08/fzf-make).

## :bookmark_tabs: <samp>DEVELOPMENT</samp>

if you are using `Nix`, you can access a devShell that you can `develop`
with the project dependencies to build and develop.

```bash
nix develop
nix develop github:Sigmapitech/myrpg
```

### <samp>Using direnv</samp>

You may load the devShell automatically using [direnv](https://direnv.net)
shell integration.

```
echo "use flake" | tee .envrc
direnv allow
```

### <samp>Recommanded programs</samp>

Here is a list of programs you might use during your development session.

- [`Valgrind`](https://valgrind.org) for instrumentation and dynamic analysis
- [`Kachegrind`](https://kcachegrind.github.io/html/Home.html), a front-end for
  `Callgrind` profile report.
- [`ltrace`](http://www.ltrace.org) to log external function call at runtime.

#### Epitech Tool

- [`cs`](https://github.com/Sigmapitech/cs) to ensure coding style compliance
- [`efc`](https://github.com/Dawoox/efc) to statically look for banned functions.
