# OS-Ass3-5781
Startup files for assignment 3 in OS 5781
 


# OS-Ass3-5781
Startup files for assignment 3 in OS 5781
Tomer Revivo 204470892, Shelly Revivo 315661884
Course: Operating Systems
Assignment 3: Threads and Locks: Bounded Buffer
Semester A, Year 2021.

explention of how the code works:

In main - we create 3 processes for different suppliers, and 3 processes for different consumers.
Each process has a test file that we received in the git hub
We summon the processes, any process that does not end, will wait for a certain condition in order to continue, and in the meantime it waits for another process to run in the background.
In the vendor and needs departments we created functions and linked them to each process.
Any process that has done a certain action such as consuming or providing will wait a few seconds (given in the file) for the next process after it.
If all processes have been completed successfully, a message will appear stating that they have been completed. Otherwise, a message that did not end successfully will appear.
Each time a process worker the processor decides which process will be earlier, if it is the supplier - he will check if there are more than 200 units in the machine and if necessary and place to put more units.
If it is the consumer he will check if there are any bottles and he can take a specific number of bottles or not. In case he does not succeed he will wait until there are more bottles.




Our comments:
In order to run the program, we will go to the folder where all the files including the test files are located, and run make
Then run./machine

Test files must be modified before running -
For example :
If the file says:
supplier 1
3
5
10
Change to:
supplier1
3
5
10

In our case, the code recognizes the first word as a name and not the whole sentence, so the examiner will have to delete one space after the name. If not deleted it will recognize the number 1 as additional data and destroy the run. We will be glad that you do not forget to do this before so that there will be no problems with the test.
