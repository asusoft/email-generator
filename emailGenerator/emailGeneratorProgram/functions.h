#include <QDir>

/*! Writes output data
  \param[in] filePath file to write in
  \param[in] lines lines of output data
*/
void writeOutput(QString filePath, QStringList lines);

/// <summary>
/// Gets the absolute path to a file
/// <param name="path">absolute path to the file</param>
/// </summary>
QString getFileLocation(char* path);

/*! Gets all data in a file
\param[in] file file to be read
\throw error while reading file
\return lines lines of the file
*/
QStringList getFileData(QString filePath) throw(int);

/// <summary>
/// Generates an email using given data
/// <param name="temp">Email template to use</param>
/// <param name="data">Data to create eamil for</param>
/// </summary>
QStringList generateEmail(QStringList temp, QStringList data)throw (int);
