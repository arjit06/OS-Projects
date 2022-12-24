# OS-Projects 

1) Modified Dining Philosophers Problem: 						
(a) Writing  a program to simulate the philosophers using threads, and the forks using global variables.
Resolving the deadlock using the following techniques: 1. Strict ordering of resource requests, and  2. Utilization of semaphores to access the resources. 
  
(b) Repeating the above system  with a system that also has two sauce bowls. The user would require access to one of the two sauce
bowls to eat, and can access any one of them at any point of time.
			 
			 						
 						               
2) Interprocess Communication:	
Writing two programs P1 and P2. The first program P1 will generate an array of 50 random strings (of characters) of fixed length each. P1 then sends
a group of five consecutive elements of the array of strings to P2 along with the ID’s of the strings, where the ID is the index of the array corresponding
to the string. The second program P2 then accepts the received strings, and sends back the highest ID received back to P1 to acknowledge the strings
received. The program P2 simply prints the ID’s and the strings on the console. On receiving the acknowledged packet, P1 sends the next five strings, with the
string elements starting from the successor of the acknowledged ID.
					
The above mechanism is implemented using three different techniques: 					
(i) Unix domain sockets									
(ii) FIFOs							
(iii) shared memory				
						
									
						
3) Process Scheduling:	
Creating three threads and counting from 1 to 2^32-1 in each of them using different scheduling policies in each of them
i.e. SCHED_OTHER IN thread A , SCHED_RR in thread B  and SCHED_FIFO in thread C .
			
						
										
4) Writing my own syscall:	
The syscall copies copies one 2-D floating point matrix to another using using kernel functions like copy from user() and copy from user() to read data
bytes from user space and write back to user space.
