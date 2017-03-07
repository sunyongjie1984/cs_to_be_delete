/* File strauss:~caviness/Class/CISC320-02S/examples/optBST/obst.cc
 *
 * A program to compute and print the cost and root arrays as discussed 
 * in lecture for generating optimal binary search trees.
 *
 * 4/17/02, 3PM
 * This program was updated with comments and some clarifying changes in 
 * variable names
 */

#include <limits.h>
#include <iostream>
#include <iomanip>
using std::cout;
using std::endl;
using std::setw;

// Declare global variables
int n = 7;
int*   freq = new int[n+1];	// freq[i] = frequency of key[i]
char** key  = new char*[n+1];

int**  cost = new int*[n+2];	// cost[i,j] is cost of optimal bst for
                                // keys K[i],K[i+1],...,K[j]. Thus, cost[1,n]
                                // is the minimum cost of a bst with n nodes.
int**  root = new int*[n+1];	// root[i,j] = r where K[r] is the root of
            			        // the optimal bst for keys K[i],...,K[j].
				                // Thus key[r], r=root[1,n], is the key of the
				                // root of the optimal bst for n nodes, and
                                // key[root[1,r-1]] is the key of the root
                                // of the left-subtree & key[root[r+1,n]]
                                // is the key of the root of the right subtree.
     
void optBST(int n);
void printOBST(int i, int j);

int main(){
    memset(key, 0, (n + 1)*sizeof(char*));
    memset(freq, 0, (n + 1)*sizeof(int));
    memset(cost, 0, (n + 2)*sizeof(int*));
    memset(root, 0, (n + 1)*sizeof(int*));
    int i,j;

    // Allocate space for the 2-dim'l cost array
    for (i = 0; i < n+2; i++)
    {
        cost[i] = new int[n+2];
        memset(cost[i], 0, (n + 2) *sizeof(int));
    }
    // Allocate space for the 2-dim'l root array
    for (i = 0; i < n+1; i++)
    {
        root[i] = new int[n+1];
        memset(root[i], 0, (n + 1) * sizeof(int));
    }

   // Initialize key and freq arrays.  The keys must be entered in order
   // from smallest to largest.
   key[1] = "A"; freq[1] = 4;
   key[2] = "B"; freq[2] = 2;
   key[3] = "C"; freq[3] = 1;
   key[4] = "D"; freq[4] = 3;
   key[5] = "E"; freq[5] = 5;
   key[6] = "F"; freq[6] = 2;
   key[7] = "G"; freq[7] = 1;

   optBST(n);			// Compute optimal bst for keys K[1],...,K[n]

   cout << endl <<"Optimal tree of cost " << cost[1][n] << " is: ";
   printOBST(1,n);		// Print optimal bst using parenthesis notation
   cout << endl << endl;	// for the tree

   // Print the cost array
   cout << endl << "Cost array" << endl;
   for (i = 1; i <= n; i++){
      for (j = 1; j <= n; j++)
         cout << setw(3) << cost[i][j];
      cout << endl << endl;
   }

   // Print the array of roots
   cout << "Root array" << endl;
   for (i = 1; i <= n; i++){
      for (j = 1; j <= n; j++)
         cout << setw(2) << root[i][j];
      cout << endl;
   }
   getchar();
   return 0;
}

// A function to print the optimal bst for keys K[i],K[i+1],...,K[j]
// The tree is printed using parenthesis notation similar to Scheme

void printOBST(int i, int j){
  if (j < i) return;

  cout << "(";
  printOBST(i,root[i][j]-1);	// print left subtree
  cout << key[root[i][j]];	// print root
  printOBST(root[i][j]+1,j);	// print right subtree
  cout << ")";
}

// Calculate the cost and root arrays of the optimal bst for keys
// K[1],K[2],...,K[n]

void optBST(int n){
int i,j,r,t;

for (i = 1; i <= n; i++)        // Initializations that simplify main loop
   for (j = i+1; j <= n+1; j++)
      cost[i][j] = INT_MAX;	// Assuming that the cost of any bst is
				// less than INT_MAX.
for (i = 1; i <= n+1; i++)
   cost[i][i-1] = 0;             // Cost of optimal bst of zero nodes

for (i = 1; i <= n; i++){
   cost[i][i] = freq[i];         // Cost of optimal bst of one node
   root[i][i] = i;		 // Root of optimal bst of one node
}

for (j = 1; j <= n-1; j++)	// Find optimal bsts containing j+1 nodes
   for (i=1; i <= n-j; i++){    // Find optimal bsts for keys K[i],...,K[i+j]
      for (r = i; r <= i+j; r++){ // Try K[r] as the root of t bst for keys
         t = cost[i][r-1] + cost[r+1][i+j]; // K[i],...,K[j]
         if (t < cost[i][i+j]){   // It it has the minimum cost so far
            cost[i][i+j] = t;	  // update cost[i][i+j] and  
            root[i][i+j] = r;     // root[i][i+j]
         }
      }
      /* At this point, we know that the optimal subtree for nodes
       * containing keys K[i], K[i+1], ... , K[i+j] is a tree with root
       * containing key K[r], where r = root[i,i+j], and that the sum of
       * the cost of the two
       * optimal subtrees of the root is stored in cost[i,i+j].  But cost[i,i+j]
       * is not yet the total cost of the optimal tree with root K[r] for
       * we still need to add in the frequency for the root and we need
       * to add in the extra cost when the subtrees are pushed down a
       * level and hence it costs one more step to access each of their nodes.
       * The next loop adds-in these additional costs.
       */
      for (int k = i; k <= i+j; cost[i][i+j] += freq[k++])
         ; // empty body
      // Actually, the sum = freq[i] + ... + freq[i+j] need be computed
      // only once for each value of i and j and the sum then added to 
      // cost[i][i+j] at this point, i.e.,  cost[i][i+j] += sum;
   }
}