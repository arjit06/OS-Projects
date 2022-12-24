#import numpy as np
import matplotlib.pyplot as plt

def func():
    pass

file=open("data.txt",'r')
l=file.readlines()
thread1_readings=[]
thread2_readings=[]
thread3_readings=[]
priorities=[5,15,25,35,45,55,65,75,85,95]
for a in l:
    b=a.split()
    if len(b)==2:
        if b[0]=="Thread1:":
            thread1_readings.append(float(b[1])) 
        elif b[0]=="Thread2:":
            thread2_readings.append(float(b[1])) 
        elif b[0]=="Thread3:":
            thread3_readings.append(float(b[1])) 
file.close()

Width=1

# print(thread1_readings)
# print(thread2_readings)
# print(thread3_readings)

# setting position of bars
br1 = [4*i for i in range(len(thread1_readings))]
br2 = [x + Width for x in br1]
br3 = [x + Width for x in br2]

plt.bar(br1, thread1_readings, color ='r', width = Width, edgecolor ='black', label ='SCHED_OTHER')
plt.bar(br2, thread2_readings, color ='g', width = Width,edgecolor ='black', label ='SCHED_RR')
plt.bar(br3, thread3_readings, color ='b', width = Width, edgecolor ='black', label ='SCHED_FIFO')

plt.xlabel('Priorities for SCHED_RR, SCHED_FIFO  (nice values for SCHED_OTHER)', fontweight ='bold', fontsize = 15)
plt.ylabel('Time in s', fontweight ='bold', fontsize = 15)
plt.xticks([4*r + Width for r in range(len(thread1_readings))], ["5 (nice-18)","15 (nice-16)","25 (nice-14)","35 (nice-12)","45 (nice-10)","55 (nice-8)","65 (nice-6)","75 (nice-4)","85 (nice-2)","95 (nice-0)"])

plt.legend()
plt.show()