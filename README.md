# ls

Custom realization of UNIX utility ls

## Compile

```
make
```

## Usage

```
./ft_ls [-flags] [files or dirs]
```

## Flags

```
-G -- Enable colorized output
-R -- Recursively list subdirectories encountered
-U -- Use time of file creation, instead of last modification
      for sorting (-t) or long output (-l)
-a -- Include directory entries whose names begin with a dot (.)
-d -- Directories are listed as plain files
      (not searched recursively)
-f -- Output is not sorted.  This option turns on the -a option
-g -- This option is only available for compatibility with POSIX;
      it is used to display the group name in the long (-l) format
      output (the owner name is suppressed)
-l -- List in long format
-r -- Reverse the order of the sort to get reverse lexicographical
      order or the oldest entries first (or largest files last,
      if combined with sort by size)
-t -- Sort by time modified (most recently modified first) before
      sorting the operands by lexicographical order
-u -- Use time of last access, instead of last modification of the 
      file for sorting (-t) or long printing (-l)
-1 -- Force output to be one entry per line.  This is the default 
      when output is not to a terminal
```
