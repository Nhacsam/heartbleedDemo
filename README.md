heartbleedDemo
==============

This repo is a minimal code to explain to heartbleed bug

We will try to use some struct from the openssl code and the RFC 6520


## Installation

Istallation is very simple :
  
``  gcc -g *.c -o heartbleed ``

## Exemple of running

``$ ./heartbleed 




Hearbeat Request : 
01 1f 00 44 6f 20 6f 72 20 64 6f 20 6e 6f 74 2e |  ...Do or do not.
20 54 68 65 72 65 20 69 73 20 6e 6f 20 74 72 79 |   There is no try
20 21 00 00 00 00 00 00 00 00 00 00 00 00 00 00 |   !..............
00 00                                           |  ..




Vulnerable Hearbeat Response : 
02 1f 00 44 6f 20 6f 72 20 64 6f 20 6e 6f 74 2e |  ...Do or do not.
20 54 68 65 72 65 20 69 73 20 6e 6f 20 74 72 79 |   There is no try
20 21 41 41 41 41 41 41 41 41 41 41 41 41 41 41 |   !AAAAAAAAAAAAAA
41 41                                           |  AA




Corrected Hearbeat Response : 
02 1f 00 44 6f 20 6f 72 20 64 6f 20 6e 6f 74 2e |  ...Do or do not.
20 54 68 65 72 65 20 69 73 20 6e 6f 20 74 72 79 |   There is no try
20 21 41 41 41 41 41 41 41 41 41 41 41 41 41 41 |   !AAAAAAAAAAAAAA
41 41                                           |  AA
``

``$ ./heartbleed 




Hearbeat Request : 
01 ff 00 44 6f 20 6f 72 20 64 6f 20 6e 6f 74 2e |  ...Do or do not.
20 54 68 65 72 65 20 69 73 20 6e 6f 20 74 72 79 |   There is no try
20 21 00 00 00 00 00 00 00 00 00 00 00 00 00 00 |   !..............
00 00                                           |  ..




Vulnerable Hearbeat Response : 
02 ff 00 44 6f 20 6f 72 20 64 6f 20 6e 6f 74 2e |  ...Do or do not.
20 54 68 65 72 65 20 69 73 20 6e 6f 20 74 72 79 |   There is no try
20 21 00 00 00 00 00 00 00 00 00 00 00 00 00 00 |   !..............
00 00 00 00 00 00 00 00 21 00 00 00 00 00 00 00 |  ........!.......
70 61 73 73 77 6f 72 64 3d 6d 79 70 61 73 73 1f |  password=mypass.
00 00 00 00 00 00 00 00 21 00 00 00 00 00 00 00 |  ........!.......
70 61 73 73 77 6f 72 64 3d 6d 79 70 61 73 73 20 |  password=mypass 
00 00 00 00 00 00 00 00 21 00 00 00 00 00 00 00 |  ........!.......
70 61 73 73 77 6f 72 64 3d 6d 79 70 61 73 73 21 |  password=mypass!
00 00 00 00 00 00 00 00 21 00 00 00 00 00 00 00 |  ........!.......
70 61 73 73 77 6f 72 64 3d 6d 79 70 61 73 73 22 |  password=mypass"
00 00 00 00 00 00 00 00 21 00 00 00 00 00 00 00 |  ........!.......
70 61 73 73 77 6f 72 64 3d 6d 79 70 61 73 73 23 |  password=mypass#
00 00 00 00 00 00 00 00 21 00 00 00 00 00 00 00 |  ........!.......
70 61 73 73 77 6f 72 64 3d 6d 79 70 61 73 73 24 |  password=mypass$
00 00 00 00 00 00 00 00 21 00 00 00 00 00 00 00 |  ........!.......
70 61 41 41 41 41 41 41 41 41 41 41 41 41 41 41 |  paAAAAAAAAAAAAAA
41 41                                           |  AA




Corrected Hearbeat Response : 
wrong request``
