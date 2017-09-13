2008

#About
Parse date strings with strptime and print result with strftime

#Usage: 
```

strpftime:Parse date strings with strptime and print result with strftime
usage: strpftime -i <input strftime format> -o <output strptime format> -l <read that many chars on each line>
     -i: input format (check man strftime)
     -i: output format (check man strptime)
     -l: input format length in bytes. Must be exact
     -f: input format length in fields, space separated. May be used instead of -l
     -F: skip fields from start of line
     -t: truncate output to -l value (just output dates)
     -r: repeat original date on output
     -d: show some debugging info

```


#Examples:

```
Examples:
 cat logfile | strpftime  -i "%Y-%m-%d %H:%M:%S"  -o "%d %b %Y %H:%M" -l 20 -t
```

Convert HTTP Last-Modified to unix epoch:
```
$ echo "Sat, 20 Nov 2004 20:16:24" | strpftime -i "%a, %d %b %Y %H:%M:%S" -o "%s" -f 5
1100981784
```

