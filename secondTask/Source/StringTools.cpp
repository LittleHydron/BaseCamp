#include "StringTools.h"

void StringTools::formatText(Qt::GlobalColor color, QPlainTextEdit *textField, int from, int to) {
    QTextCharFormat fmt;
    fmt.setBackground(color);
    QTextCursor cursor(textField->document());
    cursor.setPosition(from, QTextCursor::MoveAnchor);
    cursor.setPosition(to, QTextCursor::KeepAnchor);
    cursor.setCharFormat(fmt);
}

QString StringTools::extractFileName(QString &path) {
    QString ans = "";
    for (int i=path.length()-1; i>-1; -- i) {
        if (path[i] == '/') {
            break;
        }
        ans += path[i];
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

int StringTools::coefficient(std::string &str1, std::string &str2) {
    /*
    
    This function computes 'similarity coefficient' of two strings.

    It is used to determine, how similar these strings are (from 0 to 10).
    The bigger it is, the less number of changes is needed to recieve one string from another.
    
    */
    if (str1.length() == 0) {
        if (str2.length() == 0) {
            return 10;
        } else {
            return 0;
        }
    } else {
        if (str2.length() == 0) {
            return 0;
        }
    }
    int lcs = findLCS(str1, str2);
    return 20*lcs / (str1.length() + str2.length());
}
