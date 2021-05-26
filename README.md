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
The Fat 16 file system has the following structure:
 PUT AN IMAGE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 
The reserved region section contains internal and extenral metadata about the file directory, and a jump to the bootstrap code. For this implementation, the most important section is the internal metadata which is used in phase 1. 
 PUT AN IMAGE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 
 In this practice, the File Allocation Table was not explored. However, it is a linked list of clusters. Each file and sub directory has an entry in this table.  

 The root directory contains all of the information needed to traverse the entire filesystem, however, the data region contains sub-directories with their own files. For example, let's say we have a root directory with 3 files and another directory inside. The entries in the root directory are 32 byte entries, which consists of metadata about the entry. The Data region contains the same information, however, in order to navigate to this section, the starting cluster of the directory entry you want to navigate to must be found first. 
 PUT AN IMAGE HERE
 
### Ext2
In the Ext2 file system, there are a number of important concepts. 
 PUT AN IMAGE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
The Ext2 partition is split into block groups, which all have the same size, and are stored one after another. Within these block groups are individual blocks, which contain information about a given file. In order to find the information of a particular file, its inode should first be found. An inode (index node) contains the metadata for a single file or directory on the system, indicating things like which block group it is in. 

A more in depth explanation for what each section is used for can be seen in the following section.
## Explanation of the Practice

### Requirements
In this project, we were required to implement 3 different commands that would return information about a filesystem. This filesystem could be either Ext2 or Fat16.
#### /info
Phase 1 was very straightforward. The requirements for this phase was that we had to implement the /info command. The purpose of this command was to get the metadata for each file system. 
##### Fat16

In order to get the metadata for Fat16, the program navigates to the boot sector on the file system, and reads the information from the desired offsets. 
##### Ext2
In order to get the metadata for Ext2, the program navigates to the superblock on the file system, and reads the information from the desired offsets. In this particular implementation, the superblock of is read from block group 0, however, a copy of it exists in each block group. 

#### /find
For Phase 3, we were again required to program the /find command, which would return the filesize of a file the user input. If the file cannot be found, then an error is displayed. However, in this phase, we also had to serach the subdirectories of the filesystem for the file the user input. Therefore, any file in any subdirectory should be found.  
##### Fat16

In Fat16, there are two main important sections for finding files, the root directory, and the data region. In order to check what files the sub-directory has inside, we would need to traverse to the data region. The root directory can be traveresed to by adding the offset of the reserved region and the fat table. The data region can be traversed to by adding the root offset, and the size of the root directory. Whenever we're checking if a file is the one we want, there are 6 important attributes that should be taken into consideration: file name, file extension, file attribute, starting cluster, and file size. File name and extension can be combined to get the file name the user will input, and starting cluster points to the offset of the "logical block" where the information of the file or subdirectory is stored. File size is part of the desired output.  

For each 32 byte entry in the root directory, its attribute is checked. If that attibute indicates that it is a directory, we recurse with the new directory offset. Then, all of the entries in the subdirectories are checked, if they do not match, then we exit the function and continue checking through the root directory. If the file and its extension match the file name the user input, then a message is printing saying the file has been found. Otherwise, a message saying the file could not be found is printed. 

In this project, we do not take long file names into consideration.

##### Ext2

In Ext2 files are found with a different method. Essentially, in order to find a file, we need to navigate to the block it is in. In this implementation, we first start the search in the root block to find the offset of the inode table. The inode table will tell us how many blocks are reserved for a particular inode, and their locations. Using this information, we can navigate to the block with the relevant information. From there, we can start checking the file information by looping through each entry in each block that is reserved for an inode. Within which, the name, record length, and filetype is checked. If we find a directory, we navigate to the block group of that directory by using the information that we just obtained, and repeat the search. However, if it's a file, we check its name, and if it's the same, we print out the file size. 

#### /delete
For Phase 4, we required to find a file the user desired, and then delete it. It has similar functionality to Phase 2/3
##### Fat16
In the Fat16 filesystem, deleting files is quite straightforward. In order to delete a file, it is only required that the first character of the filename have the value "0xE5". This value indicates that the following 32 bytes are 'empty', and therefore can be ignored. To implement this functionality, I simply added a flag to the function call of FileFat16::findFat16File() and findFile() to indicate if the user wants to remove the file they're looking for or not. Once the file is found, the program navigates to the offset of the file, and replaces the first char with the value "0xE5". 

##### Ext2
Although not as straightforward as Fat16, deleting files is quite straightforward in Ext2 as well. To delete a file, the entry of the file before the one the user desires to delete should have its record length modified. The record length adjusted to the file's normal record length, and the record length of the file the user wants to delete. However, if the entry is the first entry in the block, then, the next entry should replace and overwrite the entry of the file that the user wants to delete. Just like in Fat16, I once again added a flag to the function call of FileExt2::findExt2File() and findFile() to indicate if the user wants to remove the file they're looking for or not. Once the file is found, the program navigates to the offset of the file, and replaces one of the offsets with the appropriate values. More detail about this section can be seen in the Data Structures section.

