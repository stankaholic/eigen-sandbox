#include <fstream>
#include <sstream>
#include <string>
#include "NeuralNetwork/NeuralNetwork.hpp"
#include "Eigen/Dense"
#include <cctype>
#include <stdlib.h>
 
using Eigen::MatrixXd;

typedef std::vector<RowVector*> data_type;

void ReadCSV(std::string filename, data_type& data)
{
    data.clear();
    std::ifstream file(filename);
    std::string line, word;
    // determine number of columns in file
    getline(file, line, '\n');
    std::stringstream ss(line);
    std::vector<Scalar> parsed_vec;

    while (getline(ss, word, ',')) {
        parsed_vec.push_back(Scalar(std::stof(&word[0])));
    }
    unsigned long cols = parsed_vec.size();
    data.push_back(new RowVector(cols));
    for (uint i = 0; i < cols; i++) {
        data.back()->coeffRef(i) = parsed_vec[i];
    }

    // read the file
    if (file.is_open()) {
        while (getline(file, line, '\n')) {
            std::stringstream ss(line);
            data.push_back(new RowVector(1, cols));
            uint i = 0;
            while (getline(ss, word, ',')) {
                data.back()->coeffRef(i) = Scalar(std::stof(&word[0]));
                i++;
            }
        }
    }
}

std::string itos(uint value)
{
    std::string returnString;
    while (value)
    {
        uint digit = value % 10;
        std::string::value_type digitString;
        switch (digit)
        {
            case 0:
                digitString = '0';
                break;
            case 1:
                digitString = '1';
                break;
            case 2:
                digitString = '2';
                break;
            case 3:
                digitString = '3';
                break;
            case 4:
                digitString = '4';
                break;
            case 5:
                digitString = '5';
                break;
            case 6:
                digitString = '6';
                break;
            case 7:
                digitString = '7';
                break;
            case 8:
                digitString = '8';
                break;
            case 9:
                digitString = '9';
                break;
            default:
                digitString = ' ';
                break;
        }
        returnString.insert(returnString.cbegin(), digitString);
        value /= 10;
    }
    return returnString;
}

void genData(std::string filename, uint numberOfLines)
{
    std::ofstream file1(filename);
    std::stringstream line;

    for (uint i = 1; i < 70; ++i)
    {
        line << itos(i) << ",";
    }

    for (uint j = 0; j < numberOfLines; ++j) {
        file1 << line.str() << std::endl;
    }

    file1.close();
}

uint convertToCSV(std::string filename_in, std::string filename_out)
{
    std::ifstream raw_data(filename_in);
    std::ofstream csv_data(filename_out);

    std::string line;
    uint numOfLines = 0;
    bool toggle = false;

    while(getline(raw_data, line, '\n'))
    {
        if(isdigit(line[0]))
        {
            csv_data << line << ",";
            toggle = true;
        }
        else if (toggle)
        {
            csv_data << std::endl;
            ++numOfLines;
            toggle = false;
        }
    }

    return numOfLines;
}

int main()
{
    NeuralNetwork n({ 2, 3, 1 });
    data_type in_dat, out_dat;
    genData("data-in.csv", convertToCSV("raw_data", "data-out.csv"));
    ReadCSV("data-in", in_dat);
    ReadCSV("data-out", out_dat);
    //n.train(in_dat, out_dat);
    return 0;
}
