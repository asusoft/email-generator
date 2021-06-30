#include "functions.h"
#include <QTextStream>

void writeOutput(QString filePath, QStringList lines)
{
    QFile outputFile(filePath);

    if (outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&outputFile);

        for (int i = 0; i < lines.length(); i++)
            stream << lines[i] << endl;
        outputFile.close();
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
    QStringList generated = temp;
    bool isFound = false;
    QStringList dataList = data[0].split(" ");

      for(int i = 0; i < dataList.size(); i++)
       {

         for(int j=0; j < generated.size(); j++)
         {
           if (generated[j].contains(dataList[i]))
           {
               generated[j].replace(dataList[i], dataList[i+1].replace(R"(_)", R"( )"));
               isFound = true;
           }
         }

         i += 1;
         if(isFound == false)
         {
             throw 1;
         }
         isFound = false;
       }

    return generated;
}
