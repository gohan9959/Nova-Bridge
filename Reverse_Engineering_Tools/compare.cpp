#include <fstream>
#include <string>
#include <vector>
std::vector<std::string> readLines(const std::string& filename)
{
    std::vector<std::string> lines;
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }
    else
    {
        printf("Could not open file: %s\n", filename.c_str());
    }
    return lines;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: compare file1.txt file2.txt\n");
        return 1;
    }
    else{
        std::vector<std::string> file1Lines = readLines(argv[1]);
        std::vector<std::string> file2Lines = readLines(argv[2]);

        for(size_t i = 0; i < file1Lines.size(); ++i)
        {
            for(size_t j = 0; j < file2Lines.size(); ++j)
            {
                if(file1Lines[i] == file2Lines[j])
                {
                    printf(file1Lines[i].c_str());
                    printf("\n");
                }
            }
        }
        return 0;
        
    }
    
}