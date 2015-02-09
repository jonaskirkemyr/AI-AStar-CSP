#include "fileParse.h"
//#include "models/file/StringSplit.h"

bool FileParse::isFileOpen()
{
    return file->is_open();
}



FileParse::FileParse(int i)
{
    maxSize=i;
    adderSize=0;

    delimiter=" ";
    subDelimiter=",";

    file=new ifstream;
}

FileParse::~FileParse()
{
    file->close();
    delete file;
    file=nullptr;

    //delete[] adder;
    //adder=nullptr;
}

bool FileParse::openFile(string file)
{
    try
    {
        if(isFileOpen())
        {
            this->file->close();//close file before trying to open new
			this->adderSize=0;
			reset();
            cout<<"A file is already open. Closing file...\n";
        }

       //cout<<"opening file..."<<endl;
        this->file->open(file,ifstream::in);

        if(isFileOpen())
            cout<<"File '"<<file<<"' opened"<<endl;
        else
            cout<<"Couldn't open file. Please check filname and try again"<<endl;

    }
    catch(ifstream::failure e)
    {
        cerr<<"Couldn't open file. Please check filename and try again\n";
    }

    return isFileOpen();
}

bool FileParse::readFile()
{//http://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
    //don't want to try reading from a file that isn't open
    if(!isFileOpen())
        return false;

    string line;

    while(!file->eof())
    {

        if(adderSize>=maxSize)
            increase();//increase the map size if maxsize reached

        getline(*file,line);

        size_t pos=0;
        size_t findPos=0;

        vector<string> split_line;
        Split::splitString(line,split_line,delimiter);

        readDelimiter(split_line);


        //maps[mapSize]

        
        ++adderSize;
    }
    return true;
}

const string &FileParse::getDelimiter() const
{
    return delimiter;

}
const string &FileParse::getSubDelimiter() const
{
    return subDelimiter;
}

void FileParse::setDelimiter(const string& d)
{
    delimiter=d;
}

void FileParse::setSubDelimiter(const string& d)
{
    subDelimiter=d;
}

int FileParse::getSize()
{
    return adderSize;
}

int FileParse::getMaxSize()
{
    return maxSize;
}

void FileParse::setSize(int i)
{
	adderSize=i;
}

void FileParse::setMaxSize(int i)
{
    maxSize=i;
}



