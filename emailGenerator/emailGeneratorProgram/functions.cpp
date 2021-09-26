#include "functions.h"
#include <QTextStream>

void writeOutput(QString filePath, QStringList lines)
{
    QFile outputFile(filePath); // create an output file

    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) // open the created file
    {
        QTextStream stream(&outputFile);

        for (int i = 0; i < lines.length(); i++) // for each line of the texts
            stream << lines[i] << endl; // write the line to the output file
        outputFile.close(); // close the output file
    }
}

QString getFileLocation(char* path)
{
    QString result(path);

    if (result.contains(R"(\)"))
        result.replace(R"(\)", R"(/)");

    if (result.startsWith(QChar('.')))
        result = QDir::currentPath() + result.mid(1);

    return result;
}


QStringList getFileData(QString filePath) throw(int)
{
    QStringList string;
    QFile inputFile(filePath);

    if (!inputFile.exists())
    {
        throw 1;
    }
    else
    {
        if (inputFile.open(QIODevice::ReadOnly))
        {
            QTextStream in(&inputFile);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                string.append(line);
            }
            inputFile.close();
        }
        else
        {
            throw 3;
        }
    }
    return string;
}

QStringList generateEmail(QStringList temp, QStringList data) throw (int)
{
    QStringList generated = temp; // savee the given template
    bool isFound = false; // set key found to false

    QStringList dataList = data[0].split(" "); // split the data line with space to seperate key and its value

      for(int i = 0; i < dataList.size(); i++) // for each of the words of the splited data
       {
         for(int j=0; j < generated.size(); j++) // for each line of the given templated
         {
           if (generated[j].contains(dataList[i])) // if the line of the template contains the current key of the data
           {
           //replace the key in the template file with the next word of the data (the value of the key)
               generated[j].replace(dataList[i], dataList[i+1].replace(R"(_)", R"( )"));
               isFound = true; // set key found to true
           }
         }

         i += 1; // skip to the next key
         if(isFound == false) // throw an error if the key from the data list is not found in the tempalte
         {
             throw 1;
         }
         isFound = false;
       }

    return generated; // return the generated email for the given data
}
