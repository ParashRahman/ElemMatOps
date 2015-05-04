#include "matrix.cpp"

matrix get_inverse_input();
void reduced_row_echelon_with_steps( matrix& M );
void set_small_to_zero( matrix& M, int rows, int cols );


int main(){
  matrix mat = get_inverse_input();
  reduced_row_echelon_with_steps(mat);
}

matrix get_inverse_input(){
  int side;
  int augs;
  double in;

  vector< vector<double> > mat;
  vector< vector<double> > aug;

  cout << "Enter a square matrix to find the matrix" << endl;
  cout << "Number of rows: ";
  cin >> side;
  augs = side;

  illustrate( side, side, 0 );
  cout << "Enter your matrix values left to right, top to bottom" << endl;

  for (int r = 0; r < side; r++){
    vector<double> temp;
    mat.push_back(temp);
    for (int c = 0; c < side; c++){
      cin >> in;
      mat[r].push_back(in);
    }
    if (augs) {
      vector<double> temp2;
      aug.push_back(temp2);
      for ( int a = 0; a < augs; a++ ){
	if ( a == r ){ 
	  aug[r].push_back( 1 );
	} else {
	  aug[r].push_back( 0 );
	}
      }
    }
  }

  matrix ret;
  ret.main = mat;
  ret.augm = aug;
  ret.augmented=true;

  return ret;
}

// NOT FINISHED
void reduced_row_echelon_with_steps(matrix& M){

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
    set_small_to_zero( M, rows, cols );
    cout << endl << "Step " << current_col + 1 << ":" << endl;
    illustrate_matrix( M );
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
  
  set_small_to_zero( M, rows, cols );

  cout << endl << "Final:" << endl;
  illustrate_matrix( M );
}

void set_small_to_zero( matrix& M, int rows, int cols ){
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
