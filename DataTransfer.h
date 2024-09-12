#ifndef DATATRANSFER_H
#define DATATRANSFER_H

#include <memory>
#include <QString>

class DataTransfer
{
    DataTransfer()
    {
        newListAdded=false;
        listDeleted=false;
    }

    static std::unique_ptr<DataTransfer> instance;

public:
    DataTransfer(const DataTransfer& dt)=delete;
    DataTransfer(const DataTransfer&& dt)=delete;
    DataTransfer& operator=(const DataTransfer&) = delete;

    static DataTransfer& getInstance(){
        if (instance == nullptr) {
            instance = std::unique_ptr<DataTransfer>(new DataTransfer());
        }
        return *instance;
    }



    //Data
    bool newListAdded;

    QString currentListName;
    QString currentListLanguageOneName;
    QString currentListLanguageTwoName;


    bool listDeleted;


};



#endif // DATATRANSFER_H