### Design

In this project, I used the following design:
 PUT AN IMAGE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 
 The Fat16/Ext2 class was used to maintain and manage the objects that contained the metadata of the system. 
 On the other hand, the FileExt2/FileFat16 classes prodivded the functionality of getting and displaying the information obtained from the files within the filesystem. It contains the functions 'putFileInfoOnObject' and 'findFile', which obtain the metadata for the file system, and find a file in a filesystem respectively. Normally, it might be better to put the parts of the code that display things on the cmd in another dedicated class. However, in this implementation, most of the 'view' functionality is a single print, so putting these single line code snippets in a dedicated class seemed over-engineered.
 
 The errors class was used for handling command line errors. For example, this class was used to check if there were the correct number of arguments, and if those arguments were correct. For example, it checks if the command entered by the user is one of the three valid ones, and if the number of command line arguments are correct. 
 
 FileManager essentially determines the type of filesystem the user has input, and then calls the appropriate function for the file type. 
 
 The Disk file is essentially an interface for the Fat16 and Ext2 classes. The function 'printData()' is a method used by both Fat16 and Ext2 objects in order to display the information stored within that object.  If I were to redo this project, I would replace this interface, and make file manager the interface to FileExt2 and FileFat16, as that file fits the purpose better.
 The main file has the skeleton of the program. It determines which command was entered, and runs the appropriate function depending on what's been called. As it simply uses commands from other parts of the code, it is quite barebones. 
 
### Data Structures

In this project, I only used a handful of data structures. One thing I would do differently in this project is try to add more data structures, as there are some places where I declare new varaibles similar to ones used previously in the code. 

#### Fat16
 In Fat16, I only used one data structure, which looks as follows:
 PUT AN IMAGE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
This data structure was used to store all of the metadata about the disk volume. So, whenever the function FileFat16::putFileInfoOnObjectFat16() was called, the information about the disk could instantly be used. For example, when trying to find a file in Fat16, much of the information required to traverse to the "data" sector of the disk can be found in the metadata of the file. By storing this information in a datastructure in an object, retrieval of this information is efficient, saving time, and not requiring the program to run repetitive code. 
For example, when calculating the initial offset for the root directory, a Fat16 object of the data structure is used as follows:
 PUT AN IMAGE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
 
 As you can see, we need those attributes in order to navigate to the root directory. This method saves time by avoiding repetitive code.

#### Ext2

Similarly to Fat16, I also created a data structure to store the information of the Ext2 metadata.
PUT AN IMAGE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Again, like Fat16, the information from FileExt2::putFileInfoOnObjectExt2() was stored on an object. This metadata was useful to access the appropriate offsets when needed. For example
PUT AN IMAGE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

However, unlike Fat16, I created a secondary datatype so I could store information about each inode:
PUT AN IMAGE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
This datatype was created purely for the "/delete" functionality of the project. Each time a directory is traversed, the information of the most recent file read is stored in one position of an array of this datatype. As explained in the "/delete" section, to "delete" a file in Ext2, we have to replace the previous file's record length with its current record length and the record length of the file we want to delete. By creating an array of two positions of this datatype, and then alternating the index with each loop, we are easily able to store not only the information of the file that we found, but also the information of the previous file. This allows us to easily delete the file by performing the override. 

### Tests Performed
For each phase, the level of testing varied. For example, for phase 1, the testing done was very limited. However, this is due to the fact that if a value is obtained incorrectly, then it is immediately obvious something is wrong. Contrast this with phase 3, where much more tests need to be performed in order to make sure directory traversal is performed correctly. 

One test done was checking the basic functionality of the project. For example, since Phase 2 required the students to check if a file was in the root directory of the respective file system, I tested it by checking if I could find each file in the respective root directory with my program. This basic test was done for each phase, as it was the minimum required test to ensure the program was working correctly. This type of test largely consisted of printing out different values from the file system, and checking their values against the values of the actual file system via a hex-editor. Another testing method in the same vein was mounting and unmounting the different filesystems via the visual studio code WSL command line interface. This way, once I deleted a file, I could check if it had truly been deleted, or if my code was only reading that particular file as deleted.

