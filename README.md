# My<img src="./markus_assets/markus.png" width="110"/>
Personalize UofT MarkUs instance

## Purpose
This program helps you to personalize your MarkUs page. So there are only YOUR courses can be displayed here.

## Example
<img src="./markus_assets/example.png" width="400"/>

## Build
```sh
gcc -o mm main.c
./mm
```
After generated MyMarkUs.html, open it in your broser and save it for later use. You can add favicon.ico in the generated folder to enable great favicon.

## Sample Usage
```
$ ./mm
Where do you want to store the output data?
Press ENTER to set to current directory OR provide the directory path.

Will store in current directory.
Creating environment...
Please provide the CSC courses code you took this term have Markus:
Example: CSC108 can be write as [108]
309
CSC 309 added! Press 999 + ENTER to quit adding
343
CSC 343 added! Press 999 + ENTER to quit adding
373
CSC 373 added! Press 999 + ENTER to quit adding
384
CSC 384 added! Press 999 + ENTER to quit adding
999
Loading data...
Creating MyMarkus...
Loaded 4 courses!
MyMarkus Generated, please open it and save/bookmark it. Thank you!
```

## Upcoming features
- Beautiful UI
- Support Past courses
- ...
