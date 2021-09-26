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

    // create a file for error messages
    char path[14] = "errorFile.txt";
    QString errorFilePath = getFileLocation(path);
    QStringList string;
    QFile errorFile("errorFile.txt");

    if (argc < 3) // when one or both files are not provided
    {
        string.append("Insufficient arguments. Please provide all the files.");

        writeOutput(errorFilePath, string); // write error message to the error file
        errorFile.close(); //close error file
        return 0; // end the program execution
    }
    if (argc > 3) // when two many aruments were provided
    {
        string.append("Too many files provided");

        writeOutput(errorFilePath, string); // write error message to the error file
        errorFile.close(); //close error file
        return 0; // end the program execution
    }

    QString templateFilePath = getFileLocation(argv[1]); // get the location of file with the email template
    QString dataFilePath = getFileLocation(argv[2]); // get the location of file with the data

    // try getting the composition of the files
    try {

        //-------------------------------If no error occured----------------------------------------
        temp = getFileData(templateFilePath); // save the composition of template file
        data = getFileData(dataFilePath); // save the composition of data file

        for(int i=0; i < data.size(); i++) // for each of data in data file
        {
            //-------create a file name "genarated(s)" where 's' is the number of generated files---------
            QString s = QString::number(i+1);

            QString out = "generated";
            out.append(s);
            out.append(".txt");


            QByteArray ba = out.toLocal8Bit();
            char *outp = ba.data();

            //-------create an output file with the created file name---------
            QString outputFilePath = getFileLocation(outp);
            QFile outputFile(outputFilePath);

            // take a current line of the data file
            QStringList singleData;
            singleData.append(data[i]);

            // try generatingg email for the current line of the data file from the template given
            try {
                // save the generated email if no error occured
                generated = generateEmail(temp, singleData);
            } catch (int err) {

                //------write an error message to thhe error file if an error occured--------
                string.append("A value for key was found in the data list that is not included in the template.");

                writeOutput(errorFilePath, string);
                errorFile.close(); // close the erro file
                return 0; // end program execution
            }

            writeOutput(outputFilePath, generated); // write the generated email to the created output file
            out.clear(); // clear the created file name to create a new one for the next email to be generated

        }

    } catch (int err) {
    //------write an error message to thhe error file if an error occured an end the program execution--------
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
