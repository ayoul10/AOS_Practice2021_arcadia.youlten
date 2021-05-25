# Semester 2 Advanced Operating Systems Final Project - Arcadia Youlten

## How to Compile the Practice
Due to the inclusion of the make file in the project, the only thing to compile the practice is the following steps:
1. Download the project from Github or clone it into your local enviornment 
2. Using a wsl command line, navigate to the project folder. 
3. Run the command 'make'

It should be noted that [gcc](https://linuxize.com/post/how-to-install-gcc-compiler-on-ubuntu-18-04/) and [wsl](https://docs.microsoft.com/en-us/windows/wsl/install-win10) should be installed to compile correctly.
This will compile the practice. To run the practice, the following commands can be used
```bash
./shooter /info <file_system_name> 
./shooter /find <file_system_name> <file_to_find>
./shooter /delete <file_system_name> <file_to_delete>
```
The practice functions with Fat16 or Ext2 file systems. 
## Explanation of the file systems

In this practice, we were required to find information and files on two different file systems: Fat16 and Ext2. 

### Fat16

### Ext2

## Explanation of the Practice

### Requirements
In this project, the students were required to .
Phase 1
Phase 2
Phase 3
Phase 4

### Design

In this project, I used the following design:

### Data Structures

### Tests Performed

For each phase, the level of testing varied. For example, for phase 1, the testing done was very limited. However, this is due to the fact that if a value is obtained incorrectly, then it is immediately obvious something is wrong. Contrast this with phase 3, where much more tests need to be performed in order to make sure directory traversal is performed correctly. 

One test done was checking the basic functionality of the project. For example, since Phase 2 required the students to check if a file was in the root directory of the respective file system, I tested it by checking if I could find each file in the respective root directory with my program. This basic test was done for each phase, as it was the minimum required test to ensure the program was working correctly. This type of test largely consisted of printing out different values from the file system, and checking their values against the values of the actual file system via a hex-editor. 

The other test that was done was checking the functionality by using modified Ext2 files. This was to ensure that my project would work with any ext2 or fat16 file, no matter what its contents were. <example>? 
this was important, as it let me catch some mistakes in my program that I would have missed without it. 

### Observed Problems

Overall, this practice had a good level of difficulty. Most of the problems encountered were due to a lack of understanding the file system structure, so many problems were solved naturally as understanding increased. 
For example, when doing Fat16 in phase 3, I was able to recurse and traverse each directory correctly, however, my program kept ending because I was findnig strange files. I was stuck on this problem for quite a long time, as I didn't realize these "strange files" had flags that indicated they were different from normal directory entries. Once I added a check for these files in order to skip them, my project functioned flawlessly. 
Phase 4 Ext2 was the most challenging, as 
A similar problem occured with Ext2 in phase 3. Although not conceptually difficult, in phase 2 I did not make many comments in my code, and I had named some variables incorrecctly. That meant that converting between a "root-only" traversal and a full system-wide traversal was a bit difficult. I had to take a bit more time on this phase in order to reorganize code, rename variables, and properly understand how full directory traversal worked. Once I did this, I was quickly able to solve Phase 2. 

Although the practice had a good difficulty level, I personally would have liked a bit more time between checkpoints. In addition to the other practices given by the university, having to deliver one phase each 2 weeks (approximately) meant that ocassionally, other projects with stricter deadlines had to be prioritized over this one. Perhaps 2-3 additional days would have alleviated this problem a bit. 

### Temporal Estimation
In total, I spent 59 hours on this project, divided as follows:
1. Phase 1: 17 hours 
2. Phase 2: 15 hours
3. Phase 3: 22 hours 
4. Phase 4: 5 hours 

Many of these hours include class time.

Out of all of the phases, phase 3 was the most challenging, however, this was partially due to the fact that I had not taken some small details into consideration. For example, the Fat16 phase 3 problem as explained in the previous 'Observed Problems' section. If I were to redo the project, the 1st phase probably would not take 17 hours. The large amount of time spent in this phase was due to the lack of familiarity with how both file systems worked. Phase 3 would also take less time, as now I am more familiar with how the directory structure of Ext2 works, and which flags to check for in Fat16. 
## Explanation and Assessment of the Git
For this practice, we were required to use Git version control via Github. Although many students had previously used Github to work on many collaboartive projects together, this practice also requried us to make 3 different branches per phase. One phase was required for Fat16, another for Ext2, and at the end of each phase, a "delivery" branch was required. This delivery branch contained the final implementation of the code from that specific phase. These branches were required to be compatible with the main branch of the project. Therefore, the use of git not only improved the students understanding of version control, but also the ability to implement and maintain consistent, clean code for a project. 
## General Conclusions
In conclusion, this practice was very helpful in learning about the different features of the Fat16 and Ext2 file systems. Additionally, requiring the use of Git required the students to become familiar with its use and functionality. This is a very important skill, as many companies in the real world implement some form of version control. Therefore, even if Git isn't necessarily used, the skills developed in this practice can be applied in a wide variety of situations. The most difficult part of the project was doing the research to figure out how to take the next step in each phase of the practice. Although the documentation was very helpful, sometimes, it was worded in a confusing way, which made it hard to understand some functionalities of the described file system. That being said, the research was also the most rewarding part of the project, as once a solution was discovered, it was very straight-forward and simple to implement.   

## Bibliography
https://people.richland.edu/dkirby/filesystems.htm

