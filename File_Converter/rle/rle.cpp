//ENCODER

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

string versionNumber = "1.0.1";

//Functions headers.
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
    cout << "rle (c) 2020, Hashem Abou Ahmad\n";
    cout << "===========================================================\n";
    cout << "Version " << versionNumber << "\n\n";
    cout << "A run-length encoder utility.\n\n";
    cout << "Usage: rle [-(b|t)] [--help] [--version] infile [outfile]\n\n";
    cout << "Examples:\n";
    cout << "  rle myfile.doc\n";
    cout << "    > encodes 'myfile.doc' to 'myfile.doc.rlet' (text mode)\n\n";
    cout << "  rle -b ..\\myfile.doc\n";
    cout << "    > encodes 'myfile.doc' from the parent folder to 'myfile.doc.rleb' (binary mode) in the current folder\n\n";
    cout << "  rle -t myfile.doc ec.text\n";
    cout << "    > encodes 'myfile.doc' from the parent folder to 'ec.text' in the local folder (text mode)\n\n";
    cout << "  rle -b myfile.doc ec.bin\n";
    cout << "    > encodes 'myfile.doc' from the parent folder to 'ec.bin' in the local folder (binary mode)\n\n";
    cout << "  rle --help\n";
    cout << "    > displays the help\n\n";
    cout << "  rle --version\n";
    cout << "    > displays version number in the format d.d.d\n\n";
}//End of output_help() function.

void text_mode(int argc, char* argv[], bool switchIncluded) {

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
        if (argc == 2 || (argc == 3 && switchIncluded == true))
            outFile.open(outFileName + ".rlet");
        else if (argc == 3 && switchIncluded == false || (argc == 4 && switchIncluded == true))
            outFile.open(outFileName);

        vector<int> data;
        char token;
        while (inFile.get(token))
            data.push_back((unsigned char)token);
        data.push_back('\0');

        unsigned int count = 1;

        for (size_t i = 0; i < data.size() - 1; ++i) {

            size_t j = i + 1;
            if (data[i] == data[j] && j != data.size() - 1)
                ++count;
            else {
                outFile << count << ' ' << data[i] << endl;
                count = 1;
            }

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

    if (argc != 4 && switchIncluded == false) //rle.exe filename.txt desiredName.txt
        inFile.open(argv[1], ios::binary);
    else if (argc == 3 && switchIncluded == true) //rle.exe -t filename.txt 
        inFile.open(argv[2], ios::binary);
    else
        inFile.open(argv[2], ios::binary); //rle.exe -t filename.txt desiredName.txt

    if (inFile.good()) {
        string outFileName = argv[argc - 1];
        ofstream outFile;
        if (argc == 2 || (argc == 3 && switchIncluded == true))
            outFile.open(outFileName + ".rleb", ios::binary);
        else if (argc == 3 && switchIncluded == false || (argc == 4 && switchIncluded == true))
            outFile.open(outFileName, ios::binary);

        char token = '\0';
        char otherTokens = '\0';
        streamsize buffer = 1;

        inFile.get(token);
        while (!inFile.eof()) {
            inFile.get(otherTokens);
            if (inFile.eof()) {
                outFile.write((char*)&buffer, sizeof(buffer));
                outFile.write((char*)&token, sizeof(token));

                break;
            }
            if (token == otherTokens)
                ++buffer;
            else {
                outFile.write((char*)&buffer, sizeof(buffer));
                outFile.write((char*)&token, sizeof(token));
                buffer = 1;
                token = otherTokens;
            }
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