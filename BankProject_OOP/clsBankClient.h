#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<fstream>
#include "clsString.h"
#include "clsPerson.h"
using namespace std;

class clsBankClient: public clsPerson
{
	private:
		enum enMode{EmptyMode = 0,UpdateMode =1,AddMode=2};
		enMode _Mode;

		string _AccountNumber;
		string _PinCode;
		float _AccountBalance;
        bool _MarkedForDelete = false;

        static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
        {
            vector<string> vClientData;
            vClientData = clsString::SplitString(Line, Seperator);

            return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
                vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

        }

        static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
        {

            string stClientRecord = "";
            stClientRecord += Client.FirstName + Seperator;
            stClientRecord += Client.LastName + Seperator;
            stClientRecord += Client.Email + Seperator;
            stClientRecord += Client.Phone + Seperator;
            stClientRecord += Client.AccountNumber() + Seperator;
            stClientRecord += Client.PinCode + Seperator;
            stClientRecord += to_string(Client.AccountBalance);

            return stClientRecord;
        }

        static clsBankClient _GetEmptyClientObject()
        {
            return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
        }

        static  vector <clsBankClient> _LoadClientsDataFromFile()
        {

            vector <clsBankClient> vClients;

            fstream MyFile;
            MyFile.open("Clients.txt", ios::in);//read Mode

            if (MyFile.is_open())
            {

                string Line;


                while (getline(MyFile, Line))
                {
                    if (Line == "")
                        continue;

                    clsBankClient Client = _ConvertLinetoClientObject(Line);

                    vClients.push_back(Client);
                }

                MyFile.close();

            }

            return vClients;

        }

        static void _SaveCleintsDataToFile(vector <clsBankClient> vClients)
        {

            fstream MyFile;
            MyFile.open("Clients.txt", ios::out);//overwrite

            string DataLine;

            if (MyFile.is_open())
            {

                for (clsBankClient C : vClients)
                {
                    if (C.MarkedForDeleted() == false)
                    {
                        //we only write records that are not marked for delete.  
                        DataLine = _ConverClientObjectToLine(C);
                        MyFile << DataLine << endl;

                    }

                }

                MyFile.close();

            }

        }

        void _Update() {
            vector<clsBankClient> clients = _LoadClientsDataFromFile();
            for (clsBankClient& client : clients) {
                if (client.AccountNumber() == this->AccountNumber()) {
                    client = *this;
                    break;
                }
            }
            _SaveCleintsDataToFile(clients);
        }

        void _AddNew()
        {

            _AddDataLineToFile(_ConverClientObjectToLine(*this));
        }

        void _AddDataLineToFile(string  stDataLine)
        {
            fstream MyFile;
            MyFile.open("Clients.txt", ios::out | ios::app);

            if (MyFile.is_open())
            {

                MyFile << stDataLine << endl;

                MyFile.close();
            }

        }

