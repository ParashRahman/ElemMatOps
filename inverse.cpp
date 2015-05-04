#include "matrix.cpp"

matrix get_inverse_input();

int main(){
  matrix mat = get_inverse_input();
  reduced_row_echelon(mat);
  illustrate_matrix(mat);
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
