#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <algorithm>
#include <functional>
#include <sstream>

using namespace std;

#define EPSILON 0.00001

#include "matrix.h"

void illustrate_matrix(const matrix& M){
  int rows = M.main.size();
  int cols = M.main[0].size();
  int aug_cols = M.augm[0].size();

  vector<int> col_padding;
  vector<int> aug_padding;

  for ( int c = 0; c < cols; c++ ) { 
    int maxi = 0;
    for ( int r = 0; r < rows; r++ ) {
      int p = places( M.main[r][c] );
      maxi = max( p, maxi );
    }
    col_padding.push_back( maxi );
  }
  
  if ( M.augmented ){
    for ( int c = 0; c < aug_cols; c++ ) {
      int maxi = 0;
      for ( int r = 0; r < rows; r++ ) {
	int p = places( M.augm[r][c] );
	maxi = max( p, maxi );
      }
      aug_padding.push_back( maxi );
    }
  }

  for ( int r = 0; r < rows; r++ ){
    for ( int c = 0; c < cols; c++ ){
      cout<<M.main[r][c]<<string(col_padding[c]-places(M.main[r][c]) + 1, ' ');
    }
    if ( M.augmented ) {
      cout << "| ";
      for ( int a = 0; a < aug_cols; a++ ){
	cout<<
	  M.augm[r][a]<<
	  string(aug_padding[a]-places(M.augm[r][a]) + 1, ' ');
      }
    }
    cout << endl;
  }
}

void illustrate(int row, int col){
  illustrate(row, col, 0);
}

void illustrate(int row, int col, int augcol){
  const int padding = places(row-1) + places(col-1) + 2;
  int augcount = 0;
  const int augpadding = places(augcol*row-1);

  for (int i = 0; i < row; i++){
    cout << "[ ";
    for(int j = 0; j < col; j++){
      cout << i << "," << j << string(padding - places(i) - places(j) - 1,' ');
    }
    if(augcol){
      cout << "| ";
      for(int a = 0; a < augcol; a++){
	cout << "a" << 
	  a + augcount << 
	  string(augpadding - places(a+augcount) + 1, ' ');
      }
      augcount+=augcol;
    }
    cout << "]" << endl;
  }
}

int places(double value){
  ostringstream s;
  s << value;

  return s.str().size();
}

matrix get_input(){
  int rows;
  int cols;
  int augs;
  double in;

  vector< vector<double> > mat;
  vector< vector<double> > aug;

  cout << "Number of rows: ";
  cin >> rows;
  cout << "Number of columns: ";
  cin >> cols;
  cout << "Number of augmented matrix columns: (Enter 0, if this is not an augmented matrix) ";
  cin >> augs;

  illustrate(rows, cols, augs);
  cout << "Enter your matrix values left to right, top to bottom" << endl;

  for (int r = 0; r < rows; r++){
    vector<double> temp;
    mat.push_back(temp);
    for (int c = 0; c < cols; c++){
      cin >> in;
      mat[r].push_back(in);
    }
    if (augs) {
      vector<double> temp2;
      aug.push_back(temp2);
      for (int a = 0; a < augs; a++){
	cin >> in;
	aug[r].push_back(in);
      }
    }
  }

  matrix ret;
  ret.main = mat;
  ret.augm = aug;
  if(augs){
    ret.augmented=true;
  }else{
    ret.augmented=false;
  }

  return ret;
}

void reduced_row_echelon(matrix& M){

  int rows = M.main.size();
  int cols = M.main[0].size();
  int current_col = 0;

  vector<int> rows_dealt_with;

  while (current_col < cols){
    int r;

    for ( r = 0; r < rows; r++ ) {

      // If the number is not 0 and the row is not already dealt with
      bool condition1 = ! double_compare(0, M.main[r][current_col]);
      bool condition2 = find(rows_dealt_with.begin(), rows_dealt_with.end(), r)== rows_dealt_with.end();

      if ( condition1 && condition2 ) {
	rows_dealt_with.push_back(r);
	break;
      }

    }

    if ( r == rows){
      // Do nothing
    } else {
      double multiplier = 1/M.main[r][current_col];
      scalar_multiplication(M.main[r],  multiplier);
      if ( M.augmented ){
	scalar_multiplication(M.augm[r], multiplier);
      }

      for ( int i = 0; i < rows; i++ ) {
	if ( i != r && !double_compare(M.main[i][current_col], 0) ){
	  multiplier = 1/M.main[i][current_col];
	  scalar_multiplication(M.main[i], multiplier);
	  row_subtract(M.main[i], M.main[r]);
	  if ( M.augmented ) {
	    scalar_multiplication(M.augm[i], multiplier);
	    row_subtract(M.augm[i], M.augm[r]);
	  }
	}
      }
    } // end of else

    current_col++;
  } // end of while

 
  // Fix up leading ones
  for ( int r = 0; r < rows; r++ ) {
    for ( int c = 0; c < cols; c++ ){
      if ( !double_compare( M.main[r][c], 0 ) ){
	if ( double_compare( M.main[r][c], 1 ) ){
	  break;
	} else {
	  double num = 1/M.main[r][c];
	  scalar_multiplication( M.main[r], num );
	  if ( M.augmented ){
	    scalar_multiplication( M.augm[r], num );
	  }
	  break;
	}
      }
    }
  }

  // Set small numbers to 0
  for ( int r = 0; r < rows; r++ ){
    for ( int c = 0; c < cols; c++ ){
      if ( double_compare( M.main[r][c], 0 ) ){
	M.main[r][c] = 0.0;
      }
    }
    if ( M.augmented ){
      int a_cols = M.augm[0].size();
      for ( int c = 0; c < a_cols; c++ ){
	if ( double_compare( M.augm[r][c], 0 ) ){
	  M.augm[r][c] = 0.0;
	}
      }
    }
  }

}

// scalar multiplication for 1 dimensional vector
void scalar_multiplication(vector<double>& v, double s){
  transform(v.begin(), v.end(), v.begin(),
	    bind1st(multiplies<double>(), s)); 
}

// Vectors should be of same length
void row_subtract(vector<double>& subtract_from, vector<double> subtractor){
  for(int i = 0; i < subtract_from.size(); i++){
    subtract_from[i] -= subtractor[i];
  }
}

// Return true if n == m
// Return false if n != m
bool double_compare(double n, double m){
  return abs(n-m) < EPSILON;
}
