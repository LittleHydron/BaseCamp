#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H

#include <iostream>
#include <vector>
#include <tuple>
#include <QPlainTextEdit>

#define MINIMUM_COEFFICIENT 6

namespace StringTools {
    QString extractFileName(QString &);
void formatText(Qt::GlobalColor, QPlainTextEdit *, int, int);
    template<class CONTAINER>
    int findLCS(CONTAINER &container1, CONTAINER &container2, std::vector<int> *res1=nullptr, std::vector<int> *res2=nullptr) {
        int n = container1.size(), m = container2.size();
        if (n == 0) {
            if (m == 0) {
                return 1;
            } else {
                return 0;
            }
        } else {
            if (m == 0) {
                return 0;
            }
        }
        std::vector < std::vector < int > > dp(n+1, std::vector<int>(m+1));

        for (int i=1; i<n+1; ++ i) {
            for (int j=1; j<m+1; ++ j) {
                dp[i][j] = dp[i-1][j-1];
                if (container1[i-1] == container2[j-1]) {
                    ++ dp[i][j];
                }
                dp[i][j] = std::max({dp[i][j], dp[i-1][j], dp[i][j-1]});
            }
        }
        if (res1 != nullptr) {
            int i=n, j=m;
            while(i>0 && j>0) {
                if (container1[i-1] == container2[j-1]) {
                    res1->push_back(i-1);
                    res2->push_back(j-1);
                    -- i;
                    -- j;
                } else {
                    int i1 = i-1, j1 = j-1;
                    if (dp[i-1][j] > dp[i1][j1]) {
                        i1 = i-1, j1 = j;
                    }
                    if (dp[i][j-1] > dp[i1][j1]) {
                        i1 = i, j1 = j-1;
                    }
                    i = i1, j = j1;
                }
            }
            res1->push_back(-1);
            res2->push_back(-1);
            std::reverse(res1->begin(), res1->end());
            std::reverse(res2->begin(), res2->end());
            res1->push_back(container1.size());
            res2->push_back(container2.size());
        }
        return dp[n][m];
    }
    int coefficient(std::string &, std::string &);
};

#endif // STRINGTOOLS_H
