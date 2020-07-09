#include "log2.h"

Log4TextBrowser::Log4TextBrowser()
{

}

void Log4TextBrowser::append(QString str)
{
    printf("%s\n", str.toUtf8().data());
    fflush(stdout);
    if(this->tb){
        tb->append(str);
    }
}

void Log4TextBrowser::setTextBrowser(QTextBrowser *textBrowser)
{
    this->tb = textBrowser;
    logDebug() << "sfdfs";
}
