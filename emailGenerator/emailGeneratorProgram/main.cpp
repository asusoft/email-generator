#include <QtCore/QCoreApplication>
#include <conio.h>
#include <QTextStream>
#include <QFile>
#include <QDebug>
#include <iostream>
#include <QDir>
#include "functions.h"

int main(int argc, char* argv[])
{
    QCoreApplication a(argc, argv);
    QStringList error;
    QStringList temp;
    QStringList data;
    QStringList generated;
    QStringList input;

    char path[14] = "errorFile.txt";
    QString errorFilePath = getFileLocation(path);
    QStringList string;
    QFile errorFile("errorFile.txt");

    if (argc < 3)
    {
        string.append("Insufficient arguments. Please provide all the files.");

        writeOutput(errorFilePath, string);
        errorFile.close();
        return 0;
    }
    if (argc > 3)
    {
        string.append("Too many files provided");

        writeOutput(errorFilePath, string);
        errorFile.close();
        return 0;
    }

    QString templateFilePath = getFileLocation(argv[1]);
    QString dataFilePath = getFileLocation(argv[2]);

    try {
        temp = getFileData(templateFilePath);
        data = getFileData(dataFilePath);

        for(int i=0; i < data.size(); i++)
        {
            QString s = QString::number(i+1);

            QString out = "generated";
            out.append(s);
            out.append(".txt");


            QByteArray ba = out.toLocal8Bit();
            char *outp = ba.data();

            QString outputFilePath = getFileLocation(outp);
            QFile outputFile(outputFilePath);

            QStringList singleData;
            singleData.append(data[i]);

            try {
                generated = generateEmail(temp, singleData);
            } catch (int err) {
                string.append("A value for key was found in the data list that is not included in the template.");

                writeOutput(errorFilePath, string);
                errorFile.close();
                return 0;
            }

            writeOutput(outputFilePath, generated);
            out.clear();

        }

    } catch (int err) {
        switch (err)
        {
        case 1:
            string.append("One or both of the files cannot be found.");
            writeOutput(errorFilePath, string);

            return 0;
        case 2:
            string.append("Line inputed incorrectly!!!");
            writeOutput(errorFilePath, string);

            return 0;
        }
        return 0;
    }
}
