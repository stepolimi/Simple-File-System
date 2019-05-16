# Final exam (Project of Algorithms and Data Structures)
# A Simple File System

# 1- Summary

The goal of the Algorithms and Data Structures project is to implement a simple hierarchical file system with storage only in main memory.
A hierarchical filesystem organizes resources according to a tree structure,
and identifies each resource uniquely through the path that connects it to
root. The resources contained in a hierarchical file system can be files or
directory. Both have a name, represented as a string of
characters. For the former it is only possible to be inserted as leaves of the tree, while the latter can appear as both leaves and intermediate nodes.
The root of the tree is conventionally a directory, called the root directory. Only file nodes can contain data, represented as one
sequence of bytes, while directories have no associated data. All nodes
of the tree may contain metadata, but for the purposes of this project, only the
directories contain them. The directory metadata is the names of its directs
descendants.
The program that implements the filesystem will receive a diary of the actions from
perform from standard input and print the result of the same on standard
output. The program must be implemented in standard C, with the sole aid
the standard library (libc) and the base runtime. The operation of the program requires it to read a line of the diary of the actions, carry out the action
corresponding on the internal representation of the filesystem maintained by it,
and write the result on standard output before proceeding to the next action
(the execution of the actions is completely sequential)


# 2- Input Format

The filesystem paths are represented with the usual UNIX syntax: a path and therefore the sequence of names of resources that reaches from the root directory the resource identified by the path. The names are separated by the separator character of course /).
The following restrictions apply:

• resource names are alphanumeric and can be maximum at most255 characters;

• the maximum height of the tree `and 255;

• the maximum number of children of a node is 1024.

The program receives one of the following commands for each line of the journal file
given as input, where hpercorsoi indicates a generic path and hnomei a string
alphanumeric of up to 255 characters.

• create (path): The command has the effect of creating a file
empty, or without associated data, inside the filesystem. Print in
output the "ok" result if the file was created regularly, "no" if the creation of the file was not successful (for example, if you try to create
a file in a non-existent directory, or if the filesystem limits are exceeded).

• create dir (path): Create an empty directory inside the filesystem. Print the outcome "ok" if the directory has been created
regularly, "no" if the creation was not successful.

• read (path): Reads the entire contents of a file, printing in
output "content" followed by a space character and the contents of the file
if the file exists or prints "no" if the file does not exist.

• write (path) (content): Writes the contents of a file,
that must already exist (if the file already had content, it is overwritten); output "ok" followed by the number of characters written
if the writing is successful, "no" otherwise. The parameter
(content) has the form of a sequence of alphanumeric characters and spaces
delimited by double quotes. Example:
write / poems / jabberwocky "It was brillig and the slithy toves"

• delete (path): Delete a resource, print the result ("ok" -
"no"). A resource is erasable only when it has no children.

• delete_r (path): Delete a resource and all its descendants if
present. Print the result ("ok" - "no").

• find (name): Search for the location of the (name) resource within the filesystem. Output print "ok" followed by the resource path for each resource with correct name found. Resource prints must be carried out in lexicographic order of the path to be printed. The characters of path separator must be considered in the order, the comparison for the sort must therefore be made between whole strings representing paths. In case no resource is found, the command prints "no".

• exit: Ends the execution of the resource manager. Nothing prints in
output.


# 3- Requirements of temporal complexity

Said l the length of a path, d the number of resources in the entire filesystem,
r the number of child resources of the one specified by the path, and f the number
of resources found by a research, the expected temporal complexities of primitives
specified in the previous section are the following:

create: O(l)

crate_dir: O(l)

read: O(l + |file content|)

write: O(l + |file content|)

delete: O(l)

delete_r: O(r)

find: O(d + f*f)