The other test that was done was checking the functionality by using modified Ext2 files. This was to ensure that my project would work with any ext2 or fat16 file, no matter what its contents were. For example, I mounted the default Ext2 file, and added many more directories and files. Some of these files had particularly long file names, so i could check that my code was working correctly. This particular test helped me see that I was reading too many positions when reading a file name. This meant that file names would overlap into one another, and I would sometimes end up reading junk characters. With this file system test, I also realized that I was not looping through all of the blocks within a directory. This meant that if a file was contained in an directory, but not within it's first block, then my program was unable to find this file. This was a major problem, and luckily, this form of testing allowed me to catch some mistakes in my program that I would have missed without it. 

### Observed Problems

Overall, this practice had a good level of difficulty. Most of the problems encountered were due to a lack of understanding the file system structure, so many problems were solved naturally as understanding increased. For example, when doing Fat16 in phase 3, I was able to recurse and traverse each directory correctly, however, my program kept ending because I was findnig strange files. I was stuck on this problem for quite a long time, as I didn't realize these "strange files" had flags that indicated they were different from normal directory entries. Once I added a check for these files in order to skip them, my project functioned flawlessly. 

A similar problem occured with Ext2 in phase 3. Although not conceptually difficult, in phase 2 I did not make many comments in my code, and I had named some variables incorrecctly. That meant that converting between a "root-only" traversal and a full system-wide traversal was a bit difficult. I had to take a bit more time on this phase in order to reorganize code, rename variables, and properly understand how full directory traversal worked. Also, due to the limited disk volume I was using for testing, I did not realize that I needed to traverse all of the blocks that belonged to a directory. This meant that while working on phase 4, I had to go back and fix my Ext2 implementation. This ended up taking a bit more time than I expected, as I had to rework how I retrieved the block numbers and file offsets for each different directory. Once I did this, I was quickly able to solve Phases 3 and 4.  

Although the practice had a good difficulty level, I personally would have liked a bit more time between checkpoints. In addition to the other practices given by the university, having to deliver one phase each 2 weeks (approximately) meant that ocassionally, other projects with stricter deadlines had to be prioritized over this one. Perhaps 2-3 additional days would have alleviated this problem a bit. 

### Temporal Estimation
In total, I spent 70 hours on this project, divided as follows:

PUT AN IMAGE HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

1. Phase 1: 17 hours 
2. Phase 2: 15 hours
3. Phase 3: 22 hours 
4. Phase 4: 16 hours 

Many of these hours include class time.

Out of all of the phases, phase 3 was the most challenging, however, this was partially due to the fact that I had not taken some small details into consideration. For example, the Fat16 phase 3 problem as explained in the previous 'Observed Problems' section. If I were to redo the project, the 1st phase probably would not take 17 hours. The large amount of time spent in this phase was due to the lack of familiarity with how both file systems worked. Phase 3 would also take less time, as now I am more familiar with how the directory structure of Ext2 works, and which flags to check for in Fat16. Phase 4 also took more time, as I had to go back and redo its implementation after I realized I had falied to consider each block of a directory. 

## Explanation and Assessment of the Git
For this practice, we were required to use Git version control via Github. Although many students had previously used Github to work on many collaboartive projects together, this practice also requried us to make 3 different branches per phase. One phase was required for Fat16, another for Ext2, and at the end of each phase, a "delivery" branch was required. This delivery branch contained the final implementation of the code from that specific phase. These branches were required to be compatible with the main branch of the project. Therefore, the use of git not only improved the students understanding of version control, but also the ability to implement and maintain consistent, clean code for a project. 
## General Conclusions
In conclusion, this practice was very helpful in learning about the different features of the Fat16 and Ext2 file systems. Additionally, requiring the use of Git required the students to become familiar with its use and functionality. This is a very important skill, as many companies in the real world implement some form of version control. Therefore, even if Git isn't necessarily used, the skills developed in this practice can be applied in a wide variety of situations. The most difficult part of the project was doing the research to figure out how to take the next step in each phase of the practice. Although the documentation was very helpful, sometimes, it was worded in a confusing way, which made it hard to understand some functionalities of the described file system. That being said, the research was also the most rewarding part of the project, as once a solution was discovered, it was very straight-forward and simple to implement. If I had to go back and redo this project, I would make sure to compartmentalize my functions more. In my program, there are quite a number of sections of repeated code, and if I had a bit more time, I would go back and compartmentalize them. 

## Bibliography
Kirby, D. (2000). File Systems. Richland Community College. https://people.richland.edu/dkirby/filesystems.htm

Thygesen, L. K. (199 C.E.). Maverick - The Operating System. (C) 1999 Lasse Krogh Thygesen. http://www.maverick-os.dk/FileSystemFormats/FAT16_FileSystem.html

The Ext2 File System. (n.d.). Piazza. https://piazza.com/class_profile/get_resource/il71xfllx3l16f/inz4wsb2m0w2oz#:~:text=The%20Ext2%20file%20system%20divides,lower%20average%20disk%20seek%20time
