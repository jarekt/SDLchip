#this script takes a file and makes it into a c string in a header file
file_name = "tetris.ch8"
newfile_name = "tetris.h"

start_string = 'const char import_string[] = {'
end_string = '};\nconst size_t import_string_size = sizeof(import_string) / sizeof(import_string[1]);\n//this is tetris.ch8 converted using my python script into a string'

oldFile = open(file_name, "rb")
oldFile = oldFile.read()
oldFile = "".join( hex(x) +"," for x in oldFile)
oldFile = start_string + oldFile + end_string
newFile = open(newfile_name, "wt")
newFile.write(oldFile)
newFile.close()

print(oldFile)