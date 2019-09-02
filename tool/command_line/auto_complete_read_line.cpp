#include "auto_complete_read_line.h"

#include <QTextStream>

#if defined(_WIN32) && !defined(USED_DEFAULT_READLINE)
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

#if defined(_WIN32) && !defined(USED_DEFAULT_READLINE)

#else
    QTextStream text_stream(stdin);
    return text_stream.readLine();
#endif
}
