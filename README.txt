Launch Guide!

Running through a ready-made executable file:
1) You can run the game if you download all the files from the git from 
the executable_files folder and transfer these three files to the board. 
After that you can run the game in the standard way(./space_invaders).
However, if you are transferring files using SSH, 
use the following launch command: 

ssh $(SSH_OPTIONS) -t $(TARGET_USER)@$(TARGET_IP) "cd $(TARGET_DIR) && ./$(TARGET_EXE)".

2) You can run the game by compiling it yourself.
To do this, download the space_invaders file from the git repository.
Edit the Makefile with the ip board and the location of the SSH key 
and run the make run.