        string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
            string UserName, string Seperator = "#//#")
        {
            string TransferLogRecord = "";
            TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
            TransferLogRecord += AccountNumber() + Seperator;
            TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
            TransferLogRecord += to_string(Amount) + Seperator;
            TransferLogRecord += to_string(AccountBalance) + Seperator;
            TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
            TransferLogRecord += UserName;
            return TransferLogRecord;
        }

        void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
        {

            string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

            fstream MyFile;
            MyFile.open("TransferLog.txt", ios::out | ios::app);

            if (MyFile.is_open())
            {

                MyFile << stDataLine << endl;

                MyFile.close();
            }

        }

        struct stTrnsferLogRecord;
        static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
        {
            stTrnsferLogRecord TrnsferLogRecord;

            vector <string> vTrnsferLogRecordLine = clsString::SplitString(Line, Seperator);
            TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
            TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
            TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
            TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
            TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
            TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
            TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

            return TrnsferLogRecord;
        }

	public:
        struct stTrnsferLogRecord
        {
            string DateTime;
            string SourceAccountNumber;
            string DestinationAccountNumber;
            float Amount;
            float srcBalanceAfter;
            float destBalanceAfter;
            string UserName;

        };

        clsBankClient(enMode Mode, string FirstName, string LastName,
            string Email, string Phone, string AccountNumber, string PinCode,float AccountBalance) 
            : clsPerson(FirstName, LastName, Email, Phone)
        {
            _Mode = Mode;
            _AccountNumber = AccountNumber;
            _PinCode = PinCode;
            _AccountBalance = AccountBalance;

        }

        bool IsEmpty()
        {
            return (_Mode == enMode::EmptyMode);
        }

        bool MarkedForDeleted()
        {
            return _MarkedForDelete;
        }

        string AccountNumber()
        {
            return _AccountNumber;
        }

        void SetPinCode(string PinCode)
        {
            _PinCode = PinCode;
        }
        string GetPinCode()
        {
            return _PinCode;
        }
        __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

        void SetAccountBalance(float AccountBalance)
        {
            _AccountBalance = AccountBalance;
        }
        float GetAccountBalance()
        {
            return _AccountBalance;
        }
        __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


        static clsBankClient Find(string AccountNumber) {
            fstream MyFile;
            MyFile.open("Clients.txt", ios::in);
            if (MyFile.is_open()) {
                string line;
                while (getline(MyFile, line)) {
                    clsBankClient Client = _ConvertLinetoClientObject(line);
                    if (Client.AccountNumber() == AccountNumber)
                    {
                        MyFile.close();
                        return Client;
                    }
                }
                MyFile.close();
            }
            return _GetEmptyClientObject();
        }
        static clsBankClient Find(string AccountNumber,string pincode) {
            fstream MyFile;
            MyFile.open("Clients.txt", ios::in);
            if (MyFile.is_open()) {
                string line;
                while (getline(MyFile, line)) {
                    clsBankClient Client = _ConvertLinetoClientObject(line);
                    if (Client.AccountNumber() == AccountNumber && Client.PinCode == pincode)
                    {
                        MyFile.close();
                        return Client;
                    }
                }
                MyFile.close();
            }
            return _GetEmptyClientObject();
        }
        static clsBankClient GetAddNewClientObject(string AccountNumber) {
            return clsBankClient(enMode::AddMode,"","","","",AccountNumber,"",0);
        }

        enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2};
        enSaveResults Save()
        {
            switch (this->_Mode)
            {
                case enMode::EmptyMode:
                {
                    return enSaveResults::svFaildEmptyObject;
                }
                case enMode::UpdateMode:
                {
                    _Update();
                    return enSaveResults::svSucceeded;
                    break;
                }
                case enMode::AddMode:
                {
                    if (clsBankClient::IsClientExist(_AccountNumber))
                    {
                        return enSaveResults::svFaildAccountNumberExists;
                    }
                    else 
                    {
                        _AddNew();
                        this->_Mode = enMode::UpdateMode;
                        return enSaveResults::svSucceeded;
                    }
                }
            }
        }

        bool Delete()
        {
            vector<clsBankClient> clients = _LoadClientsDataFromFile();
            for (clsBankClient& client : clients) {
                if (client.AccountNumber() == this->AccountNumber())
                {
                    client._MarkedForDelete = true;
                    break;
                }
            }
             _SaveCleintsDataToFile(clients);
             *this = _GetEmptyClientObject();
             return true;
        }

        static vector<clsBankClient> GetClientsList() {
            return _LoadClientsDataFromFile();
        }

        static double GetTotalBalances() {
            double TotalBalance = 0;
            vector<clsBankClient> clients = _LoadClientsDataFromFile();
            for (clsBankClient& client : clients) {
                TotalBalance += client.AccountBalance;
            }
            return TotalBalance;
        }

        static bool IsClientExist(string AccountNumber) {
            clsBankClient client = Find(AccountNumber);
            return (!client.IsEmpty());
        }

        void Deposit(double amount) {
            this->AccountBalance += amount;
            this->Save();
        }

        bool Withdraw(double amount) {
            if (amount > this->AccountBalance) {
                return false;
            }
            else
            {
                this->AccountBalance -= amount;
                this->Save();
                return true;
            }
        }

        bool Transfer(float Amount, clsBankClient DestinationClient,string UserName) {
            if (this->AccountBalance < Amount) {
                return false;
            }
            else
            {
                this->Withdraw(Amount);
                DestinationClient.Deposit(Amount);
                _RegisterTransferLog(Amount,DestinationClient,UserName);
                return true;
            }
        }

        static  vector <stTrnsferLogRecord> GetTransfersLogList()
        {
            vector <stTrnsferLogRecord> vTransferLogRecord;

            fstream MyFile;
            MyFile.open("TransferLog.txt", ios::in);//read Mode
            if (MyFile.is_open())
            {
                string Line;
                stTrnsferLogRecord TransferRecord;

                while (getline(MyFile, Line))
                {
                    TransferRecord = _ConvertTransferLogLineToRecord(Line);
                    vTransferLogRecord.push_back(TransferRecord);
                }
                MyFile.close();
            }

            return vTransferLogRecord;
        }

};

