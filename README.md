## Corrupter is a tool to prank your friends (if you have one).

### Warning: Corrupter is a potentially dangerous application. Read the usage section carefully before doing anything!

### Corruptor is a tool that corrupts all files in directory given as an argument, as in here: ```./corruptor ~/```, <- DON'T DO THAT xd

## Usage:
- I've set the CORRUPT variable to 0 to keep you safe, but to perform a prank you got to set it to 1 (it's in the main.c file), and then run ```make```
- After that you can send the compiled binary to your friend and wait for the Corrupter to perform its prank(Don't forget to tell your friend to pass ```~/``` as second argument)
- Important! Make sure your friend (or maybe not) is using Linux, because Corrupter works only on Linux.
- Oh, I almost forgot to tell you! By the way, you can edit the WRITE_WHAT variable to change the content that will be written to all of your friend's computer files. By default it is set to "rakivo"
