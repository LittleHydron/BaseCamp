#ifndef STRINGTOOLS_H
#define STRINGTOOLS_H

/*

StringTools is a namespace with functions for working with strings

*/

#include <iostream>
#include <vector>
#include <tuple>
#include <QPlainTextEdit>

// Minimum coefficient value needed to determine that two strings can be marked as yellow
#define MINIMUM_COEFFICIENT 6

namespace StringTools {
    QString extractFileName(QString &);                           // function that extracts file name from its absolute path
    void formatText(Qt::GlobalColor, QPlainTextEdit *, int, int); // function that paints part of line in QPlainTextEdit into given color
    int coefficient(std::string &, std::string &);                // function that computes the "coefficient of similarity" of two strings

    template<class CONTAINER>
    int findLCS(CONTAINER &container1, CONTAINER &container2, std::vector<int> *res1=nullptr, std::vector<int> *res2=nullptr) {
        /*
        
        This function computes Longest Common Subsequence of two sequences (container1 and container2) using dynamic programming approach.
        vectors res1 and res2 will contain indexes of elements that are part of LCS.
        res1 contains indexes from first sequence, res2 - from second.

        */
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
        /*
        
        dp[i][j] will contain length of the longest common subsequence of the prefix of length 'i' of the first container and the 
        prefix of length 'j' of the second container.
        
        */

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
            /*
            
            Now, using dp[][], we find, which elements of each container are used to build LCS and store these indexes in res1 and res2.
            
            */
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
            /*
            
            Here we add 'dummy' elements in the front and back of res1 and res2.
            It's needed to make it easier to iterate through these vectors in the future
            
            */
            res1->push_back(-1);
            res2->push_back(-1);
            std::reverse(res1->begin(), res1->end());
            std::reverse(res2->begin(), res2->end());
            res1->push_back(container1.size());
            res2->push_back(container2.size());
        }
        /*
        
        dp[n][m] now contains LCS of our containers
        
        */
        return dp[n][m];
    }
};

#endif // STRINGTOOLS_H
