#include "auto_complete_read_line.h"

#include <QTextStream>

#ifdef _WIN32
#include <Windows.h>
#undef max
#undef min
#include <conio.h>
#endif

AutoCompleteReadLine::AutoCompleteReadLine(QObject *parent) : QObject(parent)
{

}

QString AutoCompleteReadLine::ReadLine()
{
    QTextStream text_stream(stdin);
    return text_stream.readLine();

#ifdef _WIN32

#else
    return {};
#endif
}
