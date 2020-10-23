//DECODER
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string versionNumber = "1.0.1";

//Function headers.
void output_help();

void text_mode(int argc, char* argv[], bool switchIncluded);

void binary_mode(int argc, char* argv[], bool switchIncluded);

void validation(char* argv[]);

//Main.
int main(int argc, char* argv[]) {

    if (argc == 1) {
        cout << "Error: no commandline arguments detected - showing help." << endl;
        output_help();
        exit(EXIT_FAILURE);
    }
    else if (argc == 2) {
        if (strncmp(argv[1], "-", 1) == 0)
            validation(argv);

        else
            text_mode(argc, argv, false);
    }
    else if (argc == 3 || argc == 4) {

        if (strcmp(argv[1], "-t") == 0)
            text_mode(argc, argv, true);
        else if (strcmp(argv[1], "-b") == 0)
            binary_mode(argc, argv, true);
        else if ((strcmp(argv[1], "-t") != 0) && (strcmp(argv[1], "-b") != 0))
            text_mode(argc, argv, false);
        else
            validation(argv);
    }
    else {
        cerr << "Error: too many commandline arguments detected - showing help." << endl;
        output_help();
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}//End of main() function.


//Functions.
void output_help() {
    cout << "rld (c) 2020, Hashem Abou Ahmad" << endl;
    cout << "===========================================================\n";
    cout << "Version " << versionNumber << "\n\n";
    cout << "A run-length decoder utility.\n\n";
    cout << "Usage: rld [-(b|t)] [--help] [--version] infile [outfile]\n\n";
    cout << "Examples:\n";
    cout << "  rld myfile.doc.rlet\n";
    cout << "    > decodes 'myfile.doc.rlet' to 'myfile.doc' (text mode)\n\n";
    cout << "  rld myfile.doc.rleb\n";
    cout << "    > decodes 'myfile.doc.rleb' to 'myfile.doc' (binary mode)\n\n";
    cout << "  rld -t myfile.rle myfile.doc\n";
    cout << "    > decodes 'myfile.rle' to 'myfile.doc' (text mode)\n\n";
    cout << "  rld -b myfile.rle ec.exe\n";
    cout << "    > decodes 'myfile.rle' to 'ec.exe' (binary mode)\n\n";
    cout << "  rld --help\n";
    cout << "    > displays the help\n\n";
    cout << "  rld --version\n";
    cout << "    > displays version number in the format d.d.d\n\n";
}//End of output_help() function.

void text_mode(int argc, char* argv[], bool switchIncluded) {

    ifstream inFile;

    if (argc != 4 && switchIncluded == false)
        inFile.open(argv[1]);
    else if (argc == 3 && switchIncluded == true)
        inFile.open(argv[2]);
    else
        inFile.open(argv[2]);

    if (inFile.good()) {
        string outFileName = argv[argc - 1];
        ofstream outFile;
        if (argc == 2 || (argc == 3 && switchIncluded == true)) {
            size_t extPos = outFileName.find_last_of('.');
            //filename.txt.rlet
            outFileName.erase(extPos, outFileName.length());
            outFile.open(outFileName, ios::binary);
        }
        else if (argc == 3 && switchIncluded == false || (argc == 4 && switchIncluded == true))
            outFile.open(outFileName, ios::binary);

        int token;
        streamsize space;
        while (inFile >> space >> token) {
            for (size_t i = 0; i < space; ++i)
                outFile << (unsigned char)token;
        }

        if (outFile.bad()) {
            cerr << "Error: bad output file." << endl;
            exit(EXIT_FAILURE);
        }

        outFile.close();

    }
    else if (inFile.bad()) {
        cerr << "Error: bad input file." << endl;
        exit(EXIT_FAILURE);
    }
    else if (argc > 1) {
        cerr << "Error: program <" << argv[1] << "> doesn't exist." << endl;
        exit(EXIT_FAILURE);
    }
    inFile.close();

}//End of text_mode() function.

void binary_mode(int argc, char* argv[], bool switchIncluded) {

    ifstream inFile;

    if (argc != 4 && switchIncluded == false)
        inFile.open(argv[1], ios::binary);
    else if (argc == 3 && switchIncluded == true)
        inFile.open(argv[2], ios::binary);
    else
        inFile.open(argv[2], ios::binary);

    if (inFile.good()) {
        string outFileName = argv[argc - 1];
        ofstream outFile;
        if (argc == 2 || (argc == 3 && switchIncluded == true)) {
            size_t extPos = outFileName.find_last_of('.');
            //filename.txt.rlet
            outFileName.erase(extPos, outFileName.length());
            outFile.open(outFileName, ios::binary);
        }
        else if (argc == 3 && switchIncluded == false || (argc == 4 && switchIncluded == true))
            outFile.open(outFileName, ios::binary);

        streamsize buffer;
        char token;
        while (inFile.read((char*)&buffer, sizeof(buffer))) {
            inFile.read(&token, 1);
            for (streamsize i = 0; i < buffer; ++i)
                outFile << token;
        }

        if (outFile.bad()) {
            cerr << "Error: bad output file." << endl;
            exit(EXIT_FAILURE);
        }

        outFile.close();

    }
    else if (inFile.bad()) {
        cerr << "Error: bad input file." << endl;
        exit(EXIT_FAILURE);
    }
    else if (argc > 1) {
        cerr << "Error: program <" << argv[1] << "> doesn't exist." << endl;
        exit(EXIT_FAILURE);
    }
    inFile.close();

}//End of binary_mode() function.

void validation(char* argv[]) {

    if (strcmp(argv[1], "--version") == 0)
        cout << versionNumber << endl;
    else if (strcmp(argv[1], "--help") == 0)
        output_help();
    else if (strcmp(argv[1], "-t") == 0 || strcmp(argv[1], "-b") == 0) {
        cout << "Error: no input file specified." << endl;
        exit(EXIT_FAILURE);
    }
    else if (strncmp(argv[1], "-tt", 3) == 0 || strncmp(argv[1], "-bb", 3) == 0) {
        cout << "Error: duplicate switches: <" << argv[1][1] << ">" << endl;
        exit(EXIT_FAILURE);
    }
    else if (strncmp(argv[1], "-tb", 3) == 0 || strncmp(argv[1], "-bt", 3) == 0) {
        cout << "Error: cannot use both -b and -t" << endl;
        exit(EXIT_FAILURE);
    }
    else if (argv[1][0] == '-' && argv[1][1] == '-') {
        cout << "Error: bad switch <" << argv[1] << ">" << endl;
        exit(EXIT_FAILURE);
    }
    else {
        cout << "Error: unknown switches: <" << argv[1][1] << ">" << endl;
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}//End of validation() function.