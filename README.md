CSV - Comma Separated Value file manipulation utility 
=====================================================

Command line clone of `cut` dedicated to CSV files.

Usage
-----

```bash
csv [OPTION] [FILE|-]
```

If FILE is absent, of equals `-`, reads from standard input.

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