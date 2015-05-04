#include <iostream>
#include "matrix.cpp"

int main(){
  matrix mat = get_input();
  reduced_row_echelon( mat );
  illustrate_matrix( mat );
}
