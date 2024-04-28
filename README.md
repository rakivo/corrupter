## Corruptor is a tool to prank your friends (if you have one).

### Warning: Corruptor is a potentially dangerous application. Read the usage section carefully before doing anything!

### Corruptor is a tool that corrupts all files in directory given as an argument, as in here: ```./corruptor ~/```, <- DON'T DO THAT xd

## Usage:
- I've set the CORRUPT variable to 0 to keep you safe, but to perform a prank you got to set it to 1 (it's in the main.c file), and then if you on Linux: run ```make -k```, if you on Windows: run ```.\build.bat```
- After that you can send the compiled binary to your friend and wait for the Corruptor to perform its prank(Don't forget to tell your friend to pass ```~/``` as second argument)
- Important! If your friend is using Windows(OS for games), make sure that he'll use Corruptor as here: ```./corruptor.exe ".\"```, you need to put path in quotation marks.
- Oh, I almost forgot to tell you! By the way, you can edit the WRITE_WHAT variable to change the content that will be written to all of your friend's computer files. By default it is set to "rakivo"
