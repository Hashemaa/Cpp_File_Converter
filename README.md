# Cpp_File_Converter
This is a C++ program that compresses any file to text or binary that gets stored in a text file. Then converts the file to any other file type desired, without losing data or quality!


FILE CONVERTER by Hashem Abou Ahmad.

-- An image example called 'EXAMPLE' is provided in the folder --

rle -> run-length encoder.
rld -> run-length decoder.

rle is used to encode your file to text or binary.
rld is used to decode your file to a specific type.

-b is a switch that will convert your file to binary.
-t is a switch that will convert your file to ASCII text.
Both will return the same results.
-b is faster than -t, so use -b.


STEPS:

1) Copy and paste the file you want to convert in the folder which contains the rle and rld executable files.

2) Click on the path in which the rle and rld files exist and type cmd (or open command prompt and navigate to the path where the rle and rld executable files exist).

3) In command prompt (cmd) write: rle -b (file name you want to convert, e.g. nature.jpg)

4) Wait until it is done (when you can type again in the cmd)

5) The program will generate a new file with a .rleb extension.

6) Once it is done and you can type, write: rld -b (the .rlet extension file, e.g. nature.png.rleb) (Choose a filename with an extension of your choice e.g. nature.png)

7) The program will generate the converted file in the same folder that contains the rle and rld executable files.

You can always type: rle --help 		OR 		rld --help		to view all options.
