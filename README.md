CSV - [Comma Separated Value](https://tools.ietf.org/html/rfc4180) file manipulation utility
============================================================================================

Command line clone of `cut` dedicated to [CSV](https://tools.ietf.org/html/rfc4180) files.

Usage
-----

```bash
csv [OPTION] [FILE|-]
```

If FILE is absent, or is equal to `-`, reads from standard input.

Options
-------

Options    | Remarks
-----------|-----------------------------------------------
-f,--field | Specify all field to output, first starts at 1
-h,--help  | inline documentation

Example
-------

### Outputs few column of a CSV file

```bash
csv -f 1,5,8,42 file.csv
```

### Use the output of a command with pipe

```bash
fun_stuff | csv -f 3,5,42
```

Installation
------------

### Building instruction

```bash
mkdir build
cd build
cmake ..
```

Or, quicker :

```bash
./build.sh
```

To test if it works :

```bash
./test.sh
```

### Installation instruction

Once build, run the following commands as root:

```bash
cd build
make install
```

Or

```bash
cd build
sudo make install
```

Limitations
-----------

Follow the [RFC 4180](https://tools.ietf.org/html/rfc4180) by default.
Further release may allow to change default separator character, in order to use a semi colon as an example.

In order to operate as fast as possible, the current implementation limits to 256 the number for fields that can be handled in the source stream.
Further release may be more flexible and self scales to the number of columns in the source stream.

License
-------

Copyright ⓒ2019, Guillaume Wallet <wallet.guillaume@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the [GNU Lesser General Public License](https://www.gnu.org/licenses/lgpl.html) for more details.
