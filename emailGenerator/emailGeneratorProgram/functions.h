#include <QDir>

void writeOutput(QString filePath, QStringList lines);

QString getFileLocation(char* path);

QStringList getFileData(QString filePath) throw(int);


QStringList generateEmail(QStringList temp, QStringList data);
