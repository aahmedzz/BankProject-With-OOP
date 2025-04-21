#pragma once
#include <string>
#include <iostream>
#include<vector>
using namespace std;

enum TrimType { leftTrim, rightTrim, BothSides };

class clsString
{
private:
    string _value;
    static char InvertCharCase(char character) {
        //short asciichar= toascii(character);
        //if (asciichar >= 97 && asciichar <= 122)
        //	return char(asciichar - 32);
        //else if (asciichar >= 65 && asciichar <= 90)
        //	return char(asciichar + 32);
        return isupper(character) ? tolower(character) : toupper(character);
    }
public:
    clsString() {
        _value = "";
    }
    clsString(string value) {
        _value = value;
    }

    void setValue(string value) {
        _value = value;
    }
    string getValue() {
        return _value;
    }
    __declspec(property(get = getValue, put = setValue)) string value;

    //split Methods
    static vector<string> SplitString(string S1, string Delim)
    {
        vector<string> vString;
        short pos = 0;
        string sWord; // define a string variable
        // use find() function to get the position of the delimiters
        while ((pos = S1.find(Delim)) != std::string::npos)
        {
            sWord = S1.substr(0, pos); // store the word
            if (sWord != "")
            {
                vString.push_back(sWord);
            }
            S1.erase(0, pos + Delim.length());
        }
        if (S1 != "")
        {
            vString.push_back(S1); // it adds last word of the string.
        }
        return vString;
    }
    vector<string> SplitString(string Delim) {
        return SplitString(_value, Delim);
    }

    // PrintFirstCharInWord methods
    static void PrintFirstCharInWord(string sentence) {
        cout << "The First letter in each word: \n";
        cout << sentence[0] << "\n";
        for (int i = 0; i < sentence.length(); i++) {
            if (sentence[i] == ' ') {
                cout << sentence[i + 1] << "\n";
            }
        }
    }
    void PrintFirstCharInWord() {
        PrintFirstCharInWord(_value);
    }

    // UpperCaseFirstCharInWord methods
    static string UpperCaseFirstCharInWord(string sentence) {
        sentence[0] = toupper(sentence[0]);
        for (int i = 0; i < sentence.length(); i++) {
            if (sentence[i] == ' ') {
                sentence[i + 1] = toupper(sentence[i + 1]);
            }
        }
        return sentence;
    }
    void UpperCaseFirstCharInWord() {
        _value = UpperCaseFirstCharInWord(_value);
    }

    // InvertStringChars methods
    static string InvertStringChars(string sentence) {
        for (short i = 0; i < sentence.length(); i++) {
            sentence[i] = InvertCharCase(sentence[i]);
        }
        return sentence;
    }
    void InvertStringChars() {
        _value = InvertStringChars(_value);
    }

    // PrintStringDetails methods
    static void PrintStringDetails(string sentence) {
        int upperCount = 0, lowerCount = 0;
        for (short i = 0; i < sentence.length(); i++) {
            if (isupper(sentence[i])) upperCount++;
            else if (islower(sentence[i])) lowerCount++;
        }
        cout << "\nString Length: " << sentence.length() << endl;
        cout << "Upper case letters count: " << upperCount << endl;
        cout << "Lower case letters count: " << lowerCount << endl;
    }
    void PrintStringDetails() {
        PrintStringDetails(_value);
    }

    // PrintWordsInString methods
    static void PrintWordsInString(string sentence) {
        string word = "";
        cout << "Words in the sentence: \n";
        for (int i = 0; i < sentence.length(); i++) {
            if (sentence[i] == ' ') {
                cout << word << "\n";
                word = "";
                continue;
            }
            word += sentence[i];
        }
        cout << word << endl;
    }
    void PrintWordsInString() {
        PrintWordsInString(_value);
    }

    // Trim methods
    static string TrimLeft(string sentence) {
        for (int i = 0; i < sentence.length(); i++) {
            if (sentence[i] != ' ') {
                sentence = sentence.substr(i);
                break;
            }
        }
        return sentence;
    }
    string TrimLeft() {
        return TrimLeft(_value);
    }
    static string TrimRight(string sentence) {
        for (int i = sentence.length() - 1; i >= 0; i--) {
            if (sentence[i] != ' ') {
                sentence = sentence.substr(0, i + 1);
                break;
            }
        }
        return sentence;
    }
    string TrimRight() {
        return TrimRight(_value);
    }
    static string TrimString(string sentence, TrimType trimType) {
        if (trimType == TrimType::leftTrim) {
            sentence = TrimLeft(sentence);
        }
        else if (trimType == TrimType::rightTrim) {
            sentence = TrimRight(sentence);
        }
        else if (trimType == TrimType::BothSides) {
            sentence = TrimLeft(TrimRight(sentence));
        }
        return sentence;
    }
    string TrimString(TrimType trimType) {
        _value = TrimString(_value, trimType);
        return _value;
    }

    // JoinString methods
    static string JoinString(vector<string> strings, string delim) {
        string str;
        for (string& s : strings) {
            str = str + s + delim;
        }
        return str.substr(0, str.length() - delim.length());
    }

    // ReverseString methods
    static string ReverseString(string sentence) {
        vector<string> words = SplitString(sentence, " ");
        string str = "";
        for (int i = words.size() - 1; i >= 0; i--) {
            str = str + words[i] + " ";
        }
        return str.substr(0, str.length() - 1); // Remove the trailing space
    }
    string ReverseString() {
        _value = ReverseString(_value);
        return _value;
    }

    // LowerAllString methods
    static string LowerAllString(string S1) {
        for (short i = 0; i < S1.length(); i++) {
            S1[i] = tolower(S1[i]);
        }
        return S1;
    }
    string LowerAllString() {
        _value = LowerAllString(_value);
        return _value;
    }

    // UpperAllString methods
    static string UpperAllString(string S1) {
        for (short i = 0; i < S1.length(); i++) {
            S1[i] = toupper(S1[i]);
        }
        return S1;
    }
    string UpperAllString() {
        _value = UpperAllString(_value);
        return _value;
    }

    // ReplaceWords methods
    static string ReplaceWords(string sentence, string oldWord, string newWord) {
        string str = "";
        vector<string> words = SplitString(sentence, " ");
        for (string& word : words) {
            if (LowerAllString(word) == LowerAllString(oldWord)) {
                word = newWord;
            }
            str = str + word + " ";
        }
        return str.substr(0, str.length() - 1); // Remove the trailing space
    }
    string ReplaceWords(string oldWord, string newWord) {
        _value = ReplaceWords(_value, oldWord, newWord);
        return _value;
    }

    // RemovePuncts methods
    static string RemovePuncts(string sentence) {
        string str = "";
        for (int i = 0; i < sentence.length(); i++) {
            if (!ispunct(sentence[i])) {
                str += sentence[i];
            }
        }
        return str;
    }
    string RemovePuncts() {
        _value = RemovePuncts(_value);
        return _value;
    }
};

