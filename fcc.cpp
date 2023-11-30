#include <fstream>
#include <iostream>
#include <vector>



bool more_to_read(std::ifstream &file) {
  file >> std::noskipws;
  while (file.peek() == ' ') {
    char discard;
    file >> discard;
  }
  return !(file.eof() || std::iscntrl(file.peek()));
}

//Will return a vector from an open file
std::vector<std::string> library_vector(std::ifstream &file_library) {
             

       std::vector<std::string> library_vector; 

       if (!file_library.is_open()) {
           //will return empty vector
           return library_vector;
       }

       std::string library;

       while (more_to_read(file_library)) {
           std::string word{};
           file_library >> word;
           library_vector.push_back(word);
       }
       
        return library_vector;
}
//Will return the number of times there was an error fixed but also fixes
//all of the typos in the fixme_file
int fixed_fixme_filename(std::vector<std::string> typo_file,std::vector<std::string> &fixme_file, std::vector<std::string> fixo_file) {

    int fixo_fixed_counter{ 0 };

    for (int i = 0; i < fixme_file.size(); i++) {
        auto word_index = fixme_file[i];
        for (int x = 0; x < typo_file.size(); x++) {
            if (typo_file[x] == fixme_file[i]) {
                fixme_file[i] = fixo_file[x];
                fixo_fixed_counter++;
            }
        }
    }
    return fixo_fixed_counter;
}
    

int fcc(const std::string &fixme_filename, const std::string &typo_filename,
        const std::string &fixo_filename, std::string &fixed_sentence) {


    //Calling in the files to open:
    std::ifstream fixme_file_open{};
    fixme_file_open.open(fixme_filename);

    std::ifstream typo_file_open{};
    typo_file_open.open(typo_filename);

    std::ifstream fixo_file_open{};
    fixo_file_open.open(fixo_filename);


    //The files are turned into vectors:
    std::vector<std::string> fixme_library = library_vector(fixme_file_open);
    std::vector<std::string> typo_library = library_vector(typo_file_open);
    std::vector<std::string> fixo_library = library_vector(fixo_file_open);

    if (!(fixo_library.size() == typo_library.size())) {
        return -1;
    }

    //Amount of words fixed and fixes the fixme_library vector, this will be returned by the function:
    int fixed_amount = fixed_fixme_filename(typo_library, fixme_library, fixo_library);


    //Turns the fixme vector back into a string:
    fixed_sentence = { " " };
    for (int i = 0; i < fixme_library.size(); i++) {
        if (fixed_sentence == " ") {
            fixed_sentence = fixme_library[i];
        }
        else {
            fixed_sentence += " " + fixme_library[i];
        }
    }
    if (!(fixed_sentence == " ")) {
        fixed_sentence += ".";
    }
 
    return fixed_amount;
}
