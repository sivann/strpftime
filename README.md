2008

#About
Parse date strings with strptime and print result with strftime

#Usage: 
```
strpftime <input date string> <input strftime format> <output strptime format>
```


#Examples:

```
$ strpftime "2001-11-12 18:31:01"  "%Y-%m-%d %H:%M:%S"  "%d %b %Y %H:%M"
12 Nov 2001 18:31
```

Convert HTTP Last-Modified to unix epoch:
```
$ strpftime "Sat, 20 Nov 2004 20:16:24 GMT" "%a, %d %b %Y %H:%M:%S %z" "%s"
1100974584
```

