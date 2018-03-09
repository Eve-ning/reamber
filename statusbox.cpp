#include "statusbox.h"

namespace STATUSBOX
{
/* Redacted
void sendIndex(QTextBrowser *tb, int messageIndex){
    tb->append(statusList[messageIndex] + "\n");
    return;
}
*/

void sendMsg(QTextBrowser *tb, QString message, QString tag){
    if (tag != "")
    {
        tb->append("[" + tag + "] ");
    }
    tb->append(message + "\n");
    return;
}

void sendMsg(QTextBrowser *tb, QStringList messageList, QString tag)
{
    QString message;
    foreach (message, messageList)
    {
        sendMsg(tb, message, tag);
    }
}

void sendMsg(QTextBrowser *tb, QList<double> messageList, QString tag)
{
    double message;
    foreach (message, messageList)
    {
        sendMsg(tb, QString::number(message), tag);
    }
}

void sendMsg(QTextBrowser *tb, QList<int> messageList, QString tag)
{
    int message;
    foreach (message, messageList)
    {
        sendMsg(tb, QString::number(message), tag);
    }
}

void clear(QTextBrowser *tb){
    tb->clear();
    return;
}

}
